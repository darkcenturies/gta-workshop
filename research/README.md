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

- [S&SMP protocol findings](ssmp-protocol.md)
- [Target binary identities](targets.json)
- [Ped population findings](../docs/reverse-engineering/PECORE-PED-POPULATION.md)
- [GTA SA PS2 1.00 versus 2.01](gta-sa-ps2-1.00-vs-2.01.md)
- [Experimental S&SMP / PE DL adapter](ssmp-dl-adapter/README.md): historical
  checkpoint; official-launcher crash remains unresolved.
- [Workshop atlas and organization findings](workshop-atlas-2026-10-01.md)
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

Authored tools are private. Historical reproduction commands below run only
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
