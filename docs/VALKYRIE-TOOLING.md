# Valkyrie tool methods

Eight named method families drawn from existing GTA tooling. These public notes
explain reusable techniques and validation questions; authored implementations
remain outside the library. The names are documentation namespaces, not
downloadable applications, CLI commands or newly released tools.

**Reviewed 2026-10-01:** source/documentation inventory only. No tool was executed
or freshly gameplay-tested for this review. Existing scripts include historical
assumptions; examples below describe a method, not a completed experiment.

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

## Choose a method

Match your question and exact game/profile to the [reference catalog](workshop/CATALOG.md).
Consult original upstreams, work in your own implementation project, then return
actual results and useful failures through the [finding template](../research/finding-template.md).
Documenting a Valkyrie technique does not make a third-party dependency Valkyrie-owned.

## valkyrie-models

Model conversion and inspection.

**Method:** Inspect source geometry, materials and skeleton; map coordinates and bone influences to the target format; export and reimport before testing the model in-game.

**Inputs to establish:** Permitted model/texture fixtures, source and target format versions, skeleton metadata and authoring dependency revisions.

**Checks to record:** Bone identity, normalized weights and influence limits, UV/material assignments, scale/orientation, format roundtrip and exercised poses.

**Limits:** Conversion scripts include asset-specific assumptions. Blender, DragonFF and Sollumz are external dependencies, not Valkyrie tools.

## valkyrie-world

World indexing and map preparation.

**Method:** Index archives and loose overrides using a declared precedence rule; resolve placed models/textures; compute bounds and prepare map outputs from separately supplied inputs.

**Inputs to establish:** Permitted archive/placement fixtures, game profile, coordinate conventions and override rules.

**Checks to record:** Missing references, override precedence, transformed bounds, coordinate mapping, output coverage and deterministic fixture results.

**Limits:** Historical extractors contain expanded-map assumptions. Stock-game compatibility and complete texture coverage must be established per target.

## valkyrie-routes

Road graphs and navigation audits.

**Method:** Inspect graph headers, nodes and edges; check coordinates and connectivity; prepare the expected navigation payload and compare routes with observed surfaces.

**Inputs to establish:** Permitted graph fixtures, target graph schema, coordinate range and consumer expectations.

**Checks to record:** Header/version, node/link validity, connected components, bounds, payload integrity and separately exercised navigation behavior.

**Limits:** Existing payload joiners are consumer-specific. A structurally valid graph does not prove route quality or runtime compatibility.

## valkyrie-textures

Texture dictionary inspection and preparation.

**Method:** Inventory texture names and native formats; inspect decode failures; convert or merge permitted inputs while preserving the target dictionary contract.

**Inputs to establish:** Original/synthetic texture fixtures, RenderWare/native format versions and decoder/converter revisions.

**Checks to record:** Name resolution, dimensions, alpha, mip chains, compression, roundtrip readability and unresolved material references.

**Limits:** Decoder coverage differs by texture format. Conversion success alone does not establish correct lighting, alpha or mip behavior in-game.

## valkyrie-collision

Collision inspection and comparison.

**Method:** Identify the exact collision/container format; inspect primitives and model coverage; compare visual and collision geometry with controlled queries.

**Inputs to establish:** Permitted collision fixtures, model identifiers, transform conventions and exact container version.

**Checks to record:** Primitive counts, bounds, model-key coverage, transformed ray hits and behavior before any geometry cleanup.

**Limits:** CADB helpers are format-specific, including a v2 comparison. Collision cleanup can change gameplay and needs separate consumer validation.

## valkyrie-animation

Animation inspection and retargeting.

**Method:** Inspect animation blocks and track identities; map skeleton/coordinate conventions; retarget selected tracks while preserving names, ordering and untouched data.

**Inputs to establish:** Permitted animation fixtures, exact IFP variant, source/target skeletons and reference pose.

**Checks to record:** Track identity, frame times, root motion, quaternion/transform conventions, untouched chunks and affected playback scenarios.

**Limits:** Some inspectors have historical local-path defaults; retargeting is target-specific. A readable animation is not proof of correct game playback.

## valkyrie-binary

Binary, hook and protocol analysis.

**Method:** Identify the exact target; inventory candidate hooks/interfaces; compare bounded signatures and analysis evidence across matching revisions; label inferred semantics explicitly.

**Inputs to establish:** Independently obtained permitted binaries, SHA-256/size, architecture, load base and analysis-tool revision.

**Checks to record:** VA versus RVA, signature uniqueness, instruction context, interface/version matches and observations versus reconstruction hypotheses.

**Limits:** Existing analyzers target specific binaries. Decompilation and signature matches do not establish semantic equivalence or a complete rebuild.

## valkyrie-pipeline

Build provenance and release verification.

**Method:** Declare reviewed input paths and revisions; detect drift before copying; verify artifact identity, explicit file scope and checksums; record each executed validation gate.

**Inputs to establish:** Project-owned source, reviewed manifests, dependency pins and expected artifact contract.

**Checks to record:** Source revision/dirty state, path scope, expected previous hashes, artifact architecture/resources, archive integrity and separately recorded tests.

**Limits:** Existing sync and artifact checkers are project-specific. These notes are principles, not a supplied universal build system. CLEO AI remains an external tool.

## Public scope and follow-up

Available now: these method notes, reference routes and validation questions.
Future examples require permitted synthetic/original fixtures and actual
recorded outputs. None are claimed executed by this inventory.
Project-specific content generation and historical terrain/signal experiments
are deferred pending provenance and reproducibility review; they are not public
tool entries. Source mappings and the complete internal inventory stay private.
No authored tools, game payloads, content packs or release packages are added.
Read [publication policy](../PUBLICATION.md) and [coverage/backlog](workshop/PUBLICATION-BACKLOG.md).
