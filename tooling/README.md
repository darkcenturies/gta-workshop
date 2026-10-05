# Public Valkyrie tools

Actual tool source is in [source/](source/). The [registry](registry.json) lists
every entry point, family, runtime, imports, detected effects and source hashes.
Preserved upstream/repository licenses are beside each source collection;
external dependencies retain their own terms and are not vendored here.

## Find and run a tool

Python 3.11+ is used for the launcher and verified examples:

```powershell
python valkyrie.py list
python valkyrie.py list --family valkyrie-models
python valkyrie.py list --search collision
python valkyrie.py show workshop/tools/compare-cadb-models.py
python valkyrie.py run workshop/tools/compare-cadb-models.py -- OLD.cadb NEW.cadb
```

The launcher uses the caller's current directory and forwards arguments to the
selected source. It never installs dependencies or runs an entry merely to list
it. `show` exposes dependencies and detected effects; read the script for its
complete input/output contract. There are no bundled game inputs or mod binaries.

## Runnable examples without game inputs

Use your chosen Python environment, install the two example dependencies, then:

```powershell
python -m pip install -r tooling/requirements.txt
python valkyrie.py demo valkyrie-collision
python valkyrie.py demo valkyrie-content
python valkyrie.py demo valkyrie-signal
```

| Example | Expected result under ignored `work/demos/` |
| --- | --- |
| Collision | Two synthetic CADB files; missing model 1, added model 3 |
| Content | Original 64×64 icon, mono 22050 Hz WAV and result metadata |
| Signal | Repeatable 8×8 estimated-loss grid and metadata using synthetic terrain |

These examples execute the published helper functions. They do not use games,
fetch websites, install content, measure real radio reception or deploy anything.
Other authoring/analysis tools require separately obtained permitted inputs.

## Continuous torso fitting and locomotion checks

The `valkyrie-models` entries include [hss_fitting.py](source/workshop/tools/model-conversion/hss_fitting.py),
its [synthetic regression](source/workshop/tools/model-conversion/tests/test_hss_torso_fit_blender.py)
and a [paired DFF/IFP sampler](source/workshop/tools/model-conversion/validate_hss_locomotion_blender.py).
The helper preserves a continuous rest surface across torso weight regions,
while fitting limbs to the donor joint frames. It expects globally aligned
points and the exact SA bone names shown in the source; it does not transfer
weights, export a model or change animation bindings.

Run the regression in Blender, from the repository root:

```powershell
blender --background --factory-startup --python-exit-code 1 --python tooling/source/workshop/tools/model-conversion/tests/test_hss_torso_fit_blender.py
```

The sampler requires separately installed INU_tools; both DFF and IFP must use
that importer's coordinate convention. Supply permitted local models and clips:

```powershell
blender --background --factory-startup --python-exit-code 1 --python tooling/source/workshop/tools/model-conversion/validate_hss_locomotion_blender.py -- MODEL_DIR PED_IFP OUTPUT_JSON
```

