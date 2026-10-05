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

### Measured seam closures and a traceable review queue

A subsequent bounded authoring pass closed nine visually reviewed edge seams
using existing source positions, UV projections and prelight bytes. Four other
sampled openings were retained as intentional deck/divider separations. Native
DFF geometry, UVs and colours passed readback; COLL face indices and winding
were checked separately. Twenty-six matched overhead/oblique Blender captures
passed the declared image checks. These remain diagnostics, not gameplay tests.

The same pinned Scout catalog search found eight requested model identities,
but each result reported zero placements despite their presence in the imported
source scene. That is a catalog coverage limitation. Scout supplied asset
identity; separate source-geometry tools supplied the seam audit and repairs.
Do not describe catalog search as exhaustive world validation or auto-repair.

A curved pair of boundaries can enclose a third existing surface. The repair
must subtract the occupied area before export. Testing only distant obstacle
corners missed a source plane crossing the narrow closure; clipping the obstacle
to the closure's height band corrected that failure. Preserve UVs and colours
through each clip. Triangle-centre overlap sampling is a useful check, with
incomplete intersection coverage, rather than proof of no overlap anywhere.

Compression matters even for COLL v1: the engine stores collision coordinates
on a 1/128-metre grid. Clipped slivers may collapse or reverse projected winding.
This trial retained every face with nonzero runtime area, bounded omitted source
slivers to one grid step in thickness and 0.1% of each repair's area, and chose
collision winding from the compressed vertices. The render geometry retains
those slivers. These bounds describe local export acceptance; runtime contact,
shadows and streaming still require owner inspection.

For LOD naming, a bounded RenderWare frame-name edit preserved every geometry
and unknown plugin byte. Full parsed reserialization failed on a bin-mesh list
extension. Reversing the bounded rename restored the original file byte for
byte. The package appended collision records to an existing bundle and checked
all original payload prefixes, keeping the existing archive-slot count.

Whole-source visitation produced a marked queue covering road/ground edges,
facade bases, missing terrain samples, installed route findings and extension
studies. These are candidates: water, roof terraces, lower decks and intended
retaining structures create false positives. Keep raw screens traceable, stable
review IDs and repair evidence. Preserve rejected design intents as questions,
not approved building footprints or road alignments. Do not equate model
visitation with finding every artistic or runtime problem.

Validation in this pass: eight synthetic clipping/plugin/installer tests, four
collision-coordinate tests and three collision-winding tests passed. Installer
failure injection restored existing files and removed newly created files;
changed prerequisites and candidates were rejected before writing. The native
package and matched captures passed; no GTA process was launched. Existing
public authoring and collision family notes were consulted; CADB comparison
was unsuitable for these classic COL files. No claim of execution of that tool
or of a new engine compatibility profile is made.

The reproduction pattern is: supply original or permitted synthetic surfaces,
identify and review their two actual boundary banks, interpolate source UVs and
colours, subtract existing coplanar surfaces, export and parse native files,
check compressed collision geometry, and compare the same camera and settings.
Use a synthetic triangle with an overlapping coplanar obstacle and an overhead
deck as positive and negative clipping controls. Exact game input hashes,
private authoring source, coordinates, route data, assets, images and installable
packages remain with the implementation owner and are withheld here.


### Scaling closures exposes a missing height/design gate

A 100-location diagnostic plan (nine prior accepted closures and 91 new
proposals) passed native export/readback but was withheld from installation.
The owner identified low/recessed floors in its matched views. Measuring both
source banks along the complete traced boundary found large level differences
and road-labelled surfaces paired across distinct heights. Two proposed traces
reached about ten metres of separation. Closing a hole with a narrow interpolated
strip can therefore conceal a gap while creating an unsuitable grassy wall or
joining separate structures. Format validity and unchanged source endpoints do
not establish a sound design.

The replacement acceptance gate separates small seam closures from terrain,
curb/retaining-wall and road/deck work. Record longitudinal bank-height profiles,
material roles and the intended structural treatment. Numerical thresholds
produce review leads, not counts of confirmed defects or permission to raise
all lower ground. Pending site designs cannot be promoted to a verified native
installation, even when parsing and image comparisons pass. The previously
installed bounded package was verified unchanged; the larger proposal was not
installed. One additional vegetation-obscured proposal produced no visible local
change in either inspection angle and also requires replacement or closer review.

Blender 4.5.8 and the same independently installed DragonFF parser identity
reported above produced 200 matched diagnostic views. A local review interface
loaded all 400 before/proposal images, displayed bank profiles, retained
proposal-only captions and passed desktop/mobile checks without JavaScript
errors. Fourteen synthetic bank-match, clipping, plugin, upgrade, design-gate
and failure-recovery tests passed, plus four collision-coordinate and three
collision-winding tests. Actual native verification rejected the unreviewed
plan at its first new proposal; this was an intentional design gate, not a
successful expanded repair. No GTA process was launched for these checks.

The current public workflow and the authoring/collision family prerequisites
were consulted. The three public synthetic demos were also executed with
Python 3.11: `python valkyrie.py demo valkyrie-collision`,
`python valkyrie.py demo valkyrie-content` and
`python valkyrie.py demo valkyrie-signal`. Their launcher definitions and source
hashes are recorded in [the tool registry](../tooling/registry.json).
These examples use original synthetic CADB records, tone/drawing and flat
terrain; they do not test this game's classic COL payloads or runtime behavior.
Private source, plan coordinates, surfaces, images and installable assets remain
with the implementation owner. This update is proposed through the existing
findings PR and makes no new game-version compatibility claim.


### Review and finish the continuous scene

The repair unit must include every observed seam in the comparison frame and
its continuation into adjoining sections. A marker is an inspection entry point,
not a completion boundary. Follow observed defects through street/terrain joins
and source model/chunk boundaries until sound geometry or a genuine structural
boundary is reached. Record member issue IDs and newly noticed unindexed defects.

Use the treatment appropriate to each defect and classify intentional openings
or separate decks explicitly. Compare matched wide views of the full scene and
adjoining sections alongside close-ups. Individual native-format checks do not
establish scene completion. Keep the scene open while observed confirmed defects
remain, then re-inspect for residual gaps and height/material transitions.

This records the owner's broader review requirement. It does not claim that the
pending diagnostic proposals or the surroundings of prior accepted patches have
been redesigned or completed. No additional game installation was performed.


### A connected street, terrain and building study

A subsequent local study used a street-enclosed source block as the authoring
unit. It added a connecting service street, unequal branches, complete new
building meshes, graded ground and rear-edge treatments. It remains an
uninstalled design proposal; adjacent unfinished blocks and building-edge
acceptance keep the continuous scene open. No GTA runtime acceptance is claimed.

Two useful negative results changed the checks. Unconstrained polygon Delaunay
triangles filtered only by their centroids omitted parts of a junction around
holes. Constrained triangulation plus a projected union/coverage check found
and corrected those gaps. Checking centreline grades alone also missed steep
or warped triangles at bends and branch caps. Inspect the actual driving
triangles and compressed collision, then compare matched full-scene views.

Texture identity is insufficient for integration. A narrow road-strip atlas
can contain shoulders and large repeating bands. Tiling it over a yard or
mapping it with arbitrary world UVs exposed obvious stripes. Original unmarked
asphalt, yard ground, paving and grass-transition materials were assigned to
their respective roles instead. Use the colour layer actually read by the
diagnostic shader; Blender's active colour layer can differ from it.

Source chunks can contain both sides of a street. Bound passage cuts to the
actual building, clip visible and physical walls consistently, and preserve
unrelated frontages. A bounded geometry splice retained material bytes, frames,
atomics, effect records and unknown plugins while updating affected vertex
attributes and mesh indices. Full parsed reserialization again encountered a
list-valued bin-mesh extension; it was unsuitable as a blanket preservation
method. Independently parse the resulting DFF and classic COL records.

Python 3.11, NumPy/SciPy, Shapely 2.1.2 and Blender 4.5.8 ran the local study;
native parsing used the same independently installed DragonFF parser identity
reported above. Six original synthetic clipping, affine-attribute,
container-preservation and two-sided collision-ray tests passed. Native checks
measured complete projected coverage within the declared sliver tolerance,
checked every driving triangle and sampled body-clearance rays through both
passages. The source extractor was rerun and compared array-for-array with the
authoring inputs. Six matched before/proposed-after camera pairs were rendered.
These are diagnostic and sampling results, not exhaustive building design or
gameplay proofs. LOD, registration, streaming and traffic integration were not
completed, and no game installation or GTA launch occurred.

The current public authoring/route/texture/collision workflow was consulted;
the private authoring tools above were executed. Scout's earlier identity search
remains asset-discovery evidence, not execution of an automatic city redesign.
Public tool demos from the preceding pass do not validate these new assets.
Permitted reproduction uses original synthetic street boundaries, a building
wall with packed affine UV/colour attributes, an adjoining facade that must
survive the cut and a concave road polygon with holes. Record native parser
and triangulator identities, compare polygon-union coverage and per-triangle
grades, preserve unrelated container bytes and repeat the same cameras.
Actual game input hashes, coordinates, private source and derived geometry,
textures and images remain with their local owner and are withheld here.

### Rejected design and staged effort estimates, 2026-10-02

The owner subsequently rejected the connected-block study: its rough blockout,
building treatment and terrain/material integration did not meet the requested
environmental-design quality. Passing native and sampled collision checks did
not establish visual acceptance. The proposal remains uninstalled. This local
outcome does not establish a universal capability limit for GTA Scout; the
layout and additions were authored independently of its earlier asset search.

A follow-up assessment inspected existing diagnostic images and bank-section
reports rather than generating another layout. Narrow plan-view openings can
follow long roadside traces and pair surfaces at very different elevations.
Estimate the continuous repair scene after structural classification. A large
bank-height difference is a reason to inspect decks, abutments and retaining
geometry, not automatic permission to fill the opening or lift the lower bank.

Use relative effort ranges anchored to a simple, bounded seam using an existing
toolchain. Record scope, evidence, confidence, dependencies and stage-specific
completion criteria. These initial estimates are judgment, not measured
throughput or a points-to-time conversion. Separate discovery and graybox
work from finished construction. A road connection includes its junctions,
grading, necessary frontage changes, materials, physical geometry, LODs,
navigation integration and relevant runtime review. A neighborhood graybox
establishes land use, circulation, terrain sections and building masses;
finished buildings and terrain become separately estimated tasks afterward.
Overlapping tasks must not be summed as independent work.

Review in stages: inspect; select fitting references; fit options into actual
site views; graybox; detail; verify. Record Yes/No/Unclear for purpose, scale,
access/grades, ground/foundation joins, material mapping, continuing defects,
street/wide-view quality and evidence appropriate to the claimed stage.
Unclear or failed design checks keep the stage open before costly export work.
Calibrate estimates against accepted outcomes and actual revisions.

This was an assessment/documentation pass against the same local classic
GTA San Andreas asset workflow described above. Python 3.11 read the existing
reports, and six saved diagnostic images were visually inspected. No fresh
Scout run, new geometry export, synthetic asset test, installation or GTA launch
was performed. The existing public workflow and authoring reference catalog
were consulted. Estimates, source/model identities, scene coordinates and
game-derived images remain private/local; the method and negative outcome are
returned here. Library validation is separate from asset acceptance.

### Plan city functions before filling racing scenery, 2026-10-02

A further planning review inspected eleven saved whole-map, district and site
views from the same local classic GTA San Andreas authoring workflow. Observed
frontage ribbons, exposed building backs and isolated skyline pieces suggest
that a coherent free-roam environment needs plot depth, front/rear access,
servicing, building volumes and terrain sections as well as road connections.
These are site-planning inferences, not proof that every source opening is a
defect. Render background can include water, intentional structural clearance,
absent ground or hidden surfaces; classify the physical scene before infill.

Choose land use before geometry: housing with rear courts and service access;
business sites with street-facing entrances and loading/parking access;
industrial yards with working warehouse relationships; hillside plots on
graded terraces; and open landscape with connected ridges, valleys and useful
destinations. Preserve regional architectural/material character. New local
streets must serve identified plots and connect at feasible elevations.

Compare relocation with completing existing bodies and adding access. A move
must identify a complete building and its physical geometry, LODs, effects and
neighbours first; a source chunk may contain unrelated frontages or scenery.
Closing arbitrary roof edges or moving skyline fragments is insufficient.
Develop one bounded study with references, site-fit options and terrain/access
sections, then a graybox. Re-estimate construction after layout acceptance.
Initial study ranges are judgment, not district completion prices or a city
schedule. The prior rejected layouts were not promoted to approved alignments.

