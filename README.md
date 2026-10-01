# GTA Workshop

The public starting point for **darkcenturies' GTA work**, maintained by one
developer. Find a project, choose its source owner, do the work there, and return
public-safe findings here. Covers GTA III, Vice City and San Andreas, including
mods, multiplayer, servers, research and asset authoring.

**Start here:** [Projects](#projects-and-source-owners) · [Build](#build-the-public-mods) ·
[Workflow](#how-work-flows) · [Documentation](docs/README.md) ·
[Detailed colored maps](docs/GTA-WORKSHOP.md)

## What is in this repository

| Included here | Details |
| --- | --- |
| Doctor + Crashfix | One artwork-free x86 `doctor-valkyrie.asi`; diagnosis and crash guards share the build. |
| Valkyrie Map | Approved public 0.2.0 source baseline; exact source for the later 0.2.1-test download remains unresolved. |
| Valkyrie Repair | C# repair application, version 1.2, with isolated self-tests. |
| Research | Protocol findings, analysis tools and six checksummed decompilation targets, with original provenance. |
| Project catalog | 36 components with owners, visibility, dependencies, checks and findings-return requirements. |
| Mod-making references | Dryxio's 18 cataloged GTA repositories, original upstream attribution and task-specific routes. |

Use the [mod catalog](docs/MODS.md) for source versions and known gaps,
[research index](research/README.md) for findings, and
[publication backlog](docs/workshop/PUBLICATION-BACKLOG.md) for proposed outputs.
This checkout contains source and research. A merge does not publish binaries,
update a website, install a mod or deploy a server.

## Projects and source owners

Start every GTA task here, then implement it in the owner below.
**Visibility describes source**, independently of whether a service or download
is available to players. Private links require access. The
[component catalog](docs/workshop/CATALOG.md) gives exact routes and checks.

| Work | Source owner | Visibility |
| --- | --- | --- |
| Doctor/Crashfix, Map, Repair and public research | **This repository** | Public |
| Phone and its reviewed embedded trainer/map dependencies | [valkyrie-phone](https://github.com/darkcenturies/valkyrie-phone) | Public; independent build |
| Shared Core, Atmosphere, Fuel, Radar, native components and mod/asset tools | [valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) | Private; individual exports need review |
| SRG / GTA Midnight conversion | [street-racing-girls](https://github.com/darkcenturies/street-racing-girls) | Private by owner policy; consumes Workshop Core |
| Upstate/re3 integration and port tools | Valkyrie Workshop | Private owned patch; [novawish/re3](https://github.com/novawish/re3) is the separate public engine input |
| SP-RP gamemode, accounts and server operations | [sp-rp](https://github.com/darkcenturies/sp-rp) | Private |
| SP-RP website and UCP | [sp-rp-web](https://github.com/darkcenturies/sp-rp-web) | Private |
| SP-RP Discord bot | [sp-rp, bot/live](https://github.com/darkcenturies/sp-rp/tree/bot/live) | Private; same remote, separate production branch |
| GTA rendering integration | [dlss5-neural-rendering-kit](https://github.com/darkcenturies/dlss5-neural-rendering-kit) | Private; redistribution and reproducibility review pending |
| GTA/SP-RP launcher integration | [dc-launcher](https://github.com/darkcenturies/dc-launcher) | Private; also serves non-GTA games |

Models, maps, vehicles and animations follow their project owner. Game assets,
player records, credentials and production configuration stay outside this
public repository. Listing a private project does not approve its source for
publication. See [ownership details](docs/REPOSITORIES.md) and
[the public release boundary](PUBLICATION.md).

## How work flows

1. **Find the task:** consult the [component catalog](docs/workshop/CATALOG.md)
   and [Dryxio references](research/dryxio-catalog.md).
2. **Choose visibility and owner:** public fixes happen in their public owner;
   private work starts directly in its private owner.
3. **Build and verify there:** record the exact GTA target, applicable references,
   commands, results and untested cases.
4. **Commit, push and review:** implementation and public-safe findings both
   need durable contributions. Every task originating here returns findings
   here, including failed experiments. Use the [finding template](research/finding-template.md).
5. **Publish separately when authorized:** source merges, binary releases,
   website downloads and live deployments are distinct outcomes.

[![Colored ownership and findings-return map](docs/workshop/ownership.svg)](docs/GTA-WORKSHOP.md)

The [full atlas](docs/GTA-WORKSHOP.md) contains five colored maps: ownership,
task flow, dependencies, Dryxio routes and publication gates.
[Worked task routes](docs/workshop/EXAMPLES.md) show end-to-end examples.

## Build the public mods

Run from the repository root on Windows with MSVC C++ Build Tools, a Windows SDK
and the .NET Framework 4.x compiler. No game/server install is needed to compile.
See [compiler setup and output paths](docs/BUILDING.md).

```powershell
./build.ps1 -List
./build.ps1 -CheckEnvironment
./build.ps1 -Release
# Or build only Doctor + Crashfix:
./build.ps1 -Target doctor -Release
```

Targets: `all`, `map`, `doctor`, `repair`; `crashfix` aliases the combined
Doctor build. Current native mods target classic GTA San Andreas. Doctor/Crashfix
has no artwork; other permitted artwork is retained. Former partner profiles
are retired; historical research and upstream attribution are preserved.

**CLEO AI is for CLEO scripts.** The released mods here are C++/C#; a CLEO
reference review does not validate native hooks. Select methods through the
[GTA SA workflow](docs/GTA-SA-MOD-WORKFLOW.md). Build/test success and actual
gameplay validation must be reported separately.

## Contribute or use an agent

Read [AGENTS.md](AGENTS.md), [contributing](CONTRIBUTING.md) and the relevant
component guide. Use a branch and PR; preserve unrelated local work. In this
owner's workspace use the existing canonical checkout or a shared worktree.

Before submitting:

```powershell
python tools/check_workshop.py
python tools/check_public.py
```

The first checks navigation and catalog consistency. The second checks public
scope, implementation hashes, the SDK pin and archive integrity. Code changes
also need their applicable builds/tests. Private work returns a sanitized
result here; restricted implementation and evidence remain in their owner.

## Repository layout and further reading

| Path | Purpose |
| --- | --- |
| `client/valkyrie-asi-suite/` | Approved public mod source and component recipes |
| `docs/` | Guides; start at [the documentation index](docs/README.md) |
| `docs/workshop/` | Catalog, editable maps, rendered SVGs and publication backlog |
| `docs/reverse-engineering/` | Target indexes, generated archives, metadata and checksums |
| `research/` | Findings, references, experiment checkpoints and finding template |
| `deploy/` | Historical path for analysis/export utilities; not live deployment |
| `tools/` | Public-boundary, documentation, archive and artifact checks |
| `publication/` | Reviewed public-file allowlist and implementation hashes |
| `third_party/plugin-sdk/` | Pinned SDK submodule; see [SDK setup](docs/PLUGIN_SDK.md) |

[Structure and placement rules](docs/STRUCTURE.md) ·
[Archive reading guide](docs/AGENT_START.md) ·
[Research workflow](docs/RESEARCH_WORKFLOW.md) ·
[Private-server integration](docs/INTEGRATION.md)

Original project code uses [BSD-3-Clause](LICENSE). Crashfix and third-party
components retain their own terms; read [credits and notices](THIRD_PARTY_NOTICES.md).
Obtain game prerequisites separately. This is an unofficial GTA workshop, with
no affiliation to Rockstar Games, Take-Two or former partner projects.
