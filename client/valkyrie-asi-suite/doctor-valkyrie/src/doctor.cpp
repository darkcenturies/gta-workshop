#include "doctor.h"

#include <windows.h>
#include <tlhelp32.h>

#include <cstdint>
#include <cctype>
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "crashwindow.h"
#include "cleowatch.h"
#include "doctorlist.h"
#include "log.h"
#include "reportpaths.h"
#include "resource.h"
#include "version.h"
#include "crashfix_support.h"

namespace doctor {
namespace {

// ---------------------------------------------------------------------------
// What the game was doing when it died.
//
// "Last file loaded" and "Last library loaded" are the two fields that identify
// most GTA San Andreas crashes, and they are the two a crash address cannot give
// you. We record them ourselves rather than parse another ASI's log, because the log
// is written after the crash and we want the values at the moment of it.
//
// San Andreas links its CRT statically, so the game's own fopen calls come out
// through gta_sa.exe's import of CreateFileA. Hooking the import table gets the
// engine's file loads and every plugin's alongside them, and unlike a code
// detour it cannot land on the wrong address in a build we did not expect.
// ---------------------------------------------------------------------------

CRITICAL_SECTION g_lock;
bool g_lockReady = false;

char g_lastFile[MAX_PATH] = {0};
char g_lastLibrary[MAX_PATH] = {0};
char g_gameRoot[MAX_PATH] = {0};
char g_userProfile[MAX_PATH] = {0};
constexpr size_t kFileHistoryCapacity = 2048;
constexpr size_t kLibraryHistoryCapacity = 256;
char g_fileHistory[kFileHistoryCapacity][MAX_PATH] = {};
char g_libraryHistory[kLibraryHistoryCapacity][MAX_PATH] = {};
unsigned long long g_fileHistoryCount = 0;
unsigned long long g_libraryHistoryCount = 0;

LPTOP_LEVEL_EXCEPTION_FILTER g_previousFilter = nullptr;
// This is a re-entrancy guard, not a once-per-process latch. another ASI and other
// reporters can invoke a filter for a recoverable startup fault; if play then
// continues, a later real crash still needs its own report.
volatile LONG g_reporting = 0;
volatile LONG g_reportSequence = 0;
bool g_installed = false;
bool g_showWindow = true;
bool g_knownDiagnosis = false;
void* g_emergencyReserve = nullptr;

struct EnvironmentInfo {
    char launchedExe[MAX_PATH];
    char doctorModule[MAX_PATH];
    char currentDirectory[MAX_PATH];
    char processLayer[512];
    char peLayers[1024];
    char saLayers[1024];
    char dashSaLayers[1024];
    char launcherLayers[1024];
    bool elevated;
    bool compatibilityShim;
    bool workingDirectoryMismatch;
    bool doctorMisplaced;
    int otherGameProcesses;
};

EnvironmentInfo g_environment{};
LONG WINAPI OnUnhandled(EXCEPTION_POINTERS* pointers);

// another ASI can replace the executable's imported SetUnhandledExceptionFilter
// entry. Calling the statically imported symbol here therefore only asks
// another ASI's shim to install us; it does not guarantee Windows will ever call us.
// Resolve KernelBase directly, which is where the real implementation lives on
// supported Windows. This leaves another ASI's own import hook untouched.
using SetUnhandledExceptionFilterFn =
    LPTOP_LEVEL_EXCEPTION_FILTER(WINAPI*)(LPTOP_LEVEL_EXCEPTION_FILTER);

SetUnhandledExceptionFilterFn NativeSetUnhandledExceptionFilter() {
    static SetUnhandledExceptionFilterFn fn = []() {
        HMODULE kernelBase = GetModuleHandleA("KernelBase.dll");
        if (kernelBase) {
            if (auto direct = reinterpret_cast<SetUnhandledExceptionFilterFn>(
                    GetProcAddress(kernelBase, "SetUnhandledExceptionFilter"))) {
                return direct;
            }
        }
        // Older Windows may not expose KernelBase. This is a compatibility
        // fallback; modern Windows installations take the direct path above.
        return &SetUnhandledExceptionFilter;
    }();
    return fn;
}

LPTOP_LEVEL_EXCEPTION_FILTER InstallNativeUnhandledFilter() {
    return NativeSetUnhandledExceptionFilter()(&OnUnhandled);
}

// Filled in by WriteReport so the window can show what we just wrote without
// reading the file back.
char g_reportPath[MAX_PATH] = {0};
std::string g_diagnosis;
std::string g_diagnosisSpanish;
cleowatch::Watcher g_cleoWatcher;

using CreateFileAFn = HANDLE(WINAPI*)(LPCSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES,
                                      DWORD, DWORD, HANDLE);
using CreateFileWFn = HANDLE(WINAPI*)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES,
                                      DWORD, DWORD, HANDLE);
using LoadLibraryAFn = HMODULE(WINAPI*)(LPCSTR);
using LoadLibraryWFn = HMODULE(WINAPI*)(LPCWSTR);
using LoadLibraryExAFn = HMODULE(WINAPI*)(LPCSTR, HANDLE, DWORD);
using LoadLibraryExWFn = HMODULE(WINAPI*)(LPCWSTR, HANDLE, DWORD);

CreateFileAFn g_createFileA = nullptr;
CreateFileWFn g_createFileW = nullptr;
LoadLibraryAFn g_loadLibraryA = nullptr;
LoadLibraryWFn g_loadLibraryW = nullptr;
LoadLibraryExAFn g_loadLibraryExA = nullptr;
LoadLibraryExWFn g_loadLibraryExW = nullptr;

const char* BaseName(const char* path) {
    if (!path) return "";
    const char* slash = strrchr(path, '\\');
    const char* fwd = strrchr(path, '/');
    if (fwd > slash) slash = fwd;
    return slash ? slash + 1 : path;
}

bool ContainsInsensitive(const char* text, const char* needle) {
    if (!text || !needle || !*needle) return false;
    const size_t needleLength = strlen(needle);
    for (const char* p = text; *p; ++p) {
        if (_strnicmp(p, needle, needleLength) == 0) return true;
    }
    return false;
}

std::string SpanishDuplicateLines(std::string text) {
    const struct { const char* from; const char* to; } words[] = {
        {" loaded ", " cargado "}, {" times:", " veces:"},
    };
    for (const auto& word : words) {
        size_t at = 0;
        while ((at = text.find(word.from, at)) != std::string::npos) {
            text.replace(at, strlen(word.from), word.to);
            at += strlen(word.to);
        }
    }
    return text;
}

bool QueryLayerView(HKEY root, REGSAM view, const char* executable,
                    char* out, size_t outSize) {
    HKEY key = nullptr;
    const char* subkey =
        "Software\\Microsoft\\Windows NT\\CurrentVersion\\"
        "AppCompatFlags\\Layers";
    if (RegOpenKeyExA(root, subkey, 0, KEY_QUERY_VALUE | view, &key) != ERROR_SUCCESS) {
        return false;
    }
    DWORD type = 0;
    DWORD bytes = static_cast<DWORD>(outSize);
    const LONG result =
        RegQueryValueExA(key, executable, nullptr, &type,
                         reinterpret_cast<BYTE*>(out), &bytes);
    RegCloseKey(key);
    if (result != ERROR_SUCCESS || (type != REG_SZ && type != REG_EXPAND_SZ)) {
        if (outSize) out[0] = '\0';
        return false;
    }
    out[outSize - 1] = '\0';
    return true;
}

void QueryCompatibilityLayers(const char* executable, char* out, size_t outSize) {
    if (!outSize) return;
    out[0] = '\0';
    const struct {
        HKEY root;
        const char* label;
    } locations[] = {
        {HKEY_CURRENT_USER, "user"},
        {HKEY_LOCAL_MACHINE, "machine"},
    };
    for (const auto& location : locations) {
        char value[512] = {0};
        bool found = QueryLayerView(location.root, KEY_WOW64_64KEY, executable,
                                    value, sizeof(value));
        if (!found) {
            found = QueryLayerView(location.root, KEY_WOW64_32KEY, executable,
                                   value, sizeof(value));
        }
        if (!found || !value[0]) continue;
        if (out[0]) strncat_s(out, outSize, "; ", _TRUNCATE);
        strncat_s(out, outSize, location.label, _TRUNCATE);
        strncat_s(out, outSize, ": ", _TRUNCATE);
        strncat_s(out, outSize, value, _TRUNCATE);
    }
}

bool IsElevated() {
    HANDLE token = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) return false;
    TOKEN_ELEVATION elevation{};
    DWORD bytes = 0;
    const bool elevated =
        GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation),
                            &bytes) &&
        elevation.TokenIsElevated != 0;
    CloseHandle(token);
    return elevated;
}

