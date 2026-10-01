#!/usr/bin/env python3
"""
ifp-names.py -- List the animations in a San Andreas .ifp, or compare two.

San Andreas uses the ANP3 form of IFP, where the keyframes are quantised to
16-bit and the whole thing is packed tighter than the ANPK form the earlier
games used. Only the names are wanted here, but the frames still have to be
stepped over to find the next name, so the frame sizes matter.

Unlike ANPK, ANP3 says which kind of frame follows with a number rather than a
four letter tag - reading it as a tag walks straight off the end of the file:

    3   rotation only          4 shorts + time     = 10 bytes
    4   rotation + position    7 shorts + time     = 16 bytes

    ifp-names.py FILE            list what is in it
    ifp-names.py FILE OTHER      what the second has that the first does not
"""
import struct
import sys

FRAME_BYTES = {3: 10, 4: 16}


def cstr(raw):
    return raw.split(b"\0")[0].decode("latin-1", "replace")


def read(path):
    buf = open(path, "rb").read()
    if buf[:4] != b"ANP3":
        raise ValueError(f"{path}: not ANP3 (starts {buf[:4]!r})")

    pos = 4
    _size = struct.unpack_from("<I", buf, pos)[0]
    pos += 4
    _name = cstr(buf[pos:pos + 24])
    pos += 24
    count = struct.unpack_from("<i", buf, pos)[0]
    pos += 4

    out = []
    for _ in range(count):
        name = cstr(buf[pos:pos + 24])
        pos += 24
        objects, _frameBytes, _unk = struct.unpack_from("<iii", buf, pos)
        pos += 12
        out.append(name)

        for _ in range(objects):
            pos += 24                                  # bone name
            kind, frames, _bone = struct.unpack_from("<iii", buf, pos)
            pos += 12
            pos += frames * FRAME_BYTES.get(kind, 10)

    return out


def main():
    if len(sys.argv) == 2:
        names = read(sys.argv[1])
        print(f"{len(names)} animations")
        for n in names:
            print(f"  {n}")
        return

    have = read(sys.argv[1])
    other = read(sys.argv[2])
    a, b = set(have), set(other)

    print(f"  installed: {len(have)} animations")
    print(f"  compared:  {len(other)} animations")

    added = sorted(b - a)
    gone = sorted(a - b)

    print(f"\n  {len(added)} added")
    for n in added:
        print(f"    + {n}")

    print(f"\n  {len(gone)} removed")
    for n in gone:
        print(f"    - {n}")


main()
