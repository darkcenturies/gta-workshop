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

## Historical evidence follow-up on 2026-10-04

The later historical audit separates early design proposals, participant
recollections, retail remnants and modern reconstruction. It does not recover
an original five-mission strand or supply invented missing content.

- The December 2000 material presented in the
  [itemized design-document transcript](https://gtaforums.com/topic/991814-gta-3-design-document-itemized-from-gtaseriesvideos-video/)
  describes a moving optional contact who survives being run over. Its
  twenty-businessmen, rocket-launcher, one-minute task is explicitly an example,
  not an identified member of the later five missions. Two linked character
  images were visually inspected; the full underlying document was unavailable.
  Indexed transcript text was available while direct forum retrieval returned
  403. No exact document page or video timecode is asserted.
- Douglass C. Perry's original
  [IGN AI preview](https://www.ign.com/articles/2001/02/22/grand-theft-auto-how-smart-is-the-ai)
  was retrieved directly. It explicitly attributes an ice-cream truck/dynamite/
  crowd-bombing task to Darkel, without a mission title, location, reward or
  complete script. Structured publication metadata is 2001-02-22 at 00:30 UTC;
  a [2002 quotation](https://forums.neoseeker.com/1958/t149589-some-darkel-info/)
  gives February 21. A timezone explanation is plausible but unverified.
- Related `Fried Ice Cream` material appears in the design presentation among
  El Burro-related jobs. This and the later preview are different snapshots,
  not proof of a simple one-way reassignment or unchanged design. Do not merge
  their parameters into an allegedly recovered Darkel script.
- [Rockstar's 2011 Part One Q and A](https://www.rockstargames.com/newswire/article/51974aa3a99a59/grand-theft-auto-iii-your-questions-answered-part-one-claude-dar.html)
  says five missions were progressively reduced to one or two and then removed
  before 9/11 for quality/tonal reasons. It names none and rejects schoolchildren
  bus missions. The official URL returned its app shell; text was checked through
  a [contemporaneous reproduction](https://www.igrandtheftauto.com/gta3/news/gta-iii-your-questions-answered-part-1)
  and the preserved answer image in the GamesRadar feature below.
- [Rockstar's Part Two](https://www.rockstargames.com/newswire/article/25o241181oaa23/grand-theft-auto-iii-your-questions-answered-part-two-911-the-gh.html)
  rejects the airplane/Donald Love and other extreme post-9/11 rumours.
  Its answer was inspected through the
  [contemporaneous reproduction](https://www.igrandtheftauto.com/gta3/news/gta-iii-your-questions-answered-part-2),
  since the official body did not render. It does not identify the one
  post-9/11 mission removal as Darkel content.
- In a [September 17, 2026 interview](https://thunderpick.io/blog/obbe-vermeij-exclusive-rockstars-former-technical-director-on-plans-for-gta-paris-what-the-team-wanted-to-build-with-gta-tokyo-and-reflecting-on-the-25th-anniversary-of-grand-theft-auto),
  former technical director Obbe Vermeij recalls insufficient missions, tonal
  problems and moving missions to other contacts. This participant recollection
  supports redistribution generally, but identifies no particular mission.
  The interview question's economy-destruction premise is not an independently
  verified character biography.
- [Joe Donnelly's GamesRadar reporting](https://www.gamesradar.com/the-strange-story-of-darkel-one-of-gta-3s-most-mysterious-cut-characters-with-speculated-but-unsubstantiated-ties-to-terrorism/)
  records GTA3D's artistic license, including bootleg-booze missions, and his
  inconclusive contact with Bill Fiore's representatives. Those fan missions
  and interviews supply no authenticated original dialogue.

### Independent retail-disc observations

A separately supplied European PS2 v1.40 image was inspected locally; no game
payload is added to this repository. Exact ISO SHA-256:
`9b63fe3709b7099e23f59dd7722a4b27f431ef5d635e0670c635ebf9796e4c4e`.
7-Zip 25.01 extraction, gta3sc 0.9.8 GTA III IR2 decompilation, five-language GXT
decoding, IMG v1 inspection, symbol/caller analysis and whole-image ASCII/
UTF-16LE literal scans found:

- `darkel.dff`, `DARKEL.TXD` and the `CRED129` Bill Fiore credit survive. Twelve
  identical IMG copies are not twelve different development versions.
- `MAIN.SCM` has 80 mission blocks and 128 script-name entries, none naming or
  requesting Darkel. This is not a count of campaign story missions.
- `DIABLO2`, block 41, is the retail El Burro ice-cream mission, with `EL_PH2`
  phone audio and four model-10 targets. It has no separately named Darkel
  version. Its success banner parameter is 6000 while `ADD_SCORE` adds 8000;
  these are distinct observations, not interchangeable reward values.
- `TRAMPS` creates two `scum_man` and two `scum_wom` pedestrians with Molotovs.
  It has no Darkel load, conversation or mission trigger. The tunnel is not an
  authenticated Darkel spawn merely because these peds are present.
- The symbol-bearing PS2 ELF has 12 `CDarkel` functions and 17 data objects;
  native callers confirm the surviving frenzy subsystem is active. These
  addresses do not apply to the re3 target above.
- No Darkel-specific subtitle sequence, labeled audio or `Love Hurts` title
  was identified. Literal absence is scoped to this image and cannot exclude
  anonymous recordings or content in a different build.

A follow-up mission-audio audit compared the ELF's 109-entry
`MissionAudioNameSfxAssoc` table against literal `LOAD_MISSION_AUDIO` calls:
96 labels referenced, 13 unreferenced. Five unreferenced `ammu_g`–`ammu_k`
labels alias the referenced `ammu_a` sample. Eight distinct candidate IDs remain:
`a3_a`, `ammu_d`, `ammu_e`, `ammu_f`, `door_2`, `door_4`, `door_5`, `door_6`.
Sony ADPCM samples were extracted through SDT offsets and decoded with FFmpeg
9.0.1. No candidate is attributed to Darkel. Engine/numeric uses and anonymous
pedestrian speech were not exhaustively traced, listened to or transcribed;
unreferenced by this SCM does not prove unused everywhere.

The resulting local design dossier records character facts, separate task
concepts, exact retail observations, source-access limits and unresolved
implementation fields. No original titles/order for the five, authentic voice
lines, per-task rewards or historical Darkel coordinates were recovered. No
gameplay validation or new mod implementation was performed in this audit.
Game-derived payloads, full source captures and the local document remain
outside the public tree; this finding returns only facts, methods and citations.
The public contribution passed inventory/hash/syntax checks, all three synthetic
Valkyrie demos, all 54 published evidence checksums and whitespace validation.
Those maintenance checks do not establish historical mission completeness or
in-game compatibility.

### Turning evidence into a new adaptation

A later owner-requested writing pass assembled a local persona, five linked
mission designs and 69 new dialogue lines. These are authored adaptation,
not newly discovered original missions or recordings. The historical task
motifs remain separately attributed; new titles, motives, plot connections,
placements and balance values carry explicit authorship labels. The count of
five is a chosen scope, not identification of Rockstar's discarded strand.

The useful handoff separates a readable character/mission brief from structured
mission definitions and dialogue records with stable local IDs. These IDs are
design labels, not game audio or text-bank IDs. Review includes objective and
failure transitions, dialogue playback only when the speaker is present,
cleanup, reward ownership and proposed save/load behavior. The 17-page document
was rendered and visually inspected; the JSON records were parsed and checked
for unique line IDs and consistent mission/reward totals. This is document
validation, not implemented or tested gameplay. The creative draft and earlier
generated concept illustrations remain local, outside this public library.

### Correction after creative review

The owner rejected that first adaptation's writing and character fit. Its
money-driven employer persona and retaliation arc are abandoned writing,
not a usable historical characterization. A corrected local foundation keeps
wandering frenzy encounters separate from the later five-mission account and
does not assert a recovered private motive or authentic dialogue. Its four
pages were rendered and visually inspected; it is a foundation revision,
not a completed replacement mission strand or a gameplay result.

The [Mr. Fike article](https://gta.fandom.com/wiki/Mr._Fike) calls that cut
GTA Advance contact a spiritual successor to Darkel. The retrieved
[v1.3 Advance document transcription](https://gtaforums.com/topic/1000231-gta-advance-design-document-itemized-from-leak/)
describes his destructive bonus jobs, including Insanity Check and Mass
Destruction. This comparison offers a design reference, but the inspected
material contains no developer statement proving direct Darkel influence.
Fike's documented tasks, speech and motives must not be imported as missing
Darkel evidence. The original Advance document pages were not inspected.

## Retained asset audit on 2026-10-04

The same European PS2 v1.40 input was compared with an owner-local modified
Windows Upstate/re3 installation. The comparison is not a pristine PC retail
baseline and cannot establish differences across every PC release. Its IMG v1
directory SHA-256 was
`773b90354a7cce1af62b490fe778254f10b2b4b7a743a42909ed51862d54d987`.
Its IMG SHA-256 was
`d0195989d780a021698523da296822d59cbb8b3ea45c639c3e8f5334de6eec25`.

Directory inventory found 3,126 DFF entries. Cross-reference used all supplied
IDE files and literal `LOAD_SPECIAL_CHARACTER` / `LOAD_SPECIAL_MODEL` requests
in the complete retail SCM disassembly. Lack of an IDE entry alone does not
establish unused status: many story actors are loaded through special slots.

| Candidate | PS2 allocated bytes | Compared PC archive | Observation |
| --- | ---: | --- | --- |
| `buggy.DFF` | 169,984 | Absent | Readable extra dune-buggy mesh; unregistered and not specially requested. |
| `8ball.DFF` | 40,960 | Absent | Readable extra character mesh; retail script instead requests `EIGHT` / `EIGHT2`. |
| `g.dff` / `G.TXD` | 45,056 / 36,864 | Zero-length DFF allocation; 2,048-byte TXD allocation | PS2 retains geometry; identity and design date remain unverified. |
| `stu_man.dff` / `STU_MAN.TXD` | 45,056 / 18,432 | Zero-length DFF allocation; 2,048-byte TXD allocation | Unregistered extra male mesh; distinct filename from registered `stud_man`. |
| `stu_wom.dff` / `STU_WOM.TXD` | 49,152 / 18,432 | Zero-length DFF allocation; 2,048-byte TXD allocation | Unregistered extra female mesh; distinct filename from registered `stud_wom`. |
| `darkel.dff` / `DARKEL.TXD` | 61,440 / 18,432 | Nonempty pair already present | Importing the PS2 copies is unnecessary merely to obtain Darkel assets. |
| `novy.dff` / `NOVY.TXD` | 61,440 / 18,432 | Nonempty pair already present | Unregistered/unrequested candidate; no historical identity asserted. |

The selected models were extracted locally and decoded using the existing
[DragonFF gtaLib](https://github.com/Parik27/DragonFF) modules. The standalone
reader file `dff.py` SHA-256 was
`2df8ee3f8f0436430aff91413f12232b072e55e61ac990b342ef2af21816079a`.
Uniformly shaded analysis previews used Python 3.11.8, NumPy 1.26.4 and
Matplotlib 3.10.8; the eight-panel preview was visually inspected. It includes
the retail `bfinject` for comparison: the extra `buggy` has visibly different
upper geometry without its corresponding roll cage. This does not date the
asset or authenticate a particular alpha build. These previews are original
mesh analysis, not generated character concepts or in-game screenshots.

Full IMG sector allocations must be preserved during extraction. Several
legacy files contain later atomics/LOD clumps beyond their first declared
clump length; trimming at that length produced incomplete reader inputs.
The selected decoded geometries report native platform type zero. A PS2
source disc does not automatically make every DFF PS2-native geometry.
Several PS2 TXDs failed the current decoder, including `G`, `STU_MAN`,
`STU_WOM` and `NOVY`; a failure does not establish that the source is corrupt.
No dedicated `buggy.txd` or `8ball.txd` entry was found. Texture-name literal
matches offer possible shared dependencies, not verified material conversion.

Control examples prevent false cut-content claims: `DONKY` and `CURLY` are
requested by the retail SCM; `boatramp1` is registered and placed; and
`cskydark` is referenced by retail map IDE records. `schoolbus.txd` belongs
to the registered static wreck `fuckedup_skewlbus` (model 878), placed six
times in `PROPS.IPL`. That is not a recovered driveable school bus or a
Darkel mission.

Actual local commands were `python work/asset_audit.py`,
`python work/asset_compare.py`, `python work/asset_gallery.py` and
`python work/asset_finish.py`, with the user-supplied extracted disc and
the independently installed comparison game. These experimental scripts,
original DFF/TXD files, JSON evidence, image and research pack remain local.
No game installation was changed. No PC import, animation, vehicle damage,
collision or gameplay compatibility was validated. A usable PC restoration
still needs target-readable textures, legacy frame/LOD/version handling,
registration and runtime checks. This asset audit does not recover missions.

### Original texture preview follow-up

A later local preview resolved the earlier `G`, `STU_MAN`, `STU_WOM` and
`NOVY` decoder failures. Their PS2 rasters omit the 80-byte upload headers
which the current reader assumed. The original
[aap/rwtools PS2 texture reader](https://github.com/aap/rwtools/blob/master/src/txdread.cpp)
documents raster flag `0x20000` for headers and `0x10000` for swizzled pixels
without headers. A local compatibility reader used those flags to choose
headerless pixel offsets, conditional unswizzling, palette remapping and
PS2 alpha scaling. No vendor/module file or installed game was modified.

Actual command: `python work/textured_preview.py`. The five characters
`darkel`, `novy`, `g`, `stu_man` and `stu_wom` rendered with their own
decoded PS2 textures and original UVs. Front/back comparison images were
visually inspected to select the face direction; a closer front view was
saved locally. The extra `8ball.DFF` still references unresolved `8-Ball`,
`8bandage`, `gymshoes` and `prison` textures, so all four surfaces remain
explicit grey placeholders. A substring hit in `PLAYERP.TXD` is actually
`playa_prison`, not the exact requested `prison` texture.

The retail `bfinject` also rendered with its own dictionary. Extra `buggy`
materials were previewed with exact texture-name matches from the static
school-bus wreck dictionary; this resolves preview names, not historical
dictionary ownership. Stored paint-marker colors are visible and separate
wheels were not reconstructed. Images, decoded textures, compatibility
reader and per-texture source hashes remain local. This is a texture/UV
preview result, not a PC dictionary export or in-game compatibility test.

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

### Later attribution from an assertion observer

A subsequent runtime reached the world/radar calls and still asserted. A bounded
parameter/assertion observer captured the actual failing campaign script:
`ul_gtpg`, at instruction offset 88314. Its preceding player-zone check uses a
conversion label removed when that map was disabled. The pinned engine does not
advance past an unknown zone label, so subsequent label bytes desynchronize the
decoder. This trace supersedes the implicit mission-accessor hypothesis as
attribution for the observed assertion; it does not prove every encounter call
or its radar result correct. See the
[loading-assertion finding](gta3-pager-extension-2026-10-03.md#loading-assertion-traced-to-a-retained-conversion-script)
for exact input identity, separate compatibility-guard tests and pending retry.
