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
