"""Bounding sphere per model, for naming what you clicked on the 3D map.

    world3d-bounds.py GAME_DIR OUT.json

world3d-objects.py sizes each object from its .ide draw distance, which only
roughly tracks how big the thing is: a small object with a long draw distance
claims far more space than it fills, and clicks land on the wrong model.

Every RenderWare model already carries a real bounding sphere, written into the
first morph target of each geometry. This reads that and nothing else - it walks
the geometry header far enough to know where the sphere sits and seeks straight
to it, skipping the triangle and vertex arrays entirely, which is what makes
doing this for every model in the world reasonable.

The radius written out is measured from the model's own origin, because that is
the point an .ipl places:

    reach = |sphere centre| + sphere radius

Output is {"models": {"name": [reach, cx, cy, cz, hx, hy, hz], ...}} - the reach
used for picking, then the centre and half extents of the real box, used to draw
an outline that fits the model instead of a cube around it. Models whose
vertices could not be read carry the reach alone.

Run it on Windows, against the game install.
"""

import json
import os

import numpy as np
import struct
import sys

SECTOR = 2048
CHUNK_STRUCT = 0x01
CHUNK_GEOMETRY = 0x0F
FLAG_TEXTURED = 0x04
FLAG_PRELIT = 0x08


def chunks(data, start, end):
    """Walk one level of the RenderWare chunk tree."""
    at = start
    while at + 12 <= end:
        cid, size, _ver = struct.unpack_from("<III", data, at)
        body = at + 12
        tail = body + size
        if tail > end:
            return
        yield cid, body, tail
        at = tail


def find(data, start, end, wanted, depth=0):
    """Every chunk of one type, at any depth."""
    if depth > 6:
        return
    for cid, body, tail in chunks(data, start, end):
        if cid == wanted:
            yield body, tail
        else:
            yield from find(data, body, tail, wanted, depth + 1)


def geometry_bounds(data, body, tail):
    """(sphere, box) for one geometry, either of which may be None.

    The box is the real extent of the vertices, which is what an outline drawn
    around the model has to match. The sphere is kept because picking tests
    against a sphere and a sphere is cheaper to test."""
    for cid, sbody, stail in chunks(data, body, tail):
        if cid != CHUNK_STRUCT:
            continue
        try:
            p = sbody
            flags, num_uv, _native = struct.unpack_from("<HBB", data, p)
            p += 4
            num_tris, num_verts, _num_morphs = struct.unpack_from("<III", data, p)
            p += 12

            # Older files carry lighting values before the arrays.
            version = struct.unpack_from("<I", data, body - 4)[0]
            if version < 0x34000:
                p += 12

            if flags & FLAG_PRELIT:
                p += 4 * num_verts
            if flags & FLAG_TEXTURED or num_uv:
                p += 8 * num_verts * max(1, num_uv)
            p += num_tris * 8

            if p + 16 > stail:
                return None, None
            cx, cy, cz, r = struct.unpack_from("<ffff", data, p)
            p += 16

            # The morph target's own flags, then the vertices themselves.
            has_verts, _has_normals = struct.unpack_from("<II", data, p)
            p += 8

            box = None
            if has_verts and num_verts and p + num_verts * 12 <= stail:
                verts = np.frombuffer(data, dtype="<f4",
                                      count=num_verts * 3, offset=p).reshape(-1, 3)
                if verts.size and np.isfinite(verts).all():
                    box = (verts.min(axis=0), verts.max(axis=0))
        except (struct.error, ValueError):
            return None, None

        sphere = None
        if r > 0 and r == r:                      # not zero, not a NaN
            sphere = (cx, cy, cz, r)
        return sphere, box
    return None, None


def model_shape(data):
    """(reach, centre, half extents) for a whole model, over every geometry."""
    reach = 0.0
    lo = hi = None
    for gbody, gtail in find(data, 0, len(data), CHUNK_GEOMETRY):
        sphere, box = geometry_bounds(data, gbody, gtail)
        if sphere:
            cx, cy, cz, r = sphere
            reach = max(reach, (cx * cx + cy * cy + cz * cz) ** 0.5 + r)
        if box:
            lo = box[0] if lo is None else np.minimum(lo, box[0])
            hi = box[1] if hi is None else np.maximum(hi, box[1])

    if lo is None:
        return reach, None, None
    centre = (lo + hi) / 2.0
    half = (hi - lo) / 2.0
    # A flat panel has no thickness at all; give it enough to be drawn.
    half = np.maximum(half, 0.05)
    if not reach:
        reach = float(np.linalg.norm(np.abs(centre) + half))
    return reach, centre, half


def img_entries(path):
    """Name -> (offset, length) for one VER2 archive."""
    out = {}
    try:
        with open(path, "rb") as f:
            head = f.read(8)
            if head[:4] != b"VER2":
                return out
            count = struct.unpack_from("<I", head, 4)[0]
            table = f.read(count * 32)
    except OSError:
        return out

    for i in range(count):
        at = i * 32
        if at + 32 > len(table):
            break
        offset, streaming, size = struct.unpack_from("<IHH", table, at)
        name = table[at + 8:at + 32].split(b"\0")[0].decode("latin-1").lower()
        if name.endswith(".dff"):
            out[name] = (offset * SECTOR, (streaming or size) * SECTOR)
    return out


def main():
    if len(sys.argv) < 3:
        print(__doc__)
        raise SystemExit(2)

    game, out_path = sys.argv[1], sys.argv[2]

    # Where each model lives. Loose files win over archived ones, the same way
    # the game itself prefers them.
    archived = {}
    loose = {}
    archives = 0
    for base, _dirs, entries in os.walk(game):
        if os.sep + "backups" in base.lower():
            continue
        for entry in entries:
            low = entry.lower()
            full = os.path.join(base, entry)
            if low.endswith(".img"):
                found = img_entries(full)
                if found:
                    archives += 1
                for name, where in found.items():
                    archived[name] = (full,) + where
            elif low.endswith(".dff"):
                loose[low] = full

    print("  %d archives hold %d models, %d more sit loose"
          % (archives, len(archived), len(loose)))

    bounds = {}
    unreadable = 0
    boxed = 0
    handles = {}

    names = set(archived) | set(loose)
    for name in names:
        try:
            if name in loose:
                with open(loose[name], "rb") as f:
                    data = f.read()
            else:
                path, offset, length = archived[name]
                f = handles.get(path)
                if f is None:
                    f = handles[path] = open(path, "rb")
                f.seek(offset)
                data = f.read(length)
            reach, centre, half = model_shape(data)
        except (OSError, struct.error, MemoryError, ValueError):
            unreadable += 1
            continue

        if reach > 0:
            row = [round(reach, 2)]
            if centre is not None:
                row += [round(float(v), 2) for v in centre]
                row += [round(float(v), 2) for v in half]
                boxed += 1
            bounds[name[:-4]] = row
        else:
            unreadable += 1

    for f in handles.values():
        f.close()

    with open(out_path, "w") as f:
        json.dump({"models": bounds}, f, separators=(",", ":"))

    if bounds:
        vals = sorted(v[0] for v in bounds.values())
        print("  %d models measured, %d could not be read" % (len(bounds), unreadable))
        print("  %d have a real box; the rest only a sphere" % boxed)
        print("  reach: smallest %.1f, median %.1f, largest %.1f"
              % (vals[0], vals[len(vals) // 2], vals[-1]))
    print("  written to %s (%d KB)" % (out_path, os.path.getsize(out_path) // 1024))


if __name__ == "__main__":
    main()
