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
