"""Map crash addresses to supplied image bases and exact-build symbol indexes.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
import bisect
import csv
from pathlib import Path
from _common import emit, identity, integer, parser, read_json, run, sha256


def address(value):
    if isinstance(value, str):
        value = int(value, 0)
    # Do not round addresses through floating point (64-bit VAs can exceed 2**53).
    if isinstance(value, bool) or not isinstance(value, int) or not 0 <= value < 2**64:
        raise ValueError('Expected an unsigned 64-bit address')
    return value


def symbolize(crash, symbols, target_hash):
    if identity(crash['target_sha256']) != identity(target_hash):
        raise ValueError('Crash and symbol target identities differ')
    base = address(crash['image_base'])
    size = address(crash['image_size'])
    if not size or base + size > 2**64:
        raise ValueError('Invalid image bounds')
    index = []
    starts = set()
    for symbol in symbols:
        start = address(symbol['rva'])
        length = integer(symbol['size'], 'symbol size', 1)
        if start in starts or start + length > size or not symbol['name']:
            raise ValueError('Duplicate, unnamed or out-of-image symbol')
        starts.add(start)
        index.append((start, length, symbol['name']))
    if not index:
        raise ValueError('No symbols supplied')
    index.sort()
    if any(a[0] + a[1] > b[0] for a, b in zip(index, index[1:])):
        raise ValueError('Ambiguous overlapping symbol ranges')
    starts = [item[0] for item in index]
    if not crash['addresses']:
        raise ValueError('No crash addresses supplied')
    frames = []
    for raw in crash['addresses']:
        va = address(raw)
        rva = va - base
        row = {'va': hex(va), 'rva': hex(rva) if 0 <= rva < size else None,
               'symbol': None, 'symbol_offset': None}
        at = bisect.bisect_right(starts, rva) - 1
        if 0 <= rva < size and at >= 0:
            start, length, name = index[at]
            if rva < start + length:
                row.update(symbol=name, symbol_offset=rva - start)
        frames.append(row)
    return {'tool': 'valkyrie-diagnostics', 'target_sha256': target_hash, 'frames': frames,
            'scope': 'Supplied CSV symbol ranges and loaded base; no minidump/PDB decoding, inferred function extents or root-cause proof.'}


def main():
    p = parser(__doc__)
    p.add_argument('crash', type=Path)
    p.add_argument('--symbols', type=Path, required=True)
    p.add_argument('--target-sha256', required=True)
    a = p.parse_args()
    with a.symbols.open(encoding='utf-8-sig', newline='') as stream:
        report = symbolize(read_json(a.crash), csv.DictReader(stream), a.target_sha256)
    report['input_sha256'] = {'crash': sha256(a.crash), 'symbols': sha256(a.symbols)}
    return emit(report, a.output)


if __name__ == '__main__':
    run(main)
