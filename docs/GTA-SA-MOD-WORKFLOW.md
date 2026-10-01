# GTA San Andreas mod-making workflow

GTA Workshop explains how to do the work and records the findings. Implement
mods in [their source owner](REPOSITORIES.md), not this knowledge repository.

1. Identify classic GTA SA target/version, architecture and exact input hash.
2. Choose the task from [the component catalog](workshop/CATALOG.md).
3. Consult [Dryxio and original upstream references](../research/dryxio-catalog.md).
4. Read the owner's component recipe, provenance and test requirements.
5. Make the smallest evidence-backed change, build and run meaningful checks.
6. Return the outcome and limitations here using [the finding template](../research/finding-template.md).

## Select the method

| Task | Method |
| --- | --- |
| CLEO script | CLEO AI/opcode references, exact profile, validation/compilation; game behavior separately tested |
| Native ASI | Reviewed SDK and exact-target signature/layout evidence, MSVC x86 build and component tests |
| C# utility | Owner's compiler/build recipe and isolated behavioral tests |
| Engine/port | Exact upstream revision, owned patch, input provenance and consumer tests |
| World/model/traffic | Relevant authoring tools, original/synthetic public examples, format/roundtrip checks |
| Protocol/server | Exact host/client version and packet/interface evidence; private data excluded |

CLEO AI is relevant to actual CLEO scripts. It was not the compiler or validator
for the current native C++/C# mods. A documentation review is not installed use
or gameplay verification.

## Current mod direction

Doctor and Crashfix share one artwork-free ASI in private Valkyrie Workshop.
Map, Repair and other private mods are developed there. Phone remains public
in its own repository. Retire former partner runtime functions/profiles while
preserving historical research and attribution. Other permitted artwork is allowed.

Keep source, compilation, tests, package integrity and in-game evidence distinct.
No gameplay validation or installation is implied by a catalog entry.
Release and deployment use the owner's separate process and authorization.
