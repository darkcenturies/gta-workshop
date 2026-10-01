#include "crashwindow.h"

#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <richedit.h>

#include <cstring>
#include <cstdio>
#include <algorithm>
#include <string>

#include "resource.h"
#include "reportpaths.h"
#include "version.h"

namespace crashwindow {
namespace {

// Keep the banner prominent, but give the explanation enough width that it
// reads like a report rather than a stack of cramped text boxes.
const int kHeaderHeight = 0;
const int kPad = 18;
const int kBottomPad = 30;
const int kButtonHeight = 34;
const int kTextHeight = 270;
const int kPathHeight = 22;
const int kInitialWidth = 1020;
const int kInitialHeight = 760;
const int kMinimumWidth = 760;
const int kMinimumHeight = 560;

const COLORREF kBackground = RGB(24, 24, 27);   // matches the composited BMP
const COLORREF kText = RGB(228, 232, 235);
const COLORREF kDim = RGB(150, 158, 165);

const char* kClassName = "DoctorValkyrieCrashWindow";

const int kIdText = 1001;
const int kIdCopy = 1002;
const int kIdOpen = 1003;
const int kIdClose = 1004;
const int kIdPath = 1005;
const int kIdDiagnosis = 1006;
const int kIdFullLog = 1007;
const int kIdProblem = 1008;
const int kIdSolution = 1009;
const int kIdProblemLabel = 1010;
const int kIdSolutionLabel = 1011;
const int kIdFindings = 1012;
const int kIdTranslate = 1013;
const int kIdFooter = 1014;
const int kIdSupports = 1017;

HBRUSH g_backBrush = nullptr;
HFONT g_bodyFont = nullptr;
HFONT g_smallFont = nullptr;
std::string g_diagnosis;
std::string g_diagnosisSpanish;
std::string g_logPath;
std::string g_logText;
std::string g_findings;
bool g_spanish = false;
bool g_done = false;
HWND CreateReportBox(HMODULE self, HWND parent, int id, int x, int y,
                     int width, int height, bool visible) {
    const DWORD style = WS_CHILD | WS_VSCROLL | ES_MULTILINE | ES_READONLY |
                        ES_AUTOVSCROLL | WS_BORDER |
                        (visible ? WS_VISIBLE : 0);
    HWND box = CreateWindowExW(0, L"RICHEDIT50W", L"", style, x, y, width,
                               height, parent, reinterpret_cast<HMENU>(id),
                               self, nullptr);
    SendMessageW(box, EM_AUTOURLDETECT, TRUE, 0);
    SendMessageW(box, EM_SETEVENTMASK, 0,
                 SendMessageW(box, EM_GETEVENTMASK, 0, 0) | ENM_LINK);
    return box;
}

// The rendered diagnosis carries its own DIAGNOSIS banner, which is useful in
// the complete report but redundant in the dedicated window page.
std::string ForWindow(const char* text) {
    std::string out;
    const char* p = text;
    while (*p) {
        const char* nl = strchr(p, '\n');
        const size_t len = nl ? static_cast<size_t>(nl - p) : strlen(p);
        std::string line(p, len);
        const bool banner = line.compare(0, 3, "===") == 0 ||
                            line == " DIAGNOSIS" ||
                            line == " DIAGNÓSTICO" ||
                            line == " WHAT THIS MEANS";  // older reports
        const bool internalMatchNote =
            line.find("[matched on ") != std::string::npos ||
            line.find("[coincidencia en ") != std::string::npos;
        if (!banner && !internalMatchNote) {
            // Edit controls want CRLF or they render one long line.
            out += line;
            out += "\r\n";
        }
        if (!nl) break;
        p = nl + 1;
    }
    // Trim the blank lines the stripped banner left at the top.
    size_t start = 0;
    while (start + 1 < out.size() && out.compare(start, 2, "\r\n") == 0) start += 2;
    return out.substr(start);
}

struct Sections {
    std::string problem;
    std::string solution;
    std::string findings;
};

size_t FirstFinding(const std::string& text, size_t start = 0) {
    const char* markers[] = {
        "\r\n\r\n   [matched on",
        "\r\n\r\nENVIRONMENT WARNING:",
        "\r\n\r\nDETECTED MOD RISK:",
        "\r\n\r\nDETECTED MOD CONFLICT:",
        "\r\n\r\nDUPLICATE ACTIVE COMPONENTS",
        "\r\n\r\nADVERTENCIA DEL ENTORNO:",
        "\r\n\r\nRIESGO DE MOD DETECTADO:",
        "\r\n\r\nCOMPONENTES ACTIVOS DUPLICADOS",
        "\r\n\r\n---------------------------------------------------------------\r\n"
        " Other findings from the crash log",
        "\r\n---------------------------------------------------------------\r\n"
        " Otros hallazgos del registro del fallo",
        "\r\n---------------------------------------------------------------\r\n"
        " Other possibilities for the same crash",
        "\r\n---------------------------------------------------------------\r\n"
        " Otras posibilidades para el mismo fallo",
    };
    size_t first = std::string::npos;
    for (const char* marker : markers) {
        const size_t at = text.find(marker, start);
        if (at != std::string::npos) first = (std::min)(first, at);
    }
    return first;
}

// Rules are written as Problem: and Solution: fields. Keep those fields
// separate in the window so the first thing a player sees is the answer, not
// a wall of crash-report prose.
Sections SplitSections(const char* text) {
    const std::string rendered = ForWindow(text);
    const size_t problemAt = rendered.find("Problem:");
    const size_t solutionAt = rendered.find("Solution:");
    const size_t findingAt = FirstFinding(rendered);
    Sections sections;
    if (problemAt != std::string::npos) {
        const size_t start = problemAt + strlen("Problem:");
        sections.problem = rendered.substr(start, solutionAt == std::string::npos
                                                     ? std::string::npos
                                                     : solutionAt - start);
    } else {
        sections.problem = rendered.substr(0, findingAt);
    }
    if (solutionAt != std::string::npos) {
        const size_t start = solutionAt + strlen("Solution:");
        const size_t end = FirstFinding(rendered, start);
        sections.solution = rendered.substr(
            start, end == std::string::npos ? std::string::npos : end - start);
    }
    if (findingAt != std::string::npos) {
        sections.findings = rendered.substr(findingAt);
    }
    if (sections.problem.empty()) sections.problem = rendered;
    if (sections.solution.empty()) {
        sections.solution = "No specific fix was found. Use Copy for Discord and post the log.";
    }
    return sections;
}

void Copy(HWND owner) {
    std::string all = g_spanish ? g_diagnosisSpanish : g_diagnosis;
    all += g_spanish ? "\r\nArchivo de registro: " : "\r\nLog file: ";
    all += g_logPath;
    all += "\r\n";
    if (!OpenClipboard(owner)) return;
    EmptyClipboard();
    if (HGLOBAL block = GlobalAlloc(GMEM_MOVEABLE, all.size() + 1)) {
        if (void* dest = GlobalLock(block)) {
            memcpy(dest, all.c_str(), all.size() + 1);
            GlobalUnlock(block);
            SetClipboardData(CF_TEXT, block);
        }
    }
    CloseClipboard();
}

// Open Explorer with the log selected, which is one less instruction to give
// somebody who has to post it.
void Reveal() {
    std::string args = "/select,\"";
    args += g_logPath;
    args += "\"";
    ShellExecuteA(nullptr, "open", "explorer.exe", args.c_str(), nullptr, SW_SHOWNORMAL);
}

// GTA can leave DirectInput's cursor state behind when it dies: hidden,
// captured, or clipped to the old game client area. A crash window must always
// be usable, including on scaled Windows 10 desktops. The process is about to
// end, so there is no game cursor state to restore afterwards.
void RestoreDesktopCursor() {
    ReleaseCapture();
    ClipCursor(nullptr);
    HCURSOR cursor = LoadCursor(nullptr, IDC_ARROW);
    SetCursor(cursor);
    // ShowCursor uses a display counter. A fullscreen game may have hidden it
    // more than once, so bring the counter back to visible without looping
    // forever if another component has done something pathological.
    for (int i = 0; i < 64 && ShowCursor(TRUE) < 0; ++i) {
    }
}

std::string ReadReport(const char* path) {
    if (!path || !*path) return "No crash-report file was created.";
    FILE* file = nullptr;
    if (fopen_s(&file, path, "rb") != 0 || !file) {
        return "The crash-report file could not be opened.";
    }
    fseek(file, 0, SEEK_END);
    const long length = ftell(file);
    rewind(file);
    if (length <= 0) {
        fclose(file);
        return "The crash-report file is empty.";
    }
    // A report is normally a few KB. Keep the preview responsive even if a
    // corrupt process somehow produced an unexpectedly large file.
    const size_t count = static_cast<size_t>(length > 1024 * 1024
                                                  ? 1024 * 1024
                                                  : length);
    std::string out(count, '\0');
    out.resize(fread(&out[0], 1, count, file));
    fclose(file);
    if (static_cast<size_t>(length) > count) {
        out += "\r\n\r\n[The report was truncated in this window. Open the log for all of it.]";
    }
    return out;
}

void ReplaceAll(std::string& text, const std::string& from,
                const std::string& to) {
    if (from.empty()) return;
    size_t at = 0;
    while ((at = text.find(from, at)) != std::string::npos) {
        text.replace(at, from.size(), to);
        at += to.size();
    }
}

void SetUtf8(HWND control, const std::string& text) {
    const int count = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1,
                                          nullptr, 0);
    if (count <= 0) return;
    std::wstring wide(static_cast<size_t>(count), L'\0');
    MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, &wide[0], count);
    SetWindowTextW(control, wide.c_str());
}