int OtherGameProcesses() {
    int count = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return 0;
    PROCESSENTRY32 process{};
    process.dwSize = sizeof(process);
    if (Process32First(snapshot, &process)) {
        do {
            if (process.th32ProcessID == GetCurrentProcessId()) continue;
            if (_stricmp(process.szExeFile, "gta_sa.exe") == 0 ||
                _stricmp(process.szExeFile, "gta-sa.exe") == 0) {
                ++count;
            }
        } while (Process32Next(snapshot, &process));
    }
    CloseHandle(snapshot);
    return count;
}

void CaptureEnvironment(const char* gameFolder, HMODULE self) {
    GetModuleFileNameA(nullptr, g_environment.launchedExe,
                       sizeof(g_environment.launchedExe));
    GetModuleFileNameA(self, g_environment.doctorModule,
                       sizeof(g_environment.doctorModule));
    GetCurrentDirectoryA(sizeof(g_environment.currentDirectory),
                         g_environment.currentDirectory);
    GetEnvironmentVariableA("__COMPAT_LAYER", g_environment.processLayer,
                            sizeof(g_environment.processLayer));
    g_environment.elevated = IsElevated();
    g_environment.compatibilityShim =
        GetModuleHandleA("AcGenral.dll") != nullptr ||
        GetModuleHandleA("AcLayers.dll") != nullptr;
    g_environment.otherGameProcesses = OtherGameProcesses();
    char expectedDirectory[MAX_PATH] = {0};
    strncpy_s(expectedDirectory, sizeof(expectedDirectory), gameFolder, _TRUNCATE);
    const size_t folderLength = strlen(expectedDirectory);
    if (folderLength && expectedDirectory[folderLength - 1] == '\\') {
        expectedDirectory[folderLength - 1] = '\0';
    }
    g_environment.workingDirectoryMismatch =
        _stricmp(expectedDirectory, g_environment.currentDirectory) != 0;
    char expectedDoctor[MAX_PATH] = {0};
    _snprintf_s(expectedDoctor, sizeof(expectedDoctor), _TRUNCATE,
                "%sdoctor-valkyrie.asi", gameFolder);
    g_environment.doctorMisplaced =
        _stricmp(expectedDoctor, g_environment.doctorModule) != 0;

    struct Target {
        const char* name;
        char* layers;
        size_t size;
    } targets[] = {
        {"gta_sa.exe", g_environment.saLayers, sizeof(g_environment.saLayers)},
        {"gta-sa.exe", g_environment.dashSaLayers,
         sizeof(g_environment.dashSaLayers)},
    };
    for (const auto& target : targets) {
        char path[MAX_PATH] = {0};
        _snprintf_s(path, sizeof(path), _TRUNCATE, "%s%s", gameFolder, target.name);
        QueryCompatibilityLayers(path, target.layers, target.size);
    }
}

bool HasWindowsVersionLayer(const char* layers) {
    const char* versions[] = {
        "NT4SP5", "WIN2000", "WIN95", "WIN98", "WINXPSP1",
        "WINXPSP2", "WINXPSP3", "VISTARTM", "VISTASP1",
        "VISTASP2", "WIN7RTM", "WIN8RTM", "WIN81RTM",
        "WIN10RTM", "WIN11RTM",
    };
    for (const char* version : versions) {
        if (ContainsInsensitive(layers, version)) return true;
    }
    return false;
}

bool CompatibilityModeActive() {
    const bool peCompat = HasWindowsVersionLayer(g_environment.peLayers);
    const bool saCompat = HasWindowsVersionLayer(g_environment.saLayers) ||
                          HasWindowsVersionLayer(g_environment.dashSaLayers);
    const bool launcherCompat =
        HasWindowsVersionLayer(g_environment.launcherLayers);
    const bool processCompat = HasWindowsVersionLayer(g_environment.processLayer);
    return peCompat || saCompat || launcherCompat || processCompat;
}

std::string EnvironmentWarnings(bool includeCompatibility = true) {
    std::string warnings;
    if (includeCompatibility && CompatibilityModeActive())
        warnings += "\n\nENVIRONMENT REVIEW: Windows compatibility settings are active. Compare behavior with and without them; their presence alone does not establish the crash cause.";
    if (g_environment.otherGameProcesses)
        warnings += "\n\nENVIRONMENT REVIEW: Another GTA process was running at startup.";
    if (g_environment.workingDirectoryMismatch)
        warnings += "\n\nENVIRONMENT REVIEW: The working directory differs from the game folder.";
    return warnings;
}

std::string SpanishEnvironmentWarnings(bool includeCompatibility = true) {
    std::string warnings;
    if (includeCompatibility && CompatibilityModeActive()) {
        warnings += "\n\nADVERTENCIA DEL ENTORNO: El modo de compatibilidad "
                    "de Windows está activo. Desactívelo en los cuatro "
                    "ejecutables de GTA San Andreas.";
    }
    const bool peAdmin = ContainsInsensitive(g_environment.peLayers, "RUNASADMIN");
    const bool saAdmin = ContainsInsensitive(g_environment.saLayers, "RUNASADMIN") ||
                         ContainsInsensitive(g_environment.dashSaLayers, "RUNASADMIN");
    const bool launcherAdmin =
        ContainsInsensitive(g_environment.launcherLayers, "RUNASADMIN");
    if (peAdmin != saAdmin || peAdmin != launcherAdmin || saAdmin != launcherAdmin) {
        warnings += "\n\nADVERTENCIA DEL ENTORNO: Solo algunos ejecutables "
                    "están configurados como administrador. Desactive esa "
                    "opción en los cuatro.";
    } else if (g_environment.elevated) {
        warnings += "\n\nADVERTENCIA DEL ENTORNO: El juego se ejecuta como "
                    "administrador. Ejecútelo normalmente.";
    }
    if (g_environment.otherGameProcesses > 0) {
        warnings += "\n\nADVERTENCIA DEL ENTORNO: Ya había otro proceso de "
                    "GTA San Andreas/GTA activo. Cierre todos los procesos del "
                    "juego y del iniciador antes de intentarlo de nuevo.";
    }
    if (g_environment.workingDirectoryMismatch) {
        warnings += "\n\nADVERTENCIA DEL ENTORNO: El directorio de trabajo "
                    "no es la carpeta de GTA San Andreas. Use el acceso directo "
                    "normal o corrija el campo «Iniciar en».";
    }
    if (g_environment.doctorMisplaced) {
        warnings += "\n\nADVERTENCIA DEL ENTORNO: Doctor Valkyrie se cargó "
                    "desde una ubicación no estándar. Conserve una sola copia "
                    "en la carpeta principal de GTA San Andreas.";
    }
    return warnings;
}

