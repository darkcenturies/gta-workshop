"""Convert a character GLB into a GTA:SA ped, keeping the character's own mesh.

This is the counterpart to build_scallion_sa_skin.py, for sources that arrive as
a plain multi-part GLB rather than a GTA V asset: no Sollumz, no GTA V skeleton
to collapse, and no rig on the source at all.

The earlier attempt went the other way round - it kept a stock ped's body and
only repainted it. That produces a valid file but never looks like the
character, because the stock ped's clothing is not shaped like theirs and every
texel ends up sampling whatever garment happens to be nearest. Here the
character's own geometry is kept and reduced, and the rig is what gets
borrowed:

  1. Import a stock ped for its 32-bone armature and its skin weights.
  2. Import the character, join the parts, and put them in the ped's space.
  3. Reduce to a stock-sized triangle budget.
  4. Unwrap into a single atlas, since a ped has exactly one texture.
  5. Transfer weights from the stock ped onto the reduced character mesh.
     Weights vary smoothly over a body, so nearest-surface transfer is well
     behaved here in a way that colour transfer was not.
  6. Cap influences at four per vertex, which is what stock peds use.
  7. Export a 0x36003 DFF against the borrowed armature.

The texture is baked outside Blender, against the untouched GLB, once this has
produced the reduced mesh and its UV layout.

Run:
    blender --background --factory-startup --python build_ped_from_glb_blender.py -- \
        <glb> <donor.dff> <out.dff> <out.blend> <triangle budget> <texture name>
"""
import sys
import traceback

import bpy
import bmesh
from mathutils import Vector

HAND_BONES = {"L Hand", "R Hand", "L Finger", "R Finger", "L Finger01", "R Finger01"}
MAX_INFLUENCES = 4


def log(msg):
    print(msg, flush=True)


def enable_dragonff():
    """--factory-startup leaves add-ons off, and read_factory_settings resets
    preferences again, so the order here matters."""
    bpy.ops.wm.read_factory_settings(use_empty=True)
    for name in ("DragonFF", "dragonff", "bl_ext.user_default.DragonFF"):
        try:
            bpy.ops.preferences.addon_enable(module=name)
            log(f"DragonFF enabled as {name!r}")
            return
        except Exception:
            continue
    raise RuntimeError("DragonFF add-on is not installed")


def import_donor(path):
    before = set(bpy.data.objects)
    bpy.ops.import_scene.dff(filepath=path)
    added = [o for o in bpy.data.objects if o not in before]
    mesh = next((o for o in added if o.type == "MESH"), None)
    arm = next((o for o in added if o.type == "ARMATURE"), None)
    if mesh is None or arm is None:
        raise RuntimeError("donor ped did not import as a mesh plus armature")
    log(f"donor: {len(mesh.data.vertices)} verts, {len(mesh.data.polygons)} faces, "
        f"{len(arm.data.bones)} bones, {len(mesh.vertex_groups)} groups")
    return mesh, arm


def import_glb(path):
    before = set(bpy.data.objects)
    bpy.ops.import_scene.gltf(filepath=path)
    added = [o for o in bpy.data.objects if o not in before and o.type == "MESH"]
    if not added:
        raise RuntimeError("the GLB contained no meshes")
    log(f"source: {len(added)} parts")

    # Part names are the only reliable orientation landmarks, and joining
    # destroys them, so take the measurements first.
    marks = {}
    for o in added:
        pts = [o.matrix_world @ v.co for v in o.data.vertices]
        if not pts:
            continue
        c = sum(pts, Vector((0, 0, 0))) / len(pts)
        marks[o.name] = c

    for o in bpy.data.objects:
        o.select_set(False)
    for o in added:
        o.select_set(True)
    bpy.context.view_layer.objects.active = added[0]
    bpy.ops.object.join()
    joined = bpy.context.view_layer.objects.active
    bpy.ops.object.transform_apply(location=True, rotation=True, scale=True)
    log(f"joined: {len(joined.data.vertices)} verts, {len(joined.data.polygons)} faces, "
        f"{len(joined.data.materials)} materials")
    return joined, marks


def world_bounds(obj):
    lo = Vector((1e9, 1e9, 1e9))
    hi = Vector((-1e9, -1e9, -1e9))
    for corner in obj.bound_box:
        p = obj.matrix_world @ Vector(corner)
        for i in range(3):
            lo[i] = min(lo[i], p[i])
            hi[i] = max(hi[i], p[i])
    return lo, hi