std::string LocalizeCompleteReport(std::string report,
                                   const std::string& englishDiagnosis,
                                   const std::string& spanishDiagnosis) {
    ReplaceAll(report, englishDiagnosis, spanishDiagnosis);
    std::string englishCrlf = englishDiagnosis;
    std::string spanishCrlf = spanishDiagnosis;
    ReplaceAll(englishCrlf, "\n", "\r\n");
    ReplaceAll(spanishCrlf, "\n", "\r\n");
    ReplaceAll(report, englishCrlf, spanishCrlf);
    const struct { const char* en; const char* es; } labels[] = {
        {"Last file loaded:", "Último archivo cargado:"},
        {"Last library loaded:", "Última biblioteca cargada:"},
        {"Unhandled exception at", "Excepción no controlada en"},
        {"In module:", "En el módulo:"},
        {"Access violation", "Infracción de acceso"},
        {"Illegal instruction", "Instrucción no válida"},
        {"Integer division by zero", "División entera por cero"},
        {"Floating-point division by zero", "División decimal por cero"},
        {"read at", "lectura en"},
        {"write at", "escritura en"},
        {"execute at", "ejecución en"},
        {"Register dump:", "Volcado de registros:"},
        {"Stack dump:", "Volcado de pila:"},
        {"Backtrace (may be wrong):", "Traza inversa (puede ser imprecisa):"},
        {"Environment:", "Entorno:"},
        {"Launched executable:", "Ejecutable iniciado:"},
        {"Doctor module:", "Módulo de Doctor:"},
        {"Working directory:", "Directorio de trabajo:"},
        {"Running elevated:", "Ejecutándose como administrador:"},
        {"Compatibility shims:", "Capas de compatibilidad:"},
        {"Working-dir match:", "Directorio de trabajo correcto:"},
        {"Doctor in game root:", "Doctor en la carpeta del juego:"},
        {"Other GTA processes:", "Otros procesos de GTA:"},
        {"(none recorded)", "(ninguno registrado)"},
        {"Loaded modules at failure", "Módulos cargados al producirse el fallo"},
        {"GTA San Andreas / game-local", "GTA San Andreas / local del juego"},
        {"External / system", "Externo / sistema"},
        {"External / background", "Externo / segundo plano"},
        {"file activity in chronological order", "actividad de archivos en orden cronológico"},
        {"library-load activity", "actividad de carga de bibliotecas"},
        {"retained", "conservados"},
        {"oldest entries omitted", "entradas más antiguas omitidas"},
        {"EXTRA FINDINGS", "HALLAZGOS ADICIONALES"},
        {" WHAT THIS MEANS", " QUÉ SIGNIFICA"},
        {"Duplicate active components:", "Componentes activos duplicados:"},
        {"Problem:", "Problema:"},
        {"Solution:", "Solución:"},
        {"About:", "Acerca de:"},
        {"Type:", "Tipo:"},
        {"Last command:", "Último comando:"},
        {"doctor-valkyrie", "Doctor Valkyrie"},
        {"GTA San Andreas rules embedded in the ASI.",
         "Reglas de GTA San Andreas integradas en el ASI."},
        {"Community crash list", "Lista comunitaria de fallos"},
        {"used with attribution.", "utilizada con atribución."},
    };
    for (const auto& label : labels) ReplaceAll(report, label.en, label.es);
    return report;
}

