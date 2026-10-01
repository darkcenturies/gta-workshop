# Agent instructions for GTA Workshop

The repository is maintained by darkcenturies as a solo developer. Use the name
**GTA Workshop** and singular-owner or neutral project wording in new docs,
diagrams and summaries. Do not describe the owner as a team or organization.
Preserve actual third-party team names and attribution when citing their work.

GTA Workshop is the main public entry point for these GTA projects. Start with
docs/GTA-WORKSHOP.md and research/dryxio-catalog.md, then choose the source
owner and visibility before implementation. Include SRG/GTA Midnight, Upstate,
GTA rendering and Launcher work in routing; the catalog is not limited to SP-RP.
Private code, logs and sensitive requests start in their private owner, never a
public staging branch. Consult the relevant Dryxio and original upstream
references, recording applicability, revisions and actual validation. Catalog
descriptions do not authorize new private source exports. PUBLICATION.md and
the existing implementation allowlist remain the code-release boundary.

GTA SDK: initialize `third_party/plugin-sdk` with `git submodule update --init --recursive`. Read docs/PLUGIN_SDK.md for its source map, pinned version and upstream setup. Existing released mod recipes do not require it.

Read docs/AGENT_START.md first: it contains the project map, build commands, archive-reading workflow, known gaps and scope. Then read CONTRIBUTING.md and the relevant component's README. This is a public research/mod repository, not the SP-RP server.

Build entry point: `./build.ps1 -CheckEnvironment`, then `./build.ps1 -Target doctor -Release` (or map, crashfix, repair, all). Setup and outputs are in docs/BUILDING.md. These use the installed MSVC x86 toolchain; the repository includes build recipes, not Microsoft's compiler. No server or game install is needed to compile.

Research entry point: docs/reverse-engineering/generated/index.json → target metadata.json → functions/symbols/named CSV indexes → bounded excerpts of decompiled.c/disassembly.txt. Do not read the whole archive into context. `python tools/check_public.py` includes the archive-integrity check. Keep observed facts separate from decompiler inference and historical notes.

Valkyrie Radar is unreleased and private. Do not export its implementation, renderer, routing component, tile pipeline or project-specific research notes. Shared Map code must not reintroduce private Radar additions; the public Map currently uses the earlier 0.2.0 baseline.

Full generated decompilation/disassembly and reconstructed pseudocode are intentionally public under docs/reverse-engineering/. Preserve target hashes, metadata and archive checksums. Do not treat the old private-only export rule as current policy. Keep private gamemode code, player data, production configuration and history out. Never copy a private repository wholesale. Use exact-version evidence for game addresses and signatures. Preserve upstream credits and directory-specific licenses. Distinguish archived observations from current verified behavior. Build and run relevant existing tests for changes; never install a mod or deploy to a server merely to validate a contribution.

## Mandatory return of findings

**Every task stemming from this repository must commit its public-safe findings
back to this repository, even when implementation happens in another repo.**
A chat answer, private code commit or external PR alone does not complete the
workshop task. Return the durable result here in the same session, push the
contribution branch and open a PR. Follow review and checks before merging;
this requirement does not authorize bypassing branch protection.

This applies to implementation, investigation, compatibility testing, failed
experiments, corrections and tools found unsuitable for the task. Record useful
negative results so the next agent does not repeat the investigation. Update
an existing relevant note instead of creating duplicate status documents.
Put project/visibility changes in docs/GTA-WORKSHOP.md, tool evaluations in
research, and component findings beside the existing component documentation.

Each return record must include, where applicable:

- The question/change, GTA target/version and implementation owner.
- The observation or outcome, distinguishing facts from inference.
- Tool/upstream revisions, evidence references and original attribution.
- Reproduction steps using permitted inputs, checks actually run and results.
- Limitations, useful failed approaches and unresolved questions.
- Safe implementation commit/PR/release references and accurate status:
  proposed, merged, released and deployed are separate states.
- What remains private and its withholding reason, without restricted details.

For private work, commit full restricted findings in the private owner and
return a sanitized summary here. Never copy private source, infrastructure
details, credentials, player records, private logs or restricted attachments
to satisfy this rule. Withhold private links/titles if they disclose sensitive
information. If substantive findings cannot safely be disclosed, still return
a safe task-category, owner, completion-state and withholding-reason record.

If access, validation or an actual review requirement prevents the return PR,
report the blocker and exact pending step. Do not claim local notes, unpushed
branches or unmerged PRs are already committed to public main.

## Routing and required reference workflow

