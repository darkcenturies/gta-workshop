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
