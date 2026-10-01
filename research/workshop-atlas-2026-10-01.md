# Detailed colored GTA workshop atlas

## Question and owner

Expand the public workshop's short graph and catalog into a detailed, colored
representation of source routing, implementation, dependencies, tool selection,
findings return and publication. This documentation is owned by
darkcenturies/gta-workshop. It covers GTA-only work; it does not export
private implementation or deploy services.

The public name is **GTA Workshop**, maintained by darkcenturies as a solo
developer. Entry points and diagrams use singular-owner or neutral wording;
the GitHub URL is now `https://github.com/darkcenturies/gta-workshop`. The
existing canonical checkout folder stays `sp-rp-public-research` and its origin
uses the new URL. Active workshop/index links are updated. Third-party author/team credits
remain attribution rather than a description of this project's ownership.

## Result

The [atlas](../docs/GTA-WORKSHOP.md) has five separately labeled maps:
ownership/mandatory return, complete task flow, dependencies, Dryxio references
and publication gates. Across them there are **97 nodes and 133 edges**.
The [component catalog](../docs/workshop/CATALOG.md) and structured companion
record **36 entries across 10 owner routes**, including the separate bot branch
and external third-party re3 route. The catalog expands grouped native suite
nodes, public components, historical source gaps, server components, SRG,
Upstate, assets, rendering, Launcher and supporting services.

The [publication backlog](../docs/workshop/PUBLICATION-BACKLOG.md) distinguishes
already public work, proposals and withholding reasons. [Worked task routes](../docs/workshop/EXAMPLES.md)
show Doctor, SRG, CLEO, Upstate and server/rendering examples. These examples
describe routes; they are not newly executed game experiments.

## Methods and actual validation

- Consulted existing public instructions/source catalog, private owner READMEs,
  source entrypoints and the current Dryxio inventory. Only public-safe ownership,
  role, target and workflow descriptions were incorporated.
- Verified all 36 component source entrypoints and all 10 owner entrypoints
  against their canonical checkouts. Verified that every catalog ID appears in
  the human catalog and every referenced Dryxio repository resolves in the
  18-entry inventory. The separate texture reference is not counted as a repo.
- Rendered all five source graphs with **@mermaid-js/mermaid-cli 12.0.0** using
  the shared config and an installed Chromium-family browser. Pure SVG labels,
  no embedded fonts, no HTML foreign objects and no remote asset payloads.
- Inspected the rendered maps and measured SVG text bounds and node bounds in
  the browser. No labels outside the canvas or overlapping nodes were found.
  Each SVG includes an accessible title and description. This geometric check
  does not prove that every edge is free of crossings; complementary maps and
  full-size image links keep different relations legible.
- Checked local documentation links, XML/SVG validity, UTF-8 replacement
  characters and public-safe source descriptions. Used labeled states with
  consistent colors rather than making visibility depend on color alone.
- Kept existing implementation hashes and dependency pins unchanged. The added
  allowlist paths are documentation, structured catalog, editable diagram
  sources, renderer configuration and rendered diagrams only.

Run `python tools/check_public.py` for the contribution's public boundary and
archive checks. Applicable repository CI still runs public native builds/tests.
Their outcome belongs in the contribution PR; no new runtime game validation
or production publishing is claimed by this documentation update.

## Limitations and remaining work

Visibility/ownership records are dated **2026-10-01**, not a live health monitor.
Dryxio references preserve existing evaluation status; none is promoted to
installed or runtime-tested by this atlas work. Historical private helper
READMEs may retain earlier target claims; the catalog marks those as evidence
to recheck rather than assuming current compatibility. Existing later-Map
source and standalone Nullfix source gaps remain unresolved.

Private source policy, source-review gates, input provenance and publication
authorization remain unchanged. Every task originating here must return
committed public-safe findings, including useful failed/blocked outcomes;
restricted evidence stays in its private owner. Follow
[AGENTS.md](../AGENTS.md#mandatory-return-of-findings) and the
[atlas maintenance guide](../docs/workshop/README.md) for future updates.

## Merged-branch lifecycle policy

On 2026-10-01 the owner requested automatic branch deletion on every owned
GitHub repository. The authenticated account's repository inventory contained
18 repositories with administrator permission. Set `delete_branch_on_merge`
to true separately on each, then read back each setting: **18/18 verified true**.
This settings audit inspected repository metadata only, not private contents.

Eligible branches from future merged PRs are automatically deleted. This action
did not delete existing branches, change code, change branch protection, or
deploy anything. Existing-branch cleanup remains a separate operation requiring
merged-work and active-owner/worktree checks. The agent instructions record the
policy so future sessions keep automatic deletion enabled.

## Repository organization review

On 2026-10-01 the owner requested a GTA repository inventory, organization
ratings and consolidation recommendations. This was a read-only structural
review of tracked layouts, current entry-point documentation, ownership rules,
build/test entry points and repository metadata. It was not a fresh gameplay,
security, licensing or code-quality assessment. No repositories were combined.

The review found useful separation between the public GTA Workshop, private
shared mod development, SP-RP server, website and GTA Midnight conversion.
Launcher and rendering-kit repositories also serve broader game workflows.
Public Phone remains an independent build with reviewed shared-source exports.

Concrete documentation inconsistencies remain: this repository's
PUBLIC-RESEARCH-ORGANIZATION.md still describes obsolete mod directories, the
Phone maintenance guide uses the old public repository name, and its GitHub
description still advertises retired partner compatibility. Historical export
snapshots in the private Workshop and the Phone's adapted public source copy
increase maintenance/navigation costs. Those are observations, not permission
to delete historical material or export private additions.

Recommended next work is to reconcile canonical entry-point documentation,
clearly separate active source from historical exports/reference material, and
evaluate consolidating the already-public Phone scope into GTA Workshop. Such
a migration needs an explicit publication review, preserved licenses, adapted
independent build/package recipes and release continuity; it must not import
private history. Keep project-specific private conversions and independently
deployed server/site products separate unless a concrete dependency problem
justifies changing their ownership. The bot is already part of the server
remote through its distinct bot/live production branch, not another repository.

Private backup contents were not inspected. Restricted source details, local
worktree inventory and unrelated project inventory are withheld because they
are unnecessary for the public GTA workflow. CLEO AI was not run: repository
organization assessment has no CLEO script input. The existing public-boundary
and archive checker is the applicable validation for this findings return;
there is no claimed runtime or deployment result.
