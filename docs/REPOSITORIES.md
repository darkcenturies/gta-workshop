# Where Valkyrie work belongs

This repository is the main GTA workshop entry point. The broader
[project catalog and graph](GTA-WORKSHOP.md) routes SRG/GTA Midnight, Upstate,
GTA rendering, Launcher, server, mod and asset work to their owners and records
visibility separately. Read it before choosing where to implement a new task.

This repository owns the public Doctor, Crashfix, Repair, earlier Map and
interoperability research listed in [MODS.md](MODS.md). Its canonical checkout
is `C:\Users\Admin\sp-rp-public-research`.

The phone has its own public repository,
[darkcenturies/valkyrie-phone](https://github.com/darkcenturies/valkyrie-phone).
Phone fixes belong there, with shared-source changes reconciled into the
Valkyrie workshop integration repository. Atmosphere and unreleased mods remain
in that workshop; their presence in the phone or PSH does not expand this
repository's release scope.

Former partner adaptations are historical consumers, not current prerequisites.
The maintained mods target GTA SA and retire those compatibility bridges and
branded profiles. Preserve upstream credits and historical research evidence.

The workshop's old `public-release/` tree is historical staging material. Edit
this repository directly for public mods/research instead of maintaining two
copies. Keep existing licensing, publication checks and component boundaries.

Reusable integration lessons: register game hooks on the game thread, chain
other plugins' handlers, make intrusive control changes opt-in, restore owned
input/camera state on every exit, and validate complete package dependencies.
These are review guidelines here, not a claim that this repository's existing
binaries have been changed or newly verified in Silent Hill.
