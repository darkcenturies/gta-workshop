# Standalone Valkyrie development tools

Nine independently runnable tools package reusable GTA III development methods.
They complement the ten original authoring/analysis families. Each stable
`valkyrie-*` command identifies one primary entry in the
[registry](../tooling/registry.json); exact historical registry IDs still work.
The associated [findings](../research/gta3-native-methods-2026-10-11.md) explain
the failures, provenance and evidence limits behind these tools.

## Setup and report contract

Use Python 3.11+. Rendering and capture need Pillow; install the existing
`tooling/requirements.txt` for all examples. Other new commands use the standard
library. No engine checkout, game installation, network connection or game
payload is needed for their synthetic demonstrations.

```powershell
python valkyrie.py list --family valkyrie-timing
python valkyrie.py show valkyrie-timing
python valkyrie.py demo valkyrie-timing --output work/development-demos
python valkyrie.py run valkyrie-timing -- work/development-demos/valkyrie-timing/timing.csv
```

Each tool accepts `--output NEW_REPORT.json`. Omit it for JSON on stdout.
Reports use schema version 1 and explicitly set
`gameplay_tested_by_this_tool: false`. Inputs are read-only; output files are
created exclusively and never overwrite existing reports. Demos also require
an unused output subdirectory. Exit 0 means the supported operation completed;
exit 1 means invalid input/dependency/output, and exit 2 means a completed
contract check reported failure. A successful measurement report is not a
claim that the game feature works. External URL references are not fetched.

Inspect these files before publishing reports: script strings, symbol names,
INI values and reference URLs can originate in private inputs. The tools do
not automatically sanitize user reports or authorize publishing supplied data.

## valkyrie-scripts

**Use:** decode supported GTA III SCM main/mission sections, arguments and
branch destinations using an independently established opcode schema.

```powershell
python valkyrie.py run valkyrie-scripts -- INPUT.scm --schema OPCODES.json --output script-report.json
```

Schema: `profile: "gta3"` and `opcodes`, mapping decimal or `0x` opcode strings
to `{name, args}`. Argument kinds are `value` (tagged literal/variable), `text`
(eight-byte ASCII label), and `tail` (zero-terminated tagged arguments, last).
An optional `branch_arg` identifies an integer argument whose destination must
be an instruction in the same section. Negative destinations are relative to
the current section start using III's `start - value` convention.

Output contains section bounds, instructions, argument offsets, negation and
the input hash. Input is capped at 64 MiB. Unknown opcodes, truncated fields,
out-of-section reads and non-instruction branches fail. Tag 6 is signed
16-bit fixed point divided by 16. The tool does not execute scripts, ship an
engine schema, support every SCM variant or recover missing mission content.

## valkyrie-timing

**Use:** find differences in measurement traces across frame rates over equal
elapsed time. Supply CSV columns `scenario,metric,unit,fps,time_s,value`.

```powershell
python valkyrie.py run valkyrie-timing -- measurements.csv --baseline-fps 30 --absolute-tolerance 0.001 --relative-tolerance 0.001
```

Every scenario/metric/unit requires at least two unique timestamps at the
baseline and another rate, with matching start/end times. The tool linearly
interpolates candidate traces at baseline timestamps and reports maximum
absolute error and failed samples. Tolerance is absolute plus relative times
the absolute baseline value. Caller-supplied sampling can miss short events;
units, adequate sampling and native measurement provenance remain the caller's
responsibility. This analyzer does not run the engine or apply an FPS fix.

## valkyrie-rendering

**Use:** measure image differences while guarding comparison conditions.

```powershell
python valkyrie.py run valkyrie-rendering -- reference.png candidate.png --reference-meta reference.json --candidate-meta candidate.json --allow-condition lighting
```

Both metadata files require `target_revision`, `renderer`, `scene`, `camera`
and `time_s`. All metadata differences must be explicitly allowed with repeated
`--allow-condition KEY`. Images must have equal dimensions. Output gives RGB
mean absolute error, changed-pixel fraction and explicitly permitted condition
changes. `--pixel-threshold` selects a 0–255 per-channel difference threshold.
Alpha is composited against the same black background for both images.
No quality score, effect-activation verdict or authenticity claim is generated.

## valkyrie-population

**Use:** summarize walkers, occupants, vehicles and near/far counts; identify
shared pedestrian-pool reserve pressure while vehicle slots remain available.

```powershell
python valkyrie.py run valkyrie-population -- population.csv --ped-capacity 140 --vehicle-capacity 110 --ped-reserve 10
```

CSV columns: `scenario,time_s,walkers,occupants,vehicles,near_vehicles,far_vehicles,near_walkers,far_walkers`.
Counts are nonnegative integers; walkers plus occupants share the declared ped
capacity. Near/far counts cannot exceed their respective totals. Reports contain
per-scenario means, minimum free ped slots and reserve-pressure sample counts.
Use capacities measured for your exact target. Pressure is a diagnostic lead;
the tool does not establish spawn rejection, visibility or frame-time cost.

