# Experimental S&SMP / PE 0.3.DL adapter

**Status, 2026-09-12: not release-ready. The user reports that the standalone adapter still crashes when connecting through the official open.mp launcher from Steam.** This is a source and research checkpoint for the S&SMP developer, not a supported plug-and-play release.

## What is included

- `source/`: single-ASI runtime adapter, tested baseline guard, 303 generated address edits, and statically linked MinHook source with its license and pinned revision.
- `baseline/`: historical two-file patch builder, complete instruction inventory and candidate mapping, guard source, and reproduction evidence. This changes a separately generated copy of S&SMP; the standalone adapter instead changes process memory.
- `optional-untested/`: five additional generated lookup forms, compiled during development but not included in either successful test. Do not silently substitute this variant.
- [Engineering findings](BASELINE-ENGINEERING.md), [current test status](SESSION-STATUS.md), historical patch manifest, and environment fingerprints.

No game/vendor binaries, game assets, IDBs, crash dumps, private server configuration, or credentials are included. Obtain your own exact inputs. Original adapter contributions follow the repository BSD-3-Clause license; MinHook retains its included upstream license. Binary-derived research is subject to the repository research scope notice.

## Exact input fingerprints

| Input | SHA-256 |
| --- | --- |
| Original S&SMP 1.3.1 Patch 1 `ssmptw.asi` | `47daa8ce8152de39a25f04aecdf0843a449ed941d5705aa2e087ec0f59cf98eb` |
| open.mp cached 0.3.DL `samp.dll` | `bccdb297464bd382625635be25585df07a8fa6668bc0015650708e3eb4ffcd4b` |
| R3-1 recognized pass-through, not gameplay tested | `9c9b2cc31a4ced6967420b1880c096b5c4e7630e227aa379be4019c21b6fddc1` |

These are exact versions, not a compatibility claim for every PE, FLA, R3, or DL build. R3-1 must not be confused with R3.

## Build the single ASI

From an **x86 Visual Studio Native Tools Command Prompt**:

```bat
cd research\ssmp-dl-adapter\source
build.cmd
```

Output: `source/build/!PE-DL-Adapter.asi`. The original build used Visual Studio 2019, `/O2 /MT /EHsc /W4`. No Python or vendor input binary is required to compile the standalone source. Compiler timestamps can change the full-file hash.

For controlled testing, close GTA and put that one ASI beside an **original** `ssmptw.asi`, keeping the leading exclamation mark. Do not combine it with the historical patched S&SMP or guard DLL. It does not overwrite S&SMP or extract a helper. To undo, close GTA and rename only the adapter to `.asi.disabled`. Hot unloading is unsupported.

The adapter hooks GetModuleHandleA and acts at two identified S&SMP call sites. It checks exact disk hashes and expected operand bytes, applies 303 runtime edits, and initializes the integrated guard. Initialization timing and loader-lock behavior still need review: much of this prototype's setup originates in DllMain. Guard rejection terminates the process; transactional rollback is not implemented.

## Developer priorities

1. Reproduce the official launcher / Steam crash and capture a fresh dump. The latest available log stops at `Standalone ASI armed before S&SMP module lookup`; there is no evidence that all runtime patches were reached in that launch.
2. Verify all candidate mappings semantically, including direct patch payloads, stored/derived pointers, calling conventions, layouts, overwrite lengths, and continuations.
3. Review initialization ordering and replace brittle generated-code scanning with a supported shared model-table interface where possible.
4. Audit lifecycle/reconnect, the five remaining lookup forms, positive-ID coexistence and the separate `plugins/ssmp-rpc.asi`.
5. Run official-launcher DL and unchanged R3 regressions covering downloads/cache reuse, movement/collision, vehicles, custom artwork and multiplayer synchronization.

Server dual-client acceptance and a reachable artwork HTTP endpoint remain separate requirements. This adapter does not make a localhost development CDN reachable to remote players. The observed 8416 count was downloadable files, not screen resolution.
