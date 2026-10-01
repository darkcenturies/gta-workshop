# Public release boundary

The public workshop catalog and guides now cover all our GTA work, including
SRG/GTA Midnight, Upstate, rendering and Launcher integration. Public-safe
descriptions and external reference links are permitted documentation. Listing
a private project is not approval to publish its implementation or history.
See docs/GTA-WORKSHOP.md for current visibility, owner and withheld reasons.

This repository keeps its existing published scope: Doctor, Crashfix, Repair,
the earlier public Map baseline, and the existing interoperability research.
The broader catalog does not broaden this implementation scope. Proposed generic
server/mod examples and future source releases require separate reviewed scope
and manifest changes; they are not automatically approved by this catalog.

Valkyrie 3D Radar and Fuel implementations, shared private additions, routing,
tile-generation pipelines, server gamemode, production configuration and player
data must not be imported. Public decompilation archives remain as previously
published, with their provenance and checksum checks.

`publication/approved-files.json` records the reviewed paths and normalized
SHA-256 values for implementation files. `tools/check_public.py` rejects new
paths and changed implementation until their release boundary is reviewed and
the manifest is intentionally updated. This protects shared `game.cpp` as well
as obvious private component directories. The manifest itself requires review;
it is not a replacement for GitHub branch protection.

Maintenance follows branch -> pull request -> boundary checks -> review.
Never merge private history or mirror a private source tree into this repository.

Public Phone has its own already-public, reviewed source/dependency scope.
That does not authorize importing its implementation wholesale here, or copying
private Radar routing/rendering and shared extensions beyond that approved scope.
