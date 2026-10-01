# Public outputs: current state, proposals and withholding reasons

This is a publication decision catalog, not an automatic release schedule.
Source state is recorded in [the component catalog](CATALOG.md); release and
deployment states require their own evidence. The [publication map](publication.svg)
shows the gates and the [workshop map](../GTA-WORKSHOP.md) shows the full flow.

## Already public

| Public output | Location | Boundary or known gap |
| --- | --- | --- |
| Doctor + Crashfix source | This repo's approved mod tree | One artwork-free ASI; preserve guard GPL and diagnostic notices. Builds/tests are separate from game verification. |
| Map source | This repo's earlier 0.2.0 baseline | Exact later 0.2.1 source is unresolved; private Radar extensions stay excluded. |
| Repair source | This repo's Repair component | Current build embeds combined Doctor/Crashfix; historical binary records describe earlier versions. |
| Phone and reviewed embedded dependencies | Public valkyrie-phone | Its reviewed scope is separate from this repo's allowlist and private Workshop development. |
| Generated decompilation / protocol evidence | Existing public archives | Exact historical targets, metadata and checksums; preserve vendor provenance. |
| Analysis tools, guides and returned findings | Existing approved paths here | Reproducible permitted inputs; findings must state actual validation and limits. |
| External re3 engine | Third-party novawish/re3 | Public upstream availability does not publish our compatibility patch or assets. |

## Proposed next public outputs

These are candidates, with no approval to copy private source implied.

| Candidate | Private/public owner to consult | Reviewable output | Gates before it is public source |
| --- | --- | --- | --- |
| CLEO mod-making workshop | This public repo; relevant Dryxio CLEO references | Original/synthetic example, pinned opcodes/profile, generation/validation/compile record | Terms, example scope and allowlist review; actual compile results; game behavior separately reported |
| Native ASI workshop | Public mods; shared/private source owner if involved | Original minimal example and exact-target layout/signature evidence | Source provenance, notices, consumer build/tests and publication-boundary review |
| Function-level reverse-engineering handoff | Existing public research scope | Target hash, bounded evidence, question, candidate/inference and validation limits | Permitted inputs; preserve archive/vendor terms; do not publish newly restricted private research |
| World/model/traffic authoring workshop | Workshop and project owner | Original/synthetic scene, editable source, before/after record and format/roundtrip checks | Asset provenance, tool/output terms and review of any scripts to be exported |
| Generic server component examples | SP-RP and Workshop | Reusable interface example or synthetic fixture detached from accounts/operations | Owner scope approval, dependency/protocol terms, meaningful host tests and clean public snapshot |
| SRG / GTA Midnight project findings | SRG private owner | Sanitized compatibility/authoring summary and contribution questions | Privacy review; private source policy remains; no generated game payloads |
| Upstate/re3 reproducibility findings | Workshop; third-party engine and mod authors | Exact engine/patch revision record and safe format/build results | Original credits and restricted-input review; owned patch export requires separate approval |
| GTA rendering compatibility findings | Private rendering owner | Host/driver/profile evidence and reproducible permitted configuration | Component terms and private configuration review; no blanket GPU/game support claims |
| Launcher/service integration guides | Launcher, server, website and bot owners | Generic workflow/interfaces and sanitized validation | No production configuration/credentials; relevant source scope and service checks |
| Individual private mod/tool source releases | Workshop or project owner | Bounded corresponding source, notices, package recipe and validation | Explicit release-scope review, provenance, approved-file review, consumer tests and destination PR |

## Work withheld and why

| Scope | Reason it remains withheld | What can still return here |
| --- | --- | --- |
| SRG / GTA Midnight source | Explicit private-source owner policy | Safe project status, findings, tests/limits and withholding reason |
| Fuel implementation/tooling | Explicitly excluded from public research source imports | Sanitized result; full private evidence in Workshop |
| Radar renderer/router/tile pipeline and project-specific notes | Unreleased private scope explicitly excluded | Only a privacy-reviewed safe outcome; no hidden implementation export |
| Other private shared source, mod and tool additions | No bounded source release approved | Generic findings and proposed export scope after privacy review |
| Gamemode/account/production implementation | Private gameplay and operations; sensitive user/service data | Synthetic reusable examples after separate review; safe outcome summary now |
| Game-derived payloads, executable inputs and vendor assets | Not implicitly licensed for redistribution by a tool or catalog | Provenance and permitted synthetic reproduction; inputs obtained independently |
| Winmode Nullfix standalone source | Corresponding source not located | Verified source-search/provenance result; preserve unresolved state |
| Exact later Map source | Baseline gap remains unresolved without private additions | Safe source-version finding; no claim that baseline equals later download |
| Reuse with unclear terms | Link/reference does not establish a copying grant | Tool evaluation and outstanding terms question; no source import yet |

## Completion evidence

For each accepted proposal record the source owner, intended output, decision,
source/review revisions, notices, actual checks, unresolved gates and destination
PR. Update this backlog when a proposal becomes public. Do not relabel an
unmerged PR as shipped, or a merged source contribution as a live deployment.
Every workshop-originated task returns findings under [AGENTS.md](../../AGENTS.md#mandatory-return-of-findings).
