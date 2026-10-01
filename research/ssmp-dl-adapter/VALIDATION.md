# Checkpoint validation

Performed on 2026-09-12 before publishing this source checkpoint:

- Root `build.ps1 -CheckEnvironment` found Visual Studio 2019 Build Tools and the Repair compiler.
- Both checked-in x86 `build.cmd` recipes compiled successfully. The standalone adapter C++ compiled without warnings; vendored MinHook emitted its existing C4201/C4100/C4310/C4244 warnings.
- Both outputs have PE machine `0x014c` (x86).
- Rebuilt the historical binary from the original S&SMP input without modifying it. Output SHA-256 exactly matched `76d4e0a72cd9c9875331bd8359f0bbdeaeb28a572d6cff9d992d6822858e5301`.
- All 303 generated standalone address triples matched the historical patch manifest, converting instruction file offsets to RVAs using the original PE section table. This establishes data consistency, not semantic correctness of every candidate.
- `python tools/check_public.py` passed public-boundary, Python syntax and existing research archive integrity checks.
- `git diff --cached --check` passed after removing trailing whitespace from the copied bootstrap listing.

Build outputs are ignored and not distributed in this source commit. No game launch or installation change was performed for these publication checks. Runtime evidence and unresolved failure are in SESSION-STATUS.md.
