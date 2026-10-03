# Bully school map conversion findings

Question: can school exterior and interior geometry from a locally supplied
Bully: Scholarship Edition PC installation be converted for classic GTA San
Andreas PC as an overhaul base?

## Observed format and tools

The inspected source NIF header was Gamebryo 20.3.0.9. `World.img` used the
IMG v1 archive plus external `World.dir`. School definitions were text IDEs;
placements were IPB records inside the archive. Models and textures were NIF
and NFT, respectively. These are observations of the supplied PC inputs, not
claims about the PS2, Wii, Xbox or mobile editions.

Tools actually used: Python 3.11, PyFFI 2.2.3, bullyfury 0.1.2, the installed
DragonFF standalone DFF/TXD/COL readers, Blender 4.5.3 LTS and Sanny Builder 4.2.0.
Exact local input and parser hashes belong in the private build manifest.

Upstream references and attribution:

- [DragonFF](https://github.com/Parik27/DragonFF), Parik27 and contributors,
  GPL-3.0-or-later: exported GTA file readback and preview geometry.
- [PyFFI](https://github.com/niftools/pyffi), NifTools, BSD: NIF meshes and hierarchy.
- [bullyfury 0.1.2](https://pypi.org/project/bullyfury/), MIT: archive access,
  NFT texture extraction and parsed Bully collision primitives.
- [Sanny Builder CLI](https://docs.sannybuilder.com/editor/cli): ordinary SA
  startup script compilation, separate from CLEO extension validation.
- [GTA Scout Blender guide](https://github.com/Dryxio/gta-scout/blob/main/docs/blender-cli.md):
  consulted through the authoring catalog; its renderer/catalog tools were not run.

The Valkyrie model, texture and collision methods were consulted through their
registry. Host/project-specific legacy entries were not required for this NIF
input. No native ASI hook or CLEO script was authored, and no native build result
is implied by compiling an ordinary main mission script.

## Failed approach and correction

Combining full NIF world transforms with IPB instance transforms double-applied
the named model node's authoring placement. Exported files could parse correctly
while the scene rendered as scattered pieces. This experiment was rejected.

The corrected method removes the named model node's authoring transform, retains
all child transforms, bakes IPB instance scale once, then writes IPB position and
quaternion to GTA IPL. Repeated props retain their instance-specific placements.
Previews must read exported GTA geometry rather than only inspecting the source.

Invisible `NOGO_` navigation meshes and `DL_` projected lighting volumes can
appear as opaque helper shapes under ordinary materials. Exclude them from
visible scenery and record the missing gameplay/lighting semantics separately.
An empty NIF placeholder is another explicit skip, not a successful mesh export.

A second export issue appears at the loader boundary: ordinary SA static `objs`
retain one atomic object. Multi-atomic models can render fully in Blender while
the game retains only one part. This follows the reconstructed loader's
[`SetRelatedModelInfoCB`](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/FileLoader.cpp)
behavior; it is engine-reference evidence, not an executed test of the supplied
game binary. The corrected export joins each model into one geometry and atomic,
preserving its separate material assignments. Validation enforces this contract.

The source NFT set resolved the NIF reference `sc27_glass` through its shipped
`sc27_glass_d` texture. Record this exact discrepancy; do not silently fabricate
a replacement texture or use arbitrary filename guesses.

The conservative whole-IPB parser in bullyfury 0.1.2 rejected an encountered
`rail` chunk. Reading the verified initial instance table avoided that unsupported
chunk without claiming lossless understanding of the rest of the container.

## Validation performed

The final experiment emitted 897 static model variants and 2,062 placements
across one school exterior and fifteen school interior scenes. Independent
readback checked 526,593 mesh triangles, 215 texture dictionaries, 1,991 stored
texture entries including complete mip chains, and 298 collision models.
All exported diffuse references resolved. Model indices, finite coordinates,
map references and payload hashes were checked. Exterior and main-hall renders
confirmed that the corrected assemblies were visible and aligned.

Joining affected 505 models. Independent write/readback preserved a per-triangle
digest of all 526,593 triangles, vertex positions, normals, UVs, colors and material
texture references. Every model contains one atomic and geometry. The largest
has 31,284 vertices, below the format's 16-bit index limit; oversized models would
need placement splitting, not truncation. This check supplements the scene renders.

Native D3D9 BGRA8888 TXDs and RenderWare 0x36003 DFFs were emitted. Parsed Bully
boxes/meshes were translated into GTA COL3; source surface IDs were mapped to
the default surface, and unsupported collision tails were withheld.

An ordinary mission-free startup script compiled with Sanny Builder. Temporary
area travel uses vanilla game controls. Destination points came from horizontal
collision triangles; that establishes static floor evidence, not safe spawning
or successful gameplay.

For a whole-map replacement, removing text IPL lines alone is insufficient:
the default IMG archives also contain binary placement streams. The experiment
removed 164 such entries from the exterior archive and 26 from the interior
archive, checking every retained entry byte-for-byte against its original.

## Reproduction and limits

### Subsequent runtime failure and configuration findings

A user launch later crashed while loading a new game, before the school loaded.
The crash report put an access violation at `0x004C67BB`, with EAX zero and
ESI `0x00B478FC`; the stack included pedestrian definition loading. Offline
disassembly of the supplied SA 1.0 US executable placed this at AddPedModel's
virtual initialization call. The reconstructed
[`CModelInfo` implementation](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Models/ModelInfo.cpp)
supports that function identification. It does not establish the state of live
third-party patches.

Two installed limit adjusters both owned the ped-model pool: one used a fixed
350-record capacity, the other an unlimited pool. Their patch interaction is a
suspected cause, not a confirmed successful repair. Independently, a co-installed
character pack supplied an IDE-only GTA.DAT override. The observed effective
Mod Loader cache omitted the school configuration. Change IDE-only overrides to
append-only readme registrations and give each pool one adjuster owner.

The map package also must preserve stock IDE definitions, supporting IMG archives
and zone definitions even when all stock scene placements are removed. Fixed-ID
resources still need definitions. Corrected registration checks retained 54 stock
IDEs and three supporting archives, loaded only sixteen school scene IPLs, counted
291 ped records within capacity 350 and found no conflicting model IDs. Preparation
and syntax checks passed; successful post-repair gameplay has not been observed.

The user's next launch passed pedestrian definition loading, registered the stock,
school and character/phone definitions, and loaded the school exterior IPL. This
confirms progress past the first startup failure in that run. It then crashed at
`0x00534134`, dereferencing a null collision-model pointer in GetBoundRect. Offline
disassembly and the reconstructed
[`CEntity::GetBoundRect`](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Entity/Entity.cpp)
agree that world insertion reads collision bounds before visible model streaming.

The exporter had emitted COL records only for the 298 models with parsed physical
collision, leaving 599 placed models without bounds. Even non-colliding scenery
needs a bounds record for world sectors and culling. The corrected archive has
897 per-model records: 298 physical and 599 bounds-only, with no fabricated collision
surfaces. Write/readback verified coverage of every model and retained all original
collision bytes unchanged. Validation now requires finite ordered bounds and full
per-model coverage. This corrects another exporter failure; successful post-fix
gameplay still needs verification.

With separately permitted local game inputs: inspect the source archive/IDE/IPB
headers, convert geometry and textures, read all exported GTA assets back,
assemble IPLs, render exterior and interior views, compile the ordinary startup
script, then filter embedded default map streams while verifying retained data.
Record input/tool hashes and separate source, build, install and gameplay states.

There was no successful in-game validation. Natural entrance routing, animation controllers,
NPCs, missions, traffic, projected lighting shaders, detailed collision surface
mapping and radar replacement remain outside the completed static conversion.
Do not describe this as a finished total conversion or verified runtime release.

Implementation, installers, extracted game assets, generated map archives and
renders remain with their private/local owner. This contribution returns the
public-safe method and failed experiment only; merging it does not publish a mod.

### Startup bytecode failure after complete scene loading

The next user launch loaded all sixteen school IPLs and the supporting game data,
then failed at `0x0085C4AC`. Offline disassembly places that target in data, reached
by the script opcode dispatch call returning at `0x00469FF7`. Its argument was
`0x5DE1`, outside the stock command range. The same two bytes occur at offset 1047
in the startup script's player spawn Z float.

The compiled CREATE_PLAYER instruction put its output variable before its four
inputs. SA consumes four inputs followed by a variable output. The misplaced
float type is consumed as an unsupported output, leaving its payload to be read
as the next opcode. This explains the exact observed invalid command value;
no live process memory was captured. GET_PLAYER_CHAR and fade argument order
also needed correction.

[Sanny Builder's mode documentation](https://docs.sannybuilder.com/edit-modes)
distinguishes legacy custom parameter ordering from SBL's original ordering.
The local Sanny 4.2.0 log selected `sa_sbl` when the earlier command supplied both
`--game sa` and `--mode sa`. Use the explicit SBL mode by itself and author its
input/output order. Successful compilation alone did not catch this mismatch.
The [command library](https://library.sannybuilder.com/#/sa) supplies independent
parameter signatures; the reconstructed
[script parameter reader](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Scripts/RunningScript.cpp)
supports the input/output consumption explanation.

The corrected 1,664-byte binary was independently decoded against Sanny's
stock-command catalog: 146 instructions, 22 instruction-aligned branch targets,
variable outputs, valid player/character handle ordering, global bounds and fade
direction checks passed. Sanny decompilation confirmed the corrected ordering.
The original binary was rejected at CREATE_PLAYER. Mutations placing a literal
in the output, jumping into an instruction, and reversing a fade's arguments were
also rejected. Python and PowerShell parsing passed. Runtime compatibility remains
unverified; this is a startup correction awaiting an owner launch, not a successful
in-game test. Bytecode, game payloads and implementation stay private/local.

### Physical collision coverage correction, 2026-10-04

After the startup correction, the owner reported reaching the map and finding
widespread missing collision. This is partial owner runtime evidence, not a full
play-through. The installed archive had physical primitives for 298 models and
only culling bounds for 599. Empty source COL bodies include major buildings,
walls and interior floors; scanning all source collision entries found no duplicate
model IDs hiding another parsed physical mesh. Bounds alone do not make scenery
solid.

For solid scenery without parsed source primitives, the corrected port derives
collision from the transformed exported render mesh. This is an explicit fallback
policy; Bully's runtime collision generation and scripted behavior were not
reconstructed. Preserve existing physical colliders and keep decal, glow, shadow,
reflection, screen and water overlays non-solid. Use a concave mesh to preserve
rooms and door openings rather than enclosing entire buildings in AABB primitives.

COL3 mesh vertices use a signed fixed-point grid. Weld on the 1/128-unit grid,
reject out-of-range coordinates and excessive counts, remove collapsed/duplicate
triangles, and group triangles spatially for collision candidate checks. The
[reconstructed SA collision implementation](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Collision/Collision.cpp)
shows the face-group bounds checks used during sphere-versus-scene candidate
selection. Two very small scaled props collapsed below the mesh grid and used
float box primitives with their actual local bounds instead.

The tested upgrade retained all 298 original physical records byte-for-byte,
added 517 solid models (515 meshes and two tiny boxes), and left 82 visual overlays.
An independent generic COL parser agreed with all 897 records. Exact quantized
triangle coverage matched every derived mesh; 6,024 representative static rays
from both sides passed. A synthetic doorway retained its open center and blocked
both side panels. Coordinate-overflow rejection and explicit effect-policy checks
passed. Full asset validation passed 2,062 placements, 526,593 visible triangles,
215 TXDs, 1,991 texture entries, 420,343 collision triangles and 4,348 face groups.
All non-overlay models now require physical primitives; flags, compressed ranges,
face-group coverage/bounds and the collision archive hash are checked.

Python and PowerShell parsing passed. Updated collision gameplay and performance
remain awaiting owner verification. The prior startup correction and all visible
models, textures and placements are preserved. Generated colliders, asset payloads,
implementation and local operational details remain private/local.

### Contact normals, partial terrain coverage and interior lighting, 2026-10-04

The owner subsequently reported remaining terrain/object collision gaps and overly
bright interiors. Read-only inspection of the running classic SA 1.0 US process
matched collision counts and bounds for all 897 imported model definitions against
the installed archive. This rules out missing archive registration for that run;
it does not prove that every surface behaves correctly during gameplay.

Original parsed terrain faces had the expected SA normal direction, but generated
collision faces used the exported render order. In
[gta-reversed's triangle-plane reconstruction](https://github.com/gta-reversed/gta-reversed/blob/7f3197a0e9b49aa5e364775957df6bd44eb656d3/source/game_sa/Collision/ColTrianglePlane.cpp),
SA's normal is computed in the opposite cross-product order to that render
convention. The previous two-sided ray probes verified intersection geometry,
but did not verify contact-normal direction. Generated faces now reverse their
render order. Duplicate removal preserves opposite-facing cycles so two-sided
walls retain both normal directions. This is a correction to the preceding
verification method, not a claim that SA always rejects backface line queries.

Separate terrain probes found four visible points across two models outside the
parsed source collision surfaces. The revised coverage policy combines visible
render surfaces with source collision primitives, while preserving authentic
collision-only helper models rather than replacing them with their dummy render
planes. This increases collision detail and still requires gameplay/performance
verification. Source runtime collision generation remains unreconstructed.

All interior placements previously used exterior area 0, and baked-color geometry
also enabled RenderWare lighting. The correction assigns areas 1 through 15 to
the interiors, links both the visible area and player area before scene loading,
and disables additional geometry lighting where baked colors exist. Authored
colors, textures, materials, normals and all other DFF bytes remain unchanged.
The anticipated brightness improvement is an inference from these asset settings;
it has not yet been visually confirmed inside SA. Global brightness and third-party
shader configuration were not modified.

The repaired build passed independent readback of 897 COL records, oriented
quantized render coverage for 768 nondegenerate rebuilt models, 5,988 contact-normal
probes and 1,553 upward terrain contacts. Two tiny props retain float boxes. The
42 original collision-only helper records and 85 overlay records are unchanged;
three of those overlays already had parsed physical collision. There remain 815
physical models and 82 bounds-only overlays, now with 515,928 collision triangles
and 5,464 face groups. Byte comparison confirmed that 870 DFF changes consist only
of their geometry lighting flag. Full asset readback and 1,112 packed IMG payloads
passed. The 1,851-byte Sanny 4.2.0 SBL startup script passed independent decoding of
180 instructions, 22 branch targets and matching player/visible areas for all
sixteen destinations. A deliberately invalid area assignment was rejected.

Python 3.11, NumPy, DragonFF and bullyfury 0.1.2 were used for the local checks;
PowerShell syntax passed. The applicable catalog route was model/world authoring
with the original gta-reversed engine reference at revision
`7f3197a0e9b49aa5e364775957df6bd44eb656d3`. No CLEO source or native hook was added;
CLEO AI was not run for this ordinary SCM and asset correction. Implementation,
live memory details, game assets and generated binaries remain private/local.
This finding records verified file changes and owner-reported symptoms; merging
the finding does not establish a successful gameplay test or publish a mod.
