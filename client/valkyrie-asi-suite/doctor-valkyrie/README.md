# Valkyrie Doctor & Crashfix

One x86 ASI for classic GTA San Andreas PC 1.0: `doctor-valkyrie.asi`.
Build from the suite with `./build.ps1 -OnlyTarget doctor-valkyrie -Release`.
The Crashfix build entry point redirects to this same combined output.

Close GTA, back up existing Doctor and standalone Crashfix ASIs outside the
game folder, then use one combined ASI. Do not keep a standalone Crashfix
active alongside it. Reports go to `Valkyrie_crashes`. The diagnostic window
contains text, diagnosis, full report, copy and open controls; no artwork.

Native guards verify entry/continuation bytes and skip unsupported or already
modified sites. Check `Valkyrie Crashfix.log` for installed/skipped guards.
The GTA guards have no CLEO, audio-library or client-core dependency.
See COMBINED-LICENSE.md for distribution terms. In-game validation is pending.
