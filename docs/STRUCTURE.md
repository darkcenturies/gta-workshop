# Repository structure

[GTA Workshop](../README.md) is the overview; [Documentation](README.md) is the
guide index. This page defines placement in the public repository. For other
projects use [source ownership](REPOSITORIES.md).
The canonical owner checkout remains `C:\Users\Admin\sp-rp-public-research`,
with remote `darkcenturies/gta-workshop`.

```text
gta-workshop/
  README.md                     Overview, owners, workflow and commands
  AGENTS.md                     Agent rules and mandatory findings return
  CONTRIBUTING.md               Contribution and review process
  PUBLICATION.md                Public/private source boundary
  build.ps1                     Public Windows build entry point
  client/valkyrie-asi-suite/     Approved mod source and component recipes
  docs/
    README.md                   Guide index
    STRUCTURE.md                File placement rules
    GTA-WORKSHOP.md             Five detailed colored maps
    workshop/                   Catalog, map sources/SVGs, worked routes
    reverse-engineering/        Exact-target archives and metadata
  research/                     Findings, reference inventories, checkpoints
  deploy/                       Analysis/export tools under existing paths
  tools/                        Boundary, documentation and artifact checks
  publication/                  Reviewed file and implementation manifest
  third_party/plugin-sdk/       Pinned SDK submodule
  .github/                      Review ownership, PR template and CI
  work/                         Ignored experiments and scratch output
```

## Placement rules

| Material | Destination |
| --- | --- |
| Approved public mod fix | Its existing component in `client/valkyrie-asi-suite/` |
| General build, SDK or contribution guide | `docs/`, linked from its index |
| Ownership, visibility or component change | Structured/human catalog and affected maps together |
| Finding or useful failed experiment | Existing related `research/` note, or a bounded finding using its template |
| Reviewed binary-research output | `docs/reverse-engineering/`, with metadata and checksums |
| Documentation or scope validation | `tools/`, documented in its maintenance guide |
| Temporary local inputs and candidate output | Ignored `work/`; never a public staging area for restricted source |
| Private implementation or evidence | Its private owner; return only public-safe findings here |

Keep root files for entry points, policy, licensing and build configuration.
Detailed project status belongs in its documentation area. Source and archive
paths remain stable for recipes, provenance and external references.
`deploy/` holds analysis utilities, not a live server checkout.

Do not maintain another public source snapshot in the private Workshop's
historical `public-release/` folder. Phone still has its own independent
repository and reviewed synchronization scope; it has not moved here.
New files require reviewed allowlist entries. Reorganization does not approve
private exports, altered mod implementation hashes or SDK upgrades.

## Current navigation and historical evidence

Current guides describe the actual layout. Dated findings and original archives
preserve historical targets and attribution. Correct conflicting instructions;
explain historical observations instead of silently rewriting their evidence.

The obsolete root structure guide is superseded by this page. Its claimed
`map-suite`, `crashfix` and `repair-tool` directories did not match the
maintained tree. Use the exact current paths and mod catalog.
