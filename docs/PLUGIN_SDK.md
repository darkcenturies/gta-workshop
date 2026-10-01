# GTA plugin SDK reference

Use [DK22Pac/plugin-sdk](https://github.com/DK22Pac/plugin-sdk) and the relevant
[Dryxio SDK references](../research/dryxio-catalog.md) as external references.
No SDK is vendored in this knowledge repository.

In the implementation owner, follow its exact reviewed dependency pin and
initialize its submodules. Phone's recipe uses its existing plugin-sdk and
ImGui pins; changing them requires dependency review and consumer tests.

For GTA SA native work search the matching game classes, RenderWare declarations,
calling conventions and hook examples. Check the exact executable architecture,
hash, addresses, field offsets and signature bytes against evidence.
A declaration or successful compile does not establish layout correctness.

Preserve SDK and bundled dependency notices. Fork availability is not a license
grant or evidence of compatibility with every game profile.
Read [the native build-method guide](BUILDING.md) and [research workflow](RESEARCH_WORKFLOW.md).
