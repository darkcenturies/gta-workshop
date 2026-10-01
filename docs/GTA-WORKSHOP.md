# GTA Workshop: detailed atlas

Start with [the README](../README.md) for the concise overview and
[the documentation index](README.md) for a task guide. This public workshop
contains mod-making knowledge and generated research evidence.
Implementation lives in its named owner.

## Read the atlas

| View | Question |
| --- | --- |
| [Ownership and return](#1-ownership-and-mandatory-return) | Where does implementation go and how do findings return? |
| [Task flow](#2-complete-task-flow) | What happens from intake through validation and completion? |
| [Dependencies](#3-components-and-dependencies) | Which owner supplies shared source and prerequisites? |
| [Dryxio routes](#4-dryxio-task-routes) | Which references fit the task? |
| [Publication](#5-publication-and-release-gates) | What is public knowledge, private source or a separate release? |
| [36-component catalog](workshop/CATALOG.md) | Exact owners, targets, states, methods and checks |
| [Public output backlog](workshop/PUBLICATION-BACKLOG.md) | Existing knowledge, proposals and withholding reasons |
| [Worked routes](workshop/EXAMPLES.md) | End-to-end examples |

Blue means workshop/evidence; green public knowledge or separate public Phone
source; purple private implementation/evidence; teal external references;
amber decisions; coral withheld/blocked; orange separate publication.
Labels repeat the meaning. Colors are not live health indicators.

## 1. Ownership and mandatory return

Public guides, findings and generated archives stay here. Doctor/Crashfix,
Map, Repair, authored tools and experimental implementation belong in private
Valkyrie Workshop. Phone stays independently public. Every route returns safe
findings; full restricted evidence stays in its owner.

[![Ownership and findings return](workshop/ownership.svg)](workshop/ownership.svg)

## 2. Complete task flow

Choose target, visibility and owner before sharing requests or implementation.
Consult relevant references, implement and test in the owner, record failures
as well as success, and commit public-safe findings back here.

[![Task flow with validation, failure and return](workshop/task-flow.svg)](workshop/task-flow.svg)

## 3. Components and dependencies

Arrows point consumer to provider, not execution order. Private shared Core,
private mod implementations and Phone's reviewed public dependency scope are
distinct. Server gameplay and native components have separate owners.
Upstate consumes an external engine and locally supplied assets.

[![Component dependencies and source boundaries](workshop/dependencies.svg)](workshop/dependencies.svg)

The [catalog](workshop/CATALOG.md) expands all 36 components, including historical
source gaps. Exact later Map/standalone Nullfix source gaps remain recorded;
moving ownership does not resolve them.

## 4. Dryxio task routes

All 18 cataloged GTA references and the separate texture reference are included.
Edges indicate research applicability, not adoption, installation or licenses.
Keep original fork-parent attribution and exact evaluation status.

[![Dryxio reference routes](workshop/dryxio-routes.svg)](workshop/dryxio-routes.svg)

See [the reference catalog](../research/dryxio-catalog.md) and
[structured revisions](../research/dryxio-catalog.json).
CLEO AI applies to scripts, not native C++/C#/server validation.

## 5. Publication and release gates

GTA Workshop publishes knowledge and generated research, not implementation.
Existing public Phone source has its own destination. Any future source release
needs a separate owner-approved destination and provenance/package review.
Source merges, releases, website downloads and deployments are separate.

[![Knowledge, implementation and publication gates](workshop/publication.svg)](workshop/publication.svg)

## Current public and private boundaries

Public here: guides, catalogs, graph sources/SVGs, findings, target metadata,
checksums, generated decompilation/disassembly, reconstructed research pseudocode
and approved IDA evidence. Private: authored mod/tool/adapter implementation,
build recipes and packaging. Phone's already-public implementation stays separate.

Private gamemode/accounts, production details, credentials, input executables
and game assets are excluded. Historical partner targets remain public evidence,
not current affiliation or installation requirements.
[PUBLICATION.md](../PUBLICATION.md) is authoritative.

## Go-to path

Find the component, choose target and visibility, consult Dryxio and original
upstreams, implement/validate in its owner, and return safe findings here.
Use [worked routes](workshop/EXAMPLES.md) and
[the agent return requirements](../AGENTS.md#mandatory-return-of-findings).

[Graph maintenance and rendering](workshop/README.md) preserves consistent
sources and colored SVGs. The canonical checkout folder remains
`C:\Users\Admin\sp-rp-public-research`; use the existing checkout or worktree.
