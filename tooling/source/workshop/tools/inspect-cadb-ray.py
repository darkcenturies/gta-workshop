#!/usr/bin/env python3
"""Report every vertical CADB intersection at one world XY coordinate."""
import argparse
import math
import struct


def rotate(v, q):
    x, y, z = v
    qx, qy, qz, qw = q
    tx, ty, tz = 2 * (qy*z-qz*y), 2 * (qz*x-qx*z), 2 * (qx*y-qy*x)
    return (x + qw*tx + qy*tz-qz*ty,
            y + qw*ty + qz*tx-qx*tz,
            z + qw*tz + qx*ty-qy*tx)


def triangle_z(x, y, a, b, c):
    den = (b[1]-c[1])*(a[0]-c[0]) + (c[0]-b[0])*(a[1]-c[1])
    if abs(den) < 1e-8:
        return None
    u = ((b[1]-c[1])*(x-c[0]) + (c[0]-b[0])*(y-c[1])) / den
    v = ((c[1]-a[1])*(x-c[0]) + (a[0]-c[0])*(y-c[1])) / den
    w = 1-u-v
    if min(u, v, w) < -1e-6:
        return None
    return u*a[2] + v*b[2] + w*c[2]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("cadb")
    ap.add_argument("x", type=float)
    ap.add_argument("y", type=float)
    args = ap.parse_args()
    models = {}
    with open(args.cadb, "rb") as f:
        if f.read(4) != b"cadf":
            raise ValueError("not a CADB")
        version, model_count, placement_count = struct.unpack("<HHI", f.read(8))
        for _ in range(model_count):
            mid, ns, nb, nf = struct.unpack("<HHHH", f.read(8))
            spheres = [struct.unpack("<ffff", f.read(16)) for _ in range(ns)]
            boxes = [struct.unpack("<ffffff", f.read(24)) for _ in range(nb)]
            faces = []
            radius = 0.0
            for _ in range(nf):
                v = struct.unpack("<fffffffff", f.read(36))
                tri = (v[0:3], v[3:6], v[6:9])
                faces.append(tri)
                radius = max(radius, *(math.hypot(p[0], p[1]) for p in tri))
            for cx, cy, cz, sx, sy, sz in boxes:
                radius = max(radius, math.hypot(cx, cy) + math.hypot(sx, sy))
            for cx, cy, cz, r in spheres:
                radius = max(radius, math.hypot(cx, cy) + r)
            models[mid] = (spheres, boxes, faces, radius)
        hits = []
        for _ in range(placement_count):
            mid = struct.unpack("<H", f.read(2))[0]
            px, py, pz = struct.unpack("<fff", f.read(12))
            q = struct.unpack("<ffff", f.read(16))
            model = models.get(mid)
            if model is None or math.hypot(args.x-px, args.y-py) > model[3] + 0.01:
                continue
            spheres, boxes, faces, _ = model
            for tri in faces:
                world = []
                for point in tri:
                    r = rotate(point, q)
                    world.append((r[0]+px, r[1]+py, r[2]+pz))
                z = triangle_z(args.x, args.y, *world)
                if z is not None:
                    hits.append((z, mid, "face"))
            # ColAndreas boxes are oriented with the placement quaternion.
            for cx, cy, cz, sx, sy, sz in boxes:
                corners = [(cx+dx*sx, cy+dy*sy, cz+dz*sz)
                           for dx,dy,dz in ((-1,-1,-1),(1,-1,-1),(1,1,-1),(-1,1,-1),
                                            (-1,-1,1),(1,-1,1),(1,1,1),(-1,1,1))]
                world = []
                for point in corners:
                    r = rotate(point, q); world.append((r[0]+px,r[1]+py,r[2]+pz))
                for ia,ib,ic in ((0,1,2),(0,2,3),(4,6,5),(4,7,6),(0,4,5),(0,5,1),
                                 (1,5,6),(1,6,2),(2,6,7),(2,7,3),(3,7,4),(3,4,0)):
                    z = triangle_z(args.x,args.y,world[ia],world[ib],world[ic])
                    if z is not None: hits.append((z,mid,"box"))
            for cx,cy,cz,radius in spheres:
                center = rotate((cx,cy,cz),q)
                wx,wy,wz = center[0]+px,center[1]+py,center[2]+pz
                d2 = (args.x-wx)**2 + (args.y-wy)**2
                if d2 <= radius*radius:
                    dz = math.sqrt(radius*radius-d2)
                    hits.extend(((wz-dz,mid,"sphere"),(wz+dz,mid,"sphere")))
    unique = []
    for hit in sorted(hits, reverse=True):
        if not unique or abs(hit[0]-unique[-1][0]) > 1e-3 or hit[1:] != unique[-1][1:]:
            unique.append(hit)
    print(f"CADB v{version}: {model_count} models, {placement_count} placements")
    for z, mid, kind in unique[:100]:
        print(f"z={z:.6f} model={mid} primitive={kind}")
    if not unique:
        print("no vertical intersections")


if __name__ == "__main__":
    main()
