"""Compare two extracted GTA San Andreas PS2 discs file by file.

Usage:
    python deploy/ps2-disc-diff.py OLD_DISC_DIR NEW_DISC_DIR
    python deploy/ps2-disc-diff.py --gxt OLD.GXT NEW.GXT
    python deploy/ps2-disc-diff.py --img ARCHIVE.IMG [ARCHIVE.IMG ...]

A disc directory is the extracted contents of the ISO. Loose files are compared
by MD5, VER2 IMG archives entry by entry, and large audio streams by size
only. Region-specific names are normalised so SLES_529.27 (1.00 DE) lines up
with SLES_525.41 (2.01 EU) and .GM overlays with .PM.

--gxt prints every text entry whose string differs between two GXT files.
--img lists the entries of one or more IMG archives (name, sector, sectors).

Bring your own discs. Nothing here downloads or ships game data.
"""
import hashlib
import os
import struct
import sys

SECTOR = 2048


def walk(root):
    out = {}
    for folder, _, names in os.walk(root):
        for name in names:
            path = os.path.join(folder, name)
            out[os.path.relpath(path, root).upper().replace(os.sep, '/')] = path
    return out


def normalise(key):
    return key.replace('.GM', '.PM').replace('SLES_529.27', 'SLES_525.41')


def md5(path):
    digest = hashlib.md5()
    with open(path, 'rb') as stream:
        for chunk in iter(lambda: stream.read(1 << 22), b''):
            digest.update(chunk)
    return digest.hexdigest()


def is_ver2(path):
    # SYSTEM/IOPRP300.IMG is an IOP module image, not a game archive.
    with open(path, 'rb') as stream:
        return stream.read(4) == b'VER2'


def img_entries(path):
    with open(path, 'rb') as stream:
        header = stream.read(8)
        if header[:4] != b'VER2':
            raise ValueError(path + ' is not a VER2 IMG archive')
        count = struct.unpack('<I', header[4:])[0]
        entries = []
        for _ in range(count):
            offset, size1, size2, name = struct.unpack('<IHH24s', stream.read(32))
            entries.append((name.split(b'\0')[0].decode('latin1').lower(), offset, size1 or size2))
    return entries


def img_hashes(path):
    hashes = {}
    with open(path, 'rb') as stream:
        for name, offset, sectors in img_entries(path):
            stream.seek(offset * SECTOR)
            hashes[name] = hashlib.md5(stream.read(sectors * SECTOR)).hexdigest()
    return hashes


def gxt_strings(path):
    data = open(path, 'rb').read()
    pos = 4
    if data[pos:pos + 4] != b'TABL':
        raise ValueError(path + ' has no TABL block')
    size, = struct.unpack('<I', data[pos + 4:pos + 8])
    pos += 8
    out = {}
    for i in range(size // 12):
        name, offset = struct.unpack('<8sI', data[pos + i * 12:pos + i * 12 + 12])
        name = name.split(b'\0')[0].decode()
        key_block = offset if name == 'MAIN' else offset + 8
        if data[key_block:key_block + 4] != b'TKEY':
            raise ValueError('%s: table %s has no TKEY block' % (path, name))
        keys_size, = struct.unpack('<I', data[key_block + 4:key_block + 8])
        tdat = key_block + 8 + keys_size
        if data[tdat:tdat + 4] != b'TDAT':
            raise ValueError('%s: table %s has no TDAT block' % (path, name))
        base = tdat + 8
        for j in range(keys_size // 8):
            string_offset, crc = struct.unpack('<II', data[key_block + 8 + j * 8:key_block + 16 + j * 8])
            end = data.index(b'\0', base + string_offset)
            out[(name, crc)] = data[base + string_offset:end].decode('latin1')
    return out


def diff_gxt(old, new):
    a, b = gxt_strings(old), gxt_strings(new)
    for key in sorted(set(a) | set(b)):
        if a.get(key) != b.get(key):
            print('[%s %08x]\n  old: %s\n  new: %s' % (key[0], key[1], a.get(key), b.get(key)))


def diff_discs(old_root, new_root):
    old = {normalise(k): v for k, v in walk(old_root).items()}
    new = {normalise(k): v for k, v in walk(new_root).items()}
    print('## files only on the old disc:', sorted(set(old) - set(new)))
    print('## files only on the new disc:', sorted(set(new) - set(old)))
    for key in sorted(set(old) & set(new)):
        a, b = old[key], new[key]
        if key.endswith('.IMG') and is_ver2(a) and is_ver2(b):
            ha, hb = img_hashes(a), img_hashes(b)
            changed = sorted(n for n in ha if n in hb and ha[n] != hb[n])
            print('IMG %s: only_old=%d only_new=%d changed=%d' % (
                key, len(set(ha) - set(hb)), len(set(hb) - set(ha)), len(changed)))
            for name in sorted(set(ha) - set(hb)):
                print('  removed', name)
            for name in sorted(set(hb) - set(ha)):
                print('  added', name)
            for name in changed:
                print('  changed', name)
        elif '/AUDIO/' in '/' + key and os.path.getsize(a) > 50e6:
            if os.path.getsize(a) != os.path.getsize(b):
                print('AUDIO size differs', key)
        elif md5(a) != md5(b):
            print('CHANGED %s %d -> %d bytes' % (key, os.path.getsize(a), os.path.getsize(b)))


def main(argv):
    if len(argv) == 3 and argv[0] == '--gxt':
        diff_gxt(argv[1], argv[2])
    elif len(argv) >= 2 and argv[0] == '--img':
        for path in argv[1:]:
            for name, offset, sectors in img_entries(path):
                print(os.path.basename(path), name, offset, sectors, sep='\t')
    elif len(argv) == 2:
        diff_discs(argv[0], argv[1])
    else:
        raise SystemExit(__doc__)


if __name__ == '__main__':
    main(sys.argv[1:])
