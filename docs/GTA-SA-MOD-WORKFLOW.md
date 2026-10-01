# GTA San Andreas mod-making workflow

Use this public reference library to learn a method and record evidence.
Implement the mod in your own project's repository.

1. Define the behavior and exact game/version, architecture and input hash.
2. Choose a task family from [the reference catalog](workshop/CATALOG.md).
3. Read [Dryxio and original upstream references](../research/dryxio-catalog.md).
   Record revisions, prerequisites, supported profiles and applicable terms.
4. Select applicable [Valkyrie tools](#select-and-run-public-tools), inspect their
   inputs and prerequisites, then choose the interface and project build recipe.
5. Make a focused change and run meaningful checks. Report compilation,
   isolated tests, package integrity and in-game behavior separately.
6. Return the reusable method, observations, failures and limitations here as
   committed public-safe findings using [the template](../research/finding-template.md).

## Select the method

| Task | Reference route | Evidence to collect |
| --- | --- | --- |
| CLEO script | CLEO AI and opcode/library references | Exact profile, validation/compilation results, exercised behavior |
| Native ASI | SDK and engine references | Target signatures/layouts, toolchain and hook behavior |
| Binary/protocol analysis | Ghidra/reconstruction references and generated archives | Input hash, bounded evidence, observations versus inference |
| World/model/traffic | Authoring references | Permitted fixtures, format/roundtrip and loading behavior |
| Multiplayer/server | Client/server and protocol references | Exact versions, synthetic data and interface behavior |
| Graphics/navigation | Rendering/radar/GPS references | Target, dependencies and measured visual/runtime behavior |

CLEO AI applies to actual CLEO scripts. Record whether it ran and what it
produced. A citation is not tool use, and script compilation does not validate
native hooks or server code. Read [worked examples](workshop/EXAMPLES.md).

Keep restricted source, executable inputs, assets and operational data outside
the public library. Explain reproducible methods using permitted inputs.
Record release/deployment separately; a guide merge does not publish a mod.

## Select and run public tools

After choosing upstream references, route the task to the published family below.
Use only the tools relevant to the question; a family is not a required install.
[Family notes](VALKYRIE-TOOLING.md) link actual source and exact entry IDs;
[setup and commands](../tooling/README.md) explain the launcher and dependencies.

| Work stage / task | Public tool family | Inputs and checks |
| --- | --- | --- |
| Inspect or convert a model | [valkyrie-models](VALKYRIE-TOOLING.md#valkyrie-models) | Permitted model files; format, skin/pose checks; Blender when required |
| Index or bound a world | [valkyrie-world](VALKYRIE-TOOLING.md#valkyrie-world) | World definitions and models; bounds/index consistency |
| Inspect navigation graphs | [valkyrie-routes](VALKYRIE-TOOLING.md#valkyrie-routes) | Route graph/surface inputs; connectivity and route integrity |
| Extract, merge or audit textures | [valkyrie-textures](VALKYRIE-TOOLING.md#valkyrie-textures) | Permitted texture dictionaries; dimensions, formats and audit output |
| Inspect collision geometry | [valkyrie-collision](VALKYRIE-TOOLING.md#valkyrie-collision) | Collision/CADB inputs; model differences and geometry evidence |
| Inspect animation or conversion | [valkyrie-animation](VALKYRIE-TOOLING.md#valkyrie-animation) | Permitted animation inputs; names, motion and conversion checks |
| Investigate binaries or protocols | [valkyrie-binary](VALKYRIE-TOOLING.md#valkyrie-binary) | Exact target hash and analysis host; signatures, symbols and bounded exports |
| Check scripts or build/package integration | [valkyrie-pipeline](VALKYRIE-TOOLING.md#valkyrie-pipeline) | Separate project tree/manifests; declared profile and package integrity |
| Generate original UI/audio or inspect content methods | [valkyrie-content](VALKYRIE-TOOLING.md#valkyrie-content) | Original/permitted inputs; deterministic outputs, provenance and dimensions |
| Experiment with signal coverage | [valkyrie-signal](VALKYRIE-TOOLING.md#valkyrie-signal) | Terrain/transmitter parameters; repeatability and model assumptions |

From the workshop root, discover an entry without executing it:

```powershell
python valkyrie.py list --family valkyrie-collision
python valkyrie.py show workshop/tools/compare-cadb-models.py
```

Read the source's arguments, runtime, dependencies and file effects. Then run
against your permitted inputs, for example:

```powershell
python valkyrie.py run workshop/tools/compare-cadb-models.py -- OLD.cadb NEW.cadb
```

`OLD.cadb` and `NEW.cadb` are user-supplied paths, not bundled files. The launcher
preserves your current directory. Host scripts such as Blender/Ghidra entries
must run in their supported host using its recipe. Project checks need the
separate project under test; they do not build a mod from this library.

Start with the [three synthetic examples](workshop/EXAMPLES.md#run-public-tools-with-synthetic-inputs)
when learning without game inputs. Record the exact entry ID, source hash,
runtime/package versions, command, input identity, output and skipped checks in
your returned finding. Mark a consulted or unsuitable tool accordingly;
listing a tool does not establish execution or game compatibility.
