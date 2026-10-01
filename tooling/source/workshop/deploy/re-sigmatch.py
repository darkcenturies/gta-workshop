#!/usr/bin/env python3
"""
re-sigmatch.py -- Find S&SMP's hooked functions in a different samp.dll build.

ssmptw.asi hooks nine samp.dll offsets. Those offsets are only valid for the
build it was made for (0.3.7-R3); in another build (0.3.DL) the same functions
live elsewhere. This takes a byte signature of each function from the reference
DLL and searches for it in the target DLL, reporting the new offset.

Absolute addresses inside the code differ between builds, so bytes that look like
an address into the module are wildcarded before searching.

Usage: re-sigmatch.py <reference samp.dll> <target samp.dll>
"""
import struct, sys, re

OFFSETS = [0xA71B0, 0xE330, 0xB74E0, 0xB7540, 0xB6C10, 0xB7570, 0xA14E0, 0xA3830, 0xB6A50]
SIGLEN = 32

def load(path):
    data = open(path, "rb").read()
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    nsec = struct.unpack_from("<H", data, pe+6)[0]
    optsz = struct.unpack_from("<H", data, pe+20)[0]
    opt = pe + 24
    imgbase = struct.unpack_from("<I", data, opt+28)[0]
    secs = []
    so = opt + optsz
    for i in range(nsec):
        o = so + i*40
        vsz, va, rsz, rp = struct.unpack_from("<IIII", data, o+8)
        secs.append((va, vsz, rp, rsz))
    return data, imgbase, secs

def rva2off(secs, rva):
    for va, vsz, rp, rsz in secs:
        if va <= rva < va + max(vsz, rsz):
            return rp + (rva - va)
    return None

ref_path = sys.argv[1]
tgt_path = sys.argv[2]
ref, ref_base, ref_secs = load(ref_path)
tgt, tgt_base, tgt_secs = load(tgt_path)

print(f"# reference: {ref_path} (base 0x{ref_base:X})")
print(f"# target   : {tgt_path} (base 0x{tgt_base:X})\n")
print(f"{'offset':>10}  {'result':>12}  detail")

for off in OFFSETS:
    o = rva2off(ref_secs, off)
    if o is None:
        print(f"  0x{off:06X}  {'NO SECTION':>12}")
        continue
    sig = ref[o:o+SIGLEN]

    # Build a regex over the bytes, wildcarding everything that legitimately moves
    # between builds: absolute addresses into the module, and the rel32 operand of
    # call/jmp (E8/E9), which is relative to the instruction's own position.
    parts = []
    i = 0
    while i < len(sig):
        b = sig[i]
        if b in (0xE8, 0xE9) and i + 5 <= len(sig):
            parts.append(re.escape(bytes([b])) + b"...."      # opcode + wildcard rel32
                         .replace(b".", b"[\\x00-\\xff]"))
            i += 5
            continue
        if i + 4 <= len(sig):
            v = struct.unpack_from("<I", sig, i)[0]
            if ref_base <= v < ref_base + 0x400000:
                parts.append(b"[\\x00-\\xff]{4}")
                i += 4
                continue
        parts.append(re.escape(bytes([b])))
        i += 1
    rx = b"".join(parts)
    try:
        hits = [m.start() for m in re.finditer(rx, tgt, re.DOTALL)]
    except re.error:
        hits = []

    if len(hits) == 1:
        # convert file offset back to an RVA in the target
        new = None
        for va, vsz, rp, rsz in tgt_secs:
            if rp <= hits[0] < rp + rsz:
                new = va + (hits[0] - rp)
        print(f"  0x{off:06X}  {'MATCH':>12}  -> target +0x{new:X}")
    elif len(hits) > 1:
        print(f"  0x{off:06X}  {'AMBIGUOUS':>12}  {len(hits)} matches")
    else:
        print(f"  0x{off:06X}  {'NOT FOUND':>12}  (function changed between builds)")
