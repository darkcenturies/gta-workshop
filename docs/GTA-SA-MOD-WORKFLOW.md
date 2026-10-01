# GTA San Andreas mod-making workflow

Use this public reference library to learn a method and record evidence.
Implement the mod in your own project's repository.

1. Define the behavior and exact game/version, architecture and input hash.
2. Choose a task family from [the reference catalog](workshop/CATALOG.md).
3. Read [Dryxio and original upstream references](../research/dryxio-catalog.md).
   Record revisions, prerequisites, supported profiles and applicable terms.
4. Choose the interface and toolchain; follow your project's actual build recipe.
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