def _pick(marks, *keys):
    hits = [c for n, c in marks.items()
            if any(k.lower() in n.lower() for k in keys)]
    if not hits:
        return None
    return sum(hits, Vector((0, 0, 0))) / len(hits)


def _side(marks, letter):
    hits = []
    for n, c in marks.items():
        segs = n.split("_")
        if letter in segs or any(s.startswith(letter) and s[1:].isdigit() for s in segs):
            hits.append(c)
    if not hits:
        return None
    return sum(hits, Vector((0, 0, 0))) / len(hits)


def _bone(arm, name):
    for b in arm.data.bones:
        if b.name.strip() == name:
            return arm.matrix_world @ b.head_local
    return None


def align_to_donor(src, arm, marks):
    """Match the source to the ped's skeleton, not to a bounding box.

    DragonFF leaves a ped on its own axes, which are not Blender's, and the
    glTF importer rotates the source onto yet another set. Comparing bounding
    boxes therefore compares different axes and silently mis-scales. Two real
    directions - up the spine, and across the shoulders - pin the orientation
    down without any assumption about which axis is which.
    """
    d_pelvis = _bone(arm, "Pelvis")
    d_head = _bone(arm, "Head")
    d_lhand = _bone(arm, "L Hand")
    d_rhand = _bone(arm, "R Hand")
    d_foot = _bone(arm, "L Foot")
    if None in (d_pelvis, d_head, d_lhand, d_rhand, d_foot):
        raise RuntimeError("donor armature is missing the bones needed to align")

    s_head = _pick(marks, "head_face", "head_skin_shell", "nose")
    s_lhand = _side(marks, "L") if _side(marks, "L") else None
    s_rhand = _side(marks, "R") if _side(marks, "R") else None
    s_lhand = _pick(marks, "hand_L") or s_lhand
    s_rhand = _pick(marks, "hand_R") or s_rhand
    s_foot = _pick(marks, "foot", "sole", "boot")
    if None in (s_head, s_lhand, s_rhand, s_foot):
        raise RuntimeError("could not find head/hand/foot landmarks in the GLB part names")

    d_up = (d_head - d_foot).normalized()
    d_left = (d_lhand - d_rhand).normalized()
    s_up = (s_head - s_foot).normalized()
    s_left = (s_lhand - s_rhand).normalized()

    def basis(up, left):
        u = up.normalized()
        l = (left - u * left.dot(u)).normalized()
        f = u.cross(l)
        return u, l, f

    du, dl, df = basis(d_up, d_left)
    su, sl, sf = basis(s_up, s_left)
    from mathutils import Matrix
    D = Matrix((du, dl, df)).transposed()
    S = Matrix((su, sl, sf)).transposed()
    R = D @ S.inverted()

    # Both models are authored upright and axis aligned, so the transform
    # between them can only be a signed axis permutation. The landmarks are not
    # precise enough to give that exactly - a donor "up" taken from the head to
    # one foot leans sideways, and a face centroid sits forward of the centre
    # line - and the few degrees of residual tilt convert height into depth,
    # which showed up as a character 27% too deep front to back. Snapping the
    # rotation to the nearest permutation removes the tilt without discarding
    # what the landmarks correctly established, which is the ordering and the
    # signs.
    snapped = Matrix.Identity(3)
    used = set()
    for col in range(3):
        v = R.col[col]
        order = sorted(range(3), key=lambda r: -abs(v[r]))
        row = next(r for r in order if r not in used)
        used.add(row)
        for r in range(3):
            snapped[r][col] = 0.0
        snapped[row][col] = 1.0 if v[row] >= 0 else -1.0
    # A signed permutation can just as easily be a reflection as a rotation,
    # and a reflection mirrors the character - left hand on the right, and the
    # whole model handed the wrong way round. Force a proper rotation by
    # flipping whichever axis the landmarks were least sure about.
    if snapped.determinant() < 0:
        weakest = min(range(3), key=lambda c: max(abs(R[r][c]) for r in range(3)))
        for r in range(3):
            snapped[r][weakest] = -snapped[r][weakest]
        log("align: permutation was a reflection; flipped an axis to keep it a rotation")
    drift = max(abs(R[r][c] - snapped[r][c]) for r in range(3) for c in range(3))
    log(f"align: snapped the rotation to an axis permutation "
        f"(largest change {drift:.3f}, determinant {snapped.determinant():+.0f})")
    R = snapped

    d_len = (d_head - d_foot).length
    s_len = (s_head - s_foot).length
    scale = d_len / s_len if s_len > 0 else 1.0
    log(f"align: head-to-foot source {s_len:.3f} -> donor {d_len:.3f} (scale {scale:.4f})")

    bpy.ops.object.select_all(action="DESELECT")
    src.select_set(True)
    bpy.context.view_layer.objects.active = src
    M = Matrix.Diagonal((scale, scale, scale)).to_4x4() @ R.to_4x4()
    src.matrix_world = M @ src.matrix_world
    bpy.ops.object.transform_apply(location=True, rotation=True, scale=True)

    # Sit the reoriented source on the donor's own pelvis and foot line.
    pts = [src.matrix_world @ v.co for v in src.data.vertices]
    s_foot_now = min(p.dot(du) for p in pts)
    d_foot_now = d_foot.dot(du)
    centre = sum(pts, Vector((0, 0, 0))) / len(pts)
    offset = du * (d_foot_now - s_foot_now)
    offset += dl * (d_pelvis.dot(dl) - centre.dot(dl))
    offset += df * (d_pelvis.dot(df) - centre.dot(df))
    src.location = src.location + offset
    bpy.ops.object.transform_apply(location=True)

    pts = [src.matrix_world @ v.co for v in src.data.vertices]
    log(f"align: along the spine source spans "
        f"{min(p.dot(du) for p in pts):.3f}..{max(p.dot(du) for p in pts):.3f}, "
        f"donor foot {d_foot.dot(du):.3f} head {d_head.dot(du):.3f}")


