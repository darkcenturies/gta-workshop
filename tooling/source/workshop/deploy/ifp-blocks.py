#!/usr/bin/env python3
"""
ifp-blocks.py -- List the animation blocks inside a ped.ifp.

A ped's walk/run style comes from its animation GROUP, named in peds.ide (the
"woman", "man", "oldman" ... column). The game resolves that group name against
the blocks in ANIM\\PED.IFP. If the block a skin asks for isn't there, the ped
falls back to the default set - which is why a female skin can end up running
like CJ.

This lists the blocks a ped.ifp actually contains, so two builds can be compared.

Usage: ifp-blocks.py <ped.ifp> [ped.ifp ...]
"""
import struct, sys, re, os

def blocks(path):
    data = open(path, "rb").read()
    names = []

    # ANPK (the format our cutscene .ifp files use): NAME chunks
    if data[:4] == b"ANPK":
        for m in re.finditer(rb"NAME", data):
            s = m.start()
            n = struct.unpack_from("<I", data, s+4)[0]
            if 1 <= n <= 32:
                nm = data[s+8:s+8+n].split(b"\x00")[0].decode("latin-1", "replace")
                if re.match(r"^[A-Za-z0-9_:\-]+$", nm):
                    names.append(nm)
        return "ANPK", names

    # ANP3 / standard SA ped.ifp: 'ANP3' <size> then per-animation
    #   name[24] ... - the block names are fixed-width strings
    if data[:4] == b"ANP3":
        off = 8
        # animation count follows the header
        cnt = struct.unpack_from("<I", data, off)[0]
        off += 4 + 24        # count + package name
        for _ in range(min(cnt, 4000)):
            if off + 24 > len(data):
                break
            nm = data[off:off+24].split(b"\x00")[0].decode("latin-1", "replace")
            if re.match(r"^[A-Za-z0-9_\-]+$", nm or "x"):
                names.append(nm)
            # skip to the next animation: frame count + per-bone data
            nframes = struct.unpack_from("<I", data, off+24)[0]
            off += 28
            for _ in range(min(nframes, 512)):
                if off + 32 > len(data):
                    break
                fr = struct.unpack_from("<I", data, off+28)[0]
                off += 32 + fr * 8
        return "ANP3", names

    return data[:4].decode("latin-1", "replace"), names


for p in sys.argv[1:] or ["/mnt/c/Games/Project Eagle/anim/ped.ifp"]:
    if not os.path.isfile(p):
        print(f"{p}: missing")
        continue
    kind, names = blocks(p)
    print(f"=== {p}")
    print(f"    format {kind}, {os.path.getsize(p)} bytes, {len(names)} names parsed")
    # the walk-style groups referenced by peds.ide
    for want in ("woman", "man", "oldman", "fatman", "oldfatman", "sexywoman",
                 "shopping", "busywoman", "player"):
        hit = [n for n in names if n.lower() == want]
        print(f"    {want:12s} {'PRESENT' if hit else '-- missing --'}")
    print(f"    first names: {', '.join(names[:8])}")
    print()
