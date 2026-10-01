> Historical checkpoint from 23 August 2026. Its paused/unpublished status is superseded by the [current archive inventory](README.md); preserved as a record of the work at that date.

# S&SMP and Project Eagle decompilation checkpoint

Paused at the owner's request shortly after midnight on 23 August 2026. This
archive is intentionally **not committed or pushed yet** because four targets
remain incomplete.

## Completed and hash-verified

| Target | SHA-256 | Decompiled functions | Strings | Symbols | Output |
|---|---|---:|---:|---:|---|
| S&SMP 1.3.1 Patch 1 Linux `ssmp.so` | `100d63366daef700caab4998dfb1dde48bb7c3a5136ac7bca8a912a6237517f3` | 1,121 / 1,121 | 1,524 | 4,230 | `generated/ssmp-server-1.3.1-patch1/` |
| Current Patch 1 `ssmptw.asi` | `47daa8ce8152de39a25f04aecdf0843a449ed941d5705aa2e087ec0f59cf98eb` | 2,364 / 2,364 | 769 | 12,076 | `generated/ssmp-client-1.3.1-patch1/` |

Each completed directory contains:

- `decompiled.c`: best-effort C-like output for every recovered function;
- `disassembly.txt`: complete instruction fallback;
- `functions.csv`, `calls.csv`, `strings.csv`, and `symbols.csv`;
- `metadata.json`: format, language, hashes, and coverage totals.

These are decompiler reconstructions, not the original authors' exact source,
names, types, comments, or build system.

## Paused target

`ssmp-launcher-current` passed its input size/hash checks and spent about half
an hour in Ghidra's initial analysis. The process was interrupted cleanly on
request. It had not reached the export script, so its output directory contains
no files and is not represented in `generated/index.json`.

The diagnostic log remains outside Git at:

`build/reverse-engineering/logs/ssmp-launcher-current.log`

It contains repeated constructor-resolution warnings from optimized 64-bit C++
framework code. The log continued moving through new addresses until the pause;
there was no analyzer crash or target-level failure.

## Remaining targets

1. `ssmp-launcher-current`
2. `ssmp-memcleaner-patch1`
3. `ssmp-rpc-local-extra` (tracked separately because it was not in the official
   Patch 1 client archive)
4. `project-eagle-core-current`

## Reproducible toolchain

- Target hashes and provenance: `deploy/reverse-targets.json`
- Orchestrator: `deploy/decompile-ssmp-pe.ps1`
- Headless exporter: `deploy/ghidra_scripts/ExportDecompiled.py`
- Ghidra: official 12.1.3 release, downloaded outside Git; release ZIP SHA-256
  `93a5d11a9ad510622acaaf908c556a7b9b764d338e78a7567f3689bf5081fd54`
- Runtime: portable Temurin JDK 21.0.12.1 and PyGhidra 3.1.0 outside Git

The wrapper verifies each input's byte count and SHA-256 before analysis,
rejects outputs whose metadata hash differs, and includes only directories with
complete metadata in `generated/index.json`. Partial runs merge with previously
completed targets in that index.

## Resume

From the repository root in PowerShell:

```powershell
.\deploy\decompile-ssmp-pe.ps1 -Only `
  ssmp-launcher-current, `
  ssmp-memcleaner-patch1, `
  ssmp-rpc-local-extra, `
  project-eagle-core-current `
  -MaxCpu 4
```

After all six targets appear in `generated/index.json`, validate coverage and
repository size, document the final totals, then commit only the reverse-
engineering files. Do not include the unrelated in-progress 3D panel changes.
