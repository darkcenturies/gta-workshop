#!/usr/bin/env python3
"""Read a GTA:SA ped out of a RenderWare .dff, weights and bone names included.

The existing readers (dff-read.py, dff-geometry.py) pull vertices and triangles,
which is enough to build collision. Fitting a ped to a reconstruction needs more:
UVs, normals, the skin section's per-vertex bone indices and weights, and the
name of the bone each index refers to.

That last part is the one that is easy to get wrong. A skin section's bone
indices do NOT index the frame list. They index the bone array of the root
frame's HAnim section, and each entry there carries a node ID. The name comes
from finding the frame whose own HAnim declares that same node ID:

    skin bone index  ->  root HAnim bone[i].node_id  ->  frame with that node_id
                                                     ->  that frame's name

Reading the indices as frame order instead produces plausible-looking nonsense,
which is why this is done explicitly here.

Usage:
    sarw.py <ped.dff> [...]
"""
from __future__ import annotations

import struct
import sys
from dataclasses import dataclass, field

CLUMP = 0x0010
STRUCT = 0x0001
EXTENSION = 0x0003
FRAME_LIST = 0x000E
GEOMETRY_LIST = 0x001A
GEOMETRY = 0x000F
MATERIAL_LIST = 0x0008
MATERIAL = 0x0007
TEXTURE = 0x0006
STRING = 0x0002
HANIM_PLG = 0x011E
SKIN_PLG = 0x0116
FRAME_NAME = 0x253F2FE

FLAG_TRISTRIP = 0x0001
FLAG_POSITIONS = 0x0002
FLAG_TEXTURED = 0x0004
FLAG_PRELIT = 0x0008
FLAG_NORMALS = 0x0010
FLAG_TEXTURED2 = 0x0080


def chunks(data, start, end):
    pos = start
    while pos + 12 <= end:
        cid, size, ver = struct.unpack_from("<III", data, pos)
        body = pos + 12
        if body + size > end:
            return
        yield cid, body, body + size, ver
        pos = body + size


def first(data, start, end, wanted):
    for cid, body, tail, ver in chunks(data, start, end):
        if cid == wanted:
            return body, tail, ver
    return None, None, None


@dataclass
class Bone:
    index: int
    node_id: int
    flags: int
    name: str = ""
    frame: int = -1
    parent: int = -1


