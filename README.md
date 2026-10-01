# GTA Workshop

A public learning and research workshop for **darkcenturies' GTA projects**,
maintained by one developer. Find how a mod works, choose relevant references,
follow the implementation owner and return useful findings here.

**Start:** [Projects](#projects-and-implementation-owners) ·
[Mod-making](#how-to-make-or-improve-a-mod) · [Research](#public-research) ·
[Documentation](docs/README.md) · [Colored maps](docs/GTA-WORKSHOP.md)

## What belongs here

**Public:** mod-making guides, project catalogs, detailed workflow maps,
Dryxio/original upstream references, reproducible findings, target metadata,
checksums and generated decompilation/disassembly archives.

**Elsewhere:** mod implementations, authored analysis/export tools, experimental
adapter source, build recipes, release packages, game assets and private data.
This repository explains the work; its owners hold the implementation.
[Publication policy](PUBLICATION.md) defines the boundary.

## Projects and implementation owners

| Project/work | Implementation owner | Source visibility |
| --- | --- | --- |
| Doctor + Crashfix, Map and Repair | [Valkyrie Workshop](https://github.com/darkcenturies/valkyrie-workshop) | Private |
| Shared Core, Atmosphere, Fuel, Radar, trainer and mod/asset tools | Valkyrie Workshop | Private |
| Phone and its reviewed embedded dependencies | [valkyrie-phone](https://github.com/darkcenturies/valkyrie-phone) | Public, independent build |
| SRG / GTA Midnight conversion | [street-racing-girls](https://github.com/darkcenturies/street-racing-girls) | Private; shared Core comes from Workshop |
| Upstate/re3 port and compatibility patch | Valkyrie Workshop | Private; [novawish/re3](https://github.com/novawish/re3) is the separate public engine |
| SP-RP gamemode, accounts and server operations | [sp-rp](https://github.com/darkcenturies/sp-rp) | Private |
| Website and UCP | [sp-rp-web](https://github.com/darkcenturies/sp-rp-web) | Private |
| Discord integration | [sp-rp, bot/live](https://github.com/darkcenturies/sp-rp/tree/bot/live) | Private, same remote as the server |
| GTA rendering integration | [dlss5-neural-rendering-kit](https://github.com/darkcenturies/dlss5-neural-rendering-kit) | Private |
| GTA/SP-RP launcher integration | [dc-launcher](https://github.com/darkcenturies/dc-launcher) | Private; also serves non-GTA games |

The [36-component catalog](docs/workshop/CATALOG.md) records exact ownership,
targets, dependencies, validation and withholding reasons. Visibility describes
source, not player-facing downloads or services. Private links require access.
Maps, vehicles, models and animations follow their project owner.

## How to make or improve a mod

1. **Choose a task and GTA target:** consult the [component catalog](docs/workshop/CATALOG.md).
2. **Research the method:** use [Dryxio's 18 GTA references](research/dryxio-catalog.md)
   and original upstream attribution; record revisions and applicability.
3. **Choose the implementation owner:** private work starts in its private repo;
   public Phone work follows its reviewed public scope.
4. **Build and verify there:** [native build guide](docs/BUILDING.md),
   [SDK guide](docs/PLUGIN_SDK.md) and [GTA SA workflow](docs/GTA-SA-MOD-WORKFLOW.md).
   CLEO AI applies to CLEO scripts, not native C++/C# hook validation.
5. **Return findings here:** commit/push a safe record and open a PR, including
   useful failures. Use the [finding template](research/finding-template.md).
   Private implementation and full restricted evidence remain in their owner.
6. **Publish separately when authorized:** source commits, binary releases,
   website downloads and deployments are distinct results.

[![Colored ownership and findings-return map](docs/workshop/ownership.svg)](docs/GTA-WORKSHOP.md)

The [full atlas](docs/GTA-WORKSHOP.md) has five colored maps: ownership, task flow,
dependencies, Dryxio routes and publication. [Worked routes](docs/workshop/EXAMPLES.md)
show complete examples. Doctor/Crashfix is one artwork-free ASI in its private
owner; other permitted artwork is retained. Current maintained mods target
classic GTA SA, independently of former partner profiles.

## Public research

Start with [the research index](research/README.md) and
[the archive guide](docs/reverse-engineering/README.md). Six exact-target archives
retain their metadata and checksums. Generated output is research evidence,
not original vendor source or a runnable implementation. Historical partner
targets remain attributed evidence, not current affiliation or prerequisites.

Authored research tools and experimental implementations are private. Methods,
observations, limitations and generated evidence remain public. Executable
inputs, player records, credentials and game payloads are excluded.

## Contribute and navigate

Read [CONTRIBUTING.md](CONTRIBUTING.md); agents also read [AGENTS.md](AGENTS.md)
and [the agent guide](docs/AGENT_START.md). Every task started here returns
committed public-safe findings, including work completed in another repo.

| Path | Purpose |
| --- | --- |
| `docs/` | Mod-making guides and [documentation index](docs/README.md) |
| `docs/workshop/` | Detailed catalog, graph sources/SVGs and worked routes |
| `docs/reverse-engineering/` | Generated archives, metadata, checksums and research notices |
| `research/` | Findings, reference inventories and historical checkpoints |
| `publication/` | Approved public knowledge/evidence inventory |
| `.github/` | Contribution ownership and repository checks |

[Structure](docs/STRUCTURE.md) · [Research workflow](docs/RESEARCH_WORKFLOW.md) ·
[Publication backlog](docs/workshop/PUBLICATION-BACKLOG.md) ·
[Credits and rights](THIRD_PARTY_NOTICES.md)

Original contributions retain [BSD-3-Clause](LICENSE); third-party research and
references retain their own rights. Obtain prerequisites separately.
This is an unofficial GTA workshop.
