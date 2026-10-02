# Native vehicle damage authoring findings

Question: which model structure lets an imported car use GTA San Andreas
1.0 US native panel damage, flying components and cracked glass?

## Engine evidence

Reviewed GTA Community's gta-reversed at revision
`204e610a53d002c26ec12b6f70ce1145f0f14219`:

- [VehicleModelInfo preprocessing](https://github.com/gta-reversed/gta-reversed/blob/204e610a53d002c26ec12b6f70ce1145f0f14219/source/game_sa/Models/VehicleModelInfo.cpp)
  sets the component damageability mask when both intact and damaged atomics
  are found under a recognized damageable component frame.
- [Automobile damage handlers](https://github.com/gta-reversed/gta-reversed/blob/204e610a53d002c26ec12b6f70ce1145f0f14219/source/game_sa/Entity/Vehicle/Automobile.cpp)
  switch visibility, spawn flying components and shatter the windscreen.
  Severe front bumper impacts can propagate to wings, bonnet and windscreen.

These are upstream reconstructed-engine claims, not executed runtime evidence
from this investigation. No native hook or ABI change was made.

## Local authoring observations

An owner-local imported car had doors, bonnet and hatch damage pairs, but its
bumpers and windscreen were merged into fixed chassis geometry. Deformation
and functional lamp materials alone did not provide those missing components.
Damaged door and hatch meshes still used intact window materials.

A private adaptation transferred existing faces into native dummy frames with
independent intact/damaged atomics. Readback verified exact intact normals,
UVs and raw materials, with position tolerance of 2e-7 m. Original frame and
collision records remained unchanged; untouched geometry chunks were compared
byte-for-byte. Face accounting and index checks passed. CPU previews of intact,
damaged and hidden components were inspected. A locally supplied stock car's
shatter material established texture naming and mapping; no stock payload is
published here.

Useful failure: comparing rounded vertex coordinates as signatures can fail
at rounding boundaries after subtracting and restoring a component pivot.
Follow original face indices and compare positions with an explicit numerical
tolerance, while keeping unchanged attributes exact. Another failure: parsed
DragonFF geometry extension objects cannot all be serialized directly; preserve
unknown raw extensions and rebuild only mesh-dependent structures.

## Reproduction and limits

With independently permitted inputs, inventory frame names, parents and
atomic geometry indices. Compare a local stock car's damage pairs. Check
collision piece identifiers and plugin configuration separately. Transfer
existing faces into recognized component pairs, compact vertices/materials,
recalculate bounds and read the resulting DFF back. Compare intact face
attributes in world space and inspect damaged and removed states visually.

This evaluation used Python 3.11, NumPy, Pillow and the installed DragonFF
parser/writer. The DragonFF checkout had no Git metadata, so its revision was
not established. Original DragonFF attribution remains with
[Parik27/DragonFF](https://github.com/Parik27/DragonFF).

The Dryxio authoring/native reference routes were consulted. The public
`workshop/tools/model-conversion/inspect_dff_asset.py` entry was inspected
(source SHA-256
`e50462ef55ed6ccd96afc4cc51b862d777ff0ecf7e25257813b17703a30dfb7d`);
it requires Blender/bpy and was not executed. The task-specific private
DragonFF readback and CPU renderer ran instead. CLEO AI was not applicable.

Continuous widebody shells lack artist-authored detachable seams. Transferring
whole faces preserves intact appearance but requires visual review of detached
edges; inner fracture caps are a separate authoring task. Native GTA does not
supply independent damage physics for every glass pane merely by adding a
cracked texture. Component-state cracking and pane-specific bullet/fracture
simulation are different scopes.

No game launch, impact test, repair test or plugin-combination runtime pass was
performed. Static results cannot establish flying debris, all collision damage
paths, independent pane breakage or runtime lamp behavior. Private source,
inputs, asset fingerprints, generated models and installation details are
withheld; only the reusable method and limitations are returned. Private
implementation source was committed and pushed before installation.

## Follow-up: removal exposed an unfinished inner body

The owner rejected the initial removal preview because it exposed missing
inner-body surfaces. Recognized component names and intact/damaged pairs were
necessary, but did not finish the damage-ready asset. The initial investigation
explicitly lacked inner backing; that limitation should have been resolved
before describing the model as ready for normal destruction.

A direct CPU comparison with a locally supplied stock Elegy showed its fixed
front carrier and rear body remain behind removed bumpers. Its front fenders
also remain on the chassis. GTA does not synthesize a new body surface when
an outer component is hidden.

Further face ownership inspection found inner wheel housing and undertray
faces assigned to removable skins. The correction returns those faces to
fixed body geometry and adds recessed bumper supports, a shaped rear body,
floor joins and short returns from actual shell boundary edges. Outward
wheel-housing faces are also needed: a correct inner-facing liner can still
vanish from an exterior view under backface culling. An inward-normal offset
for edge returns avoided visible protrusions caused by a simple longitudinal
offset at curved bumper corners. The rear floor was adjusted to leave exhaust
tips exposed.

Readback verified original restored positions, normals, UVs and raw materials,
unchanged collision and unchanged unrelated geometry. Six exposed support rays
hit the new front/rear backing rather than the distant cabin. Matched intact,
removed and backface-culled CPU previews were inspected alongside the stock
car. The private correction was committed and pushed. Gameplay verification,
flying panel backside appearance and exhaustive closure remain untested.

Reusable lesson: damage-frame validation must be followed by a visual audit of
what stays on the car and what falls off. Review both sides of inner panels,
not only an intact exterior or a two-sided renderer. Keep intentional wheel
and engine openings distinct from missing body surfaces.

## Follow-up: distinguish a damage enum from detachable bodywork

The owner also identified an inconsistent reference comparison: the stock
Elegy's fenders stayed on while the imported car's front wings were removed.
The imported fenders were returned to fixed components. Their redundant
damaged atomics were removed and indices compacted; readback confirmed all
remaining geometry chunks unchanged. A culled removal preview now retains
fenders while hiding the intended detachable parts. A native damage enum or
recognized component name alone is not a reason to make that body panel
physically removable. Select the intended parts from the actual reference.

## Follow-up: parity extends beyond damage frames

A read-only DragonFF comparison with locally available stock Banshee, Elegy
and Sultan found that a damage-ready import can still omit their embedded COL
shadow geometry, native paint-key materials, remap textures, tuning attachment
frames and scratch materials. Check the model and its registration together:
`carcols.dat` and `carmods.dat` are separate from the DFF hierarchy. These
differences are observations about the compared inputs, not requirements that
every GTA car must support every upgrade or paintjob.

Absence of COL shadow triangles does not prove that no shadow appears at any
graphics setting. Likewise, missing attachment frames should be recorded
without claiming their runtime consequences from names alone. Distinguish
component-state glass cracking from independent pane damage, and count active
geometry separately from stored intact/damaged/LOD alternatives when discussing
rendering cost. No game launch or runtime verification was performed. Asset
payloads, private inventory and product-specific counts remain withheld.

## Follow-up: apply native parity without discarding the supplied model

An asset-only preparation retained the supplied model's existing frame
transforms, exterior vertex positions/normals, occupant fit, physical collision
and light/steering chunks while adding the missing native authoring features.
Readback compared the original physics volumes/mesh exactly; a separate COL
shadow receiver used the existing authored body mesh. This receiver should not
be described as a guaranteed new cast-shadow silhouette across renderers.

For native recolouring, separate the colourable substrate from a white decal
layer. Baking paint and multicolour artwork into one diffuse map makes a later
respray multiply both. A single remap atlas can hold substrate, seam skin and
decal regions while extra decal vertices retain their original palette. Local
palette/mask data reproduced the supplied baked livery exactly. Colour-table,
upgrade-list and wheel-class registration were prepared alongside the model;
only actually authored upgrade compatibility was advertised.

Useful failure: negative/repeated UVs must be resolved before atlas placement.
Scaling an original wrapping UV directly into a quadrant samples neighbouring
regions. Clip triangles at periodic texture boundaries, interpolate their
existing attributes and verify unchanged geometric area before remapping.

Detached bumpers received inset inner skins and measured boundary returns;
other detachable parts retained authored interior lining. Damaged states gained
transparent locally supplied stock scratch overlays. Fixed quarter glass was
placed in the native fixed-glass damage group without inventing rear doors.
This allows shared cracking/removal, not independent per-pane bullet physics.
Material alpha must also be checked: native window-alpha removal skips fully
opaque materials even if the texture itself has transparency.

The same Python/NumPy/Pillow/DragonFF workflow performed bounded chunk edits,
geometry/texture readback, frame and collision preservation checks and matched
CPU previews. Two existing renderer clipping/depth regressions passed. Factory,
damaged, removed, resprayed, clean and inward-facing detached-part views were
inspected with backface culling. No game launch, garage/paintjob streaming test,
crash/repair test or plugin runtime pass was performed. Private implementation,
asset inputs/outputs and installation inventory remain withheld. The cited
GTA Community vehicle-material and hierarchy source is reconstructed-engine
evidence; compilation/readback and gameplay validation are different gates.

## Follow-up: scratch overlays need surface-aware mapping

Matched CPU views exposed a failure in whole-component planar scratch mapping:
an acceptable flat-door projection became long stripes over curved bumpers and
wrapped hatch surfaces. A component name does not define a single texture plane.
Preserve an accepted flat-panel mapping and correct only the rejected surfaces.

The correction used small square patches measured in model units, projected in
local tangent planes. Clip intersecting skin triangles at the patch rectangle,
interpolate their attributes, and exclude faces whose outward normals turn away
from that plane. Keep glass, trim, liners and underlying paint/artwork UVs out
of the overlay selection. This bounds texture scale and avoids projecting a
scratch onto perpendicular returns or unrelated spoiler surfaces.

The existing Python/NumPy/Pillow/DragonFF workflow read back the exported result
and compared untouched chunks, frame transforms, collision and the original
skin's positions, normals and UVs. Culled before/after close-ups covered each
changed component plus an unchanged door. The two existing preview-renderer
clipping/depth regressions passed. These checks establish a localized asset
correction, not physical damage behavior or plugin compatibility in gameplay.
No game was launched. Private source, asset payloads and installation details
remain withheld; the earlier dependency provenance and evidence limits apply.

## Follow-up: preserve angular damage instead of smoothing it away

A local stock-model comparison found that authored damaged panels combine
displacement, added topology and hard creases. Some alternate bumper atomics
also rotate relative to their shared dummy. Measure intact/damaged points in
that common basis and make diagnostic renderers honor frame rotations.

The first experiment used smooth interpolation of donor displacement samples.
The owner rejected its rounded dents because the reference showed triangular
folds. Exact paint UV matches and barycentric correspondence within the intact
UV chart can locate the original positions of added damaged crease vertices.
Disambiguate mirrored seams by spatial proximity and reject uncertain samples;
UV identity alone is not enough to match overlapping parts.

The corrected experiment used SciPy Delaunay control regions and piecewise
affine displacement. Clipping the existing target triangles at those region
edges creates actual crease boundaries. Interpolate original surface/texture
attributes before deformation; apply each region's normal transform while
retaining discontinuities between regions. Transfer the same field to skin,
artwork and inner lining. This reconstructs a stock-inspired crease layout for
different topology, not the donor's exact face connectivity or a fragment
simulation. No triangles were removed merely to manufacture visible holes.

Almost collinear authored vent faces exposed another failure: a nonlinear
field opened previously invisible slivers. Pin their feature edges and panel
perimeters. Verify conserved surface area before deformation, valid indices,
finite attributes, noncollapsed/nonreversed faces and unchanged intact chunks,
materials, frames and collision. Crease splitting increases stored geometry;
separate alternate-state totals from runtime rendering/performance claims.

The existing Python/NumPy/Pillow/DragonFF workflow plus SciPy performed asset
readback and culled comparisons of stock intact/damaged and target previous/new
panels. Two existing renderer clipping/depth regressions passed. No game launch,
impact-physics, fragment, performance or plugin compatibility test was performed.
Private implementation, assets and installation details remain withheld.

## Follow-up: evaluate crease strength against the reference

The owner found the triangular pass too subtle in the matched stock comparison.
Judge fold depth and sharpness beside the reference, not merely by whether the
target differs from its previous version. A stronger experiment added normal
buckling to existing crease geometry while retaining lateral fit, texture
coordinates, material chunks, intact components and collision. Narrow feature
edges stayed pinned; existing hard normals rotated with their faces. Culled
close-ups made the increased ridges and bumper crumpling directly comparable.

A normal-axis shear can rotate a valid face beyond 90 degrees. A negative dot
product with its previous normal alone does not prove topological inversion.
In this constrained pass, in-plane coordinates/projected winding remain exact;
face-area checks and exported readback separately reject collapse and invalid
attributes. Distinguish geometric validity from aesthetic acceptance and
gameplay evidence. The stronger pass retained the earlier crease topology,
passed static checks and the two renderer regressions, and was inspected in
matched CPU previews. No gameplay or plugin runtime test was performed.

## Follow-up: exposed engine detail after bonnet loss

On GTA:SA PC, removing a bonnet can expose an engine photograph stretched over
a shallow surface. An experiment replaced the central photograph with beveled
volumes for a longitudinal V6, separate cylinder banks, intake runners, plenum,
cover, intake duct, airbox and accessories. Retain the target vehicle's engine
identity while adopting stock vehicle texture/detail conventions. A stock
engine transplant is unnecessary. The
[Nissan 2003 press kit](https://usa.nissannews.com/en-US/releases/2003-350z-press-kit)
identifies the VQ35DE; the
[factory engine manual](https://boredmder.com/FSMs/Nissan/350z/2003/EM.pdf)
provides intake collector and duct context. These were consulted as mechanical
references; no vendor image was downloaded into the asset.

Reuse locally available atlas regions for the matching cover and cast surfaces,
shared vehicle metal and existing plastic/rubber textures for actual sides.
Check texture names case-insensitively against both local and shared dictionaries.
Preserve the original cowl/perimeter geometry and provide a recessed tray plus
lower backing: adding engine volumes alone does not close exposed gaps beneath
them. Compare culled oblique and top views, as a top view can hide missing sides.

The existing Python 3.11.8, NumPy 1.26.4, Pillow and local DragonFF workflow
generated the model, checked readback and produced matched CPU previews.
Existing materials, unrelated geometry, frame/atomic and collision chunks were
verified against the input; the texture dictionary and other archive payloads
were preserved. Two existing renderer regressions passed. New solid vertices
and face centroids were sampled against the closed bonnet underside. Such
sampling is not an exhaustive intersection proof; inherited perimeter junctions
must be distinguished from newly authored masses. No gameplay, deformation,
performance or plugin runtime test was performed. Implementation, assets and
private installation details remain withheld; the method is reproducible with
permitted local models/textures and a synthetic beveled-volume authoring exercise.

### Correction: retain context and align details to the atlas

Owner review rejected an empty surrounding bay, inconsistent material tones
and bolts placed on a guessed grid. Retain small wiring, brackets, fittings and
covered compartments as photographed surfaces when modeling each one is
unnecessary. Preserve original UVs and smooth normals on that context; suppress
the redundant central photograph beneath the replacement cover so it does not
look like a second lid. Locate raised fasteners by inverting the cover's actual
UV transform from measured native texel centres. Sample each cap at its mark,
and compare culled close-ups; a regular mechanical-looking grid is insufficient.

[GTA Scout](https://github.com/Dryxio/gta-scout) revision
`499ab20f625a90ef2ef3dc67bffc17589f522d59` (`gta-asset-search` 0.1.0a1)
was executed for its synthetic demo, fresh local source catalogue, shared-pack
matching, lexical discovery and native UV overlay. Shared descriptions had
limited matching coverage on the local installation; no semantic embeddings
were built. A junkyard engine texture lead was rejected rather than replacing
the target engine's identity. Metadata, UV context and visual evidence remain
distinct: successful catalogue construction does not validate the model.

Blender 4.5.3 initially crashed during the static importer's UV/color assignments.
A local review adapter creates both mesh attributes, then reacquires their
handles before writes. With that adaptation the Scout importer completed a
matched bay inspection scene; upstream files were unchanged. Record this
adaptation when reproducing rather than claiming the unmodified bridge passed.
Newly generated readback and two renderer regressions passed. Installation
remained guarded while GTA was running; no gameplay verification was performed.
Private implementation, asset identities and local evidence are withheld.

### Correction: a bound texture can still look untextured

Further owner inspection found flat caps, narrow side-strip mappings and an
overstretched backing patch. A valid texture binding is insufficient: constant
UVs sample one texel, while a tiny atlas strip stretched over a broad face can
lose readable detail. An auxiliary generated diffuse atlas with material-specific
metal, plastic, reservoir and mechanical-detail regions addressed those surfaces.
Map full cap/side extents into their material region; retain target-specific
cover branding and the existing photographic context separately. Do not credit
texture detail with independent geometry, component physics or runtime damage.

The finishing pass changes material assignments and UVs while preserving all
positions, normals, topology, original material chunks, unrelated geometry,
frames and collision. A native texture-dictionary append retains original
native texture chunks byte-for-byte and adds a D3D9 raster with full mip levels;
decoded pixels are checked against the authored input. Culled comparisons and
the adapted Scout/Blender inspection distinguish surface coverage from missing
textures. Generated atlas artwork and game assets remain private/local.

### Correction: match the visual frequency of the surrounding game

Owner review found the generated atlas more detailed than the desired GTA:SA
vehicle style. Simplifying the actual diffuse content matters as well as reducing
resolution: use broad material shading, modest wear and fewer fine surface marks.
The revised imagegen-authored atlas converts to a 256x256 native raster with four
128x128 material regions and full mipmaps. This experiment is an aesthetic
approximation, not evidence that all stock vehicles use that resolution.

The follow-up replaces only the previously added auxiliary native texture.
Dictionary count, every original vehicle native texture and the entire mapped
DFF remain unchanged. Native pixel readback and archive preservation checks
passed, as did the two existing renderer regressions. The adapted GTA Scout
importer and Blender 4.5.3 produced a revised inspection view with no missing
texture bindings. Source was committed before local installation; no gameplay
or performance test ran. Game assets, generated artwork, private implementation
and local paths remain withheld.

### Correction: use actual component geometry instead of blanket rounding

Owner review rejected rounding every procedural fitting. A trial was discarded
without installation: different castings, plastic covers and brackets need their
own silhouettes. Actual GTA Scout local searches found no VQ35 engine model;
the lexical engine result was a junkyard texture. A local car blend's embedded
engine material faces proved to be another coarse placeholder. Scout discovers
and inspects supplied GTA assets; it does not reconstruct engine geometry from
photographs or directly import STL scans.

[JustTheOtherDave's OEM VQ35DE intake scan](https://www.printables.com/model/1057081-oem-vq35de-intake-plenum-nissan-350z-infiniti-g35),
updated October 31, 2024, provides actual lid, lower-plenum and runner geometry
under [CC BY-SA 4.0](https://creativecommons.org/licenses/by-sa/4.0/).
The author's scan is explicitly incomplete rather than a watertight printable
mesh. Public STL download controls and Blender 4.5.3 were used; source files were
hashed, welded and reduced to roughly 2200/1400/1600 triangles for the experiment.
Attribution and ShareAlike remain applicable to distributed adapted geometry.

Keep discovery, authoring and inspection distinct: import/reduce the real scan
in Blender, fit its separate scanner poses to the target bay, convert it into the
existing DFF, then inspect through the adapted Scout bridge. Shading averages
adjoining scan normals within a crease threshold, without rounding every fitting.
No exact factory assembly dimensions are claimed. Remove obsolete procedural
duplicates and recess central photographic backing that otherwise hides the
imported geometry; preserve photographed wiring and the bay perimeter.

Native readback checks preserve unrelated geometry, material chunks, frames,
collision and the texture dictionary. Culled top/oblique and closed-bonnet views
were produced, along with sampled bonnet clearance and two passing renderer
regressions. The imported intake is partial, not a complete scanned engine.
Gameplay, exact mating dimensions and performance remain unverified. Private
implementation, adapted assets and local paths are withheld.

### Negative result: authentic scan geometry can still form a wrong assembly

Owner review rejected the fitted intake experiment after local installation.
Static import, material resolution and preservation checks passed, but the
separately scaled lower components and retained procedural cover/banks did not
form a coherent engine. Authentic source geometry is not proof of correct
assembly, and an inspection tool does not certify proportions or connections.

A subsequent preview uses factory manual EM-15/17 and
[the intake manufacturer's stock-bay photos](https://topspeedauto.com/content/CF-NISSAN-350Z-INTAKE.pdf)
to establish part relationships. Keep the upper scan uniformly scaled, omit
unregistered lower scan poses, reduce the plastic cover's depth, angle cylinder
banks and connect the throttle/duct/sensor chain. The visible throttle opening
must be identified at the neck's outer plane; nearby bolt-hole boundary points
can produce a plausible but wrong fitted circle. Inspect the resulting joint
visually, in addition to reporting plane/circle residuals.

Blender 4.5.3 and the same adapted Scout importer produced a static preview with
resolved texture bindings. Native readback retained unrelated model data and
sampled bonnet clearance passed. The follow-up remains a preview, not installed
or gameplay-tested. Component dimensions remain estimates rather than factory
measurements. Private authoring source, assets and paths remain withheld.

### Whole-compartment art direction and comparison correctness

Owner review also rejected the core-only revision: an engine placed inside a
photographed surrounding bay remained visually inconsistent. A complete
compartment treatment should coordinate silhouettes, structure, connections
and surface art across the inner wings, towers, rear covers, cowl, engine,
cooling system and harnesses. A readable component-specific diffuse atlas is
more useful than arbitrary generic surface patches. Small details may be
painted deliberately; major forms still need appropriate geometry.

Native UV-to-world measurements exposed misplaced towers in the earlier
authored layout. Reuse the supplied bay as placement/boundary evidence, rather
than assuming that a plausible guessed arrangement is correct. Photographic
geometry can contain disconnected raised islands: an edge appearing only once
is not necessarily an exterior boundary. Recess obsolete interior islands so
they cannot cover newly modeled components.

The follow-up uses a built-in-imagegen 4x4 diffuse atlas converted to 512x512
with full native mipmaps, plus newly authored compartment geometry. Actual
Scout/Blender 4.5.3 oblique, top and closed inspection ran; original model
attributes, unrelated geometry, frames, collision and original native texture
chunks were checked. Sampled bonnet probes cover vertices and face centroids,
not exhaustive intersections. The candidate remains uninstalled and has no
gameplay verification; dimensional fidelity and visual acceptance remain open.

Two comparison pitfalls were corrected. Before and after models need their
own matching texture dictionaries when an auxiliary atlas changes. Also hash
inputs before import and again after rendering: hashing only after a render
can incorrectly label an old loaded scene with a newly written file's hash.
Authoring and inspection must not mutate their shared inputs concurrently.
Generated art, game assets and private implementation remain withheld.

The next owner review identified overlapping geometry and rejected wholly new
texture artwork in favor of reuse. The duplicate cowl ledge and fully interior
photo islands were removed; the intake duct and outer harness were rerouted
around the tower instead of through it. Closed inspection also located a
headlamp backing protruding through the bumper, resolved by recessing it.
These are observed, scoped corrections, not an exhaustive intersection proof.

The revised atlas repacks existing vehicle engine-cover, plenum, compartment
and cap pixels with stock mechanical, plastic and metal regions. Record each
source texture, dictionary checksum and crop rectangle, and inspect the crops
at native resolution: a nominal metal or radiator rectangle can accidentally
include neighboring atlas parts. No generated artwork is used in this revised
candidate. Original native texture chunks remain unchanged; only the auxiliary
atlas is replaced. The asset remains a static review candidate, uninstalled.

A subsequent close-up isolated another construction error: a clamp on an
angled intake was a capped cylinder aligned to a world axis, rather than a
band around the hose. Its offset cap produced a cut-looking crescent beside
the sensor. Derive collar centers and tangents from the duct centerline, use
hollow annular bands, and insert matching duct sections around each band.
This scoped geometry correction keeps the reused texture pixels unchanged.
Static Scout views and sampled clearance checks do not establish gameplay
or exhaustive assembly intersection correctness.

### Stock rotating engine accessories

Stock San Andreas donor inspection through GTA Scout and Blender 4.5.3 found
separate pulley atomics in Bandito, BF Injection and Hotknife. BF Injection's
`misc_a` and `misc_e` each have 78 triangles, a local Y shaft axis and
`vehiclegeneric256` texture binding. Bandito's `misc_e` has 40 triangles and
uses its own interior texture; its frame orientation differs. Inspect the
local mesh, frame rotation and parent chain before reusing a pivot. These
are observed geometry facts, not proof of a travelling belt animation.

The [SilentPatch documentation](https://silentsblog.com/mods/gta-sa/) identifies
animated engine components on these three vehicles. Its
[vehicle implementation](https://github.com/CookiePLMonster/SilentPatch/blob/master/SilentPatchSA/VehicleSA.cpp)
gates the engine component speed using engine-on state and the time step.
Animation is vehicle runtime behavior, not a reusable DFF animation clip;
copying a pulley mesh alone does not establish animation on another model.

[VehFuncs spinning-part documentation](https://github.com/JuniorDjjr/VehFuncs/wiki/%5BEN%5D-Spinning-parts)
defines `f_gear` for engine-on rotation that speeds up with the gas pedal,
`mu=` for a speed multiplier, and default Y rotation with X/Z overrides.
A local authoring experiment reused the two BF Injection meshes as separate
chassis-child parts, retained native UV/material chunks, replaced procedural
accessories and fitted a tangential belt strap. Static readback checked the
original frame prefix, unrelated geometry, native bindings and sampled
bonnet clearance across full rotations. Offline demonstration rotation is
not a gameplay test: the belt remains stationary and the dependency is absent
in the inspected target. No game launch, plugin installation or asset install
was performed. Runtime compatibility and owner acceptance remain open.

Scout source revision was `499ab20f625a90ef2ef3dc67bffc17589f522d59`.
The stock catalog source pass needed an explicit `--ide data/vehicles.ide`;
the first metadata pass using only GTA.dat did not expose donor vehicle rows.
The corrected catalog search found Bandito as `sa:model:568`. Stock archive
extraction and exact texture decoding supplied the three actual Scout static
renders. Authoring and render-only section/motion work are supporting steps,
not claims that Scout authors animation. Native asset payloads, rendered
game-derived images and private implementation are withheld.

### Independent engine assembly motion

VehFuncs is one implementation option, not a requirement. A native module can
animate a small authored rig directly. Separate the rigid engine assembly
from fixed body equipment, parent its pulleys and belt to the engine pivot,
and keep each shaft's own pivot. Fixed reservoirs, strut brace and body panels
must not inherit engine vibration. External hose connections need allowance
for movement; the reviewed experiment uses sub-millimetre translation and
small rocking hidden inside their joint overlap, not a skinned hose system.

The inspected x86 SA executable has SHA-256
`48e05d75fee714c192cfbaff6b3e19f63fa7414fd74bd42a43178bc0dc052eb3`.
Disk readback found automobile vtable VA `0x871120`, virtual slot 17 pointing
to `0x6AAB50`; [Plugin-SDK's entity wrapper](https://github.com/DK22Pac/plugin-sdk/blob/master/plugin_sa/game_sa/CEntity.cpp)
also identifies PreRender as slot 17. RenderWare frame declarations and
vehicle offsets were cross-checked using local Plugin-SDK revision
`15f15b60bbf74c106e1b496ff92c98764abf4605`, attributed to the GTA Community.
Unknown target layouts and modified hook slots are refused. This disk/SDK
verification and compilation do not establish live ABI compatibility.

Useful motion checks cover frame-rate independence, engine-off stop/rest,
pause, bounded vibration and independent angle wrapping on shafts of unequal
radius. Multiplying an already wrapped crank angle by a non-integer pulley
ratio causes the accessory angle to jump at each revolution; integrate and
wrap each angle separately. Rebuild matrices from the rest pose rather than
adding vibration repeatedly. Reacquire frame pointers and distinguish reused
vehicles/clumps; advance simulation once per game frame, not each render pass.
Visual speed driven by the gas pedal is not a measurement of physical RPM.

The native module compiled with MSVC x86, C++17, warnings as errors, and host
motion checks passed. The authoring pass added coil/fuel wiring, heater and
vacuum/EVAP lines, power/ground cables and cooling/fan connections, reusing the
existing diffuse pixels. [Nissan's factory EM manual](https://boredmder.com/FSMs/Nissan/350z/2003/EM.pdf)
was consulted for system presence, not a claim of surveyed coordinates.
Actual Scout/Blender static and offline motion inspection is distinct from
native execution. No game launch or gameplay verification was performed.
Private rig implementation, game payloads and native binaries are withheld.
