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

With separately permitted local game inputs: inspect the source archive/IDE/IPB
headers, convert geometry and textures, read all exported GTA assets back,
assemble IPLs, render exterior and interior views, compile the ordinary startup
script, then filter embedded default map streams while verifying retained data.
Record input/tool hashes and separate source, build, install and gameplay states.

There was no in-game validation. Natural entrance routing, animation controllers,
NPCs, missions, traffic, projected lighting shaders, detailed collision surface
mapping and radar replacement remain outside the completed static conversion.
Do not describe this as a finished total conversion or verified runtime release.

Implementation, installers, extracted game assets, generated map archives and
renders remain with their private/local owner. This contribution returns the
public-safe method and failed experiment only; merging it does not publish a mod.
