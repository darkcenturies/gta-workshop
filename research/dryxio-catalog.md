# Dryxio: the GTA reference catalog

Required starting research for GTA workshop tasks. Select the references that
fit the task, record the source revision and then validate our actual target.
Consulting the catalog is required; installing every tool or adopting every
fork is not. [Dryxio's own project index](https://github.com/Dryxio/dryxio)
is the upstream entry point; retain original authors and fork parents.

The [machine-readable inventory](dryxio-catalog.json) records **18 GTA-related
repositories** returned by the public account on **2026-10-01**, with exact
inventory revisions, fork parents and evaluation status. The profile's texture
research is linked below separately. Non-GTA projects are explicitly excluded.
This inventory verifies public metadata, not builds, licenses or runtime results.
The earlier [revision review](dryxio-upstreams.json) and
[detailed findings](dryxio-workflow.md) keep their original review dates.

## Select a route

| Task | Reference | How it fits our work |
| --- | --- | --- |
| GTA SA CLEO scripts | [CLEO AI](https://github.com/Dryxio/cleo-ai), [library fork](https://github.com/Dryxio/library) | Look up opcodes and profiles, validate, compile, then test in game. CLEO AI does not validate our native C++/C# mods or re3 CLEO Redux scripts. |
| Native SA ASIs and engine definitions | [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed fork](https://github.com/Dryxio/gta-reversed) | Compare exact-target declarations and evidence for Doctor/Crashfix, Core and SRG. This is not an automatic replacement of our pinned DK22Pac SDK. |
| Reverse engineering and reconstruction | [Ghidra Bridge](https://github.com/Dryxio/ghidra-bridge), [ReAgent](https://github.com/Dryxio/reagent) | Gather bounded evidence and check candidate reconstructions. Resolve tool isolation against our canonical-checkout/worktree rules. |
| Maps and world editing | [Ariane](https://github.com/Dryxio/ariane) | Reference for III/VC/SA editing and its separately documented agent channel. SRG and Upstate still validate their own formats and targets. |
| Models, props, vehicles and Blender authoring | [GTA Scout](https://github.com/Dryxio/gta-scout) | Reference for discovering and authoring with locally supplied assets. Keep original/synthetic public examples separate from game-derived payloads. |
| Traffic and road graphs | [GTA Flow](https://github.com/Dryxio/gta-flow) | Reference for authoring and roundtrip validation. Its alpha/profile limits must be checked before SRG, extended-map or server use. |
| SA-MP client/protocol research | [samp-source](https://github.com/Dryxio/samp-source), [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild) | Distinguish byte matching from functional reconstruction. R5 results do not prove S&SMP compatibility. |
| Multiplayer populations and engine research | [MTA Neon](https://github.com/Dryxio/mtasa-neon), [mtasa-blue fork](https://github.com/Dryxio/mtasa-blue), [Neon documentation](https://github.com/Dryxio/wiki.mtasa-neon.com) | Compare architecture and test questions. MTA is a separate platform, not a replacement server deployment for SP-RP. |
| Graphics/mod-stack comparisons | [SkyGfx fork](https://github.com/Dryxio/skygfx) | Reference for visual and compatibility investigations. It does not establish our DLSS host/driver compatibility. |
| GPS and radar references | [GTA-GPS-Redux fork](https://github.com/Dryxio/GTA-GPS-Redux), [Definitive Edition radar fork](https://github.com/Dryxio/Radar-in-style-GTA-SA-The-Definitive-Edition) | Compare appropriate behavior and dependencies; do not imply ownership of the upstream work or export our private Radar implementation. |
| Engine limits and extended-map research | [fastman92 limit adjuster fork](https://github.com/Dryxio/fastman92_limit_adjuster) | Start from the fork and its original parent, then inspect supported versions and compatibility before using it. |

Dryxio also links **GTA SA Textures IRL** in his
[project index](https://github.com/Dryxio/dryxio): texture-location research,
not a mod compiler or an asset redistribution grant.

## Evidence and attribution

For each task, record which references were consulted, their exact revisions,
why they fit, their fork/original authors, applicable terms, commands actually
run and the remaining tests. A reference can be `metadata-only`,
`documentation-reviewed`, `locally-built` or `runtime-tested`; do not promote
one status into another. Inventory revisions are not installed dependency pins.

Newly inventoried forks and Neon documentation have **no license review in this
change**. Links are references, not permission to copy source, assets or binaries.
Keep the previous review's uncertainty intact and resolve terms for each reuse.

Our existing native build/tests remain the relevant gate for Doctor/Crashfix,
Map, Repair and Phone. Use [the GTA SA workflow](../docs/GTA-SA-MOD-WORKFLOW.md)
for actual CLEO sources and [the research workflow](../docs/RESEARCH_WORKFLOW.md)
for exact-target evidence. Every project uses its own platform-specific build
and runtime checks; our public/private project owners are in
[the workshop map](../docs/GTA-WORKSHOP.md).
