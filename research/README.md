# Research and references

Return to [GTA Workshop](../README.md) for reference routes or use
[the documentation index](../docs/README.md) to choose a guide. Research here
records methods, evidence, findings and limitations using separately obtained
inputs. A historical target is not a current product requirement.

## Start research or mod-making

| Need | Start here |
| --- | --- |
| Task-specific Dryxio tools/mods | [Reference catalog](dryxio-catalog.md), [structured inventory](dryxio-catalog.json) |
| Pinned upstreams and prior evaluations | [Upstreams](upstreams.md), [Dryxio evaluation](dryxio-workflow.md) |
| Turn evidence into a verified improvement | [Research workflow](../docs/RESEARCH_WORKFLOW.md) |
| Record a new finding | [Finding template](finding-template.md) |
| Read binary evidence efficiently | [Agent/archive guide](../docs/AGENT_START.md), [archive index](../docs/reverse-engineering/README.md) |

## Findings and historical checkpoints

These dated records preserve evidence from earlier investigations. Project
names identify the researched targets; they are not a private mod catalog.

- [Windows x64 re3 Mod Loader callbacks](re3-modloader-callbacks-2026-10-04.md)
- [Native vehicle damage authoring](native-vehicle-damage-2026-10-02.md)
- [Bully school static map conversion](bully-school-map-port-2026-10-03.md)
- [GTA III pager identity and native extension methods](gta3-pager-extension-2026-10-03.md)
- [GTA III cut-character reconstruction and CLEO lifecycle methods](gta3-darkel-reconstruction-2026-10-03.md)
- [S&SMP protocol findings](ssmp-protocol.md)
- [Target binary identities](targets.json)
- [Ped population findings](../docs/reverse-engineering/PECORE-PED-POPULATION.md)
- [GTA SA PS2 1.00 versus 2.01](gta-sa-ps2-1.00-vs-2.01.md)
- [Experimental S&SMP / PE DL adapter](ssmp-dl-adapter/README.md): historical
  checkpoint; official-launcher crash remains unresolved.
- [Workshop atlas and organization findings](workshop-atlas-2026-10-01.md)
- [Defined tools public source](defined-tools-public-source-2026-10-01.md)
- [Content and signal method review](content-signal-methods-2026-10-01.md)
- [Valkyrie tooling method review](valkyrie-tool-methods-2026-10-01.md)
- [Public reference library scope correction](public-reference-library-2026-10-01.md)

The authoritative completed archive is
`docs/reverse-engineering/generated/index.json`: six targets, 45 checked files.
Use target metadata and SHA-256 to resolve old conflicting coverage notes.
Recovery counts describe generated output, not complete semantic understanding
or a successful rebuild of an original product.

## Reproduction and findings return

Record the target/version, input hash, tools/revisions, bounded evidence,
observed result, inference, reproduction and untested cases. Every task started
through this workshop returns committed public-safe findings, including useful
negative results. Restricted inputs and full private evidence stay in their
private owner; explain the withholding reason without copying them here.

Defined tooling is public under tooling/. Older commands below remain historical
reproduction records; use the current tool registry for published paths. Historical reproduction commands below run only
in the preserved private research source, using your own permitted inputs:

```sh
python -m pip install capstone
python deploy/ssmp-rpc-map.py /path/to/ssmp.so
python deploy/ssmp-hookmap.py /path/to/ssmp.so /path/to/samp03svr
```

The hook mapper also invokes GNU objdump. Check input hashes against targets.json;
keep scratch projects under ignored `work/`. Reviewed generated archives need
metadata and updated checksums. Review knowledge-only scope, local links and exact research hashes before submitting.
Public CI checks archive SHA-256 and overview formatting; authored tools are private.

[Workflow tool routing — 2026-10-01](workflow-tool-routing-2026-10-01.md) records
how published entry points connect to task guides and evidence requirements.