@dataclass
class Ped:
    path: str = ""
    version: int = 0
    raw: bytes = b""
    vertices: list = field(default_factory=list)
    normals: list = field(default_factory=list)
    uvs: list = field(default_factory=list)
    triangles: list = field(default_factory=list)
    tri_materials: list = field(default_factory=list)
    textures: list = field(default_factory=list)
    bones: list = field(default_factory=list)
    frame_names: list = field(default_factory=list)
    frame_parents: list = field(default_factory=list)
    frame_local: list = field(default_factory=list)
    frame_world: list = field(default_factory=list)
    skin_indices: list = field(default_factory=list)
    skin_weights: list = field(default_factory=list)
    max_influences: int = 0
    bones_used: int = 0
    skin_to_bone: list = field(default_factory=list)
    vertex_offset: int = -1
    normal_offset: int = -1
    sphere_offset: int = -1

    @property
    def bone_names(self) -> list:
        return [b.name for b in self.bones]

    def dominant_bone(self, vertex: int) -> int:
        w = self.skin_weights[vertex]
        return self.skin_indices[vertex][w.index(max(w))]

    def bone_origins(self) -> dict:
        """Where each bone sits in the same space the vertices are in.

        Inverting the skin-to-bone matrix and taking its translation. This is
        the measurement bone_rest_positions cannot give: that one reads the
        frame hierarchy, which a skinned mesh does not sit in.
        """
        out = {}
        for i, m in enumerate(self.skin_to_bone):
            if i >= len(self.bones):
                break
            # Rotation is orthonormal, so the inverse translation is
            # -R^T * t without needing a general inverse.
            r = (m[0], m[1], m[2], m[4], m[5], m[6], m[8], m[9], m[10])
            t = (m[12], m[13], m[14])
            out[self.bones[i].node_id] = (
                -(r[0] * t[0] + r[3] * t[1] + r[6] * t[2]),
                -(r[1] * t[0] + r[4] * t[1] + r[7] * t[2]),
                -(r[2] * t[0] + r[5] * t[1] + r[8] * t[2]),
            )
        return out

    def bone_rest_positions(self) -> dict:
        """World-space rest position of every named bone, in ped coordinates."""
        out = {}
        for b in self.bones:
            if 0 <= b.frame < len(self.frame_world):
                m = self.frame_world[b.frame]
                out[b.name] = (m[9], m[10], m[11])
        return out

    def patch_vertices(self, vertices, normals=None) -> bytes:
        """Return the original DFF bytes with new vertex positions written in.

        Topology, UVs, materials, the skin section and the skeleton are all left
        exactly as they were, so the result is a valid ped by construction. Only
        the position block, the normal block and the bounding sphere change.
        """
        if len(vertices) != len(self.vertices):
            raise ValueError(
                f"expected {len(self.vertices)} vertices, got {len(vertices)}"
            )
        data = bytearray(self.raw)
        for i, v in enumerate(vertices):
            struct.pack_into("<fff", data, self.vertex_offset + i * 12,
                             float(v[0]), float(v[1]), float(v[2]))
        if normals is not None and self.normal_offset >= 0:
            if len(normals) != len(self.vertices):
                raise ValueError("normal count does not match vertex count")
            for i, n in enumerate(normals):
                struct.pack_into("<fff", data, self.normal_offset + i * 12,
                                 float(n[0]), float(n[1]), float(n[2]))
        if self.sphere_offset >= 0:
            cx = sum(v[0] for v in vertices) / len(vertices)
            cy = sum(v[1] for v in vertices) / len(vertices)
            cz = sum(v[2] for v in vertices) / len(vertices)
            r = max(((v[0] - cx) ** 2 + (v[1] - cy) ** 2 + (v[2] - cz) ** 2) ** 0.5
                    for v in vertices)
            struct.pack_into("<ffff", data, self.sphere_offset, cx, cy, cz, r)
        return bytes(data)


def _read_frame_list(data, body, tail):
    """Frame names in order, their parents, and each frame's HAnim node id."""
    sbody, stail, _ = first(data, body, tail, STRUCT)
    count = struct.unpack_from("<I", data, sbody)[0]
    parents = []
    local = []
    p = sbody + 4
    for _ in range(count):
        # 3x3 rotation (row major), position, parent index, matrix flags
        m = struct.unpack_from("<12f", data, p)
        parent = struct.unpack_from("<i", data, p + 48)[0]
        parents.append(parent)
        local.append(m)
        p += 56
    names = []
    node_ids = []
    seen = 0
    for cid, ebody, etail, ver in chunks(data, body, tail):
        if cid != EXTENSION:
            continue
        name = ""
        node_id = -1
        for c2, b2, t2, v2 in chunks(data, ebody, etail):
            if c2 == FRAME_NAME:
                name = data[b2:t2].split(b"\0")[0].decode("latin-1", "replace").strip()
            elif c2 == HANIM_PLG:
                _ver, nid, nnodes = struct.unpack_from("<III", data, b2)
                node_id = nid
        names.append(name)
        node_ids.append(node_id)
        seen += 1
        if seen >= count:
            break
    while len(names) < count:
        names.append("")
        node_ids.append(-1)
    return names, parents, node_ids, local


def _compose(parent, child):
    """parent * child, for the 3x3-plus-translation layout stored in a frame."""
    pr, pt = parent[:9], parent[9:]
    cr, ct = child[:9], child[9:]
    out = []
    for r in range(3):
        for c in range(3):
            out.append(sum(cr[r * 3 + k] * pr[k * 3 + c] for k in range(3)))
    for c in range(3):
        out.append(sum(ct[k] * pr[k * 3 + c] for k in range(3)) + pt[c])
    return tuple(out)


