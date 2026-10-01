#!/usr/bin/env python3
"""
txd-merge.py  --  Copy textures from one TXD into another, in place.

A sprite textdraw can only draw from a texture dictionary the client already
has, addressed as "dictionary:texture". Getting a *new* dictionary into that
position turned out to be the hard part - the empire artwork was tried in
custom_mods.img, declared in an IDE to own a slot, given geometry so the
streamer would fetch the pair, forced in with an object underfoot, and dropped
loose in the modloader folder our own models load from. None of it drew.

What does draw is LD_SPAC:white, which proved sprite textdraws work perfectly
well - so the answer is not to add a dictionary but to add to one that already
works. models/txd/LD_SPAC.txd is a loose file the game loads, so the empire
icons can simply live inside it and be addressed as LD_SPAC:ty_drug.

RenderWare TXD layout:

    0x16 TextureDictionary
        0x01 Struct      u16 textureCount, u16 deviceId
        0x15 TextureNative   x textureCount
        0x03 Extension

Merging is therefore: append the source's TextureNative chunks, raise the count,
and fix the sizes of the chunks that contain them.

    txd-merge.py --list TXD
    txd-merge.py TARGET SOURCE [texture ...]     all textures if none named
"""
import os, shutil, struct, sys


def chunks(blob, start, end):
    """(id, header_offset, body_offset, size) for each chunk in a range."""
    out, off = [], start
    while off + 12 <= end:
        sid, size, ver = struct.unpack_from("<III", blob, off)
        out.append((sid, off, off + 12, size))
        off += 12 + size
        if size <= 0:
            break
    return out


def texture_name(blob, body):
    """A TextureNative's name lives in its Struct child, 8 bytes in."""
    p = body + 12
    return blob[p + 8:p + 40].split(b"\0")[0].decode("latin-1", "replace")


def parse(path):
    blob = open(path, "rb").read()
    root = chunks(blob, 0, len(blob))
    if not root or root[0][0] != 0x16:
        sys.exit(f"{path}: not a texture dictionary")
    _sid, rhdr, rbody, rsize = root[0]

    inner = chunks(blob, rbody, rbody + rsize)
    struct_chunk = next((c for c in inner if c[0] == 0x01), None)
    if struct_chunk is None:
        sys.exit(f"{path}: no struct chunk")

    count, device = struct.unpack_from("<HH", blob, struct_chunk[2])
    natives = [c for c in inner if c[0] == 0x15]
    ext = next((c for c in inner if c[0] == 0x03), None)

    return dict(blob=blob, root=root[0], inner=inner, struct=struct_chunk,
                count=count, device=device, natives=natives, ext=ext)


def raw(blob, chunk):
    _sid, hdr, _body, size = chunk
    return blob[hdr:hdr + 12 + size]


def main():
    argv = sys.argv[1:]
    if not argv:
        sys.exit(__doc__)

    if argv[0] == "--list":
        t = parse(argv[1])
        print(f"{argv[1]}: {t['count']} textures declared, {len(t['natives'])} found")
        for c in t["natives"]:
            print(f"   {texture_name(t['blob'], c[2])}")
        return

    target_path, source_path = argv[0], argv[1]
    wanted = argv[2:]

    tgt = parse(target_path)
    src = parse(source_path)

    have = {texture_name(tgt["blob"], c[2]) for c in tgt["natives"]}
    add = []
    for c in src["natives"]:
        n = texture_name(src["blob"], c[2])
        if wanted and n not in wanted:
            continue
        if n in have:
            print(f"  skipping {n} - already in the target")
            continue
        add.append((n, c))

    if not add:
        print("nothing to add")
        return

    backup = target_path + ".before-empire"
    if not os.path.exists(backup):
        shutil.copy2(target_path, backup)
        print(f"backed up to {os.path.basename(backup)}")

    # Rebuild: struct (with the new count), every existing native, the new
    # natives, then the extension last as the format expects.
    body = bytearray()

    new_count = tgt["count"] + len(add)
    body += struct.pack("<III", 0x01, 4, tgt["root"][0] and 0x1803FFFF)
    body += struct.pack("<HH", new_count, tgt["device"])

    for c in tgt["natives"]:
        body += raw(tgt["blob"], c)
    for n, c in add:
        body += raw(src["blob"], c)
        print(f"  added {n}")
    if tgt["ext"] is not None:
        body += raw(tgt["blob"], tgt["ext"])

    out = struct.pack("<III", 0x16, len(body), 0x1803FFFF) + bytes(body)
    open(target_path, "wb").write(out)

    check = parse(target_path)
    names = [texture_name(check["blob"], c[2]) for c in check["natives"]]
    print(f"\n{os.path.basename(target_path)}: {check['count']} declared, {len(names)} present")
    assert check["count"] == len(names), "declared count does not match what is in the file"
    for n, _c in add:
        assert n in names, f"{n} did not survive the write"
    print("verified: re-read and every added texture is there")


if __name__ == "__main__":
    main()
