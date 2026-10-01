# Dryxio references and Valkyrie workflow opportunities

Reviewed on **2026-09-30**, starting from [Dryxio's public profile](https://github.com/Dryxio). This is a source/documentation review, not a local installation, binary reconstruction or game-compatibility test. The [revision catalog](dryxio-upstreams.json) records full commits and immutable README links. These are evaluation references, not new dependencies or replacements for our existing pins.

## References by task

| Project | Documented upstream capability | Potential use here and remaining check |
| --- | --- | --- |
| [Ghidra Bridge](https://github.com/Dryxio/ghidra-bridge) | CLI/Python queries for decompilation, xrefs, types, containing functions, context, P-code and CFG. | Assemble bounded evidence for Doctor/Crashfix investigations. Its export format must be checked against our archive; our CSV/C exports are not automatically bridge inputs. |
| [ReAgent](https://github.com/Dryxio/reagent) | Candidate C/C++ reconstruction with checker, structural/parity checks, configured build/test gates and evidence manifests. | Trial one exact-target function. A passing checker or parity report is not proof of equivalence. Review output before incorporating source. |
| [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa) | SA-focused Plugin-SDK fork with corrections to layouts, signatures and addresses. The README identifies classic Win32 SA and Compact/Hoodlum 1.0 US targets. | Compare a relevant declaration against our pinned DK22Pac SDK and matching binary. Do not switch the submodule or assume S&SMP/PECore compatibility from this claim. |
| [samp-source](https://github.com/Dryxio/samp-source) | R5 byte-matching reconstruction with acceptance evidence and provenance. The reviewed README says full-client integration is unfinished. | Learn from complete-region comparisons, relocation/call-target checks and negative controls. Neither source presence nor a matched function proves a complete replacement DLL. |
| [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild) | Separate from-scratch R5 functional rebuild, with target identity/signature checks, deterministic testbed and behavioral evidence. | Use as a reference for compatibility test design. Functional compatibility and byte identity are separate goals; R5 evidence does not establish S&SMP behavior. |
| [Ariane](https://github.com/Dryxio/ariane) | III/VC/SA map editor with isolated save destinations, change review and backups. CLI/MCP belongs to a separate Agent Alpha bundle. | Evaluate reversible authoring and before/after captures with locally supplied assets. Stable editor availability does not imply an agent interface or multiplayer validation. |
| [GTA Scout](https://github.com/Dryxio/gta-scout) | Early-alpha asset discovery/inspection for AI-assisted Blender work; synthetic demos/tests are available. | Improve asset provenance and editable preview handoffs. Scout supplies discovery; the agent/Blender workflow supplies modeling. Game textures and models stay local. |
| [GTA Flow](https://github.com/Dryxio/gta-flow) | Early-alpha explicit traffic-graph authoring, deterministic compilation and binary verification for `sa_compact`. | Evaluate its synthetic intersection and file-roundtrip method as general research. No FLA/extended-map, console or MTA runtime backend is claimed. Blender previews do not simulate driving. |
| [CLEO AI](https://github.com/Dryxio/cleo-ai) | Pinned opcode reference, static validation, Sanny compilation and fixed generation evaluations. | Apply the lookup → validate → compile → runtime-check pattern to reproducible examples. Its default GTA/CLEO profile does not establish multiplayer support. |
| [MTA Neon](https://github.com/Dryxio/mtasa-neon) | Experimental MTA-derived engine with native NPC/traffic systems, authoritative syncer and handoff. | Compare population ownership and handoff questions with our public ped-population findings. MTA's protocol/runtime is a separate platform; this is not a drop-in SA-MP solution. |
| [SkyGfx fork](https://github.com/Dryxio/skygfx) | README describes PS2-style graphics and a build requiring an external RenderWare SDK path. | Reference for visual comparison and mod-stack test cases. This review did not establish Dryxio-specific changes, current buildability or source reuse terms. |

## Findings from the reviewed documentation

These observations concern what the pinned upstream documentation says. Suggested SP-RP/Valkyrie uses are inferences and remain unevaluated locally.

1. **Evidence can be handed off per function.** Bridge documents context/P-code/CFG queries; ReAgent documents bounded manifests and stored evidence export. A useful contribution would connect one finding to its exact input hash, address/RVA, tool revision, assembly excerpt and validation result, instead of relying on a chat transcript. Our current archive index remains the entry point.
2. **Acceptance needs explicit failure behavior.** ReAgent documents `UNKNOWN` when validation commands are absent, rejection with `require_verified: true`, and standalone parity exiting zero on RED unless `--strict-exit` is used. Any future automation must check the report and meaningful build/test results, not just an exit code or generated source count. [Pinned ReAgent README](https://github.com/Dryxio/reagent/blob/d12cea338c61898b06a86fe8adb25275fa9d5615/README.md).
3. **Platform setup affects reproducibility.** ReAgent documents direct Windows/POSIX argument arrays, while legacy command strings require `/bin/sh`. Its default isolated validation copies a project; our repository rules require canonical checkouts/worktrees. Before a trial, resolve that copy behavior using a supported configuration and an owned worktree, or use a separate synthetic fixture. Do not blindly adopt the upstream example configuration.
4. **Authoring and runtime evidence differ.** Ariane separates stable and Agent Alpha channels; Scout and Flow identify alpha limits. Flow's documented file roundtrip checks unchanged regions separately from the modified region. Preserve that distinction in our own results: a render, format check, compile, roundtrip and in-game test establish different things.
5. **Binary identity and behavioral compatibility differ.** The two R5 projects have distinct objectives. Record byte coverage only for accepted, non-overlapping regions and keep differential/runtime observations separate. No new SA-MP, S&SMP or PECore compatibility has been established by this review.

## Prioritized evaluation backlog

All entries below are **proposed**, with no installation or runtime trial performed in this change.

| Priority | Evaluation | Reviewable result and acceptance condition |
| --- | --- | --- |
| 1 | One Doctor/Crashfix-relevant function via Bridge | Finding record with matching target hash, source revision, address/RVA, callers and assembly. Independently check one claimed behavior; document format/conversion gaps. |
| 1 | One SDK declaration comparison | Pinned upstream diff, size/offset/signature assertions and exact-target evidence. If a correction is justified, build the affected x86 consumer and record runtime validation still needed. |
| 2 | One bounded ReAgent experiment | Tool/provider configuration, attempt limits, candidate diff, checker/parity reports and meaningful build/test output. Use an owned worktree or synthetic fixture after resolving isolation behavior. Keep unknown/untested status visible. |
| 2 | Ariane/Scout authoring handoff | Small original or synthetic scene, editable source, reproducible transforms, before/after preview and provenance. Establish the chosen editor channel first; any game-derived assets remain local. |
| 2 | CLEO-style validation discipline | One released-mod example with explicit dependencies and compiler-backed verification. Measure successful validation separately from runtime behavior. |
| 3 | Flow synthetic roundtrip | Input graph, deterministic output hashes, reimport result and separate unchanged-region comparison. No game install needed; multiplayer/driving remains untested. |
| 3 | Neon population comparison | Public finding comparing spawn/despawn ownership, syncer loss, handoff and reconnect cases with our ped-population record. Identify platform differences before proposing implementation. |

## Where work belongs

Public methods and findings belong here, together with source for the ten explicitly reviewed tool families. Mod implementations and release packages remain in their implementation repositories. Follow each repository's instructions and record the reviewed source revision when carrying a public correction back to its owner.

This catalog does not expand public scope to unreleased Valkyrie implementations or their project-specific notes. Do not copy private source/history, production data, local catalogs, imported NODES containing original game bytes, executables or game assets into a finding. The SDK stays at its existing [documented pin](../docs/PLUGIN_SDK.md). Changes to a dependency require their own scoped review and consumer validation.

MIT/zlib/GPL labels in the catalog describe reviewed upstream root licenses, not all dependencies, assets or derived output. Ariane, CLEO AI, the R5 projects and SkyGfx have no reuse terms established by this review. Consult/cite these references and resolve applicable terms before copying code. Preserve notices for any accepted reuse; our root BSD license does not replace them.

See [the practical workflow](../docs/RESEARCH_WORKFLOW.md), [finding template](finding-template.md), [upstream catalog](upstreams.md) and [integration process](../docs/INTEGRATION.md).

## Local asset-authoring observations, 2026-10-01

The earlier documentation review above remains historical. A later local trial
actually executed GTA Scout at `499ab20f625a90ef2ef3dc67bffc17589f522d59`
with independently supplied classic PC San Andreas assets. Catalog search,
visual packet preparation and review import ran; a five-image architectural
texture packet reported five accepted reviews and zero failures. This is
texture inspection, not a full visual review of the game's model corpus.
The bundled description pack failed its checksum verification and was excluded.
No checksum bypass was used.

Blender 4.5.8 and separately installed DragonFF were used for geometry authoring
and native DFF/COLL readback. The parser's `gtaLib/dff.py` SHA-256 was
`459ae43cb9bbd4e4ab620e8eb02c6edc72575b3c030d6e63644c194d2fa33583`.
The exact local executable identity, asset provenance, meshes and restricted
evidence remain with the implementation owner. This finding establishes an
authoring method; it makes no new game-version compatibility claim.

### Material fit requires more than discovery

Observed in the local trial: a broad infill candidate passed its sampled road
clearance checks but was rejected for visual fit. Generic UV scale, fixed
prelight, abrupt land-use boundaries and coarse terrain prevented integration
with the existing scene. A catalogue match and a structural export check do not
answer those visual questions.

The replacement method measures source corner colours and the square root of
UV area divided by world triangle area. This gives a scale reference; it does
not identify the correct atlas crop or orientation by itself. Keep facade
window rows, entrance bands and bounded paving panels deliberate. Inspect actual
source UVs before treating an atlas as a seamless texture. Stained retaining-wall
concrete was unsuitable for a sidewalk; a separately inspected plain slab
texture supplied the appropriate geometry role.

Native byte colours and Blender linear colour values must remain distinct.
For an sRGB-encoded normalized component `c`, the linear value is `c / 12.92`
when `c <= 0.04045`, otherwise `((c + 0.055) / 1.055) ** 2.4`.
Using a byte normalized to 0–1 directly as emission strength changes brightness.
For example, byte 128 normalizes to about 0.502 but converts to about 0.216 linear.
This statement concerns the Blender diagnostic, not a claim of exact GTA
lighting reconstruction.

Reproduce that colour distinction with original numerical fixtures:

```python
def linear(byte):
    c = byte / 255
    return c / 12.92 if c <= 0.04045 else ((c + 0.055) / 1.055) ** 2.4

assert linear(0) == 0
assert abs(linear(128) - 0.2158605001) < 1e-9
assert linear(255) == 1
```

### Carry traffic findings into physical design

A later graph export can be structurally valid and installed while its physical
surface findings remain. Read the actual installation receipt and normalized
export, rather than assuming an earlier authoring report still describes the
installed graph. Preserve usable routes as design context and keep unresolved
locations visible. A centreline proximity screen is not a road-width, vehicle
envelope or collision test.

The trial found proposed block reservations overlapping existing road and
building geometry. Bounding-triangle overlap is a conservative planning screen;
component identification still precedes removal or relocation. Source-backed
street endpoints also do not establish a usable junction: barriers and full
road widths require explicit geometry and collision edits.

A bounded district study exported nine DFF/COLL pairs. Vertex positions, UVs,
prelight bytes and collision face counts passed native readback checks. Matched
before/after Blender renders exposed grid-cell height cracks and a rectangular
terrain boundary; the authoring pass corrected shared per-vertex heights and
used a clipped curved embankment. These checks do not establish complete terrain
continuity, LODs, streaming, traffic behaviour or finished whole-map quality.
No game was launched for this authoring trial.

The district's spatial design was then explicitly rejected: a self-contained
terrain patch and symmetrical courtyard remained visually isolated and did not
form a coherent part of the surrounding district. It is a failed design trial,
not a successful map improvement. Preserve that negative outcome alongside the
passing format checks. The next design must begin with the district's street
hierarchy, terrain sections and site-specific building roles, rather than
replicating a procedural courtyard across the map.

Private authoring source, game-derived images, geometry, runtime adapters and
installable map packages are withheld from this public finding. They are not
required for the original numerical reproduction above. Scout's original
[agent guide](https://github.com/Dryxio/gta-scout/blob/499ab20f625a90ef2ef3dc67bffc17589f522d59/AGENTS.md)
and [Blender guide](https://github.com/Dryxio/gta-scout/blob/499ab20f625a90ef2ef3dc67bffc17589f522d59/docs/blender-cli.md)
describe packet inspection and local rendering prerequisites.