enum class Page { Diagnosis, Findings, FullLog };
Sections g_englishSections;
Sections g_spanishSections;
std::string g_logTextSpanish;
Page g_page = Page::Diagnosis;
void ShowPage(HWND window, Page page);

std::string DiagnosisActionText(const Sections& sections, bool spanish) {
    std::string text = sections.solution;
    if (!sections.findings.empty()) {
        text += spanish ? "\r\n\r\nOTROS HALLAZGOS\r\n"
                        : "\r\n\r\nOTHER FINDINGS\r\n";
        text += sections.findings;
    }
    return text;
}

void ApplyLanguage(HWND window) {
    const Sections& sections = g_spanish ? g_spanishSections : g_englishSections;
    SetUtf8(GetDlgItem(window, kIdProblem), sections.problem);
    SetUtf8(GetDlgItem(window, kIdSolution),
            DiagnosisActionText(sections, g_spanish));
    SetUtf8(GetDlgItem(window, kIdProblemLabel),
            g_spanish ? "CAUSA PROBABLE" : "LIKELY CAUSE");
    SetUtf8(GetDlgItem(window, kIdSolutionLabel),
            g_spanish ? "QUÉ HACER" : "WHAT TO DO");
    SetUtf8(GetDlgItem(window, kIdDiagnosis),
            g_spanish ? "Diagnóstico" : "Diagnosis");
    SetUtf8(GetDlgItem(window, kIdFindings),
            sections.findings.empty()
                ? (g_spanish ? "Sin otros hallazgos" : "No other findings")
                : (g_spanish ? "Otros hallazgos" : "Other findings"));
    SetUtf8(GetDlgItem(window, kIdFullLog),
            g_spanish ? "Registro completo" : "Full log");
    SetUtf8(GetDlgItem(window, kIdCopy), g_spanish ? "Copiar" : "Copy");
    SetUtf8(GetDlgItem(window, kIdOpen),
            g_spanish ? "Abrir registro" : "Open log");
    SetUtf8(GetDlgItem(window, kIdClose), g_spanish ? "Cerrar" : "Close");
    SetUtf8(GetDlgItem(window, kIdTranslate),
            g_spanish ? "English" : "Español");
    std::string footer = "Valkyrie © 2026 valkyrie  •  v";
    footer += DOCTOR_VALKYRIE_VERSION;
    SetUtf8(GetDlgItem(window, kIdFooter), footer);
    SetUtf8(GetDlgItem(window, kIdSupports),
            g_spanish ? "Compatible con:" : "GTA San Andreas");
    EnableWindow(GetDlgItem(window, kIdFindings), !sections.findings.empty());
    ShowPage(window, g_page);
}