def triangle_count(obj):
    me = obj.data
    return sum(len(p.vertices) - 2 for p in me.polygons)


def decimate(obj, budget):
    bpy.ops.object.select_all(action="DESELECT")
    obj.select_set(True)
    bpy.context.view_layer.objects.active = obj

    # Weld first: joined parts meet at coincident but unshared vertices, and
    # collapse decimation cannot cross those seams, so islands survive at full
    # density and the budget is spent in the wrong places.
    bm = bmesh.new()
    bm.from_mesh(obj.data)
    bmesh.ops.remove_doubles(bm, verts=bm.verts, dist=1e-5)
    bm.to_mesh(obj.data)
    bm.free()
    obj.data.update()
    bpy.ops.object.mode_set(mode="OBJECT")
    bpy.ops.object.modifier_add(type="TRIANGULATE")
    bpy.ops.object.modifier_apply(modifier=obj.modifiers[-1].name)

    before = triangle_count(obj)
    log(f"welded and triangulated: {before} triangles")
    if before <= budget:
        log("already inside budget, not decimating")
        return
    mod = obj.modifiers.new(name="Decimate", type="DECIMATE")
    mod.decimate_type = "COLLAPSE"
    mod.ratio = budget / before
    mod.use_collapse_triangulate = True
    bpy.ops.object.modifier_apply(modifier=mod.name)
    log(f"decimated: {triangle_count(obj)} triangles (target {budget})")


def unwrap(obj, texture_name):
    bpy.ops.object.select_all(action="DESELECT")
    obj.select_set(True)
    bpy.context.view_layer.objects.active = obj

    # One ped, one texture: every part collapses onto a single material whose
    # texture is named after the donor, so the patched TXD still matches.
    obj.data.materials.clear()
    mat = bpy.data.materials.new(name=texture_name)
    mat.use_nodes = True
    # DragonFF writes the DFF's texture reference from an image node, so the
    # material needs a real image whose name matches the one inside the TXD.
    # Without it the ped exports with an empty texture name and renders
    # untextured in game.
    img = bpy.data.images.new(texture_name, width=128, height=256)
    img.name = texture_name
    node = mat.node_tree.nodes.new("ShaderNodeTexImage")
    node.image = img
    bsdf = mat.node_tree.nodes.get("Principled BSDF")
    if bsdf is not None:
        mat.node_tree.links.new(node.outputs["Color"], bsdf.inputs["Base Color"])
    obj.data.materials.append(mat)
    for poly in obj.data.polygons:
        poly.material_index = 0

    while len(obj.data.uv_layers) > 1:
        obj.data.uv_layers.remove(obj.data.uv_layers[-1])
    if not obj.data.uv_layers:
        obj.data.uv_layers.new(name="Float2")
    obj.data.uv_layers[0].name = "Float2"

    bpy.ops.object.mode_set(mode="EDIT")
    bpy.ops.mesh.select_all(action="SELECT")
    bpy.ops.uv.select_all(action="SELECT")

    # Repack the source's own islands rather than unwrapping from scratch.
    # The character was authored with a real face layout, a sleeve layout and
    # so on; a fresh automatic unwrap throws all of that away and shreds the
    # face across a dozen small charts, which at 128x256 leaves nothing
    # readable. Packing keeps each authored island whole and only moves it.
    try:
        bpy.ops.uv.pack_islands(rotate=True, margin=0.004, scale=True)
    except TypeError:
        bpy.ops.uv.pack_islands(rotate=True, margin=0.004)
    bpy.ops.object.mode_set(mode="OBJECT")

    # DragonFF splits a vertex whenever position, normal or UV differ. A
    # flat-shaded mesh therefore exports three vertices per triangle, tripling
    # the vertex count over a stock ped for no visual gain.
    for poly in obj.data.polygons:
        poly.use_smooth = True
    obj.data.update()
    log("packed the source's own UV islands into one atlas, smooth shaded")


