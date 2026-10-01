# GTA San Andreas update for review

> Historical implementation record. Authored code/build recipes are now private
> in Valkyrie Workshop; generated findings and evidence remain public. Paths and
> commands below describe the preserved historical source, not this public tree.


The current public and private mod line targets classic GTA San Andreas PC 1.0.
Edition-specific integrations, branding, HUD/Lua patches, radio hooks, contacts,
presets and mission content patches have been retired. Historical research and
mandatory upstream license/attribution records remain unchanged.

Doctor and Crashfix build as one `doctor-valkyrie.asi`, with native crash guards,
crash reports and the attributed general CrashInfo lists. There are no bitmap or
icon resources in that ASI. Repair bundles it and preserves reversible updates
and retirement of old standalone copies. Other original artwork remains.
The combined distribution uses GPL-3.0, retaining Doctor's BSD notices.

Map now centers on stock San Andreas and uses stock zoom limits.

Dryxio CLEO AI is pinned in GTA-SA-MOD-WORKFLOW.md. Its reference sync, strict
workspace validation and ten upstream unit tests passed. These repositories
currently contain no actual CLEO script sources; native ASIs use MSVC tests.
Release x86 builds, native installer/guard tests, Repair tests, preset and
packager checks passed. Public archive/boundary checks passed. In-game startup,
save loading, device resets and gameplay compatibility await owner testing;
no game installation or production publication was performed for validation.
