# From research to a verified improvement

Choose one concrete question and [implementation owner](REPOSITORIES.md).
Consult [Dryxio references](../research/dryxio-catalog.md), original upstreams and
the exact-target [archive](reverse-engineering/README.md). Public research
records evidence; implementation happens in its owner.

## Collect bounded evidence

Record target/version, input SHA-256/size, architecture, image/load base and
VA/RVA for binary addresses. Record source revisions and actual installed
tool/package versions separately. Search indexes before reading large outputs.

Separate observed bytes/behavior from decompiler inference, upstream claims and
hypotheses. Check layout, signatures and calling conventions before applying
native hooks. For authoring work use permitted original/synthetic fixtures in
public reproduction; game-derived payloads remain private/local.

Defined analysis/export tools are public under tooling/; experimental runtime
implementations remain private.
Follow their owner's recipes. Methods, generated evidence and sanitized results
remain public; a historical source path is not a file available in this tree.

## Implement and validate in the owner

Use the canonical checkout or shared worktree. Preserve unrelated work, run the
relevant existing build and behavioral checks, and report skipped/unknown gates.
Compiler success, test success, package integrity and actual gameplay are distinct.

For generated research compare file hashes/sizes with the published checksum
ledger. Retain original provenance and exact target metadata. Intentional
regeneration needs reviewed changes to metadata and both checksum records.
Do not regenerate archives merely to repair documentation.

## Return the durable outcome

Use [the finding template](../research/finding-template.md). Record the question,
owner, target/revisions, method, evidence, observations/inference, actual checks,
limitations, failed approaches and remaining questions. Commit/push safe findings
through a workshop PR even when implementation stays private.

Preserve full restricted evidence in its private owner. Public return records
explain withholding without exporting code, private history, data or assets.
A failed or unsuitable method is useful evidence; record it accurately.

Review, source merge, binary release and deployment are separate outcomes.
