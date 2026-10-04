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

This retained sampler selects `hss_f_*.dff`; an optional fourth argument selects
comma-separated stems within that pattern. It samples `woman_idlestance`,
`woman_walknorm` and `woman_run` at four times each, reports edge stretch and
checks finite geometry and an upright height between one and three units.
Those assumptions suit the evaluated conversions; inspect them before adapting
it to another naming convention, stature or animation set. Its output expressly
records `gameplay_tested: false`. The Blender entries are listed as host scripts;
the Python launcher does not execute Blender for you. No input models or clips
are bundled. See the [dated findings](../research/dryxio-workflow.md#continuous-torso-fitting-after-an-in-game-proportion-report-2026-10-04).

## Source collections and portability

This is the reviewed 48-file source set for the ten defined families. It is not
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
