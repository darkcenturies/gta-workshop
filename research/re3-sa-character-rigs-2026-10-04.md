# SA character rigs in skinned-ped re3

## Question and target

Can classic PC San Andreas gameplay characters replace GTA III characters through
native Mod Loader when the re3 host supports skinned pedestrians?

The inspected Windows x64 host was re3 Extended with engine dependency
`x87/gta-extended-2025` revision `f8142f1a7cefcfd6bcd778ed8802e21c93b97c91`,
librw `5501c4fdc7425ff926be59369a13593bb6c81b54` and Cowboy-69 Mod Loader
`76c127e983069bcb1308b198c11ce8b81147b0bc`.
Production executable: 12,591,616 bytes, SHA-256
`706969d0b1643b34089a7b6a11c25ce50cb11bb5542cefb809ac4eafcf41f9c7`.
The separate test host was 12,598,784 bytes, SHA-256
`67a1d33fcd1e3bb95b592ddb93ebd8968573125f792b711ad595831e3361d9bf`.

## Method and references

The [authoring route](../docs/workshop/CATALOG.md#authoring) and
[Dryxio catalog](dryxio-catalog.md) were consulted. GTA Scout was reviewed as
an asset-discovery reference; it was not executed. Blender was not needed for
the direct RenderWare conversion. No CLEO script or native engine hook was authored.

Original upstream references:

- [re3 skinned-ped configuration](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/core/config.h)
- [III bone tags and names](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/animation/Bones.h)
- [Animation association initialization and copying](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/animation/AnimBlendAssociation.cpp)
- [Animation blending and skinned frame bindings](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/animation/RpAnimBlend.cpp)
- [Player BMP skin selection](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/renderer/PlayerSkin.cpp)
- [librw frame streaming](https://github.com/aap/librw/blob/5501c4fdc7425ff926be59369a13593bb6c81b54/src/frame.cpp)
- [DragonFF by Parik27 and contributors](https://github.com/Parik27/DragonFF)

Tools actually executed: Python 3.11, NumPy 1.26.4, Pillow 11.3.0, the installed
DragonFF standalone `gtaLib` model/texture parser, an installed INU_tools IFP reader,
MSVC 19.51 and CMake 4.3.1. Installed DragonFF `gtaLib/dff.py` SHA-256:
`459ae43cb9bbd4e4ab620e8eb02c6edc72575b3c030d6e63644c194d2fa33583`.
This identifies the evaluated file, not an asserted upstream release number.

Published `valkyrie-models` entry `workshop/deploy/sarw.py` was executed to
independently inspect both exported DFFs. Source SHA-256:
`7f5a4111df9de105f0b277ffe7121d9b9bcc0fbcc21e567da5a7c809aeafd67a`.
The actual command shape, with local game-derived input paths withheld, was:

```text
python tooling/source/workshop/deploy/sarw.py LOCAL_CLAUDE_DFF LOCAL_CATALINA_DFF
```

The report found 16 bones, four maximum influences, normals, UVs and the expected
material texture names on both outputs. It was inspection, not gameplay testing.
Other model-family Blender conversion/stress scripts were consulted and skipped
because their target rig is SA rather than the III donor rig used here.

## Observations

The inspected host enables `PED_SKIN`. This supports skinned geometry; it does
not make the SA bone IDs interchangeable with III's. The two inspected SA gameplay
characters have 32-bone HAnim hierarchies; the III target uses 16 semantic tags.
Skin vertex indices address the HAnim bone table, not the file's frame-list order.

The native animation association templates also retain a node ordering. Matching
only names or tag values is insufficient if the skin's hierarchy traversal differs
from the donor used to build those templates. librw's default stream behavior
prepends children. For the inspected stock III donor, reversed sibling traversal
matches the ordered III tags from waist through the limbs and hands.

The evaluated conversion collapsed facial, finger, toe and other helper influences
to supported III bones, fitted vertices/normals to the locally supplied III rig,
rebuilt inverse binds and normalized weights, and retained source triangles/UVs.
Output used RW 3.4.0.3 and D3D8 RGBA texture dictionaries with mipmaps.

Claude's default player-skin path additionally needs a matching `player.bmp`.
Changing only the DFF/TXD can leave the original/default skin atlas in use.
Native Mod Loader's BMP redirect was recognized in the isolated fixture.

## Checks and results

| Check | Claude | Catalina |
| --- | --- | --- |
| Exported vertices / triangles | 1,089 / 1,280 | 1,040 / 1,338 |
| Triangle/UV export roundtrip | Passed | Passed |
| Skin tags, normalized weights and inverse-bind/rest consistency | Passed | Passed |
| Independent pinned librw parsing and atomic clone bindings | Passed | Passed |
| Native material lookup of 256x256 TXD texture | Passed | Passed |
| Offline sampled animation poses | 36 | 36 |
| Worst p99 edge stretch across sampled poses | 1.910 | 2.323 |
| Isolated player-alias boot and copied-save reload | Passed | Passed |

Offline samples used idle, player walk/run, sprint, pistol upper-body, sitting,
vehicle entry, female walk and female run. Partial-animation tracks missing from
the tested clip used an idle base. A coarse p99 stretch budget of 3.0 and finite/
bounded geometry checks passed. Individual small edges can stretch more; these
numbers do not establish visual perfection. Offline textured previews were inspected.

Both isolated native Mod Loader runs imported the replacement player DFF/TXD,
reloaded a copied save and reached `EXTENDED_SMOKE player=1` without exiting.
Catalina was aliased as the player solely to exercise loading of her converted
rig. This is not evidence of her actual campaign special-character spawn.
The user's game session and original saves were not controlled by these tests.

## Reproduction and limits

Use independently permitted classic PC SA and III inputs. Extract the two
gameplay DFF/TXD pairs, inspect the source HAnim tables and III donor hierarchy,
convert with matching tag/order/bind rules, then reimport and inspect the output.
Compile the independent validator against the host's pinned librw and repeat the
isolated boot/save-reload test through the matched Mod Loader host.

The converter, native validation helper, complete hashes/logs and installation
payload remain with their implementation owner. Game-derived meshes, textures,
previews, executable inputs and saves are withheld. No mod release or website
deployment is part of this knowledge return; the public contribution contains
only this method and scoped evidence.

Cutscene body/head conversion, the opening prison outfit, normal player combat,
vehicle contact, Catalina's campaign spawn and close-up native rendering remain
untested owner checks. The offline preview is not an in-game screenshot. Retail
GTA III without skinned-ped support and Linux/macOS folder loaders were not tested.


## Correction and retained-rig validation — 2026-10-05

The earlier fitted 16-joint conversion above is historical. The corrected local
conversion retains all 32 SA gameplay joints for each character and keeps the
original joined-finger hand meshes, thumb shapes, triangles, UVs and skin
influences. Rebuilding separate fingers and projecting their UVs onto the old
hand tile produced texture striping and black margins. That experiment was
rejected and excluded from the final conversion. Preserve source hand artwork
and topology when the requested target is the original SA appearance.

The required generic host changes are public in
[re3 Extended PR 9](https://github.com/darkcenturies/re3-extended/pull/9), merged as
`00fbbdfcf3826d826cd49084215a74c94fd0fb59`, version 0.1.7. Native association
copies must be rebound against their actual target clump; template node ordering
from a stock 16-node model cannot be reused for a larger retained hierarchy.
Untracked helper rotations stay initialized, optional cutscene body cloning is
scoped, and per-model quaternion poses can drive original finger helper frames.
The generic host contains no character artwork or source animation clips.

A stock III Claude hand bind matrix was not fully orthogonal: its rotation-block
orthogonality error was approximately 0.008. Animation quaternions cannot encode
shear. Taking the nearest proper rotation for the target bind basis removed an
approximately 1.25 mm discrepancy in a direct native-SA finger skinning comparison.
This changes target joint axes, while keeping source vertex positions, UVs, joint
positions and hand influence weights. Rebasing uses the complete source local
quaternion through each character's own bind and parent axes. Angle-only curl
approximations or copying another character's bind bases are insufficient.

Native SA idle, two-handed pistol and seated-vehicle finger tracks were inspected
with the installed IFP reader. Independent skinning of the original gameplay
models and the converted models agreed within 0.00000007 metres in all six
character/pose comparisons. Both gameplay models retained 32 joints and their
original 1,089/1,280 and 1,040/1,338 vertex/triangle counts. UV coordinates were
exactly equal, skin-weight normalization differed by less than 0.000001, and
all four decoded gameplay/cutscene texture atlases matched source RGBA pixels
exactly. No separate fingers, new hand UVs or extra thumb joints were retained.

Cutscene bodies retained 61 Claude / 56 Catalina joints and split into 25 / 24-joint
facial heads. Claude's cutscene root bind is Z-up, unlike the X-up gameplay bind;
using only the gameplay axis conversion made the cutscene body incorrectly prone.
The source root inverse-bind orientation determines the appropriate rigid axes.
The standalone head also needs cancellation of III's head attachment rotation.

Two independent neck causes were corrected. Splitting a head from its body while
retaining mixed neck/head influences on only one side can open the shared border.
The coincident border must follow the same head joint on both sides. Facial root
motion must also be removed when the cutscene body already supplies head motion;
applying it again inside the standalone facial animation moves the neck twice.
Face-expression child motion remains retargeted from the III dialogue clips.

Current evidence, with game-derived paths and payloads withheld:

| Check | Result |
| --- | --- |
| Native DFF/TXD loading, texture lookup, skin indices/binds and clone binding | Nine pairs passed |
| Native facial interpolation/skinning | 56 directory entries × 20 full-clip samples; locked root vertices passed |
| Original cutscene triangle/UV surfaces | Recombined body/head surfaces matched both source meshes |
| Original cutscene hand skin influences | 164 Claude / 142 Catalina vertices checked; error below 0.000001 |
| Neck coincidence during body animation and head yaw | 39 samples per character; gap below 0.00000006 m |
| Offline III gameplay/hand pose deformation | 36 samples per character; p99 stretch approximately 2.233 / 2.175 |
| Independent published model inspection | Both outputs reported 32 bones, UVs, normals and four maximum influences |
| Isolated Windows association checks | Five clips per character, correct target bindings, finite matrices and four normalized finger helper poses |
| Scoped body selection followed by gameplay clone | 61/56-node cutscene bodies; subsequent gameplay clones stayed at 32 nodes |
| Installer synthetic cases | Success, hashes, inventory, rollback, existing mods, unknown host, settings and save preservation passed |
| Public host CI | Windows x64, Linux x64 and macOS ARM64 builds passed |

The isolated Windows fixture loaded a copied save and aliased Catalina as the
player. This does not prove her campaign special-slot spawn, weapon/vehicle
contact, every dialogue scene or native close-up visual quality. Head/neck and
hand previews remain offline renders. Linux/macOS character-file streaming and
retail GTA III remain unvalidated. The conversion implementation, derived
artwork/clips, full local logs, fixtures, saves and character installation archive
remain private/local; this knowledge return contains method and scoped evidence.


## Native rendering correction - 2026-10-05

The previous native parser and offline pose gates did not establish that the
running game used the intended character atlas or attached the facial head
correctly. A subsequent in-game report of missing heads/body parts required
native renderer captures through the matched Windows host.

Observed causes and corrections:

- A replacement special-slot head resolved its material through the stock III
  dictionary. That atlas contained transparent regions; the intended SA atlas
  was opaque. Bind matching material names directly from the active model TXD.
  A dictionary containing the right pixels does not prove a model used it.
- Skinned head attachment was conditional on the parent bone's world position
  being more than 100 units from the origin. World distance is not a validity
  test. Apply the parent head matrix and attachment rotation at every position.
- Some scenes have no Claude facial ANM, including C1_TEX. The placeholder
  animation contained identity rotations/zero translations, which discarded
  the converted head's attachment-cancelling bind rotation and helper offsets.
  Initialize both placeholder keyframes from authored frame transforms after
  clump initialization, then allow a real facial clip to replace that default.
  Initializing before clump setup was insufficient because setup overwrote the
  interpolated helper pose.

The original SA joined-finger meshes, thumbs, UVs, skin influences and all 28
binary character payloads remained byte-identical to the prior validated
conversion. The correction was in generic host rendering/initialization, rather
than a new hand design. The opening-outfit atlas was also checked directly.

A clean test host generated from the pinned engine
`f8142f1a7cefcfd6bcd778ed8802e21c93b97c91` and librw
`5501c4fdc7425ff926be59369a13593bb6c81b54` exercised actual C1_TEX
associations, Catalina's special slot, the 61/56-node cutscene bodies and the
25/24-node heads. Native D3D9 entity Render callbacks drew both components in
one pass at 0, 3 and 8 seconds, including world X=1000. Six captured material
atlases matched their supplied decoded pixels exactly. Independently skinning
captured native hierarchy matrices showed coincident 23/30 shared neck-vertex
pairs at every sampled time; the maximum disagreement was below 0.000002 m.
Nine native DFF/TXD pairs and 56 facial entries also passed oriented geometry
face/draw-index consistency and full-clip interpolation checks. Synthetic
quaternion regressions cover all axes, quarter turns, half turns and normalized
rotations. Owned-update installer tests cover complete backups, rollback and
refusal of edited/untracked mods while preserving settings and saves.

Useful rejected diagnosis: reversing only BinMesh draw indices disagrees with
native geometry faces and is not a valid winding correction. Source triangles
and native draw indices already agreed. Earlier incomplete offscreen captures
also used a non-MSAA color target against an MSAA depth buffer and omitted
camera registration in the lighting world. Register the test camera, match
color/depth sample counts and restore the real camera before destroying the
capture target. These fixture corrections do not imply an actual game-camera
MSAA fault. Capture-only MSAA changes did not alter the user's configuration.

Reproduction requires independently permitted classic SA/III inputs and an
owned fixture with the compatible test-only host. Compare captured material
pixels against the supplied atlas, skin body/head vertices with the actual
native matrices, verify coincident neck borders and inspect a combined entity
render. Do not substitute a null-backend texture lookup or offline preview for
those runtime gates. This remains controlled native fixture evidence; the
reported campaign scene and complete combat/vehicle/campaign behavior still
require visual gameplay review. Linux/macOS character rendering is unvalidated.
Character conversion source, derived artwork/clips, game fixtures, screenshots,
private paths/logs and the local character archive remain withheld. Generic
host code belongs in the separately approved re3 Extended destination.


The generic host correction merged through
[PR 11](https://github.com/darkcenturies/re3-extended/pull/11) as
[8880683e](https://github.com/darkcenturies/re3-extended/commit/8880683ec63087c250b90ebc7d284b8e3f4229db),
version 0.1.9. The [PR build](https://github.com/darkcenturies/re3-extended/actions/runs/37248881919)
passed Windows x64, Linux x64 and macOS ARM64, including the synthetic bind-pose
regressions. Main publication is a separate build; these source/CI results do
not imply a new character-artwork download in this public repository.

The subsequent [main build](https://github.com/darkcenturies/re3-extended/actions/runs/37249532640)
completed successfully for all three platforms and release publication at the
same merged revision. The [0.1.9 release](https://github.com/darkcenturies/re3-extended/releases/tag/v0.1.9)
Windows asset is ID `611104603`; its matching Actions artifact is ID
`11320177488`. The downloaded Windows ZIP SHA-256 is
`f890b7aecdcaae10bf1883ede828d52a7ffb85791e1c06a3885ccca4c336359c`.
All 52 manifest file hashes, the 375-setting registry fingerprint and absence
of the test-only command export were verified before selecting the two host
binaries for the local character update. Final-package installer regressions
passed fresh install, owned update, complete backup, rollback and refusal of
edited/untracked payloads. The installed update matched all 33 payload hashes,
preserved all 146 recorded settings/save/existing-extension files, backed up
the complete previous installation and retained all 28 character binary
payloads byte-for-byte. This is a verified local installation and controlled
native rendering result; the affected campaign scene still requires a visual
retry. Character artwork, conversion implementation and installation records
remain private/local.

## Opening betrayal correction, 2026-10-05

The reported scene was BET. Inspect its actual script and model assignments
before using a different scene as a proxy: it creates PLAYERX with no separate
Claude head, attaches CATH to Catalina, and uses two independently animated
COLT1 model instances driven by COLT1/COLT2 clips. A fixture that invents a
Claude head entity cannot validate this script's missing-head behavior.

Two separate faults were observed. The converted body originally omitted the
silent actor's head geometry. Adding an embedded head restored it, but the host's
skin-hierarchy callback returned null after the first atomic, stopping traversal.
The second atomic kept its rest orientation while the body turned. Continuing
the callback binds every skinned atomic. A named embedded head can then remain
visible until a mission attaches its separate dialogue head. Bone-name agreement
and finite matrices alone did not detect the unbound second mesh.

The held pistols require a separate check. Retaining SA joint positions changes
the hand locations relative to the III-authored prop paths; the measured wrist
position transfer reached about 0.265 m. Transfer the held prop's position while
retaining authored actor tracks, gun rotations and timing. The left prop changes
ownership during Catalina's pickup, so shifting its entire timeline would disturb
another actor. Per-character wrist axes and native SA grip poses address palm
orientation. Joined-finger meshes, thumb shapes, UVs and hand skin influences
remain original; changing texture coordinates or separating fingers is unnecessary.

The stock BET stance also turns Catalina's feet outward. Native stock renders
and five converted foot-axis comparisons confirmed the authored pose; the largest
rotation-matrix component disagreement was below 0.0007. Flared SA trousers make
the same ankle angle more conspicuous. This result supports retaining that stance,
not a claim that every foot contact in the campaign has been validated.

The same pinned engine/librw inputs above produced a Windows D3D9 fixture using
the actual BET association names at 0, 12, 22.8, 30 and 39 seconds. Both body
atomics reported a hierarchy binding at every sample. Claude required no invented
head entity, and the corrected render showed his head following his jacket.
Captured material pixels matched supplied decoded atlases exactly. Independent
body/head skinning in six additional dialogue-head samples, including a position
far from the origin, retained coincident neck borders within 0.000002 m.

All nine native DFF/TXD pairs and 56 facial entries passed the native parser and
full-clip sampling gates. Source preservation, 36 gameplay poses and 39 neck
poses per character passed. A synthetic installer test covered an owned update
without backups, exact independently verified host/plugin hashes, refusal of
edited models or unknown plugin bytes, locked-receipt preflight, and preserved
settings/saves. A no-backup update does not retain old payloads for I/O rollback.
The prior backup-mode suite was not rerun in this correction.

The generic host changes are tracked by
[PR 15](https://github.com/darkcenturies/re3-extended/pull/15).
Controlled Windows fixture evidence remains distinct from a full campaign
playthrough. Linux/macOS character rendering remains unverified. Game-derived
models, textures, animation payloads, fixtures, screenshots, conversion source,
local installation records and private history remain withheld.

Eight native held-prop comparisons retained stock gun rotations and reproduced
the stock wrist-relative positions within 0.001 m after transfer to the SA wrists.
This validates the sampled prop transfer, rather than every possible weapon grip.

The generic host changes merged as
[980c264c](https://github.com/darkcenturies/re3-extended/commit/980c264c9f76663b4c3fae5e5f11e593672c4c9a),
version 0.1.13. The [PR build](https://github.com/darkcenturies/re3-extended/actions/runs/37295244243)
and [main build](https://github.com/darkcenturies/re3-extended/actions/runs/37296563575)
passed Windows x64, Linux x64 and macOS ARM64; main release publication also passed.
The [0.1.13 release](https://github.com/darkcenturies/re3-extended/releases/tag/v0.1.13)
Windows asset is ID `612256902`, with Actions artifact ID `11339067953`.
The downloaded Windows ZIP SHA-256 is
`a5d8505ed0749be7ad5ebe18093f6faba5a919200f1c9f347a52abb0b14bdc5b`.
All 52 manifest hashes, Windows x64 PE types, source revision and absence of the
test-only command export were verified before selecting the matched host pair.
The character conversion was separately rebuilt from committed main source;
all 31 character payload files matched the native-tested conversion byte-for-byte.

## 2026-10-05: stock comparisons reveal missing weapon and arm-neutral mismatch

The owner reported a missing opening shotgun, raised aiming arms and splayed
gameplay idle arms. Matching stock/replacement Windows D3D9 entity renders
provided a stronger check than finite matrices or a rear-only preview. Five BET
times (0, 12, 22.8, 30, 39 seconds) were inspected from front, side and a shared
two-actor camera; four actual player idle poses covered 0 through 2.25 seconds.
The same camera, lighting and association times were used for stock, prior and
corrected inputs. These inspection cameras omit scenery, authored mission-camera
playback and audio; they are not a recorded campaign playthrough.

Observed: the stock PLAYERX right-hand geometry includes a second material for
the shotgun. Replacing that whole geometry loses the weapon even though the
mission creates no independent shotgun entity. Its locally inspected weapon
surface contains 439 vertices and 268 triangles. Keeping only that surface as
another fully bound atomic preserves the SA joined hand. Restricting the part
to the opening model prevents a shotgun appearing in unrelated dialogue aliases.
Original weapon UVs, oriented triangles, decoded texture pixels and local-space
vertices were verified; the running renderer's material pixels also matched.

The arm issue was a rest-pose mismatch. Retaining the SA A-pose mesh and joint
positions while assigning III animation axes did not align the original limbs
with III's animation neutral pose. A wrist-only counterrotation cannot correct
an upstream upper-arm/forearm mismatch. Articulate the original arm segments
into the target neutral alignment while retaining their lengths, influences
and joined-hand surfaces. Each original hand and its helpers move rigidly
together; native SA finger poses are then expressed in that new neutral basis.
Existing cutscene thumb/terminal helpers retain their source rest rotations.

All 56 measured native arm-segment comparisons improved. Gameplay idle direction
differences fell from about 23 degrees to below 0.23 degrees; cutscene differences
remained up to 7.91 degrees with the retained SA anatomy. Eight held-pistol
comparisons kept authored gun rotations and stock wrist-relative placement
within 0.00004 metres. This supports the sampled alignment correction, rather
than asserting identical silhouettes or every possible aiming/contact pose.

Independent preservation checks retained source UVs, textures, skin influences
and arm segment lengths. The 100 Claude / 84 Catalina hand-only vertices matched
reposed native SA idle/weapon/vehicle finger deformation within 0.000002 metres.
Vertices blending forearm and hand cross separately articulated segments; their
linear-blend skinning residual was recorded separately, reaching about 0.0061 m.
Do not silently widen an exact hand-preservation claim to include that seam.
Nine native model pairs, 1,120 facial interpolation samples, 36 gameplay and 39
neck poses per actor passed. Six additional attached-head renders retained
coincident native neck borders and exact character atlases. All three opening
Claude atomics were bound in five samples. No finger separation, remeshing or
replacement thumb was necessary.

The conditional native comparison harness and developer instructions are in
[re3 Extended PR 16](https://github.com/darkcenturies/re3-extended/pull/16).
The full Windows host/loader/plugin build, audio/shader checks, synthetic tests,
installer checks and 52-file package boundary gate passed locally. The existing
verified 0.1.13 runtime supports the local asset correction; the harness change
does not introduce a new runtime release. A synthetic owned-update test passed
without creating backups, including edited-file/unknown-plugin refusal,
locked-receipt preflight and settings/save preservation.

Reproduction requires independently permitted classic game inputs and an owned
test fixture. Inspect embedded weapon materials as well as actor/prop scripts;
compare actual entity renders at equal times and views, measure semantic joint
directions, and verify textures/skin bindings and attached neck borders.
Complete campaign playback and Linux/macOS character rendering remain unverified.
Game-derived models, textures, clips, screenshots, comparison artifacts, private
conversion implementation, fixtures and local installation records stay withheld.