void ShowPage(HWND window, Page page) {
    g_page = page;
    HWND text = GetDlgItem(window, kIdText);
    if (!text) return;
    const bool diagnosis = page == Page::Diagnosis;
    const int diagnosisControls[] = {
        kIdProblem, kIdSolution, kIdProblemLabel, kIdSolutionLabel,
    };
    for (int id : diagnosisControls) {
        ShowWindow(GetDlgItem(window, id), diagnosis ? SW_SHOW : SW_HIDE);
    }
    ShowWindow(text, diagnosis ? SW_HIDE : SW_SHOW);
    if (page == Page::FullLog) {
        SetUtf8(text, g_spanish ? g_logTextSpanish : g_logText);
        SendMessageA(text, WM_SETFONT, reinterpret_cast<WPARAM>(g_smallFont), TRUE);
    } else if (page == Page::Findings) {
        SetUtf8(text, g_spanish ? g_spanishSections.findings
                                : g_englishSections.findings);
        SendMessageA(text, WM_SETFONT, reinterpret_cast<WPARAM>(g_bodyFont), TRUE);
    }
    if (!diagnosis) {
        SendMessageA(text, EM_SETSEL, 0, 0);
        SendMessageA(text, EM_SCROLLCARET, 0, 0);
        SendMessageA(text, WM_VSCROLL, SB_TOP, 0);
    }
}

