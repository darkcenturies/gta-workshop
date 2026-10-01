# The public GTA workshop

Start GTA work in `darkcenturies/sp-rp-public-research`: find the project,
read its public references, choose visibility and follow the source owner.
This is the main catalog and contribution entry point for our GTA III,
Vice City and San Andreas work, including multiplayer and server development.
The repository URL remains unchanged. A catalog entry is public documentation,
not approval to publish the implementation it describes.

## Read the atlas

This workshop is the **start of GTA work and the return destination for its
findings**. Implementation lives in its named source owner. The five maps below
show different relations explicitly: routing, execution order, dependencies,
tool selection and publication state.

| View | Follow this when you need to… |
| --- | --- |
| [1. Ownership and return](#1-ownership-and-mandatory-return) | Choose the public/private owner and understand how findings come back |
| [2. Complete task flow](#2-complete-task-flow) | Start, choose methods, implement, test, handle failure and finish |
| [3. Components and dependencies](#3-components-and-dependencies) | Follow Core, Phone sync, server components, external engines and local inputs |
| [4. Dryxio task routes](#4-dryxio-task-routes) | Find the applicable references among all 18 cataloged GTA repos |
| [5. Publication gates](#5-publication-and-release-gates) | Distinguish existing public work, proposals, withheld source and actual publishing |
| [Detailed component catalog](workshop/CATALOG.md) | Inspect all 36 entries: target, owner, source, tests, references and required return |
| [Publication backlog](workshop/PUBLICATION-BACKLOG.md) | See what is public now, what we want public next and why other work is withheld |
| [Worked task routes](workshop/EXAMPLES.md) | Walk Doctor, SRG, CLEO, Upstate, server and rendering examples end to end |

**Color key:** blue = workshop/evidence; green = public source/contribution;
purple = private source/evidence; teal = external references; amber = decisions
and proposals; coral = withheld/blocked; orange = separate publishing actions.
Node labels repeat those meanings. Color indicates scope/stage, not live health.

Open any image for full-size detail. The [editable graph sources and rendering
instructions](workshop/README.md) accompany every colored image.

## 1. Ownership and mandatory return

Start at the hub, route to the actual owner, then follow the return lane. Every
owner returns findings, including Phone and supporting services; private owners
retain full restricted evidence and return a safe summary. Source exports are a
separate decision in map 5.

[![GTA ownership routes and mandatory findings return](workshop/ownership.svg)](workshop/ownership.svg)

## 2. Complete task flow

Classify visibility before public issues/branches, consult applicable references,
choose the actual toolchain, implement in the owner and repeat failed checks.
Useful negative results return too. Commit/push the owner contribution and the
workshop finding; code completion alone does not close the workshop task.

[![Complete task workflow, failed checks and public-safe return](workshop/task-flow.svg)](workshop/task-flow.svg)

## 3. Components and dependencies

Here arrows point **from consumer to provider**, rather than execution order.
Private Core, the approved public baseline and Phone's reviewed embedded subset
are distinct scopes. Server components belong to Workshop; gameplay belongs to
SP-RP. Upstate's external engine and local game assets are distinct from our patch.

[![GTA component owners and dependency boundaries](workshop/dependencies.svg)](workshop/dependencies.svg)

The [36-entry catalog](workshop/CATALOG.md) expands the grouped nodes, including
all named native-suite components, standalone helpers and historical source gaps.
Historical target-specific docs are evidence to recheck, not proof of the current
classic-SA direction or current compatibility.

## 4. Dryxio task routes

All 18 cataloged GTA repositories appear here, plus the separate profile-linked
texture reference. These edges show research fit, not automatic adoption or
installed dependencies. Exact revisions, fork parents and evaluation status are
in [the Dryxio inventory](../research/dryxio-catalog.json); task-specific details
are in [the reference catalog](../research/dryxio-catalog.md).

[![Dryxio references mapped to CLEO, native, world, protocol and visual tasks](workshop/dryxio-routes.svg)](workshop/dryxio-routes.svg)

## 5. Publication and release gates

Public-safe findings can return without exporting private source. A proposed
source export needs owner approval, provenance/terms, a bounded snapshot,
allowlist review and applicable checks. A merged contribution is distinct from
a binary release, website download and live deployment.

[![Existing public work, proposed exports, withholding and publishing gates](workshop/publication.svg)](workshop/publication.svg)

## What is already public, and where

Visibility was checked through GitHub on **2026-10-01**. This describes source
visibility at that date, not current release quality or live deployment status.
Private links require access; public readers can still use the descriptions.

| Project / work | Source owner | Current visibility and publication boundary |
| --- | --- | --- |
| Doctor + Crashfix, Map, Repair | This repository; [mod catalog](MODS.md) | Already public source. Doctor/Crashfix share one artwork-free ASI. Map retains the earlier approved baseline. |
| Generated decompilation, protocol findings and existing analysis tools | This repository; [research](../research/README.md) | Already public, with target hashes, archive checksums and separate upstream notices. Historical partner targets remain evidence. |
| Phone and its reviewed trainer/map dependencies | [valkyrie-phone](https://github.com/darkcenturies/valkyrie-phone) | Already public source in its own buildable repository. Its reviewed shared code does not make all Workshop implementation public. |
| Shared Core, Atmosphere, Fuel, experimental Radar and standalone mod development | [valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) | Private owner. Unreleased/private implementation has not been approved for export here; individual source releases require scope, license and package review. |
| SRG / GTA Midnight | [street-racing-girls](https://github.com/darkcenturies/street-racing-girls) | Private San Andreas conversion; its owner instructions explicitly require private source. Shared Valkyrie Core comes from Workshop. The legacy SRG identifiers remain in use. |
| Upstate/re3 port and GTA III animation conversion tools | Valkyrie Workshop | Our compatibility patch and tooling are private. The separately public [novawish/re3](https://github.com/novawish/re3) upstream is not our owned project or the complete port. Upstream availability does not publish our patch. |
| GTA rendering / DLSS integration | [dlss5-neural-rendering-kit](https://github.com/darkcenturies/dlss5-neural-rendering-kit) | Private integration repository; component redistribution terms and reproducible configuration need review before any export. Historical local test profiles are not a universal compatibility claim. Only its GTA use belongs in this catalog. |
| GTA/SP-RP Launcher integration | [dc-launcher](https://github.com/darkcenturies/dc-launcher) | Private source. A build or release record is separate from anonymous source/download availability. Its WoW work is outside this workshop's scope. |
| SP-RP gamemode, accounts and server operations | [sp-rp](https://github.com/darkcenturies/sp-rp) | Private server implementation by owner policy. Generic reusable examples can be proposed separately. Player records, credentials and production secrets are never public workshop inputs. |
| AI, async persistence and multiplayer native components | Valkyrie Workshop | Private native component source consumed by the server; the catalog does not authorize copying it. Publish only separately reviewed generic interfaces or examples. |
| Website/UCP and Discord integration | [sp-rp-web](https://github.com/darkcenturies/sp-rp-web), [sp-rp bot/live](https://github.com/darkcenturies/sp-rp/tree/bot/live) | Private supporting source; their public-facing services do not expose their repositories. Server and bot use separate production branches. |
| Models, vehicle imports, maps, road nodes, animation and asset conversion | Workshop; project-specific work in SRG | Private authoring source and locally supplied assets. Sanitized techniques, original/synthetic examples and permitted tooling are publication candidates; copied game payloads are not implicitly approved. |

Third-party inputs keep their own attribution and distribution terms. Our
catalog does not redistribute their games, engines, textures or binaries.
RubyGame, WWE, Metalart and non-GTA Launcher/rendering features are outside scope.

## What we want to publish next

These are **proposals**, not already public source or approved releases:

- Practical mod-making guides, with the relevant Dryxio and original upstream references.
- Original/synthetic CLEO, native ASI and asset-authoring examples with reproducible checks.
- Generic server workshops: protocol evidence, component interfaces, test fixtures and reusable tooling after review.
- Public-safe project summaries, compatibility evidence and contribution tasks for SRG, Upstate and rendering work.
- Individual private mod/tool releases once their source, dependency notices, packaging and tests have been reviewed.

Every proposed item records the source owner, intended public output, current
visibility, why it is withheld, applicable terms and the remaining review.
Do not label a goal as shipped, or a source review as a runtime test. Private
because of owner policy, private pending release review and restricted inputs
are different reasons; state the applicable reason explicitly.

## The go-to path for new work

1. Start with this map, the [Dryxio catalog](../research/dryxio-catalog.md),
   [research workflow](RESEARCH_WORKFLOW.md) and the relevant component guide.
2. Decide visibility **before** writing code, issues, logs or attachments.
   A branch, issue or draft PR in a public repository is public. Keep sensitive
   requests and implementation in their private owner from the outset.
3. Public fixes to the approved mods/research are implemented here. Existing
   public Phone source is implemented in Phone, reconciling shared changes with
   Workshop through its reviewed sync process. New generic public components
   need a deliberate scope/allowlist review before inclusion.
4. Private implementation goes directly to its owner's canonical checkout or
   owned worktree. Use a public-safe catalog description here where appropriate.
   No private staging branch or automatic public-to-private dispersal is used.
5. Consult the task-relevant Dryxio references and original upstreams, recording
   revision, target, applicability and actual evaluation status. Follow their
   documented methods where applicable; explain a relevant tool's limitations
   or non-applicability instead of claiming it validated another platform.
6. Build/test in the owner. A public contribution requires reviewed source,
   license/provenance, public boundary checks and its applicable validation.
   Never merge private history into this public remote. Update the catalog when
   source visibility or approval changes.

7. Return findings to this repository for **every task started through it**,
   including work implemented elsewhere and useful negative results. Commit and
   push the public-safe record and open a PR in the same session. Keep restricted
   evidence in the private owner and return a sanitized outcome, validation,
   remaining questions and withholding reason here. Follow the detailed
   [agent return requirements](../AGENTS.md#mandatory-return-of-findings).

Source merges, binary releases, website downloads and live deployments remain
separate actions. [PUBLICATION.md](../PUBLICATION.md) defines the code boundary;
this broader catalog does not weaken it.