def _world_frames(local, parents):
    world = [None] * len(local)

    def resolve(i):
        if world[i] is not None:
            return world[i]
        par = parents[i]
        if par < 0 or par >= len(local) or par == i:
            world[i] = local[i]
        else:
            world[i] = _compose(resolve(par), local[i])
        return world[i]

    for i in range(len(local)):
        resolve(i)
    return world


def _read_root_hanim(data, body, tail):
    """The ordered bone array the skin section's indices refer to."""
    for cid, ebody, etail, ver in chunks(data, body, tail):
        if cid != EXTENSION:
            continue
        for c2, b2, t2, v2 in chunks(data, ebody, etail):
            if c2 != HANIM_PLG:
                continue
            _ver, node_id, num_nodes = struct.unpack_from("<III", data, b2)
            if num_nodes == 0:
                continue
            p = b2 + 12 + 8  # skip flags and keyframe size
            bones = []
            for i in range(num_nodes):
                nid, nindex, flags = struct.unpack_from("<III", data, p + i * 12)
                bones.append(Bone(index=i, node_id=nid, flags=flags))
            return bones
    return []


def _read_materials(data, body, tail):
    names = []
    mbody, mtail, _ = first(data, body, tail, MATERIAL_LIST)
    if mbody is None:
        return names
    for cid, b, t, ver in chunks(data, mbody, mtail):
        if cid != MATERIAL:
            continue
        texname = ""
        for c2, b2, t2, v2 in chunks(data, b, t):
            if c2 != TEXTURE:
                continue
            got = []
            for c3, b3, t3, v3 in chunks(data, b2, t2):
                if c3 == STRING:
                    got.append(data[b3:t3].split(b"\0")[0].decode("latin-1", "replace"))
            if got:
                texname = got[0]
        names.append(texname)
    return names


def _read_geometry(data, body, tail, ped):
    sbody, stail, ver = first(data, body, tail, STRUCT)
    p = sbody
    flags, num_uv, native = struct.unpack_from("<HBB", data, p)
    p += 4
    num_tris, num_verts, num_morphs = struct.unpack_from("<III", data, p)
    p += 12
    if ver < 0x34000:
        p += 12
    if flags & FLAG_PRELIT:
        p += 4 * num_verts
    sets = max(1, num_uv) if (flags & (FLAG_TEXTURED | FLAG_TEXTURED2) or num_uv) else 0
    if sets:
        for i in range(num_verts):
            u, v = struct.unpack_from("<ff", data, p + i * 8)
            ped.uvs.append((u, v))
        p += 8 * num_verts * sets
    for i in range(num_tris):
        b, a, mat, c = struct.unpack_from("<HHHH", data, p + i * 8)
        ped.triangles.append((a, b, c))
        ped.tri_materials.append(mat)
    p += 8 * num_tris
    ped.sphere_offset = p
    p += 16  # bounding sphere
    has_verts, has_normals = struct.unpack_from("<II", data, p)
    p += 8
    if has_verts:
        ped.vertex_offset = p
        for i in range(num_verts):
            ped.vertices.append(struct.unpack_from("<fff", data, p + i * 12))
        p += 12 * num_verts
    if has_normals:
        ped.normal_offset = p
        for i in range(num_verts):
            ped.normals.append(struct.unpack_from("<fff", data, p + i * 12))
        p += 12 * num_verts

    ped.textures = _read_materials(data, body, tail)

    for cid, ebody, etail, v in chunks(data, body, tail):
        if cid != EXTENSION:
            continue
        for c2, b2, t2, v2 in chunks(data, ebody, etail):
            if c2 != SKIN_PLG:
                continue
            num_bones, used, max_w, pad = struct.unpack_from("<BBBB", data, b2)
            ped.bones_used = used
            ped.max_influences = max_w
            q = b2 + 4 + used
            for i in range(num_verts):
                ped.skin_indices.append(list(struct.unpack_from("<4B", data, q + i * 4)))
            q += num_verts * 4
            for i in range(num_verts):
                ped.skin_weights.append(list(struct.unpack_from("<4f", data, q + i * 16)))
            q += num_verts * 16
            # The skin-to-bone matrices, one per bone, 4x4 column-major. These
            # are what put a bone and the vertices it drives into the same
            # space: a skinned mesh's vertices are NOT in the frame hierarchy's
            # rest pose, so measuring a bone against frame_world gives answers
            # that look plausible and are wrong - a toe a metre and a half from
            # its own vertices.
            for i in range(num_bones):
                m = struct.unpack_from("<16f", data, q + i * 64)
                ped.skin_to_bone.append(list(m))
    return ped


