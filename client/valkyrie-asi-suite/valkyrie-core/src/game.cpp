#include "game.h"

#include <windows.h>

#include <cmath>
#include <cstring>
#include <limits>

#include "log.h"

namespace game {
namespace {

// GTA SA 1.0 US, HOODLUM. plugin-sdk identifies this build by the first four
// bytes of the entry section, which the unpacker stub leaves alone.
constexpr uintptr_t kVersionProbe = 0x401000;
constexpr uint32_t kHoodlum = 0x16197BE9;
constexpr uint32_t kCompact = 0x53EC8B55;

// CRadar, all cdecl.
//
// Two ways to plant a coordinate blip. The short range one is what the game
// uses for shops: on the radar only when you are near, on the full map always.
// That is the behaviour we want for four hundred businesses, and the long range
// one is kept for the few things worth seeing from across the state.
constexpr uintptr_t kSetCoordBlip = 0x583820;
constexpr uintptr_t kSetShortRangeCoordBlip = 0x583920;
constexpr uintptr_t kChangeBlipScale = 0x583CC0;
constexpr uintptr_t kSetBlipSprite = 0x583D70;
constexpr uintptr_t kClearBlip = 0x587CE0;

// The call to CGame::Process inside Idle(). plugin-sdk hangs its
// gameProcessEvent on this exact call site, which makes it the best documented
// once-per-frame point in the game.
constexpr uintptr_t kFrameCallSite = 0x53E981;

// FrontEndMenuManager, and the fields in it we care about. The offsets are
// plugin-sdk's, which asserts them against the real structure layout.
constexpr uintptr_t kMenuManager = 0xBA6748;
constexpr uintptr_t kDrawRadarOrMap = kMenuManager + 0x59;
constexpr uintptr_t kMenuActive = kMenuManager + 0x5C;
// The map's crosshair, in world coordinates - see the note in game.h.
constexpr uintptr_t kMapCursor = kMenuManager + 0x70;  // CVector2D

// The real screen cursor, as whole pixels.
constexpr uintptr_t kMouseScreenX = kMenuManager + 0xBC;
constexpr uintptr_t kMouseScreenY = kMenuManager + 0xC0;
constexpr uintptr_t kMapZoom = kMenuManager + 0x64;
constexpr uintptr_t kMapBaseX = kMenuManager + 0x68;
constexpr uintptr_t kMapBaseY = kMenuManager + 0x6C;
constexpr uintptr_t kCurrentMenuPage = kMenuManager + 0x15D;

// CRadar's live range and origin. Fastman's 48,000-unit map patch changes the
// range from the stock 2990 to an expanded-map value of 23920. The frontend map is never
// rotated, so using these values directly avoids the driving radar's cached
// heading that CRadar::TransformRealWorldPointToRadarSpace would apply here.
constexpr uintptr_t kRadarRange = 0xBA8314;
constexpr uintptr_t kRadarOrigin = 0xBAA248;  // CVector2D

// CPad::NewMouseControllerState (CMouseControllerState). The wheel booleans
// are bytes 3 and 4 in the stock 0x14-byte structure; byte 0 is LMB.
constexpr uintptr_t kNewMouseState = 0xB73418;
constexpr uintptr_t kMouseLeft = kNewMouseState;
constexpr uintptr_t kMouseWheelUp = kNewMouseState + 3;
constexpr uintptr_t kMouseWheelDown = kNewMouseState + 4;

// CMenuManager::ProcessUserInput, GTA SA 1.0 US. The first two conditional
// branches enter native map zoom when the wheel byte is set. The last address
// begins GTA's 6000-unit-map origin clamp; we jump over that block while
// retaining its cursor-coordinate clamp at 0x578821.
constexpr uintptr_t kMapWheelUpBranch = 0x57762B;
constexpr uintptr_t kMapWheelDownBranch = 0x57795E;
constexpr uintptr_t kMapOriginClamp = 0x578785;
constexpr uintptr_t kMapOriginClampEnd = 0x578821;

// CRadar::DrawRadarSectionMap. ProperRadar patches an internal texture lookup
// at 0x586584; hooking the function entry lets the detailed path (and that
// existing patch) continue unchanged while replacing only the unstable full
// overview with one pre-composed texture.
constexpr uintptr_t kDrawRadarSectionMap = 0x586520;
constexpr size_t kDrawRadarSectionMapPrologue = 7;
constexpr float kOverviewTextureMaxZoom = 650.0f;

// CTxdStore / CSprite2d, GTA SA 1.0 US. These are the same plugin-sdk entry
// points used by the game's own frontend texture loader.
constexpr uintptr_t kTxdPushCurrent = 0x7316A0;
constexpr uintptr_t kTxdPopCurrent = 0x7316B0;
constexpr uintptr_t kTxdFindSlot = 0x731850;
constexpr uintptr_t kTxdSetCurrent = 0x7319C0;
constexpr uintptr_t kTxdAddRef = 0x731A00;
constexpr uintptr_t kTxdAddSlot = 0x731C80;
constexpr uintptr_t kTxdRemoveSlot = 0x731CD0;
constexpr uintptr_t kTxdLoadFile = 0x7320B0;
constexpr uintptr_t kRwTextureRead = 0x4C7510;
constexpr uintptr_t kSpriteDraw = 0x728350;

// eMenuPage: the map is page 5. Checking the page rather than just "a menu is
// open" is what keeps the overlay off the pause menu, where it has no business
// being and covered half the buttons.
constexpr unsigned char kPageMap = 5;

// The call to the menu's own drawing, hooked after it runs so we paint on top
// of the map rather than under it. plugin-sdk calls this menuDrawingEvent and
// lists two call sites for San Andreas: one for the menu before a game has
// started, and this one for the pause menu during play. The pause menu is the
// only one with a map on it.
//
// It sits right beside the frame hook above, in the same Idle loop, which is a
// good sign it is the right one. The first address tried here came from the
// GTA 2 block at the top of plugin-sdk's Events.h rather than the San Andreas
// one, and pointed at a push instruction - caught only because the hook checks
// for a call opcode before patching anything.
constexpr uintptr_t kMenuDrawCallSite = 0x53EB8C;

// The radar's world-to-screen pair. On the map screen the game sets these up
// for the map, so the same calls that place a blip place our cursor test.
constexpr uintptr_t kTransformRealWorldToRadar = 0x583530;
constexpr uintptr_t kTransformRadarToScreen = 0x583480;

// Text and rectangles.
constexpr uintptr_t kFontSetScale = 0x719380;
constexpr uintptr_t kFontSetColor = 0x719430;
constexpr uintptr_t kFontSetFontStyle = 0x719490;
constexpr uintptr_t kFontSetWrapx = 0x7194D0;
constexpr uintptr_t kFontSetRightJustifyWrap = 0x7194F0;
constexpr uintptr_t kFontSetDropColor = 0x719510;
constexpr uintptr_t kFontSetDropShadow = 0x719570;
constexpr uintptr_t kFontSetEdge = 0x719590;
constexpr uintptr_t kFontSetProportional = 0x7195B0;
constexpr uintptr_t kFontSetBackground = 0x7195C0;
constexpr uintptr_t kFontSetJustify = 0x719600;
constexpr uintptr_t kFontSetOrientation = 0x719610;
constexpr uintptr_t kFontPrintString = 0x71A700;
constexpr uintptr_t kFontGetStringWidth = 0x71A0E0;
constexpr uintptr_t kSpriteDrawRect = 0x727B60;

// Drawing a blip picture at a size of our choosing. The table address is the
// stock one and may have moved - see SpriteTableUsable, which checks before
// anything indexes it.
constexpr uintptr_t kDrawRotatingRadarSprite = 0x584850;
constexpr uintptr_t kRadarBlipSprites = 0xBAA250;

// The game's own "draw a blip picture" function. It has to index the picture
// table, so the table's address is a plain number inside its code - which is
// how we find it when it has been moved.
constexpr uintptr_t kDrawRadarSprite = 0x585FF0;
constexpr size_t kScanBytes = 0x300;

// A CSprite2d is one texture pointer.
constexpr size_t kSpriteStride = 4;

// Eagle's table runs to 130; anything past that is certainly not ours.
constexpr int kMaxBlipSprites = 200;

// The flush.
//
// CFont::PrintString does not draw anything - it adds the text to a batch, and
// CFont::DrawFonts renders the batch. The menu calls that itself as the last
// thing it does, which is before we run, so text we queued afterwards sat in
// the buffer and was never painted. Panels appeared with nothing written on
// them and nothing said why.
constexpr uintptr_t kFontDrawFonts = 0x71A210;

// eFontAlignment: centre, left, right.
constexpr unsigned char kAlignLeft = 1;

// Font 1 is the game's plain menu face. Style 2 is the blocky one used for
// headings, which is unreadable at the size we need.
constexpr short kFontStyle = 1;

// Base size, in the 640x448 space the game's font is designed against. These
// are multiplied up by the real back buffer so the panel is the same size on
// any monitor rather than shrinking on a big one.
constexpr float kFontScaleX = 0.30f;
constexpr float kFontScaleY = 0.62f;

// Line spacing, in the same base space. Comfortably clear of the glyph height:
// text that overlaps is unreadable, text that is a little airy is not, so this
// errs the safe way. The first version of this had it far too tight and the
// legend came out as a solid black smear.
constexpr float kLineBase = 11.0f;

// RsGlobal - appName, then the back buffer size.
constexpr uintptr_t kRsGlobal = 0xC17040;
constexpr uintptr_t kScreenWidth = kRsGlobal + 0x4;
constexpr uintptr_t kScreenHeight = kRsGlobal + 0x8;

// The game's rectangle: x1, y1, x2, y2 in memory order.
struct Rect {
    float left, bottom, right, top;
};

struct Colour {
    uint8_t r, g, b, a;
};

struct Sprite {
    void* texture;
};

bool g_ready = false;
const char* g_version = "";
bool g_overviewDrawn = false;
bool g_overviewLoadTried = false;
void* g_overviewTexture = nullptr;

using DrawRadarSectionMapFn = void(__cdecl*)(int, int, Rect);
DrawRadarSectionMapFn g_originalDrawRadarSectionMap = nullptr;

void* LoadOverviewTexture() {
    if (g_overviewLoadTried) {
        return g_overviewTexture;
    }
    g_overviewLoadTried = true;

    char path[MAX_PATH]{};
    if (!GetModuleFileNameA(nullptr, path, MAX_PATH)) {
        logfile::Line("map overview: cannot locate gta_sa.exe");
        return nullptr;
    }
    char* slash = strrchr(path, '\\');
    if (!slash) {
        logfile::Line("map overview: game path has no directory");
        return nullptr;
    }
    slash[1] = '\0';
    strncat_s(path, "sprp-map-sa-overview.txd", _TRUNCATE);

    using FindSlot = int(__cdecl*)(const char*);
    using AddSlot = int(__cdecl*)(const char*);
    using LoadFile = bool(__cdecl*)(int, const char*);
    using SlotFn = void(__cdecl*)(int);

    int slot = reinterpret_cast<FindSlot>(kTxdFindSlot)("sprp_map_overview");
    const bool added = slot < 0;
    if (added) {
        slot = reinterpret_cast<AddSlot>(kTxdAddSlot)("sprp_map_overview");
    }
    if (slot < 0 ||
        (added && !reinterpret_cast<LoadFile>(kTxdLoadFile)(slot, path))) {
        if (slot >= 0 && added) {
            reinterpret_cast<SlotFn>(kTxdRemoveSlot)(slot);
        }
        logfile::Line("map overview: could not load %s - retaining ProperRadar tiles", path);
        return nullptr;
    }

    reinterpret_cast<SlotFn>(kTxdAddRef)(slot);
    reinterpret_cast<void(__cdecl*)()>(kTxdPushCurrent)();
    reinterpret_cast<SlotFn>(kTxdSetCurrent)(slot);
    using ReadTexture = void*(__cdecl*)(const char*, const char*);
    g_overviewTexture =
        reinterpret_cast<ReadTexture>(kRwTextureRead)("sprp_overview", nullptr);
    reinterpret_cast<void(__cdecl*)()>(kTxdPopCurrent)();

    if (!g_overviewTexture) {
        logfile::Line("map overview: TXD loaded but sprp_overview was not readable");
        return nullptr;
    }
    logfile::Line("map overview: single 3072x3072 texture loaded; ProperRadar tile storm bypassed below %.0f zoom",
                  kOverviewTextureMaxZoom);
    return g_overviewTexture;
}

void DrawOverview() {
    void* texture = LoadOverviewTexture();
    if (!texture) {
        return;
    }

    const MapView view = Map();
    const Point screen = ScreenSize();
    if (!std::isfinite(view.zoom) || !std::isfinite(view.baseX) ||
        !std::isfinite(view.baseY) || screen.x <= 0.0f || screen.y <= 0.0f) {
        return;
    }

    const float sx = screen.x / 640.0f;
    const float sy = screen.y / 448.0f;
    const Rect rect{
        (view.baseX - view.zoom) * sx,
        (view.baseY + view.zoom) * sy,
        (view.baseX + view.zoom) * sx,
        (view.baseY - view.zoom) * sy,
    };
    const Colour white{255, 255, 255, 255};
    Sprite sprite{texture};
    using Draw = void(__thiscall*)(Sprite*, const Rect&, const Colour&);
    reinterpret_cast<Draw>(kSpriteDraw)(&sprite, rect, white);
}

void __cdecl DrawRadarSectionMapReplacement(int x, int y, Rect rect) {
    if (Map().zoom <= kOverviewTextureMaxZoom && LoadOverviewTexture()) {
        if (!g_overviewDrawn) {
            DrawOverview();
            g_overviewDrawn = true;
        }
        return;
    }
    if (g_originalDrawRadarSectionMap) {
        g_originalDrawRadarSectionMap(x, y, rect);
    }
}

// The frame hook. The game's call is rewritten to land here instead; we run our
// own work and then go where it was going.
using VoidFn = void (*)();
VoidFn g_originalFrame = nullptr;
FrameFn g_beforeFrameFn = nullptr;
FrameFn g_afterFrameFn = nullptr;

void __cdecl FrameTrampoline() {
    if (g_beforeFrameFn) {
        g_beforeFrameFn();
    }
    if (g_originalFrame) {
        g_originalFrame();
    }
    if (g_afterFrameFn) {
        g_afterFrameFn();
    }
}

// The menu draw is a thiscall - the menu manager arrives in ECX. __fastcall is
// the only way to get at a register argument from C++, and it lines up: the
// function takes no stack arguments, so there is nothing to clean up either
// way. The second __fastcall register is whatever happened to be in EDX and is
// ignored.
//
// It is declared as returning int even though the reference calls it void, and
// that is the whole point. A void trampoline leaves EAX holding whatever our
// own last call put there, and if the game reads a return value from this the
// answer is then garbage every single frame. That is not theoretical: the first
// version of this was void, and the result was a game where the menu never
// closed - no HUD, no control of the character or camera, while the map itself
// worked perfectly. Capturing the value and handing it straight back costs
// nothing and cannot be wrong either way.
using MenuDrawFn = int(__fastcall*)(void*, void*);
MenuDrawFn g_originalMenuDraw = nullptr;
FrameFn g_menuDrawFn = nullptr;

int __fastcall MenuDrawTrampoline(void* self, void* edx) {
    int result = 0;
    if (g_originalMenuDraw) {
        result = g_originalMenuDraw(self, edx);
    }
    // After, so we are drawing over a finished map rather than under it.
    if (g_menuDrawFn) {
        g_menuDrawFn();
    }
    return result;
}

// Make a page writable, do something, put it back. Leaving the game's code
// segment writable would be its own kind of bug.
template <typename Fn>
bool WithWritable(uintptr_t at, size_t len, Fn&& fn) {
    DWORD old = 0;
    if (!VirtualProtect(reinterpret_cast<void*>(at), len, PAGE_EXECUTE_READWRITE, &old)) {
        return false;
    }
    fn();
    VirtualProtect(reinterpret_cast<void*>(at), len, old, &old);
    return true;
}

// Split ASIs share documented GTA call sites. Their startup threads can wake
// together, so serialize the read-chain-write sequence across DLL boundaries.
class HookLock {
public:
    explicit HookLock(const char* name) {
        handle_ = CreateMutexA(nullptr, FALSE, name);
        if (handle_) {
            const DWORD wait = WaitForSingleObject(handle_, 5000);
            held_ = wait == WAIT_OBJECT_0 || wait == WAIT_ABANDONED;
        }
    }

