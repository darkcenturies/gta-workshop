# Agent instructions for GTA Workshop

GTA Workshop is maintained by darkcenturies as a solo developer. Use singular
owner or neutral project wording. It is a public reference library and knowledge
return destination for anyone learning GTA III, Vice City and San Andreas
mod-making, multiplayer, engine research and asset authoring. Organize by
techniques and research questions, not the maintainer's products.

## Read and route before acting

Read README.md, docs/README.md, docs/GTA-WORKSHOP.md, CONTRIBUTING.md and
PUBLICATION.md. Choose the task from docs/workshop/CATALOG.md and catalog.json.
Read research/dryxio-catalog.md and applicable original upstream documentation.
For implementation read the owner's AGENTS.md, component guide and publishing
rules. Never use this public repository as staging for private work.

The public tree contains guides, catalogs, editable graphs/rendered SVGs,
findings, target metadata, checksums and approved generated research archives.
It also contains public source, helpers, launcher and examples for the ten
defined Valkyrie tool families under tooling/. It contains no mod source,
runtime adapter implementation, SDK submodules or mod release packages.
The owner explicitly authorized public tool source on 2026-10-01; this supersedes
earlier documentation-only rules for those families, not for unrelated tools.

Private product inventory, ownership and canonical local routing belong in the
maintainer's private workspace index, not this library. Public reference links
must teach a relevant technique or support evidence, with original attribution.
Historical findings may retain target names without becoming project navigation.

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

- Question/task, exact GTA target/version and a shareable project reference when relevant.
- Observation/result, clearly separated from inference or upstream claims.
- Tool/package versions, source revisions, attribution and evidence references.
- Reproduction with permitted inputs and commands actually run.
- Actual checks/results, skipped gates, limits and remaining questions.
- Safe commit/PR/release reference and accurate proposed/merged/released/deployed state.
- Withheld scope and reason, without restricted implementation or private details.

Commit full restricted findings in the private owner. Return a sanitized summary
here; do not export restricted source, history, infrastructure, private logs,
credentials, player records or assets to satisfy this rule. If substantive
details cannot be shared, still return a safe reusable task-category, method, completion
state and withholding reason without enumerating private projects. Report actual access/review blockers accurately.

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

Defined exporter/analysis tools are public under tooling/. Experimental runtime
adapter source and mod implementations stay outside this repository.
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
reference/research/tooling tree. docs/workshop/catalog.json and CATALOG.md describe all
task families, upstream references, evaluation status and validation methods.
They must not catalog private products. Public tool source links are encouraged.

Update reference applicability, revisions, fork-parent attribution, evaluation
status, validation and return requirements in both catalogs. Update affected .mmd sources and rendered SVGs
together using docs/workshop/README.md. Preserve stable topic IDs.

Five maps separate library navigation, learning workflow, evidence requirements,
reference selection and publication boundaries. Evidence arrows point method to requirement; task-flow arrows
show execution order. Node labels carry meanings as well as colors. Catalog
inclusion is not source approval; graph color is not live health.

New public knowledge files require reviewed inventory entries. Keep generated
research evidence hashes exact. Mod source/build/package directories are prohibited. Defined tool source
and its reviewed examples are allowed under tooling/ and must match registry hashes.
Publication boundaries are not broadened by
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

## Publishing and library identity

Keep the README concise and useful to any GTA modder. Navigation, catalogs,
diagrams and worked routes describe references, techniques and evidence.
Do not add a private product roster, local checkout map or internal release
roadmap. Keep historical implementation notes dated and subordinate to research.
Original target names and required credits remain in evidence where relevant.

Documentation/research merges do not build or install mods, release binaries,
publish downloads or deploy a server. Those actions follow the implementation
project's separate authorization and release process. Verify task-relevant
checks and report actual results. Finished verified maintenance must be pushed
and merged in the same session under the owner's standing merge instruction;
preserve protections and report any actual blocker rather than leaving work
silently on an unmerged branch.

## Valkyrie method families

Read docs/VALKYRIE-TOOLING.md and catalog.json method_families for the ten
reviewed public method notes. Stable valkyrie-* names describe technique
families. Actual source paths and launcher IDs are in tooling/registry.json;
do not rebrand external dependencies.
Keep descriptions, route IDs, evaluation states and limits consistent. Do not
add private mod implementation, product owners or personal local paths to
public entries. Link public tool source and state dependencies honestly. Deferred techniques need provenance and reproducibility review before
publication. Source/documentation review does not imply executed tool use.

## Tool source checks

Only export the ten defined families and directly required helper code. Keep
original attribution, explicit source paths and hashes; never copy private Git
history, mod implementation or game inputs. Update tooling/registry.json, catalog
source links and approved-files.json together. Stage explicit files, run
python tooling/check_inventory.py and the three valkyrie.py synthetic demos,
verify unchanged research checksums and documentation links. Other legacy
tools are source-published with prerequisites; do not claim they all executed.
