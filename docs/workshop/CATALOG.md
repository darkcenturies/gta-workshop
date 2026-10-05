# GTA mod-making reference catalog

Choose a task and follow its upstream references. This library catalogs public
methods and research, not the maintainer's mods or private repositories.

The 18 repository entries below use the existing inventory dated **2026-10-01**.
Descriptions and evaluation states are recorded inventory evidence, not fresh
installation or runtime claims. Recheck current upstream documentation and terms
before use. [Detailed inventory](../../research/dryxio-catalog.md) ·
[Revisions/metadata](../../research/dryxio-catalog.json) ·
[Structured routes](catalog.json) · [Colored maps](../GTA-WORKSHOP.md)

<a id="scripting"></a>

## CLEO scripting

Choose the exact game/CLEO profile, inspect supported opcodes, validate and compile; report gameplay separately.

| Reference | Recorded description | Evaluation | Original upstream |
| --- | --- | --- | --- |
| [cleo-ai](https://github.com/Dryxio/cleo-ai) | Create GTA San Andreas mods with your AI, using CLEO. | `prior-documentation-review` | Original project; retain its attribution |
| [library](https://github.com/Dryxio/library) | Scripting documentation for Sanny Builder & CLEO Redux | `metadata-only-reference` | [Fork parent](https://github.com/sannybuilder/library) |

Record exact revisions, applicable terms, tools actually used, checks and
remaining limits in the returned finding.

<a id="native"></a>

## Native plugins and engine behavior

Record executable hash/architecture, SDK pin, layouts, calling conventions and signature evidence before native hooks.

| Reference | Recorded description | Evaluation | Original upstream |
| --- | --- | --- | --- |
| [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa) | GTA San Andreas Plugin SDK extended using findings from our complete, 100% reverse-engineered GTA San Andreas codebase, built with LLM assistance via auto-re-agent | `prior-documentation-review` | Original project; retain its attribution |
| [gta-reversed](https://github.com/Dryxio/gta-reversed) | Reimplementation of GTA:SA 1.0 US | `metadata-only-reference` | [Fork parent](https://github.com/gta-reversed/gta-reversed) |
| [fastman92_limit_adjuster](https://github.com/Dryxio/fastman92_limit_adjuster) | The project about the partly automated modification of the existing executable code in large quantity, code recompilation for the application with the goal of extending the existing functionality. | `metadata-only-reference` | [Fork parent](https://github.com/fastman92/fastman92_limit_adjuster) |

Record exact revisions, applicable terms, tools actually used, checks and
remaining limits in the returned finding.

<a id="analysis"></a>

## Reverse engineering and reconstruction

Use exact input hashes and bounded xrefs/types/assembly; distinguish observed evidence from inferred reconstruction.

| Reference | Recorded description | Evaluation | Original upstream |
| --- | --- | --- | --- |
| [ghidra-bridge](https://github.com/Dryxio/ghidra-bridge) | Give your AI access to Ghidra’s program analysis. | `prior-documentation-review` | Original project; retain its attribution |
| [reagent](https://github.com/Dryxio/reagent) | Reconstruct and validate C/C++ code from compiled programs with AI. | `prior-documentation-review` | Original project; retain its attribution |

Record exact revisions, applicable terms, tools actually used, checks and
remaining limits in the returned finding.

<a id="authoring"></a>

## World, model and traffic authoring

Check supported game/file formats, use permitted fixtures and record import/edit/export roundtrip behavior.

| Reference | Recorded description | Evaluation | Original upstream |
| --- | --- | --- | --- |
| [ariane](https://github.com/Dryxio/ariane) | A fully modern map editor for GTA III, GTA: Vice City, and GTA: San Andreas | `prior-documentation-review` | Original project; retain its attribution |
| [gta-scout](https://github.com/Dryxio/gta-scout) | Create GTA-style 3D models and scenes with your AI and Blender, using models and textures from your game. Early alpha. | `prior-documentation-review` | Original project; retain its attribution |
| [gta-flow](https://github.com/Dryxio/gta-flow) | Create and edit GTA San Andreas traffic routes with AI and Blender. Early alpha. | `prior-documentation-review` | Original project; retain its attribution |

Record exact revisions, applicable terms, tools actually used, checks and
remaining limits in the returned finding.

<a id="multiplayer"></a>

## Multiplayer and server research

Match exact client/server revisions; separate byte-matching claims, functional behavior and documentation; use synthetic data.

| Reference | Recorded description | Evaluation | Original upstream |
| --- | --- | --- | --- |
| [samp-source](https://github.com/Dryxio/samp-source) | Rebuilding SA-MP 0.3.7 R5 from source, byte for byte. AI-assisted reverse engineering with verifiable binary matches. | `prior-documentation-review` | Original project; retain its attribution |
| [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild) | Evidence-driven from-scratch rebuild of the SA-MP 0.3.7-R5 client DLL | `prior-documentation-review` | Original project; retain its attribution |
| [mtasa-neon](https://github.com/Dryxio/mtasa-neon) | Experimental Multi Theft Auto: San Andreas (MTA:SA) engine fork focused on larger worlds, expanded engine limits, and new Lua capabilities. | `prior-documentation-review` | Original project; retain its attribution |
| [mtasa-blue](https://github.com/Dryxio/mtasa-blue) | Multi Theft Auto is a game engine that incorporates an extendable network play element into a proprietary commercial single-player game. | `metadata-only-reference` | [Fork parent](https://github.com/multitheftauto/mtasa-blue) |
| [wiki.mtasa-neon.com](https://github.com/Dryxio/wiki.mtasa-neon.com) | Data-driven documentation for MTA:SA Neon, based on the MTA wiki with full upstream history | `metadata-only-reference` | Original project; retain its attribution |

Record exact revisions, applicable terms, tools actually used, checks and
remaining limits in the returned finding.

<a id="presentation"></a>

## Graphics, navigation and radar

Check exact target, prerequisites and mod combinations; report exercised visual/runtime scenarios and measurements.

| Reference | Recorded description | Evaluation | Original upstream |
| --- | --- | --- | --- |
| [skygfx](https://github.com/Dryxio/skygfx) | Bringing the PS2 graphics of GTA San Andreas to PC | `prior-documentation-review` | [Fork parent](https://github.com/aap/skygfx) |
| [GTA-GPS-Redux](https://github.com/Dryxio/GTA-GPS-Redux) | A complete GPS mod for Grand Theft Auto San Andreas | `metadata-only-reference` | [Fork parent](https://github.com/juicermv/GTA-GPS-Redux) |
| [Radar-in-style-GTA-SA-The-Definitive-Edition](https://github.com/Dryxio/Radar-in-style-GTA-SA-The-Definitive-Edition) | Upgrade your classic GTA SA radar to the sleek Definitive Edition 3D style | `metadata-only-reference` | [Fork parent](https://github.com/multimaks2/The-Definitive-UI) |

Record exact revisions, applicable terms, tools actually used, checks and
remaining limits in the returned finding.

## Public Valkyrie tools

The ten families include 72 published source/helper files. Collision, content
and signal synthetic examples passed; other tools retain explicit prerequisites.
See [the full method guide](../VALKYRIE-TOOLING.md).

| Named family | Task routes | Public material |
| --- | --- | --- |
| [valkyrie-models](../VALKYRIE-TOOLING.md#valkyrie-models) | authoring | Source links, commands, inputs, checks and limits |
| [valkyrie-world](../VALKYRIE-TOOLING.md#valkyrie-world) | authoring, presentation | Source links, commands, inputs, checks and limits |
| [valkyrie-routes](../VALKYRIE-TOOLING.md#valkyrie-routes) | authoring, presentation | Source links, commands, inputs, checks and limits |
| [valkyrie-textures](../VALKYRIE-TOOLING.md#valkyrie-textures) | authoring, presentation | Source links, commands, inputs, checks and limits |
| [valkyrie-collision](../VALKYRIE-TOOLING.md#valkyrie-collision) | authoring, analysis | Source links, commands, inputs, checks and limits |
| [valkyrie-animation](../VALKYRIE-TOOLING.md#valkyrie-animation) | authoring | Source links, commands, inputs, checks and limits |
| [valkyrie-binary](../VALKYRIE-TOOLING.md#valkyrie-binary) | analysis, native, multiplayer | Source links, commands, inputs, checks and limits |
| [valkyrie-pipeline](../VALKYRIE-TOOLING.md#valkyrie-pipeline) | native, scripting | Source links, commands, inputs, checks and limits |
| [valkyrie-content](../VALKYRIE-TOOLING.md#valkyrie-content) | authoring | Source links, commands, inputs, checks and limits |
| [valkyrie-signal](../VALKYRIE-TOOLING.md#valkyrie-signal) | authoring, analysis | Source links, commands, inputs, checks and limits |

## Additional texture reference

GTA SA Textures IRL is a separate profile-linked texture reference documented
in the [Dryxio inventory](../../research/dryxio-catalog.md). It is not counted
among the 18 repositories. Check original rights and permitted input provenance.

## Using and improving the catalog

Read the [workflow](../GTA-SA-MOD-WORKFLOW.md), work in your own project and
return reproducible knowledge through a findings contribution. External source
availability does not establish compatibility or permission to redistribute.
Keep fork parents, evaluation status and revisions aligned with the inventory.
Historical target records belong in research; private product ownership belongs
in the maintainer's private workspace index.