## valkyrie-settings

**Use:** check INI values, expected migrations and unrelated-value preservation.

```powershell
python valkyrie.py run valkyrie-settings -- before.ini after.ini --rules rules.json
```

Rules contain `settings: [{section,key,type,default,...}]`. Types are `bool`,
`int`, `float`, `string`; numeric bounds use `min`/`max`, and optional `choices`
restrict values. Optional `restart_required` is reported, not enacted. Section
names are case-sensitive; keys are case-insensitive. Duplicate sections/keys
and DEFAULT inheritance are rejected rather than guessing loader precedence.
Existing valid values must survive; missing/invalid old values use the declared
default. Unrelated changes fail unless allowed with
`--allow-change Section.lowercasekey`. `--expect-defaults` checks listed defaults.
No file is edited and no native menu or device reset is exercised.

## valkyrie-saves

**Use:** reject mismatched profile, input identity, overlapping blocks and
incorrect serialized block lengths against an independently established contract.

```powershell
python valkyrie.py run valkyrie-saves -- INPUT.save --contract blocks.json --profile stock
```

Contract: `profile`, `input_sha256`, `blocks: [{name,offset,size,expected_size}]`.
All blocks must be named, nonoverlapping and within the supplied file. Reports
include unchecked byte count and actual/expected sizes. Profiles and offsets
come from the caller's exact save-format investigation: this is a contract
auditor, not an automatic save decoder, repairer or converter. A valid contract
cannot establish that native loading or the full save/load flow works.

## valkyrie-capture

**Use:** validate ordered image captures, synchronized PCM duration and declared
scene-event positions before external video encoding.

```powershell
python valkyrie.py run valkyrie-capture -- capture.json --root capture-inputs
```

Manifest: `fps,width,height,frames` (ordered relative image paths), `audio`
(relative uncompressed WAV), and optional `events: [{frame,type,provenance}]`.
Frame numbering is zero-based. Images must match declared dimensions; mono or
stereo PCM must be non-silent and match frame duration within one audio sample.
Reports include input hashes, timing error and event timestamps. Relative paths
cannot escape the supplied root. This tool does not record, encode or delete
media, independently identify audio origin, or prove declared native events.

## valkyrie-diagnostics

**Use:** map exact-build crash addresses to supplied symbol ranges without
guessing function extents or confusing loaded VA with image-relative RVA.

```powershell
python valkyrie.py run valkyrie-diagnostics -- crash.json --symbols symbols.csv --target-sha256 TARGET_HASH
```

Crash JSON: `target_sha256,image_base,image_size,addresses`. Addresses accept
integers or decimal/`0x` strings. Symbol CSV: `rva,size,name`, with independently
established nonoverlapping ranges. `--target-sha256` identifies the symbol target
and must match the crash target. Out-of-image/uncovered addresses remain
unresolved. Full 64-bit addresses are preserved. No minidump/PDB decoder, live
hook, guessed nearest-symbol match or automatic root-cause claim is included.

## valkyrie-restoration

**Use:** validate evidence records and search/filter a restoration catalogue.

```powershell
python valkyrie.py run valkyrie-restoration -- research/gta3-public-findings.json --root . --search timing
```

Each record requires `id,title,target,observation,limitations,kind,validation`
and nonempty `sources`. Sources are relative `path` references, hashed by the
tool, or public HTTPS `url` references, recorded without fetching them.
Kinds: `recovered-asset`, `retained-code`, `platform-difference`,
`upstream-feature`, `documented-proposal`, `authored-reconstruction`, `unsupported`.
Validation: `not-tested`, `inspected`, `synthetic-tested`, `native-tested`,
`gameplay-tested`, `failed`. IDs are unique; `--kind` and `--search` filter output
after validating the complete catalogue. The tool preserves supplied validation
labels and never authenticates or promotes them. The included catalogue records
this contribution's source/documentation inspection, not newly executed game tests.

## Reproduce the tool checks

```powershell
python -m unittest discover -s tooling/source/workshop/tools/gta3/tests -v
python valkyrie.py demo valkyrie-scripts --output work/development-demos
python valkyrie.py demo valkyrie-rendering --output work/development-demos
python valkyrie.py demo valkyrie-population --output work/development-demos
python valkyrie.py demo valkyrie-settings --output work/development-demos
python valkyrie.py demo valkyrie-saves --output work/development-demos
python valkyrie.py demo valkyrie-capture --output work/development-demos
python valkyrie.py demo valkyrie-diagnostics --output work/development-demos
python valkyrie.py demo valkyrie-restoration --output work/development-demos
```

The timing demo appears in Setup above. Each demo creates original toy inputs
and executes its actual tool entry point. Tests include malformed input, report
preservation, mismatched targets/conditions, lost settings, pool pressure,
timing drift, save overlap, audio duration and evidence-category boundaries.
Game assets, native hosts, live logs and installation receipts remain excluded.
