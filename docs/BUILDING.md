# Native build and validation methods

Use this guide to plan a build in your project's source repository. Follow that
project's actual recipe and dependency pins; this library ships no mod source,
SDK checkout or packaged build system.

## Establish the target

Record game/version, executable hash and architecture. For classic GTA SA PC
native plugins, select an x86 Windows toolchain matching the chosen SDK and
project. Record compiler, Windows SDK and dependency revisions. An ASI is a
DLL loaded through an ASI loader; a file extension alone proves no compatibility.

## Prepare and build

Use the project's documented prerequisites, pinned dependencies and build
configuration. Initialize required submodules in that project. Build the
smallest affected target without installing it. Keep the command, revision,
diagnostics and artifact identity in the finding record.

Check ABI assumptions separately: calling conventions, class layouts, field
offsets, hook signatures and load addresses. SDK declarations and compiler
success do not establish correctness against a different executable profile.
See [SDK references](PLUGIN_SDK.md) and [research workflow](RESEARCH_WORKFLOW.md).

## Report separate validation gates

| Gate | What it establishes |
| --- | --- |
| Dependency/provenance review | Exact inputs and applicable terms |
| Compilation/linking | The selected source builds with that configuration |
| Focused tests | Behavior covered by the executed fixtures |
| Package integrity | Expected files and a readable package |
| In-game checks | Only the exercised target, scenarios and mod combination |

Record skipped and unknown gates. Do not install or deploy merely to validate
documentation. Build recipes and releases stay with the implementation project;
return reusable methods, actual checks and limits using the
[finding template](../research/finding-template.md).
