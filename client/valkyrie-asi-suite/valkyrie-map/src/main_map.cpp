// GTA SA pause-map control. This component intentionally has no socket,
// SA-MP, or server dependency: loading GTA directly is a supported path.
#include <windows.h>

#include "game.h"
#include "log.h"
#include "mapzoom.h"
#include "switches.h"
#include "version.h"

namespace {

void BeforeFrame() {
    game::BeginMapFrame();
    mapzoom::BeforeFrame();
}

void AfterFrame() {
    mapzoom::AfterFrame();
}

DWORD WINAPI Start(LPVOID) {
    logfile::Open("sprp-map.log", "SP-RP map");
    logfile::Line("sprp-map %s (network-free; single-player supported)",
                  SPRP_SUITE_VERSION);
    switches::ReadMap();

    if (!game::Init()) {
        logfile::Line("map: unsupported executable - standing down");
        return 0;
    }

    Sleep(5000);
    if (!game::HookFrame(&BeforeFrame, &AfterFrame)) {
        logfile::Line("map: frame hook unavailable - nothing patched");
        return 0;
    }
    if (!mapzoom::Install()) {
        logfile::Line("map: custom controls unavailable");
    }
    if (!game::InstallMapOverviewPatch()) {
        logfile::Line("map: composed overview unavailable; detailed renderer retained");
    }
    return 0;
}

}  // namespace

extern "C" BOOL APIENTRY DllMain(HMODULE self, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(self);
        if (HANDLE thread = CreateThread(nullptr, 0, &Start, nullptr, 0, nullptr)) {
            CloseHandle(thread);
        }
    }
    return TRUE;
}
