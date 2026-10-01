# Agent start: GTA Workshop

Read [AGENTS.md](../AGENTS.md), [README](../README.md) and
[the documentation index](README.md). This is a public reference library,
organized by methods and research questions, not private products.

| Task | Start |
| --- | --- |
| Find a relevant tool or upstream | [Reference catalog](workshop/CATALOG.md), [Dryxio inventory](../research/dryxio-catalog.md) |
| Make or improve a mod | [GTA SA workflow](GTA-SA-MOD-WORKFLOW.md), [mod types](MODS.md) |
| Native compilation methods | [Build guide](BUILDING.md), [SDK guide](PLUGIN_SDK.md) |
| Binary/protocol investigation | [Research index](../research/README.md), [archive](reverse-engineering/README.md) |
| Return findings | [Template](../research/finding-template.md), [research workflow](RESEARCH_WORKFLOW.md) |
| Understand the learning routes | [Colored maps](GTA-WORKSHOP.md), [examples](workshop/EXAMPLES.md) |
| Apply evidence elsewhere | [Project boundaries](REPOSITORIES.md), [integration](INTEGRATION.md) |

## Read generated research efficiently

Start at `docs/reverse-engineering/generated/index.json` and choose the exact
target. Read metadata and CSV headers, search function/symbol/named indexes,
then load bounded decompiled/disassembly excerpts. Six targets and 45 archived
files have a published ledger; IDA evidence has its own manifest.

Record input hash, architecture, image/load base and VA/RVA. Distinguish
observed bytes from inferred types and hypotheses. Generated output is evidence,
not original vendor source or proof of a complete runnable rebuild.

## Implement elsewhere and return knowledge

Read your implementation project's instructions. For the maintainer's local
projects, use the private workspace index to find canonical checkouts; do not
publish the internal inventory here. Preserve unrelated edits, record actual
checks and useful failures, and avoid installation/deployment for doc validation.

Every originating task returns committed/pushed public-safe findings through
a library PR. Keep restricted details outside this tree and explain limits
safely. Defined tool source is public under tooling/. Mod implementations and mod
release packages do not belong here.
