# Valkyrie tool methods

Ten named tool families with **45 published source/helper files**. Browse the
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

## Choose a method

Match your question and exact game/profile to the [reference catalog](workshop/CATALOG.md).
Consult original upstreams, work in your own implementation project, then return
actual results and useful failures through the [finding template](../research/finding-template.md).
Documenting a Valkyrie technique does not make a third-party dependency Valkyrie-owned.

## valkyrie-models

**Actual source:**

- [sarw.py](../tooling/source/workshop/deploy/sarw.py) — `workshop/deploy/sarw.py`
- [build_ped_from_glb_blender.py](../tooling/source/workshop/tools/model-conversion/build_ped_from_glb_blender.py) — `workshop/tools/model-conversion/build_ped_from_glb_blender.py`
- [inspect_dff_asset.py](../tooling/source/workshop/tools/model-conversion/inspect_dff_asset.py) — `workshop/tools/model-conversion/inspect_dff_asset.py`
- [inspect_gtav_asset.py](../tooling/source/workshop/tools/model-conversion/inspect_gtav_asset.py) — `workshop/tools/model-conversion/inspect_gtav_asset.py`
- [validate_sa_skin_pose.py](../tooling/source/workshop/tools/model-conversion/validate_sa_skin_pose.py) — `workshop/tools/model-conversion/validate_sa_skin_pose.py`

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

**Limits:** The existing study has historical map extents, terrain fallbacks and fixed display thresholds. It is an experimental approximation, not measured radio coverage or proof of integration into a game feature. Synthetic reproduction is a proposed next experiment, not a completed test.

**Review evidence:** Source/documentation review of the historical experiment; no terrain processing, propagation calculation or gameplay test executed in this review.
## Run the published tools

Actual source is in [tooling/source/](../tooling/source/). The ten family names
group existing entry points; the launcher runs an exact registry ID.

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

These ten families and their required helper code are public. New runnable
examples should record exact inputs, outputs, actual checks and limitations.
Mod implementation, mod releases, game/web payloads and private data remain
excluded. Source mappings are public for these tools; the wider private product
inventory remains in the workspace index. No private Git history is imported.
