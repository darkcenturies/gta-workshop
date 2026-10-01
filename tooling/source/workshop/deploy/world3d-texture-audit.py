#!/usr/bin/env python3
"""
world3d-texture-audit.py -- Name the textures the extractor silently drops.

world3d-textures.py builds the manifest by calling txdread.to_image on every
texture in every dictionary the world needs. When that returns None the texture
is counted into a `failed` total and thrown away, and the total is all that is
ever printed. A texture that is not in the manifest is then filtered out of the
atlas by world3d-atlas.build before it can reserve a cell, and every material
that wanted it is drawn on the reserved plain white cell instead - which is why
those surfaces come out white with no texture on them.

So the count is the one number that matters and the one thing nobody can act
on. This walks the same dictionaries the bake would, calls the same reader, and
reports what actually failed: the texture, the dictionary it lives in, the
archive that came from, its dimensions and its raster layout. The raster
layout is the actionable part - a run of failures sharing one format is one
gap in txd-read.py rather than a hundred separate problems.

Writes nothing. It only reads the archives.

    world3d-texture-audit.py INDEX.json [--limit N] [--json OUT.json]

INDEX.json is the world-index.json the bake already produced; its `textures`
section maps every dictionary name to the archive and offset it lives at.
"""
import argparse
import collections
import importlib.util
import json
import os
import sys

_here = os.path.dirname(os.path.abspath(__file__))
_spec = importlib.util.spec_from_file_location(
    "txdread", os.path.join(_here, "txd-read.py"))
txdread = importlib.util.module_from_spec(_spec)
_spec.loader.exec_module(txdread)


def audit_dictionary(name, record):
    """(read, failures) for one dictionary. Failures carry why."""
    try:
        with open(record["src"], "rb") as f:
            f.seek(record["off"])
            data = f.read(record["len"])
        textures = txdread.read_txd(data)
    except OSError as e:
        return 0, [{"texture": "<whole dictionary>", "dictionary": name,
                    "archive": os.path.basename(record["src"]),
                    "width": 0, "height": 0, "format": "",
                    "raster": "", "why": "%s: %s" % (type(e).__name__, e)}]
    except Exception as e:
        return 0, [{"texture": "<whole dictionary>", "dictionary": name,
                    "archive": os.path.basename(record["src"]),
                    "width": 0, "height": 0, "format": "",
                    "raster": "", "why": "unreadable dictionary: %s" % e}]

    ok, bad = 0, []
    for tex in textures:
        if txdread.to_image(tex) is not None:
            ok += 1
            continue
        # Ask again without the swallow, so there is a reason rather than None.
        why = "to_image returned None"
        try:
            txdread.pixels(tex["name"], tex["width"], tex["height"],
                           tex["format"], tex["raster"], tex["palette"],
                           tex["raw"])
        except Exception as e:
            why = "%s: %s" % (type(e).__name__, e)
        bad.append({"texture": tex.get("name", "?"),
                    "dictionary": name,
                    "archive": os.path.basename(record["src"]),
                    "width": tex.get("width", 0),
                    "height": tex.get("height", 0),
                    "format": str(tex.get("format", "")),
                    "raster": str(tex.get("raster", "")),
                    "why": why})
    return ok, bad


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("index")
    ap.add_argument("--limit", type=int, default=0,
                    help="stop after this many dictionaries (for a quick look)")
    ap.add_argument("--json", dest="out", default=None,
                    help="write the full failure list here")
    args = ap.parse_args()

    index = json.load(open(args.index, encoding="utf-8"))["textures"]
    names = sorted(index)
    if args.limit:
        names = names[:args.limit]

    total_ok = 0
    failures = []
    for n, name in enumerate(names, 1):
        ok, bad = audit_dictionary(name, index[name])
        total_ok += ok
        failures.extend(bad)
        if n % 200 == 0 or n == len(names):
            print("    %d/%d dictionaries, %d readable, %d dropped so far"
                  % (n, len(names), total_ok, len(failures)), flush=True)

    print()
    print("%d dictionaries, %d textures read, %d DROPPED"
          % (len(names), total_ok, len(failures)))
    if not failures:
        print("nothing is being dropped at extraction.")
        return

    print()
    by_raster = collections.Counter(f["raster"] for f in failures)
    print("dropped by raster layout:")
    for raster, count in by_raster.most_common(12):
        print("   raster %-10s %6d" % (raster or "?", count))

    print()
    by_format = collections.Counter(f["format"] for f in failures)
    print("dropped by format word:")
    for fmt, count in by_format.most_common(12):
        print("   format %-12s %6d" % (fmt or "?", count))

    print()
    by_archive = collections.Counter(f["archive"] for f in failures)
    print("dropped by archive:")
    for arch, count in by_archive.most_common(12):
        print("   %-24s %6d" % (arch, count))

    print()
    by_why = collections.Counter(f["why"].split(":")[0] for f in failures)
    print("dropped by reason:")
    for why, count in by_why.most_common(8):
        print("   %-40s %6d" % (why[:40], count))

    print()
    print("examples:")
    for f in failures[:12]:
        print("   %-28s in %-18s %4dx%-4d raster %-6s  %s"
              % (f["texture"][:28], f["dictionary"][:18], f["width"],
                 f["height"], f["raster"], f["why"][:44]))

    if args.out:
        with open(args.out, "w", encoding="utf-8") as f:
            json.dump(failures, f, indent=1)
        print()
        print("full list written to %s" % args.out)


main()