void Layout(HWND window) {
    RECT client{};
    GetClientRect(window, &client);
    const int width = client.right - client.left;
    const int height = client.bottom - client.top;
    const int contentWidth = width - kPad * 2;
    const int viewButtonWidth = 160;

    int top = kHeaderHeight + kPad;
    MoveWindow(GetDlgItem(window, kIdDiagnosis), kPad, top,
               viewButtonWidth, kButtonHeight, TRUE);
    MoveWindow(GetDlgItem(window, kIdFullLog),
               kPad + viewButtonWidth + 8, top,
               viewButtonWidth, kButtonHeight, TRUE);

    const int reportTop = top + kButtonHeight + 10;
    const int buttonTop = height - kBottomPad - kButtonHeight;
    const int footerHeight = 34;
    const int footerTop = buttonTop - footerHeight - 8;
    const int pathTop = footerTop - kPad / 2 - kPathHeight;
    const int reportHeight = (std::max)(220, pathTop - kPad / 2 - reportTop);
    const int causeLabelHeight = 18;
    const int solutionLabelHeight = 18;
    int causeHeight = (std::max)(100, reportHeight * 38 / 100);
    int solutionHeight = reportHeight - causeLabelHeight - causeHeight - 5 -
                         solutionLabelHeight;
    if (solutionHeight < 90) {
        causeHeight -= 90 - solutionHeight;
        solutionHeight = 90;
    }

    top = reportTop;
    MoveWindow(GetDlgItem(window, kIdProblemLabel), kPad, top,
               contentWidth, causeLabelHeight, TRUE);
    top += causeLabelHeight;
    MoveWindow(GetDlgItem(window, kIdProblem), kPad, top,
               contentWidth, causeHeight, TRUE);
    top += causeHeight + 5;
    MoveWindow(GetDlgItem(window, kIdSolutionLabel), kPad, top,
               contentWidth, solutionLabelHeight, TRUE);
    top += solutionLabelHeight;
    MoveWindow(GetDlgItem(window, kIdSolution), kPad, top,
               contentWidth, solutionHeight, TRUE);

    MoveWindow(GetDlgItem(window, kIdText), kPad, reportTop,
               contentWidth, reportHeight, TRUE);
    MoveWindow(GetDlgItem(window, kIdPath), kPad, pathTop,
               contentWidth, kPathHeight, TRUE);

    const int buttonWidth = 140;
    const int gap = 10;
    int bx = width - kPad - buttonWidth;
    const int buttons[] = {kIdClose, kIdOpen, kIdCopy};
    for (int id : buttons) {
        MoveWindow(GetDlgItem(window, id), bx, buttonTop,
                   buttonWidth, kButtonHeight, TRUE);
        bx -= buttonWidth + gap;
    }
    MoveWindow(GetDlgItem(window, kIdTranslate), kPad, buttonTop,
               140, kButtonHeight, TRUE);
    MoveWindow(GetDlgItem(window, kIdFooter), kPad, footerTop + 8,
               250, 20, TRUE);
    MoveWindow(GetDlgItem(window, kIdSupports), kPad + 257, footerTop + 8,
               105, 20, TRUE);
    const int showBranding = width >= 940 ? SW_SHOW : SW_HIDE;
    ShowWindow(GetDlgItem(window, kIdFooter), showBranding);
    ShowWindow(GetDlgItem(window, kIdSupports), showBranding);
    InvalidateRect(window, nullptr, TRUE);
}