[NACTO's Commercial Alley guide](https://nacto.org/publication/urban-street-design-guide/streets/commercial-alley/)
was consulted for the relationship between servicing and pedestrian/public
space; [Street Design in Context](https://nacto.org/publication/urban-street-design-guide/streets/street-design-principles/street-design-in-context/)
supports choosing streets around adjoining land use. These are functional
references rather than a requirement to adopt real-world US dimensions in a
game. Source scene images remain the local architectural reference.

Python 3.11 read the existing source-camera reports. A local review places
seven study anchors on the saved overhead projection and links source views,
relocation options and bounded first-study estimates. The markers are study
locations, not infill footprints or validated road alignments. No fresh Scout
execution, authoring export, game installation or GTA launch occurred. Private
map coordinates, source identities, geometry and game-derived images remain
with their local owner; only the reusable planning method is returned here.
Desktop/mobile presentation checks loaded all seven site images, retained the
seven linked map markers and study rows, exercised marker/return navigation,
and found no horizontal page overflow or JavaScript errors. These checks
validate the review interface, not physical layout feasibility.

### Compare bounded city grayboxes before detailed authoring, 2026-10-02

The next study compared two layouts inside one tapering street-enclosed block.
Existing frontage and roof traces informed estimated rear building envelopes,
private plots, shared courts and gardens. One option uses pedestrian access and
street-front deliveries; the other adds a short dead-end service alley and a
loading/turning court. The pedestrian option is recommended for refinement,
not accepted construction. Both retain original street frontages. No new
freestanding buildings, source cuts or relocations were authored in this pass.

Measured opposite street-bank sections and boundary samples anchor conceptual
terrain. Projecting facade/roof traces into rear envelopes does not establish
complete building bodies: exact depths, roof returns, rear doors, foundations
and style still require individual survey and design. Thirty rays across two
candidate entrance widths at three body heights cleared the selected rendered
structural mesh. An initially obstructed service-edge candidate was moved and
rescreened. These samples do not establish classic-COL clearance or vehicle
turning; a swept vehicle envelope remains a later gate.

Two negative results improved the concept checks. Filtering ground triangles
by centroid left missing coverage at concave boundaries and building envelopes.
Clip each terrain triangle to the intended domain, subtract envelopes and use
constrained triangulation of the clipped pieces. Projected uncovered area was
reduced below one millionth of a square metre in both options. Centroid-based
use colours also made jagged plot/path boundaries; exact clipped polygon
overlays made the graybox circulation legible. The largest concept service
triangle grade was 4.15%; that is not drainage or driving acceptance.

A first entrance camera was obstructed despite the sampled approach being
clear. Repositioning it along the screened corridor and rerendering all three
phases produced a useful view. Review the camera itself; geometric access
samples are not proof of a readable comparison. Four matched source/option
cameras produced twelve captures, including whole-block and eye-level views.
Two fitted plans and three source-bank sections support a Yes/No/Unclear review.
Building attachment, detailed access, materials and continuous-scene completion
remain open, including adjacent visible defects beyond this first layout.

Python 3.11, NumPy/SciPy, Shapely 2.1.2 and Blender 4.5.8 ran the private bounded
study against the same classic GTA San Andreas source workflow described above.
The current public authoring/route/texture/collision method families were
consulted; their source-discovery tools were not freshly executed. No fresh
Scout run, native export, source modification, game installation or GTA launch
occurred. Original scene and relevant installed map hashes remained unchanged.
Desktop/mobile review checks loaded thirteen images and two inline plans,
validated twelve comparison links and six quality rows, checked all review
links, and found no horizontal page overflow or JavaScript errors. Presentation
and projected geometry checks do not constitute design acceptance.

Permitted reproduction uses an original synthetic concave block, facade/roof
traces, sampled perimeter heights and two access alternatives. Build conceptual
envelopes and sectional ground; compare polygon-union coverage, actual service
triangle grades and bounded entrance rays; render the same source/option
cameras and inspect eye-level views. Record inferred geometry separately from
surveyed bodies and keep detailed/native stages gated by review. The actual
game inputs, coordinates, derived geometry, images and private implementation
remain with their local owner and are withheld from this public note.

### Source facades must determine continuations, 2026-10-02

A later city-block detailing candidate was rejected. Pattern-generated house
widths, floor heights, cream walls and repeated blue windows did not continue
the original facade proportions or materials. Small leftover green beds also
failed to express the selected landscape layout. This is an agent-authored
design failure; it does not establish a GTA Scout capability limit. The rejected
geometry was produced by local Python/Blender scripts, without a fresh Scout
inspection pass for those individual buildings. It was not accepted or installed.

The correction starts with actual facade panels, source UVs, vertex colours,
material identities and adjoining corners/roofs. A connected plane or a DFF
chunk is not a building identity. Roof-labelled materials can be window
canopies, and a missing-ground polygon is not the street-facing facade line.
Derive each building's width, storeys and plausible depth from its own frontage,
then continue its own materials and UV density onto the side and rear surfaces.
New matching material should solve a specific missing surface. An unrelated
universal plaster/window/roof template cannot establish integration.

A bounded source-only survey measured 241 wall panels and 4,832 unique source
triangles, referencing 16 facade textures. These are panel counts, not completed
building counts. A local atlas displays source locations, panel dimensions,
actual-UV elevations and the associated pixels; unlit textures are the readable
default and source prelight is optional. Desktop checks exercised every panel
and its material combination. Filtering, lighting controls and mobile layout
also passed, with no overflow or JavaScript errors. This validates a survey
interface, not building grouping, design fit or a completed detailing stage.

GTA Scout at `499ab20f625a90ef2ef3dc67bffc17589f522d59` actually ran using
Python 3.11.8: catalog stats, sixteen exact-name source-bound texture searches,
local visual-packet preparation, a contact sheet, and sixteen native DFF
material-UV diagnostics. The agent inspected the real contact-sheet pixels,
recorded visible descriptions and limitations, then imported the responses:
sixteen accepted descriptions, zero ambiguous, failed or unchanged. Description
acceptance is not design acceptance. Seven surveyed source chunks were extracted
read-only; UV diagnostics select one chunk per texture, not every occurrence.
The existing catalog snapshot was reused; a new full snapshot, shared-pack
retry and semantic-vector build were skipped. Scoped source hashes remained
unchanged. No new geometry export, installation or GTA launch occurred.

The pinned [Scout agent guide](https://github.com/Dryxio/gta-scout/blob/499ab20f625a90ef2ef3dc67bffc17589f522d59/AGENTS.md)
retains the agent's Blender CLI construction workflow. Scout supplies discovery
and inspection, while the agent supplies geometry and architectural decisions.
Its [UV diagnostic guide](https://github.com/Dryxio/gta-scout/blob/499ab20f625a90ef2ef3dc67bffc17589f522d59/docs/blender-cli.md)
also separates material UV references from proven runtime dictionary binding.
Record the actual interface, command, script/input/evidence hashes and result;
do not call a catalog citation or a rendered candidate a full Scout run.
On this Windows host, the UV helper's initial help output failed under the
default code page; `python -X utf8` successfully ran help and all diagnostics.

Permitted reproduction uses an independently supplied facade texture and static
DFF with known material references. Run catalog search, prepare local override
packets, inspect images, import honest responses using the emitted schema, and
run `asset_catalog_uv_context.py --dff MODEL --texture-name NAME --image PNG
--out OUTPUT`. Keep packet evidence in place while annotations reference it.
Review separate architectural continuations against measured original facades
before export. Actual assets, names, coordinates, source-derived diagrams,
pixels and private implementation are withheld; this record publishes the
method and negative outcome only. Whole-block design and native/runtime gates
remain open.

### Roof skins and source image orientation, 2026-10-02

A further bounded correction authored twenty-nine building continuations from
identified source elevations and return walls. Rear bays retain physical source
widths, original storey levels, triangle material references, UVs and prelight.
Six small overlapping return strips were assigned to a single parcel and their
new party boundaries closed using the respective facade materials. This is an
unaccepted Blender candidate, not a completed neighbourhood or native package.
Complex corner groups and access/landscape detailing remain unfinished.

The wall survey now contains 346 panels and 5,635 unique source triangles,
referencing eighteen texture identities. One identity is signage, excluded from
wall finishes. Replacing rounded world-space angle/intercept grouping with
actual plane residual checks recovered previously omitted narrow panels and
doors. These counts still do not identify 346 buildings. Actual return planes
can mix neighbouring elevations; upper bands can be separated from lower ones.
The line between lower return tips also need not be the upper facade plane.

The original scene's packed pixels were vertically flipped relative to native
texture decoding. Pixel comparisons confirmed this for all eighteen survey
images and ten plain wall crop references. Original scene UVs already follow
the packed-image convention; a crop inspected in a native PNG must convert its
vertical interval before use with those packed pixels. Treat image orientation
and UV dialect as explicit inputs. A geometrically correct plain crop can
otherwise display a door, painted stripe or unrelated atlas region. The survey
viewer now defaults to the actual source scene orientation.

Cornices, canopies and a projected roof outline are not complete roof surfaces.
The correction adds actual gently draining flat membranes behind parapets and
repairs two incomplete pitched roofs using their source eaves/ridges and roof
materials. One source apex almost coincided with a rear eave, producing a nearly
vertical hip; the candidate retains the eaves and uses a centred, plausible
pitch. Small closing bands use each building's own wall atlas. Upper-wall
setbacks are traced on their actual source planes, and intentional overhangs
are distinguished from unsupported joins.

Independent candidate checks passed twenty-nine roof footprint unions, upward
authored roof winding, source texture provenance and non-overlapping parcels.
Across 673 tested roof-interface samples, forty fell on intentional front
overhangs; the remaining samples found supporting wall triangles. The check
fails on unexplained unsupported samples. These bounded checks do not certify
manifold geometry, continuous UV joins, doors, collision, LODs or runtime fit.
Twenty fresh Blender captures passed geometry/image hash checks and camera
parity across ten source/detail pairs. They remain diagnostic evidence, not
GTA gameplay captures or whole-block design acceptance. Their visual inspection
also retained open entrance grade joins, arcade rear enclosure and roof finish
transitions; a roof sample pass cannot certify those details.
The source-only atlas also passed all 346
selections, filtering/lighting controls and desktop/mobile presentation checks
without horizontal overflow or JavaScript errors.

Dryxio GTA Scout revision `499ab20f625a90ef2ef3dc67bffc17589f522d59` and
Python 3.11.8 actually ran eighteen exact source-bound searches, eighteen native
DFF UV diagnostics, packet preparation and review import. Eighteen inspected
texture descriptions were accepted, with no ambiguous or failed responses.
Two additional native roof images were decoded read-only, visually inspected
and described through Scout. Their first import accepted two descriptions; a
later identical import returned two unchanged descriptions. A fine mottled
charcoal surface was selected; a coarse slab-grid candidate was rejected.
Search ranking changed after catalog annotations, so the extraction helper now
selects explicit dictionary/texture identities rather than rank positions.
The existing catalog was reused; no full snapshot, shared-pack retry or semantic
vector build ran. Scout inspection and agent-authored geometry remain separate.

Permitted reproduction uses independently supplied facade/roof triangles and
texture images: measure actual planes, bind explicit asset identities, compare
native and packed pixels, preserve physical source UV density, add roof skins
and check roof unions plus three-dimensional wall interfaces. Record command,
script/input hashes, import results and unresolved observations. Original scene
and seven scoped installed map inputs retained their hashes. No native export,
installation or GTA launch occurred. Actual assets, local identities,
coordinates, rendered pixels and private implementation are withheld; this
record publishes the reusable method, actual checks and incomplete state.

### Exact ground banks and mixed-material shells, 2026-10-02

A subsequent review found that a window-material filter omitted a separate
cornice band from four source elevations. Their new roof levels were about
1.15 metres too low. Source coplanarity, vertical band connectivity and actual
cornice pixels established the correction; the source crown now continues
around the new returns. A material family is not a complete building inventory.

The entrance also exposed errors in a smoothed ground boundary, independent
UV phase choices and prelight interpolation. The candidate now joins the raw
source bank, its elevation, actual UV density/phase and linear-light colours.
Integer UV translations belong to a chart, not to each vertex separately.
At a shared bank vertex, different source triangles can have different charts;
each new boundary triangle must inherit the appropriate original edge chart.
Small corner wedges need subdivision rather than averaging incompatible UVs.
Quantized prelight comparisons allow the actual byte-rounding error.

Further unfinished shells required individual stepped wings, pilaster caps,
cornice skins, an L-shaped lower body with an inset upper storey, and an angled
corner. Their outlines and height breaks follow actual source vertices and
planes. Existing returns can interpenetrate adjacent properties; assign that
strip once, retain the street elevations and close the resulting party edges.
Record polygon holes as well as exterior rings. Dropping an inner ring from
verification metadata can falsely report overlapping ownership or a roof hole.
A projected footprint count is not a count of complete or approved buildings.
Pedestrian paths also need checking against the newly established volumes.
Visual review rejected dense one-metre plain-crop repetition on broad plaster
backs. Those returns now copy actual source wall bands at their physical UV
scale; small plain crops remain only for residual junctions. Correct material
identity alone did not establish the correct appearance or texture density.

Dryxio GTA Scout CLI at the same pinned revision and Python version actually
ran scoped texture/model searches and native material UV diagnostics. Existing
reviewed source descriptions were reused, and a newly inspected carved cornice
description was imported successfully. The initial native UV invocation lacked
the existing DragonFF module path; setting that path allowed the diagnostic to
run. A later direct invocation omitted the Scout scripts directory; it was
corrected and rerun. These failures remain in local execution evidence.
No full catalog refresh, shared-pack retry or semantic-vector build ran.
Scout remains the starting inspection workflow; agent-authored construction
and independent geometry checks are supporting steps, not Scout execution.

Permitted reproduction uses independently supplied source walls, banks and
texture images. Run source-bound Scout searches and native UV diagnostics,
inspect the actual pixels, then measure full mixed-material profiles. Construct
separate roof layers, preserve original roof pieces where appropriate, and
verify actual triangles against roof unions and three-dimensional wall support.
For upward roof prelight, use measured upward source roof illumination instead
of inheriting a vertical wall's baked darkness. This is a provisional lighting
continuation, not a new lighting bake or runtime acceptance.

The current candidate remains unaccepted. Access, foundations, roof finish,
remaining corner groups, landscape detailing and native collision/LOD/runtime
gates remain open. Actual assets, local identities, coordinates, source-derived
diagrams, screenshots and implementation are withheld. Public reproduction
publishes the method and limitations; the local evidence retains exact hashes,
commands, failures and unresolved observations.

Independent checks passed 295 actual ground-bank samples, including 211
matching-texture UV samples, within 0.001-metre height, 0.002 periodic UV and
0.005 linear-prelight tolerances. Forty roofed footprint units include small
pilaster units; they are not forty complete buildings. Actual roof unions,
source material provenance and zero owned parcel overlap passed. Across 1,014
roof-interface samples, forty corresponded to intentional source overhangs and
none remained unexplained. The original scene and seven scoped installed map
inputs retained their hashes. No native export, installation or GTA launch ran.
An entrance diagnostic camera formerly inside an unfinished shell moved outside
the completed volume; source and candidate phases retain camera parity.

The physical UV check also passed 1,339 nondegenerate return triangles, with
maximum relative reconstructed edge-length error about 0.0001211 against a
0.001 gate. Fifty-six degenerate source UV triangles cannot establish density
and remain separately reported. Twenty-four current Blender captures cover
twelve matched cameras; geometry/image hashes and camera parity passed.
These are bounded measurements and diagnostic captures, not whole-building
or whole-block acceptance.

### Consolidated decisions and a remaining visual defect, 2026-10-02

A documentation audit found that most detailed measurements and negative
outcomes were already recorded. The private design overview now connects the
historical studies, chosen layout, evidence locations, agent-owned effort
estimates and remaining acceptance gates. Installed repairs, diagnostic repair
proposals and unexported design candidates are distinct states. Historical
reproduction recipes do not reinstate an owner-rejected design.

The latest owner image appears to show thin faces extending across or above
a roof, and the owner questions some building proportions and overall polish.
These remain unresolved observations. The image alone does not establish
whether the strips belong to retained source geometry, authored returns,
intersecting roofs or intentional architectural pieces. A sampled authored-roof
support check can pass while retained faces still protrude. Source frontage and
height measurements also do not certify sensible depth, floor use or access.

The next bounded review must inventory original and added faces together,
trace complete mixed-material vertical profiles, inspect roof intersections
and clearance in multiple views, and explain the dimensions and access of
each building in the continuing scene. Do not blindly raise roofs or remove
original faces from a screenshot inference. Record Yes/No/Unclear for complete
profiles, credible proportions, enclosure, roof clearance, foundations,
access, texture/lighting transitions and scene completeness; failed or unclear
answers keep that stage open despite passing numerical checks.

Actual Scout CLI search and native UV execution for the prior construction
checkpoint remain evidenced. This documentation audit did not run a new Scout
inspection, author geometry, export, install or launch the game. The evidence
does not establish an autonomous architectural-design capability or a universal
tool limit. Exact asset identities, source pixels, scene locations, screenshot
hashes and implementation remain private. No new public assets or tool source
are introduced by this findings return.

Blender construction follows Scout's documented workflow at the pinned
revision: its README separates discovery/inspection from agent-authored
modeling, and its agent guide retains the existing Blender CLI construction
workflow. Actual prior CLI use includes `scripts/asset_catalog.py` search,
`scripts/asset_catalog_uv_context.py` native material diagnostics and
`scripts/asset_catalog_visual.py` visual-review packet preparation/import.
These calls do not constitute an automatic building-generation or roof-repair
operation. Following the tool workflow leaves the agent responsible for the
quality of modeling and the completeness of visual review.

## Real-species foliage authoring review, 2026-10-02

Question: can classic PC San Andreas plants be authored from real botanical
references using Scout, painted textures and simple models? This pass reviewed
documentation and upstream reconstructed plant-system code, then executed a
bounded local Scout inspection to compare generated texture prototypes with
existing vegetation. It did not export a new vegetation model, modify a game
installation or test gameplay.
No exact local game executable was selected, so compatibility remains untested.

Scout at `499ab20f625a90ef2ef3dc67bffc17589f522d59` supplies asset discovery
and inspection, while its agent guide assigns construction to the Blender
workflow. Its source adapter does not calculate placements or model dimensions.
The [texture family](../docs/VALKYRIE-TOOLING.md#valkyrie-textures) supplies
dictionary inspection/preparation methods, not botanical texture painting.
Scout was executed in the follow-up below; the Valkyrie texture family was
consulted, not executed.

Two authoring routes should remain separate. Placed props use model geometry,
named materials and a texture dictionary; a dictionary can contain multiple
images and serve multiple models. An original small plant can be prototyped
with intersecting textured cards and an alpha mask, but one model does not
require exactly one image. Larger plants may combine opaque stems with leaf
cards. These are proposed construction choices, not observations of a selected
stock model's geometry.

The [upstream PlantMgr reconstruction](https://github.com/gta-reversed/gta-reversed/blob/f270ecea6b66a0b07bf462abf7ad86c38f3ee979/source/game_sa/PlantMgr.cpp)
loads grass models and `models/grass/plant1.txd` through a separate plant path.
Its [surface-property loader](https://github.com/gta-reversed/gta-reversed/blob/f270ecea6b66a0b07bf462abf7ad86c38f3ee979/source/game_sa/PlantSurfPropMgr.cpp)
reads `DATA/PLANTS.DAT`, including model/UV selection, colour, scale, wind and
density fields associated with surfaces. This is a source-review observation
of reconstructed code, not independent verification against a game executable.
Exporting a new prop alone does not establish automatic ground distribution.

For a first original texture, California poppy (*Eschscholzia californica*)
provides a concrete botanical brief: four broad orange cup-forming petals,
slender flower stalks and finely divided blue-green basal foliage, following
[NC State Extension](https://plants.ces.ncsu.edu/plants/eschscholzia-californica/).
Use botanical references to check anatomy before and after painting; a plausible
generated image is not evidence of species accuracy. Start with a few distinct
clumps, neutral diffuse lighting and true transparency. Check the chosen UV
layout, texture-name resolution, back faces, alpha edges, mipmaps, distant
silhouette, lighting and dense-card performance in the actual target. None of
those new-asset export or runtime gates was exercised by this review.

### Local native-resolution comparison

Scout's synthetic two-asset quick start and lexical search ran successfully.
A fresh classic-PC-SA source snapshot reported 14,344 model records, 32,878
texture occurrences and no adapter failures; the catalog imported 47,222
records. These are counts for one installed source snapshot, not a verified
vanilla inventory or a complete vegetation census. The installation has mods;
inspection read base archives and loose files, without resolving all runtime
Mod Loader overrides. Its main vegetation IDE supplied 171 model declarations;
other declarations and the separate grass subsystem remain outside that count.

Executed `asset-catalog --db DATABASE search flower --kind model --limit 15`,
`search flower --kind texture --limit 25`, `search genveg --kind model --limit 12`
and `search poppy --limit 10`, with further `veg` and `starflower` searches.
No poppy-named match was returned. Incomplete lexical metadata does not establish
that no visually poppy-like plant exists.

Scout's `prepare-asset-catalog-views.mjs` extracted five selected models and their
dictionaries, then a further sixteen, with no extraction failures. Native
material inspection with DragonFF distinguished textures actually referenced by
the selected geometry from other images sharing a dictionary. The broader
sixteen-model sample referenced 24 distinct texture names. Observed examples:

| Texture | Native dimensions | Observation |
| --- | --- | --- |
| `starflower1` | 128 x 128 | Purple flower spikes; botanical species not established |
| `mp_flowerbush` | 256 x 128 | Flowering branch image used by two inspected bush models |
| `veg_bush3` | 128 x 256 | Leafy branch image |
| `planta256`, `plantb256` | 128 x 128 | Names do not guarantee a 256-pixel image |
| `foliage256` | 256 x 256 | Dense green foliage image |
| `txgrass0_0` through `txgrass1_3` | 64 x 64 | Eight textures in the local `plant1.txd` |
| `gras07Si` | 128 x 64 | Additional image in that grass dictionary |

The loose grass dictionary was decoded with Scout's existing `TXDReader.js`;
this was a supporting direct decode, not a Scout catalog search or an executed
Valkyrie texture-family tool. The five-model Blender 4.5.8/DragonFF preview batch
wrote twenty views and five ready records without missing textures, but Blender
exited nonzero with an access violation after completion. A broader batch
produced only one model's four views before a crash; a factory-startup retry
also crashed. Do not report a clean renderer run or complete broader model
preview coverage. Native texture sheets remain usable independently of that
renderer failure. The DragonFF parser hash matches the earlier local trial.

Two built-in image-generation attempts produced transparent California-poppy
prototypes. Visual review rejected the first for broad leaves inconsistent with
the botanical brief; the edit remained unsuitable as an accepted real-species
asset. The original was 1,254 x 1,254 pixels. A diagnostic reduction to 128 x 128
beside the native `starflower1` image showed that resampling alone does not
resolve overly bright flowers, regular clump layout or inappropriate detail.
For a subsequent trial, select species and model role first, use a tightly
framed single clump or a deliberate atlas, and judge silhouette, colour and
readability at the actual target dimensions before export. This is a proposed
workflow, not a validated new foliage package.

Public reproduction uses independently supplied game files: run the Scout
synthetic quick start, build a fresh metadata snapshot, perform the searches
above, then run `prepare-asset-catalog-views.mjs GAME OUTPUT --catalog-root SOURCE
14400 14402 802 804 818`. Inspect native PNG dimensions and DFF material texture
names before selecting references. Game-derived PNGs, DFF/TXD cache payloads,
source locators, private catalogs and comparison images remain local and are
withheld from this public record. No new tool or mod source is published.

### Botanical shortlist after the rejected prototype

A follow-up documentation review selected six proposed authoring subjects from
botanical sources, rather than inferring species from existing game filenames.
These are design recommendations; this review did not establish their absence
from San Andreas, produce accepted textures or execute new model/runtime tests.
Proposed game locations below are artistic choices, not distribution claims.

| Real species and source | Traits to preserve | Proposed role |
| --- | --- | --- |
| [Blue-eyed grass, *Sisyrinchium bellum*](https://www.nps.gov/prsf/learn/nature/blue-eyed-grass.htm) | Narrow grass-like leaves; blue-violet flowers with yellow centres and six similar perianth segments | Small meadow or park clump |
| [California sagebrush, *Artemisia californica*](https://research.fs.usda.gov/feis/species-reviews/artcal) | Fine narrow foliage, branching shrub form and inconspicuous flowers | Dry coastal hills and roadside scrub |
| [California buckwheat, *Eriogonum fasciculatum*](https://landscapeplants.oregonstate.edu/plants/eriogonum-fasciculatum) | Narrow clustered leaves and clusters of tiny pale flowers | Low spreading hillside shrub |
| [Western swordfern, *Polystichum munitum*](https://landscapeplants.oregonstate.edu/plants/polystichum-munitum) | Dark green once-pinnate fronds growing from a dense crown | Shaded forest floor and gardens |
| [Bougainvillea, *Bougainvillea glabra*](https://plants.ces.ncsu.edu/plants/bougainvillea-glabra/common-name/bougainvillea/) | Woody climbing habit, green leaves and colourful bracts surrounding tiny flowers | Courtyard walls, fences and trellises |
| [Coast live oak, *Quercus agrifolia*](https://landscapeplants.oregonstate.edu/plants/quercus-agrifolia) | Broad evergreen crown, thick oval leaves with spiny margins and furrowed mature bark | Larger park and hillside tree |

Blue-eyed grass, swordfern and bougainvillea offer three distinct initial forms:
a small clump, radial fronds and a climbing branch. Photograph/reference the
whole habit as well as leaf/flower details, choose an actual species or cultivar,
then simplify for native-scale viewing. Small prototypes can start at 128 x 128;
branch/frond layouts may use 128 x 256 or 256 x 256 where the inspected model role
justifies it. These are trial dimensions, not universal game requirements.
Retain natural flower colour while matching surrounding texture contrast and
detail. Use image generation as a draft requiring botanical and visual review.
Check before claiming success; trees require their own trunk/crown geometry,
distance representation and runtime acceptance rather than just a whole-tree
cutout. No new image-generation or game-asset extraction ran in this follow-up.

### Duplicate-role audit and rejected swordfern trial

A subsequent 2026-10-02 trial generated a transparent western-swordfern frond
atlas using real frond photographs and a locally inspected SA fern texture as
references. The generated image was 887 x 1,774 pixels; a diagnostic reduction
was 128 x 256. User review rejected its polished visual detail and the choice
of another fern when that vegetation role already exists. No model was built,
so the prototype has no measured polygon count. Texture detail, image dimensions
and mesh triangle count are separate properties. No DFF/TXD export, installation
or runtime validation occurred. Reducing dimensions alone did not establish
style acceptance.

The same Scout revision and DragonFF parser from the native comparison above
were used for a bounded follow-up. Selecting main vegetation-IDE declarations,
vegetation/procedural/potted dictionary prefixes and flower/potted model names
yielded 238 candidate declarations across 50 dictionaries. This is a candidate
selection, including false positives, not an exhaustive vegetation inventory.
Scout successfully extracted twenty selected flower and potted-plant props;
native DFF material inspection identified 33 distinct referenced texture names.
No Blender render was attempted in this follow-up.

Observed examples from that installed source snapshot:

| Model | Parsed triangles | Material-referenced texture observation |
| --- | ---: | --- |
| `veg_fern_balcny_kb1` (635) | 6 | `kb_balcony_ferns`, 128 x 128, hanging fern foliage |
| `veg_Pflowers01` (817) | 40 | `starflower4`, 128 x 128, pale flowers and foliage |
| `veg_palmkb2` (626) | 26 | `yuka256`, 128 x 256; names alone do not identify species |
| `fosterflowers1` (11413) | 636 | `starflower1` through `starflower3`, 128 x 128, several flower silhouettes |

These counts describe whole selected models, not a universal budget for new
plants. The modded-installation and unresolved runtime-override limits above
still apply. To repeat extraction with independently supplied game files, run
`prepare-asset-catalog-views.mjs GAME OUTPUT --catalog-root SOURCE 325 625 626 627
628 630 635 638 741 817 11413 14400 2895 15038 2194 2240 2244 2246 2247 948`.
Inspect actual material names and decoded native dimensions; dictionary contents
alone do not establish which images a model uses.

Future original additions should pass a visual duplication check before
generation, then preserve a distinctive real-species silhouette at native scale.
Two proposed alternatives are [common sunflower, *Helianthus annuus*](https://plants.ces.ncsu.edu/plants/helianthus-annuus/),
with yellow ray florets around a dark disc, and [bird-of-paradise,
*Strelitzia reginae*](https://ask.ifas.ufl.edu/publication/MG106), with orange
sepals and blue petals emerging from a beak-like bract. Neither distinctive
flower form was recognized in the inspected sample; this is a bounded visual
observation, not proof of absence from the whole game. No replacement species
was generated or accepted in this follow-up. Reference photographs, game-derived
payloads, comparison sheets and rejected drafts remain local; no redistribution
rights or finished mod are asserted.

### Bird-of-paradise card prototype and continued style review

The next owner-selected subject was *Strelitzia reginae*. The
[UF/IFAS description and photographs](https://ask.ifas.ufl.edu/publication/MG106)
were consulted for its upright leathery leaves, basal clump and blue petals/orange
sepals emerging from a beak-like bract. A built-in image-generation draft and a
surface-style edit produced transparent whole-clump textures. A 1,254 x 1,254
generated source was reduced to an actual 128 x 128 RGBA authoring texture.
The native `starflower4` comparison used equal threefold nearest-neighbour
enlargement. Owner review identified softer, tidier rendering than the sharper,
more irregular SA reference; equal dimensions had not established a style match.
The texture remained under revision, not visually accepted. A second style edit
used `CJ_PLANT` as an additional coarse broadleaf reference, producing a sharper,
heavily weathered variant. Both that variant and the preceding softer texture
were retained locally. Its mottling/worn edges are generated design choices,
not botanical identifying traits or evidence of an accepted SA style match.

A concrete original model prototype used three intersecting rectangular cards
at 0, 60 and 120 degrees. Each card was 1.25 metres wide/high and split into two
triangles, yielding 12 vertices and six triangles. Every card sampled the whole
clump texture with full-image UVs. These authoring dimensions were chosen before
the native scale check below. Repeated flowers and intersections
are limitations of this cheap construction and need angle/distance review.
The triangle count happens to equal the inspected balcony fern, but this does
not establish equivalent silhouette, fill cost or runtime performance.

OBJ/MTL interchange and a packed-texture Blender project were written locally.
The OBJ check confirmed six triangular faces and twelve vertices, positive
triangle areas (minimum 0.78125 square metres), and a 128 x 128 RGBA texture with
alpha range 0 to 255. Blender 4.5.8 LTS completed a CPU preview run with exit zero,
saved the project and wrote three orthographic views at 20, 80 and 140 degrees.
The preview used nearest texture filtering and an unlit, two-sided alpha-test
material with threshold 0.5; it was not GTA lighting. This clean run applies
only to the original card prototype, not the previously unstable stock-DFF
preview batches. No DFF/TXD export, mipmap, placement or gameplay gate ran.

A follow-up size check transformed the selected native `veg_Pflowers01`
vertices through their frame hierarchy. Its authored extent was approximately
2.20231 x 2.82843 x 0.90066 model units; the new draft's card height was 1.25.
A shared-camera diagnostic preserved those scales and grounded each model's
minimum Z. It rendered with exit zero. The draft was therefore taller and
narrower than the spreading native patch, despite equal 128 x 128 image sizes.
No runtime placement scale was applied. Different silhouette occupancy, card
dimensions, contrast and fine-leaf density affect apparent pixelation; neither
equal image dimensions nor sharpening alone establishes a matched game asset.

For a permitted independent trial, create original clump artwork, reduce it to
the selected native dimensions, build the three cards above, map all UV corners
to the image, and inspect texture contrast plus the resulting mesh from several
angles before export. The authoring scripts, original mod draft, game-derived
comparison images and reference photographs remain local; this record publishes
method and evaluation limits rather than a mod package or new public tool.

### Native-grid drawing route, 2026-10-03

Owner review rejected the large generated source images themselves, rather
than merely their resized outputs. A response had conflated lack of an explicit
output-size field in the exposed image-generator call with inability to make
low-resolution artwork. Those are different constraints. This trial switched
to original coded drawing on a native 128 x 128 canvas instead of another
photographic generation/downsampling attempt.

The reviewed [Phone artwork source](https://github.com/darkcenturies/valkyrie-phone/blob/8c67c8e79227014ee6974bba303d3c28e37d09b7/valkyrie-asi-suite/valkyrie-phone/tools/generate-phone-art.py)
uses controlled raster shapes, shading bands, hard masks and final-grid grain
for its 16-pixel icons. Some shape stages use larger working masks before
sampling; other glyphs start directly at 16 x 16. Do not describe every Phone
asset as a natively painted 16-pixel image, or conflate the coded artwork route
with the built-in photographic generator. The source was consulted, not run:
its generation entry point can rewrite existing asset outputs.

An original plant drawing then used only 128 x 128 artwork buffers. Curved
paddle-blade masks, stiff petioles, a shared crown and two orange/blue flowers
were rasterised onto integer pixels. Deterministic per-pixel/coarse-patch
shading supplied the texture; no photograph or existing game/Phone pixels
were copied. There was no resampling or supersampling. The resulting RGBA PNG
used binary alpha (0 and 255), and rerunning its original drawing source
produced identical PNG SHA-256
`b40b667da3b207c4b7e05acdb5bea1e79c1a3185adb9b2013aee5eebd44d285d`.

The new image was bound to the previous six-triangle card model. Blender
4.5.8 LTS saved a project with a packed 128 x 128 texture and exited zero;
the recorded geometry remained twelve vertices and six triangles. The physical
authoring dimensions and previous game-export/runtime limits were unchanged.
A local 1:1 comparison showed each 128 x 128 image at its actual dimensions,
without an enlarged generated preview. Native sizing and reproducibility
passed; botanical/style acceptance remained under review. Original mod drawing
source and assets stay local, outside the public tooling scope; the comparison's
game-derived reference is likewise withheld.

## Retained roof intersections, material-strip depth and a rejected lighting trial, 2026-10-02

A combined source/authored review traced apparent roof protrusions to retained
return shells crossing inside a completed corner. Roof-seat elevations and
parapet caps were also distinct source levels. Raising a whole roof would hide
genuine facade detail. The bounded candidate instead trims measured interior
portions, retains exterior fragments with source barycentric XYZ/UVs and
winding, and preserves the full shallow facade/recess envelope. An initial
broader selection caught recessed details and was rejected before delivery.
Original vendor assets and the immutable source scene were not modified.

One tall body had been given the depth of a short material strip rather than
the full mixed-material shared side wall. Source-bound frontage and height can
both pass while this produces an implausibly thin building. Inspect the entire
shared plane across material families and use its real rear vertices. Resolve
the neighbouring property strip once rather than dropping the neighbour or
accepting overlapping bodies. Outward wall winding also needs an explicit
check: emission previews can conceal reversed copied rear faces.

Dryxio GTA Scout CLI at revision
`499ab20f625a90ef2ef3dc67bffc17589f522d59`, Python 3.11.8, actually ran three
texture searches and three native UV diagnostics successfully for this pass.
Actual pixels were inspected; the existing catalog and reviewed descriptions
were reused. No new description import, full catalog refresh or semantic
vector build ran. Construction and independent verification remain supporting
agent/Blender work, not Scout's automatic modeling or lighting operations.

The latest lighting review found copied street-facing baked vertex colours on
new court walls. The diagnostic texture-times-colour emission shader does not
recalculate illumination or shadows for the changed scene. Disabled imported
light helpers also had suspicious repeated pivot positions; they were not
used as lamp-placement evidence. Native DFF effects, model frames and installed
instance transforms supplied actual light positions for a bounded trial.
Do not infer a complete lighting setup from those effects alone.

A temporary scene-occluded, source-fitted linear vertex-light estimate was
rejected. Across 700 original ground references, RGB residual RMSE was about
0.239 / 0.187 / 0.100 in linear light, and the court became uniformly too
bright. Missing Blender SciPy stopped the first attempt; a NumPy-only fit then
exposed unsigned-byte overflow in midpoint alpha interpolation. The trial
authoring change and recoloured candidate were discarded. This is a negative
result, not a repaired lighting state or an engine reconstruction. Courtyard
fixture design, a coherent bake, indirect light and native day/night/runtime
validation remain open. Do not cure copied hotspots with a brightness floor.

The surviving geometry candidate passes forty owned footprint units with zero
overlap, 950 combined original/authored corner-clearance faces, 10,583 outward
perimeter samples and 1,502 nondegenerate physical UV checks. Sixty-three
degenerate source UV references remain separately reported. Ground-bank checks
pass 286 samples, including 202 matching-texture UV samples, within the prior
height, periodic UV and linear-prelight tolerances. Roof support has no
unexplained samples. These counts do not certify full solids, sensible use,
access, finished lighting or whole-block acceptance.

For permitted reproduction, inspect independently supplied source materials
with Scout's catalog and native UV scripts, retain full mixed-material profiles,
compare source and authored faces together above the actual roof seat, and
verify source-coordinate/UV preservation after clipping. Treat lighting as a
separate stage after enclosure and lamp-layout review. Original scene and
seven scoped installed map inputs retain their hashes; no native export,
installation or game launch ran. Assets, identities, coordinates, local hashes,
source-derived screenshots and implementation remain private.

Subsequent owner crops traced a sliced doorway to a partial repeated material
bay and an apparently empty frame to omitted recessed source geometry. The
door stood behind its frame; selecting only the dominant facade plane omitted
the door/reveals and let copied painted infill cover the opening. A bounded
correction restores the complete original recessed assembly with its UVs and
physical dimensions, and removes flat infill from the arch. The other wall
uses a complete native architectural bay and blank source band continuations
rather than allowing a partial door/window repeat. Four additional actual
Scout searches and two native UV diagnostics passed; source pixels and exact
diagnostic crop matches were inspected, without a new description import.

The first replacement bay exposed a transposed UV-to-barycentric colour
transform, producing transparent vertex colours from opaque source colours.
That candidate was rejected and the corrected transform gained an independent
opacity check. Source UV/material identity alone had not caught this visual
failure. Final physical UV checks now cover 1,528 nondegenerate triangles and
outward perimeter checks cover 10,662 samples. Nineteen original recessed
pieces retain their UVs and edge lengths, and flat paint no longer crosses
the arch. Access, foundations and the already documented lighting defect remain
open; this does not establish completed or runtime-accepted architecture.

## Building inventories and park review, 2026-10-02

An owner-requested review of a GTA:SA-derived map candidate used actual
Dryxio GTA Scout CLI at revision
`499ab20f625a90ef2ef3dc67bffc17589f522d59`: 27 material searches and native UV
diagnostics across seven source models. Existing catalog descriptions were
reused, native pixels and overlays were visibly inspected, and no new
description import or semantic rebuild ran. An initial doubled source-name
suffix stopped UV setup; corrected paths succeeded. UV sampling used dominant
families per model and retained earlier individual facade/roof/door evidence;
it did not independently reinspect every face or prove runtime binding.

A building inventory must distinguish main volumes, connected wings, trim
pieces and unfinished assemblages. Forty footprint units in this case became
34 main-volume review cards after grouping six pilasters with their complex.
Three additional unfinished source groups were shown rather than omitted.
Those groups still contain unsegmented pieces; the card count is not the true
physical building count. A lower-body height can also exclude an upper storey.
Source-facing and court-facing contextual images expose different defects;
nearby geometry may obscure a street view and should be reported honestly.

The park review found that existing green polygons occupied about 15% of the
authored ground while paths, planting, seating, access and building edges were
unfinished. The proposal retains two coherent gardens and a shared court,
resolves the incomplete architecture first, fits actual door/street/service
connections, and tests larger planted cores before selecting props through
Scout. No landscaping implementation or accepted footprint resulted. An
illustrative route centre line avoiding owned footprints is not finite-width,
source-group, slope or native collision acceptance. Copied facade prelight
remains a separate unresolved lighting problem.

For permitted reproduction, run Scout searches and native UV diagnostics on
independently supplied inputs, group geometric parts by actual architecture,
retain measurements and uncertainties, and use the existing Blender preview
workflow for contextual building pictures and numbered plans. Distinguish
current geometry pictures from design annotations; do not present an overlay
as an implemented after-state. Barcelona's
[official block-interior garden guide](https://www.barcelonabusturistic.cat/es/interiores-de-manzana)
is a spatial precedent for shared gardens amid rear-facing buildings, not a
plan-copying or asset license. Source-derived images, identities, coordinates,
local paths, game assets and implementation remain private. No native export,
installation, gameplay validation or whole-block acceptance ran.

## Source-shaped closures and connected gardens, 2026-10-03

A continued GTA:SA-derived map authoring pass resolved three incomplete source
assemblages into individually traced bodies, a two-level corner and a stepped
corner. This is bounded authoring, not evidence that GTA Scout automatically
models a street. Actual Scout searches, native UV overlays and visible source
pixels preceded construction through the existing Blender CLI workflow.

Dryxio GTA Scout revision remained
`499ab20f625a90ef2ef3dc67bffc17589f522d59`, with Python 3.11.8,
Node 24.17.0 and Blender 4.5.8 LTS. Seven static native assets received actual
four-azimuth visual packet inspections and imported AI descriptions. A semantic
rebuild and hybrid bench search also ran. Retrieval describes reviewed text;
it neither chooses the design nor certifies geometry. The selected furniture
was a weathered wooden bench, a compact broadleaf tree and a faceted globe
lamp, retained at native physical scale. Very large conifers and a bannered
road lamp were rejected for scale or contextual fit; a utilitarian bench was
a valid unused alternative. A palm render failed and received no accepted
visual review. Search misses prompted exact catalog names rather than invented
asset descriptions.

The upstream extraction initially lacked its PNG dependency; `npm ci
--ignore-scripts` restored it. A multi-asset render batch failed with an
allocator error. Separate runs recovered inspectable views for several assets.
The selected lamp produced a ready four-view manifest with matching image and
source hashes, but the process still returned exit one during cleanup. Those
usable images do not turn the process into a successful run. Keep exit status,
manifest completeness, visible inspection and selection as distinct evidence.

Geometry-only acceptance was insufficient. Flat closures initially passed
roof coverage but looked like bulky boxes and intersected retained roof
sheets. Two source gables instead supplied measured eaves and ridge heights;
new pitched skins use inspected native clay tiles at measured texture density.
Obsolete interior sheets are trimmed locally, preserving the shallow original
facade/recess envelope and source barycentric coordinates, UVs and winding.
A leaning reference panel failed a physical UV-density check and was replaced
by a vertical reference from the same source family. Extending coordinate/UV
checks to all clipped fragments then caught an ill-conditioned near-vertical
XY projection. Local coordinates and a vertical-plane branch address that
numerical cause; increasing tolerance would conceal it.

The accepted layout direction remains two connected gardens and a shared
pedestrian court. Enlarged planting areas use real rooting space, building
aprons and a finite-width main walk. Seating bays connect to surrounding
paving rather than becoming isolated circular islands. Bench and lamp
clearances need actual projected meshes, not only placement centres. The
illustrated southern route terminates inside the court; a through-building
street passage remains a separate access design, not an implied connection.

Copied facade prelights were replaced on newly authored surfaces by a bounded
Cycles direct-diffuse vertex-colour bake with the retained source scene as
occlusion context and newly designed court lamps. Original asset prelights
remain unchanged, and authored ground meets the source bank through a six-metre
linear-light blend. This is an authoring lighting design, not reconstruction
of GTA's renderer or a tested day/night setup. The first bake was visually too
dark. More importantly, the lamp globe and pole shared one opaque native atlas,
so an internal light could not escape. A measured globe-shell material split
keeps native vertices, UVs and pixels while allowing authored light transmission;
the metal pole stays opaque. Uniformly making the whole lamp transparent would
lose its physical shadows. Native effects/export behavior remains untested.

For a permitted independent trial, use Scout's `asset_catalog.py search`,
`prepare-asset-catalog-views.mjs`, `render-asset-catalog-views.py`, visual packet
prepare/import and semantic build/search commands with independently supplied
assets. Inspect all four views and dimensions before selection. Trace real
source facades and roof profiles, construct in the existing Blender CLI route,
then verify combined original/authored joins, physical UV density, clipping
preservation, finite-width circulation and source-ground banks before matched
contextual renders. An authoring check or render is not an installation check.
Source assets, coordinates, identities, implementation, local receipts and
game-derived images remain private. No native export, installation or game
launch ran during this finishing pass.

Final authoring checks pass 47 footprint units with zero parcel overlap,
zero unexplained roof-support samples, 5,781 nondegenerate physical UV checks
and 13,934 outward perimeter samples. Another 472 degenerate source UV
references are reported without a density claim. All 759 retained trim
fragments preserve source positions and UVs within approximately
`2.3e-11` metres and `1.1e-11` UV units. Both arcade backs retain complete,
opaque native opening features. Two connected planted areas total about
4,969 square metres; eight benches, ten trees and eleven lamps have no
projected building overlap, and bench/lamp meshes avoid the main walk.
Ground-bank checks pass 197 samples, including 174 matching-texture UV
samples, with maximum height error below `3.4e-10` metres, periodic UV
error below `9.5e-9` and linear-prelight error below `0.0024`. Changed
footprints alter the eligible bank samples; the lower count is not whole-map
coverage. These checks do not certify watertight solids, drainage, door
thresholds, native access, collision, LODs or runtime lighting.

The combined render also exposed black foliage despite a valid native texture.
Transparent alpha-card UV corners had contributed zero shader colour during
the vertex bake. A second bake samples the identical faces with an opaque
receiver that casts no extra shadows, while real native alpha cards remain
as occluders. This separates illumination sampling from opacity; it is not a
brightness-floor correction or a change to the foliage texture.

A final roof check found that world-derived tile UVs had been computed from
the triangle's pre-correction vertex order after its XYZ winding was flipped
upward. Texture identity and physical area density could still pass, while
adjacent triangles disagreed in phase. Derive UVs from the final ordered XYZ
vertices, and check shared roof vertices for periodic UV agreement. The
correction changes UVs only: it does not move buildings, alter normals or
require rerunning a white-diffuse irradiance bake. Candidate hashes, independent
checks and every contextual render still need refreshing after that edit.

## Roof undersides, exterior joins and park planting, 2026-10-03

A further local classic PC San Andreas asset-authoring trial used Dryxio GTA
Scout at the same pinned revision, Python 3.11.8, Node 24.17.0, Blender 4.5.8
LTS and the separately supplied DragonFF parser recorded above. Actual catalog
queries, native static-model extraction, four-azimuth packets and imported AI
visual descriptions preceded bounded construction in the existing Blender CLI
workflow. Four new descriptions were imported; three assets were selected:
flower rows, a leafy shrub and a perforated metal litter bin. A sparse dry
shrub was a valid unused alternative. A large disconnected hedge arrangement
did not fit the gardens. Another bin had a missing texture, and a different
bin failed before a reviewable manifest existed; neither was selected.
Semantic rebuild and hybrid retrieval ran against the reviewed catalog.

Exit codes remain separate from evidence completeness. The first renderer
invocation lacked its DragonFF environment and returned zero despite a Python
import exception and no manifest. Supplying the parser path and an explicit
Python-error exit code corrected that setup. Six later assets produced
four-view manifests but their processes crashed during allocator cleanup with
exit 11. Independently verified image/source hashes allowed visual inspection;
they do not establish successful process completion. The selected assets have
all four verified views and no missing textures. A help command also failed
under Windows cp1251; Python's `-X utf8` corrected the output encoding.

A maximum-height wall rectangle incorrectly treats space beside lower eaves
or decorative crowns as a missing face. Instead, exterior wall targets follow
the actual roof profile and graded foundation. Verify the final combined
retained source and new surfaces against those profiles. Project recessed
door backs at their measured depth before subtracting coverage: an initial
closure filled a complete arched doorway because the fixed projection depth
was shallower than its original recess. The opening-intersection check caught
that regression; extending the bound from the actual source measurement
preserved the door, reveals and UVs without flat infill.

Upward roof coverage is insufficient for views from below. New skins received
lower faces and closed edges at a deliberate physical thickness. Classify
retained native triangles before deriving those counterparts: some original
roof references were already downward-facing underside geometry. Treating
every reference as an upper skin produced incorrectly oriented new lower
faces; a winding check caught it. Retain original undersides and derive new
counterparts from the actual upper surfaces. This remains a surface-coverage
method, not a proof of complete manifold interiors.

The two connected gardens retain their shared court and finite-width main
walk. Border flowers keep native row dimensions; shrubs use an explicitly
recorded smaller ornamental scale rather than an implied native-size claim.
Bins sit beside seating bays. Modest edging follows the grade and replaces
its paving strip, with closed side faces, rather than stacking a new park
plane on top. Projected full meshes, not just centres, must clear buildings
and circulation and remain inside their planted areas. A soil-texture lead
was rejected after its visible baked patches proved unsuitable for continuous
tiling; a search hit is not material-fit evidence.

Native foliage alpha and light sampling are separate gates. The contextual
view exposed dark straight bands on large flower cards despite intact alpha.
Additional lighting vertices preserved the original surfaces and linearly
interpolated their UVs, but did not resolve the contextual bands completely.
Dense opposing cards also introduce coplanar self-occlusion in a one-sided
receiver. The revised border preview samples nearby baked ground irradiance
as an explicit two-sided ambient approximation, after the bank blend. Trees
retain their opaque no-shadow receiver. Native cutout pixels and UVs stay
unchanged. This approximates game foliage shading; it is not a native engine
equivalence, a successful physical leaf simulation or a brightness clamp.

The first authoring checks covered 47 footprint units, 240 end/rear or complex
exterior profile targets, 51 roof layers with underside coverage and 121 park
placements. There is zero parcel overlap, no unexplained sampled roof-support
gap and no projected furniture/building or main-walk obstruction. Original
street arches and recessed elevations are retained; these profile checks do
not certify every interior face. Ground-bank height, colour and UV checks
remain bounded to the previously recorded eligible samples. Native collision,
door usability, drainage, a southern through-building access, LODs and runtime
lighting remain separate unfinished gates. No native export, installation or
game launch ran. The subsequent whole-building review below changes the
footprints and refreshes these checks; those first counts are historical.

### Whole-building dimensions and connected source components

The next review distinguishes footprint units, principal bodies and property
groups. Small caps are not houses; a civic complex can have three wings, and
two houses can share lower service ranges. Treat proposed uses and hidden
room layouts as design decisions, never recovered facts from a facade.

Individually chosen rear additions deepen three shallow domestic bodies and
five shop ranges without stretching the street windows or storey heights.
The source frontage remains in place. Protect neighbours' original bodies
before ordering additions: otherwise an earlier enlarged annex can cause a
later property's overlap rule to omit it entirely. An explicit inventory
assertion and independent parcel check catch this regression. The civic
vestibule also gains a real rear body, within its connected wing arrangement.

For a rough spatial comparison, the English
[nationally described space standard](https://www.gov.uk/government/publications/technical-housing-standards-nationally-described-space-standard/technical-housing-standards-nationally-described-space-standard)
lists 50 square metres for a one-bedroom, two-person single-storey dwelling.
A footprint with an inward envelope and a separate stair/service reserve is
only a screening proxy, not that standard's Gross Internal Area or a completed
room plan. It does not establish legal compliance or inferred occupancy.
Portugal's heritage record for
[Vila Luz Pereira](https://imovel2.patrimoniocultural.gov.pt/detalhes.php?code=20641081)
provides a real example of a U-shaped residential arrangement around a long
court with a street-like character. Its connected court/access relationship
is a typological reference, not a source of invented dimensional measurements.

Native UV/pixel inspection distinguishes decorative stone crowns from roof
skins, attic walls or supposed floating skylights. Six complete source crowns
receive backs and finite returns, preserving their original fronts and native
physical texture density. Verify the combined original and added crown edge
incidence independently. This closes the selected ornaments; it does not
certify whole building interiors.

A broader retained-face height screen exposed the earlier method's central
limit: a roof covering a lower arcade footprint can pass while the real
building still has an unresolved upper house and pitched roof. Keep each
flagged connected source component under review. Height flags alone are not
confirmed defects and do not authorize mass deletion or lifting every roof.
Individual entrances, thresholds, rear service routes and deliberate street
passages remain design gates. Refresh contextual pictures and measure each
whole property before declaring architectural parity or full completion.

### Continuous banks can still produce steep pedestrian approaches

A subsequent centre-line audit sampled the authored main walk at roughly
one-metre spacing. Every point had a paving surface, yet a short source-bank
transition reached about 8.7 percent grade; five short segments exceeded the
project's five-percent design target. The ground-bank height, light and UV
continuity checks had passed. Those checks establish seam continuity, not
comfortable pedestrian access.

Inspect route slope independently after footprint and ground revisions. A
longer graded approach or a deliberate stepped route with an alternative
needs actual design; changing a centre-line label does not rebuild terrain.
The measured steep area remains open and is marked in the private review.
The target is a project design choice, not a building-code ruling. The check
covers the centre line on authored paving only; crossfall, kerbs, drainage,
street connections and native collision remain unverified. Local geometry,
coordinates, implementation and rendered pictures remain withheld.

### Copied bands, closure winding and actual doorway ground

A subsequent San Andreas-format authoring pass used GTA Scout revision
`499ab20f625a90ef2ef3dc67bffc17589f522d59` and its
`scripts/asset_catalog_uv_context.py` command on locally supplied DFF/PNG
inputs. The three successful native UV overlays were visually inspected and
their input/output hashes recorded privately. Scout established source
charts and pixels; the existing Blender workflow authored the repairs.

Two nearly coincident source wall charts had different horizontal UVs. Their
projection onto one rear plane introduced overlapping coverage. Giving one
chart ownership and clipping later coverage preserved native interpolation;
an independent projected pairwise-area check passed. Initial subtraction
failed on mixed-dimensional polygon/line intersections. Extracting area-only
components and using bounded overlay precision resolved that failure without
silently declaring the failed build successful.

The perimeter winding gate previously omitted roof-to-wall closing bands.
Include these closures and test each normal against its owned footprint.
Judge roof slab edges against the roof skin's boundary: an intentional eave
or retained pitch is not necessarily bounded by the main wall footprint.

Align complete textured door features to the actual ground at the entrance,
not a height averaged from far-apart building ends. Independent barycentric
sampling of retained source ground and authored paving confirmed roughly
25 mm clearances for two corrected rear doors. One previously floated about
508 mm above ground; the other had about 81 mm of its sill buried. These are
geometric threshold checks on opaque facades, not usable interiors, collision
or certified accessibility. Landings, service routes and architectural purpose
remain separate design work.

Completing a retained upper house also requires its own footprint, pitch and
lower roof faces; coverage of the arcade below is insufficient. A rejected
extra front pitch strip crossed existing window/crown features. Retaining the
original pitch skins avoids that mistake. Decorative crowns and side dormers
remain explicit connected-component review items. Source assets, restricted
implementation, coordinates and rendered pictures stay private; native export,
installation and runtime acceptance were not performed.

A texture-wide UV overlay is not a single-wall topology view: it stacks every
selected native triangle using that material onto one atlas. Crossed green
lines therefore do not prove a flat wall contains all those triangles.
Count physical wall faces separately from texture use, source feature clipping
and later vertex-lighting subdivisions. Recheck winding after subdivision;
testing a large face's centroid can miss smaller boundary-facing portions.
Keep UV/colour corners paired when changing winding. Native mesh budgets and
LODs remain separate from a triangle-soup authoring preview.

For permitted reproduction, follow Scout's catalog search, selected static
model preparation/rendering and visual packet prepare/import commands with
independently supplied inputs. Record failures, reject missing textures,
measure geometry and inspect context before selection. Use the existing
Blender construction route, then refresh independent checks, candidate hashes
and matched review cameras after geometry or lighting changes. Source assets,
identities, coordinates, restricted implementation, game-derived images and
local execution receipts remain private. This contribution publishes methods
and bounded authoring observations, not a game asset package or runtime claim.

### Audit original facades as well as constructed bodies

A further San Andreas-format authoring review found three original frontages
without completed supporting bodies. The former footprint/roof checks covered
only the constructed property list, so its passing dimensions did not describe
every facade visible in the pictures. Source return materials can also occupy
only a shallow stub of a longer shared wall. Resolve the whole source component
and actual front plane before choosing a property boundary or measuring depth.

GTA Scout revision `499ab20f625a90ef2ef3dc67bffc17589f522d59` supplied five
successful `scripts/asset_catalog_uv_context.py` inspections on locally supplied
DFF/PNG inputs. Native pixels, UV overlays and hashes were reviewed privately.
The existing Blender workflow performed construction, independent checks and
matched contextual rendering; these are not Scout automatic modeling calls.

Screen the complete retained facade survey against owned bodies, including
panels omitted from the author's building list. Unassigned lengths are review
leads, not confirmed holes: shared returns, free-standing walls, ornaments and
out-of-block context require separate interpretation. Three observed frontages
received individual bodies, but six other wall-panel leads remained uncleared.
Keep those locations on the review map instead of declaring the whole scene
complete. A filtered facade survey also cannot certify all small roof details,
topology, entrances, realistic use or native collision.

A partial native hip ended at a rear cut/ridge line. Treating that line as an
eave produced a nearly vertical slope despite passing projected roof coverage.
Test three-dimensional pitch and wall profiles at every roof crease; two end
heights cannot describe a central hip/platform. An individually redesigned
rear ridge provided a finite slope within the existing footprint. The roof
used its own source texture and a shared projected chart. That establishes
chart continuity, not equal physical tile density on every different pitch.

Vertex irradiance sampled directly on coincident roof corners produced dark
triangular artifacts. A separate white, non-shadowing receiver, offset 25 mm
along the outward roof normals, sampled the actual scene while the real roof
and walls remained its occluders. Only the selected authored roof colours were
replaced; geometry, UVs, alpha and other colour vertices remained unchanged.
This is a bounded preview-bake method, not GTA engine-lighting equivalence.
Also sample a midpoint on short ground-bank edges: an endpoint-only grid
followed by endpoint removal silently skips edges shorter than its spacing.

For permitted reproduction, run Scout's native UV-context command on your own
model/texture inputs, inspect the resulting pixels, map retained source planes
to supporting bodies and check actual transverse depth. Then test parcel
overlap, complete wall/roof profiles, pitch, source chart continuity and real
bank samples. Refresh candidate hashes and matched photographs after geometry
or lighting changes. Native export, installation and runtime acceptance remain
unperformed. Source assets, coordinates, restricted implementation, images and
local execution receipts are withheld; this record returns the method and
negative outcomes only.

## Unity character extraction before GTA:SA skin authoring (2026-10-03)

The authoring route was evaluated with a separately supplied Unity Android
package. The target remains preparation for classic GTA San Andreas ped
authoring; no DFF/TXD conversion, installation or gameplay validation occurred.
Game payloads, character names, input identity, private extraction scripts and
rendered images remain local. This record returns reusable methods and checks.

UnityPy 1.25.4 on Python 3.11 read serialized versions 2017.4.17f1 and
2017.4.3f1 after numerically ordered `.splitN` files were reconstructed.
Inventory distinguished shared mesh identity from renderer material variants
and repeated scene instances. The local handoff contained 116 meshes, 119
individual GLBs, six source-root assemblies, 79 textures and 122 material
records. These counts describe parts and variants, not complete characters.
The GLB writer used pygltflib 1.16.5 and NumPy 2.4.6. Mesh references, bone
names/parents, decoded influences, UVs and exact original bind matrices were
retained separately from the import-ready files.

An observed UnityPy compressed-weight defect produced a negative implicit
fourth influence: the integer accumulator was subtracted directly from `1`.
Decoding the original quantized stream with `(31 - integer_sum) / 31` restored
nonnegative normalized weights. Compare the original
[AssetStudio decoder](https://github.com/Perfare/AssetStudio/blob/master/AssetStudio/Classes/Mesh.cs)
and the installed
[UnityPy MeshHelper](https://github.com/K0lb3/UnityPy/blob/master/UnityPy/helpers/MeshHelper.py)
before assuming a dependency update needs the same workaround. Do not repair
this failure by clamping negatives or replacing influences with nearest bones.

Five accessory rigs initially moved at rest in Blender because bind frames
included scale not representable by ordinary authoring bones. Rigid bone
rotation/translation frames and matching regenerated inverse binds preserved
the original vertex positions in the editable export; exact source matrices
remained in the local evidence. This is an authoring normalization, not proof
of source-animation equivalence. Another source convention stored body meshes
Z-up; its container transform had to be applied consistently to mesh and rig.
Also keep image vertical orientation, UV transforms and triangle winding
consistent when converting Unity coordinates to glTF.

All 125 GLBs imported in Blender 4.5.8 LTS, with vertex groups retained for
every imported skinned vertex. Maximum measured rest-pose displacement was
less than 0.000001 Blender units. Three clothed textured previews were visually
inspected. Missing renderer bone lists require clearly identified numbered
joints; missing material assignments require a separate texture-selection
step. Assembly discovery alone cannot resolve mutually exclusive outfit parts.
Animations, facial morphs and Unity shader behavior were not transferred.

The published `valkyrie-models` entry
`workshop/tools/model-conversion/build_ped_from_glb_blender.py` was consulted
at SHA-256
`7d2ce70deb00be835a326eaa7cc8fea593d48e2be9977ad585ae98ee18b14039`.
It was not executed: its donor-weight transfer assumes an unrigged GLB.
`validate_sa_skin_pose.py` was deferred because it exercises GTA:SA bone names,
not the source skeleton. GTA Scout was consulted as the catalog's Blender
authoring reference; it was not used as a Unity extractor.

For permitted reproduction, inventory a separately supplied Unity package,
reconstruct split assets in numeric order, resolve renderer references and
deduplicate by mesh/material identity. Decode quantized weights, validate
nonnegative sums and joint indices, retain source bind evidence, then export
GLB with embedded textures. Import every output in Blender, compare evaluated
rest positions, inspect clothed previews and preserve explicit missing-data
flags. A GTA:SA handoff still needs target bone mapping, pose checks, material
preparation, DFF/TXD roundtrip and game testing; successful extraction cannot
establish those later gates.

### Follow-up: fitting bases and selectable outfit variants (2026-10-03)

The next local authoring pass converted five clothed outfit meshes with three
hairstyles each to 15 complete classic GTA SA ped variants. The target executable
was identified by the installed fastman92 limit adjuster as GTA SA 1.0 US HOODLUM,
14383616 bytes. The native selector compiled for x86; this establishes build and
installation evidence, not gameplay or ABI acceptance.

Bone-name hashes on two meshes without renderer references were matched against
named renderers in the same source package. Every joint resolved unambiguously:
139 on the female fitting base and 117 on the male base. Reimported named rigs
retained rest positions within 0.000001 units. Retain exact original bind matrices
separately even when making an editable rigid authoring skeleton. A fitting base
can stay separate from registered wearable variants and use a neutral material
when no renderer texture assignment survives.

Torso and shoulder landmarks established source/target axes and uniform scale.
Per-bone segment directions fitted the source rest pose to a stock 32-bone ped
rig; helper influences collapsed to the relevant target limb. Independent source
fingers could not safely share a single target finger chain's distinct pivots:
that experiment visibly separated fingertips. Collapsing them onto the palm kept
the neutral shape; weapon-grip articulation remains unfinished. Hair follows the
head without secondary motion. Existing outfit meshes retain their own body
geometry; a full variant table does not establish arbitrary garment composition.

Diffuse images retained their UV transforms and received a native D3D9 RGBA TXD
with mip chains. The installed DragonFF module advertised 0.0.2; its `gtaLib/dff.py`
SHA-256 was `459ae43cb9bbd4e4ab620e8eb02c6edc72575b3c030d6e63644c194d2fa33583`.
Use [DragonFF](https://github.com/Parik27/DragonFF) as the original format/tool
reference. Reimport must explicitly enable TXD loading and specify its filename
when several DFFs share a dictionary; disabling loose image lookup alone does
not load the TXD. All 15 DFFs reimported with textures, 32 bones and normalized
weights of at most four influences. The published stress-pose checker was run
with its bone labels adapted to the actual donor: 14 bones were exercised,
p99 edge stretch stayed below 1.43, while isolated tiny edges reached about 19
times their rest length. Neutral textured previews were inspected. This remains
a deformation prototype, rather than a completed animation-quality gate.

For selection, a data table maps character/outfit/hair tuples to complete ped
models. Parser checks reject malformed rows, duplicates and missing combinations.
Validate both ped model type and expected model-name hash before applying a
registered ID. Reuse a queued game-update skin change instead of changing the
player's model in the UI render callback. Only one preview selection should draw
at once when the existing viewer owns one global preview model.

Audit all IDE sections before reserving IDs: a gap in `peds.ide` may contain
cutscene objects in `default.ide`. A free local range was selected instead, with
enough ped records and killable model IDs configured in the existing adjuster.
The [FLA development configuration](https://github.com/fastman92/fastman92_limit_adjuster/blob/master/fastman92%20limit%20adjuster/Dev%20INI%20files/fastman92limitAdjuster_GTASA_dev.ini)
documents those limits. [Mod Loader's changelog](https://github.com/thelink2012/modloader/blob/master/doc/CHANGELOG.md)
requires newly supplied IDE files to be registered through `gta.dat`; a separate
mod folder and merge fragment avoid replacing original archives/data files.

The local installer verified executable identity, payload hashes, dependencies
and vacant model slots, backed up changed files and verified installed hashes.
Walking, crouching, grips, vehicle use and the native menu remain untested in
game. For permitted reproduction, use independently supplied source parts and
a local donor, repeat rest/weight/TXD/DFF checks and preserve numerical pose
limitations before installation. Game assets, input identity, restricted runtime
implementation, local paths, renders and installation receipts are withheld.

### Correction after reported backward-facing skins (2026-10-04)

The user reported that installed models faced backward and the selector offered
only one skin. The previous neutral renders and pose percentiles did not cover
those failures. A stock textured ped and the prior converted model were rendered
from the same camera: the stock face was visible while the conversion showed its
back. A catalog audit found that different source body/face families had all been
assigned one shared character label. Loaded-model logs confirmed that several
outfit IDs were available; that did not establish multiple character choices.

The initial axis fit used up and left to derive forward, silently preserving
handedness. Source and donor conventions required a reflection. Independent
foot/toe directions now establish forward, projected orthogonal to up and left;
the resulting basis preserves anatomical limb identity and reverses triangle
winding when reflected. Merely turning a complete weighted rig around would
not correct its relationship to stock animation. Chest helper weights now
collapse onto the torso instead of translating through unrelated donor helper
pivots. Front views of corrected clothed models were inspected against the stock
camera convention.

The revised local catalog contains four source character groups, 23 outfits and
three hairstyles per outfit, for 69 unique combinations. Multipart uniform
footwear/accessories were included. All 69 DFFs reimported with textures, at most
four normalized influences and the same 32 bone IDs as the stock donor. Maximum
imported bone-matrix component difference from stock was 0.000346. The 14-bone
stress pose yielded worst p99 edge stretch 1.6953 and tiny-edge maximum around
20; these remaining deformation limits must not be hidden by the facing fix.
Native selector source was unchanged; the correction was in assets and data.

Update preflight checked old installed hashes and the new vacant model range,
preserving a separately applied map-registration repair. A missing old `gta.dat`
fragment was traced to its byte-identical Mod Loader readme replacement; the
update accepts only that explicitly verified migration. Do not recreate a
competing data-file fragment or overwrite another session's repair just because
an earlier installation receipt describes the old path. The corrected package
was installed with backups and verified payload hashes. Gameplay animation,
weapon grips and vehicle use still require confirmation after restart.

Reproduce with permitted source parts: compare a stock donor and conversion
from an identical front camera, independently check forward and handedness,
inspect the generated character-group counts, verify all rig/weight roundtrips
and exercise updates against the actual installed files. Blender remained
4.5.8 LTS with the previously recorded DragonFF module; Python compilation and
PowerShell syntax checks passed. Game assets, source identity, private helper
implementation, previews, local paths and runtime receipts remain withheld.

Final installed-configuration inspection also caught an updater defect:
`\s*` at the end of a numeric INI match consumed line endings, joining the next
section heading to the replacement value. Horizontal whitespace plus an
end-of-line lookahead preserves the CR/LF boundary. Synthetic regression checks
cover existing-section updates, higher limits, unrelated fields, idempotence
and creating missing sections. The previous valid configuration was restored
and updated with the corrected helper; both live limit sections were verified.
Payload hashes alone cannot validate separately generated runtime configuration.

### Model motion groups and authored hair attachments (2026-10-04)

The later animation report was clarified as CJ-style motion in both the skin
preview and player, rather than broken skeletal playback. The selector changed
the model without explicitly adopting its ped model motion group; its isolated
preview always blended the default idle. A model's `woman` IDE field alone does
not prove that an existing player instance or independent preview uses that
association group. Select the loaded model group, refresh existing locomotion
associations and restore the current clothing/stat group when returning to CJ.
Keep weapon and vehicle motion selection under the game's normal control.

The original [Plugin-SDK](https://github.com/DK22Pac/plugin-sdk) declares ped-model
motion type, player movement-group state and movement-association refresh.
The original [reversed player research](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Entity/Ped/PlayerPed.cpp)
identifies movement reapplication at VA `0x609650` and group processing at
`0x6098F0` for SA PC 1.0 US. The existing native blend call is VA `0x4D4610`.
The local x86 executable's function-entry bytes were checked against the
published [1.0 US research target](../docs/reverse-engineering/generated/gta-sa-1.0-us/metadata.json).
The local executable identity and detailed byte receipt remain private. Check
loaded association bounds, slot offsets, required locomotion entries and block
availability before calling the native API. SDK compilation alone is not an ABI
or gameplay test. CLEO validation is not applicable to this native/asset change.

Side renders confirmed hair caps sitting too high. Independent Unity hair
prefabs carry root attachment placement separately from their skin bind pivots.
Dropping the former raised two caps by 0.072 source units and lost their forward
offsets. Read position, rotation and scale from the original prefab hierarchy,
then place the independent assembly at the body's head. Embedded whole-body
hair already uses body coordinates and needs a different alignment path.

Six additional styles required evaluating their original prefab rest skinning:
bone-world matrices multiplied by exact source bind matrices, blended using
original normalized weights. Their vertex displacement relative to placement
alone ranged from about 0.0156 to 0.2454 source units. One style's binding implied
roughly double the raw mesh scale; another appeared bald in the first gallery.
Corrected clothed renders confirmed the restored cap size and position. Rigid
GLB authoring frames that preserve raw mesh rest shape do not reproduce every
prefab's authored skin deformation. Keep both original data and evaluated rest
vertices, rather than inventing corrective scale from a thumbnail.

A direct native table comparison found matching HAnim ID/index/flag sequences;
different frame-list ordering was insufficient to diagnose the motion report.
Matching bone IDs and inverse bind matrices also cannot validate selection of
the intended animation style. Treat model-space fitting, attachment placement,
association selection and runtime appearance as separate checks.

The extraction inventory contains parts, material variants, outfits and hair,
not one complete character per mesh. The initial four menu entries were body
families from a converted subset. An omitted complete female police model adds
a fifth body choice; 25 named hairstyles fit the four customizable families.
The local wardrobe now has 575 outfit/hair combinations plus the police model.
Named hair assets do not establish distinct NPC face identities. Multipart
fantasy characters and static parts still need separate fitting/assembly.

Blender remains 4.5.8 LTS, UnityPy 1.25.4 and the previously recorded DragonFF
module. All 576 native exports pass normalized influence checks, stock HAnim
table comparison and diffuse-reference resolution to a 49-texture dictionary.
Maximum skin-bind component difference is 0.000002623. All 708,676 exported hair
vertices have only the Head influence; this proves binding, not scalp fit or
secondary hair dynamics. All 576 stock-rig roundtrips retained the 32 IDs with
maximum imported matrix difference 0.000346. The x86 build, animation-controller
and backend regressions, wardrobe parser, motion-group policy and installer
checks passed. Clothed body, hairstyle and side-view renders were inspected.
Numerical deformation reports remain authoring evidence; tiny-edge stretch,
weapon grips and real gameplay appearance still need separate validation.

Reproduce with independently supplied assets: recover prefab placements, evaluate
rest skinning where it differs from raw vertices, render front/side comparisons,
verify exported hair weights and native tables, test missing association groups
and restoration to CJ, then inspect actual movement after restart. Additional
IDs were individually audited because the next contiguous range contained map
objects. Game-derived models/textures, decoded source geometry, private native
implementation, input identities, renders and runtime receipts remain withheld.

A subsequent installation attempt exposed a separate process-guard failure:
the running executable used `gta-sa.exe`, while the updater checked only
`gta_sa.exe`. Some model payloads copied before Windows rejected the loaded
plugin replacement. Recognize both names, recheck immediately before writes and
probe existing destination files for exclusive access before copying any of
them. Synthetic checks now cover both names, a held file handle and a probe that
leaves file bytes unchanged. Keep the original backup; classify every partially
updated file by its verified old or new hash before constructing a resume
manifest. An interrupted update is incomplete until the game closes and all
payload/configuration checks finish. Never report an installation as successful
because model copies preceded the failure.

### Animation pointer-slot correction after a skin-preview fault (2026-10-04)

A subsequent user test faulted when opening the skin preview. The logged access
violation mapped to the helper's animation-block loaded-byte read, rather than
to an exported mesh. The pinned original Plugin-SDK revision
`15f15b60bbf74c106e1b496ff92c98764abf4605` binds `ms_aAnimAssocGroups` to
`0xB4EA34` as a pointer value. On SA PC 1.0 US, that address stores a pointer to
the heap association array; it is not the array base. Direct SDK-field indexing
therefore reads unrelated globals. See the original
[SDK binding](https://github.com/DK22Pac/plugin-sdk/blob/15f15b60bbf74c106e1b496ff92c98764abf4605/plugin_sa/game_sa/CAnimManager.cpp)
and [reversed animation manager](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Animation/AnimManager.h).

Exact-target x86 disassembly at VA `0x4D4617` (RVA `0xD4617`) contains
`8B 15 34 EA B4 00`: load the DWORD stored at `0xB4EA34` before applying the
20-byte group stride. A local minidump independently contained a non-null slot
value and a definition count of 139. The heap array was absent from the dump;
its group contents were not inferred. The local target hash and faulting plugin
instruction are retained with private evidence. This is a demonstrated binding
error; the dump's later stack-overflow exception does not establish every
subsequent failure's cause.

Read the slot value whenever inspecting a group, then check array availability,
bounds, entry offset, count and block availability. The previous fake SDK test
used a direct array and missed the real indirection. The corrected x86 fixture
uses a pointer slot, the native group stride and loaded-byte offset, and covers
null slot/array and replacement array alongside motion-policy regressions.
The trainer x86 build, motion fixture, animation-controller/backend and wardrobe
parser checks passed. Capstone 5.0.9 and minidump 0.0.24 were used for bounded
local inspection. In-game retesting remains pending; compilation and synthetic
checks alone do not certify crash-free gameplay. No CLEO source was involved.

Reproduce with an independently permitted executable: hash it, disassemble the
native global load, compare the pinned SDK binding and exercise a matching
pointer-slot fixture. Raw dumps, process addresses, runtime logs, private native
implementation, local paths, executable inputs and game assets remain withheld.

### Continuous torso fitting after an in-game proportion report (2026-10-04)

The next in-game screenshot showed a pinched waist and elongated neck. A paired
DFF/IFP import reproduced the silhouette in the installed female idle clip.
The defect was already present in the neutral export: fitting each torso weight
region to donor pivots changed neighboring regions by different translations.
Source anatomical lumbar and neck landmarks did not coincide with the donor's
animation pivots. A roundtrip, matching HAnim IDs and a pose stretch percentile
could all pass because they used this already deformed export as the baseline.

Keep one continuous torso shape after global facing/scale/pelvis alignment,
while retaining donor limb fitting and the native animation rig. Compare against
source geometry as well as the exported rest pose. On the reported clothed
outfit, 4,174 edges with only torso influences ranged from 0.333 to 3.322 times
their uniformly scaled source lengths before correction. The corrected range
was 0.999466 to 1.000787, including short-edge floating-point rounding. Same-clip
clothed before/after renders showed the shorter neck and smooth waist.

A Blender regression exercises changes between torso weight regions without
moving the rest surface and verifies that limb fitting remains active. Blender
4.5.8 LTS, the previously recorded DragonFF module and locally installed
INU_tools 2.3.1 were used. Use the same tool's DFF and IFP import conventions for
animation comparison; mixing rig rest conventions can introduce a separate
false deformation. Four samples each of the actual female idle, walk and run
clips passed for six outfits covering five body families: 72 poses, worst p99
edge stretch 1.463. The native executable/animation-pointer correction remains
separate from this mesh-fitting change. Python compilation and diff checks passed.
In-game retesting remains pending; these results establish an offline correction
and do not certify every animation, weapon grip, collision or cloth appearance.

Reproduce with independently permitted source and game inputs: preserve vertex
correspondence in the authoring scene, compare source/rest edge lengths in the
affected weight regions, then render identical samples of actual animation clips.
Use consistent camera framing and keep static fitting and posed deformation
results separate. The reusable fitting helper, synthetic regression and paired
DFF/IFP sampler are now [published in valkyrie-models](../tooling/README.md#continuous-torso-fitting-and-locomotion-checks).
Their registry entries preserve source hashes and the reviewed source revision;
the helper and sampler require caller-supplied geometry/frames and permitted
inputs respectively. Project assembly recipes, trainer implementation, models,
source geometry, fitting-base assets, clips, screenshots, input identities and
installation paths remain withheld. No CLEO source was involved.

The final offline conversion checks covered 576 exported models and 288 actual
idle/walk/run samples across 24 outfit assemblies, with worst p99 edge stretch
1.548374. These extend the preliminary six-outfit result above. Installation
completed locally; the owner's in-game retest remains pending.

For this source publication, the two synthetic regression tests passed again
in Blender 4.5.8. The published sampler passed 12 idle/walk/run samples on one
locally supplied model and reproduced its previously recorded measurements.
The public inventory, three synthetic demos and 54 research evidence hashes
passed; the input model, clips and output receipt remain local.

### Wardrobe coverage and appearance preservation (2026-10-05)

The coverage question was whether a female-only conversion had omitted other
bodies and authored faces. Inventory renderer references and managed appearance
components, not only mesh-name prefixes. The local Unity 2017.4.17f1 audit
recovered 118 meshes, 139 material/renderer parts and 119 source textures with
zero extraction errors. Static MeshRenderer references resolved seven additional
female styles and other accessories; a second material assignment supplied an
alternate hair appearance. Named hair prefabs are not evidence of unique faces
or NPC identities. Source face components explicitly map compatible UV/material
slots to eight iris textures and six further face atlases; two bodies instead
use eight iris RGB presets. Swapping arbitrary atlases would not establish
compatible face choices.

The resulting local humanoid catalogue contains 1,042 fitted geometries across
13 body/character groups, 33 female and eight male hairstyles, male outfits and
police, four zombies, a fantasy creature and wearable accessories. Combining
compatible face/eye presets yields 14,018 complete appearance rows. The source
ledger separately retains a quadruped cat requiring a different animation rig,
an orphan hairstyle without a renderer/material assignment, duplicate geometry,
a scene prop and two technical fitting bases. This is a resolved humanoid
conversion, not a claim that every original mesh is a working player skin.

Decode compressed skin weights from the quantized stream, including implicit
fourth influences. Prefer evaluated authored prefab transforms for independent
hair and player/head-relative references for one-bone attachments; dropped-item
scene transforms are unsuitable. A broad hat needed final seating against the
fitted scalp. The male officer omitted toes: using the foot frame's down axis
as a toe direction made its shoes stand upright. Recover both down and forward
components from the matching rig, then inspect the resulting clothed pose.
These failures demonstrate why native binding checks alone cannot establish
placement or silhouette correctness.

Keep appearance edits independent of fitted geometry. Bounded texture-name
replacements and explicit iris RGB patches left every byte outside their
declared appearance regions unchanged on 12,976 aliases, including vertices,
UVs, skin data, alpha and plugins. Ten hair palettes preserve alpha and relative
shading; normalizing luminance permits light colours on dark source textures.
Map actual native hair material slots rather than recolouring shared texture
names globally. A scoped native draw override can restore shared texture pointers
and RGBA immediately, following the original [Plugin-SDK PedPainting pattern](https://github.com/DK22Pac/plugin-sdk/blob/15f15b60bbf74c106e1b496ff92c98764abf4605/examples/PedPainting/Main.cpp).
Bounded exact-target x86 inspection confirmed both SDK render call sites set
ECX to the entity and call a thiscall routine that reads the entity from ECX.
The local native implementation/evidence remains with its implementation owner.

Do not allocate appearance models blindly across a presumed 65,536-entry table.
The native entity model index is signed 16-bit; this catalogue stays below
32,768 and was allocated against the complete destination IDE inventory. Colour
choices do not consume additional model IDs. Check the texture dictionary's
streaming cost; the evaluated 428-texture RGBA dictionary is 189,248,684 bytes.
The [original FLA configuration](https://github.com/fastman92/fastman92_limit_adjuster/blob/master/fastman92%20limit%20adjuster/Dev%20INI%20files/fastman92limitAdjuster_GTASA_dev.ini)
documents `[STREAMING] Memory available`; the local installer requests a
512 MB minimum while preserving higher settings and unrelated configuration.

Executed checks: all 1,042 geometries passed native HAnim/inverse-bind, normalized
weight, finite-vertex, texture-reference and head-bound-hair checks. The 466 new
exports passed DragonFF reimport and 14-bone stress checks (worst p99 edge stretch
1.6627), extending the earlier 576 results. Paired INU_tools samples passed on
336 female and 228 male idle/walk/run poses (worst p99 1.609 and 1.374 respectively).
Clothed body, authored face/iris, hair palette and corrected attachment renders
were inspected. The native x86 build, complete-catalogue parser, unbiased character
randomization, scoped material restoration (including nested/exception exits),
movement, animation controller/backend and installer fixtures passed. These are
offline checks; in-game walking, grips, menu interaction and crash-free rendering
remain pending.

Blender 4.5.8, the previously recorded DragonFF module, INU_tools 2.3.1,
UnityPy 1.25.4, TypeTreeGeneratorAPI 0.0.10, NumPy 2.4.6 and Pillow 12.3.0 were
used. The source reconstruction, bounded appearance helpers, native skin checker,
palette builder, texture writer and synthetic tests are now inventoried in
[valkyrie-models](../tooling/README.md#wardrobe-coverage-face-aliases-and-hair-palettes).
The sampler now accepts explicit clip names for male/female comparisons. Its
registry preserves the reviewed source revision and exact source hashes.

Reproduce using separately permitted assets and assemblies: augment the source
manifest, classify every renderer/mesh disposition, resolve authored appearance
slots, compare native bindings against a supplied donor and sample matching
DFF/IFP imports. Run the nine synthetic appearance/palette checks without game
inputs. Private assembly/catalogue recipes, native mod code, installation and
package operations, source/converted models, textures, fitting bases, clips,
assemblies, screenshots and private Git history remain excluded. No CLEO source
was involved. Source publication and local installation do not publish a mod
download or establish gameplay verification.


### Humanoid animation reconstruction and native movement (2026-10-05)

The question was how to retain source character actions in a trainer and use
source movement on converted GTA SA skins. Follow the [Dryxio native and
model-authoring routes](../docs/workshop/CATALOG.md), then distinguish scalar
muscle decoding, pose reconstruction, native animation encoding and gameplay
integration. A Unity 2017.4.17f1 local inventory found 132 clips: 121 humanoid
clips and 11 animal/prop/environment clips. Controller references provided
movement choices for six character families. The non-humanoid clips need
their original rigs and were retained as local authoring inputs.

The streamed clip data contains timed scalar keys and cubic coefficients;
dense samples and constants complete each binding's actual channel width.
Humanoid body channels are muscle/IK values, not rotations to copy into bones.
[Unity's Avatar bindings](https://github.com/Unity-Technologies/UnityCsReference/blob/master/Modules/Animation/ScriptBindings/Avatar.bindings.cs)
expose pre/post rotations, limits and signs; the
[AssetRipper humanoid channel enum](https://github.com/AssetRipper/AssetRipper/blob/master/Source/AssetRipper.SourceGenerated.Extensions/Enums/AnimationClip/HumanoidMuscleType.cs)
provides the versioned channel layout. The evaluated offline reconstruction
uses serialized avatar rest frames, signed limits and swing/twist, then
fixed-length two-bone goals. It does not execute Unity's IK/stretch or animator
state machine. Unreachable source goals are clipped: the largest measured
goal residual was 0.19282 source units, and the largest per-clip mean was
0.04896. The target collapses fingers; precise hand contacts are unverified.

Retarget against paired native DFF/IFP conventions, not bounding boxes or an
unrelated armature importer. A native ped bind skeleton and its animated frame
have different basis directions. Preserve native bone tags and parent-local
rotations. Pelvis alignment needs the real torso direction; a near-coincident
dummy spine child caused poor torso/head poses in an initial experiment.
The supplied target has 32 tags, including helper tags above 255. Restricting
all bone tags to one byte would wrongly discard those helpers.

Two native encoding mistakes were caught before installation. ANP3's frame
allocation contains only keyframe bytes, excluding sequence headers, and its
compressed flag must be 1. More subtly, INU_tools 2.3.1 reads compressed time
with /30, while SA uses signed 16-bit **60 Hz ticks**. A paired import/export
roundtrip could conceal this mistake. The
[original reconstructed frame types](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Animation/AnimSequenceFrames.h)
and [ANP3 loader](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Animation/AnimManager.cpp)
support the format checks. On the exact local SA 1.0 US executable
`a559aa772fd136379155efa71f00c47aad34bbfeae6196b0fe1047d0645cbd26`,
bounded x86 inspection of `CalcTotalTimeCompressed` at `0x4CF3E0` confirmed the
signed time read at `0x4CF42E` and multiplication at `0x4CF43A` by the float at
`0x859044` (approximately 1/60). Thirty Hz sampling therefore writes two ticks
per pose interval. The paired validator corrects only its local add-on cache.
The older wardrobe sampler is corrected here too: earlier normalized-fraction
shape measurements remain shape evidence, but their reported seconds were
not valid native timing evidence.

Source walk/run loops are mostly animated in place. Zero forward root travel
would produce zero SA animation-derived ground speed. The
[original reconstructed walk-speed routine](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Entity/Ped/Ped.cpp)
reads first/root-sequence end-minus-start Y divided by clip duration.
Bounded exact-target inspection at `0x5E04B0` confirmed the subtraction at
`0x5E04F2` and duration division at `0x5E04F5`. The local assembly recipe adds
positive linear Y travel to 14 selected movement clips, calibrated against
supplied native walk/run/sprint clips. These are target travel speeds, not
inferred source controller velocities. Source vertical bob and limb poses
remain separate. Partial Mod Loader walkcycle groups select six native slots;
this does not import the source game's NPC behavior, weapon or vehicle logic.
[Original Mod Loader streaming documentation](https://github.com/thelink2012/modloader/blob/master/doc/plugins/gta3/std.stream.md)
and [animgrp merger](https://github.com/thelink2012/modloader/blob/master/src/plugins/gta3/std.data/data_traits/animgrp.cpp)
were consulted for loose IFP registration and group-fragment merging.

All 121 converted clips passed native flag/allocation, 32-tag, quaternion,
signed-clock and duration checks. Four paired samples per clip on female,
male and zombie skins produced 1,452 finite noncollapsed poses, with worst
p99 edge stretch 2.32105. Nineteen distinct movement/idle selections on one
representative of each of 13 body groups produced 988 poses, with worst p99
1.93261. The height gate allows prone poses (0.2..3 native units); stretch is
reported rather than accepted against a visual-quality threshold. A four-family
clothed pose gallery was inspected locally. These checks cannot establish
foot planting, grip accuracy, seamless transitions or crash-free gameplay.

Eight synthetic decoder/writer checks passed, including known cubic values,
truncation, allocation, actual 60 Hz tick bytes, signed limits, root order and
forward travel speed. The isolated native path/catalog/streaming/reference
and restart fixtures, existing wardrobe/motion/animation regressions and
complete x86 trainer build passed. Native object symbols were checked separately
from fixture objects. The evaluated destination had no extra Mod Loader IFP
blocks or animgrp files, including its IMG archives; adding the block gives
135/180 blocks, 1,992/2,500 hierarchies and 145/200 groups. Audit the complete
new destination again rather than assuming another installation has this budget.
Gameplay, all trainer controls and movement transitions remain pending.

Blender 4.5.8, INU_tools 2.3.1, UnityPy 1.25.4, NumPy 2.4.6 and the previously
recorded SDK pin were used. Six reusable modules/helpers/tests are published
in [valkyrie-models](../tooling/README.md#unity-muscle-channels-and-native-sa-animation-clocks)
from reviewed merged source revision `c0a0ff458df6c8b2006719a7f257816243dd3752`,
with exact per-file hashes. Reproduce synthetic decoding and native writing
without game inputs; supply separately permitted clip trees/avatar/target rigs
for reconstruction and paired sampling. The source controller selection,
assembly/package/install recipes and trainer runtime implementation stay outside
this library, together with models, clips, textures, assemblies, screenshots,
private history and installation evidence. No CLEO source was involved. Tool
publication and the local package do not publish a mod download.

## Loading-time model table overflow (2026-10-05)

A subsequent owner test crashed during loading, before the trainer menu opened.
On the previously identified SA 1.0 US HOODLUM x86 target, the exception was in
native model lookup at `0x4C598B`, called by collision loading. An expanded
wardrobe used model IDs above 19,999 while the model-information pointer table
retained its stock 20,000-entry capacity. Increasing ped records and kill counters
had not resized that table. Earlier successful asset/animation fixtures and
animation-block budgets did not test this independent limit.

The stock pointer table begins at `0xA9B0C8`. Its first out-of-range pointer slot
is `0xAAE948`, also the native last-search-index global. A local minidump contains
a heap pointer there, matching the exception's ESI register; the backward lookup
then used that pointer as an index and dereferenced invalid memory. Missing heap
pointee and code pages were not treated as dump evidence. The disk instructions,
exception log and missing capacity setting explain this specific loading fault.

The [Dryxio limit-adjuster reference](https://github.com/Dryxio/fastman92_limit_adjuster)
routes to [fastman92's original implementation](https://github.com/fastman92/fastman92_limit_adjuster/blob/master/fastman92%20limit%20adjuster/fastman92%20limit%20adjuster/Source%20files/Modules/FileIDlimit.cpp).
Its file-ID patch and DFF capacity are independent of registered-kill counters.
Capacity must cover the highest allocated ID, with the file-ID patch enabled
when exceeding stock capacity; record counts alone do not establish that bound.
Relocation also changes subsequent streaming ranges and may require unsigned
combined file IDs. The installed limit adjuster was 7.6; upstream source review
supports the distinction, without claiming exact correspondence to that binary.

The implementation owner corrected the installer and added synthetic checks of
IDs 19,999/20,000, the expanded range, preserved higher capacities, unrelated
settings and idempotence. These passed. Native loading after the correction and
in-game movement remain separate validation gates. Local logs, memory dump,
configuration, assets, runtime source and installation recipes are withheld;
this record returns the reusable failure mechanism and corrected validation scope.
