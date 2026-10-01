# SP-RP Public Research

GTA SDK: initialize `third_party/plugin-sdk` with `git submodule update --init --recursive`. Read docs/PLUGIN_SDK.md for its source map, pinned version and upstream setup. Existing released mod recipes do not require it.

Read docs/AGENT_START.md first: it contains the project map, build commands, archive-reading workflow, known gaps and scope. Then read CONTRIBUTING.md and the relevant component's README. This is a public research/mod repository, not the SP-RP server.

Build entry point: `./build.ps1 -CheckEnvironment`, then `./build.ps1 -Target doctor -Release` (or map, crashfix, repair, all). Setup and outputs are in docs/BUILDING.md. These use the installed MSVC x86 toolchain; the repository includes build recipes, not Microsoft's compiler. No server or game install is needed to compile.

Research entry point: docs/reverse-engineering/generated/index.json → target metadata.json → functions/symbols/named CSV indexes → bounded excerpts of decompiled.c/disassembly.txt. Do not read the whole archive into context. `python tools/check_public.py` includes the archive-integrity check. Keep observed facts separate from decompiler inference and historical notes.

Valkyrie Radar is unreleased and private. Do not export its implementation, renderer, routing component, tile pipeline or project-specific research notes. Shared Map code must not reintroduce private Radar additions; the public Map currently uses the earlier 0.2.0 baseline.

Full generated decompilation/disassembly and reconstructed pseudocode are intentionally public under docs/reverse-engineering/. Preserve target hashes, metadata and archive checksums. Do not treat the old private-only export rule as current policy. Keep private gamemode code, player data, production configuration and history out. Never copy a private repository wholesale. Use exact-version evidence for game addresses and signatures. Preserve upstream credits and directory-specific licenses. Distinguish archived observations from current verified behavior. Build and run relevant existing tests for changes; never install a mod or deploy to a server merely to validate a contribution.

## Commits, pushes and publishing

Inspect origin, branch and working-tree changes first. Use a task branch from
current main (or the existing contribution branch); stage explicit paths, inspect
`git diff --cached` and run `git diff --check`. Run `python tools/check_public.py`
and applicable builds/tests described above, then commit, push the branch and
open a PR. Preserve unrelated edits and the independent public Git history.
Never merge or mirror private repository history into this repository.

Pushing starts .github/workflows/checks.yml; it does not deploy sp-rp.com, install
mods or publish website downloads. A GitHub release, a website download and a
source merge are separate outcomes. Website publication is handled by its owning
repository and release process; report only actions actually completed.

For maintainer imports, accept only an intentionally reviewed public snapshot.
Keep existing public scope and licenses, review all added/removed files, and run
this checkout's current checks. A passing credential/path check alone is not
proof that newly added implementation was approved for public release.
For the GTA SA refresh, use docs/GTA-SA-MOD-WORKFLOW.md. Doctor and Crashfix now build into one ASI. Former partner editions and product profiles are retired; preserve historical research and license provenance.
