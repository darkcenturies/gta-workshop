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

### Vehicle artwork and effects follow-up on 2026-10-04

Question: does the supplied disc retain older vehicle textures and other content
changed or omitted later? The same European PS2 v1.40 disc was compared with
the modified PC installation identified above. ISO SHA-256:
`9b63fe3709b7099e23f59dd7722a4b27f431ef5d635e0670c635ebf9796e4c4e`.
This is a comparison with that installation, not a pristine PC retail release.
No later PS2 revision was supplied, so these observations do not establish
v1.40-exclusive assets or authenticate a beta build.

All 61 vehicle definitions in the PS2 `DEFAULT.IDE` cars section were enumerated;
their PS2 and compared PC dictionaries decoded. Selected DFF material bindings
were also inspected, avoiding the inference that every dictionary-only texture
was actually used by a vehicle.

| Vehicle | Direct observation | Interpretation limit |
| --- | --- | --- |
| Sentinel | PS2 DFF binds `sentinelbody64` and `sentinelbodyb64`, with separate shaded panels. Compared PC DFF binds the simpler `sentinalbody64` artwork. | A usable restoration needs the matching material/UV arrangement, not just a renamed image. |
| Subway train | PS2 DFF binds `subextfrontgraf1tga` and `subextfrontgraf2tga`; both graffiti textures are absent from the compared PC train dictionary. PC adds interior, seat and advertisement textures. | Artwork changed between these inputs; no unused PS2 status or precise development date is established. |
| Dodo | `dodoalpha64` contains a cross-shaped propeller image on PS2, versus circular blurred artwork in the compared PC file. | This is a visual variant, not another recovered aircraft. |
| Ghost boat | PS2 `polboat128` corresponds visually to PC `ghost8bitb128`; PS2 `polboatb128` corresponds to PC `ghost8bit128`. PC also adds `ghostbody64`. | Police lettering survives on PC under renamed textures. Different names alone do not establish deleted police-boat artwork. |
| Dead Dodo | Body-atlas shading differs between inputs. | This does not establish an extra driveable plane. |

