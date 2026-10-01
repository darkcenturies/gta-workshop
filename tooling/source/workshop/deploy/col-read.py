#!/usr/bin/env python3
"""
col-read.py -- Read a GTA collision file, to learn its exact layout.

We need to generate collision for models that have none. Rather than write the
format from memory - where one wrong field width is another silent crash - this
reads the collision files we already have and reports what is actually in them,
so the writer can be checked against real examples.

A collision archive is one or more models back to back:

    fourcc   "COLL" | "COL2" | "COL3" | "COL4"
    size     uint32, bytes following this field
    name     22 bytes
    modelid  uint16
    bounds   COLL: radius, centre, min, max
             COL2+: min, max, centre, radius

COL2 and later then carry counts and offsets, and store vertices as int16
scaled by 128 rather than as floats.

Usage: col-read.py <file.col> [...]
"""
import struct
import sys


def read_one(data, pos):
    """Parse one collision model starting at pos; return a summary and the next pos."""
    fourcc = data[pos:pos + 4]
    if fourcc not in (b"COLL", b"COL2", b"COL3", b"COL4"):
        return None, len(data)

    size = struct.unpack_from("<I", data, pos + 4)[0]
    end = pos + 8 + size
    name = data[pos + 8:pos + 30].split(b"\x00")[0].decode("latin-1")
    model_id = struct.unpack_from("<H", data, pos + 30)[0]

    info = {"fourcc": fourcc.decode(), "size": size, "name": name, "id": model_id}

    p = pos + 32
    if fourcc == b"COLL":
        radius, cx, cy, cz = struct.unpack_from("<ffff", data, p)
        p += 16
        mn = struct.unpack_from("<fff", data, p); p += 12
        mx = struct.unpack_from("<fff", data, p); p += 12
        info["bounds"] = (mn, mx, (cx, cy, cz), radius)
    else:
        mn = struct.unpack_from("<fff", data, p); p += 12
        mx = struct.unpack_from("<fff", data, p); p += 12
        cen = struct.unpack_from("<fff", data, p); p += 12
        radius = struct.unpack_from("<f", data, p)[0]; p += 4
        info["bounds"] = (mn, mx, cen, radius)

        n_spheres, n_boxes = struct.unpack_from("<HH", data, p); p += 4
        if fourcc == b"COL2":
            n_faces, n_lines, _pad = struct.unpack_from("<HBB", data, p); p += 4
        else:
            n_faces = struct.unpack_from("<I", data, p)[0]; p += 4
            n_lines = 0
        flags = struct.unpack_from("<I", data, p)[0]; p += 4
        off_spheres, off_boxes, off_lines, off_verts, off_faces, off_planes = \
            struct.unpack_from("<IIIIII", data, p)
        p += 24

        info.update({
            "spheres": n_spheres, "boxes": n_boxes, "faces": n_faces,
            "lines": n_lines, "flags": hex(flags),
            "off": {"spheres": off_spheres, "boxes": off_boxes, "lines": off_lines,
                    "verts": off_verts, "faces": off_faces, "planes": off_planes},
            "header_len": p - pos,
        })

    return info, end


def main():
    for path in sys.argv[1:]:
        data = open(path, "rb").read()
        print(f"=== {path.split('/')[-1]}  ({len(data)} bytes)")
        pos = 0
        n = 0
        while pos < len(data) - 8:
            info, nxt = read_one(data, pos)
            if info is None:
                break
            n += 1
            if n <= 3:
                mn, mx, cen, r = info["bounds"]
                print(f"  [{info['fourcc']}] '{info['name']}' id={info['id']} size={info['size']}")
                print(f"      min {tuple(round(v,2) for v in mn)}  max {tuple(round(v,2) for v in mx)}")
                print(f"      centre {tuple(round(v,2) for v in cen)}  radius {r:.2f}")
                if "faces" in info:
                    print(f"      spheres={info['spheres']} boxes={info['boxes']} "
                          f"faces={info['faces']} lines={info['lines']} flags={info['flags']}")
                    print(f"      header {info['header_len']} bytes, offsets {info['off']}")
            pos = nxt
        print(f"  {n} collision models in this file\n")


if __name__ == "__main__":
    main()
