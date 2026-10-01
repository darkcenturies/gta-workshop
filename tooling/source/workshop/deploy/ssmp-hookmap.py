#!/usr/bin/env python3
"""
ssmp-hookmap.py -- Inventory everything S&SMP's server plugin patches.

ssmp.so works by rewriting samp03svr's machine code in place. Every such site
appears in its own instructions as an absolute address in samp03svr's range
(0x08048000-0x0819ffff), pushed or loaded as an immediate. Collecting those
gives a complete list of what the plugin touches - which is the only honest way
to answer "what would we still be missing?".

For each address found it disassembles samp03svr at that point, so the hook can
be identified by what the original code was doing.

Usage: ssmp-hookmap.py <ssmp.so> <samp03svr>
"""
import re
import struct
import subprocess
import sys

LO, HI = 0x08048000, 0x081A0000


def sections(path):
    """PT_LOAD segments of a 32-bit ELF as (vaddr, offset, filesz)."""
    d = open(path, "rb").read()
    e_phoff = struct.unpack_from("<I", d, 0x1C)[0]
    e_phentsize = struct.unpack_from("<H", d, 0x2A)[0]
    e_phnum = struct.unpack_from("<H", d, 0x2C)[0]
    segs = []
    for i in range(e_phnum):
        o = e_phoff + i * e_phentsize
        p_type, p_off, p_vaddr, _, p_filesz, _ = struct.unpack_from("<IIIIII", d, o)
        if p_type == 1:
            segs.append((p_vaddr, p_off, p_filesz))
    return d, segs


def disasm(path, start, length=24):
    out = subprocess.run(
        ["objdump", "-d", "--start-address", hex(start),
         "--stop-address", hex(start + length), path],
        capture_output=True, text=True).stdout
    lines = [l for l in out.splitlines() if re.match(r"^\s+[0-9a-f]+:", l)]
    return lines


def main():
    so, svr = sys.argv[1], sys.argv[2]

    # Immediates in samp03svr's range, as they appear in ssmp.so's code:
    #   68 xx xx xx xx        push $imm32
    #   b8..bf xx xx xx xx    mov  $imm32, reg
    #   c7 04 24 xx xx xx xx  movl $imm32, (%esp)
    data = open(so, "rb").read()
    found = {}
    for m in re.finditer(rb"[\x68\xb8-\xbf]", data):
        i = m.start()
        if i + 5 > len(data):
            continue
        val = struct.unpack_from("<I", data, i + 1)[0]
        if LO <= val < HI:
            found.setdefault(val, []).append(i)

    print(f"{len(found)} distinct samp03svr addresses referenced by ssmp.so\n")

    d, segs = sections(svr)

    def vaddr_ok(a):
        return any(v <= a < v + f for v, _, f in segs)

    for addr in sorted(found):
        where = ", ".join(f"+0x{o:x}" for o in found[addr][:3])
        if not vaddr_ok(addr):
            print(f"0x{addr:08x}  (ssmp.so {where})  -- not in a loaded segment")
            continue
        print(f"0x{addr:08x}  referenced from ssmp.so {where}")
        for line in disasm(svr, addr, 20)[:4]:
            print(f"      {line.strip()}")
        print()


if __name__ == "__main__":
    sys.exit(main())
