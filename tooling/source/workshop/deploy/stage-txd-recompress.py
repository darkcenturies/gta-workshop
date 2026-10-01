#!/usr/bin/env python3
"""Copy just the texture files that need recompressing into a staging folder.

Only 37 of 380 texture dictionaries contain any uncompressed texture, and the
other 343 are already stored well. Pointing a batch converter at models/ would
re-encode all 6,042 already-compressed textures, and DXT compression is lossy -
every one of them would come out slightly worse to gain about 9MB.

So the 37 are copied out on their own, keeping their folder structure. Convert
that folder, then run this again with --restore to put them back.

    python3 deploy/stage-txd-recompress.py            # copy them out
    ... convert deploy/txd-recompress/ in Magic.TXD ...
    python3 deploy/stage-txd-recompress.py --restore  # put them back

--restore refuses to copy back a file that grew, which would mean the converter
was set to add mipmaps rather than compress.
"""

import argparse
import pathlib
import shutil
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
MODELS = ROOT / "models"
STAGE = ROOT / "deploy" / "txd-recompress"
# Magic.TXD's Mass Conversion writes to a separate output root, so the
# originals in STAGE stay untouched and can be compared against.
CONVERTED = ROOT / "deploy" / "txd-recompress-out"
LIST = ROOT / "deploy" / "uncompressed-txds.txt"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--restore", action="store_true")
    ap.add_argument("--force", action="store_true",
                    help="restore even files that got bigger")
    args = ap.parse_args()

    if not LIST.is_file():
        print("run deploy/analyse-textures.py first - %s is missing" % LIST.name,
              file=sys.stderr)
        return 1

    files = [l.strip() for l in LIST.read_text().splitlines() if l.strip()]

    if not args.restore:
        if STAGE.exists():
            shutil.rmtree(STAGE)
        total = 0
        for rel in files:
            src = MODELS / rel
            if not src.is_file():
                print("  ! missing: %s" % rel)
                continue
            dst = STAGE / rel
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src, dst)
            total += src.stat().st_size
        print("staged %d files (%.1f MB) in %s"
              % (len(files), total / 1048576, STAGE))
        print("\nConvert that folder, then re-run with --restore.")
        return 0

    # Prefer the converter's output; fall back to the staging folder if it was
    # converted in place.
    source_root = CONVERTED if CONVERTED.is_dir() else STAGE
    if not source_root.is_dir():
        print("nothing to restore - looked in %s and %s" % (CONVERTED, STAGE),
              file=sys.stderr)
        return 1
    print("reading converted files from %s\n" % source_root)

    restored = skipped = 0
    before = after = 0
    for rel in files:
        src = source_root / rel
        if not src.is_file():
            # Magic.TXD may flatten or rename; try by filename anywhere below.
            matches = list(source_root.rglob(pathlib.Path(rel).name))
            if len(matches) == 1:
                src = matches[0]
        dst = MODELS / rel
        if not src.is_file():
            continue
        old = dst.stat().st_size if dst.is_file() else 0
        new = src.stat().st_size

        if new >= old and not args.force:
            print("  skipped (no smaller): %-52s %.0fKB -> %.0fKB"
                  % (rel, old / 1024, new / 1024))
            skipped += 1
            continue

        shutil.copy2(src, dst)
        before += old
        after += new
        restored += 1

    print("\nrestored %d files, skipped %d" % (restored, skipped))
    if restored:
        print("size of those files: %.1f MB -> %.1f MB (%.1f MB saved)"
              % (before / 1048576, after / 1048576, (before - after) / 1048576))
    print("\nNow rebuild nothing - these are data files - but DO restart the")
    print("server and check the log for '[artwork:error]' before committing.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
