# Repository structure

[GTA Workshop](../README.md) is the public reference library;
[Documentation](README.md) routes readers by task and research question.

```text
gta-workshop/
  README.md                     Public library overview and entry routes
  AGENTS.md                     Agent rules and mandatory findings return
  CONTRIBUTING.md               Contribution/review process
  PUBLICATION.md                Knowledge/research boundary
  THIRD_PARTY_NOTICES.md         Attribution and research rights
  docs/
    README.md                   Guide index
    STRUCTURE.md                Placement rules
    GTA-WORKSHOP.md             Five colored reference/workflow maps
    workshop/                   Reference catalog, diagrams, worked examples
    reverse-engineering/        Generated evidence, metadata and checksums
  tooling/                      Defined public tool source and runnable examples
  valkyrie.py                    Tool browser and runner
  research/                     Findings, upstream inventories, historical notes
  publication/                  Approved knowledge/evidence inventory
  .github/                      Review and repository checks
```

| Material | Destination |
| --- | --- |
| Mod-making or research guide | `docs/`, linked from its index |
| Reference route or evaluation correction | Structured/human catalog, upstream inventory and affected maps |
| Finding or useful failed experiment | Existing related research note or bounded new finding |
| Generated binary evidence | Reverse-engineering archive, with provenance and exact hashes |
| Mod implementation or release | Your implementation project, outside this library |
| Private product ownership/local routing | Maintainer's private workspace index |
| Restricted evidence or input | Authorized private/local storage; safe reusable finding here |

Root files are entry points, policy, notices and configuration. Archive paths,
metadata and checksums stay stable and byte-exact. Dated project notes remain
historical evidence; active navigation is organized around reusable techniques.
Local scratch work is ignored and never a public input or source directory.