LRESULT CALLBACK Proc(HWND window, UINT message, WPARAM wparam, LPARAM lparam) {
    switch (message) {
        case WM_CTLCOLORSTATIC:
        case WM_CTLCOLOREDIT: {
            auto dc = reinterpret_cast<HDC>(wparam);
            SetBkColor(dc, kBackground);
            const HWND control = reinterpret_cast<HWND>(lparam);
            SetTextColor(dc, control == GetDlgItem(window, kIdPath) ||
                                 control == GetDlgItem(window, kIdProblemLabel) ||
                                 control == GetDlgItem(window, kIdSolutionLabel) ||
                                 control == GetDlgItem(window, kIdFooter) ||
                                 control == GetDlgItem(window, kIdSupports)
                                 ? kDim : kText);
            return reinterpret_cast<LRESULT>(g_backBrush);
        }
        case WM_ERASEBKGND: {
            RECT client{};
            GetClientRect(window, &client);
            FillRect(reinterpret_cast<HDC>(wparam), &client, g_backBrush);
            return 1;
        }
        case WM_SETCURSOR:
            if (LOWORD(lparam) == HTCLIENT) {
                SetCursor(LoadCursor(nullptr, IDC_ARROW));
                return TRUE;
            }
            break;
        case WM_NOTIFY: {
            auto* link = reinterpret_cast<ENLINK*>(lparam);
            if (link && link->nmhdr.code == EN_LINK &&
                link->msg == WM_LBUTTONUP) {
                wchar_t url[2048]{};
                TEXTRANGEW range{link->chrg, url};
                SendMessageW(link->nmhdr.hwndFrom, EM_GETTEXTRANGE, 0,
                             reinterpret_cast<LPARAM>(&range));
                ShellExecuteW(nullptr, L"open", url, nullptr, nullptr, SW_SHOWNORMAL);
                return 1;
            }
            break;
        }
        case WM_PAINT: {
            PAINTSTRUCT ps{};
            BeginPaint(window, &ps);
            EndPaint(window, &ps);
            return 0;
        }
        case WM_GETMINMAXINFO: {
            auto* info = reinterpret_cast<MINMAXINFO*>(lparam);
            info->ptMinTrackSize.x = kMinimumWidth;
            info->ptMinTrackSize.y = kMinimumHeight;
            return 0;
        }
        case WM_SIZE:
            Layout(window);
            return 0;
        case WM_COMMAND:
            switch (LOWORD(wparam)) {
                case kIdCopy:
                    Copy(window);
                    SetDlgItemTextA(window, kIdCopy, "Copied");
                    return 0;
                case kIdOpen:
                    Reveal();
                    return 0;
                case kIdDiagnosis:
                    ShowPage(window, Page::Diagnosis);
                    return 0;
                case kIdFindings:
                    ShowPage(window, Page::Findings);
                    return 0;
                case kIdFullLog:
                    ShowPage(window, Page::FullLog);
                    return 0;
                case kIdTranslate:
                    g_spanish = !g_spanish;
                    ApplyLanguage(window);
                    return 0;
                case kIdClose:
                    DestroyWindow(window);
                    return 0;
                default:
                    break;
            }
            return 0;
        case WM_CLOSE:
            DestroyWindow(window);
            return 0;
        case WM_DESTROY:
            g_done = true;
            PostQuitMessage(0);
            return 0;
        default:
            break;
    }
    return DefWindowProcA(window, message, wparam, lparam);
}

HFONT MakeFont(int height, const char* face, int weight) {
    return CreateFontA(height, 0, 0, 0, weight, FALSE, FALSE, FALSE,
                       DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
                       CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, face);
}

}  // namespace