def transfer_weights(src, donor, arm):
    """Take the donor's vertex groups across by nearest surface."""
    for group in donor.vertex_groups:
        if group.name not in src.vertex_groups:
            src.vertex_groups.new(name=group.name)

    bpy.ops.object.select_all(action="DESELECT")
    donor.select_set(True)
    src.select_set(True)
    bpy.context.view_layer.objects.active = src

    mod = src.modifiers.new(name="WeightTransfer", type="DATA_TRANSFER")
    mod.object = donor
    mod.use_vert_data = True
    mod.data_types_verts = {"VGROUP_WEIGHTS"}
    mod.vert_mapping = "POLYINTERP_NEAREST"
    bpy.ops.object.datalayout_transfer(modifier=mod.name)
    bpy.ops.object.modifier_apply(modifier=mod.name)
    log("weights transferred from the donor ped")


def clean_weights(obj):
    """Cap influences and renormalise, the way stock peds are built."""
    stripped = 0
    for v in obj.data.vertices:
        entries = [(g.group, g.weight) for g in v.groups if g.weight > 0.0]
        entries.sort(key=lambda e: -e[1])
        keep = entries[:MAX_INFLUENCES]
        drop = entries[MAX_INFLUENCES:]
        if drop:
            stripped += 1
        total = sum(w for _, w in keep)
        for gi, _w in drop:
            obj.vertex_groups[gi].remove([v.index])
        if total <= 0.0:
            continue
        for gi, w in keep:
            obj.vertex_groups[gi].add([v.index], w / total, "REPLACE")
    log(f"influences capped at {MAX_INFLUENCES} ({stripped} vertices trimmed)")

    unweighted = [v.index for v in obj.data.vertices
                  if not any(g.weight > 0 for g in v.groups)]
    if unweighted:
        log(f"WARNING: {len(unweighted)} vertices carry no weight and will collapse")
    return len(unweighted)


def main():
    argv = sys.argv[sys.argv.index("--") + 1:]
    glb, donor_dff, out_dff, out_blend, budget_s, texture_name = argv[:6]
    budget = int(budget_s)

    enable_dragonff()
    donor, arm = import_donor(donor_dff)
    src, marks = import_glb(glb)
    align_to_donor(src, arm, marks)
    decimate(src, budget)
    unwrap(src, texture_name)
    transfer_weights(src, donor, arm)
    unweighted = clean_weights(src)

    # Bind to the borrowed skeleton and drop the donor's own body.
    mod = src.modifiers.new(name="Armature", type="ARMATURE")
    mod.object = arm
    src.parent = arm
    bpy.data.objects.remove(donor, do_unlink=True)
    src.name = "mesh"

    bpy.ops.object.select_all(action="DESELECT")
    src.select_set(True)
    arm.select_set(True)
    bpy.context.view_layer.objects.active = src

    try:
        bpy.ops.export_dff.scene(filepath=out_dff, export_version="0x36003")
    except TypeError:
        bpy.ops.export_dff.scene(filepath=out_dff)
    log(f"exported {out_dff}")
    bpy.ops.wm.save_as_mainfile(filepath=out_blend)
    log(f"saved {out_blend}")
    log(f"RESULT triangles={triangle_count(src)} unweighted={unweighted}")
    log("BUILD OK")


if __name__ == "__main__":
    try:
        main()
    except Exception:
        traceback.print_exc()
        print("BUILD FAILED", flush=True)
        sys.exit(2)