    ~HookLock() {
        if (held_) ReleaseMutex(handle_);
        if (handle_) CloseHandle(handle_);
    }

    bool Held() const { return held_; }

private:
    HANDLE handle_ = nullptr;
    bool held_ = false;
};

bool Executable(const void* address) {
    MEMORY_BASIC_INFORMATION mbi{};
    if (!address || VirtualQuery(address, &mbi, sizeof(mbi)) == 0 ||
        mbi.State != MEM_COMMIT || (mbi.Protect & PAGE_GUARD)) {
        return false;
    }
    const DWORD protection = mbi.Protect & 0xFF;
    return protection == PAGE_EXECUTE || protection == PAGE_EXECUTE_READ ||
           protection == PAGE_EXECUTE_READWRITE ||
           protection == PAGE_EXECUTE_WRITECOPY;
}

}  // namespace

bool Init() {
    if (g_ready) {
        return true;
    }

    // Reading through a pointer into another module's image can fault if the
    // game is not what we think it is, so ask before looking.
    MEMORY_BASIC_INFORMATION mbi{};
    if (VirtualQuery(reinterpret_cast<void*>(kVersionProbe), &mbi, sizeof(mbi)) == 0 ||
        mbi.State != MEM_COMMIT) {
        logfile::Line("game: cannot read the entry point - not going to guess at what this is");
        return false;
    }

    const uint32_t probe = *reinterpret_cast<uint32_t*>(kVersionProbe);
    if (probe == kHoodlum) {
        g_version = "1.0 US HOODLUM";
    } else if (probe == kCompact) {
        g_version = "1.0 US Compact";
    } else {
        logfile::Line("game: this is not San Andreas 1.0 US (probe %08X) - standing down, nothing patched",
                  probe);
        return false;
    }

    logfile::Line("game: San Andreas %s", g_version);
    g_ready = true;
    return true;
}

const char* VersionName() {
    return g_version;
}

int SetCoordBlip(BlipType type, Vector at, uint32_t colour, BlipDisplay display,
                 bool longRange) {
    if (!g_ready) {
        return 0;
    }
    // The real signature takes the vector by value and a script name it ignores
    // for coordinate blips. Both functions take the same arguments.
    using Fn = int(__cdecl*)(BlipType, Vector, uint32_t, BlipDisplay, const char*);
    const uintptr_t at_fn = longRange ? kSetCoordBlip : kSetShortRangeCoordBlip;
    return reinterpret_cast<Fn>(at_fn)(type, at, colour, display, nullptr);
}

void SetBlipSprite(int blip, int sprite) {
    if (!g_ready || blip == 0) {
        return;
    }
    using Fn = void(__cdecl*)(int, int);
    reinterpret_cast<Fn>(kSetBlipSprite)(blip, sprite);
}

void ChangeBlipScale(int blip, int size) {
    if (!g_ready || blip == 0) {
        return;
    }
    using Fn = void(__cdecl*)(int, int);
    reinterpret_cast<Fn>(kChangeBlipScale)(blip, size);
}

void ClearBlip(int blip) {
    if (!g_ready || blip == 0) {
        return;
    }
    using Fn = void(__cdecl*)(int);
    reinterpret_cast<Fn>(kClearBlip)(blip);
}

bool MapIsOpen() {
    if (!g_ready) {
        return false;
    }

    const bool menu = *reinterpret_cast<const bool*>(kMenuActive);
    const unsigned char page = *reinterpret_cast<const unsigned char*>(kCurrentMenuPage);
    const bool onMap = menu && page == kPageMap;

    // Log whenever this changes, so if it ever reads the game wrongly the log
    // says so plainly rather than the map just misbehaving.
    static bool last = false;
    static unsigned char lastPage = 0xFF;
    if (onMap != last || page != lastPage) {
        last = onMap;
        lastPage = page;
        logfile::Line("game: menu %s, page %u%s", menu ? "open" : "closed", page,
                      onMap ? " - the map" : "");
    }
    return onMap;
}

bool MenuIsOpen() {
    return g_ready && *reinterpret_cast<const bool*>(kMenuActive);
}

void FlushText() {
    if (g_ready) {
        reinterpret_cast<void(__cdecl*)()>(kFontDrawFonts)();
    }
}

bool HookFrame(FrameFn before, FrameFn after) {
    if (!g_ready) {
        return false;
    }
    if (g_beforeFrameFn) {
        // Already hooked. Swapping the callback is fine; installing the patch
        // twice would chain the trampoline to itself and hang the game.
        g_beforeFrameFn = before;
        g_afterFrameFn = after;
        return true;
    }

    HookLock lock("Local\\SPRP.FrameHook");
    if (!lock.Held()) {
        logfile::Line("game: timed out waiting to install the cooperative frame hook");
        return false;
    }

    // The site remains a five-byte relative call after another split ASI has
    // installed itself. Its current destination becomes our original, forming
    // a chain instead of overwriting whichever component loaded first.
    auto* site = reinterpret_cast<uint8_t*>(kFrameCallSite);
    if (*site != 0xE8) {
        logfile::Line("game: the frame call site does not look like a call (%02X) - not hooking", *site);
        return false;
    }

    const int32_t rel = *reinterpret_cast<int32_t*>(kFrameCallSite + 1);
    g_originalFrame = reinterpret_cast<VoidFn>(kFrameCallSite + 5 + rel);
    if (g_originalFrame == &FrameTrampoline ||
        !Executable(reinterpret_cast<const void*>(g_originalFrame))) {
        logfile::Line("game: frame call target %p is not a safe chain target - not hooking",
                      reinterpret_cast<void*>(g_originalFrame));
        g_originalFrame = nullptr;
        return false;
    }
    g_beforeFrameFn = before;
    g_afterFrameFn = after;

    const int32_t patched = static_cast<int32_t>(reinterpret_cast<uintptr_t>(&FrameTrampoline)) -
                            static_cast<int32_t>(kFrameCallSite + 5);

    const bool ok = WithWritable(kFrameCallSite + 1, sizeof(int32_t), [&] {
        *reinterpret_cast<int32_t*>(kFrameCallSite + 1) = patched;
    });

    if (!ok) {
        logfile::Line("game: could not make the frame call site writable");
        g_beforeFrameFn = nullptr;
        g_afterFrameFn = nullptr;
        return false;
    }

    logfile::Line("game: cooperative frame hook installed; previous target %p",
                  reinterpret_cast<void*>(g_originalFrame));
    return true;
}

bool HookMenuDraw(FrameFn fn) {
    if (!g_ready) {
        return false;
    }
    if (g_menuDrawFn) {
        g_menuDrawFn = fn;
        return true;
    }

    HookLock lock("Local\\SPRP.MenuDrawHook");
    if (!lock.Held()) {
        logfile::Line("game: timed out waiting to install the cooperative menu hook");
        return false;
    }

    auto* site = reinterpret_cast<uint8_t*>(kMenuDrawCallSite);
    if (*site != 0xE8) {
        logfile::Line("game: the menu draw call site does not look like a call (%02X) - "
                      "no map overlay this session", *site);
        return false;
    }

    const int32_t rel = *reinterpret_cast<int32_t*>(kMenuDrawCallSite + 1);
    g_originalMenuDraw = reinterpret_cast<MenuDrawFn>(kMenuDrawCallSite + 5 + rel);
    if (g_originalMenuDraw == &MenuDrawTrampoline ||
        !Executable(reinterpret_cast<const void*>(g_originalMenuDraw))) {
        logfile::Line("game: menu call target %p is not a safe chain target - no overlay",
                      reinterpret_cast<void*>(g_originalMenuDraw));
        g_originalMenuDraw = nullptr;
        return false;
    }
    g_menuDrawFn = fn;

    const int32_t patched = static_cast<int32_t>(reinterpret_cast<uintptr_t>(&MenuDrawTrampoline)) -
                            static_cast<int32_t>(kMenuDrawCallSite + 5);

    const bool ok = WithWritable(kMenuDrawCallSite + 1, sizeof(int32_t), [&] {
        *reinterpret_cast<int32_t*>(kMenuDrawCallSite + 1) = patched;
    });

    if (!ok) {
        logfile::Line("game: could not make the menu draw call site writable");
        g_menuDrawFn = nullptr;
        return false;
    }

    logfile::Line("game: cooperative menu hook installed; previous target %p",
                  reinterpret_cast<void*>(g_originalMenuDraw));
    return true;
}

Point WorldToMapRadar(float worldX, float worldY) {
    const float range = *reinterpret_cast<const float*>(kRadarRange);
    const float* origin = reinterpret_cast<const float*>(kRadarOrigin);
    if (!std::isfinite(range) || range < 1000.0f ||
        !std::isfinite(origin[0]) || !std::isfinite(origin[1])) {
        const float invalid = std::numeric_limits<float>::quiet_NaN();
        return {invalid, invalid};
    }
    return {(worldX - origin[0]) / range,
            (worldY - origin[1]) / range};
}

Point WorldToScreen(float worldX, float worldY) {
    float world[2] = {worldX, worldY};
    float radar[2] = {0.0f, 0.0f};
    float screen[2] = {0.0f, 0.0f};

    using ToRadar = void(__cdecl*)(float*, const float*);
    using ToScreen = void(__cdecl*)(float*, const float*);
    reinterpret_cast<ToRadar>(kTransformRealWorldToRadar)(radar, world);
    reinterpret_cast<ToScreen>(kTransformRadarToScreen)(screen, radar);

    return {screen[0], screen[1]};
}

Point MapCursor() {
    const float* p = reinterpret_cast<const float*>(kMapCursor);
    return {p[0], p[1]};
}

int MapZoomWheel() {
    const bool up = *reinterpret_cast<const bool*>(kMouseWheelUp);
    const bool down = *reinterpret_cast<const bool*>(kMouseWheelDown);
    return up == down ? 0 : (up ? 1 : -1);
}

bool MapLeftHeld() {
    return *reinterpret_cast<const bool*>(kMouseLeft);
}

bool InstallMapControlPatch() {
    auto* up = reinterpret_cast<uint8_t*>(kMapWheelUpBranch);
    auto* down = reinterpret_cast<uint8_t*>(kMapWheelDownBranch);
    auto* clamp = reinterpret_cast<uint8_t*>(kMapOriginClamp);

    const bool branchesOriginal = up[0] == 0x75 && up[1] == 0x1E &&
                                  down[0] == 0x75 && down[1] == 0x1E;
    const bool branchesPatched = up[0] == 0x90 && up[1] == 0x90 &&
                                 down[0] == 0x90 && down[1] == 0x90;
    const bool clampOriginal = clamp[0] == 0xD9 && clamp[1] == 0x46 &&
                               clamp[2] == 0x6C && clamp[3] == 0xD8 &&
                               clamp[4] == 0x66;
    const bool clampPatched = clamp[0] == 0xE9;

    if ((!branchesOriginal && !branchesPatched) ||
        (!clampOriginal && !clampPatched)) {
        logfile::Line(
            "game: map-control signatures changed (up %02X %02X, down %02X %02X, clamp %02X %02X %02X %02X %02X) - not patching",
            up[0], up[1], down[0], down[1], clamp[0], clamp[1], clamp[2],
            clamp[3], clamp[4]);
        return false;
    }

    bool ok = true;
    if (branchesOriginal) {
        ok = WithWritable(kMapWheelUpBranch, 2, [&] {
            up[0] = up[1] = 0x90;
        }) && ok;
        ok = WithWritable(kMapWheelDownBranch, 2, [&] {
            down[0] = down[1] = 0x90;
        }) && ok;
    }
    if (clampOriginal) {
        const int32_t relative = static_cast<int32_t>(kMapOriginClampEnd) -
                                 static_cast<int32_t>(kMapOriginClamp + 5);
        ok = WithWritable(kMapOriginClamp, 5, [&] {
            clamp[0] = 0xE9;
            *reinterpret_cast<int32_t*>(clamp + 1) = relative;
        }) && ok;
    }

    if (!ok) {
        logfile::Line("game: could not make the native map controls writable");
        return false;
    }

    logfile::Line(
        "game: native map wheel and 6000-unit origin clamp suppressed; custom map control owns them");
    return true;
}

bool InstallMapOverviewPatch() {
    if (!g_ready) {
        return false;
    }

    auto* site = reinterpret_cast<uint8_t*>(kDrawRadarSectionMap);
    const uint8_t expected[kDrawRadarSectionMapPrologue] = {
        0x8B, 0x54, 0x24, 0x04, 0x83, 0xEC, 0x08,
    };
    if (memcmp(site, expected, sizeof(expected)) != 0) {
        logfile::Line(
            "map overview: DrawRadarSectionMap entry changed (%02X %02X %02X %02X %02X %02X %02X) - leaving it alone",
            site[0], site[1], site[2], site[3], site[4], site[5], site[6]);
        return false;
    }

    auto* trampoline = static_cast<uint8_t*>(
        VirtualAlloc(nullptr, kDrawRadarSectionMapPrologue + 5,
                     MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE));
    if (!trampoline) {
        logfile::Line("map overview: could not allocate the detailed-map trampoline");
        return false;
    }

    memcpy(trampoline, site, kDrawRadarSectionMapPrologue);
    trampoline[kDrawRadarSectionMapPrologue] = 0xE9;
    *reinterpret_cast<int32_t*>(trampoline + kDrawRadarSectionMapPrologue + 1) =
        static_cast<int32_t>(kDrawRadarSectionMap + kDrawRadarSectionMapPrologue) -
        static_cast<int32_t>(reinterpret_cast<uintptr_t>(trampoline) +
                             kDrawRadarSectionMapPrologue + 5);

    const int32_t replacement =
        static_cast<int32_t>(reinterpret_cast<uintptr_t>(
            &DrawRadarSectionMapReplacement)) -
        static_cast<int32_t>(kDrawRadarSectionMap + 5);
    const bool ok = WithWritable(
        kDrawRadarSectionMap, kDrawRadarSectionMapPrologue, [&] {
            site[0] = 0xE9;
            *reinterpret_cast<int32_t*>(site + 1) = replacement;
            site[5] = 0x90;
            site[6] = 0x90;
        });
    if (!ok) {
        VirtualFree(trampoline, 0, MEM_RELEASE);
        logfile::Line("map overview: could not make DrawRadarSectionMap writable");
        return false;
    }

    FlushInstructionCache(GetCurrentProcess(), site,
                          kDrawRadarSectionMapPrologue);
    g_originalDrawRadarSectionMap =
        reinterpret_cast<DrawRadarSectionMapFn>(trampoline);
    logfile::Line(
        "map overview: detailed tiles retained; distant full map uses one composed draw");
    return true;
}

void BeginMapFrame() {
    g_overviewDrawn = false;
    if (g_ready && MapIsOpen() && !g_overviewLoadTried) {
        // Loading during the first section draw would stall in the middle of
        // the renderer. Do it at the start of that map frame instead.
        LoadOverviewTexture();
    }
}

Point MousePos() {
    // These two are the real screen cursor, kept as whole pixels.
    return {static_cast<float>(*reinterpret_cast<const int*>(kMouseScreenX)),
            static_cast<float>(*reinterpret_cast<const int*>(kMouseScreenY))};
}

MapView Map() {
    return {*reinterpret_cast<const float*>(kMapZoom),
            *reinterpret_cast<const float*>(kMapBaseX),
            *reinterpret_cast<const float*>(kMapBaseY)};
}

void SetMapView(MapView view) {
    *reinterpret_cast<float*>(kMapZoom) = view.zoom;
    *reinterpret_cast<float*>(kMapBaseX) = view.baseX;
    *reinterpret_cast<float*>(kMapBaseY) = view.baseY;
}

Point ScreenSize() {
    return {static_cast<float>(*reinterpret_cast<const int*>(kScreenWidth)),
            static_cast<float>(*reinterpret_cast<const int*>(kScreenHeight))};
}

// How much bigger this screen is than the 448-line space the game's interface
// was drawn for. Everything we size goes through this.
float UiScale() {
    const float height = static_cast<float>(*reinterpret_cast<const int*>(kScreenHeight));
    return height > 0.0f ? height / 448.0f : 1.0f;
}

float LineHeight() {
    return kLineBase * UiScale();
}

void DrawRect(float left, float top, float right, float bottom, uint32_t argb) {
    // CRect holds x1, y1, x2, y2 in that order.
    const Rect rect{left, top, right, bottom};

    // CRGBA is four bytes, red first, passed by const reference.
    const uint8_t colour[4] = {
        static_cast<uint8_t>((argb >> 16) & 0xFF),
        static_cast<uint8_t>((argb >> 8) & 0xFF),
        static_cast<uint8_t>(argb & 0xFF),
        static_cast<uint8_t>((argb >> 24) & 0xFF),
    };

    using Fn = void(__cdecl*)(const Rect&, const uint8_t(&)[4]);
    reinterpret_cast<Fn>(kSpriteDrawRect)(rect, colour);
}

// Set the font up the same way every time.
//
// Every one of these matters. The menu draws its own text immediately before we
// run and leaves the font however it liked - a shadow, an edge, centre
// alignment, a wrap width halfway across the screen. Anything not set here is
// inherited, and inherited state is why text that works one frame looks wrong
// the next.
static void PrepareFont(uint32_t argb, float scale) {
    // CFont::SetColor takes the colour BY VALUE - a four byte struct, which on
    // this ABI is passed as a plain 32 bit word. CSprite2d::DrawRect takes the
    // same struct by const reference, which is a pointer.
    //
    // Getting those two the same way round is not cosmetic. Passing a pointer
    // where a value is wanted hands the game a stack address as a colour, and
    // the top byte of a stack address is zero - so the alpha is zero and the
    // text draws perfectly, completely invisibly. Rectangles kept working
    // because a pointer is what they actually wanted, which is why the panels
    // showed up with nothing written on them.
    const uint32_t rgba = ((argb & 0x00FF0000) >> 16)         // red
                        | (argb & 0x0000FF00)                  // green
                        | ((argb & 0x000000FF) << 16)          // blue
                        | (argb & 0xFF000000);                 // alpha
    const uint32_t shadow = 0xFF000000;

    reinterpret_cast<void(__cdecl*)(short)>(kFontSetFontStyle)(kFontStyle);
    reinterpret_cast<void(__cdecl*)(bool)>(kFontSetProportional)(true);
    reinterpret_cast<void(__cdecl*)(bool, bool)>(kFontSetBackground)(false, false);
    reinterpret_cast<void(__cdecl*)(bool)>(kFontSetJustify)(false);
    reinterpret_cast<void(__cdecl*)(unsigned char)>(kFontSetOrientation)(kAlignLeft);
    reinterpret_cast<void(__cdecl*)(short)>(kFontSetDropShadow)(1);
    reinterpret_cast<void(__cdecl*)(short)>(kFontSetEdge)(0);
    reinterpret_cast<void(__cdecl*)(uint32_t)>(kFontSetDropColor)(shadow);
    reinterpret_cast<void(__cdecl*)(uint32_t)>(kFontSetColor)(rgba);

    const float ui = UiScale();
    reinterpret_cast<void(__cdecl*)(float, float)>(kFontSetScale)(
        kFontScaleX * scale * ui, kFontScaleY * scale * ui);

    // No wrapping. Ours are single lines that we have already measured.
    const Point screen = ScreenSize();
    reinterpret_cast<void(__cdecl*)(float)>(kFontSetWrapx)(screen.x * 2.0f);
    reinterpret_cast<void(__cdecl*)(float)>(kFontSetRightJustifyWrap)(0.0f);
}

void PrintText(float x, float y, const char* text, uint32_t argb, float scale) {
    PrepareFont(argb, scale);
    reinterpret_cast<void(__cdecl*)(float, float, const char*)>(kFontPrintString)(x, y, text);
}

// Note on making a marker bigger, so nobody tries this again.
//
// The game will not resize a blip: its size setting applies only to the plain
// square markers, and a picture is drawn at a fixed size whatever it says.
//
// There IS a call that draws a blip picture at any width and height - and it
// needs a pointer into the game's table of pictures. That table moves: allowing
// more blip pictures than the game shipped with means putting them somewhere
// with room, so the stock address is wrong here.
//
// Searching the game's own code for the new address looks promising and is not
// safe. A heuristic cannot tell a table of textures from any other run of
// plausible numbers; it settled on an address inside another mod entirely, and
// handing that to the sprite drawing killed the game inside d3d9.
//
// The only sound way would be to read the limit adjuster's own record of what
// it moved and where. That is a great deal of work for a slightly larger icon,
// so the overlay rings the marker instead, which asks the game for nothing.

float TextWidth(const char* text, float scale) {
    PrepareFont(0xFFFFFFFF, scale);
    using Fn = float(__cdecl*)(const char*, bool, bool);
    return reinterpret_cast<Fn>(kFontGetStringWidth)(text, true, false);
}

}  // namespace game
