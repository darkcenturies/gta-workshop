// The bits of San Andreas we talk to.
//
// Every address here is Grand Theft Auto: San Andreas v1.0 US, and they were
// read out of plugin-sdk (github.com/DK22Pac/plugin-sdk, the -sa fork the
// server owner pointed at) rather than written from memory. Our players run the
// HOODLUM 1.0 build, which the crash logs confirm and which Init() checks for
// before anything is called or patched.
//
// One rule matters more than the rest: CALL the radar functions, never touch
// CRadar::ms_RadarTrace directly. GTA SA raises the blip limit from the
// stock 175 to 3000 through fastman92's limit adjuster, and the way that works
// is by allocating a bigger array somewhere else and rewriting every reference
// to it. The functions have been patched to use the new array; the old address
// at 0xBA86F0 still exists and is now a lie. Reading it would appear to work
// and would corrupt memory under the adjuster.
#pragma once

#include <cstdint>

namespace game {

// The vector the game passes around. Laid out to match, because we hand these
// straight to a game function by value.
struct Vector {
    float x, y, z;
};

// CRadar::SetCoordBlip's first argument. We only ever use BLIP_COORD - a plain
// marker at a position, which is what a shop or an empire site is.
enum BlipType : int {
    BLIP_NONE = 0,
    BLIP_CAR = 1,
    BLIP_CHAR = 2,
    BLIP_OBJECT = 3,
    BLIP_COORD = 4,
    BLIP_CONTACTPOINT = 5,
    BLIP_SPOTLIGHT = 6,
    BLIP_PICKUP = 7,
    BLIP_AIRSTRIP = 8,
};

// Whether a blip shows on the radar, as a ground marker, both or neither.
// Businesses want BLIP_ONLY: a marker column standing in the street outside
// every shop in the state would be absurd.
enum BlipDisplay : int {
    BLIP_DISPLAY_NEITHER = 0,
    BLIP_DISPLAY_MARKER_ONLY = 1,
    BLIP_DISPLAY_BLIP_ONLY = 2,
    BLIP_DISPLAY_BOTH = 3,
};

// True once we have confirmed the game is the build these addresses belong to.
// Nothing in here does anything until it is.
bool Init();

// Which build we found, for the log and for the version we report to the
// server. Empty until Init() has run.
const char* VersionName();

// Plants a blip and returns its handle, or 0 if the game's blip table is full.
// The handle packs an index and a generation counter, so it is not an array
// index and must not be treated as one.
//
// `longRange` picks which of the game's two functions does it, and the
// difference is the whole point of this plugin:
//
//   short range  on the radar only when you are near it, on the full map
//                always. What San Andreas uses for shops - open the map and
//                every Binco in the state is there, but your radar stays
//                readable while you drive.
//   long range   on the radar from anywhere, clamped to the rim when it is
//                too far to draw properly. Right for a handful of things,
//                ruinous for four hundred.
//
// Short range is the default for everything, because "the radar shows what is
// nearby and the map shows all of it" is the behaviour we are after.
int SetCoordBlip(BlipType type, Vector at, uint32_t colour, BlipDisplay display,
                 bool longRange = false);

// CRadar::SetBlipSprite - gives a blip its picture. Sprite numbers come from
// the server, and Eagle's own table runs to 130 where San Andreas stopped at
// 63; see data/gtasa_radarBlipSpriteFilenames.dat in the game folder.
void SetBlipSprite(int blip, int sprite);

// CRadar::ChangeBlipScale - blip size in radar units. The game uses 1 for the
// small dots and 2 for most things worth looking at.
void ChangeBlipScale(int blip, int size);

// CRadar::ClearBlip - takes one away again.
void ClearBlip(int blip);

// Is the player looking at the full map right now?
//
// This is the difference between the two things we have been asked for at once:
// the radar should only show what is nearby, and the map should show everything
// in every city. A blip cannot do both - the game has one flag for it, and a
// short range blip is culled by distance on the map as well as on the radar,
// which is why most of Los Santos was missing.
//
// So the answer is to stop it being one choice. Blips live as short range, and
// while the map is open they are long range instead.
bool MapIsOpen();

// Any menu page, not just the map. Used to hold off the blip range switch until
// the player actually leaves the menu.
bool MenuIsOpen();

// Paint the text queued so far.
//
// CFont::PrintString only adds to a batch; nothing appears until this runs. The
// menu flushes its own text before we get control, so anything we queue after
// that is ours to flush. Forgetting it is why the first panels came out blank.
void FlushText();

// Install a callback to run once per frame, on the game's own thread.
//
// This is the only safe place to touch the radar. Everything else we do -
// reading the socket, parsing what the server sent - happens on our own thread
// and leaves work in a queue for this to pick up.
using FrameFn = void (*)();
bool HookFrame(FrameFn before, FrameFn after);

// Install a callback that runs after the menu has drawn itself, so we can paint
// on top of the map. Same thread, same rules as the frame hook.
bool HookMenuDraw(FrameFn fn);

// ---------------------------------------------------------------------------
// Drawing. All of it only makes sense from inside the menu-draw callback.
// ---------------------------------------------------------------------------

struct Point {
    float x, y;
};

// Convert a world position into the pause map's unrotated radar coordinate.
// Calling CRadar's ordinary transform outside the draw phase is wrong because
// it uses the driving radar's cached heading. This reads the live origin and
// Fastman-patched map range but deliberately applies no rotation.
Point WorldToMapRadar(float worldX, float worldY);

// Where a world position lands on screen, using the game's own two-step radar
// transform. Going through the game rather than working out the map's maths
// ourselves means our idea of where a blip is can never drift from where the
// game actually painted it - which is the whole point when the job is deciding
// what the cursor is pointing at.
Point WorldToScreen(float worldX, float worldY);

// Where the map's crosshair is pointing, in WORLD coordinates.
//
// Not a screen position, despite living next to the menu's other mouse fields.
// The map tracks its cursor in game space, which is why a reading of it looks
// like "2467, -1664" on a 2560x1440 screen - that is a street in Los Santos,
// not a pixel.
//
// This is the whole reason the hover panel never found anything: it was being
// compared against screen positions worked out from the radar transform, and
// the two were never going to meet. Nothing needs transforming at all - the
// cursor and the markers are already in the same space.
Point MapCursor();

// The current pause-map wheel direction after CPad::UpdatePads: +1 zooms in,
// -1 zooms out, and 0 means no wheel input this frame. Reading the input itself
// is essential at GTA's native 300/1100 clamps, where the resulting zoom delta
// becomes zero even though the player is still turning the wheel.
int MapZoomWheel();

// True while the physical left mouse button is held. The map module uses the
// state after CPad::UpdatePads, then replaces only GTA's abrupt camera delta;
// menu clicks and marker selection still pass through the native frontend.
bool MapLeftHeld();

// Take the pause-map wheel and final origin clamp away from the stock frontend.
// GTA SA scales the native wheel jump to 224 and can transiently drive
// the 300 overview down to 76; ProperRadar observes that invalid intermediate
// view and corrupts/flickers its tile LOD. The mapzoom module owns both pieces
// after this succeeds. Exact instruction signatures are checked before patching.
bool InstallMapControlPatch();

// Replace ProperRadar's thousands-of-tiles overview path with one pre-composed
// texture at distant zoom levels. Its 96x96 source atlas is sound, but the
// runtime full-map hook produces flickering black columns when nearly all 9216
// tiles are visible. The ordinary detailed renderer remains in use up close.
bool InstallMapOverviewPatch();

// Called once before the game's map draw so the overview replacement knows it
// may issue its single draw again. Individual section calls after that are
// deliberately suppressed for the rest of the frame.
void BeginMapFrame();

// The mouse in actual screen pixels, for putting a panel next to it.
Point MousePos();

// Where the map is scrolled and zoomed to. The pause map has its own view,
// separate from the radar's, and these are what describe it.
struct MapView {
    float zoom, baseX, baseY;
};
MapView Map();

// Move the complete map view. Zoom and origin have to change together: changing
// only zoom makes the map scale around GTA's fixed screen centre, while changing
// the origin by the matching amount keeps the world point under the cursor put.
// See client/valkyrie-asi-suite/src/mapzoom.cpp.
void SetMapView(MapView view);

// The back buffer size, for keeping panels on screen.
Point ScreenSize();

// How much bigger this screen is than the space the game's interface was drawn
// for. Multiply anything measured in pixels by this so a panel is the same size
// on a 4K monitor as on a small one.
float UiScale();

// The spacing to use between lines of text, already scaled. Ask rather than
// assume - guessing this is what turned the first legend into a black smear.
float LineHeight();

// A flat coloured rectangle. Corners are screen pixels.
void DrawRect(float left, float top, float right, float bottom, uint32_t argb);

// One line of text at a screen position. Colour is ARGB.
void PrintText(float x, float y, const char* text, uint32_t argb, float scale = 1.0f);

// How wide that text would be, for sizing a panel around it.
float TextWidth(const char* text, float scale = 1.0f);

}  // namespace game