int LoadEmbeddedRules(HMODULE self, int resourceId, const char* sourceName) {
    HRSRC resource =
        FindResourceA(self, MAKEINTRESOURCEA(resourceId), RT_RCDATA);
    if (!resource) return -1;
    const DWORD size = SizeofResource(self, resource);
    if (!size) return -1;
    HGLOBAL loaded = LoadResource(self, resource);
    if (!loaded) return -1;
    const void* data = LockResource(loaded);
    if (!data) return -1;
    try {
        return doctorlist::LoadText(static_cast<const char*>(data), size,
                                    sourceName);
    } catch (...) {
        return -1;
    }
}

int LoadEmbeddedSpanish(HMODULE self, int resourceId) {
    HRSRC resource = FindResourceA(self, MAKEINTRESOURCEA(resourceId), RT_RCDATA);
    if (!resource) return -1;
    const DWORD size = SizeofResource(self, resource);
    HGLOBAL loaded = size ? LoadResource(self, resource) : nullptr;
    const void* data = loaded ? LockResource(loaded) : nullptr;
    if (!data) return -1;
    try {
        return doctorlist::LoadSpanishText(static_cast<const char*>(data), size);
    } catch (...) {
        return -1;
    }
}

int LoadFileRules(const char* path, const char* sourceName) {
    try {
        return doctorlist::Load(path, sourceName);
    } catch (...) {
        return -1;
    }
}

// Our own logs are not evidence about the crash, and recording them is how a
// log ends up saying "Last file loaded: the previous crash log" - which is the
// single most common way a GTA San Andreas crash report arrives useless. 64 of
// the 219 logs we studied were self-diagnosing like that. Skip our own writes.
// Keep the tracking hook restricted to the main executable. Mod Loader's
// translator identifies an ASI from its return address, so rewriting another
// ASI's imports is unsafe; the x86 wrappers below preserve GTA's caller stack
// while still recording the engine's own stream/file activity.
bool Uninteresting(const char* name) {
    if (!name || !*name) return true;
    const char* base = BaseName(name);
    const size_t len = strlen(base);
    if (len > 4 && _stricmp(base + len - 4, ".log") == 0) return true;
    if (_strnicmp(base, "doctor-valkyrie", 15) == 0) return true;
    return false;
}

void RecordFile(const char* path) {
    if (Uninteresting(path) || !g_lockReady) return;
    EnterCriticalSection(&g_lock);
    strncpy_s(g_lastFile, sizeof(g_lastFile), path, _TRUNCATE);
    strncpy_s(g_fileHistory[g_fileHistoryCount % kFileHistoryCapacity],
              MAX_PATH, path, _TRUNCATE);
    ++g_fileHistoryCount;
    LeaveCriticalSection(&g_lock);
}

void RecordFileW(LPCWSTR path) {
    if (!path || !g_lockReady) return;
    char narrow[MAX_PATH];
    const int n = WideCharToMultiByte(CP_ACP, 0, path, -1, narrow,
                                      sizeof(narrow), nullptr, nullptr);
    if (n > 0) RecordFile(narrow);
}

void RecordLibrary(const char* path) {
    if (!path || !*path || !g_lockReady) return;
    EnterCriticalSection(&g_lock);
    strncpy_s(g_lastLibrary, sizeof(g_lastLibrary), BaseName(path), _TRUNCATE);
    strncpy_s(g_libraryHistory[g_libraryHistoryCount % kLibraryHistoryCapacity],
              MAX_PATH, path, _TRUNCATE);
    ++g_libraryHistoryCount;
    LeaveCriticalSection(&g_lock);
}

void RecordLibraryW(LPCWSTR path) {
    if (!path) return;
    char narrow[MAX_PATH];
    const int n = WideCharToMultiByte(CP_ACP, 0, path, -1, narrow,
                                      sizeof(narrow), nullptr, nullptr);
    if (n > 0) RecordLibrary(narrow);
}

void SafeRecordFileA(LPCSTR name) {
    __try { RecordFile(name); } __except (EXCEPTION_EXECUTE_HANDLER) {}
}
void SafeRecordFileW(LPCWSTR name) {
    __try { RecordFileW(name); } __except (EXCEPTION_EXECUTE_HANDLER) {}
}
void SafeRecordLibraryA(LPCSTR name) {
    __try { RecordLibrary(name); } __except (EXCEPTION_EXECUTE_HANDLER) {}
}
void SafeRecordLibraryW(LPCWSTR name) {
    __try { RecordLibraryW(name); } __except (EXCEPTION_EXECUTE_HANDLER) {}
}

#if defined(_M_IX86)
// Mod Loader's std.asi path translator identifies the calling ASI from the
// return address on the stack. A normal C++ forwarding call makes that return
// address point into Doctor Valkyrie and triggers
// "translator.SetupASI failed to identify caller ASI". These wrappers record
// argument 1, restore the entry stack exactly, then tail-jump to the original
// target so std.asi still sees the real GTA caller.
__declspec(naked) void WINAPI OnCreateFileA() { __asm {
    pushad
    push dword ptr [esp + 36]
    call SafeRecordFileA
    add esp, 4
    popad
    jmp dword ptr [g_createFileA]
} }
__declspec(naked) void WINAPI OnCreateFileW() { __asm {
    pushad
    push dword ptr [esp + 36]
    call SafeRecordFileW
    add esp, 4
    popad
    jmp dword ptr [g_createFileW]
} }
__declspec(naked) void WINAPI OnLoadLibraryA() { __asm {
    pushad
    push dword ptr [esp + 36]
    call SafeRecordLibraryA
    add esp, 4
    popad
    jmp dword ptr [g_loadLibraryA]
} }
__declspec(naked) void WINAPI OnLoadLibraryW() { __asm {
    pushad
    push dword ptr [esp + 36]
    call SafeRecordLibraryW
    add esp, 4
    popad
    jmp dword ptr [g_loadLibraryW]
} }
__declspec(naked) void WINAPI OnLoadLibraryExA() { __asm {
    pushad
    push dword ptr [esp + 36]
    call SafeRecordLibraryA
    add esp, 4
    popad
    jmp dword ptr [g_loadLibraryExA]
} }
__declspec(naked) void WINAPI OnLoadLibraryExW() { __asm {
    pushad
    push dword ptr [esp + 36]
    call SafeRecordLibraryW
    add esp, 4
    popad
    jmp dword ptr [g_loadLibraryExW]
} }
#else
HANDLE WINAPI OnCreateFileA(LPCSTR name, DWORD a, DWORD b,
                            LPSECURITY_ATTRIBUTES c, DWORD d, DWORD e, HANDLE f) {
    SafeRecordFileA(name);
    return g_createFileA(name, a, b, c, d, e, f);
}
HANDLE WINAPI OnCreateFileW(LPCWSTR name, DWORD a, DWORD b,
                            LPSECURITY_ATTRIBUTES c, DWORD d, DWORD e, HANDLE f) {
    SafeRecordFileW(name);
    return g_createFileW(name, a, b, c, d, e, f);
}
HMODULE WINAPI OnLoadLibraryA(LPCSTR name) {
    SafeRecordLibraryA(name);
    return g_loadLibraryA(name);
}
HMODULE WINAPI OnLoadLibraryW(LPCWSTR name) {
    SafeRecordLibraryW(name);
    return g_loadLibraryW(name);
}
HMODULE WINAPI OnLoadLibraryExA(LPCSTR name, HANDLE file, DWORD flags) {
    SafeRecordLibraryA(name);
    return g_loadLibraryExA(name, file, flags);
}
HMODULE WINAPI OnLoadLibraryExW(LPCWSTR name, HANDLE file, DWORD flags) {
    SafeRecordLibraryW(name);
    return g_loadLibraryExW(name, file, flags);
}
#endif

