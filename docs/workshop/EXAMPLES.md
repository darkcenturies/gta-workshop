# Worked reference routes

These examples explain methods; they are not claims of newly executed builds or
gameplay tests. Consult [the catalog](CATALOG.md) and
[agent requirements](../../AGENTS.md).

## Add a scripted interaction

Define the exact GTA SA/CLEO profile and a minimal interaction. Read CLEO AI
and opcode/library references. Check supported opcodes and required runtime,
validate and compile in your script project, then exercise the behavior in the
target game. Return the method, actual outputs, tested scenarios and failures.
Record whether CLEO AI was actually used; do not infer use from a citation.

## Investigate a native crash

Record executable hash, architecture, crash location and reproduction. Consult
SDK/engine references and bounded binary evidence. Check signatures, calling
conventions and layouts before implementing a focused fix in your plugin repo.
Report compilation, fixture tests and gameplay separately. Publish safe evidence
and reasoning without exporting restricted logs or implementation.

## Change a map or traffic route

Choose authoring references for the exact game/file format. Use an original or
permitted synthetic fixture to document import, edit and export. Check a
deterministic roundtrip and graph/format integrity, then loading and behavior
in the game separately. Return revisions, provenance and observed limits;
do not upload game-derived asset payloads.

## Study a multiplayer interface

Choose matching client/server versions and relevant source/documentation.
Compare protocol observations with bounded archived evidence. Reproduce with
synthetic inputs, distinguish byte-level matches from inferred semantics and
record incompatible cases. Keep player/account and operational data excluded.

## Compare graphics or navigation behavior

Read graphics/GPS/radar references and original fork parents. Record game target,
mod combination, configuration and measurement method. Compare only scenarios
actually exercised, including performance or device/reset behavior where
relevant. Publish reproducible observations and dependency limits, not assumed
compatibility across all profiles.
