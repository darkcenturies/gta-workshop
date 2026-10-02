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