def read_ped(path) -> Ped:
    data = open(path, "rb").read()
    ped = Ped(path=str(path), raw=data)
    cbody, ctail, cver = first(data, 0, len(data), CLUMP)
    if cbody is None:
        raise RuntimeError(f"{path}: no clump")
    ped.version = cver

    fbody, ftail, _ = first(data, cbody, ctail, FRAME_LIST)
    names, parents, node_ids, local = _read_frame_list(data, fbody, ftail)
    ped.frame_names = names
    ped.frame_parents = parents
    ped.frame_local = local
    ped.frame_world = _world_frames(local, parents)

    bones = _read_root_hanim(data, fbody, ftail)
    by_node = {}
    for i, nid in enumerate(node_ids):
        if nid >= 0 and nid not in by_node:
            by_node[nid] = i
    for b in bones:
        frame = by_node.get(b.node_id, -1)
        b.frame = frame
        b.name = names[frame] if frame >= 0 else f"<node {b.node_id}>"
        b.parent = parents[frame] if frame >= 0 else -1
    ped.bones = bones

    gbody, gtail, _ = first(data, cbody, ctail, GEOMETRY_LIST)
    if gbody is None:
        raise RuntimeError(f"{path}: no geometry list")
    geo_body, geo_tail, geo_ver = first(data, gbody, gtail, GEOMETRY)
    if geo_body is None:
        raise RuntimeError(f"{path}: no geometry")
    _read_geometry(data, geo_body, geo_tail, ped)
    return ped


def _report(path):
    ped = read_ped(path)
    xs = [v[0] for v in ped.vertices]
    ys = [v[1] for v in ped.vertices]
    zs = [v[2] for v in ped.vertices]
    print(f"{path}")
    print(f"  rw {hex(ped.version)}  {len(ped.vertices)} verts  {len(ped.triangles)} tris  "
          f"{len(ped.uvs)} uvs  normals={'yes' if ped.normals else 'no'}")
    print(f"  bounds X[{min(xs):.2f}..{max(xs):.2f}] Y[{min(ys):.2f}..{max(ys):.2f}] "
          f"Z[{min(zs):.2f}..{max(zs):.2f}]")
    print(f"  textures {ped.textures}")
    print(f"  bones {len(ped.bones)}  used {ped.bones_used}  max influences {ped.max_influences}")
    if ped.skin_weights:
        groups = {}
        for i in range(len(ped.vertices)):
            groups.setdefault(ped.dominant_bone(i), []).append(i)
        names = ped.bone_names
        print("  dominant-bone vertex counts:")
        for k in sorted(groups, key=lambda k: -len(groups[k])):
            nm = names[k] if k < len(names) else f"?{k}"
            us = [ped.uvs[i][0] * 128 for i in groups[k]] if ped.uvs else [0]
            vs = [ped.uvs[i][1] * 256 for i in groups[k]] if ped.uvs else [0]
            print(f"    {nm:<18} {len(groups[k]):4d}   uv px "
                  f"u {min(us):5.0f}..{max(us):5.0f}  v {min(vs):5.0f}..{max(vs):5.0f}")


if __name__ == "__main__":
    for arg in sys.argv[1:]:
        _report(arg)
