# Test status — 2026-09-12

| Configuration | Observation | Limit |
| --- | --- | --- |
| Historical patched S&SMP + guard, isolated PE copy | User confirmed it worked after the skin crash was fixed; log showed 418 native / 282 generated lookup updates. | Custom launch harness using DL and open.mp client, not official launcher UI. Full regression incomplete. |
| Original S&SMP + standalone ASI, isolated PE copy | Log confirmed 303 runtime edits, 418 native / 282 generated updates and skin setup; process remained responsive during observation. | Same custom launch harness. No claim of complete gameplay coverage. |
| Original S&SMP + same standalone ASI, Steam PE, official open.mp launcher | User reports connection still crashes. Last observed log contains only the adapter armed message. | Unresolved. No fresh crash dump was available for this run. The older pre-adapter dump cannot establish this crash's cause. |
| Exact R3-1 pass-through | Code recognizes the fingerprint without applying DL edits. | Not gameplay tested. |
| Optional five-extra-lookups variant | Compiled. | Not installed/tested in the successful run. |

Standalone artifact installed during this session: SHA-256 `4c2bc2563bd13604a502d15a49bc9b992957137d373bf36ee9061f5a59a96100`.
The original Steam S&SMP hash was rechecked unchanged after adding the adapter. No original game files were replaced by that installation.

Connecting, downloading, and a server-side spawn message alone do not prove a stable playable client. Do not publish this checkpoint as a finished compatibility release.