This retained sampler selects `hss_*.dff`; an optional fourth argument selects
comma-separated stems within that pattern. An optional fifth argument supplies comma-separated
clip names (for example `idle_stance,walk_civi,run_civi`). It defaults to `woman_idlestance`,
`woman_walknorm` and `woman_run` at four times each, reports edge stretch and
checks finite geometry and an upright height between one and three units.
Those assumptions suit the evaluated conversions; inspect them before adapting
it to another naming convention, stature or animation set. Its output expressly
records `gameplay_tested: false`. The Blender entries are listed as host scripts;
the Python launcher does not execute Blender for you. No input models or clips
are bundled. See the [dated findings](../research/dryxio-workflow.md#continuous-torso-fitting-after-an-in-game-proportion-report-2026-10-04).

## Wardrobe coverage, face aliases and hair palettes

The additional `valkyrie-models` helpers recover skinned/static renderer
references, authored attachment roots and managed face-component fields from
caller-supplied Unity assets. `complete_hss_source.py` augments an existing
extraction manifest with source provenance and resolved fitting-base bones;
it is not an APK-to-finished-skin pipeline. UnityPy 1.25.4 and
TypeTreeGeneratorAPI 0.0.10 were evaluated with separately supplied managed
assemblies. `extract_hss_hair_placements.py` evaluates original prefab rest
bindings. `write_hss_txd.py` writes native D3D9 texture dictionaries from PNGs
and a texture manifest. Inspect their prerequisites before running them.

`rw_texture_names.py` makes bounded ordinary-DFF texture-name replacements and
single-material RGB changes. Names must fit their allocated string; RGB edits
require one modulated geometry with independent material entries. It preserves
opaque structs/plugins and opacity. `validate_hss_native.py` requires DragonFF's
`gtaLib` on `PYTHONPATH`, NumPy, a source manifest, catalogue and donor DFF; its
32-bone and Head-index assumptions are specific to the evaluated stock rig.

`build_hss_hair_colors.py` creates ten shaded hair palettes and material-slot
metadata from a compatible source/catalogue. It preserves alpha, recolours only
declared hair materials and appends texture records; supply a fresh appearance
manifest when rerunning after catalogue changes. It does not install a menu or
runtime renderer. Run the nine synthetic checks without game inputs:

```powershell
python -m unittest discover -s tooling/source/workshop/tools/model-conversion/tests -p test_rw_texture_names.py
python -m unittest discover -s tooling/source/workshop/tools/model-conversion/tests -p test_hair_colors.py
```

No model, texture, clip, assembly, private catalogue recipe or native trainer
implementation is included. See the [coverage and validation findings](../research/dryxio-workflow.md#wardrobe-coverage-and-appearance-preservation-2026-10-05).

## Unity muscle channels and native SA animation clocks

Six additional `valkyrie-models` modules/helpers/tests handle locally supplied
Unity 2017 scalar clip trees and native compressed SA animation output:
`unity_animation_curves.py`, `unity_humanoid_pose.py`, `sa_animation_writer.py`,
`validate_sa_animations.py`, `validate_sa_animations_blender.py`, and the
synthetic conversion test. Scalar muscle channels are not quaternion curves.
The pose module needs Blender `mathutils` and a serialized humanoid avatar;
it reconstructs swing/twist and fixed-length limb goals without running Unity's
IK/stretch or animator logic. Individual target fingers may be collapsed.

The writer accepts caller-supplied animation/bone/key dictionaries, writes
compressed ANP3 flag 1 and exact frame allocations, and quantizes quaternion,
root position and signed 60 Hz timestamps. Sampling frequency and native time
encoding are separate: a 30 Hz pose interval occupies two ticks. The ordinary
validator reports durations and forward root speed, checks allocations, tags,
unit quaternions and frame order, and rejects unsupported/truncated data.

The paired Blender validator requires INU_tools 2.3.1. That revision reads ANP3
time with a /30 divisor; the helper corrects its own import cache to the native
/60 clock without modifying the add-on. It samples four poses on supplied DFFs,
checks finite geometry and height 0.2..3 units, and reports edge stretch. Its
bounds allow prone actions; they are not a visual-quality acceptance test.
The earlier wardrobe sampler received the same ANP3 clock correction; ANPK
float seconds remain unchanged.

The corrected humanoid solver converts sole goals to ankle targets using the
serialized foot-axis length and internal effector rotation. Hand goals retain
their wrist origin. `tests/test_humanoid_pose_blender.py` uses synthetic geometry
only and checks rotated offsets, fixed segment lengths and unlocked knee bend.
Run it in Blender with `--factory-startup -b --python-exit-code 1 --python`.
The paired sampler explicitly uses 30 FPS, nonperiodic time fractions and
root-relative joint movement; a changing root clock alone is not a pose test.

```powershell
python -m unittest discover -s tooling/source/workshop/tools/model-conversion/tests -p test_animation_conversion.py
python tooling/source/workshop/tools/model-conversion/validate_sa_animations.py INPUT.ifp REPORT.json
```

Run Blender host scripts with `--factory-startup -b --python-exit-code 1` and
arguments after `--`. Eight synthetic tests ran without game inputs. Native
pose sampling used separately supplied local assets; no assets or trainer,
package/install recipe, animator state machine or gameplay integration is
bundled. See the [animation conversion findings](../research/dryxio-workflow.md#humanoid-animation-reconstruction-and-native-movement-2026-10-05).

## Source collections and portability

This is the reviewed 63-file source set for the ten defined families. It is not
a bulk export of other authoring, website or operational tooling. It includes CLI utilities, modules, host scripts, build
adapters and tests. Historical filenames remain entry points; the ten
`valkyrie-*` names group them by task. Shared filenames can occur in different
collections; select an exact registry ID rather than assuming they are equal.

- Python modules may need NumPy, Pillow, analysis packages or sibling helpers;
  see the import list and source. Blender `bpy`/`mathutils` scripts run in Blender,
  not ordinary Python. Ghidra scripts run in their supported analysis host.
- PowerShell scripts need PowerShell and their declared Windows toolchain.
  Shell scripts need Bash and their project commands.
- C#/C++ entries are source/build/test support, not directly executable commands.
  Mod-specific checks require the separately owned implementation under test.
- Historical scripts may expect a project tree, manifests, game paths, assets,
  installed binaries or an authorized database. These prerequisites are not
  bundled. Personal home-directory defaults are placeholders, not checkout routes.
- Some scripts modify files, databases, installations or remote services when
  deliberately run. Detected effects are navigation hints, not a complete audit.
  Read their parameters and supply the appropriate input/output environment.

Source publication does not imply every dependency is installed, every legacy
default is portable, or every tool has passed runtime/gameplay validation.
Current validation parses Python source, verifies the inventory and runs the
three synthetic examples. Existing mod implementations remain outside this repo.

## Maintenance

New tool changes start here. Existing consumer copies are compatibility snapshots
until their callers migrate; reconcile them through explicit reviewed paths and
hashes. Do not bulk-copy a private project or its history. Keep mod code, game
payloads, content packs, credentials, player data and runtime services excluded.
Preserve original notices. Use [method notes](../docs/VALKYRIE-TOOLING.md) and
return executed checks, failures and limitations as findings.
