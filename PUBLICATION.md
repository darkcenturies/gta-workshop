# Public release boundary

This repository keeps its existing published scope: Doctor, Crashfix, Repair,
the earlier public Map baseline, and the existing interoperability research.
Moving private development into a different repository does not broaden this scope.

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