Read the five colored maps in docs/GTA-WORKSHOP.md with
docs/workshop/CATALOG.md and catalog.json for individual component routing.
Task-flow arrows show execution order; dependency arrows point from consumer
to provider. Consult docs/workshop/EXAMPLES.md for end-to-end routes and
docs/workshop/PUBLICATION-BACKLOG.md for current/proposed/withheld outputs.
Maintain source facts, catalog entries, graph sources and rendered images
together using docs/workshop/README.md. Never treat graph color as live health,
catalog inclusion as source approval, or a tool-reference edge as installed use.

Read docs/GTA-WORKSHOP.md, docs/AGENT_START.md, CONTRIBUTING.md and PUBLICATION.md
before editing. Then read research/dryxio-catalog.md, the applicable original
upstream documentation, the component README and relevant build/research guide.
For work routed elsewhere, read that owner's AGENTS.md and publishing rules.
Use the private workspace index for owner navigation when available, without
copying its unrelated inventory or sensitive contents into this public repo.

Choose component ownership, GTA target and visibility before writing code,
issues, logs or attachments. Public branches, issues and draft PRs expose their
contents. Private work starts directly in the private owner, never in a public
staging branch. Use the canonical checkout; fetch and inspect status, update a
clean base if behind, preserve unrelated changes and use an owned worktree
when isolation is needed. Do not create extra clones.

Dryxio's GTA tools, mods and forks are required reference points where relevant.
Choose the task's go-to path from the catalog: CLEO, native ASI, engine analysis,
multiplayer or asset workflows. Follow applicable documented methods; record
non-applicability or limitations instead of silently skipping a relevant tool.
Preserve original upstream credits for forks. A metadata inventory is not
installation, source/license approval or evidence of runtime use.

CLEO AI applies to CLEO tasks. Record whether it actually ran, what input/output
was evaluated and what checks passed. Citing it does not prove it implemented
or validated native C++, C#, re3 or server code. Preserve the distinction between
earlier documentation reviews and the broader metadata-only inventory.
See research/dryxio-workflow.md and docs/GTA-SA-MOD-WORKFLOW.md. Do not replace
the existing reviewed SDK submodule pin merely because another SDK is listed.

## Scope, product direction and evidence

Catalog descriptions are permitted public documentation; they do not authorize
new source exports. New components require deliberate scope/provenance review.
Never change publication/approved-files.json just to make an unreviewed import
pass. Public Phone has its own reviewed dependency scope; private shared
additions do not become public because related baseline code is public.
SRG/GTA Midnight remains private under its owner policy and consumes Workshop's
Core. Upstate's public upstream is separate from the Workshop-owned private
compatibility patch.

The current SA direction is independent of PE/Project Silent Hill. Doctor and
Crashfix share one artwork-free ASI. Retire former partner runtime functions
and product profiles, preserving historical research, license provenance and
upstream credits. Other artwork is permitted where rights and component
requirements allow it; Doctor's restriction does not apply to every project.

Run python tools/check_public.py for every contribution, including documentation.
For code, run relevant existing builds/tests. For documentation, verify links,
paths, references and status accuracy. Add reviewed new files to the Git index
before the boundary check because it examines tracked paths. A passing check
does not itself approve an export. Compilation, automated tests and in-game
validation are different evidence; record only what actually ran and its limits.

## Commits, pushes and publishing

Inspect origin, branch and working-tree changes first. Use a task branch from
current main (or the existing contribution branch); stage explicit paths, inspect
`git diff --cached` and run `git diff --check`. Run `python tools/check_public.py`
and applicable builds/tests described above, then commit, push the branch and
open a PR. Preserve unrelated edits and the independent public Git history.
Never merge or mirror private repository history into this repository.

Commit subjects must be full plain sentences suitable for a public changelog.
When implementation is elsewhere, coordinate both contributions: the owner
contains code and restricted evidence; this repo contains public-safe return
findings. Update the project map and relevant entry points when visibility,
ownership or the go-to workflow changes. Report the actual commit/PR and merge
state, not a proposed outcome as completed work.

Pushing starts .github/workflows/checks.yml; it does not deploy sp-rp.com, install
mods or publish website downloads. A GitHub release, a website download and a
source merge are separate outcomes. Website publication is handled by its owning
repository and release process; report only actions actually completed.

For maintainer imports, accept only an intentionally reviewed public snapshot.
Keep existing public scope and licenses, review all added/removed files, and run
this checkout's current checks. A passing credential/path check alone is not
proof that newly added implementation was approved for public release.
For the GTA SA refresh, use docs/GTA-SA-MOD-WORKFLOW.md. Doctor and Crashfix now build into one ASI. Former partner editions and product profiles are retired; preserve historical research and license provenance.
