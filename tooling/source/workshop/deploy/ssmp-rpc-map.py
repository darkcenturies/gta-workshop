#!/usr/bin/env python3
"""Locate S&SMP protocol strings and their code references in ssmp.so.

The Linux plugin is a stripped, position-independent 32-bit ELF.  Ordinary
string searches show that it registers a custom RPC, but not which code uses
each protocol key.  GCC's i386 PIC prologue gives each function a stable EBX
base; resolving ``[ebx + displacement]`` operands recovers those references
without requiring an interactive disassembler.

Usage: ssmp-rpc-map.py <ssmp.so> [string ...]
"""

from __future__ import annotations

import struct
import sys


DEFAULT_TERMS = (
    "Custom RPC",
    "vehicle_",
    "IsSSmpPlayer",
    "ClientJoin",
)


def cstrings(data: bytes, start: int, size: int, vaddr: int):
    strings = {}
    end = start + size
    cursor = start
    while cursor < end:
        tail = data[cursor:end]
        zero = tail.find(b"\0")
        if zero < 0:
            break
        raw = tail[:zero]
        if len(raw) >= 4 and all(32 <= byte < 127 for byte in raw):
            strings[vaddr + cursor - start] = raw.decode("ascii")
        cursor += zero + 1
    return strings


def load_elf(path: str):
    data = open(path, "rb").read()
    if data[:5] != b"\x7fELF\x01":
        sys.exit("expected a 32-bit ELF")

    section_offset = struct.unpack_from("<I", data, 0x20)[0]
    section_size = struct.unpack_from("<H", data, 0x2E)[0]
    section_count = struct.unpack_from("<H", data, 0x30)[0]
    names_index = struct.unpack_from("<H", data, 0x32)[0]

    rows = []
    for index in range(section_count):
        offset = section_offset + index * section_size
        rows.append(struct.unpack_from("<IIIIIIIIII", data, offset))

    names_row = rows[names_index]
    names = data[names_row[4]:names_row[4] + names_row[5]]

    sections = {}
    for row in rows:
        name_offset = row[0]
        end = names.find(b"\0", name_offset)
        name = names[name_offset:end].decode("ascii")
        sections[name] = row
    return data, sections


def main():
    if len(sys.argv) < 2 or sys.argv[1] in ("-h", "--help"):
        print(__doc__.strip())
        return

    try:
        import capstone
        from capstone.x86 import X86_OP_MEM, X86_REG_EBX
    except ImportError:
        sys.exit("capstone is required to analyse ssmp.so")

    path = sys.argv[1]
    terms = tuple(sys.argv[2:]) or DEFAULT_TERMS
    data, sections = load_elf(path)
    text = sections[".text"]
    rodata = sections[".rodata"]

    text_addr, text_offset, text_size = text[3], text[4], text[5]
    ro_addr, ro_offset, ro_size = rodata[3], rodata[4], rodata[5]
    strings = cstrings(data, ro_offset, ro_size, ro_addr)
    wanted = {
        address: value
        for address, value in strings.items()
        if any(term.lower() in value.lower() for term in terms)
    }

    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    instructions = list(md.disasm(
        data[text_offset:text_offset + text_size], text_addr
    ))

    references = {address: [] for address in wanted}
    pic_base = None
    for index, instruction in enumerate(instructions):
        # __x86.get_pc_thunk.bx puts the return address in EBX.  GCC follows
        # it immediately with `add ebx, immediate` to establish the GOT base.
        if instruction.mnemonic == "call" and index + 1 < len(instructions):
            following = instructions[index + 1]
            if following.mnemonic == "add" and following.op_str.startswith("ebx, "):
                try:
                    immediate = following.operands[1].imm
                except (IndexError, AttributeError):
                    immediate = None
                if immediate is not None:
                    pic_base = instruction.address + instruction.size + immediate

        if pic_base is None:
            continue

        for operand in instruction.operands:
            if operand.type != X86_OP_MEM or operand.mem.base != X86_REG_EBX:
                continue
            address = (pic_base + operand.mem.disp) & 0xFFFFFFFF
            if address in references:
                references[address].append(instruction.address)

    for address, value in sorted(wanted.items()):
        locations = references[address]
        joined = ", ".join(f"0x{item:08x}" for item in locations) or "no code reference"
        print(f"0x{address:08x}  {joined:40s}  {value}")


if __name__ == "__main__":
    main()
