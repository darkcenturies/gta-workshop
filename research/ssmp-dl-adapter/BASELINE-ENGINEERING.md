# Historical baseline engineering findings

For the current standalone adapter and unresolved official-launcher crash, read README.md and SESSION-STATUS.md. This document describes the earlier two-file baseline.

## Exact inputs

All addresses below are module RVAs unless explicitly identified as GTA absolute addresses. The address inventory was based on the R3-1 binary; do not silently substitute another R3 build.

| Input | SHA-256 |
|---|---|
| Original S&SMP 1.3.1 Patch 1 ssmptw.asi | 47daa8ce8152de39a25f04aecdf0843a449ed941d5705aa2e087ec0f59cf98eb |
| open.mp cached 0.3.DL samp.dll | bccdb297464bd382625635be25585df07a8fa6668bc0015650708e3eb4ffcd4b |
| Tested patched ssmptw.asi | 76d4e0a72cd9c9875331bd8359f0bbdeaeb28a572d6cff9d992d6822858e5301 |
| Tested guard DLL | 5d9c8392a5741d567c68060a97f6097071c5c127bccef5b18e220da597a7eb82 |

Other relevant installed inputs are fingerprinted in test-environment-sha256.json. The startup chat label still says R3; the guard hashes the loaded DLL to identify DL independently.

## Client changes

1. **Address dependencies:** the patch builder changes 294 instruction operands, plus nine stored patch destinations (303 sites). Candidate mappings cover 227 unique source offsets. These are not 227 independently proven function contracts; complete semantic review remains necessary.
2. **Bootstrap and ASLR:** a new `.pedl` section calls the exact-DLL guard through both S&SMP cached module getters at 0x3ECE and 0x1784D. Retire HIGHLOW relocations at 0x3ED0 and 0x1784F because the replacement calls use relative displacements.
3. **DL identification:** suppress S&SMP's version-pointer overwrite at 0x14A10 and retire relocation 0x14A12. Replacing DL's string with `0.3.7` while retaining DL's length was inconsistent. The S&SMP protocol trailer was not removed.
4. **Stored patch destinations:** S&SMP table 0x510FC..0x5111C now targets DL `[A7657,A760C,B3A03,A07B5,A764E,B39D9,B3D0B,B3D4B,B3D8B]`. The old write to B387B corrupted an unrelated DL pool getter. See the manifest for original values.
5. **Frame names:** replace DL reader 0xA5C10 with a bounded cdecl reader using GTA RwStreamRead at absolute 0x7EC9D0. Consume the complete chunk, retain at most 23 characters plus terminator, and log actual truncation. The observed 24-byte `Para_Harness_SpineTrace` chunk only had padding and was preserved. Truly longer names need reference-identity review; truncation is not a universal asset conversion strategy.
6. **Signed model space:** DL indexes negative custom object IDs. Pointing DL solely at PE's positive table caused an access violation at A76CA for -3500 after downloads. Allocate a table with indices -32768..199999, copy PE's 200000 positive pointers, set DL slot 0x152AE0, and change the initialization copy count at A7606. Raise DL base validation at D56B to 199999 after checking exact bytes. Keep the original PE allocation as the initialization source, not as the active DL lookup table.
7. **S&SMP readers:** replace its stdcall getter at ED5F, and change the ModelPointers initialization load at 12DE0 to the shared allocation. The base source pointer remains separate. Replace DL's stdcall ped-type checker at B39D0 with the corresponding shared-table check.
8. **Relocated lookups:** the DL installer A7560 recognizes original GTA instruction bytes, but FLA moved hundreds of lookups into executable trampolines. Skin 21999 was a correct CPedModelInfo in DL's shared table while GTA read the old CAtomicModelInfo at the same ID. Reimplement the installer over its version-selected table (152AE8 or 1538B8, 0xDCF bytes of 5-byte records), update 418 recognized native operands, and find 282 generated x4-indexed operands through their exact old table pointer and jump back to a known DL continuation. Then set initialized flag 1E0444. Changing leftover bytes at the original GTA site does not update the trampoline actually being executed.

The tested source retains verbose skin-21999 diagnostics. Its DLL name, export spelling and x86 calling conventions matter: `_ValidateSamp@4`; model getter and ped checker are stdcall, frame reader and table installer are cdecl. Replacements jump to complete functions, so no truncated original instruction is resumed.

## Separate server/download issue

The built-in artwork listener answered HTTP 401 inside WSL but Windows TCP connections timed out. Specific host and Hyper-V TCP 7777 allow rules did not resolve it. A local Windows HTTP asset server on 127.0.0.1:17877 with `artwork.cdn` pointing there delivered all 8416 files successfully. The 8417 HTTP 200 log entries include one manual texture probe. This was a development transport workaround, not a client DLL fix, and its localhost URL must not be published to remote clients.

The local server's `network.acks_limit` changed from 3000 to 10000 after a measured 3688/sec burst. It is a local tuning result, not a universal recommended setting. Server backups were retained. Dual-client acceptance belongs to the open.mp server configuration; this client patch does not convert the server protocol or prove a new R3 regression pass.

## Remaining work before release

- Verify every candidate address against exact R3-1 and DL disassembly, including direct patch payloads, derived pointers, hook lengths, continuation targets, packed class layouts and calling conventions.
- Audit lifecycle: allocation ownership, disconnect/reconnect, skin unload/reload, resets and dynamic additions. Prefer a supported shared model-table interface in FLA/S&SMP over generated-code scanning.
- Investigate positive-ID overlap between installed PE objects/vehicles and downloadable skins; one successful skin does not prove all IDs can coexist. Audit remaining derived table pointers and allocations above the scanned 2GB address range.
- Five observed FLA trampolines add a helper call before the return jump. The optional source recognizes those with an additional helper-module check; this variant needs its own test. The tested build does not update those five.
- Audit the separately installed `plugins/ssmp-rpc.asi` (hash provided). It remained enabled in the successful run. An earlier A/B test did not implicate it in one startup crash, but that is not a full audit. It is distinct from Discord rich presence.
- Exercise official open.mp launcher selection, first download and cache reuse, remote HTTP/CDN, reconnect, map collision, extended vehicles, animations, passenger/player synchronization, and an unchanged R3 client on the same server.
- The prior branding artwork test used -31000, outside this server build's valid custom object range (minimum -30000). Choose an unused valid ID, register it successfully and retest rendering. Download success does not establish this invalid test worked.
- Replace generic rejection text referring to a nonincluded Restore-Eagle.ps1, add complete transactional initialization rollback, and improve failure diagnostics before distribution. The prototype terminates on guard rejection; it does not implement production in-process rollback.