void Show(const char* diagnosis, const char* diagnosisSpanish,
          const char* logPath, bool knownCause, bool startInSpanish) {
    g_diagnosis = diagnosis ? diagnosis : "";
    g_logPath = logPath ? logPath : "";
    g_logText = ReadReport(g_logPath.c_str());
    g_diagnosisSpanish = diagnosisSpanish ? diagnosisSpanish : g_diagnosis;
    g_englishSections = SplitSections(g_diagnosis.c_str());
    g_spanishSections = SplitSections(g_diagnosisSpanish.c_str());
    g_logTextSpanish = LocalizeCompleteReport(
        g_logText, g_diagnosis, g_diagnosisSpanish);
    const Sections& sections = g_englishSections;
    g_spanish = startInSpanish;
    g_done = false;
    (void)knownCause;

    HMODULE self = nullptr;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       reinterpret_cast<LPCSTR>(&Show), &self);

    // A fullscreen game keeps the display and the foreground, so our window
    // would open behind it and the player would see a frozen screen and assume
    // the game simply hung. Put the game away first.
    if (HWND game = FindWindowA("Grand theft auto San Andreas", nullptr)) {
        ShowWindow(game, SW_MINIMIZE);
    }
    RestoreDesktopCursor();

    g_backBrush = CreateSolidBrush(kBackground);
    g_bodyFont = MakeFont(-15, "Segoe UI", FW_NORMAL);
    g_smallFont = MakeFont(-12, "Consolas", FW_NORMAL);

    WNDCLASSA cls{};
    cls.lpfnWndProc = &Proc;
    cls.hInstance = self;
    cls.hCursor = LoadCursor(nullptr, IDC_ARROW);
    cls.hbrBackground = g_backBrush;
    cls.lpszClassName = kClassName;
    RegisterClassA(&cls);

    RECT work{};
    SystemParametersInfoA(SPI_GETWORKAREA, 0, &work, 0);
    const int usableWidth = work.right - work.left - 40;
    const int usableHeight = work.bottom - work.top - 40;
    const int width = (std::max)(kMinimumWidth,
                                 (std::min)(kInitialWidth, usableWidth));
    const int height = (std::max)(kMinimumHeight,
                                  (std::min)(kInitialHeight, usableHeight));

    RECT frame{0, 0, width, height};
    const DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    AdjustWindowRect(&frame, style, FALSE);
    const int frameWidth = frame.right - frame.left;
    const int frameHeight = frame.bottom - frame.top;
    const int x = (GetSystemMetrics(SM_CXSCREEN) - frameWidth) / 2;
    const int y = (GetSystemMetrics(SM_CYSCREEN) - frameHeight) / 3;

    const char* title = "Valkyrie Doctor & Crashfix — GTA San Andreas";
    HWND window = CreateWindowExA(
        WS_EX_TOPMOST, kClassName, title,
        style, x, y, frameWidth, frameHeight,
        nullptr, nullptr, self, nullptr);
    if (!window) {
        return;  // The log is already written; that is the important half.
    }

    int top = kHeaderHeight + kPad;

    const int viewButtonWidth = 160;
    HWND diagnosisButton = CreateWindowExA(
        0, "BUTTON", "Diagnosis", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, kPad,
        top, viewButtonWidth, kButtonHeight, window,
        reinterpret_cast<HMENU>(kIdDiagnosis), self, nullptr);
    SendMessageA(diagnosisButton, WM_SETFONT, reinterpret_cast<WPARAM>(g_bodyFont), TRUE);
    HWND logButton = CreateWindowExA(
        0, "BUTTON", "Full log", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        kPad + viewButtonWidth + 8, top, viewButtonWidth, kButtonHeight, window,
        reinterpret_cast<HMENU>(kIdFullLog), self, nullptr);
    SendMessageA(logButton, WM_SETFONT, reinterpret_cast<WPARAM>(g_bodyFont), TRUE);
    top += kButtonHeight + 10;

    const int reportHeight = kTextHeight - kButtonHeight - 10;
    const int causeLabelHeight = 18;
    const int causeHeight = 72;
    const int solutionLabelHeight = 18;
    const int solutionHeight = reportHeight - causeLabelHeight - causeHeight -
                               solutionLabelHeight - 10;

    HWND problemLabel = CreateWindowExA(
        0, "STATIC", "LIKELY CAUSE", WS_CHILD | WS_VISIBLE, kPad, top,
        width - kPad * 2, causeLabelHeight, window,
        reinterpret_cast<HMENU>(kIdProblemLabel), self, nullptr);
    SendMessageA(problemLabel, WM_SETFONT, reinterpret_cast<WPARAM>(g_smallFont), TRUE);
    top += causeLabelHeight;
    LoadLibraryW(L"Msftedit.dll");
    HWND problem = CreateReportBox(self, window, kIdProblem, kPad, top,
                                   width - kPad * 2, causeHeight, true);
    SetUtf8(problem, sections.problem);
    SendMessageA(problem, WM_SETFONT, reinterpret_cast<WPARAM>(g_bodyFont), TRUE);
    top += causeHeight + 5;

    HWND solutionLabel = CreateWindowExA(
        0, "STATIC", "WHAT TO DO", WS_CHILD | WS_VISIBLE, kPad, top,
        width - kPad * 2, solutionLabelHeight, window,
        reinterpret_cast<HMENU>(kIdSolutionLabel), self, nullptr);
    SendMessageA(solutionLabel, WM_SETFONT, reinterpret_cast<WPARAM>(g_smallFont), TRUE);
    top += solutionLabelHeight;
    HWND solution = CreateReportBox(self, window, kIdSolution, kPad, top,
                                    width - kPad * 2, solutionHeight, true);
    SetUtf8(solution, DiagnosisActionText(sections, false));
    SendMessageA(solution, WM_SETFONT, reinterpret_cast<WPARAM>(g_bodyFont), TRUE);

    // The full CrashInfo-style report occupies this same large area when the
    // player switches views, rather than opening a second, smaller window.
    top = kHeaderHeight + kPad + kButtonHeight + 10;
    HWND text = CreateReportBox(self, window, kIdText, kPad, top,
                                width - kPad * 2, reportHeight, false);
    SetUtf8(text, g_logText);
    SendMessageA(text, WM_SETFONT, reinterpret_cast<WPARAM>(g_smallFont), TRUE);
    top += reportHeight + kPad / 2;

    char userProfile[MAX_PATH] = {0};
    GetEnvironmentVariableA("USERPROFILE", userProfile, sizeof(userProfile));
    std::string pathLine = "Log: " + reportpaths::RedactUserProfile(
        g_logPath.c_str(), userProfile);
    HWND path = CreateWindowExA(0, "STATIC", pathLine.c_str(),
                                WS_CHILD | WS_VISIBLE | SS_PATHELLIPSIS, kPad,
                                top, width - kPad * 2, kPathHeight, window,
                                reinterpret_cast<HMENU>(kIdPath), self, nullptr);
    SendMessageA(path, WM_SETFONT, reinterpret_cast<WPARAM>(g_smallFont), TRUE);
    top += kPathHeight + kPad / 2;

    const int buttonWidth = 140;
    const int gap = 10;
    int bx = width - kPad - buttonWidth;
    struct { int id; const char* label; } buttons[] = {
        {kIdClose, "Close"},
        {kIdOpen, "Open log"},
        {kIdCopy, "Copy"},
    };
    for (const auto& b : buttons) {
        HWND button = CreateWindowExA(
            0, "BUTTON", b.label, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, bx, top,
            buttonWidth, kButtonHeight, window, reinterpret_cast<HMENU>(b.id),
            self, nullptr);
        SendMessageA(button, WM_SETFONT, reinterpret_cast<WPARAM>(g_bodyFont), TRUE);
        bx -= buttonWidth + gap;
    }
    HWND translateButton = CreateWindowExA(
        0, "BUTTON", "Español", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
        kPad, top, buttonWidth, kButtonHeight, window,
        reinterpret_cast<HMENU>(kIdTranslate), self, nullptr);
    SendMessageA(translateButton, WM_SETFONT,
                 reinterpret_cast<WPARAM>(g_bodyFont), TRUE);
    HWND footer = CreateWindowExA(0, "STATIC", "", WS_CHILD | WS_VISIBLE |
        SS_LEFTNOWORDWRAP,
        0, 0, 0, 0, window, reinterpret_cast<HMENU>(kIdFooter), self, nullptr);
    SendMessageA(footer, WM_SETFONT, reinterpret_cast<WPARAM>(g_smallFont), TRUE);
    HWND supports = CreateWindowExA(0, "STATIC", "GTA San Andreas",
        WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 0, 0, 0, 0, window,
        reinterpret_cast<HMENU>(kIdSupports), self, nullptr);
    SendMessageA(supports, WM_SETFONT,
                 reinterpret_cast<WPARAM>(g_smallFont), TRUE);
    Layout(window);
    ApplyLanguage(window);
    // Diagnosis is the main screen. Extra findings appear below the action so
    // nothing important is hidden behind a separate tab.
    ShowPage(window, Page::Diagnosis);
    ShowWindow(window, SW_SHOW);
    SetForegroundWindow(window);
    UpdateWindow(window);

    MSG message{};
    while (!g_done && GetMessageA(&message, nullptr, 0, 0) > 0) {
        if (!IsDialogMessageA(window, &message)) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
    }

    if (g_bodyFont) DeleteObject(g_bodyFont);
    if (g_smallFont) DeleteObject(g_smallFont);
    if (g_backBrush) DeleteObject(g_backBrush);
    g_bodyFont = nullptr;
    g_smallFont = nullptr;
    g_backBrush = nullptr;
}

}  // namespace crashwindow
