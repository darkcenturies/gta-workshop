# Public decompilation and reverse-engineering archive

This is the full completed generated research export, not just a summary. It contains decompiled C-like output, full disassembly, function/symbol/string/call CSV indexes and exact-version metadata. The independently reconstructed S&SMP interface pseudocode is included separately.

## Completed targets

| Target | Decompiled / internal functions | Failed functions |
| --- | ---: | ---: |
| [ssmp-server-1.3.1-patch1](generated/ssmp-server-1.3.1-patch1/) | 1,121 / 1,121 | 0 |
| [ssmp-client-1.3.1-patch1](generated/ssmp-client-1.3.1-patch1/) | 2,364 / 2,364 | 0 |
| [project-eagle-core-current](generated/project-eagle-core-current/) | 7,617 / 7,617 | 0 |
| [gta-sa-1.0-us](generated/gta-sa-1.0-us/) | 20,820 / 20,823 | 3 |
| [gta-sa-ps2-1.00-de](generated/gta-sa-ps2-1.00-de/) | 8,533 / 8,533 | 0 |
| [gta-sa-ps2-2.01-eu](generated/gta-sa-ps2-2.01-eu/) | 8,523 / 8,523 | 0 |

The machine-readable [index](generated/index.json) records binary sizes and SHA-256 hashes. Each target's metadata.json records architecture, format and recovery counts. The 30 files of the first four targets are preserved byte-for-byte from the research export. The two PS2 targets were exported on 26 September 2026 with deploy/decompile-ssmp-pe.ps1, Ghidra 12.1.3, PyGhidra 3.1.0 and JDK 25; see [the PS2 version comparison](../../research/gta-sa-ps2-1.00-vs-2.01.md). [checksums.json](checksums.json) also covers the reconstructed pseudocode.

- [S&SMP reconstructed pseudocode](ssmp-server-1.3.1-patch1.pseudo.cpp)
- [GTA named function index](generated/gta-sa-1.0-us/named.csv)
- [Ped population findings](PECORE-PED-POPULATION.md)
- [Historical August checkpoint](CHECKPOINT-2026-08-23.md)
- [Reproduction guide](REPRODUCING.md)
- [Research scope and rights notice](NOTICE.md)

## Reading and contributing

Start with metadata.json and functions.csv, then look up an address in decompiled.c and disassembly.txt. The GTA archive additionally has named.csv mapping recovered addresses to names. Large files may exceed GitHub's browser preview limit; clone the repository to search them locally. No Git LFS is required for these files.

Decompiler output is an analysis reconstruction. Names, types and control flow may be approximate; failed recovery is retained in the coverage record. This is not a claim to possess the vendors' original authored source or build system. Treat inferred meanings as hypotheses until verified.

The launcher, memory cleaner and extra RPC target listed in research/targets.json have no completed export in this snapshot. They are not silently counted as complete. Upstream reference repositories remain linked in research/upstreams.md rather than copied into this collection.

The owner approved public publication of this archive on 10 September 2026, superseding the earlier private-only export rule. That scope change does not include the SP-RP gamemode, player data, production configuration, input executables or private Git history.

## IDA databases

[SA-MP IDA archive](ida/README.md): nine upstream reference databases, with provenance and SHA-256 checksums.
