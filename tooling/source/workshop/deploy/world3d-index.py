#!/usr/bin/env python3
"""
world3d-index.py -- Find where every model and texture in the world is kept.

The game does not keep its models in one place. There are around thirty archives
under S&S/Cdimages, one per city, plus loose files in modloader that override
whatever is in an archive. Before anything can be converted, we need one index
saying "this model lives in that archive at that offset" - and it has to resolve
overrides the same way the game does, or the map will show the stock building
where the server actually has a custom one.

    world3d-index.py GAME_DIR OUT.json
"""
import json
import os
import struct
import sys

SECTOR = 2048


def img_entries(path):
    """Name -> (offset, length) for one VER2 archive, read from its directory."""
    out = {}
    try:
        with open(path, "rb") as f:
            head = f.read(8)
            if head[:4] != b"VER2":
                return out
            count = struct.unpack_from("<I", head, 4)[0]
            table = f.read(count * 32)
    except OSError:
        return out

    for i in range(count):
        at = i * 32
        if at + 32 > len(table):
            break
        offset, streaming, size = struct.unpack_from("<IHH", table, at)
        name = table[at + 8:at + 32].split(b"\0")[0].decode("latin-1").lower()
        length = (streaming or size) * SECTOR
        if name:
            out[name] = (offset * SECTOR, length)
    return out


def main():
    game, out_path = sys.argv[1], sys.argv[2]

    archives = []
    for base, dirs, names in os.walk(game):
        # The backups folder holds the archives Eagle replaced; loading those
        # would give us the world as it was before the conversion.
        # Prune backups before descending. Named backups such as
        # valkyrie-hd-backup-20260905 otherwise sort after live archives and
        # silently override their entries.
        dirs[:] = [d for d in dirs if "backup" not in d.lower()]
        for name in names:
            if name.lower().endswith(".img"):
                archives.append(os.path.join(base, name))

    models, textures = {}, {}
    for archive in sorted(archives):
        for name, (offset, length) in img_entries(archive).items():
            record = {"src": archive, "off": offset, "len": length}
            if name.endswith(".dff"):
                models[name[:-4]] = record
            elif name.endswith(".txd"):
                textures[name[:-4]] = record

    # Loose files win. This is modloader's rule and the reason the server can
    # replace a building without touching an archive.
    loose = 0
    for base, dirs, names in os.walk(os.path.join(game, "modloader")):
        dirs[:] = [d for d in dirs if "backup" not in d.lower()]
        for name in names:
            low = name.lower()
            path = os.path.join(base, name)
            if low.endswith(".dff"):
                models[low[:-4]] = {"src": path, "off": 0, "len": os.path.getsize(path)}
                loose += 1
            elif low.endswith(".txd"):
                textures[low[:-4]] = {"src": path, "off": 0, "len": os.path.getsize(path)}
                loose += 1

    with open(out_path, "w") as f:
        json.dump({"models": models, "textures": textures}, f, separators=(",", ":"))

    print(f"  {len(archives)} archives read")
    print(f"  {len(models)} models, {len(textures)} textures")
    print(f"  {loose} loose files took priority over an archive")
    print(f"  written to {out_path} ({os.path.getsize(out_path) // 1024} KB)")


main()
