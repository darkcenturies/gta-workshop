#!/usr/bin/env python3
"""Compare model-key coverage between two CADB v2 files."""
import argparse
import struct


def keys(path):
    result = set()
    with open(path, "rb") as stream:
        if stream.read(4) != b"cadf":
            raise ValueError(f"{path}: not a CADB")
        version, count, _ = struct.unpack("<HHI", stream.read(8))
        if version != 2:
            raise ValueError(f"{path}: unsupported CADB v{version}")
        for _ in range(count):
            modelid, spheres, boxes, faces = struct.unpack("<HHHH", stream.read(8))
            result.add(modelid)
            stream.seek(spheres * 16 + boxes * 24 + faces * 36, 1)
    return result


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("old")
    parser.add_argument("new")
    args = parser.parse_args()
    old, new = keys(args.old), keys(args.new)
    print(f"old={len(old)} new={len(new)} shared={len(old & new)}")
    print("missing from new:", " ".join(map(str, sorted(old-new))))
    print("added by new:", " ".join(map(str, sorted(new-old))))


if __name__ == "__main__":
    main()
