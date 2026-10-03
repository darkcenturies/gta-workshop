# GTA III Darkel reconstruction methods — 2026-10-03

## Question and evidence boundary

Can a documented cut-character challenge be reconstructed for re3 while
preserving the campaign script and using original unused assets already present
in a separately supplied GTA III installation?

The [v1.39 design-document transcript](https://gtaforums.com/topic/991814-gta-3-design-document-itemized-from-gtaseriesvideos-video/)
attributes its material to the GTA Series Videos presentation of the December
29, 2000 document. It describes an optional wandering, invulnerable Darkel
contact and gives a specific example: twenty businessmen, rocket launcher,
one minute. This is a transcribed design concept, not a recovered mission script
or alpha executable. Dialogue, coordinates, encounter rules and rewards in a
reconstruction need separate authorship labels. No original five-mission chain
was recovered in this investigation.

## Target and observed results

Source inspection used [novawish/re3 revision 9a7fa478578beaba947ea867c15a25e411d641d8](https://github.com/novawish/re3/tree/9a7fa478578beaba947ea867c15a25e411d641d8).
The local target was Windows x64 re3 with CLEO Redux 1.5.1, matching symbols and
Input64.cleo. Native command validation used Sanny Builder Library v0.394,
whose local `gta3.json` was 803,234 bytes with SHA-256
`2f6a6db85a9f0a7862f1613c8ef6b0ae7728c6bb76e7cb284f28634d8499ef0a`.
Node.js v24.17.0 and Python 3.11.8 ran script/installer checks.

Observed in an IMG v1 directory: the original Darkel DFF/TXD pair and three
businessman model/texture pairs were present. Presence and valid archive bounds
do not prove animation/rendering compatibility. No game payloads were downloaded,
extracted into this public tree or redistributed.

Relevant source findings:

- [CDarkel](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/control/Darkel.cpp)
  is the surviving rampage subsystem. Its class name does not establish that
  the original cut contact missions survive. It provides timer/status, model
  filters, weapon interruption/restoration and attributed-kill accounting.
- The stock weapon filter also accepts credited explosions. Using it is not
  equivalent to proving the launcher's strict original attribution rules.
- [Script commands](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/control/Script.cpp)
  create retained mission peds. A dedicated unused ped ID avoids sharing a
  special-character slot with the campaign. Check every loaded IDE for collisions.
- [FORCE_RANDOM_PED_TYPE](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/control/Script4.cpp)
  stores a model ID in this engine despite its name. Model IDs and ped-type enum
  values must not be assumed interchangeable from metadata wording alone.
- [Radar serialization](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/core/Radar.cpp)
  saves all radar traces. [CLEO JS restarts on load](https://re.cleo.li/docs/en/script-lifecycle.html);
  JavaScript-owned marker handles therefore need a save-aware cleanup design.
  The initial prototype used transient frame markers and a locator instead;
  the later persistent-contact correction is described below.
- [Ped-pool saves](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/core/Pools.cpp)
  serialize player peds, not these contact/target peds. Session relocation state
  resets on load; ordinary reward money remains stock saved player state.

## Evaluated route and validation

Selected [CLEO Redux JavaScript](https://re.cleo.li/docs/en/api.html), using named
GTA III natives and an opt-in script directory. No campaign SCM recompilation,
engine rebuild or memory-address hook was required. Initial runtime operations
requested no memory, filesystem, DLL or network permissions. A standalone installer only
registers the existing contact model, checks inputs and preserves original bytes.

Executed checks, with the actual mission implementation kept outside this public
library:

- Syntax checking and deterministic mocked-native execution of the actual script.
  Thirty-one native command names and observed input arities matched the supplied
  library. Lifecycle, ownership, cleanup, reward, retry, loading, input and bounded
  spawning scenarios passed. This checks a contract, not the native runtime.
- Six synthetic installer tests passed: campaign preservation, later unrelated
  IDE edits, ID collisions, IMG bounds, modified-file refusal, write rollback
  and update preservation.
- Real game preflight passed. Installation from merged source completed after
  closing the game; campaign bytes were verified unchanged by SHA-256.
- No graphical or gameplay verification was executed. Original-model animation,
  invulnerability/get-up behavior, challenge difficulty, actual death/arrest
  cleanup, story coexistence and save/load still require in-game checks.

Initial runtime log evidence confirmed that CLEO discovered and loaded the
script. A user-reported hotkey collision revealed that an existing vehicle
spawner also used F7. After auditing installed scripts/configuration and the
available engine source, the locator moved to unused F8. The regression checks
that F7 no longer toggles it. Runtime discovery/loading is narrower evidence
than successful challenge gameplay. Audit existing bindings before assigning
new keys; checking only the new script cannot establish coexistence.

For independent reproduction, supply your own permitted GTA III data, inspect
IMG v1 entries without copying payloads, resolve command names/arguments against
the matching [Sanny Builder Library](https://library.sannybuilder.com/#/gta3),
and inspect the pinned engine functions above. Separate syntax/contract checks,
installation and gameplay evidence. Do not edit a running JS challenge: CLEO
hot-reloads changed scripts and can interrupt their cleanup lifecycle.

[Dryxio CLEO AI applicability](dryxio-catalog.md) was reviewed but not executed.
Its reviewed GTA SA/CLEO profile does not establish re3 JS validity. No SCM
compiler, native ABI validator, DragonFF conversion or beta-asset restoration
pack was used. Mod source, binaries, game assets, private paths and full local
input identities remain outside this public knowledge contribution.

## Persistent mission contact correction

The owner reported that the transient marker did not provide the expected mission
icon. Inspection of a separately supplied original HUD dictionary confirmed that
`radar_don` depicts a D, distinct from `radar_sal`. No replacement texture or game
payload was needed. The pinned engine's native contact-blip command with sprite
6 provides that radar/pause-map icon and an ordinary mission cylinder.

Persistent contacts need explicit save/load recovery. The revised prototype
identifies its saved traces using a distinctive color, contact type, sprite and
bounded encounter position, then removes only those owned traces through normal
script commands. Handle-generation checks preserve reused slots. It also waits
for a free slot: the inspected `SetCoordBlip` implementation has no safe full-table
failure return. The marker stays available at long range and while driving,
hides during missions and moves with the contact.

Microsoft DbgHelp inspected the matching local PDB: the radar table contains
32 entries of 48 bytes. Every field offset used by recovery was checked against
those symbols, rather than inferred only from a header. The experimental
installer now restricts this operation to the inspected engine/PDB pair.
[CLEO Memory.Translate](https://re.cleo.li/docs/en/using-memory.html#finding-memory-addresses-in-re3-and-revc)
resolves the symbol across ASLR; bounded read-only access requires the
[mem permission](https://re.cleo.li/docs/en/using-memory-64.html).
No memory writes, raw function calls, engine rebuild or filesystem/network/DLL
permission was added. Removing the script does not rewrite markers already in
save files; retain a pre-release save for removal tests.

The actual-script harness passed new saved-duplicate recovery, preserving story
markers, reused-slot, full-table retry, missing-symbol, distant/driving visibility,
mission hiding and relocation scenarios. Thirty-three native names and observed
arities matched Sanny v0.394. Seven synthetic installer tests passed, including
rejecting an unverified engine/PDB. These are mocked contract checks; rendered
visibility, animation and gameplay remain unverified.

A separately invoked profile switch was also installed after a complete local
game/source backup was verified against its per-file hashes. It disabled unrelated
map, vehicle and animation experiments using original installation receipts and
restored retained originals. Campaign/settings/saves were not edited. Keeping the
existing engine pool sizes avoids changing the installed save format; compiled
compatibility patches remain even after map content is disabled. Source changes
were preserved separately as files and a binary Git diff. The script update came
from merged implementation source. No implementation, backup payload, private
path, game asset or executable is exported with this finding.

## Decoder assertion investigation

A subsequent owner run reproduced a `CRunningScript::CollectParameters`
assertion before the encounter became playable. This corrects any interpretation
of the preceding installation/contract checks as runtime success. Engine and
symbol-file identities still matched the inspected profile; an embedded compile
path in a popup does not establish which map assets are currently loaded.

Global opcode tracing did not expose useful JavaScript call evidence. Bounded
first-call logging in the script did: startup, the timer and the first key query
returned, then execution stopped before any world/radar command. The implicit
mission-state accessor was suspected, but the following key query was not
separately logged, so this trace does not isolate the cause. Successful discovery
and mocked argument counts cannot prove the bridge's decoder compatibility.

An experimental follow-up bypasses that accessor using the exact inspected
PDB. DbgHelp verified a 163,840-byte script buffer and a four-byte mission-offset
symbol. The campaign's declared global offset is validated against its
variable-space header and buffer bounds. Only an idle flag is claimed; release
requires the same owned address and value. This follow-up introduces a bounded
four-byte memory write, unlike the earlier read-only radar recovery. Explicit
pedestrian cleanup remains necessary. It does not change the engine executable
or campaign file. See the pinned
[script-space definitions](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/control/Script.h),
[mission-state implementation](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/control/Script.cpp)
and [CLEO memory API](https://re.cleo.li/docs/en/using-memory-64.html).

Syntax and actual-script mocked execution passed without the implicit binding:
33 native contracts, bounds/ownership cases, invalid arguments and prior
lifecycle/radar scenarios. Seven installer tests passed. Installation from
merged implementation source was verified by file hashes. **Runtime retry is
pending**; this is a workaround hypothesis, not a confirmed repair. Per-key
logging now distinguishes the next input calls if the assertion persists.
Implementation, full logs, private symbols, binaries and game assets remain
withheld. Reproduce with independently permitted inputs and a disposable save;
keep diagnostic changes bounded and distinguish observed calls from inference.
