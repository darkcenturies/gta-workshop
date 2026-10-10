"""Validate supplied save-block bounds, sizes and profile identity.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
from pathlib import Path
from _common import emit, identity, integer, parser, read_json, run, sha256


def audit(path, contract, expected_profile):
    if not expected_profile or contract['profile'] != expected_profile:
        raise ValueError('Save profile differs from requested contract')
    actual_hash = sha256(path)
    if actual_hash != identity(contract['input_sha256']):
        raise ValueError('Save identity differs from declared input')
    size = path.stat().st_size
    results = []
    names = set()
    for block in contract['blocks']:
        name = block['name']
        if not isinstance(name, str) or not name or name in names:
            raise ValueError('Duplicate or empty block name')
        names.add(name)
        offset = integer(block['offset'], 'block offset')
        length = integer(block['size'], 'block size', 1)
        expected = integer(block['expected_size'], 'expected block size', 1)
        if offset + length > size:
            raise ValueError('Block outside supplied save: ' + name)
        results.append({'name': name, 'offset': offset, 'size': length,
                        'expected_size': expected, 'passed': length == expected})
    if not results:
        raise ValueError('No save blocks declared')
    ordered = sorted(results, key=lambda row: row['offset'])
    if any(a['offset'] + a['size'] > b['offset'] for a, b in zip(ordered, ordered[1:])):
        raise ValueError('Save blocks overlap')
    return {'tool': 'valkyrie-saves', 'passed': all(row['passed'] for row in results),
            'profile': expected_profile, 'input_sha256': actual_hash, 'input_size': size,
            'uninspected_bytes': size - sum(row['size'] for row in results), 'blocks': results,
            'scope': 'Caller supplies independently established block offsets/sizes; this does not discover, load, repair or convert saves.'}


def main():
    p = parser(__doc__)
    p.add_argument('save', type=Path)
    p.add_argument('--contract', required=True, type=Path)
    p.add_argument('--profile', required=True)
    a = p.parse_args()
    report = audit(a.save, read_json(a.contract), a.profile)
    report['contract_sha256'] = sha256(a.contract)
    return emit(report, a.output)


if __name__ == '__main__':
    run(main)
