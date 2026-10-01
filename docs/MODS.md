# Choose a mod-making method

Choose by the behavior you want to change and the game's supported interfaces.
Use the [reference catalog](workshop/CATALOG.md) and
[GTA SA workflow](GTA-SA-MOD-WORKFLOW.md) to investigate the route.

| Mod type | Research focus | Meaningful validation |
| --- | --- | --- |
| CLEO script | Opcode/profile references and script tools | Validation, compilation and repeatable in-game behavior |
| Native ASI plugin | SDK declarations, engine behavior and hooks | Exact-target signatures/layouts, x86 compilation and affected game behavior |
| Map/model/texture change | Authoring tools, file formats and provenance | Permitted input roundtrip, loading, visual/collision checks |
| Traffic/navigation change | Route graph, population and navigation references | Deterministic exports, graph connectivity and in-game behavior |
| Graphics/radar change | Render pipeline, device state and mod compatibility | Targeted visual checks, reset behavior and performance measurements |
| Multiplayer/server change | Versioned protocol, callbacks and interfaces | Synthetic fixtures and compatible client/server behavior |
| Engine compatibility work | Upstream revision, layouts and asset formats | Focused consumer tests and separately recorded gameplay/save checks |

Implement in your project's repository and return the method and findings here.
Compilation alone does not establish game behavior. A reference entry does not
claim compatibility, adoption or permission to redistribute its source/assets.
