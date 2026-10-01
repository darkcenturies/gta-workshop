# Agent start: GTA Workshop

Read [AGENTS.md](../AGENTS.md), [README](../README.md) and
[the documentation index](README.md). This repository is the knowledge hub;
mod implementations and authored tools are in their named owners.

## Choose a route

| Task | Start |
| --- | --- |
| Find the implementation owner | [Component catalog](workshop/CATALOG.md), [owner guide](REPOSITORIES.md) |
| Make or improve a mod | [GTA SA workflow](GTA-SA-MOD-WORKFLOW.md), [Dryxio catalog](../research/dryxio-catalog.md) |
| Native compilation methods | [Build guide](BUILDING.md), [SDK guide](PLUGIN_SDK.md) |
| Binary/protocol investigation | [Research index](../research/README.md), [archive](reverse-engineering/README.md) |
| Return findings | [Template](../research/finding-template.md), [research workflow](RESEARCH_WORKFLOW.md) |
| Understand all project routes | [Five colored maps](GTA-WORKSHOP.md), [worked examples](workshop/EXAMPLES.md) |
| Change placement or publication | [Structure](STRUCTURE.md), [public boundary](../PUBLICATION.md) |

## Read generated research efficiently

Use `docs/reverse-engineering/generated/index.json` to choose the exact target.
Read metadata.json and CSV headers, search function/symbol/named indexes, then
load bounded decompiled/disassembly passages. Six targets and 45 archived files
are checked by the published ledger. IDA evidence has its own manifest.

Record input hash, architecture, image/load base and VA/RVA. Do not treat product
names or plausible inferred types as proof. Decompilation is generated evidence,
not original vendor source or a complete runnable rebuild.
Historical compatibility records retain target attribution and limits.

## Work in the owner and return here

Use canonical checkouts/shared worktrees. Read the owner's instructions before
changing code or executing a build. Record meaningful checks, actual commands,
limits and useful failed results. Do not install or deploy just to validate a guide.

Every originating task returns committed/pushed public-safe findings through a
workshop PR. Restricted implementation and full evidence stay private. No mod
source, build recipes or authored research scripts belong in this public tree.
