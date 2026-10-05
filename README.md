# GTA Workshop

A public reference library for **making, understanding and improving GTA mods**.
Find tools and upstream documentation, choose a method, study research evidence
run public Valkyrie tools and contribute what you learn. Covers GTA III, Vice City and San Andreas,
with task-specific multiplayer and engine research.

**Start:** [Reference catalog](docs/workshop/CATALOG.md) ·
[Mod-making workflow](docs/GTA-SA-MOD-WORKFLOW.md) ·
[Research](research/README.md) · [Colored maps](docs/GTA-WORKSHOP.md)

## Find the right reference

| What you want to do | Start here | What to check |
| --- | --- | --- |
| Write a CLEO script | [CLEO AI and script references](docs/workshop/CATALOG.md#scripting) | Game profile, opcode support, validation and compilation |
| Make a native ASI plugin | [SDK and engine references](docs/workshop/CATALOG.md#native) | Executable version, architecture, layouts and hook signatures |
| Understand a binary or protocol | [Reverse-engineering references](docs/workshop/CATALOG.md#analysis) | Input hash, provenance, observations versus inference |
| Edit maps, models or traffic | [Authoring references](docs/workshop/CATALOG.md#authoring) | Supported formats, permitted inputs and roundtrip behavior |
| Study multiplayer or server behavior | [Multiplayer references](docs/workshop/CATALOG.md#multiplayer) | Exact client/server version, interfaces and reproducible evidence |
| Study graphics, navigation or radar | [Graphics references](docs/workshop/CATALOG.md#presentation) | Supported target, dependency conflicts and measured behavior |

The catalog routes all **18 documented Dryxio GTA repository references** and
the separate texture reference, preserving fork-parent attribution and recorded
evaluation limits. Linking a tool does not mean it was installed or tested.
Use the original upstream documentation and applicable terms before reuse.

## Public Valkyrie tools

[Ten named families](docs/VALKYRIE-TOOLING.md) include **70 tool/helper source files**
for models, worlds, routes, textures, collision, animation, binary analysis,
pipeline checks, content generation and signal experiments.

```powershell
python valkyrie.py list
python valkyrie.py list --family valkyrie-models
python valkyrie.py demo valkyrie-collision
```

[Actual source](tooling/source/) · [Setup, commands and examples](tooling/README.md) ·
[Searchable entry-point registry](tooling/registry.json)

Content and signal examples need NumPy/Pillow; other tools may need Blender,
Ghidra, a project checkout or separately supplied game inputs. Three synthetic
examples passed; that does not establish all legacy tools or gameplay behavior.

## How to use the library

1. Define one question and the exact game/version you are targeting.
2. Choose relevant references from the catalog; record revisions and prerequisites.
3. Follow the [mod-making workflow](docs/GTA-SA-MOD-WORKFLOW.md) or
   [research workflow](docs/RESEARCH_WORKFLOW.md).
4. Implement and test in your project's repository. Record compilation,
   isolated tests and in-game behavior separately.
5. Return useful methods, results and failures here as committed public-safe
   findings. Use the [finding template](research/finding-template.md).

[![Reference library and contribution flow](docs/workshop/ownership.svg)](docs/GTA-WORKSHOP.md)

The [five colored maps](docs/GTA-WORKSHOP.md) explain library navigation,
the learning workflow, evidence requirements, reference selection and publication.
[Worked examples](docs/workshop/EXAMPLES.md) show how to apply the routes.

## What is public here

Guides, reference catalogs, workflow diagrams, findings, target metadata,
checksums and approved generated decompilation/disassembly archives.
Start at the [research index](research/README.md) and
[archive guide](docs/reverse-engineering/README.md). Generated output is research
evidence, not original vendor source or a runnable implementation.

Mod implementation, experimental runtime adapters and mod release packages
belong outside this library. The ten defined tool families are public here. Executable inputs, copied game assets,
credentials and player data are excluded. [Publication policy](PUBLICATION.md)
and [coverage/backlog](docs/workshop/PUBLICATION-BACKLOG.md) explain what is
available, proposed or withheld and why.

## Contribute and navigate

Read [CONTRIBUTING.md](CONTRIBUTING.md); agents also read [AGENTS.md](AGENTS.md).
Every task originating here must return committed public-safe findings, even
when implementation happens elsewhere. This library is maintained by one
developer and welcomes reusable knowledge from any GTA project.

| Path | Purpose |
| --- | --- |
| [docs/](docs/README.md) | Mod-making and research guides |
| [docs/workshop/](docs/workshop/README.md) | Reference routes, diagrams and worked examples |
| [docs/reverse-engineering/](docs/reverse-engineering/README.md) | Generated evidence, metadata and checksums |
| [tooling/](tooling/README.md) | Public tool source, registry, launcher examples and checks |
| [research/](research/README.md) | Findings, upstream inventories and dated historical records |
| `publication/` | Approved public knowledge/evidence inventory |

[Structure](docs/STRUCTURE.md) · [Credits and rights](THIRD_PARTY_NOTICES.md)

Original contributions retain [BSD-3-Clause](LICENSE); third-party research and
references retain their own rights. Obtain prerequisites separately.
This is an unofficial GTA reference library.
