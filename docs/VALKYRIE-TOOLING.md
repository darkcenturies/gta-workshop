# Valkyrie tool methods

Nineteen named tools/families with **84 published source/helper files**. Browse the
[source registry](../tooling/registry.json) or use the [launcher and examples](../tooling/README.md).
Mod implementations and game payloads stay outside the public library.

**Checked 2026-10-01:** Python syntax, inventory/hashes and three synthetic
examples passed. Blender, Ghidra, project-dependent checks and gameplay require
their own prerequisites and are not claimed validated by those examples.

| Family | Use it to understand |
| --- | --- |
| [valkyrie-models](#valkyrie-models) | Model conversion and inspection |
| [valkyrie-world](#valkyrie-world) | World indexing and map preparation |
| [valkyrie-routes](#valkyrie-routes) | Road graphs and navigation audits |
| [valkyrie-textures](#valkyrie-textures) | Texture dictionary inspection and preparation |
| [valkyrie-collision](#valkyrie-collision) | Collision inspection and comparison |
| [valkyrie-animation](#valkyrie-animation) | Animation inspection and retargeting |
| [valkyrie-binary](#valkyrie-binary) | Binary, hook and protocol analysis |
| [valkyrie-pipeline](#valkyrie-pipeline) | Build provenance and release verification |
| [valkyrie-content](#valkyrie-content) | Generated application content |
| [valkyrie-signal](#valkyrie-signal) | Terrain-aware signal-coverage experiments |
| [valkyrie-scripts](#valkyrie-scripts) | GTA III SCM inspection |
| [valkyrie-timing](#valkyrie-timing) | Frame-rate measurement analysis |
| [valkyrie-rendering](#valkyrie-rendering) | Matched rendering comparisons |
| [valkyrie-population](#valkyrie-population) | Population and shared-pool analysis |
| [valkyrie-settings](#valkyrie-settings) | INI settings and migration audit |
| [valkyrie-saves](#valkyrie-saves) | Save-block contract audit |
| [valkyrie-capture](#valkyrie-capture) | Scene capture integrity |
| [valkyrie-diagnostics](#valkyrie-diagnostics) | Exact-build address diagnostics |
| [valkyrie-restoration](#valkyrie-restoration) | Restoration evidence catalogue |

## Choose a method

Match your question and exact game/profile to the [reference catalog](workshop/CATALOG.md).
Consult original upstreams, work in your own implementation project, then return
actual results and useful failures through the [finding template](../research/finding-template.md).
Documenting a Valkyrie technique does not make a third-party dependency Valkyrie-owned.

## valkyrie-models

Original engine-evaluated clip conversion is documented in the
[runtime/source-bind findings](../research/dryxio-workflow.md#original-runtime-poses-and-native-source-bindings--2026-10-05).
The public helpers accept supplied matrices and paired rigs; no engine runtime,
APK instrumentation, controller assets or native mod adapter is included.


**Final outcome, 2026-10-05:** The source-animation conversion was abandoned
after failed gameplay. Earlier isolated/native FK checks did not establish
working poses or movement. Read the [failed gameplay findings](../research/dryxio-workflow.md#source-animation-conversion-abandoned-after-failed-gameplay--2026-10-05).
The retained 64-joint builder is experimental. Its stock-parent and native-stack
guards have synthetic coverage; they do not establish a working conversion.

- [sa_hanim_topology.py](../tooling/source/workshop/tools/model-conversion/sa_hanim_topology.py) — stock core parent and 64-node capacity checks
- [test_sa_hanim_topology.py](../tooling/source/workshop/tools/model-conversion/tests/test_sa_hanim_topology.py) — five asset-free structural regressions

**Actual source:**

- [sarw.py](../tooling/source/workshop/deploy/sarw.py) — `workshop/deploy/sarw.py`
- [build_ped_from_glb_blender.py](../tooling/source/workshop/tools/model-conversion/build_ped_from_glb_blender.py) — `workshop/tools/model-conversion/build_ped_from_glb_blender.py`
- [inspect_dff_asset.py](../tooling/source/workshop/tools/model-conversion/inspect_dff_asset.py) — `workshop/tools/model-conversion/inspect_dff_asset.py`
- [inspect_gtav_asset.py](../tooling/source/workshop/tools/model-conversion/inspect_gtav_asset.py) — `workshop/tools/model-conversion/inspect_gtav_asset.py`
- [validate_sa_skin_pose.py](../tooling/source/workshop/tools/model-conversion/validate_sa_skin_pose.py) — `workshop/tools/model-conversion/validate_sa_skin_pose.py`

- [hss_fitting.py](../tooling/source/workshop/tools/model-conversion/hss_fitting.py) — `workshop/tools/model-conversion/hss_fitting.py`
- [test_hss_torso_fit_blender.py](../tooling/source/workshop/tools/model-conversion/tests/test_hss_torso_fit_blender.py) — `workshop/tools/model-conversion/tests/test_hss_torso_fit_blender.py`
- [validate_hss_locomotion_blender.py](../tooling/source/workshop/tools/model-conversion/validate_hss_locomotion_blender.py) — `workshop/tools/model-conversion/validate_hss_locomotion_blender.py`

- [complete_hss_source.py](../tooling/source/workshop/tools/model-conversion/complete_hss_source.py) — caller-supplied wardrobe inputs or synthetic checks
- [extract_hss_hair_placements.py](../tooling/source/workshop/tools/model-conversion/extract_hss_hair_placements.py) — caller-supplied wardrobe inputs or synthetic checks
- [write_hss_txd.py](../tooling/source/workshop/tools/model-conversion/write_hss_txd.py) — caller-supplied wardrobe inputs or synthetic checks
- [rw_texture_names.py](../tooling/source/workshop/tools/model-conversion/rw_texture_names.py) — caller-supplied wardrobe inputs or synthetic checks
- [validate_hss_native.py](../tooling/source/workshop/tools/model-conversion/validate_hss_native.py) — caller-supplied wardrobe inputs or synthetic checks
- [build_hss_hair_colors.py](../tooling/source/workshop/tools/model-conversion/build_hss_hair_colors.py) — caller-supplied wardrobe inputs or synthetic checks
- [tests/test_hair_colors.py](../tooling/source/workshop/tools/model-conversion/tests/test_hair_colors.py) — caller-supplied wardrobe inputs or synthetic checks
- [tests/test_rw_texture_names.py](../tooling/source/workshop/tools/model-conversion/tests/test_rw_texture_names.py) — caller-supplied wardrobe inputs or synthetic checks

Browse commands with `python valkyrie.py list --family valkyrie-models`.
Use an exact ID with `show` or `run`; follow the [runtime guide](../tooling/README.md).

Model conversion and inspection.

**Method:** Inspect source geometry, materials and skeleton; map coordinates and bone influences to the target format; export and reimport before testing the model in-game.

**Inputs to establish:** Permitted model/texture fixtures, source and target format versions, skeleton metadata and authoring dependency revisions.

**Checks to record:** Bone identity, normalized weights and influence limits, UV/material assignments, scale/orientation, format roundtrip and exercised poses.

**Limits:** Conversion scripts include asset-specific assumptions. Blender, DragonFF and Sollumz are external dependencies, not Valkyrie tools.

## valkyrie-world

**Actual source:**

- [test-world3d-index.py](../tooling/source/workshop/deploy/test-world3d-index.py) — `workshop/deploy/test-world3d-index.py`
- [world3d-bounds.py](../tooling/source/workshop/deploy/world3d-bounds.py) — `workshop/deploy/world3d-bounds.py`
- [world3d-index.py](../tooling/source/workshop/deploy/world3d-index.py) — `workshop/deploy/world3d-index.py`
- [world3d-radar-3dpack.py](../tooling/source/workshop/deploy/world3d-radar-3dpack.py) — `workshop/deploy/world3d-radar-3dpack.py`
- [world3d-radar-rasterize.py](../tooling/source/workshop/deploy/world3d-radar-rasterize.py) — `workshop/deploy/world3d-radar-rasterize.py`

Browse commands with `python valkyrie.py list --family valkyrie-world`.
Use an exact ID with `show` or `run`; follow the [runtime guide](../tooling/README.md).

World indexing and map preparation.

**Method:** Index archives and loose overrides using a declared precedence rule; resolve placed models/textures; compute bounds and prepare map outputs from separately supplied inputs.

**Inputs to establish:** Permitted archive/placement fixtures, game profile, coordinate conventions and override rules.

**Checks to record:** Missing references, override precedence, transformed bounds, coordinate mapping, output coverage and deterministic fixture results.

**Limits:** Historical extractors contain expanded-map assumptions. Stock-game compatibility and complete texture coverage must be established per target.

## valkyrie-routes

**Actual source:**

- [audit-radar-route-graph.py](../tooling/source/workshop/deploy/audit-radar-route-graph.py) — `workshop/deploy/audit-radar-route-graph.py`
- [audit-radar-route-surface.py](../tooling/source/workshop/deploy/audit-radar-route-surface.py) — `workshop/deploy/audit-radar-route-surface.py`
- [Join-ValkyrieRadarGraph.ps1](../tooling/source/workshop/deploy/radar-release/Join-ValkyrieRadarGraph.ps1) — `workshop/deploy/radar-release/Join-ValkyrieRadarGraph.ps1`
- [test-roadgraph.py](../tooling/source/workshop/deploy/radar-release/test-roadgraph.py) — `workshop/deploy/radar-release/test-roadgraph.py`

Browse commands with `python valkyrie.py list --family valkyrie-routes`.
Use an exact ID with `show` or `run`; follow the [runtime guide](../tooling/README.md).

Road graphs and navigation audits.

**Method:** Inspect graph headers, nodes and edges; check coordinates and connectivity; prepare the expected navigation payload and compare routes with observed surfaces.

**Inputs to establish:** Permitted graph fixtures, target graph schema, coordinate range and consumer expectations.

**Checks to record:** Header/version, node/link validity, connected components, bounds, payload integrity and separately exercised navigation behavior.

**Limits:** Existing payload joiners are consumer-specific. A structurally valid graph does not prove route quality or runtime compatibility.

## valkyrie-textures

**Actual source:**

- [stage-txd-recompress.py](../tooling/source/workshop/deploy/stage-txd-recompress.py) — `workshop/deploy/stage-txd-recompress.py`
- [txd-merge.py](../tooling/source/workshop/deploy/txd-merge.py) — `workshop/deploy/txd-merge.py`
- [txd2png.py](../tooling/source/workshop/deploy/txd2png.py) — `workshop/deploy/txd2png.py`
- [world3d-texture-audit.py](../tooling/source/workshop/deploy/world3d-texture-audit.py) — `workshop/deploy/world3d-texture-audit.py`

Browse commands with `python valkyrie.py list --family valkyrie-textures`.
Use an exact ID with `show` or `run`; follow the [runtime guide](../tooling/README.md).

Texture dictionary inspection and preparation.

**Method:** Inventory texture names and native formats; inspect decode failures; convert or merge permitted inputs while preserving the target dictionary contract.

**Inputs to establish:** Original/synthetic texture fixtures, RenderWare/native format versions and decoder/converter revisions.

**Checks to record:** Name resolution, dimensions, alpha, mip chains, compression, roundtrip readability and unresolved material references.

**Limits:** Decoder coverage differs by texture format. Conversion success alone does not establish correct lighting, alpha or mip behavior in-game.

## valkyrie-collision

**Actual source:**

- [col-read.py](../tooling/source/workshop/deploy/col-read.py) — `workshop/deploy/col-read.py`
- [dedupe-collision.py](../tooling/source/workshop/deploy/dedupe-collision.py) — `workshop/deploy/dedupe-collision.py`
- [compare-cadb-models.py](../tooling/source/workshop/tools/compare-cadb-models.py) — `workshop/tools/compare-cadb-models.py`
- [inspect-cadb-ray.py](../tooling/source/workshop/tools/inspect-cadb-ray.py) — `workshop/tools/inspect-cadb-ray.py`

Browse commands with `python valkyrie.py list --family valkyrie-collision`.
Use an exact ID with `show` or `run`; follow the [runtime guide](../tooling/README.md).

Collision inspection and comparison.

**Method:** Identify the exact collision/container format; inspect primitives and model coverage; compare visual and collision geometry with controlled queries.

**Inputs to establish:** Permitted collision fixtures, model identifiers, transform conventions and exact container version.

**Checks to record:** Primitive counts, bounds, model-key coverage, transformed ray hits and behavior before any geometry cleanup.

**Limits:** CADB helpers are format-specific, including a v2 comparison. Collision cleanup can change gameplay and needs separate consumer validation.

## valkyrie-animation

**Actual source:**

- [ifp-blocks.py](../tooling/source/workshop/deploy/ifp-blocks.py) — `workshop/deploy/ifp-blocks.py`
- [ifp-motion.py](../tooling/source/workshop/deploy/ifp-motion.py) — `workshop/deploy/ifp-motion.py`
- [ifp-names.py](../tooling/source/workshop/deploy/ifp-names.py) — `workshop/deploy/ifp-names.py`
- [port-manhunt-re3.py](../tooling/source/workshop/deploy/port-manhunt-re3.py) — `workshop/deploy/port-manhunt-re3.py`
- [test-port-manhunt-re3.py](../tooling/source/workshop/deploy/test-port-manhunt-re3.py) — `workshop/deploy/test-port-manhunt-re3.py`

Browse commands with `python valkyrie.py list --family valkyrie-animation`.
Use an exact ID with `show` or `run`; follow the [runtime guide](../tooling/README.md).

Animation inspection and retargeting.

**Method:** Inspect animation blocks and track identities; map skeleton/coordinate conventions; retarget selected tracks while preserving names, ordering and untouched data.

**Inputs to establish:** Permitted animation fixtures, exact IFP variant, source/target skeletons and reference pose.

**Checks to record:** Track identity, frame times, root motion, quaternion/transform conventions, untouched chunks and affected playback scenarios.

**Limits:** Some inspectors have historical local-path defaults; retargeting is target-specific. A readable animation is not proof of correct game playback.

**2026-10-03 packaging validation:** A local GTA III/re3 ANPK conversion was
regenerated with Python 3.11.8 and NumPy 1.26.4. All four synthetic converter
tests passed. The production re3 loader, compression and interpolation were
sampled at 65 points per clip on two character hierarchies: 236 slots retained,
37 converted and 199 byte-identical chunks. The corrected asset passed both
rigs; the known bad root-basis conversion failed 24 pose checks on each rig.
Loader source was supplied from re3 revision
`9a7fa478578beaba947ea867c15a25e411d641d8`. The existing Dryxio authoring catalog
was consulted; no CLEO, map-authoring or runtime-hook tool was needed.

For repeatable asset packaging, validate the exact candidate hash against its
conversion and loader reports before writing. Refuse failed rig results,
missing negative-regression evidence and an existing output. Use stable ZIP
timestamps and entry order, verify every member hash and CRC, then compare two
archive builds. Those checks passed locally, including rejection of deliberately
invalid reports. Include manual backup/restore instructions, source notices and
input provenance; remove local machine paths and omit reference backups,
character assets, rejected files and compiled harnesses. The package remains
a test build: vehicle contacts, collision, transitions and retail GTA III
playback were not verified. Game-derived payloads and mod packaging
implementation remain outside this public library; no mod release or website
deployment was performed by this knowledge contribution.

**2026-10-11 reclining vehicle-pose conversion:** For a GTA III/re3 source host
using Extended engine pin `f8142f1a7cefcfd6bcd778ed8802e21c93b97c91`, locally
supplied SA ANP3 `CAR_Lsit` was retargeted into both III driver-seat slots;
`CAR_sitpLO` supplies both passenger-seat slots. III shares its passenger clips
with front and rear seats, while retaining separate vehicle seat transforms.
Matching steering and low-seat drive-by actions were converted. A reverse-look
action was transferred from the normal SA base onto the reclining base.

The published `workshop/deploy/port-manhunt-re3.py` rig/format method was reused
with its BSD notice. Its SHA-256 remains
`b393a191dce723b15281c0e4c827bef7bec677946e3c96cb8ba09acbc5a18b1f`.
The important corrections for vehicle clips are to use a seated hip origin,
inherit missing action bones from the seated base, and retain rotation-only
waist tracks in partial drive-by animations unless a deliberate positional
adjustment requires translation. Assuming every waist track has translation
changes the native track type even when slot names remain correct.

Eight synthetic regressions passed with Python 3.11.8 and NumPy 1.26.4. The
production loader, compression/decompression and quaternion interpolation
passed at 65 samples per clip on local player and cop DFF hierarchies: all
236 slots retained, eleven clips changed and 225 byte-identical clips. A sampled
side-view hierarchy measured roughly 33 degrees of driver recline and a head
about 6.8 cm lower than the original normal-car pose. These are rig measurements;
rendered vehicle contact, entry/exit and every passenger seat remain unverified.
The locally evaluated importer
uses a separate Mod Loader folder, refuses conflicting dictionary overrides and
leaves original dictionaries/settings/saves intact. No game assets or private
QA receipts enter this library. The Dryxio authoring catalog and
[MTA animation groups](https://wiki.multitheftauto.com/wiki/Animation_Groups)
were consulted; no CLEO or runtime-hook tool was executed for this asset task.


**Subsequent seating-fit evaluation (2026-10-11):** Offline comparisons used
actual locally supplied player and six vehicle meshes (sedan, taxi, two sports
cars and two vans), their front/rear seat frames, and native van seat rotations.
A shared seat-facing adjustment of approximately 10 cm forward and 2.5 cm lower
was evaluated; it does not establish per-vehicle steering-wheel contact.

At the same engine pin, seated association descriptors lack
`ASSOC_HAS_TRANSLATION`. Root XY is therefore retained; velocity extraction
must not be assumed merely because a keyframe has translation. Partial waist
tracks suppress the base contribution even when rotation-only. A deliberate
left drive-by `KR00` to `KRT0` waist promotion keeps the low-seat origin and
positional adjustment during blending, retaining the original bone mask.
The right drive-by waist already has translation. Eleven synthetic regressions
and production loader checks at 65 samples on player/cop rigs passed. All
rotations and non-waist translations match the preceding import; 225 unrelated
clips remain byte-identical. Twenty-one partial blend weights retain the
adjustment within one compressed translation step (1/128 m). Signed truncation
around zero explains residual sub-centimetre differences. Native van rotation
maps forward into the rear-seat aisle. Actual gameplay contact and transitions
remain unverified. Meshes, game-derived dictionaries, private implementation
and local QA receipts remain withheld.

**World/pose composition correction (2026-10-11):** An installed animation
file and a matching receipt do not prove that the current world loads it.
The evaluated alternate-world path bypassed the legacy animation override,
selecting its own complete dictionary. The earlier installation confirmation
therefore missed an activation conflict; the imported pose data was intact.

A bounded layer containing only eleven named vehicle motions now composes with
the dictionary selected by the running world before the production loader builds
associations. Retain the base block header, original slot names/order and every
unrelated motion; replace only the named motion chunks. Validate all chunk bounds,
unique names, frame counts, finite keys and compatible bone masks/types. Reject
the entire layer on incompatibility and preserve the original input. The deliberate
left drive-by waist promotion remains an explicit exception. Honour the layer's
folder profile/priority and log both successful activation and rejection.

The actual local stock and reconstructed-world dictionaries each retained 236
slots. Production loader, compression/decompression and interpolation checks at
65 samples per clip matched all eleven replacements to the reviewed pose pack;
all 225 unrelated animations produced identical samples. A production-module
fixture checked layer discovery, ignored/disabled folders, rewind after rejection,
activation logging and preservation of the original world file. Fourteen importer
regressions and 58 native source fixtures passed. Rendered contacts, seat fit and
entry/exit transitions remain unverified. Original game/world dictionaries,
private runtime implementation and local QA artifacts are withheld.


**Seat-role selection correction (2026-10-11):** Successful layer activation
also does not prove that a passenger uses a passenger clip. In a GTA III/re3
Windows x64 opening-scene fixture, the script-created passenger was bound to
`CAR_sit`, the driver clip. Native traffic spawning and direct warping had the
same selection error. Normal door entry already selected passenger clips.

The corrected source host chooses the passenger animation by occupant role and
normal/low car type while retaining driver and boat selection. Fifteen actual
engine checks passed for normal/low drivers, spawned and warped front/rear
passengers, and the opening script passenger. Three rendered views with the
local eleven-clip layer disabled and enabled confirmed the opening passenger
using `CAR_sitp`, with lowered hands; the imported driver recline remained active.
The imported pose data did not change. Sixty native source fixtures and the
production build/package checks passed.

To reproduce the method with independently permitted inputs, start a separate
opening-scene fixture; record the active association name and blend amount,
semantic bone bindings and final bone positions. Exercise native script creation,
traffic spawning and direct warping for both car heights and front/rear seats.
Capture fixed camera views with the layer disabled and enabled, using separate
saves/settings and an excluded test host. The native fixture and its developer
commands stay in the implementation owner. The existing `valkyrie-animation` family supplies
format/rig inspection methods; `valkyrie-restoration` validates this evidence
record. Neither tool authenticates native gameplay. No converter was rerun for
this selection correction; CLEO and Blender authoring were not applicable.

These checks establish seat-role selection and the rendered opening poses,
not perfect wheel/seat contact, all meshes or entry/exit transitions. Native
implementation, game-derived inputs, captures and local receipts remain outside
Workshop; only this reusable method and bounded result are returned.


**Driver translation evaluation after rendered review (2026-10-11):** Correct clip
selection did not establish correct seat placement. The opening-scene driver
was visibly too low and too far back. A height-only candidate improved one axis
but left backward placement unresolved. The revised import applies a separate
driver waist adjustment across seated, reverse, steering and drive-by motions:
6/128 m forward and 5/128 m upward relative to the preceding pose pack. The
reclined rotations remain unchanged. Both passenger clips and 225 unrelated
clips are byte-identical; only waist Y/Z keys in nine driver clips changed.

Compare original, preceding import and candidate layers in separate native
fixtures before replacing the owned pack. Use the same driver-side camera,
neutral head look, exact local inputs and active association identities. Record
final bones in vehicle axes as well as world coordinates: on a pitched road,
forward motion also changes world height. Check that the driver correction
survives partial-action blending and that passenger placement is unchanged.
Invalidate earlier-payload QA claims when replacing the asset; retain exact
input and candidate hashes. The existing `valkyrie-animation` family covers
format/rig inspection; `valkyrie-restoration` validates the findings record.

Three actual-engine comparisons (original, preceding import and candidate)
passed 15 occupant-role cases each and captured three matching 1280x720 views.
Vehicle-local driver waist shifts measured about 4.69 cm forward and 3.91 cm up;
the pitched-road world height rose about 3.2 cm. Passenger waist differences
were below 0.03 mm. Sixteen importer regressions and the full build with 60 native
source fixtures passed. These captures show the opening driver moved up and
forward while retaining the recline.

The evaluated target is GTA III/re3 Windows x64 with the existing 0.2.134 host.
No game dictionary, capture, native implementation or private receipt is exported.
The follow-up below rejected this translation as a complete seating fix.
Those checks established the applied offset and role selection; physical fit,
wheel contact, all vehicle/character combinations and transitions were not accepted.

**Follow-up seat-surface analysis (2026-10-11):** The owner still observed
backward placement. Exact-input native mesh measurements found torso triangles
crossing the selected front backrest surfaces after the translation. Some body
vertices project inside those triangles with substantially negative clearance.
The original pose and passenger also overlap their seat surfaces, so original
hip height and the passenger's appearance are insufficient fit references.
The active character's semantic bind hierarchy matched the conversion target;
different node array indices did not establish a binding error. No new pose
offset or gameplay payload was installed during this analysis.

Use `valkyrie-animation` for rig, track and pose inspection and
`valkyrie-restoration` for the public findings record. Measure the exact active
car and character meshes, not assumed stock replacements. Export engine-posed
vertices in vehicle coordinates, explicitly identify the near-car atomic and
reviewed seat-face indices, and record input hashes. Render flags can include
alternative LOD atomics; inspect the selected geometry rather than treating
every flagged atomic as the visible surface.

For each selected face, measure signed distance only if the orthogonal
projection is inside its triangle using barycentric bounds. Independently test
noncoplanar body-triangle crossings. Infinite-plane tests and side-view
silhouettes can include points outside a seat; bounded three-dimensional
measurements avoid that error. Surface clearance is not penetration into a
watertight solid. A steering dummy is not the wheel rim.

Evaluate pelvis support, lower-back/torso clearance, roof clearance and hand
placement together. A translation that clears the torso can push the pelvis
past the cushion's front; this rejects another whole-body shift as a complete
repair. A seat-back slope and hip-to-head bone angle are different measurements,
so subtracting them is not a valid corrective joint rotation. Evaluate normal
and low-seat profiles separately, including partial actions and transitions.

Two native opening-scene runs passed fifteen role cases each and produced three
matching views each. The seat-surface analysis confirmed overlap in both the
original and imported poses. Four synthetic geometry checks validated finite
face bounds, triangle crossings, contact/coplanar exclusion and degenerate-face
rejection; sixteen existing importer regressions passed. The excluded native
probe compiled locally. These checks diagnose this frozen pose; a corrected
pose and representative vehicle/character/contact coverage remain unverified.
Python 3.11 and NumPy were used for geometry analysis; Matplotlib rendered the
private diagram. The authoring catalog was consulted, and
`valkyrie-restoration` was executed against the revised public record.
Native implementation, model/animation inputs, derived geometry, plots,
captures and private receipts are withheld. This return updates the existing
animation method; it does not add a public tool family or publish a mod.

## valkyrie-binary

**Actual source:**

- [ExportDecompiled.py](../tooling/source/workshop/deploy/ghidra_scripts/ExportDecompiled.py) — `workshop/deploy/ghidra_scripts/ExportDecompiled.py`
- [name-decompiled.py](../tooling/source/workshop/deploy/name-decompiled.py) — `workshop/deploy/name-decompiled.py`
- [re-sigmatch.py](../tooling/source/workshop/deploy/re-sigmatch.py) — `workshop/deploy/re-sigmatch.py`
- [ssmp-hookmap.py](../tooling/source/workshop/deploy/ssmp-hookmap.py) — `workshop/deploy/ssmp-hookmap.py`
- [ssmp-rpc-map.py](../tooling/source/workshop/deploy/ssmp-rpc-map.py) — `workshop/deploy/ssmp-rpc-map.py`

Browse commands with `python valkyrie.py list --family valkyrie-binary`.
Use an exact ID with `show` or `run`; follow the [runtime guide](../tooling/README.md).

Binary, hook and protocol analysis.

**Method:** Identify the exact target; inventory candidate hooks/interfaces; compare bounded signatures and analysis evidence across matching revisions; label inferred semantics explicitly.

**Inputs to establish:** Independently obtained permitted binaries, SHA-256/size, architecture, load base and analysis-tool revision.

**Checks to record:** VA versus RVA, signature uniqueness, instruction context, interface/version matches and observations versus reconstruction hypotheses.

**Limits:** Existing analyzers target specific binaries. Decompilation and signature matches do not establish semantic equivalence or a complete rebuild.

## valkyrie-pipeline

**Actual source:**

- [check-cleo-workflow.py](../tooling/source/workshop/tools/check-cleo-workflow.py) — `workshop/tools/check-cleo-workflow.py`
- [package-release.py](../tooling/source/workshop/tools/package-release.py) — `workshop/tools/package-release.py`
- [sync-phone.py](../tooling/source/workshop/tools/sync-phone.py) — `workshop/tools/sync-phone.py`
- [test-package-release.py](../tooling/source/workshop/tools/test-package-release.py) — `workshop/tools/test-package-release.py`
- [test-sync-phone.py](../tooling/source/workshop/tools/test-sync-phone.py) — `workshop/tools/test-sync-phone.py`
- [verify-combined-asi.py](../tooling/source/workshop/tools/verify-combined-asi.py) — `workshop/tools/verify-combined-asi.py`

Browse commands with `python valkyrie.py list --family valkyrie-pipeline`.
Use an exact ID with `show` or `run`; follow the [runtime guide](../tooling/README.md).

Build provenance and release verification.

**Method:** Declare reviewed input paths and revisions; detect drift before copying; verify artifact identity, explicit file scope and checksums; record each executed validation gate.

**Inputs to establish:** Project-owned source, reviewed manifests, dependency pins and expected artifact contract.

**Checks to record:** Source revision/dirty state, path scope, expected previous hashes, artifact architecture/resources, archive integrity and separately recorded tests.

**Limits:** Existing sync and artifact checkers are project-specific. These notes are principles, not a supplied universal build system. CLEO AI remains an external tool.

## valkyrie-content

**Actual source:**

- [generate-phone-art.py](../tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/generate-phone-art.py) — `phone/valkyrie-asi-suite/valkyrie-phone/tools/generate-phone-art.py`
- [generate-phone-tones.py](../tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/generate-phone-tones.py) — `phone/valkyrie-asi-suite/valkyrie-phone/tools/generate-phone-tones.py`
- [build-web-pack.py](../tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/iv-web/build-web-pack.py) — `phone/valkyrie-asi-suite/valkyrie-phone/tools/iv-web/build-web-pack.py`
- [whm.py](../tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/iv-web/whm.py) — `phone/valkyrie-asi-suite/valkyrie-phone/tools/iv-web/whm.py`

Browse commands with `python valkyrie.py list --family valkyrie-content`.
Use an exact ID with `show` or `run`; follow the [runtime guide](../tooling/README.md).

Generated application content.

**Method:** Separate procedurally generated art/audio from imported material. Generate original fixtures, declare layout/audio parameters, and prepare a content pack with a manifest of inputs and outputs.

**Inputs to establish:** Original drawings and synthesis parameters or independently permitted source content, font/dependency revisions, output dimensions, sample rate and pack schema.

**Checks to record:** Determinism, image dimensions/alpha, waveform duration/sample rate/clipping, page layout/link regions, pack readability and per-input provenance.

**Limits:** Existing generators mix procedural work with project assets or separately obtained game/web content. Documentation does not authorize redistribution of those inputs or resulting packs. The general method can be reproduced with original fixtures.

**Review evidence:** Source/documentation review of existing generators; no generation, fetching, playback or runtime test executed in this review.

## valkyrie-signal

**Actual source:**

- [build_heightmap.py](../tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/signal-coverage/build_heightmap.py) — `phone/valkyrie-asi-suite/valkyrie-phone/tools/signal-coverage/build_heightmap.py`
- [coverage.py](../tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/signal-coverage/coverage.py) — `phone/valkyrie-asi-suite/valkyrie-phone/tools/signal-coverage/coverage.py`
- [find_masts.py](../tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/signal-coverage/find_masts.py) — `phone/valkyrie-asi-suite/valkyrie-phone/tools/signal-coverage/find_masts.py`

Browse commands with `python valkyrie.py list --family valkyrie-signal`.
Use an exact ID with `show` or `run`; follow the [runtime guide](../tooling/README.md).

Terrain-aware signal-coverage experiments.

**Method:** Rasterize permitted terrain geometry to a height grid, declare transmitter positions/heights and sampling rules, then estimate a coverage grid under explicitly recorded propagation and obstacle assumptions.

**Inputs to establish:** Original/synthetic terrain and mast fixtures, grid bounds/resolution, units, missing-data handling, antenna/receiver heights, frequency and model parameters.

**Checks to record:** Coordinate alignment, empty/missing tiles, interpolation and sampling, repeatability, sensitivity to heights/obstacles, and declared mapping from estimated loss to display bands.

**Limits:** The existing study has historical map extents, terrain fallbacks and fixed display thresholds. It is an experimental approximation, not measured radio coverage or proof of integration into a game feature. The synthetic demo checks repeatability, not measured reception or integrated gameplay.

**Review evidence:** Source/documentation review of the historical experiment; no terrain processing, propagation calculation or gameplay test executed in this review.

## Run the published tools

Actual source is in [tooling/source/](../tooling/source/). The original ten families
group existing entry points; nine standalone commands also run by their stable name.

```powershell
python valkyrie.py list --family valkyrie-collision
python valkyrie.py show workshop/tools/compare-cadb-models.py
python valkyrie.py run workshop/tools/compare-cadb-models.py -- OLD.cadb NEW.cadb
python valkyrie.py demo valkyrie-content
python valkyrie.py demo valkyrie-signal
```

Install example dependencies from `tooling/requirements.txt` in your chosen
Python environment. See [setup, expected outputs and portability](../tooling/README.md).
Source publication includes helpers and project adapters; it does not imply
that every historical default is portable or every required input is bundled.
Read scripts before running commands that modify installations or data.

## Public scope and follow-up

The ten original families, nine standalone tools and their required helpers are public. New runnable
examples should record exact inputs, outputs, actual checks and limitations.
Mod implementation, mod releases, game/web payloads and private data remain
excluded. Source mappings are public for these tools; the wider private product
inventory remains in the workspace index. No private Git history is imported.

## valkyrie-scripts

**Use:** Decode supplied SCM sections, typed arguments and exact instruction branches.

**Inputs:** SCM and independently established gta3 opcode schema.

**Checks:** Bounded section reads, fixed-point arguments and branch instruction boundaries.

**Limits:** No execution, schema discovery or missing mission recovery.

[Commands and contract](VALKYRIE-DEVELOPMENT-TOOLS.md#valkyrie-scripts) · [Actual source](../tooling/source/workshop/tools/gta3/valkyrie_scripts.py) · [Findings](../research/gta3-native-methods-2026-10-11.md)

Run `python valkyrie.py show valkyrie-scripts` and
`python valkyrie.py demo valkyrie-scripts`.

## valkyrie-timing

**Use:** Compare equal-time traces across frame rates with declared units and tolerances.

**Inputs:** CSV scenario/metric/unit/FPS/time/value traces.

**Checks:** Matching intervals, unique timestamps, interpolation and per-sample error.

**Limits:** Sparse measurements can miss events; no engine run or applied fix.

[Commands and contract](VALKYRIE-DEVELOPMENT-TOOLS.md#valkyrie-timing) · [Actual source](../tooling/source/workshop/tools/gta3/valkyrie_timing.py) · [Findings](../research/gta3-native-methods-2026-10-11.md)

Run `python valkyrie.py show valkyrie-timing` and
`python valkyrie.py demo valkyrie-timing`.

## valkyrie-rendering

**Use:** Measure image differences under explicitly matched or allowed comparison conditions.

**Inputs:** Two images and target/renderer/scene/camera/time metadata.

**Checks:** Dimensions, metadata drift, pixel error and changed fraction.

**Limits:** No visual quality, activation, occlusion or authenticity verdict.

[Commands and contract](VALKYRIE-DEVELOPMENT-TOOLS.md#valkyrie-rendering) · [Actual source](../tooling/source/workshop/tools/gta3/valkyrie_rendering.py) · [Findings](../research/gta3-native-methods-2026-10-11.md)

Run `python valkyrie.py show valkyrie-rendering` and
`python valkyrie.py demo valkyrie-rendering`.

## valkyrie-population

**Use:** Summarize near/far entities and shared walker/driver reserve pressure.

**Inputs:** Measured population CSV and exact capacities/reserve.

**Checks:** Feasible counts, unique times, means and free-slot pressure.

**Limits:** Pressure is a diagnostic lead, not proven spawn rejection or visibility.

[Commands and contract](VALKYRIE-DEVELOPMENT-TOOLS.md#valkyrie-population) · [Actual source](../tooling/source/workshop/tools/gta3/valkyrie_population.py) · [Findings](../research/gta3-native-methods-2026-10-11.md)

Run `python valkyrie.py show valkyrie-population` and
`python valkyrie.py demo valkyrie-population`.

## valkyrie-settings

**Use:** Audit declared INI value contracts, defaults and unrelated preservation.

**Inputs:** Before/after INIs and typed setting rules.

**Checks:** Duplicate rejection, existing-value preservation, defaults and allowed changes.

**Limits:** No native menu, device reset or live loader behavior is exercised.

[Commands and contract](VALKYRIE-DEVELOPMENT-TOOLS.md#valkyrie-settings) · [Actual source](../tooling/source/workshop/tools/gta3/valkyrie_settings.py) · [Findings](../research/gta3-native-methods-2026-10-11.md)

Run `python valkyrie.py show valkyrie-settings` and
`python valkyrie.py demo valkyrie-settings`.

## valkyrie-saves

**Use:** Validate exact input identity, profile and independently declared serialized blocks.

**Inputs:** Local save and block/profile/hash contract.

**Checks:** Bounds, nonoverlap, expected sizes and uninspected bytes.

**Limits:** No save decoder, repair, conversion or native loading claim.

[Commands and contract](VALKYRIE-DEVELOPMENT-TOOLS.md#valkyrie-saves) · [Actual source](../tooling/source/workshop/tools/gta3/valkyrie_saves.py) · [Findings](../research/gta3-native-methods-2026-10-11.md)

Run `python valkyrie.py show valkyrie-saves` and
`python valkyrie.py demo valkyrie-saves`.

## valkyrie-capture

**Use:** Verify ordered image frames, non-silent PCM duration and declared events.

**Inputs:** Capture manifest, relative image frames and PCM WAV.

**Checks:** Dimensions, duration within one sample, hashes and event bounds.

**Limits:** No recording/encoding, audio-origin proof or native event authentication.

[Commands and contract](VALKYRIE-DEVELOPMENT-TOOLS.md#valkyrie-capture) · [Actual source](../tooling/source/workshop/tools/gta3/valkyrie_capture.py) · [Findings](../research/gta3-native-methods-2026-10-11.md)

Run `python valkyrie.py show valkyrie-capture` and
`python valkyrie.py demo valkyrie-capture`.

## valkyrie-diagnostics

**Use:** Resolve loaded addresses against supplied exact-build image and symbol ranges.

**Inputs:** Crash JSON, symbol RVA/size/name CSV and symbol target SHA-256.

**Checks:** Target identity, image bounds, range overlap and full 64-bit precision.

**Limits:** No PDB/minidump decoding, guessed function extent or root-cause proof.

[Commands and contract](VALKYRIE-DEVELOPMENT-TOOLS.md#valkyrie-diagnostics) · [Actual source](../tooling/source/workshop/tools/gta3/valkyrie_diagnostics.py) · [Findings](../research/gta3-native-methods-2026-10-11.md)

Run `python valkyrie.py show valkyrie-diagnostics` and
`python valkyrie.py demo valkyrie-diagnostics`.

## valkyrie-restoration

**Use:** Validate and search evidence categories, source references and recorded limits.

**Inputs:** Structured records and permitted relative files/public HTTPS references.

**Checks:** Unique IDs, explicit classifications, nonempty evidence and reference hashes.

**Limits:** No URL fetch, authenticity assessment or promotion of validation status.

[Commands and contract](VALKYRIE-DEVELOPMENT-TOOLS.md#valkyrie-restoration) · [Actual source](../tooling/source/workshop/tools/gta3/valkyrie_restoration.py) · [Findings](../research/gta3-native-methods-2026-10-11.md)

Run `python valkyrie.py show valkyrie-restoration` and
`python valkyrie.py demo valkyrie-restoration`.
