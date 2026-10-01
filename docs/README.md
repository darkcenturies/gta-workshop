# Documentation

Return to [GTA Workshop](../README.md) for the overview, source owners and build
quick start. Choose one route below; detailed maps and archives provide optional
depth.

| I want to… | Start with | Next |
| --- | --- | --- |
| Find a project or owner | [Source owners](../README.md#projects-and-source-owners) | [Component catalog](workshop/CATALOG.md), [ownership details](REPOSITORIES.md) |
| Understand the complete flow | [Colored atlas](GTA-WORKSHOP.md) | [Worked routes](workshop/EXAMPLES.md) |
| Build a public mod | [Mod catalog](MODS.md) | [Building](BUILDING.md), then its component README |
| Create a new mod | [GTA SA workflow](GTA-SA-MOD-WORKFLOW.md) | [Dryxio references](../research/dryxio-catalog.md), [SDK](PLUGIN_SDK.md) |
| Investigate a binary/protocol | [Research index](../research/README.md) | [Archive](reverse-engineering/README.md), [research workflow](RESEARCH_WORKFLOW.md) |
| Use an AI agent | [Agent instructions](../AGENTS.md) | [Agent start](AGENT_START.md) |
| Contribute a fix or finding | [Contributing](../CONTRIBUTING.md) | [Finding template](../research/finding-template.md) |
| Propose making something public | [Publication backlog](workshop/PUBLICATION-BACKLOG.md) | [Public boundary](../PUBLICATION.md) |
| Understand server integration | [Integration](INTEGRATION.md) | [Source ownership](REPOSITORIES.md) |
| Reorganize files or diagrams | [Structure](STRUCTURE.md) | [Atlas maintenance](workshop/README.md) |

## Documentation layers

1. **README:** concise overview and starting commands.
2. **Guides and catalog:** ownership, methods, checks and detailed maps.
3. **Evidence:** dated findings and exact-target archives with provenance and
   limitations. Historical targets are not current product requirements.

The structured inventory is [catalog.json](workshop/catalog.json); its readable
counterpart is [CATALOG.md](workshop/CATALOG.md). The
[Dryxio inventory](../research/dryxio-catalog.json) records reference revisions,
fork attribution and evaluation status. Catalog entries are not live health
or automatic source-release approval.

## Keep navigation accurate

Update the relevant guide and index together. Add evidence beside the existing
related finding rather than creating parallel status documents. Change catalog
facts and affected diagrams together following atlas maintenance instructions.
Run `python tools/check_workshop.py` and `python tools/check_public.py` from the
root. Navigation checks cover maintained entry points; historical component
notes and external websites still need contextual review.
