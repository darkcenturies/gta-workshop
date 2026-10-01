# From an upstream lead to a verified Valkyrie improvement

Use this workflow for released mods and public interoperability research. The [Dryxio review](../research/dryxio-workflow.md) supplies candidate tools and evaluation tasks. It does not establish compatibility or require installing those tools.

All GTA tasks start with [the complete workshop map](GTA-WORKSHOP.md) and
[Dryxio catalog](../research/dryxio-catalog.md). Consulting applicable references
is required; record why a relevant method fits or does not fit. Then implement
in the selected public/private owner. The catalog includes SRG, Upstate,
rendering and server work without importing their private source here.

Every task originating here must return a committed, pushed public-safe findings
record and PR here, even when another repository owns the implementation.
Keep restricted evidence in its private owner and return a sanitized outcome,
validation and withholding reason. Follow [AGENTS.md](../AGENTS.md#mandatory-return-of-findings)
for the required contents and completion conditions.

## 1. Define one question and its owner

Choose one failure, declaration, protocol field or authoring task. Start from [AGENT_START.md](AGENT_START.md), the component's README and its existing tests. Shared/private Valkyrie work must follow the owning repository's workflow. Keep public findings limited to this repository's approved scope.

For binary work, record product, executable size/SHA-256, architecture, load/image base and whether an address is a VA or RVA. Resolve the archive target via `docs/reverse-engineering/generated/index.json`. A matching product name or “1.0 US” label alone is insufficient.

## 2. Freeze references and collect bounded evidence

Use [dryxio-upstreams.json](../research/dryxio-upstreams.json) or [upstreams.md](../research/upstreams.md) to select a recorded source revision. Record actual installed package/tool versions separately: a repository commit is not an installed wheel version. Check root and dependency notices before code reuse.

Search our function/symbol/named indexes first, then read only relevant assembly/decompilation excerpts. For a Bridge trial, establish how matching Ghidra inputs are exported; do not relabel our archive as bridge output. Keep local projects, candidate output and unreviewed evidence under ignored `work/`. Preserve existing archive metadata/checksums.

Each observation should cite its source commit/path or exact-target address. Label decompiler types, upstream claims and hypotheses explicitly. For SDK comparisons, check declaration, size, offsets, calling convention and original bytes; compile success alone does not validate ABI correctness.

## 3. Keep experiments reviewable

Fetch/status the canonical checkout and preserve unrelated work. Use a task branch or `git worktree add` for isolation, never another independent clone of an owned repository. Keep candidate changes separate until evidence and applicable licenses have been reviewed.

Before using ReAgent, inspect its pinned configuration documentation, validation commands, provider and attempt limits. Resolve its project-copy validation behavior against our worktree rule; do not use its default copy example unchanged. Prefer direct argument arrays for Windows commands. Require meaningful validation, report `UNKNOWN`/skipped gates, and use `--strict-exit` if standalone parity status is used as a gate. Model/parity agreement still needs independent evidence.

For authoring work, record tool/channel, original inputs, changed object transforms, editable source and before/after previews. Prefer an isolated output destination with an undo path. Game-derived models/textures and catalogs stay local; public reproduction can use synthetic fixtures.

## 4. Verify the relevant result

| Claim | Required evidence |
| --- | --- |
| Public archive/boundary remains valid | `python tools/check_public.py` (also runs archive integrity checks) |
| A released mod builds | [BUILDING.md](BUILDING.md): check environment, then build affected target in Release |
| A guard or repair behavior passes existing checks | Relevant Crashfix native tests or Repair self-tests; explain which scenario they cover |
| SDK layout/signature is correct | Exact-target binary evidence plus compile-time size/offset checks where applicable; runtime evidence for calls/hooks |
| Traffic/asset output roundtrips | Deterministic hashes, independent reread, intended changes and unchanged portions checked separately |
| A behavior works in game | Exact executable/mod stack, reproduction steps and observed result from a separate runtime test |

Run only relevant existing checks for the actual change. Do not install a mod or deploy a server to validate a contribution. A documentation/source review does not earn a runtime-pass label. [Archive reproduction](reverse-engineering/REPRODUCING.md) remains a separate intentional operation.

## 5. Record, review and hand off

Use [finding-template.md](../research/finding-template.md). Include the upstream commit, target hash, evidence paths, commands/results, skipped checks and unresolved questions. Sanitize local paths/logs and exclude private data and vendor inputs before publication. Never refresh checksums merely to hide unexplained archive changes.

Submit a scoped PR with explicit staged paths and actual validation. Public acceptance does not deploy anything. A consuming Valkyrie/server repository records the accepted public revision, preserves notices and validates its own affected product before a release. Shared Phone changes must be reconciled with their owner through that repository's reviewed synchronization process; this guide creates no automatic mirror or deployment.
