#!/usr/bin/env python3
"""
dedupe-collision.py -- Drop collision surfaces that duplicate one behind them.

A remodelled building is drawn in layers: the wall you see, and behind it inner
skins and backing panels the mapper added so it looks right from every angle.
Generating collision from the visible mesh makes all of them solid, so players
are stopped at the outermost layer - half a metre in front of the wall they can
see, all the way around the block.

Replacing the whole thing with the original building's hand-made hull is not the
answer: the hull only knows the original, and our models add surfaces it never
had, including the floor inside the gym. Swapping it in makes players fall
through.

So this removes only what is provably redundant. A face is dropped when a ray
cast backwards out of it meets another, roughly parallel face of the same model
within a short distance. That can never open a hole, because whatever the face
was covering is still covered by the surface immediately behind it - the
collision simply moves back to where the wall actually is.

Usage:
    dedupe-collision.py reyo/gymenex.dff 20612 --write <dir> [--write <dir>]
"""
import argparse
import importlib.util
import math
import os

HERE = os.path.dirname(os.path.abspath(__file__))


def _load(name, filename):
    spec = importlib.util.spec_from_file_location(name, os.path.join(HERE, filename))
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


dffread = _load("dffread", "dff-read.py")
colgen = _load("colgen", "gen-collision.py")
findface = _load("findface", "find-face.py")


def normal(a, b, c):
    ux, uy, uz = b[0] - a[0], b[1] - a[1], b[2] - a[2]
    vx, vy, vz = c[0] - a[0], c[1] - a[1], c[2] - a[2]
    nx, ny, nz = uy * vz - uz * vy, uz * vx - ux * vz, ux * vy - uy * vx
    length = math.sqrt(nx * nx + ny * ny + nz * nz)
    if length < 1e-9:
        return None
    return (nx / length, ny / length, nz / length)


def centre(a, b, c):
    return ((a[0] + b[0] + c[0]) / 3.0,
            (a[1] + b[1] + c[1]) / 3.0,
            (a[2] + b[2] + c[2]) / 3.0)


def area(a, b, c):
    ux, uy, uz = b[0] - a[0], b[1] - a[1], b[2] - a[2]
    vx, vy, vz = c[0] - a[0], c[1] - a[1], c[2] - a[2]
    nx, ny, nz = uy * vz - uz * vy, uz * vx - ux * vz, ux * vy - uy * vx
    return 0.5 * math.sqrt(nx * nx + ny * ny + nz * nz)


def dedupe(verts, tris, mats, gap=0.75, parallel=0.9, min_area=0.5,
           walls_only=True, upright=0.6):
    """Which faces are an outer skin over another surface?

    gap         how close the surface behind must be to count as covering it
    parallel    how nearly parallel the two must be, as a dot product
    min_area    leave small detail alone; it is not what people walk into
    walls_only  never touch floors or ceilings
    upright     how level a face must be to count as a floor

    The floor rule is not caution for its own sake. Replacing this model's
    collision wholesale dropped players through the gym, because gymenex.dff
    carries the floor inside it as well as the shell. A wall removed in error
    lets somebody walk half a metre too far; a floor removed in error drops them
    out of the world. The two are not worth trading against each other, and the
    problem being fixed is walls.
    """
    faces = []
    for a, b, c, mi in tris:
        if max(a, b, c) >= len(verts):
            continue
        faces.append(((verts[a], verts[b], verts[c]), mi, (a, b, c)))

    geom = [f[0] for f in faces]
    normals = [normal(*g) for g in geom]

    keep, dropped = [], []
    for i, ((a, b, c), mi, idx) in enumerate(faces):
        n = normals[i]
        if n is None or area(a, b, c) < min_area:
            keep.append((idx[0], idx[1], idx[2], mi))
            continue

        # Anything you could stand on stays, whatever is underneath it.
        if walls_only and abs(n[2]) > upright:
            keep.append((idx[0], idx[1], idx[2], mi))
            continue

        mid = centre(a, b, c)
        back = (-n[0], -n[1], -n[2])
        origin = (mid[0] + back[0] * 0.02,
                  mid[1] + back[1] * 0.02,
                  mid[2] + back[2] * 0.02)

        covered = None
        for j, g in enumerate(geom):
            if j == i or normals[j] is None:
                continue
            dot = abs(n[0] * normals[j][0] + n[1] * normals[j][1] + n[2] * normals[j][2])
            if dot < parallel:
                continue
            hit = findface.ray_triangle(origin, back, *g)
            if hit is not None and hit <= gap:
                covered = hit
                break

        if covered is not None:
            dropped.append((area(a, b, c), i, covered,
                            mats[mi][1] if mi < len(mats) else "?"))
        else:
            keep.append((idx[0], idx[1], idx[2], mi))

    return keep, dropped


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("dff")
    ap.add_argument("modelid", type=int)
    ap.add_argument("--dir", default="/mnt/c/Users/YourUser/sp-rp/models")
    ap.add_argument("--write", action="append", default=[])
    ap.add_argument("--gap", type=float, default=0.75)
    ap.add_argument("--min-area", type=float, default=0.5)
    ap.add_argument("--include-floors", action="store_true",
                    help="also dedupe floors and ceilings - not advised, this "
                         "is what dropped players through the gym")
    args = ap.parse_args()

    path = args.dff if os.path.isabs(args.dff) else os.path.join(args.dir, args.dff)
    verts, tris, mats = dffread.read_dff(path, with_materials=True)
    solid = [t for t in tris if dffread.face_is_solid(t[3], mats)]

    keep, dropped = dedupe(verts, solid, mats, args.gap,
                           min_area=args.min_area,
                           walls_only=not args.include_floors)

    print(f"{os.path.basename(path)}")
    print(f"    {len(tris)} triangles, {len(solid)} solid")
    print(f"    {len(dropped)} dropped as an outer skin, {len(keep)} kept"
          f"{'' if args.include_floors else '  (floors and ceilings untouched)'}")

    if dropped:
        dropped.sort(key=lambda d: -d[0])
        total = sum(d[0] for d in dropped)
        print(f"    {total:.0f} m2 of duplicate surface removed; biggest:")
        for ar, i, behind, tex in dropped[:8]:
            print(f"      tri {i:>5}  {ar:8.1f} m2  covered {behind:.2f}m "
                  f"further back  '{tex}'")

    if not args.write:
        return

    name = f"sprp{args.modelid}"
    col = colgen.make_col_exact(name, args.modelid, verts, keep)
    if col is None:
        raise SystemExit("make_col_exact returned nothing - nothing written")
    for d in args.write:
        out = os.path.join(d, name + ".col")
        with open(out, "wb") as fh:
            fh.write(col)
        print(f"    wrote {out} ({len(col)} bytes)")


if __name__ == "__main__":
    main()