The decoder needed two further corrections. Header-bearing rasters use upload
height versus raster height to determine swizzling, as shown in
[aap/rwtools `convertFromPS2`](https://github.com/aap/rwtools/blob/master/src/txdread.cpp).
Several four-bit vehicle rasters are linear. PS2's low-nibble-first pixels also
need normalization for DragonFF's high-nibble-first palette decoder. Without
that correction, adjacent pixels were reversed and shared engine/badge/decal
artwork falsely looked different. Texture-name and mask strings must stop at
the first NUL; alignment padding may contain nonzero uninitialized bytes.
These fixes were local compatibility code, not upstream or game edits.

Standalone dictionaries were inventoried separately. Both particle dictionaries
contain the same 101 names, including `flame5`, `water_old` and `wake_old`.
Metadata enumeration succeeded, but PS2 `reflection01` and `pointlight`
16-bit pixel conversion still failed; no claim of complete particle decoding
is made. HUD and MISC name sets also match, at 38 and 19 entries respectively.
GENERIC has six PS2-only names (`bricklayerdark_hi64hv`, `cliffgrass_64h`,
`grasspatch_64hv`, `lo1road_128`, `pathedge_64`, `rustyboltsop`) and one PC-only
name (`dirt64`). Dictionary absence does not prove a texture is absent elsewhere
in the map or unused. Supplementary `cs_ban`, `colt1` and `colt2` dictionaries
still fail this reader; that does not establish source corruption.

External evidence is distinct from the local asset audit:
[Fire-Head's ParticleEx documentation at revision
`0f02ea63c09e5a07f92d5e05783e26249a917102`](https://github.com/Fire-Head/ParticleEx/blob/0f02ea63c09e5a07f92d5e05783e26249a917102/README.md)
describes PS2 foot dust and puddle effects, changed particle lifetimes, unused
`flame5` assignment, broken wheel rain splash and explosion scorch marks.
These are restoration leads involving code/configuration as well as textures;
they were not independently gameplay-verified here. Its listed PC executable
support does not establish compatibility with re3. No plugin was installed.

Actual local commands: `python work/vehicle_texture_audit.py`,
`python work/vehicle_material_audit.py`, `python work/misc_texture_audit.py`,
`python work/textured_preview.py` and `python work/vehicle_audit_finish.py`.
Runtime: Python 3.11.8, NumPy 1.26.4 and Pillow 12.1.1, with the existing
DragonFF modules and `dff.py` hash recorded above. JSON evidence records each
original dictionary hash, texture names/dimensions and selected material
bindings. Comparison sheets and the corrected vehicle preview were visually
inspected; the earlier local preview pack was refreshed. Previews use base
texture levels and do not validate mipmaps or in-game appearance.

The [Dryxio catalog](dryxio-catalog.md) authoring route was consulted; GTA Scout,
Blender and PC texture export were not executed. Experimental scripts, original
assets, decoded images, local comparison evidence and research packs remain
local under the publication boundary. No installed game was changed, and no
completed conversion, import, animation/damage/collision or gameplay validation
is claimed. Public validation covers inventory, synthetic tooling demos,
unchanged evidence checksums and documentation checks; it does not turn these
platform differences into confirmed cut beta content.

### Police colour clarification from the supplied disc

The owner asked whether police cars were blue. Direct inspection distinguishes
the opening movie from gameplay defaults. The supplied `MOVIES/INTROPAL.PSS`
contains blue-and-white police cars, including frames near 42.5 seconds.
`DATA/CARCOLS.DAT` assigns `police, 0,1`: palette entry 0 is RGB `(5,5,5)`
black and entry 1 is `(245,245,245)` white. Entry 2, RGB `(42,119,161)`, retains
the comment `police car blue`, but is not the police car's default assignment.
The `ghost, 0,2` assignment is a separate vehicle and does not establish blue
road patrol cars. These observations establish retained blue imagery and a
palette entry, not default blue police cars during gameplay in this disc.

FFmpeg 9.0.1 decoded the local movie; ffprobe reported MPEG-2 video, 640 by 480,
with a 95-second duration. Actual commands used `ffprobe -v error
-show_entries format=duration:stream=codec_name,width,height -of json` against
the movie, and `ffmpeg -hide_banner -loglevel error -y -ss 42.5 -i` against
that same movie with `-an -frames:v 1` and a local PNG output. A five-second
contact sheet and the selected frame were visually inspected. Movie, frame,
colour-table payload and local paths remain withheld; no game files were
changed. No later PS2 revision, runtime colour overrides or full original
livery restoration was tested. Existing public checks and evidence hashes
were revalidated for this documentation-only addition.

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

## Cut-content feasibility catalogue — 2026-10-06

### Scope and meaning of restoration

This follow-up combines the preceding local disc audit with public historical
documentation and mod release descriptions. Target: original GTA III and re3,
not Definitive Edition. It inventories documented content families rather than
claiming access to every private development build. The December 2000 design
document, early screenshots, late PS2 leftovers and PC-port regressions describe
different states; combining them creates a curated reconstruction, not one
authenticated historical beta.

- **R — recoverable:** original asset or behavior survives; conversion, repairs,
  registration and target-specific testing can still be required.
- **P — partial:** an original component survives, but missing components need
  new authoring. Authenticity applies only to the surviving component.
- **A — approximation:** documented proposal, artwork or footage exists, but
  no complete original implementation was established by this audit.
- **U — unverified:** insufficient evidence to call the claim a cut feature.

Feasibility is an engineering assessment, not a report that implementation or
gameplay testing occurred. A public download establishes release availability,
not compatibility with a particular re3 fork. This session reviewed descriptions
and evidence; it installed and executed none of the cited mod packages.

### Characters and story components

Historical names and remnants are indexed in the
[character evidence catalogue](https://gta.fandom.com/wiki/Beta_Content_in_GTA_III/Characters).
The local observations above take precedence for the exact supplied inputs.

| Content | Feasibility | Current restoration evidence |
| --- | --- | --- |
| Darkel mesh and textures | R | Already survive in the compared PC data; adding the contact requires scripting. |
| Darkel's original five missions and Bill Fiore recordings | A | Not recovered. Beta Cars in Action supplies fan missions; our prototype has pending runtime validation. |
| Wandering invulnerable Darkel challenge contact | P | Documented concept plus original model; encounter logic, rewards and dialogue require reconstruction. |
| Novy | R/P | Original model/texture pair survives; historical role is not established by spawning it. |
| Extra `8ball` prison mesh | P | Local geometry recovered; exact texture matches remain unresolved. |
| `g`, `stu_man`, `stu_wom` | R/P | Local PS2 geometry/textures readable; filenames alone do not authenticate intended roles. |
| Later early Claude and original pedestrian clumps | R/P | Recover original models where present; earliest screenshot-only appearances remain A. GTA3D uses surviving and handmade material. |
| Early gang skins and alternate heads | R/P | Surviving assets can be converted; exact population/head-selection rules need separate evidence. |
| GOON, COP2, COL3, PLASTER | P | Model remnants do not recover their entire planned scenes or behaviors. |
| Butler | P | Cutscene references require checking model, animation and scene completeness individually. |
| Buskers | P | Released model repair/replacement exists; authentic busking AI/music is a separate question. |
| The Masks, Toshiro, Major Hale, JJ the Pimp, Curtly | A | New characters/scenes would be needed. Curtly's exact role remains unknown. |
| Early Luigi, Joey, Toni, Salvatore, Maria, Catalina, Misty, Love and Ray appearances | R/P/A | Asset-by-asset decision; artwork is insufficient to recover original geometry. |
| Old character/gang/drug names | P | Text edits are easy; naming alone does not restore the earlier campaign. |
| Extra outfits and a speaking Claude | A/U | Written proposals do not establish an original wardrobe system or recorded Claude dialogue. |

[Rockstar's character Q&A, reproduced by iGTA](https://www.igrandtheftauto.com/gta3/news/gta-iii-your-questions-answered-part-1)
confirms five Darkel missions were progressively removed before 9/11 and rejects
the schoolchildren mission rumor. The document's scripted speech and Rockstar's
later account should be reported separately; no authenticated Claude dialogue
recording was recovered. The longer Maria ending speech is described by
Rockstar, but this audit did not recover its full recording.

### Missions and campaign structure

The owner specifically supplied the 2011
[Finally Found Darkel Missions thread](https://gtaforums.com/topic/475451-finally-found-darkel-missions/).
Both pages were read in the browser during this follow-up. Its initial claim
mistakes mangled executable symbol names for a school-bus mission. VRocker2k5's
August 17, 2011 reply (comment 1060675897) identifies the retained rampage
class. Silent reiterates the distinction on April 30, 2012 (1061269562).
On [page two](https://gtaforums.com/topic/475451-finally-found-darkel-missions/page/2/),
the original author acknowledges on January 12, 2013 (1062126732) that these
are rampages, with no mission names established. The evidence therefore supports
retained `CDarkel` symbols, not recovered mission scripts. The schoolchildren
attribution in the opening post is not supported by its posted strings.

The [mission evidence catalogue](https://gta.fandom.com/wiki/Beta_Content_in_GTA_III/Missions)
distinguishes source-script remnants from design-document storyboards. These are
not interchangeable evidence. The following names identify separate work items:

| Removed mission / story component | Feasibility |
| --- | --- |
| Uzee Lu… / Drive By | A |
| Getting into the Airport | P: gate asset; new complete mission needed. |
| One of the Gang | A |
| Boss Meat | A |
| Defender | A |
| Kenji's Dead | A |
| CoffeeCo | A |
| Emergency Services | A |
| The Masks introduction, warehouse ambush and earlier jailbreak | A/P: individual surviving models do not recover the earlier sequence. |
| Toshiro counterfeiting strand and Old Oriental Gentleman's original role | A/P |
| Catalina ending choice | A |
| Earlier dialogue, mission order, contacts and rewards | P/A |

Changed existing missions also belong in the inventory: Luigi's Girls; Don't
Spank Ma Bitch Up; Drive Misty for Me; Pump-Action Pimp; The Fuzz Ball; Mike Lips
Last Lunch; Farewell Chunky Lee Chong; Van Heist; Cipriani's Chauffeur; Taking Out
the Laundry; The Pick-Up; Salvatore's Called a Meeting; Triads and Tribulations;
Blow Fish; Chaperone; Cutting the Grass; Last Requests; Under Surveillance;
Grand Theft Auto; Deal Steal; Shima; Liberator; Silence the Sneak; Evidence Dash;
Drop in the Ocean; Grand Theft Aero; Escort Service; Decoy; Smack Down; Bait;
S.A.M.; Marked Man; The Exchange; Turismo; Bling-bling Scramble; Gangcar Round-Up;
Kingdom Come; Toyminator; Rigged to Blow; Bullion Run; Rumble; and Marty's pager
introduction.

For each changed mission, restore exact surviving commented instructions where
their required assets and commands survive. Source fragments establish those
fragments, not an entire previous mission version. Storyboard-only changes need
new scripts, staging and often animation/audio. No complete released restoration
of all these earlier variants was verified. A gameplay demonstration is not
automatically an available package.

Additional mission suggestions remain A unless stronger build evidence appears:
power-plant riot, playable bank robbery, pizza delivery, body-part disposal,
gambling, kidnappings, airport pursuits, military-base infiltration, out-of-town
dirt races, delivering a demo to radio, hospital pickup, basketball, showroom
limo theft and funeral ambush. An idea in planning notes does not establish that
developers implemented and subsequently removed it.

### Vehicles and vehicle behaviors

The [vehicle evidence catalogue](https://gta.fandom.com/wiki/Beta_Content_in_GTA_III/Vehicles)
documents both surviving early meshes and screenshot-only revisions. Treat the
early shared vehicle archive as individual clumps, not a drop-in retail IMG.

| Content family | Feasibility | Mod evidence |
| --- | --- | --- |
| Early Ambulance, Barracks, BF Injection, Blista, Bobcat, Bus, Cabbie, Cheetah, Coach, Dodo, Enforcer, Esperanto, Firetruck, police helicopter, Idaho, Kuruma, Linerunner, Manana, Moonbeam, Mr. Whoopee, Mule, Patriot, Perennial, Police, Pony, Predator, Rhino, Securicar, Sentinel, Stretch, Taxi, Train, Trashmaster | R/P | GTA3D contains many genuine early meshes with adaptation; not every package has every variant. |
| Separate unused `buggy` | P | Locally recovered geometry; exact vehicle assembly, wheels and materials need verification. |
| Early Banshee, Infernus/Dyablo, Stinger/Shark, Landstalker, Reefer, Stallion and gang-car variants | P/A | Beta Cars supplies recreations; authenticity varies per component. |
| Panto | A | Fan models exist; no original complete model recovered here. |
| AMCo tanker and early rendered unnamed cars | A/U | No original working vehicle established. A render is not proof of a drivable implementation. |
| Golf cart, hearse and other proposed utility vehicles | A | New models and gameplay adaptation needed. |
| Blue/white Police and Enforcer | P | Strong photographic/local evidence; existing released livery packs. Color-only edits are incomplete. |
| Early taxi, white helicopter, red ice-cream van, Yardie/Wong liveries | R/P/A | Restore surviving components; otherwise recreate from references. |
| Old vehicle names, common wheels, antennas and removed extras | R/P/A | Original geometry when available; settings and missing geometry need new work. |
| Esperanto/Idaho hydraulics | P/A | Functional additions are possible; do not claim original parameters recovered. |
| Extra damage states, removable panels and altered doors | P | Original nodes may survive; final hierarchy/entry code can require fixes. |
| Bursting tyres, buckled wheels, falling hubcaps, airbags and radiator failure proposals | A | Implementable, but no complete original GTA III system recovered. |
| Extra damage/road-surface sounds | P/A | Recover recordings if actually present; otherwise new behavior/audio. |
| Destructible Airtrain | R/P | Silent's released Destroyable Airtrain restores surviving behavior. |
| Freely flyable planes/helicopters | A as historical restoration | Released III Aircraft provides the functionality; some engine leftovers came from Vice City work on the PC port. |
| Motorcycles | A/U | Adding them is feasible; no recovered GTA III alpha motorcycle system established. |
| Drivable school bus | U as claimed original feature | Local `schoolbus.txd` belongs to placed wrecks; fan school buses do not prove a removed playable original. |

The local Sentinel material bindings, train graffiti and Dodo propeller are R/P
platform variants. Ghost boat lettering and the Dead Dodo atlas are not evidence
of wholly deleted vehicles. Preserve those distinctions when selecting assets.

### Map, props, interface, weapons and audio

The [prop catalogue](https://gta.fandom.com/wiki/Beta_Content_in_GTA_III/Props)
provides model-level evidence; recovering a prop does not recover its missing
district or gameplay.

| Content | Feasibility / limit |
| --- | --- |
| Chinatown lion and vegetable/fish crates | R/P: surviving prop assets, placement/behavior separately evaluated. |
| Power-plant pipe joint | R: surviving original prop. |
| Full Harwood power/chemical peninsula | P/A: remnants and references, not a complete original map. |
| Airport gate and radome | R/P: assets survive; placement/function may require reconstruction. |
| Removed Newport statue | A: recreate geometry from images. |
| Earlier Callahan Bridge, Portland streets/buildings, signage and stations | R/P/A: mixed surviving assets and visual references. |
| Earlier Staunton/Shoreside and concept-map layout | A/P: references are incomplete. |
| Prison island, military test/base area, golf/country-club and other proposed locations | A: design proposals are not recovered complete districts. |
| Cut multiplayer terrain and sewer props | R/P: mobile leftovers can be converted; collision/placement need testing. |
| Ghost Town and northbound tunnels | Not proof of removed full playable regions; expanding them is new map authoring. |
| Earliest HUD, health bar, radar, reticles, target colors, logos/frontend | P/A: surviving textures where present, otherwise reference-based reconstruction. |
| Early lighting/fog/timecycle | P/A: screenshot matching cannot recover unknown original parameters. |
| Sliding mission/odd-job text | R/P: released SilentPatch options, disabled by default. |
| Floating money messages | R: released Money Messages re-enables surviving code. |
| Gang formations | R/P: current SilentPatch restores disabled behavior. |
| Different rampage presentation | P: inspect retained engine flags; not recovery of Darkel missions. |
| Camera pickups | R/P: PS2 behavior, model and disabled placements survive. |
| First-person weapon animations | R assets, P/A complete mode: retaining animations is not retaining the whole controller. |
| Golf club, crowbar, magnum, minigun, suppressed pistol/Uzi, satchel/time bomb | A: design evidence; new implementation/models required. |
| Landmine model | R model, A/P functional weapon. |
| Early bat/Uzi appearance | R/P/A: component-specific asset evidence. |
| Nightstick | U/P: screenshot evidence does not establish a fully obtainable weapon. |
| Weapon crates | A: proposed collection system. |
| Dismemberment | R existing behavior where version permits; default/censorship differs. |
| Running with bat | P/A: easy to implement, exact historical movement remains a separate evidence question. |
| Hospital treatment/player naming/safehouse upgrades/emergency radio range | P/A/U: isolated text or repeated claims do not establish complete original systems. |
| Unused bank/workshop/cinema/rave ambience | R audio, P placement/trigger rules. |
| Tom Novy music and other allegedly removed songs | A/U as original radio mix: adding a recording does not authenticate planned playlist/edit/DJ transitions. |
| PS2 effects and controller vibration lost on PC | R/P platform restoration; ParticleEx, SilentPatch, SkyGfx/GInput cover different parts. |

Later browser access allowed direct expansion of the design transcript's
Extra Features, Liberty City, Vehicles, Gangs and Mission sections. Additional
design proposals belong in the inventory, without an assertion of completed
cut implementations:

| Proposal | Assessment |
| --- | --- |
| Witnesses running to phone booths to report crimes | A: implement reporting AI; original timing/rules not recovered. |
| Injured-ped states: limp arm, dragging leg, crawling | A: new animations/state logic unless exact components are independently recovered. |
| Ambulances collecting dead pedestrians | A as the proposed collection mechanic; ordinary retail paramedic revival is separate. |
| Pedestrians using ATMs | A: proposed interaction, no original complete system established. |
| Radio stations unlocked with island progression | A: new progression logic; no original complete playlist/mix recovered. |
| Vehicle-type radio preferences and contemplated country station | P/A: do not confuse existing radio selection with an authenticated missing station. |
| Hospital and chemist health purchases | P/A: text/concept survives; original complete service interface not established. |
| Buying special cars and vehicle enhancement shops | A: modern authoring feasible. |
| Selectable HUD styles | A: option proposal, not proof a complete original menu survives. |
| Five-level wanted design, armed army tanks/APCs, suppressed-Uzi FBI | A/P: some final counterparts survive, original proposed system is incomplete. |
| Traffic offences, visible guns and broader NPC policing | A/P: existing crime/AI machinery can be extended; original rules need evidence. |
| Rush-hour traffic and stronger scheduled neighborhood danger | A/P: final time/population machinery does not authenticate the whole proposal. |
| Persistent destructible buildings | P/A: selected retail mission state changes survive; broader building-destruction proposal needs authored replacements. |
| Linked-console and split-screen multiplayer | A: planned routes; no complete original implementation recovered. |

Other planning suggestions include bus-driver/chauffeur/security work,
chemical-lab secrets and scientist kidnapping, political influence, ram-raids and
scheduled armored-car ambushes. These are A as proposals. Killing gang members
on a basketball court does not establish a proposed playable basketball minigame.

Weapon evidence is separately indexed in the
[items and weapons catalogue](https://gta.fandom.com/wiki/Beta_Content_in_GTA_III/Items_and_Weapons).
Some suggestions were never implemented; avoid calling all 17 planned weapons
finished cut systems. The unused audio list above does not identify Darkel speech.

### Multiplayer limits

[Multiplayer remnants](https://gta.fandom.com/wiki/Multiplayer_in_GTA_III)
include eight named modes: Deathmatch, Deathmatch Stealth, Team Deathmatch, Team
Deathmatch Stealth, Stash the Cash, Capture the Flag, Rat Race and Domination.
Named maps include Liberty City, Red Light, Docks, Industrial Park, Chinatown,
Staunton, Tower and Sewer. Map-name strings do not prove every complete map
survives. Menu text, logos and player labels do not supply a functional protocol,
synchronization system or the original GameSpy service.

The released Zmey20009/DimZet conversion makes surviving arenas inspectable.
Modern GTA multiplayer frameworks can implement these game types, but that is
new network code, not authenticated recovery of Rockstar's unfinished system.
Neither four player labels nor a mode name alone establishes the original limit
or exact mode rules.

### Released packages versus reconstruction projects

| Package / original source | Reviewed status and interpretation |
| --- | --- |
| [GTA3D: Back to the Streets](https://www.moddb.com/mods/grand-theft-auto-3d) | Released 2019 demo: approximately 60% of early Portland; original leftovers plus handmade assets/new code. Other islands removed; not restored full campaign. |
| [Beta Cars](https://www.gtagarage.com/mods/show.php?id=26083) | Released recreations including Hachura, Aster, Space, Stallion, Sentinal, Shark, Rocket, HumVee, Beamer, Esparanto, Maurice and Buggy. |
| [Beta Cars in Action](https://www.gtagarage.com/mods/show.php?id=23941) | Released vehicle/ped/gameplay changes with fan-written Darkel missions. Original five-mission recovery not claimed by this audit. |
| [GTA 3 Beta for re3](https://libertycity.net/files/gta-3/222623-gta-3-beta-for-re3.html) | Public 2025 package; mixed vehicles, handmade skins, reconstructed timecycle and GTA3D HUD. Listing names mixed sources; provenance is incomplete. |
| [Street Musicians from Beta Version](https://libertycity.net/files/gta-3/222554-street-musicians-from-beta-version.html) | Released repaired PS2 models as pedestrian replacements; does not establish full authentic busking behavior. |
| [SilentPatch / Money Messages / Destroyable Airtrain](https://silentsblog.com/mods/gta-iii/) | Released targeted behavior restorations and fixes. Sliding texts and gang formations are now documented; distinguish port regressions from pre-release cuts. |
| [ParticleEx](https://github.com/Fire-Head/ParticleEx) | Released classic-PC effects extension: scorch marks, rain/wheel effects, foot dust, splashes, smoke/steam/exhaust and other platform differences. Some fixes involve interpretation. |
| [III Aircraft](https://www.gtagarage.com/mods/show.php?id=24533) | Released functional aircraft addition; not proof that a complete equivalent existed in GTA III's alpha. |
| [Multiplayer map conversions](https://gtaforums.com/topic/735138-multiplayer-maps/) | Released map inspection route; [Vadim M's demonstration](https://www.youtube.com/watch?v=uUOOwAb8eHs) credits Zmey20009 and DimZet. No complete original multiplayer recovery. |
| [Liberty City '01](https://gtaforums.com/topic/983493-grand-theft-auto-liberty-city-01/) | Author thread labels WIP; no public full release verified on this audit date. Previews are not an available full restoration. |

### What cannot presently be authenticated

#### Owner-selected strict restoration scope

The owner narrowed the intended mod on 2026-10-06 to directly recovered or
unlocked content, then clarified that incomplete, fan-written and assumed
content should remain visible in the catalogue with explicit labels. Catalogue
inclusion is not a claim of authenticity or eligibility for the original-only
implementation scope. New loader
or repair code may make original content work, but must not supply invented
missions, dialogue, identities, world placements, geometry or balancing under
an original-content claim.

A practical proposal is an optional original-content restoration layer plus a
separate asset inspection tool:

- Core behavior candidates: camera pickups with surviving PS2 behavior and the
  eight source-script positions; money messages; sliding mission/odd-job text;
  disabled gang formations; and rocket destruction of the Airtrain. Validate
  exact original implementation components before calling a feature recovered.
- Platform parity candidates: PS2 particles, water/foot/rain effects and exact
  vehicle texture/material variants. Exclude effects whose implementation is an
  author's hypothesis, and separate retail-platform content from beta content.
- Locally established inspection assets: original Darkel and Novy, `g`,
  `stu_man`, `stu_wom`, extra `8ball` geometry and the extra `buggy` geometry.
  Missing exact `8ball` textures or a verified complete buggy assembly stay
  incomplete; do not silently fill them from lookalikes. Inspection/spawning
  tools are modern utilities, not recovered original world placement or roles.
- Additional recoveries require individual input verification: early shared
  pedestrian/vehicle clumps, repaired busker models, multiplayer terrain, unused
  props and commented mission instructions. Availability in a mixed fan pack
  does not establish the provenance of each member.

Read-only source review of the pinned re3 revision
`9a7fa478578beaba947ea867c15a25e411d641d8` found `CAMERA_PICKUP` and
`EXPLODING_AIRTRAIN` defined in the inspected local configuration, with
`BETA_SLIDING_TEXT`, `MONEY_MESSAGES` and `USE_BETA_REPLAY_MODE` commented out.
Later original-build guards can undefine some switches; this observation is not
proof of the active installed binary's build options or gameplay behavior.
The camera implementation explicitly attributes its body to PS2.
[Pickups.cpp](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/control/Pickups.cpp),
[Plane.cpp](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/vehicles/Plane.cpp),
[Hud.cpp](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/render/Hud.cpp)
and [configuration](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/core/config.h)
provide the public comparison references. Existing unrelated local edits were
preserved; no engine or implementation edits were made for this catalogue.

The retained standard rampage message flag is a narrower recovery candidate
than a Darkel storyline. The reviewed rendering code explicitly borrows screen
positions from Vice City, so it cannot establish exact original GTA III beta
presentation by itself. Likewise a beta replay switch marked buggy requires
separate original-target comparison before inclusion. The proposal therefore
marks both as provisional candidates outside the initial strict implementation
scope; neither is removed from the catalogue.

An exact original restoration is not possible from the evidence established here
for Darkel's whole strand/recordings, an entire earlier campaign, screenshot-only
meshes, missing district geometry, undocumented handling/AI rules, unrecorded
voices, original networking or systems represented only by proposals. Most can
be made playable through modern authoring. The limitation is missing historical
information, not necessarily an engine limitation. A future legitimate recovery
could change these classifications.

Do not promote the following as established cuts: schoolchildren bomb mission,
Love-building aircraft attack, 9/11 removal of Darkel, a hidden complete fourth
island, a fully recovered freely flying Dodo, a complete voiced Claude campaign,
or proof of cut playable content from a filename alone.
[Rockstar's second Q&A, reproduced by iGTA](https://www.igrandtheftauto.com/gta3/news/gta-iii-your-questions-answered-part-2)
explains the bank-robbery set, blocked tunnels and limited-purpose Dodo.

Practical restoration priorities are original unused assets and disabled
behaviors first, component-verified visual changes second, source-backed mission
fragments third, and explicitly labeled new reconstructions last. Classic x86
ASIs are not automatically compatible with a rebuilt x64 re3 executable.

### Extended source inventory and restoration routes — 2026-10-07

A cut-content catalogue and a fork's implemented feature inventory answer
different questions. This follow-up compares the public
[x87/gta-extended-2025 source at f8142f1a7cefcfd6bcd778ed8802e21c93b97c91](https://github.com/x87/gta-extended-2025/tree/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91)
with the preceding original-content evidence. All 564 manifested source files
matched the pinned source ZIP. Read-only extraction inventoried 179 distinct
configuration declarations and 237 compiler-indexed feature functions. The
historical configurable port's generated registry contains 385 entries, plus
the separate GPS colour value, across 38 feature groups. These are indexed
feature functions and settings, not every ordinary game function or a promise
of identical controls on another executable. The historical candidate inventory
remains visible, including incomplete recoveries, proposals and fan work.

An MSVC preprocessor run against the pinned, unchanged configuration used
Windows x64 Release, LIBRW, D3D9 and OpenAL definitions. This resolves conditional
and later-undefined macros instead of treating every visible `#define` as active.
It does not compile, install or run the engine.

| Candidate | Audited source state | Practical route |
| --- | --- | --- |
| Airtrain destruction | `EXPLODING_AIRTRAIN` defined | Verify existing behavior before adding code. |
| Camera pickup | `CAMERA_PICKUP` defined | Verify behavior; restore independently authenticated script placements. |
| Floating money messages | `MONEY_MESSAGES` not defined | Enable a compile switch and rebuild; this is not a money-HUD-format option. |
| Sliding mission/odd-job text | `BETA_SLIDING_TEXT` not defined | Enable a compile switch and rebuild, rather than assume an existing INI toggle. |
| Alternate short replay | `USE_BETA_REPLAY_MODE` not defined | Provisional rebuild candidate; buggy comment and historical provenance require validation. |
| Phone-booth crime reporting | `PEDS_REPORT_CRIMES_ON_PHONE` defined | Implementation exists in this fork; exact GTA III alpha rules remain unauthenticated. |
| First-person implementation | `EX_FIRST_PERSON` defined | Existing fork feature, not proof of a complete original beta controller. |
| PC particle variant | `PC_PARTICLE` not defined | Existing PS2-oriented paths; actual asset/parameter parity remains an individual audit. |

The original source configuration is
[config.h](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/core/config.h).
The public port's
[feature guide](https://github.com/darkcenturies/gta3-faithful/blob/main/docs/FEATURES.md)
and [integration evidence](https://github.com/darkcenturies/gta3-faithful/blob/main/docs/NATIVE-MODS.md)
distinguish inherited source, historical package behavior and replacement-host
validation. Read the target's current instructions before applying historical
settings. Inherited vehicle additions explicitly attributed to reVC remain
fork additions; enabling them does not recover original GTA III alpha content.

Low-authoring asset routes are complete original mesh/texture pairs and exact
material variants: Darkel/Novy, the audited `g`/`stu_man`/`stu_wom` pairs,
Sentinel materials, train graffiti and the Dodo propeller. Geometry, textures
and original bindings must travel together where necessary. Unused original
audio and animations are authentic inspectable material, while missing usage
rules remain missing. The extra `buggy` and prison `8ball` remain partial,
not complete drop-in recoveries. Existing engine support does not authenticate
unknown roles, invented placements or missing recordings.

The machine-readable inventory was reconciled to its source manifests and
preprocessed flags. A seven-sheet local catalogue separates restoration routes,
feature groups, historical settings, source switches, indexed functions,
historical cut candidates and sources. Spreadsheet tables were inspected and
rendered; no game-derived inputs or source bodies were embedded. The full
local working-state inventory is not exported into this public reference
library. No gameplay test, feature activation, mod installation or game-asset
conversion ran for this follow-up. Dryxio's native/authoring routes were
consulted for applicability; CLEO AI and unrelated tools were not executed.

### Catalogue granularity and additional leads — 2026-10-07

A shortlist of restoration routes is not a total of cut features. Split named
models, textures, animations, sounds and behaviors into individual records.
Keep unresolved families explicitly identified and retain proposals, visual
reconstructions and rejected claims with their evidence class. Counts of rows,
settings, functions and genuinely recoverable features answer different questions.

Additional original-research leads include B_Smiles's
[rail-platform report](https://gtaforums.com/topic/745716-grand-theft-auto-iii-pre-release-discussion/?do=findComment&comment=1069084221)
and [chimney/lift report](https://gtaforums.com/topic/745716-grand-theft-auto-iii-pre-release-discussion/?do=findComment&comment=1069131140).
These identify `rail_platform.dff`, `plnt_chimgrad` and `GTAELIFT`.
The posts report missing material bindings and failed lift integration, not
complete verified drop-in restorations. Original placements remain unresolved.

In the pinned Extended source, `Pickups.cpp` contains land and nautical mine
arming/explosion logic. `Script6.cpp` and `GameLogic.cpp` retain a free-healthcare
command and the corresponding hospital fee/equipment branch. Activation is
feasible in principle, but original reward triggers and handheld mine deployment
are not thereby recovered. `PowerPoints.cpp` has empty methods: a surviving
class name and a beta comment do not supply an unlockable implementation.

Two useful negative checks prevent catalogue inflation. Ordinary Pac-Man race
and scramble pickups are retail mechanisms for magazines and bullion; the
route recorder is a separate development capability. `mainsc2` is selected by
regional/censorship conditions in `main.cpp`, so it is not universally unused.
[Silent's 2024 explanation](https://silentsblog.com/2024/10/25/silentpatch-goes-open-source/)
assigns Minimal HUD to Vice City and San Andreas, not GTA III. The same article
documents two PS2 mission variants lost through PC randomness. His
[2026 explanation](https://silentsblog.com/2026/07/31/silentpatch-2026-update/)
distinguishes unused script-sprite support, the free-jail correction and an
original half-finished subtitle feature completed with Vice City behavior.

[ParticleEx](https://github.com/Fire-Head/ParticleEx) provides a much finer
platform/effect comparison than a single particles row. Separate original
platform ports and retained-code repairs from changes whose intended final
appearance the author explicitly cannot establish. A public unused-sound index
is an extraction lead until the exact target and actual references are checked.

This expansion reviewed online researcher/mod-author descriptions and bounded
existing source; it did not activate code, convert assets or run the game.
Some direct forum/wiki opens and TCRF retrieval were blocked, while cached
search excerpts exposed several original posts. The expanded local spreadsheet
preserves weaker leads at their actual proof level and does not claim exhaustive
access to every historical page. The existing inventory check and three
synthetic repository examples passed; CI supplies documentation/checksum gates.
No game payload, mod implementation or full private working inventory is added.

### Original-footage timeline comparison — 2026-10-07

The owner supplied DerPlayer's
[Grand Theft Auto III beta development timeline](https://www.youtube.com/watch?v=xyGkB5D7fB8),
published March 16, 2023, with a duration of 52:53. The browser-visible chapter
list, complete English auto-generated transcript and selected paused frames
were compared with the existing catalogue. This is a sampled visual comparison,
not an exhaustive frame-by-frame review. The uploader's dates are attribution,
not independently authenticated build dates. Several are explicitly tentative.

| Evidence | Catalogue implication and recovery limit |
| --- | --- |
| [0:05 and 0:09: July and October 2000 wireframe demonstrations](https://www.youtube.com/watch?v=xyGkB5D7fB8&t=5s) | Both inspected clips show carjacking animation tests. Retain as development-footage evidence. No original animation file, model file or executable was recovered from these clips; a modern wireframe rendering is not recovery of the earlier build. |
| [3:00–3:03: May 2001 E3 demonstration](https://www.youtube.com/watch?v=xyGkB5D7fB8&t=180s) | Shows the early HUD/radar, an upper-left logo/debug display and blue/white police presentation in the surrounding E3 material. Existing HUD, logo and Police-variant groups cover the visuals. Record their dated variants rather than count every shot as another feature. |
| [August 20 chapter and vehicle highlights around 15:35–15:47](https://www.youtube.com/watch?v=xyGkB5D7fB8&t=935s) | Supplies a specific reference for early vehicle paint/material presentation. The image does not recover the renderer, environment map or numeric material settings. Existing PS2 material support is a comparison route, not proof of exact early-build parity. |
| [36:11 onward: E3 2002 PC preview](https://www.youtube.com/watch?v=xyGkB5D7fB8&t=2171s) | The interview describes MP3 radio, player skins and saved replays. Treat these as advertised PC functionality, not three newly discovered cut gameplay systems. Later Japanese and Xbox advertising also require separate platform/release classification. |

A bounded read of the already pinned Extended
[main.cpp](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/core/main.cpp#L1148)
found `bDisplayPosn`/`bDisplayRate` diagnostics inside `#ifndef MASTER`, with a
frame-rate calculation, controller-pad toggles and coordinate/zone text output.
This is an existing source capability worth indexing separately as a development
utility. The inspected implementation does not establish the exact E3 overlay's
appearance or that the installed binary exposes it. No activation/build/gameplay
test ran. Version text explicitly marked as a re3 addition is not authenticated
vendor beta content.

The description links the uploader's
[source-clip archive](https://archive.org/details/gta-3-beta-dev-timeline/).
Its public JSON metadata listed 57 original-upload entries: 52 video files,
two JPEGs and three metadata files. "Original" here is Internet Archive's
upload/derivative classification, not vendor-source authentication. No game
build, DFF/TXD/IFP, mission script or source-code payload was listed. Metadata
was retrieved; no remote video or game assets were downloaded. This is useful
for comparing less-compressed footage, but not an asset-restoration pack.

The sampled material establishes no additional original-only gameplay recovery.
It does not authenticate the speaking-Claude attribution made in viewer comments
or a recovered Darkel mission strand. The complete transcript cannot assign
short gameplay voice lines to a specific speaker. Preserve those questions at
their existing evidence level. The local spreadsheet was read without changes;
the comparison returns here as public-safe findings. Whitespace, inventory and
the three synthetic repository demos passed; CI supplies the independent
documentation/checksum gates. These checks do not validate in-game behavior.

### Method, checks and withholding

This follow-up reread the existing public disc evidence and consulted the Dryxio
catalog for route applicability. No external analysis tool, CLEO AI, game binary,
asset conversion, mod installation or gameplay test ran for this catalogue.
Public web pages and ordinary browser-visible historical indexes were reviewed;
direct GTAForums retrieval was intermittently blocked. Later ordinary browser
access exposed the original design-transcript post and the sections enumerated
above, and both pages of the owner-supplied Darkel thread. This still is not a
read of the entire underlying original design document.

Only this existing knowledge note changes. No game assets, mod implementation,
private local paths or source excerpts are exported. Whitespace and inventory
checks passed (72 tool/support entries). The three required synthetic examples
and 19 existing texture/hair/animation tests passed; they validate repository
tooling, not any GTA III restoration. A literal local `sha256sum -c` encountered
Windows CRLF filenames in the manifest; verification against committed Git blob
bytes avoids conflating checkout line endings with evidence changes. Repository
CI provides the independent Linux checksum and documentation gates. Actual
contribution and CI status are recorded in its PR/checks.

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
