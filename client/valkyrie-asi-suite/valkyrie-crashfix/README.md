# Valkyrie Crashfix

Crashfix now ships inside `doctor-valkyrie.asi`, alongside Doctor's crash
reporter, for classic GTA San Andreas PC 1.0. Build with `src/build.ps1` or
the suite's `build.ps1 -OnlyTarget doctor-valkyrie -Release`.
Keep only the combined ASI active. See `../doctor-valkyrie/README.md` for
migration and `../doctor-valkyrie/COMBINED-LICENSE.md` for licensing.
Crashfix retains GPL-3.0 and its upstream credits. Existing native tests cover
patch rollback, competing patches, thread state, signature rejection and guards.
Real-game reproduction remains a separate release gate.