// Swap one resolved import address in one module. Same technique guard.cpp uses
// against S&SMP's Discord pipe, and for the same reason: imports are resolved
// by name, so this finds the right slot in any build and never assumes where
// anyone's code lives.
bool RedirectImport(HMODULE module, const char* dll, const char* function,
                    void* replacement, void** original) {
    const auto base = reinterpret_cast<BYTE*>(module);
    const auto dos = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
    if (IsBadReadPtr(dos, sizeof(*dos)) || dos->e_magic != IMAGE_DOS_SIGNATURE) {
        return false;
    }
    if (dos->e_lfanew <= 0 || dos->e_lfanew > 1024 * 1024) return false;
    const auto nt = reinterpret_cast<IMAGE_NT_HEADERS*>(base + dos->e_lfanew);
    if (IsBadReadPtr(nt, sizeof(*nt)) || nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
        return false;
    }
    const size_t imageSize = nt->OptionalHeader.SizeOfImage;
    if (imageSize < sizeof(*dos) || imageSize > 1024ULL * 1024ULL * 1024ULL) {
        return false;
    }
    const auto inImage = [imageSize](size_t rva, size_t bytes) {
        return rva < imageSize && bytes <= imageSize - rva;
    };
    const auto& directory =
        nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (directory.VirtualAddress == 0 ||
        !inImage(directory.VirtualAddress, sizeof(IMAGE_IMPORT_DESCRIPTOR))) {
        return false;
    }

    auto descriptor = reinterpret_cast<IMAGE_IMPORT_DESCRIPTOR*>(
        base + directory.VirtualAddress);
    const size_t directoryBytes = directory.Size
                                      ? static_cast<size_t>(directory.Size)
                                      : imageSize - directory.VirtualAddress;
    const size_t availableDirectoryBytes =
        imageSize - static_cast<size_t>(directory.VirtualAddress);
    const size_t descriptorBytes = directoryBytes < availableDirectoryBytes
                                       ? directoryBytes
                                       : availableDirectoryBytes;
    const size_t descriptorLimit =
        descriptorBytes / sizeof(IMAGE_IMPORT_DESCRIPTOR);
    for (size_t descriptorIndex = 0; descriptorIndex < descriptorLimit;
         ++descriptorIndex, ++descriptor) {
        if (descriptor->Name == 0) break;
        if (!inImage(descriptor->Name, 1)) continue;
        const char* name = reinterpret_cast<const char*>(base + descriptor->Name);
        const size_t nameRoom = imageSize - descriptor->Name;
        const size_t dllLength = strlen(dll);
        if (dllLength >= nameRoom || name[dllLength] != '\0' ||
            _strnicmp(name, dll, dllLength) != 0) {
            continue;
        }

        // Without the original thunk table, the loader has already replaced
        // import names with function addresses. Treat that uncommon image as
        // unhookable instead of guessing which slot is which.
        if (descriptor->OriginalFirstThunk == 0 ||
            !inImage(descriptor->OriginalFirstThunk, sizeof(IMAGE_THUNK_DATA)) ||
            !inImage(descriptor->FirstThunk, sizeof(IMAGE_THUNK_DATA))) {
            return false;
        }
        auto names = reinterpret_cast<IMAGE_THUNK_DATA*>(
            base + descriptor->OriginalFirstThunk);
        auto addresses = reinterpret_cast<IMAGE_THUNK_DATA*>(
            base + descriptor->FirstThunk);
        const size_t nameLimit =
            (imageSize - descriptor->OriginalFirstThunk) /
            sizeof(IMAGE_THUNK_DATA);
        const size_t addressLimit =
            (imageSize - descriptor->FirstThunk) / sizeof(IMAGE_THUNK_DATA);
        const size_t thunkLimit = (std::min)(nameLimit, addressLimit);

        for (size_t thunkIndex = 0; thunkIndex < thunkLimit;
             ++thunkIndex, ++names, ++addresses) {
            if (names->u1.AddressOfData == 0) break;
            if (IMAGE_SNAP_BY_ORDINAL(names->u1.Ordinal)) continue;
            if (!inImage(names->u1.AddressOfData,
                         sizeof(IMAGE_IMPORT_BY_NAME))) {
                continue;
            }
            const size_t importNameRva =
                static_cast<size_t>(names->u1.AddressOfData) +
                offsetof(IMAGE_IMPORT_BY_NAME, Name);
            if (!inImage(importNameRva, 1)) continue;
            const char* importName =
                reinterpret_cast<const char*>(base + importNameRva);
            const size_t functionLength = strlen(function);
            const size_t importRoom = imageSize - importNameRva;
            if (functionLength >= importRoom ||
                importName[functionLength] != '\0' ||
                memcmp(importName, function, functionLength) != 0) {
                continue;
            }
            DWORD old = 0;
            if (!VirtualProtect(&addresses->u1.Function, sizeof(void*),
                                PAGE_READWRITE, &old)) {
                return false;
            }
            if (reinterpret_cast<void*>(addresses->u1.Function) == replacement) {
                return true;
            }
            if (original) {
                // Mod Loader may replace this import after our first pass.
                // Refresh the tail-jump target before reapplying ours so its
                // translator remains in the call chain.
                *original = reinterpret_cast<void*>(addresses->u1.Function);
            }
            addresses->u1.Function = reinterpret_cast<uintptr_t>(replacement);
            DWORD ignored = 0;
            VirtualProtect(&addresses->u1.Function, sizeof(void*), old, &ignored);
            FlushInstructionCache(GetCurrentProcess(), &addresses->u1.Function,
                                  sizeof(void*));
            return true;
        }
    }
    return false;
}

