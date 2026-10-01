# Worked reference routes

The synthetic tool examples below have executed checks. The later project routes
explain methods and do not claim newly executed builds or gameplay tests. Consult [the catalog](CATALOG.md) and
[agent requirements](../../AGENTS.md).

## Run public tools with synthetic inputs

From the workshop root, use Python 3.11+ and the example dependencies:

```powershell
python -m pip install -r tooling/requirements.txt
python valkyrie.py demo valkyrie-collision
python valkyrie.py demo valkyrie-content
python valkyrie.py demo valkyrie-signal
```

| Executed route | Published functions exercised | Expected result |
| --- | --- | --- |
| Collision comparison | [CADB comparison](../../tooling/source/workshop/tools/compare-cadb-models.py) | Synthetic old models 1/2 and new 2/3: missing 1, added 3 |
| Original content generation | [Tone generator](../../tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/generate-phone-tones.py) | 22050 Hz mono WAV, original 64×64 icon and metadata |
| Signal estimation | [Coverage model](../../tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/signal-coverage/coverage.py) | Repeatable 8×8 loss grid with 59 finite cells and metadata |

Outputs go under ignored `work/demos/`. These run published helper functions via
[the example harness](../../tooling/examples.py), without game inputs. Signal
repeatability is not measured radio accuracy or integrated gameplay validation.
See [setup and portability](../../tooling/README.md) for dependencies and limits.
For every other family, follow [the routing table](../GTA-SA-MOD-WORKFLOW.md#select-and-run-public-tools),
then `list`, `show` and the source's supported runtime recipe.

## Add a scripted interaction

Define the exact GTA SA/CLEO profile and a minimal interaction. Read CLEO AI
and opcode/library references. Check supported opcodes and required runtime,
validate and compile in your script project, then exercise the behavior in the
target game. Return the method, actual outputs, tested scenarios and failures.
Record whether CLEO AI was actually used; do not infer use from a citation.
Consult [valkyrie-pipeline](../VALKYRIE-TOOLING.md#valkyrie-pipeline) for
profile/workflow checks when its expected project structure applies.

## Investigate a native crash

Record executable hash, architecture, crash location and reproduction. Consult
SDK/engine references and bounded binary evidence. Use
[valkyrie-binary](../VALKYRIE-TOOLING.md#valkyrie-binary) for applicable mapping
and signature evidence, then [valkyrie-pipeline](../VALKYRIE-TOOLING.md#valkyrie-pipeline)
for relevant build/package checks in the separate project. Check signatures, calling
conventions and layouts before implementing a focused fix in your plugin repo.
Report compilation, fixture tests and gameplay separately. Publish safe evidence
and reasoning without exporting restricted logs or implementation.

## Change a map or traffic route

Choose authoring references for the exact game/file format. Route world indexes
to [valkyrie-world](../VALKYRIE-TOOLING.md#valkyrie-world), navigation to
[valkyrie-routes](../VALKYRIE-TOOLING.md#valkyrie-routes), and associated assets to
[valkyrie-models](../VALKYRIE-TOOLING.md#valkyrie-models),
[valkyrie-textures](../VALKYRIE-TOOLING.md#valkyrie-textures),
[valkyrie-collision](../VALKYRIE-TOOLING.md#valkyrie-collision) or
[valkyrie-animation](../VALKYRIE-TOOLING.md#valkyrie-animation) as needed. Use an original or
permitted synthetic fixture to document import, edit and export. Check a
deterministic roundtrip and graph/format integrity, then loading and behavior
in the game separately. Return revisions, provenance and observed limits;
do not upload game-derived asset payloads.

## Study a multiplayer interface

Choose matching client/server versions and relevant source/documentation.
Compare protocol observations with bounded archived evidence and applicable
[valkyrie-binary mapping tools](../VALKYRIE-TOOLING.md#valkyrie-binary). Reproduce with
synthetic inputs, distinguish byte-level matches from inferred semantics and
record incompatible cases. Keep player/account and operational data excluded.

## Compare graphics or navigation behavior

Read graphics/GPS/radar references and original fork parents. Use
[valkyrie-routes](../VALKYRIE-TOOLING.md#valkyrie-routes) for graph evidence,
[valkyrie-textures](../VALKYRIE-TOOLING.md#valkyrie-textures) for texture audits,
[valkyrie-content](../VALKYRIE-TOOLING.md#valkyrie-content) for original content
methods and [valkyrie-signal](../VALKYRIE-TOOLING.md#valkyrie-signal) for coverage
experiments when those are part of the question. Record game target,
mod combination, configuration and measurement method. Compare only scenarios
actually exercised, including performance or device/reset behavior where
relevant. Publish reproducible observations and dependency limits, not assumed
compatibility across all profiles.
