#include "mapzoom.h"

#include <cmath>

#include "game.h"
#include "log.h"
#include "switches.h"

namespace mapzoom {
namespace {

constexpr float kWheelScale = 1.30f;
constexpr float kEase = 0.22f;
constexpr float kSettled = 0.05f;
constexpr float kBoundaryEpsilon = 0.10f;

// Stock GTA San Andreas pause-map zoom limits.
constexpr float kMinZoom = 300.0f;
constexpr float kMaxZoom = 1100.0f;

constexpr game::Point kMapScreenCenter = {320.0f, 224.0f};
constexpr float kMapFrameLeft = 60.0f;
constexpr float kMapFrameTop = 60.0f;
constexpr float kMapFrameRight = 580.0f;
constexpr float kMapFrameBottom = 388.0f;
constexpr float kComposedOverviewMaxZoom = 650.0f;
constexpr float kOverviewHorizontalSlack = 0.0f;

// Edge-hover pan is in map reference pixels per frame.
constexpr float kEdgeMarginUi = 28.0f;
constexpr float kEdgePanMax = 4.5f;
constexpr float kClickPanMax = kEdgePanMax * 2.0f;
constexpr float kPanEase = 0.14f;
constexpr float kPanStop = 0.01f;

bool g_installed = false;
bool g_active = false;
bool g_beforeValid = false;
bool g_anchorValid = false;
bool g_logged = false;
float g_targetZoom = kMinZoom;
float g_overviewTransitionStart = kMinZoom;
game::MapView g_before{};
game::Point g_anchorRadar{};
game::Point g_anchorScreen{};
game::Point g_panVelocity{};

float Clamp(float value, float low, float high) {
    if (value < low) return low;
    if (value > high) return high;
    return value;
}

bool Finite(game::Point point) {
    return std::isfinite(point.x) && std::isfinite(point.y);
}

bool Sane(game::MapView view) {
    return std::isfinite(view.zoom) && view.zoom > 0.0f &&
           std::isfinite(view.baseX) && std::isfinite(view.baseY);
}

bool Different(game::MapView a, game::MapView b) {
    return std::fabs(a.zoom - b.zoom) > 0.001f ||
           std::fabs(a.baseX - b.baseX) > 0.001f ||
           std::fabs(a.baseY - b.baseY) > 0.001f;
}

game::Point Project(game::MapView view, game::Point radar) {
    return {view.baseX + view.zoom * radar.x,
            view.baseY - view.zoom * radar.y};
}

game::MapView KeepRadarTextureUnderFrame(game::MapView view) {
    // Radar coordinates cover -1..+1, so their screen extent is
    // base-zoom..base+zoom. ProperRadar draws beyond that domain as black.
    // The composed overview has the same blue ocean as the menu around its
    // edges and is issued as one safe draw. At the 300-unit floor the complete
    // texture is narrower than the menu frame, so the old "texture must cover
    // every pixel" constraint physically cannot coexist with centring the
    // asymmetric continent. Give that renderer a small horizontal gutter;
    // detailed ProperRadar tiles keep the strict bounds that prevent black
    // out-of-atlas reads.
    const float overviewSlack = view.zoom <= kComposedOverviewMaxZoom
                                    ? kOverviewHorizontalSlack
                                    : 0.0f;
    const float minBaseX = kMapFrameRight - view.zoom - overviewSlack;
    const float maxBaseX = kMapFrameLeft + view.zoom + overviewSlack;
    const float minBaseY = kMapFrameBottom - view.zoom;
    const float maxBaseY = kMapFrameTop + view.zoom;

    if (minBaseX <= maxBaseX) {
        view.baseX = Clamp(view.baseX, minBaseX, maxBaseX);
    }
    if (minBaseY <= maxBaseY) {
        view.baseY = Clamp(view.baseY, minBaseY, maxBaseY);
    }
    return view;
}

game::Point ContinentRadar() {
    return game::WorldToMapRadar(0.0f, 0.0f);
}

game::MapView AroundAnchor(float zoom) {
    return KeepRadarTextureUnderFrame(
        {zoom,
         g_anchorScreen.x - zoom * g_anchorRadar.x,
         g_anchorScreen.y + zoom * g_anchorRadar.y});
}

game::MapView ContinentView(float zoom, game::MapView fallback) {
    const game::Point radar = ContinentRadar();
    if (!Finite(radar)) {
        return KeepRadarTextureUnderFrame(
            {zoom, fallback.baseX, fallback.baseY});
    }
    return KeepRadarTextureUnderFrame(
        {zoom,
         kMapScreenCenter.x - zoom * radar.x,
         kMapScreenCenter.y + zoom * radar.y});
}

game::MapView ApplyOverviewFit(game::MapView anchored,
                               game::MapView fallback) {
    if (g_targetZoom > kMinZoom + kBoundaryEpsilon) {
        return anchored;
    }

    // Modern maps preserve the cursor anchor through ordinary wheel input.
    // Only the final wheel step has an extra constraint: while the last
    // animation approaches the minimum zoom, smoothly fit the complete
    // continent instead of snapping to it after the zoom has finished.
    const float span = g_overviewTransitionStart - kMinZoom;
    float t = span > kBoundaryEpsilon
                  ? (g_overviewTransitionStart - anchored.zoom) / span
                  : 1.0f;
    t = Clamp(t, 0.0f, 1.0f);
    t = t * t * (3.0f - 2.0f * t);  // smoothstep

    const game::MapView fitted = ContinentView(anchored.zoom, fallback);
    anchored.baseX += (fitted.baseX - anchored.baseX) * t;
    anchored.baseY += (fitted.baseY - anchored.baseY) * t;
    return KeepRadarTextureUnderFrame(anchored);
}

void Reset() {
    g_active = false;
    g_beforeValid = false;
    g_anchorValid = false;
    g_panVelocity = {};
}

void Activate(game::MapView view) {
    g_active = true;
    g_targetZoom = Clamp(view.zoom, kMinZoom, kMaxZoom);
    g_anchorValid = false;
    g_panVelocity = {};
    g_overviewTransitionStart = kMinZoom;

    if (!g_logged) {
        logfile::Line(
            "map control: cursor-anchored smooth zoom, final overview fit, edge-hover pan, range %.1f..%.1f",
            kMinZoom, kMaxZoom);
        g_logged = true;
    }
}

void CaptureCursorAnchor(game::MapView view) {
    const game::Point cursor = game::MapCursor();
    const game::Point radar = game::WorldToMapRadar(cursor.x, cursor.y);
    const game::Point screen = Project(view, radar);
    if (Finite(cursor) && Finite(radar) && Finite(screen)) {
        g_anchorRadar = radar;
        g_anchorScreen = screen;
        g_anchorValid = true;
    }
}

float EdgeStrength(float coordinate, float size, float margin, int& direction) {
    direction = 0;
    if (coordinate < margin) {
        direction = 1;
        const float linear = Clamp((margin - coordinate) / margin, 0.0f, 1.0f);
        return linear * linear;
    }
    if (coordinate > size - margin) {
        direction = -1;
        const float linear = Clamp((coordinate - (size - margin)) / margin,
                                   0.0f, 1.0f);
        return linear * linear;
    }
    return 0.0f;
}

float ClickStrength(float coordinate, float size, int& direction);

void ApplyPan(game::MapView& view, bool allowed, bool clickHeld) {
    game::Point desired{};

    if (allowed) {
        const game::Point screen = game::ScreenSize();
        const game::Point mouse = game::MousePos();
        if (Finite(screen) && Finite(mouse) && screen.x > 0.0f && screen.y > 0.0f) {
            int xDirection = 0;
            int yDirection = 0;
            float xStrength = 0.0f;
            float yStrength = 0.0f;
            float maximum = kEdgePanMax;
            if (clickHeld) {
                xStrength = ClickStrength(mouse.x, screen.x, xDirection);
                yStrength = ClickStrength(mouse.y, screen.y, yDirection);
                maximum = kClickPanMax;
            } else {
                const float ui = game::UiScale();
                const float smaller = screen.x < screen.y ? screen.x : screen.y;
                const float margin = Clamp(kEdgeMarginUi * ui, 24.0f,
                                           smaller * 0.15f);
                xStrength = EdgeStrength(mouse.x, screen.x, margin, xDirection);
                yStrength = EdgeStrength(mouse.y, screen.y, margin, yDirection);
            }
            desired.x = static_cast<float>(xDirection) * xStrength * maximum;
            desired.y = static_cast<float>(yDirection) * yStrength * maximum;
        }
    }

    g_panVelocity.x += (desired.x - g_panVelocity.x) * kPanEase;
    g_panVelocity.y += (desired.y - g_panVelocity.y) * kPanEase;
    if (std::fabs(g_panVelocity.x) < kPanStop && desired.x == 0.0f) {
        g_panVelocity.x = 0.0f;
    }
    if (std::fabs(g_panVelocity.y) < kPanStop && desired.y == 0.0f) {
        g_panVelocity.y = 0.0f;
    }

    if (g_panVelocity.x == 0.0f && g_panVelocity.y == 0.0f) {
        return;
    }

    const game::MapView beforePan = view;
    view.baseX += g_panVelocity.x;
    view.baseY += g_panVelocity.y;
    view = KeepRadarTextureUnderFrame(view);

    if (g_anchorValid) {
        g_anchorScreen.x += view.baseX - beforePan.baseX;
        g_anchorScreen.y += view.baseY - beforePan.baseY;
    }
}

float ClickStrength(float coordinate, float size, int& direction) {
    direction = 0;
    if (size <= 0.0f) {
        return 0.0f;
    }

    // LMB behaves like a virtual stick centred on the map. A small dead zone
    // makes clicking a marker stable; farther from centre progressively ramps
    // to twice edge-hover's speed instead of applying GTA's one-frame jump.
    const float centre = size * 0.5f;
    const float deadZone = Clamp(size * 0.04f, 18.0f, 42.0f);
    const float distance = coordinate - centre;
    const float magnitude = std::fabs(distance);
    if (magnitude <= deadZone || centre <= deadZone) {
        return 0.0f;
    }

    direction = distance < 0.0f ? 1 : -1;
    const float linear = Clamp((magnitude - deadZone) / (centre - deadZone),
                               0.0f, 1.0f);
    return linear * linear;
}

}  // namespace

bool Install() {
    if (switches::ZoomOff()) {
        logfile::Line("map control: off by sprp-nozoom.off");
        return false;
    }
    g_installed = game::InstallMapControlPatch();
    if (!g_installed) {
        logfile::Line("map control: native patch failed - leaving the map untouched");
    }
    return g_installed;
}

void BeforeFrame() {
    g_beforeValid = false;
    if (!g_installed || switches::ZoomOff() || !game::MapIsOpen()) {
        Reset();
        return;
    }

    const game::MapView original = game::Map();
    if (!Sane(original)) {
        Reset();
        return;
    }
    if (!g_active) {
        Activate(original);
    }

    game::MapView next = original;
    const float current = Clamp(original.zoom, kMinZoom, kMaxZoom);
    const bool smoothing = std::fabs(g_targetZoom - current) > kSettled;

    if (smoothing) {
        float zoom = current + (g_targetZoom - current) * kEase;
        if (std::fabs(g_targetZoom - zoom) <= kSettled) {
            zoom = g_targetZoom;
        }
        zoom = Clamp(zoom, kMinZoom, kMaxZoom);

        if (!g_anchorValid) {
            CaptureCursorAnchor(original);
        }
        next = g_anchorValid
                   ? AroundAnchor(zoom)
                   : KeepRadarTextureUnderFrame(
                         {zoom, original.baseX, original.baseY});
        next = ApplyOverviewFit(next, original);
    } else if (current <= kMinZoom + kBoundaryEpsilon) {
        next = ContinentView(kMinZoom, original);
    } else {
        next.zoom = current;
        next = KeepRadarTextureUnderFrame(next);
    }

    if (Different(original, next)) {
        game::SetMapView(next);
    }
    g_before = next;
    g_beforeValid = true;
}

void AfterFrame() {
    if (!g_installed || switches::ZoomOff() || !game::MapIsOpen()) {
        Reset();
        return;
    }

    const game::MapView after = game::Map();
    if (!Sane(after)) {
        Reset();
        return;
    }
    if (!g_active) {
        Activate(after);
    }

    const int wheel = game::MapZoomWheel();
    if (wheel != 0) {
        const float previousTarget = g_targetZoom;
        g_targetZoom = Clamp(
            wheel > 0 ? previousTarget * kWheelScale
                      : previousTarget / kWheelScale,
            kMinZoom, kMaxZoom);

        // Wheel zoom in both directions keeps the same world point beneath
        // the cursor, matching contemporary map controls. Re-capture it for
        // every wheel event so a user can move the mouse during the animation.
        CaptureCursorAnchor(after);

        if (wheel < 0 &&
            previousTarget > kMinZoom + kBoundaryEpsilon &&
            g_targetZoom <= kMinZoom + kBoundaryEpsilon) {
            g_overviewTransitionStart =
                after.zoom > kMinZoom ? after.zoom : previousTarget;
        } else if (wheel > 0) {
            g_overviewTransitionStart = kMinZoom;
        }

        logfile::Line("map zoom input: %s, view %.3f, target %.3f",
                      wheel > 0 ? "wheel in" : "wheel out",
                      after.zoom, g_targetZoom);
    } else if (g_beforeValid &&
               std::fabs(after.zoom - g_before.zoom) > kSettled) {
        // PgUp/PgDn remain native. Adopt their result rather than fighting it.
        g_targetZoom = Clamp(after.zoom, kMinZoom, kMaxZoom);
        g_anchorValid = false;
    }

    game::MapView finalView = after;
    const bool leftHeld = game::MapLeftHeld();
    const bool settled = std::fabs(g_targetZoom - after.zoom) <= kSettled;
    const bool panAllowed = settled &&
                            after.zoom > kMinZoom + kBoundaryEpsilon;

    if (leftHeld && g_beforeValid) {
        // GTA has already handled LMB at this point. Preserve everything else
        // it did (including click/target behaviour), but discard its abrupt
        // camera delta before the frontend draws, then apply our eased delta.
        finalView.baseX = g_before.baseX;
        finalView.baseY = g_before.baseY;
    }
    if (!panAllowed) {
        g_panVelocity = {};
    }
    ApplyPan(finalView, panAllowed, leftHeld);

    // Keyboard/controller panning remains native. Every path is bounded before
    // ProperRadar sees it, preventing out-of-atlas black columns.
    finalView = KeepRadarTextureUnderFrame(finalView);
    if (Different(after, finalView)) {
        game::SetMapView(finalView);
    }
}

}  // namespace mapzoom