// Compatibility layers (notably Windows XP mode's AcGenral/AcLayers shims)
// can expose import tables whose entries do not behave like an ordinary PE
// image. A diagnostic plugin must never bring the game down while inspecting
// somebody else's module, so treat any bad table entry as "not hookable".
bool SafeRedirectImport(HMODULE module, const char* dll, const char* function,
                        void* replacement, void** original) {
    __try {
        return RedirectImport(module, dll, function, replacement, original);
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

// Intercept only GTA's own imports. Rewriting another ASI's imports violates
// Mod Loader's caller-translation contract and can break the very mod we are
// supposed to diagnose. Engine streaming still flows through the executable.
void HookMainExecutable() {
    HMODULE executable = GetModuleHandleA(nullptr);
    if (!executable) return;
    SafeRedirectImport(executable, "kernel32.dll", "CreateFileA",
                       reinterpret_cast<void*>(&OnCreateFileA),
                       reinterpret_cast<void**>(&g_createFileA));
    SafeRedirectImport(executable, "kernel32.dll", "CreateFileW",
                       reinterpret_cast<void*>(&OnCreateFileW),
                       reinterpret_cast<void**>(&g_createFileW));
    SafeRedirectImport(executable, "kernel32.dll", "LoadLibraryA",
                       reinterpret_cast<void*>(&OnLoadLibraryA),
                       reinterpret_cast<void**>(&g_loadLibraryA));
    SafeRedirectImport(executable, "kernel32.dll", "LoadLibraryW",
                       reinterpret_cast<void*>(&OnLoadLibraryW),
                       reinterpret_cast<void**>(&g_loadLibraryW));
    SafeRedirectImport(executable, "kernel32.dll", "LoadLibraryExA",
                       reinterpret_cast<void*>(&OnLoadLibraryExA),
                       reinterpret_cast<void**>(&g_loadLibraryExA));
    SafeRedirectImport(executable, "kernel32.dll", "LoadLibraryExW",
                       reinterpret_cast<void*>(&OnLoadLibraryExW),
                       reinterpret_cast<void**>(&g_loadLibraryExW));

    // Anything we failed to find an import for still has to be callable.
    if (!g_createFileA) g_createFileA = &CreateFileA;
    if (!g_createFileW) g_createFileW = &CreateFileW;
    if (!g_loadLibraryA) g_loadLibraryA = &LoadLibraryA;
    if (!g_loadLibraryW) g_loadLibraryW = &LoadLibraryW;
    if (!g_loadLibraryExA) g_loadLibraryExA = &LoadLibraryExA;
    if (!g_loadLibraryExW) g_loadLibraryExW = &LoadLibraryExW;
}

// ---------------------------------------------------------------------------
// Working out where an address lives.
//
// This is what makes the Discord, audio and GPU driver cases diagnosable. Those
// crash inside a module that lands at a different base every launch, so the
// absolute address in the log is different every time and matches nothing. The
// offset within the module is the same every time.
// ---------------------------------------------------------------------------

struct Module {
    uintptr_t base;
    uintptr_t end;
    char name[64];
    char path[MAX_PATH];
};

std::vector<Module> Modules() {
    std::vector<Module> out;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, GetCurrentProcessId());
    if (snapshot == INVALID_HANDLE_VALUE) return out;

    MODULEENTRY32 m{};
    m.dwSize = sizeof(m);
    if (Module32First(snapshot, &m)) {
        do {
            Module entry{};
            entry.base = reinterpret_cast<uintptr_t>(m.modBaseAddr);
            entry.end = entry.base + m.modBaseSize;
            strncpy_s(entry.name, sizeof(entry.name), m.szModule, _TRUNCATE);
            strncpy_s(entry.path, sizeof(entry.path), m.szExePath, _TRUNCATE);
            out.push_back(entry);
        } while (Module32Next(snapshot, &m));
    }
    CloseHandle(snapshot);
    return out;
}

void WriteComprehensiveEvidence(FILE* f, const std::vector<Module>& modules) {
    for (int local = 1; local >= 0; --local) {
        size_t count = 0;
        for (const Module& module : modules) {
            if (reportpaths::IsGameLocal(module.path, g_gameRoot) == (local != 0)) {
                ++count;
            }
        }
        fprintf(f, "\n%s loaded modules at failure (%zu):\n",
                local ? "GTA San Andreas / game-local" : "External / system", count);
        for (const Module& module : modules) {
            if (reportpaths::IsGameLocal(module.path, g_gameRoot) != (local != 0)) {
                continue;
            }
            const std::string path = reportpaths::RedactUserProfile(
                module.path, g_userProfile);
            fprintf(f, "   0x%08X-0x%08X  %s\n      %s\n",
                    static_cast<unsigned>(module.base),
                    static_cast<unsigned>(module.end), module.name, path.c_str());
        }
    }

    // Never wait on a lock that the faulting instruction might itself have
    // held. Losing the history in that rare case is better than hanging the
    // crash reporter; last-file and the module snapshot remain available.
    if (!g_lockReady || !TryEnterCriticalSection(&g_lock)) {
        fprintf(f, "\nFile/library activity history unavailable (tracker busy).\n");
        return;
    }

    const unsigned long long firstFile =
        g_fileHistoryCount > kFileHistoryCapacity
            ? g_fileHistoryCount - kFileHistoryCapacity
            : 0;
    for (int local = 1; local >= 0; --local) {
        unsigned long long count = 0;
        for (unsigned long long i = firstFile; i < g_fileHistoryCount; ++i) {
            if (reportpaths::IsGameLocal(g_fileHistory[i % kFileHistoryCapacity],
                                         g_gameRoot) == (local != 0)) ++count;
        }
        fprintf(f, "\n%s file activity in chronological order (%llu retained%s):\n",
                local ? "GTA San Andreas / game-local" : "External / background",
                count, firstFile ? ", oldest entries omitted" : "");
        for (unsigned long long i = firstFile; i < g_fileHistoryCount; ++i) {
            const char* raw = g_fileHistory[i % kFileHistoryCapacity];
            if (reportpaths::IsGameLocal(raw, g_gameRoot) != (local != 0)) continue;
            const std::string path = reportpaths::RedactUserProfile(raw, g_userProfile);
            fprintf(f, "   [%llu] %s\n", i + 1, path.c_str());
        }
    }

    const unsigned long long firstLibrary =
        g_libraryHistoryCount > kLibraryHistoryCapacity
            ? g_libraryHistoryCount - kLibraryHistoryCapacity
            : 0;
    for (int local = 1; local >= 0; --local) {
        unsigned long long count = 0;
        for (unsigned long long i = firstLibrary; i < g_libraryHistoryCount; ++i) {
            if (reportpaths::IsGameLocal(
                    g_libraryHistory[i % kLibraryHistoryCapacity], g_gameRoot) ==
                (local != 0)) ++count;
        }
        fprintf(f, "\n%s library-load activity (%llu retained%s):\n",
                local ? "GTA San Andreas / game-local" : "External / system",
                count, firstLibrary ? ", oldest entries omitted" : "");
        for (unsigned long long i = firstLibrary; i < g_libraryHistoryCount; ++i) {
            const char* raw = g_libraryHistory[i % kLibraryHistoryCapacity];
            if (reportpaths::IsGameLocal(raw, g_gameRoot) != (local != 0)) continue;
            const std::string path = reportpaths::RedactUserProfile(raw, g_userProfile);
            fprintf(f, "   [%llu] %s\n", i + 1, path.c_str());
        }
    }
    LeaveCriticalSection(&g_lock);
}

// Only report components that were actually loaded, rather than every file in
// Modloader. That avoids blaming dormant backups while still catching the
// dangerous case: two copies of a plugin active in the crashed process.
std::string LoadedDuplicates(const std::vector<Module>& modules) {
    std::vector<doctorlist::LoadedComponent> components;
    components.reserve(modules.size());
    for (const Module& module : modules) {
        components.push_back({module.name, module.path});
    }
    return doctorlist::FindLoadedDuplicates(components);
}

const Module* Owner(const std::vector<Module>& modules, uintptr_t address) {
    for (const Module& m : modules) {
        if (address >= m.base && address < m.end) return &m;
    }
    return nullptr;
}

const char* CodeName(DWORD code) {
    switch (code) {
        case EXCEPTION_ACCESS_VIOLATION: return "Access violation";
        case EXCEPTION_ILLEGAL_INSTRUCTION: return "Illegal instruction";
        case EXCEPTION_INT_DIVIDE_BY_ZERO: return "Integer division by zero";
        case EXCEPTION_FLT_DIVIDE_BY_ZERO: return "Float division by zero";
        case EXCEPTION_PRIV_INSTRUCTION: return "Privileged instruction";
        case EXCEPTION_STACK_OVERFLOW: return "Stack overflow";
        case EXCEPTION_ARRAY_BOUNDS_EXCEEDED: return "Array bounds exceeded";
        case EXCEPTION_IN_PAGE_ERROR: return "In page error";
        case EXCEPTION_DATATYPE_MISALIGNMENT: return "Data type misalignment";
        case 0xE06D7363: return "C++ exception";
        default: return "Unhandled exception";
    }
}

// ---------------------------------------------------------------------------
// The report.
//
// Doctor owns one complete report: raw crash evidence first, then the diagnosis
// and extra findings. This avoids competing crash windows while keeping all
// evidence visible and copyable from Doctor's window.
// ---------------------------------------------------------------------------

void Write(FILE* f, EXCEPTION_POINTERS* pointers,
           const std::vector<Module>& modules) {
    const EXCEPTION_RECORD* record = pointers->ExceptionRecord;
    const CONTEXT* context = pointers->ContextRecord;
    const uintptr_t address = reinterpret_cast<uintptr_t>(record->ExceptionAddress);

    char exe[MAX_PATH] = {0};
    GetModuleFileNameA(nullptr, exe, sizeof(exe));

    SYSTEMTIME now{};
    GetLocalTime(&now);

    fprintf(f, "GTA SA v1.0 HOODLUM, doctor-valkyrie %s, %04d-%02d-%02d %02d:%02d:%02d\n",
            DOCTOR_VALKYRIE_VERSION, now.wYear, now.wMonth, now.wDay,
            now.wHour, now.wMinute, now.wSecond);
    const std::string safeLastFile = reportpaths::RedactUserProfile(
        g_lastFile[0] ? g_lastFile : "(none recorded)", g_userProfile);
    fprintf(f, "Last file loaded: %s\n", safeLastFile.c_str());
    fprintf(f, "Last library loaded: %s\n",
            g_lastLibrary[0] ? g_lastLibrary : "(none recorded)");

    const Module* owner = Owner(modules, address);
    fprintf(f, "Unhandled exception at 0x%08X in %s\n",
            static_cast<unsigned>(address), BaseName(exe));
    if (owner) {
        fprintf(f, "In module: %s+0x%X\n", owner->name,
                static_cast<unsigned>(address - owner->base));
    }
    const char* what = CodeName(record->ExceptionCode);
    if (record->ExceptionCode == EXCEPTION_ACCESS_VIOLATION &&
        record->NumberParameters >= 2) {
        const ULONG_PTR op = record->ExceptionInformation[0];
        fprintf(f, "0x%08lX: %s %s at 0x%08X\n", record->ExceptionCode, what,
                op == 0 ? "read" : (op == 1 ? "write" : "execute"),
                static_cast<unsigned>(record->ExceptionInformation[1]));
    } else {
        fprintf(f, "0x%08lX: %s\n", record->ExceptionCode, what);
    }

#if defined(_M_IX86)
    fprintf(f, "\nRegister dump:\n");
    fprintf(f, "   EAX: 0x%08lX     EBX: 0x%08lX     ECX: 0x%08lX     EDX: 0x%08lX\n",
            context->Eax, context->Ebx, context->Ecx, context->Edx);
    fprintf(f, "   ESI: 0x%08lX     EDI: 0x%08lX     EBP: 0x%08lX     ESP: 0x%08lX\n",
            context->Esi, context->Edi, context->Ebp, context->Esp);
    fprintf(f, "   EIP: 0x%08lX     EFL: 0x%08lX\n", context->Eip,
            context->EFlags);

    fprintf(f, "\nStack dump:\n");
    const auto* stack = reinterpret_cast<const DWORD*>(context->Esp);
    for (int row = 0; row < 16 &&
                      !IsBadReadPtr(stack, sizeof(DWORD) * 6); ++row) {
        fprintf(f, "   0x%08X: ",
                static_cast<unsigned>(reinterpret_cast<uintptr_t>(stack)));
        for (int col = 0; col < 6; ++col) fprintf(f, "%08lX ", stack[col]);
        fprintf(f, "\n");
        stack += 6;
    }

    fprintf(f, "\nBacktrace (may be wrong):\n");
    const auto* scan = reinterpret_cast<const DWORD*>(context->Esp);
    int printed = 0;
    for (int i = 0; i < 1024 && printed < 20; ++i) {
        if (IsBadReadPtr(scan + i, sizeof(DWORD))) break;
        const uintptr_t value = scan[i];
        const Module* module = Owner(modules, value);
        if (!module) continue;
        fprintf(f, "   0x%08X  %s+0x%X\n", static_cast<unsigned>(value),
                module->name, static_cast<unsigned>(value - module->base));
        ++printed;
    }
    if (printed == 0) {
        fprintf(f, "   (nothing on the stack resolved to a module)\n");
    }
#endif
}

void WriteDiagnosis(FILE* f, EXCEPTION_POINTERS* pointers,
                    const std::vector<Module>& modules) {
    const EXCEPTION_RECORD* record = pointers->ExceptionRecord;
    const uintptr_t address = reinterpret_cast<uintptr_t>(record->ExceptionAddress);

    doctorlist::Crash crash;
    crash.code = record->ExceptionCode;
    crash.address = static_cast<unsigned long>(address);
    crash.lastFile = g_lastFile;
    crash.lastLibrary = g_lastLibrary;
    if (const Module* owner = Owner(modules, address)) {
        crash.module = owner->name;
        crash.offset = static_cast<unsigned long>(address - owner->base);
    }

    const std::vector<doctorlist::Match> matches = doctorlist::Find(crash);
    const std::string compatibility = std::string();
    g_knownDiagnosis = !compatibility.empty() || !matches.empty();
    if (!compatibility.empty()) {
        g_diagnosis = compatibility;
        g_diagnosisSpanish = std::string();
        if (!matches.empty()) {
            g_diagnosis +=
                "\n\n---------------------------------------------------------------\n"
                " Other findings from the crash log\n"
                "---------------------------------------------------------------\n\n";
            g_diagnosis += doctorlist::Render(matches);
            g_diagnosisSpanish +=
                "\n\n---------------------------------------------------------------\n"
                " Otros hallazgos del registro del fallo\n"
                "---------------------------------------------------------------\n\n";
            g_diagnosisSpanish += doctorlist::RenderSpanish(matches);
        }
    } else {
        g_diagnosis = doctorlist::Render(matches);
        g_diagnosisSpanish = doctorlist::RenderSpanish(matches);
    }
    g_diagnosis += EnvironmentWarnings(compatibility.empty());
    g_diagnosis += std::string();
    g_diagnosisSpanish += SpanishEnvironmentWarnings(compatibility.empty());
    g_diagnosisSpanish += std::string();
    g_diagnosis = reportpaths::RedactUserProfile(g_diagnosis.c_str(), g_userProfile);
    g_diagnosisSpanish = reportpaths::RedactUserProfile(
        g_diagnosisSpanish.c_str(), g_userProfile);
    fprintf(f, "\n%s", g_diagnosis.c_str());
}

const char* Present(const char* value) {
    return value && *value ? value : "(none)";
}

void WriteEnvironment(FILE* f) {
    const std::string launchedExe = reportpaths::RedactUserProfile(
        Present(g_environment.launchedExe), g_userProfile);
    const std::string doctorModule = reportpaths::RedactUserProfile(
        Present(g_environment.doctorModule), g_userProfile);
    const std::string currentDirectory = reportpaths::RedactUserProfile(
        Present(g_environment.currentDirectory), g_userProfile);
    const std::string peLayers = reportpaths::RedactUserProfile(
        Present(g_environment.peLayers), g_userProfile);
    const std::string saLayers = reportpaths::RedactUserProfile(
        Present(g_environment.saLayers), g_userProfile);
    const std::string dashSaLayers = reportpaths::RedactUserProfile(
        Present(g_environment.dashSaLayers), g_userProfile);
    const std::string launcherLayers = reportpaths::RedactUserProfile(
        Present(g_environment.launcherLayers), g_userProfile);
    fprintf(f,
            "\nEnvironment:\n"
            "   Launched executable: %s\n"
            "   Doctor module:       %s\n"
            "   Working directory:   %s\n"
            "   Running elevated:    %s\n"
            "   __COMPAT_LAYER:       %s\n"
            "   gta_sa.exe layers:    %s\n"
            "   gta_sa.exe layers:    %s\n"
            "   gta-sa.exe layers:    %s\n"
            "   launcher layers:      %s\n"
            "   Compatibility shims: %s\n"
            "   Working-dir match:   %s\n"
            "   Doctor in game root: %s\n"
            "   Other GTA processes:   %d\n",
            launchedExe.c_str(), doctorModule.c_str(), currentDirectory.c_str(),
            g_environment.elevated ? "yes" : "no",
            Present(g_environment.processLayer),
            peLayers.c_str(), saLayers.c_str(), dashSaLayers.c_str(),
            launcherLayers.c_str(),
            g_environment.compatibilityShim ? "loaded" : "not loaded",
            g_environment.workingDirectoryMismatch ? "no" : "yes",
            g_environment.doctorMisplaced ? "no" : "yes",
            g_environment.otherGameProcesses);
}

// The whole report, in one function that owns the C++ objects. Kept separate
// from the filter itself because a function using __try cannot also hold
// objects that need unwinding, and the filter is where the __try has to be.
void WriteReport(EXCEPTION_POINTERS* pointers) {
    char folder[MAX_PATH] = {0};
    GetModuleFileNameA(nullptr, folder, sizeof(folder));
    if (char* slash = strrchr(folder, '\\')) *(slash + 1) = '\0';

    // The same folder another ASI already writes to, so a player told to "post
    // everything in Valkyrie_crashes" posts this too without being asked
    // for anything new.
    SYSTEMTIME now{};
    GetLocalTime(&now);
    const LONG sequence = InterlockedIncrement(&g_reportSequence);
    char preferredDir[MAX_PATH] = {0};
    _snprintf_s(preferredDir, sizeof(preferredDir), _TRUNCATE,
                "%sValkyrie_crashes", folder);
    char temporaryDir[MAX_PATH] = {0};
    char temporaryRoot[MAX_PATH] = {0};
    if (GetTempPathA(sizeof(temporaryRoot), temporaryRoot)) {
        _snprintf_s(temporaryDir, sizeof(temporaryDir), _TRUNCATE,
                    "%sValkyrie_crashes", temporaryRoot);
    }

    FILE* f = nullptr;
    const char* destinations[] = {preferredDir, temporaryDir};
    for (const char* dir : destinations) {
        if (!dir[0]) continue;
        CreateDirectoryA(dir, nullptr);
        _snprintf_s(g_reportPath, sizeof(g_reportPath), _TRUNCATE,
                    "%s\\doctor-valkyrie_%04d-%02d-%02d_%02d-%02d-%02d-%03d_"
                    "pid%lu_%ld.log", dir,
                    now.wYear, now.wMonth, now.wDay, now.wHour, now.wMinute,
                    now.wSecond, now.wMilliseconds, GetCurrentProcessId(),
                    sequence);
        if (fopen_s(&f, g_reportPath, "w") == 0 && f) break;
    }
    if (!f) {
        g_reportPath[0] = '\0';
        return;
    }

    const std::vector<Module> modules = Modules();
    Write(f, pointers, modules);
    WriteEnvironment(f);
    WriteComprehensiveEvidence(f, modules);
    // Render() owns the DIAGNOSIS banner. Writing another banner here made
    // the complete report look as if DIAGNOSIS were empty and the actual
    // answer belonged to a separate "WHAT THIS MEANS" section.
    fprintf(f, "\n");
    WriteDiagnosis(f, pointers, modules);
    const std::string duplicates = reportpaths::RedactUserProfile(
        LoadedDuplicates(modules).c_str(), g_userProfile);
    if (!duplicates.empty()) {
        fprintf(f, "\n===============================================================\n"
                   " EXTRA FINDINGS\n"
                   "===============================================================\n");
        fprintf(f, "\nDuplicate active components:\n%s", duplicates.c_str());
        g_diagnosis += "\n\nDUPLICATE ACTIVE COMPONENTS\n";
        g_diagnosis +=
            "More than one loaded copy of a plugin was found. Remove or disable "
            "the extra copy, then try again.\n\n";
        g_diagnosis += duplicates;
        g_diagnosisSpanish += "\n\nCOMPONENTES ACTIVOS DUPLICADOS\n";
        g_diagnosisSpanish +=
            "Se encontró más de una copia cargada de un complemento. "
            "Elimine o desactive la copia adicional y vuelva a intentarlo.\n\n";
        g_diagnosisSpanish += SpanishDuplicateLines(duplicates);
    }
    fprintf(f,
            "\n---------------------------------------------------------------\n"
            "doctor-valkyrie %s. GTA San Andreas rules embedded in the ASI.\n"
            "Community crash list by Junior_Djjr and the MixMods community\n"
            "(github.com/JuniorDjjr/CrashInfo, MIT), used with attribution.\n",
            DOCTOR_VALKYRIE_VERSION);
    fclose(f);
}

// Kept apart from the filter for the same reason WriteReport is: a function
// holding __try cannot also own objects that need unwinding.
void ShowGuarded() {
    try {
        crashwindow::Show(g_diagnosis.c_str(), g_diagnosisSpanish.c_str(),
                          g_reportPath, g_knownDiagnosis);
    } catch (...) {
    }
}

void ShowSehGuarded() {
    __try {
        ShowGuarded();
    } __except (EXCEPTION_EXECUTE_HANDLER) {
    }
}

void WriteCppGuarded(EXCEPTION_POINTERS* pointers) {
    try {
        WriteReport(pointers);
    } catch (...) {
    }
}

void WriteSehGuarded(EXCEPTION_POINTERS* pointers) {
    __try {
        WriteCppGuarded(pointers);
    } __except (EXCEPTION_EXECUTE_HANDLER) {
    }
}

LONG WINAPI OnUnhandled(EXCEPTION_POINTERS* pointers) {
    // Ignore only a crash inside our own active reporter. Once this invocation
    // finishes, a later independent fault in the same process can be recorded.
    if (!pointers || !pointers->ExceptionRecord || !pointers->ContextRecord) {
        return EXCEPTION_EXECUTE_HANDLER;
    }
    if (InterlockedCompareExchange(&g_reporting, 1, 0) != 0) {
        return EXCEPTION_EXECUTE_HANDLER;
    }

    // Keep address space in reserve during normal play. Releasing it here gives
    // report creation and the window a chance even after an out-of-memory
    // failure in this 32-bit process.
    if (g_emergencyReserve) {
        VirtualFree(g_emergencyReserve, 0, MEM_RELEASE);
        g_emergencyReserve = nullptr;
    }

    g_reportPath[0] = '\0';
    g_diagnosis.clear();
    g_diagnosisSpanish.clear();
    g_knownDiagnosis = false;

    // Doctor owns the one complete report and one visible crash window. This
    // runs inside a dying process, so contain faults in reporter code itself.
    WriteSehGuarded(pointers);

    // Then show it, because a log nobody opens has helped nobody. Guarded
    // separately: if the window fails we still want the chain to run, and the
    // report is already safely on disk by this point.
    if (g_showWindow && g_reportPath[0]) {
        ShowSehGuarded();
    }

    // Doctor handled the terminal crash; do not invoke another ASI and open a second
    // crash window for the same event.
    InterlockedExchange(&g_reporting, 0);
    return EXCEPTION_EXECUTE_HANDLER;
}

}  // namespace

