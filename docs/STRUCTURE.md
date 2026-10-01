# Repository structure

[GTA Workshop](../README.md) is the overview; [Documentation](README.md) routes
readers to guides. This repository contains public knowledge and research
evidence. Implementation belongs in [its source owner](REPOSITORIES.md).

```text
gta-workshop/
  README.md                     Overview, owners and workflow
  AGENTS.md                     Agent rules and mandatory findings return
  CONTRIBUTING.md               Contribution/review process
  PUBLICATION.md                Knowledge/research boundary
  THIRD_PARTY_NOTICES.md         Attribution and research rights
  docs/
    README.md                   Guide index
    STRUCTURE.md                Placement rules
    GTA-WORKSHOP.md             Five detailed colored maps
    workshop/                   Catalog, graph sources/SVGs, worked routes
    reverse-engineering/        Generated evidence, metadata and checksums
  research/                     Findings, reference inventories, checkpoints
  publication/                  Approved knowledge/evidence inventory
  .github/                      Ownership, PR template and CI configuration
  work/                         Ignored local scratch; never public inputs
```

| Material | Destination |
| --- | --- |
| Mod-making guide | `docs/`, linked from its index |
| Owner, visibility or component change | Structured/human catalog and affected maps together |
| Finding or useful failed experiment | Existing related `research/` note or a bounded new finding |
| Generated binary-research evidence | `docs/reverse-engineering/`, with provenance and exact hashes |
| Reference inventory | `research/`, with revision, attribution and evaluation status |
| Mod/tool/adapter implementation or build/package recipe | Its implementation owner; never this public tree |
| Restricted evidence or input | Private owner/local authorized storage; safe summary here |

Root files are entry points, policy, notices and repository configuration.
Research archives retain stable paths and byte-exact metadata. Dated notes
remain historical evidence; active guides describe the current knowledge-only
scope. Phone is still a separate public repository, not merged here.

The canonical owner checkout remains `C:\Users\Admin\sp-rp-public-research`;
the public remote is `darkcenturies/gta-workshop`. Use that existing checkout or
shared worktrees, never another owned clone. Former client/deploy/tools/SDK
directories and root build script have been removed from the public tree.
