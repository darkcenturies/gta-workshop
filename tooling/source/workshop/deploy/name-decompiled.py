#!/usr/bin/env python3
"""Name functions in a stripped decompilation using gta-reversed's addresses.

The game executable has no symbols, so Ghidra emits everything as FUN_xxxxxxxx.
gta-reversed carries the address of nearly every function it has reimplemented,
in `RH_ScopedInstall(Name, 0x...)` calls, `// 0x...` markers above definitions,
and `plugin::CallMethod<0x...>` thunks. Matching the two gives names for about a
fifth of the binary, including most of the ped AI.

That fifth is the part worth having: it is precisely the code somebody has
already identified. What remains unnamed is mostly what nobody has reversed yet,
which is also where the answers we are missing live.

Usage:
  python3 deploy/name-decompiled.py <generated-dir> [-o named.csv]

For example:
  python3 deploy/name-decompiled.py \\
      docs/reverse-engineering/generated/gta-sa-1.0-us
"""

import argparse
import csv
import io
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SOURCE = os.path.join(REPO, 'reference', 'gta-reversed', 'source')

INSTALL = re.compile(
    r'RH_Scoped\w*Install\w*\(\s*([A-Za-z_:~][\w:]*)\s*,\s*(?:"[^"]*"\s*,\s*)?0x([0-9A-Fa-f]{6})')
MARKER = re.compile(
    r'//\s*0x([0-9A-Fa-f]{6})\s*\n\s*(?:[\w:<>,\*&\s]+?)\b([A-Za-z_~][\w:]*)\s*\(')
THUNK = re.compile(r'plugin::Call\w*<[^>]*?0x([0-9A-Fa-f]{6})')


def known_addresses():
    names = {}
    for dirpath, _, files in os.walk(SOURCE):
        for filename in files:
            if not filename.endswith(('.cpp', '.h')):
                continue
            path = os.path.join(dirpath, filename)
            try:
                text = io.open(path, encoding='utf-8', errors='ignore').read()
            except OSError:
                continue
            owner = os.path.splitext(filename)[0]
            for m in INSTALL.finditer(text):
                names.setdefault(int(m.group(2), 16), '%s::%s' % (owner, m.group(1)))
            for m in MARKER.finditer(text):
                names.setdefault(int(m.group(1), 16), '%s::%s' % (owner, m.group(2)))
            for m in THUNK.finditer(text):
                names.setdefault(int(m.group(1), 16), '%s (thunk)' % owner)
    return names


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('generated', help='a directory under docs/reverse-engineering/generated')
    ap.add_argument('-o', '--out', default=None)
    args = ap.parse_args()

    functions = os.path.join(args.generated, 'functions.csv')
    if not os.path.exists(functions):
        sys.exit('no functions.csv in %s' % args.generated)
    out = args.out or os.path.join(args.generated, 'named.csv')

    names = known_addresses()
    rows = list(csv.DictReader(io.open(functions, encoding='utf-8', errors='ignore')))

    matched = []
    for row in rows:
        try:
            entry = int(row['entry'], 16)
        except (KeyError, ValueError):
            continue
        if entry in names:
            matched.append((entry, names[entry], row.get('size', '')))

    with io.open(out, 'w', encoding='utf-8', newline='') as handle:
        writer = csv.writer(handle)
        writer.writerow(['entry', 'name', 'size'])
        for entry, name, size in sorted(matched):
            writer.writerow(['%08x' % entry, name, size])

    print('known addresses  %d' % len(names))
    print('functions        %d' % len(rows))
    print('named            %d (%.1f%%)' % (len(matched), 100.0 * len(matched) / max(1, len(rows))))
    print('wrote            %s' % out)
    return 0


if __name__ == '__main__':
    sys.exit(main())