bool InstallCore() {
    if (g_installed) return true;

    InitializeCriticalSection(&g_lock);
    g_lockReady = true;

    HMODULE self = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCSTR>(&Install), &self);
    // Track only GTA's imports. The tail-jump wrappers preserve the original
    // caller return address, so Mod Loader's std.asi translator remains able
    // to identify ASIs while we restore the last-file/library crash evidence.
    HookMainExecutable();

    char folder[MAX_PATH] = {0};
    char path[MAX_PATH] = {0};
    GetModuleFileNameA(nullptr, folder, sizeof(folder));
    if (char* slash = strrchr(folder, '\\')) *(slash + 1) = '\0';
    CaptureEnvironment(folder, self);
    strncpy_s(g_gameRoot, sizeof(g_gameRoot), folder, _TRUNCATE);
    GetEnvironmentVariableA("USERPROFILE", g_userProfile, sizeof(g_userProfile));
    _snprintf_s(path, sizeof(path), _TRUNCATE, "%scleo.log", folder);
    g_cleoWatcher.Start(path);
    // Reserving does not commit physical memory; it merely keeps a small piece
    // of the 32-bit address space available for crash handling.
    g_emergencyReserve =
        VirtualAlloc(nullptr, 8 * 1024 * 1024, MEM_RESERVE, PAGE_NOACCESS);

    // Ours first: on an equal-specificity tie the earlier list wins, and where
    // we disagree with upstream about the same address it is because we know
    // something about GTA San Andreas that a general San Andreas list cannot.
    // Both lists are embedded so the public release is one ASI. Ignore stale
    // loose rule files from older releases; updating the ASI updates the whole
    // diagnosis database atomically.
    _snprintf_s(path, sizeof(path), _TRUNCATE, "%sdoctor-valkyrie.ini", folder);
    // Streamers and anyone recording will want the window off, so it is a
    // setting. Defaults to on: the whole point is that the player sees it.
    g_showWindow = GetPrivateProfileIntA("Settings", "ShowWindow", 1, path) != 0;

    int ours = LoadEmbeddedRules(self, IDR_DOCTOR_RULES,
                                 "embedded GTA San Andreas rules");
    if (ours < 0) {
        _snprintf_s(path, sizeof(path), _TRUNCATE,
                    "%sdoctor-valkyrie.txt", folder);
        ours = LoadFileRules(path, "doctor-valkyrie.txt (fallback)");
    }

    const int theirs =
        LoadEmbeddedRules(self, IDR_CRASHINFO_RULES,
                          "embedded CrashInfo community rules");
    const int oursSpanish = LoadEmbeddedSpanish(self, IDR_DOCTOR_RULES_ES);
    const int theirsSpanish = LoadEmbeddedSpanish(self, IDR_CRASHINFO_RULES_ES);

    logfile::Line("doctor: %d GTA San Andreas rules, %d community rules",
                  ours < 0 ? 0 : ours, theirs < 0 ? 0 : theirs);
    logfile::Line("doctor: %d GTA San Andreas and %d community Spanish translations",
                  oursSpanish < 0 ? 0 : oursSpanish,
                  theirsSpanish < 0 ? 0 : theirsSpanish);
    if (ours < 0) {
        logfile::Line("doctor: embedded GTA San Andreas rules are unavailable - "
                      "crashes will be logged with community explanations only");
    }

    g_previousFilter = InstallNativeUnhandledFilter();
    logfile::Line("doctor: installed, chaining to %s",
                  g_previousFilter ? "the previous crash reporter" : "nothing");

    g_installed = true;
    return true;
}

