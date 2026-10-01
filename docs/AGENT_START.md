# Agent start: SP-RP Public Research

GTA development SDK: start with [PLUGIN_SDK.md](PLUGIN_SDK.md), initialize `third_party/plugin-sdk`, then search its San Andreas classes and examples alongside the exact-target research below.

This page is the handoff context for an agent with no prior conversations. Read it with the root AGENTS.md, then open only the source and research relevant to the task.

## What this repository is

A public collection of released mod source, independently written tools, GTA/SA-MP/S&SMP interoperability findings and completed decompilation exports. It is not a runnable SP-RP server or a copy of its private gamemode. Contribution flow is branch → pull request → checks/review → merge. Nothing here deploys to the live server.

GTA SA is the base game. SA-MP is its multiplayer platform. S&SMP is a separate compatibility target, and PECore is Project Eagle's client core. Do not assume their addresses, packet layouts or version numbering are interchangeable. Use input SHA-256, not just a package name.

## First actions

For any GTA task, first use [the workshop map](GTA-WORKSHOP.md) and
[Dryxio catalog](../research/dryxio-catalog.md). Select public/private visibility
and the authoritative source owner, including SRG, Upstate and rendering tasks,
before opening an issue or writing implementation. Existing public mod and
archive work then follows the steps below.

1. Read the request and `git status --short`; preserve unrelated work.
2. Use the source map below to choose a component and read its local README/notices.
3. For an ASI task, read [BUILDING.md](BUILDING.md), run `./build.ps1 -CheckEnvironment`, then build only the affected target. Use `-Release` for release validation.
4. For a research task, read the archive index and target metadata, then search function/symbol indexes before loading large decompilation files.
5. State the evidence, make the scoped change and run relevant checks. Report what was built/tested and what still needs real-game validation.

## Source map

| Task | Start here | What it contains |
| --- | --- | --- |
| Build an ASI | root `build.ps1`, [BUILDING.md](BUILDING.md) | Public build entry point and compiler setup |
| Map controls | `client/valkyrie-asi-suite/src/main_map.cpp`, `mapzoom.cpp`, `game.cpp` | Network-free pause-map hooks and controls; earlier 0.2.0 baseline |
| Doctor diagnosis | `client/valkyrie-asi-suite/src/main_doctor.cpp`, `doctor.cpp`, `doctorlist.cpp` | Doctor 0.3.2 entry point, evidence classification and rules |
| Doctor UI/resources | `crashwindow.cpp`, `reportpaths.cpp`, `doctor-valkyrie.rc` in the same source folder | Diagnostic window, reports and embedded resources |
| Crash guards | `client/valkyrie-asi-suite/valkyrie-crashfix/src/ValkyrieCrashfix.cpp`, `SafePatch.inc`, `tests/` | Crashfix 2.3.0-test and native/machine-code tests; GPL-3.0 |
| Repair application | `client/valkyrie-asi-suite/valkyrie-repair/src/Engine.cs`, `MainForm.cs`, `SelfTests.cs` | Repair 1.2 scanning, user-approved repairs, undo and isolated tests |
| Protocol facts | [S&SMP protocol](../research/ssmp-protocol.md), [pseudocode](reverse-engineering/ssmp-server-1.3.1-patch1.pseudo.cpp) | Recorded E7/D8/E9 and join layouts; not a complete server implementation |
| Game/client internals | [archive inventory](reverse-engineering/README.md) | Four complete generated target exports and coverage |
| Population research | [ped population](reverse-engineering/PECORE-PED-POPULATION.md) | Recorded observations, methods and unresolved meanings |
| Research reproduction | [REPRODUCING.md](reverse-engineering/REPRODUCING.md), `deploy/ghidra_scripts/ExportDecompiled.py` | Explicit local inputs, hashes and Ghidra export recipe |
| Outside references | [upstream catalog](../research/upstreams.md) | Recorded upstream revisions and their separate terms |
| Research workflow improvements | [Dryxio review](../research/dryxio-workflow.md), [practical workflow](RESEARCH_WORKFLOW.md) | Pinned external tool references, documented limits and proposed evaluation tasks |

Source filenames above that omit a directory are relative to the directory named in
that row. For output paths and product versions use [MODS.md](MODS.md) and
BUILDING.md, not assumptions based on the folder name `map-suite`.

## Reading the archive efficiently

`docs/reverse-engineering/generated/index.json` identifies completed targets:

| Target | Recovered / internal functions | Failure count |
| --- | ---: | ---: |
| ssmp-server-1.3.1-patch1 | 1,121 / 1,121 | 0 |
| ssmp-client-1.3.1-patch1 | 2,364 / 2,364 | 0 |
| project-eagle-core-current | 7,617 / 7,617 | 0 |
| gta-sa-1.0-us | 20,820 / 20,823 | 3 |
| gta-sa-ps2-1.00-de | 8,533 / 8,533 | 0 |
| gta-sa-ps2-2.01-eu | 8,523 / 8,523 | 0 |

Each directory has metadata.json, functions.csv, symbols.csv, strings.csv, calls.csv, decompiled.c and disassembly.txt. GTA also has named.csv. Read the CSV headers rather than guessing their columns. For example, `rg -n -i 'population' docs/reverse-engineering/generated/gta-sa-1.0-us/named.csv` finds candidate names; use the returned address to locate bounded passages in decompiled.c/disassembly.txt. Do not dump the entire 162 MB archive into context.

Input hashes live in metadata/index files. `docs/reverse-engineering/checksums.json` instead checksums the exported files. `python tools/check_research.py` verifies all 45 archive/pseudocode files and metadata consistency. Do not casually rewrite line endings or regenerate archives while fixing a mod.

## Evidence and limitations

- Distinguish executable observations, inferred type/field meanings, historical notes and current source behavior. A plausible decompiler type is not proof.
- Completed decompilation is not original authored vendor source or full semantic understanding. Never compile decompiled.c as if it were a plugin project.
- The dated August checkpoint is historical. The completed target index supersedes its paused status and older claims that PECore had no decompilation.
- The launcher, memory cleaner and extra RPC entries in research/targets.json have no completed export here. Do not report them complete.
- Map's public source is 0.2.0, not an exact reconstruction of the later 0.2.1 download. Winmode Nullfix source has not been located. Repair embeds older shipped payloads as documented in MODS.md.
- Archive and build checks need no game install. In-game compatibility, user-interface behavior and target-specific hooks require separate runtime evidence.

## Public boundary and licenses

Valkyrie Radar is unreleased and private, including its code, shared additions, routing/tile tools and project notes. Do not import it to fill perceived gaps. The private gamemode, player data, production configuration, credentials, input executables and private Git history remain outside this repository.

Original SP-RP contributions use BSD-3-Clause; preserve attribution. Crashfix keeps GPL-3.0. Third-party resources and vendor-derived research are not automatically BSD licensed. Check [THIRD_PARTY_NOTICES.md](../THIRD_PARTY_NOTICES.md) and the component before private-server reuse. Public acceptance does not authorize deployment; [INTEGRATION.md](INTEGRATION.md) describes that separate workflow.

When handing off, include the task, changed paths, exact target/version, evidence, commands/results and remaining questions. Put reusable findings in a document or finding record, so the next agent does not depend on private chat history.
