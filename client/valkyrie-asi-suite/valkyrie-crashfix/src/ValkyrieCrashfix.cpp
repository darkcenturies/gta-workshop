#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#include <tlhelp32.h>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

static HMODULE selfModule;
static CRITICAL_SECTION logLock;
static volatile LONG shuttingDown;
static void* poolTrampoline;
static bool patchProtectionFailure=false;

struct Hook { const char* name; BYTE* address; size_t length; BYTE original[16]; BYTE patched[16]; };
static std::vector<Hook> installed;

static std::string LogPath() {
    char path[MAX_PATH]{};
    GetModuleFileNameA(selfModule, path, MAX_PATH);
    char* slash = strrchr(path, '\\');
    if (slash) strcpy_s(slash + 1, MAX_PATH - (slash + 1 - path), "Valkyrie Crashfix.log");
    return path;
}

static void Log(const char* fmt, ...) {
    EnterCriticalSection(&logLock);
    FILE* f = nullptr;
    fopen_s(&f, LogPath().c_str(), "a");
    if (f) {
        SYSTEMTIME st{}; GetLocalTime(&st);
        fprintf(f, "[%02u:%02u:%02u.%03u] ", st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        va_list ap; va_start(ap, fmt); vfprintf(f, fmt, ap); va_end(ap);
        fputc('\n', f); fclose(f);
    }
    LeaveCriticalSection(&logLock);
}

static bool Readable(const void* p, size_t bytes) {
    if (!p || bytes == 0) return false;
    MEMORY_BASIC_INFORMATION m{};
    if (!VirtualQuery(p, &m, sizeof(m)) || m.State != MEM_COMMIT || (m.Protect & (PAGE_NOACCESS | PAGE_GUARD))) return false;
    const DWORD readable = PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY;
    if (!(m.Protect & readable)) return false;
    uintptr_t a = reinterpret_cast<uintptr_t>(p), end = a + bytes;
    return end >= a && end <= reinterpret_cast<uintptr_t>(m.BaseAddress) + m.RegionSize;
}

static bool Writable(const void* p, size_t bytes) {
    if (!Readable(p, bytes)) return false;
    MEMORY_BASIC_INFORMATION m{}; VirtualQuery(p, &m, sizeof(m));
    return (m.Protect & (PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY)) != 0;
}

static bool MakeCall(Hook& h, BYTE* at, void* target, const char* name) {
    if (!Readable(at, 5) || at[0] != 0xE8) return false;
    h.name=name; h.address=at; h.length=5; memcpy(h.original, at, 5); h.patched[0]=0xE8;
    DWORD rel=DWORD(target)-DWORD(at+5); memcpy(h.patched+1,&rel,4); return true;
}

#include "SafePatch.inc"

extern "C" bool __cdecl PoolReadable(const void* pool) {
    bool ok = Writable(pool, 16);
    if (!ok) Log("GTA audio-adjacent pool guard blocked invalid ECX=%p at 0x0040FB80", pool);
    return ok;
}

__declspec(naked) static void PoolGuard() {
    __asm {
        pushfd
        pushad
        mov ebp, esp
        sub esp, 528
        and esp, 0FFFFFFF0h
        fxsave [esp]
        push ecx
        call PoolReadable
        add esp, 4
        fxrstor [esp]
        mov esp, ebp
        test al, al
        jnz valid
        popad
        popfd
        xor eax, eax
        ret
    valid:
        popad
        popfd
        jmp dword ptr [poolTrampoline]
    }
}

static bool PreparePoolGuard(Hook& hook) {
    HMODULE exe=GetModuleHandleA(nullptr);
    // The crash report names 0x0040FB80. GTA contains many allocator templates with
    // the same prefix, so this guard intentionally binds to that RVA and then verifies
    // a longer body. Pattern-only selection would risk guarding the wrong pool.
    BYTE* at=reinterpret_cast<BYTE*>(exe)+0xFB80;
    const BYTE sig[]={0x8B,0x51,0x08,0x56,0x32,0xC0,0x57,0x8B,0x79,0x0C,0x47,0x8B,0xF7,0x3B,0xF2,0x89,0x79,0x0C,0x75,0x0D,0x84,0xC0,0xC7,0x41,0x0C,0,0,0,0};
    if(!Readable(at,sizeof(sig)) || memcmp(at,sig,sizeof(sig))){ Log("GTA 0x0040FB80 body does not match the supported build; pool guard skipped"); return false; }
    poolTrampoline=VirtualAlloc(nullptr,16,MEM_COMMIT|MEM_RESERVE,PAGE_EXECUTE_READWRITE); if(!poolTrampoline) return false;
    memcpy(poolTrampoline,at,6); BYTE* t=static_cast<BYTE*>(poolTrampoline); t[6]=0xE9; int32_t back=static_cast<int32_t>((at+6)-(t+11)); memcpy(t+7,&back,4); FlushInstructionCache(GetCurrentProcess(),t,11);
    hook.name="GTA 0x0040FB80 pool guard"; hook.address=at; hook.length=6; memcpy(hook.original,at,6); hook.patched[0]=0xE9; int32_t rel=static_cast<int32_t>(reinterpret_cast<BYTE*>(&PoolGuard)-(at+5)); memcpy(hook.patched+1,&rel,4); hook.patched[5]=0x90; return true;
}

// MSVC /O2 reports inline-assembly branch labels as unused.
#pragma warning(push)
#pragma warning(disable: 4102 4733)
#include "ActorGuard.inc"
#include "IncidentGuards.inc"
#include "PrepareGuards.inc"

#pragma warning(pop)

static DWORD WINAPI Bootstrap(void*) {
    Log("Valkyrie Crashfix 3.0.0-test starting (GTA SA guards, integrated Doctor)");
    std::vector<Hook> hooks; hooks.reserve(64);
    Hook pool{}; if(PreparePoolGuard(pool)) hooks.push_back(pool);
    if(WaitForModPatches()) {
        PrepareAuditedGuards(hooks);
        if(!PrepareActorGuard(hooks)){actorChecks.clear();Log("Special actor guard SKIPPED: unsupported loader layout");}
        PrepareIncidentGuards(hooks);
    }
    if(!CommitHooks(hooks)){Log("Hook transaction not installed; any completed writes were rolled back");return 0;}
    Log("Installed %u verified hooks with peer threads paused",static_cast<unsigned>(hooks.size()));
    for(auto& h:hooks) Log("  %s at %p",h.name,h.address);
    if(patchProtectionFailure) Log("ERROR: a page protection restore failed; code remains installed");
    MonitorGuards();
    return 0;
}

BOOL WINAPI CrashfixModuleEvent(HINSTANCE module,DWORD reason,LPVOID) {
    if(reason==DLL_PROCESS_ATTACH){ selfModule=module; HMODULE pinned=nullptr; if(!GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS|GET_MODULE_HANDLE_EX_FLAG_PIN,reinterpret_cast<LPCSTR>(module),&pinned)) return FALSE; InitializeCriticalSection(&logLock); DisableThreadLibraryCalls(module); HANDLE t=CreateThread(nullptr,0,Bootstrap,nullptr,0,nullptr); if(t) CloseHandle(t); }
    else if(reason==DLL_PROCESS_DETACH){ InterlockedExchange(&shuttingDown,1); /* Windows may already be tearing modules down; installed call sites are process-local. */ }
    return TRUE;
}