bool Install() {
    // Loading a crash reporter must never be the reason the game fails to
    // start. Catch hardware faults from hostile module state at the outermost
    // boundary; list-parser allocation failures are contained above.
    __try {
        return InstallCore();
    } __except (EXCEPTION_EXECUTE_HANDLER) {
        return false;
    }
}

void Reassert() {
    if (!g_installed) return;
    LPTOP_LEVEL_EXCEPTION_FILTER current = InstallNativeUnhandledFilter();
    if (current == &OnUnhandled) {
        // Still ours; nothing loaded over the top of us.
        return;
    }
    // Somebody else took the filter after we installed. Keep it recorded for
    // diagnostics, then put Doctor back on top; Doctor deliberately owns the
    // only visible crash report for this launch.
    g_previousFilter = current;
    logfile::Line("doctor: another crash reporter installed after us - "
                  "re-asserted Doctor as the single crash reporter");
}

void CheckCleoErrors() {
    if (!g_installed || InterlockedCompareExchange(&g_reporting, 1, 0) != 0) {
        return;
    }

    std::string event;
    if (!g_cleoWatcher.Poll(&event)) {
        InterlockedExchange(&g_reporting, 0);
        return;
    }

    char gameRoot[MAX_PATH] = {0};
    GetModuleFileNameA(nullptr, gameRoot, sizeof(gameRoot));
    if (char* slash = strrchr(gameRoot, '\\')) *(slash + 1) = '\0';
    char reportDir[MAX_PATH] = {0};
    _snprintf_s(reportDir, sizeof(reportDir), _TRUNCATE,
                "%sValkyrie_crashes", gameRoot);
    CreateDirectoryA(reportDir, nullptr);

    SYSTEMTIME now{};
    GetLocalTime(&now);
    _snprintf_s(g_reportPath, sizeof(g_reportPath), _TRUNCATE,
                "%s\\doctor-valkyrie_cleo_%04d-%02d-%02d_%02d-%02d-%02d-%03d.log",
                reportDir, now.wYear, now.wMonth, now.wDay, now.wHour,
                now.wMinute, now.wSecond, now.wMilliseconds);

    g_knownDiagnosis = true;
    g_diagnosis =
        "===============================================================\n"
        " DIAGNOSIS\n"
        "===============================================================\n\n"
        "Problem: A CLEO script error stopped the script while GTA remained "
        "running. This is not a Windows crash.\n"
        "Solution: Read the CLEO error below and fix or disable the named "
        "script. If CLEO specifically offers legacy mode, renaming that "
        "script from .cs to .cs4 is a compatibility workaround; correcting "
        "the script's argument types is preferable.\n";
    g_diagnosisSpanish =
        "===============================================================\n"
        " DIAGNÓSTICO\n"
        "===============================================================\n\n"
        "Problem: Un error de un script CLEO detuvo el script mientras GTA "
        "seguía ejecutándose. No es un fallo de Windows.\n"
        "Solution: Lea el error de CLEO que aparece abajo y corrija o "
        "desactive el script indicado. Si CLEO ofrece el modo heredado, "
        "cambiar la extensión de .cs a .cs4 es una solución de compatibilidad; "
        "es preferible corregir los tipos de argumentos del script.\n";

    FILE* report = nullptr;
    if (fopen_s(&report, g_reportPath, "w") == 0 && report) {
        fprintf(report,
                "Doctor Valkyrie CLEO suspension report, version %s\n"
                "Source: %scleo.log (preserved unchanged)\n\n"
                "CLEO ERROR\n"
                "===============================================================\n"
                "%s\n\n%s",
                DOCTOR_VALKYRIE_VERSION,
                reportpaths::RedactUserProfile(gameRoot, g_userProfile).c_str(),
                reportpaths::RedactUserProfile(event.c_str(), g_userProfile).c_str(),
                g_diagnosis.c_str());
        fclose(report);
        logfile::Line("doctor: recorded CLEO script suspension in %s", g_reportPath);
        if (g_showWindow) crashwindow::Show(
            g_diagnosis.c_str(), g_diagnosisSpanish.c_str(), g_reportPath, true);
    } else {
        g_reportPath[0] = '\0';
    }
    InterlockedExchange(&g_reporting, 0);
}

}  // namespace doctor
