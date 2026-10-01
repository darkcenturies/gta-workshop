# GTA Workshop

A public workshop maintained by **darkcenturies**, a solo developer, for GTA
mods, server development, research, world/asset tooling and contribution guides.
The public repository is [darkcenturies/gta-workshop](https://github.com/darkcenturies/gta-workshop), with its existing public source/history preserved.

Start with [the complete GTA project catalog and graph](docs/GTA-WORKSHOP.md).
The colored atlas has five detailed maps: ownership/return, complete task flow,
component dependencies, all Dryxio reference routes and publication gates.
Use the [36-entry component catalog](docs/workshop/CATALOG.md),
[publication backlog](docs/workshop/PUBLICATION-BACKLOG.md) and
[worked task routes](docs/workshop/EXAMPLES.md) alongside it.
It covers **SRG / GTA Midnight, SP-RP, Upstate/re3, Valkyrie mods, Phone,
GTA rendering/DLSS, Launcher integration, assets and supporting services**,
including projects whose implementation remains private.

[![Colored GTA ownership and findings-return map](docs/workshop/ownership.svg)](docs/GTA-WORKSHOP.md)

[The Dryxio catalog](research/dryxio-catalog.md) is required starting research:
task-specific tools, mods, forks, revisions, applicability and evaluation status.
Choose visibility before writing code or opening an issue. Public implementation
belongs in its approved public owner; private implementation starts directly in
its private owner. Cataloging a project does not publish its source.

See [repository ownership](docs/REPOSITORIES.md) for the separate phone,
Atmosphere/workshop and public Phone source homes.

The [GTA plugin-sdk guide](docs/PLUGIN_SDK.md) explains the pinned DK22Pac/plugin-sdk dependency, initialization and source layout. Clone with `--recurse-submodules` to include its source.

A community workshop for GTA: San Andreas, SA-MP and S&SMP interoperability research, reusable tools, and Valkyrie's released mods.

Everyone can propose improvements through a pull request. The repository owner reviews changes before merging. This repository has no connection or deployment credentials to the live SP-RP server.

Original SP-RP code is offered under [BSD-3-Clause](LICENSE), which permits use in private projects with the required notices. Third-party components retain their own licenses; the decompilation archive is not relicensed as SP-RP-owned code. See [credits and licensing](THIRD_PARTY_NOTICES.md).

## Start here

- **AI agents: read [AGENTS.md](AGENTS.md) and [the agent start guide](docs/AGENT_START.md) first.**
- [All GTA projects, visibility, owners and workflow](docs/GTA-WORKSHOP.md)
- [Dryxio tools, mods, forks and task routes](research/dryxio-catalog.md)
- [ASI builder and compiler setup](docs/BUILDING.md) — `./build.ps1 -CheckEnvironment`, then `./build.ps1 -Release`.
- [Mod source and build guide](docs/MODS.md)
- [Full decompilation archive and coverage](docs/reverse-engineering/README.md)
- [Research index and evidence standards](research/README.md)
- [Dryxio tool references, findings and evaluation backlog](research/dryxio-workflow.md)
- [From upstream research to verified Valkyrie improvements](docs/RESEARCH_WORKFLOW.md)
- [How to contribute](CONTRIBUTING.md)
- [How accepted changes reach a private server](docs/INTEGRATION.md)
- [Credits and licensing](THIRD_PARTY_NOTICES.md)

## Current GTA SA workflow

Read [GTA-SA-MOD-WORKFLOW.md](docs/GTA-SA-MOD-WORKFLOW.md). The native
mods target classic GTA SA; former partner editions and branded profiles are
retired. Doctor and Crashfix build into `doctor-valkyrie.asi`; `crashfix` is a
compatibility alias for that build. Corresponding source and combined license
notices accompany the binary. Other non-partner artwork is retained.

Dryxio CLEO AI validates actual CLEO scripts. This native C++/C# collection
has no CLEO scripts to validate, so its reference check does not establish
native hook correctness. Build and isolated tests remain separate from gameplay
verification. Historical decompilation archives retain their original targets.

## Included

| Project | Source |
| --- | --- |
| Valkyrie Map | [client/valkyrie-asi-suite](client/valkyrie-asi-suite) |
| Doctor & Crashfix: one artwork-free x86 ASI | [doctor-valkyrie](client/valkyrie-asi-suite/doctor-valkyrie), [GPL guard sources](client/valkyrie-asi-suite/valkyrie-crashfix) |
| Valkyrie Repair 1.2 | [client/valkyrie-asi-suite/valkyrie-repair](client/valkyrie-asi-suite/valkyrie-repair) |
| Binary-analysis and pedestrian-path research tools | [deploy](deploy) |

The mod folders contain development source snapshots; versions and build instructions are in the mod guide. The separate [decompilation archive](docs/reverse-engineering/README.md) contains the actual generated research output, with exact binary hashes, recovery counts and file checksums.

The public research collection includes full generated decompilation and disassembly for GTA SA 1.0 US, PECore, and S&SMP client/server, plus reconstructed pseudocode, symbols, strings, call maps and export tooling. The private gamemode, player databases, server configuration, credentials, game assets, executable inputs and private Git history remain excluded.

This is an unofficial community project, not affiliated with Rockstar Games, Take-Two, SA-MP, S&SMP or Project Eagle. Obtain game prerequisites separately.

Unreleased Valkyrie Radar work is private and is not included in this repository.

## Repository layout

Read this before moving files:

- [Public research repository structure](PUBLIC-RESEARCH-ORGANIZATION.md)
