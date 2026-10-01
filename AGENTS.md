# Agent instructions for GTA Workshop

GTA Workshop is maintained by darkcenturies as a solo developer. Use singular
owner or neutral project wording. It is the public starting point and knowledge
return destination for GTA III, Vice City and San Andreas work, including mods,
servers, multiplayer, conversions and asset authoring.

## Read and route before acting

Read README.md, docs/README.md, docs/GTA-WORKSHOP.md, CONTRIBUTING.md and
PUBLICATION.md. Choose the task from docs/workshop/CATALOG.md and catalog.json.
Read research/dryxio-catalog.md and applicable original upstream documentation.
For implementation read the owner's AGENTS.md, component guide and publishing
rules. Never use this public repository as staging for private work.

The public tree contains guides, catalogs, editable graphs/rendered SVGs,
findings, target metadata, checksums and approved generated research archives.
It contains no mod source, authored tools, experimental adapter implementation,
build recipes, SDK submodules or release packages. Illustrative guide snippets
are instructions, not packaged implementation.

Doctor/Crashfix, Map and Repair now belong to private Valkyrie Workshop.
Phone remains public in valkyrie-phone and independently buildable.
SRG/GTA Midnight remains private and consumes Workshop Core. SP-RP, its website,
bot, Upstate, rendering and Launcher keep their named owners. Cataloging a
component does not approve publication of its implementation.

## Mandatory return of findings

**Every task stemming from this repository must commit its public-safe findings
back here, even when implementation happens in another repository.** A chat
answer, private commit or external PR alone does not complete the workshop task.
Commit/push the contribution and open a PR in the same session. Follow required
review and checks; normal maintenance does not authorize bypassing protection.

This covers implementation, investigation, failed experiments, compatibility
tests, corrections and tools found unsuitable. Useful negative outcomes prevent
the next agent repeating a failed investigation. Update the related existing
note rather than making another parallel status document.

Each return record includes, where applicable:

- Question/task, exact GTA target/version and implementation owner.
- Observation/result, clearly separated from inference or upstream claims.
- Tool/package versions, source revisions, attribution and evidence references.
- Reproduction with permitted inputs and commands actually run.
- Actual checks/results, skipped gates, limits and remaining questions.
- Safe commit/PR/release reference and accurate proposed/merged/released/deployed state.
- Withheld scope and reason, without restricted implementation or private details.

Commit full restricted findings in the private owner. Return a sanitized summary
here; do not export restricted source, history, infrastructure, private logs,
credentials, player records or assets to satisfy this rule. If substantive
details cannot be shared, still return a safe task-category, owner, completion
state and withholding reason. Report actual access/review blockers accurately.

## Reference methods and tool applicability

Use the Dryxio catalog as required starting research. Choose relevant CLEO,
native ASI, engine, multiplayer, graphics or authoring routes rather than
installing every tool. Preserve original upstream authors and fork parents.
Record revision, target, license/provenance questions and actual evaluation.

CLEO AI applies to actual CLEO scripts. Record whether it ran, evaluated
inputs/outputs and checks. A catalog citation does not establish native C++,
C#, re3 or server validation. Documentation review, metadata inventory,
installation, compilation and gameplay testing are different evidence.

For native hooks use exact executable hashes, architecture, signature bytes,
addresses/VA/RVA, layout and calling conventions. SDK declarations and compiler
success are insufficient to establish ABI or gameplay correctness.
For asset work use permitted original/synthetic inputs for public reproduction.
Game-derived authoring payloads and generated game installations stay with
their private/local owners.

## Research archive workflow

Start at docs/reverse-engineering/generated/index.json, target metadata and
function/symbol/named CSV indexes. Search before reading bounded excerpts of
decompiled.c/disassembly.txt. Do not dump entire large archives into context.

Retain exact target hashes, metadata, coverage and file checksums. Generated
decompilation/disassembly and reconstructed pseudocode are explicitly public
research evidence; they are not original vendor source, licensed project-owned
implementation or an assertion of complete semantic understanding.
Approved IDA databases are evidence with their separate manifest.

Authored exporter/analysis scripts and experimental adapter source are private.
Their methods and dated observations can be documented here. Historical notes
may describe removed source paths: follow their private provenance reference
instead of recreating that code in this public repository.
Never infer current compatibility or affiliation from historical target names.

For archive changes compare exact SHA-256 and sizes with the published checksum
ledger. For deliberately regenerated evidence review original attribution,
permitted inputs, methods and metadata; update ledger and SHA256SUMS together.
Do not regenerate evidence merely to fix prose or naming.

## Catalog and graph maintenance

README is the concise overview; docs/README.md indexes guides;
docs/STRUCTURE.md defines file placement. Keep these consistent with the actual
knowledge-only tree. docs/workshop/catalog.json and CATALOG.md describe all
components, including implementation outside this repository.

Update owner, target, source state, withholding reason, validation and return
requirements in both catalogs. Update affected .mmd sources and rendered SVGs
together using docs/workshop/README.md. Preserve stable component IDs.

Five maps separate routing, execution order, dependencies, reference selection
and publication. Dependency arrows point consumer to provider; task-flow arrows
show execution order. Node labels carry meanings as well as colors. Catalog
inclusion is not source approval; graph color is not live health.

New public knowledge files require reviewed inventory entries. Keep generated
research evidence hashes exact. Source/build/package directories are prohibited.
The allowed implementation owners and privacy boundaries are not broadened by
a guide, code snippet or passing check.

## Git, review and history

Use the canonical checkout or a shared worktree, never another clone of an
owned repo. Fetch and inspect status first; update a clean behind base. Preserve
unrelated edits. Stage explicit paths, inspect the staged diff and whitespace,
run relevant scope/link/archive checks, then commit/push and open a PR.
Commit subjects are full plain sentences suitable for a public changelog.

Eligible merged branches must be automatically deleted; keep GitHub's
delete_branch_on_merge enabled. Existing branch cleanup requires merged-work,
owner and active-worktree checks. Never casually delete permanent source branches.

The owner explicitly authorized the 2026-10-01 knowledge-only history replacement
after private preservation. That one-time migration is not permission for future
history rewrites. Older public PR views/caches and downloaded copies may retain
past implementation; fresh active history is not a recall mechanism.

## Product direction and publishing

Maintained mods target classic GTA SA independently of former partner editions.
Doctor/Crashfix shares one artwork-free ASI in its private owner. Other permitted
artwork remains allowed. Preserve historical evidence, rights and attribution
without restoring retired runtime profiles.

Documentation/research merges do not build or install mods, release binaries,
publish website downloads or deploy a server. Those actions follow the owner's
separate authorization and release process. Verify only task-relevant checks,
report actual results and leave production verification to the owner.
