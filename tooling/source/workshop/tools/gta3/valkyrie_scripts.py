"""Inspect GTA III SCM sections using a caller-supplied opcode schema.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
import hashlib
from pathlib import Path
import struct
from _common import emit, integer, parser, read_json, run


def unpack(data, offset, fmt, end=None):
    size = struct.calcsize('<' + fmt)
    if offset < 0 or offset + size > (len(data) if end is None else end):
        raise ValueError('Truncated SCM field at byte ' + str(offset))
    return struct.unpack_from('<' + fmt, data, offset)


def header(data):
    var, = unpack(data, 3, 'I')
    if var < 7:
        raise ValueError('Invalid variable section')
    obj, = unpack(data, var + 3, 'I')
    start, = unpack(data, obj + 3, 'I')
    size, largest, count = unpack(data, obj + 8, 'IIH')
    if not (var < obj < start <= size <= len(data)):
        raise ValueError('Invalid SCM section order')
    if obj + 20 + count * 4 > start:
        raise ValueError('Mission table overlaps main instructions')
    offsets = list(unpack(data, obj + 20, 'I' * count, start))
    if offsets and (offsets[0] != size or offsets[-1] >= len(data)
                    or any(a >= b for a, b in zip(offsets, offsets[1:]))):
        raise ValueError('Invalid mission offsets')
    if not offsets and size != len(data):
        raise ValueError('Unclaimed bytes after main section')
    return {'main_start': start, 'main_end': size, 'largest_mission': largest,
            'mission_offsets': offsets}


def argument(data, pos, end):
    tag, = unpack(data, pos, 'B', end)
    formats = {1: 'i', 2: 'H', 3: 'H', 4: 'b', 5: 'h', 6: 'h'}
    if tag not in formats:
        raise ValueError('Unknown SCM argument tag at byte ' + str(pos))
    value, = unpack(data, pos + 1, formats[tag], end)
    return {'offset': pos, 'tag': tag, 'value': value / 16 if tag == 6 else value}, \
        pos + 1 + struct.calcsize('<' + formats[tag])


def inspect(data, schema):
    if schema.get('profile') != 'gta3':
        raise ValueError('Schema must explicitly select gta3')
    commands = {}
    for key, spec in schema['opcodes'].items():
        opcode = int(key, 0)
        if not 0 <= opcode <= 0x7fff or opcode in commands:
            raise ValueError('Invalid or duplicate opcode identity')
        if not isinstance(spec['name'], str) or not spec['name']:
            raise ValueError('Missing command name')
        if not isinstance(spec['args'], list) or any(t not in ('value', 'text', 'tail') for t in spec['args']):
            raise ValueError('Unsupported argument schema')
        if 'tail' in spec['args'] and spec['args'][-1] != 'tail':
            raise ValueError('Variable argument tail must be last')
        commands[opcode] = spec
    h = header(data)
    starts = [h['main_start']] + h['mission_offsets']
    ends = [h['main_end']] + h['mission_offsets'][1:] + ([len(data)] if h['mission_offsets'] else [])
    sections = []
    for index, (start, end) in enumerate(zip(starts, ends)):
        pos = start
        decoded = []
        while pos < end:
            at = pos
            raw, = unpack(data, pos, 'H', end)
            pos += 2
            op = raw & 0x7fff
            if op not in commands:
                raise ValueError(f'Opcode {op:#x} missing from supplied schema at byte {at}')
            spec = commands[op]
            args = []
            for kind in spec['args']:
                if kind == 'text':
                    value, = unpack(data, pos, '8s', end)
                    args.append({'offset': pos, 'tag': 'text', 'value': value.split(b'\0')[0].decode('ascii')})
                    pos += 8
                elif kind == 'tail':
                    while True:
                        tag, = unpack(data, pos, 'B', end)
                        if not tag:
                            pos += 1
                            break
                        arg, pos = argument(data, pos, end)
                        args.append(arg)
                else:
                    arg, pos = argument(data, pos, end)
                    args.append(arg)
            decoded.append({'offset': at, 'end': pos, 'opcode': op,
                            'negated': bool(raw & 0x8000), 'name': spec['name'], 'args': args})
        boundaries = {c['offset'] for c in decoded}
        for command in decoded:
            branch = commands[command['opcode']].get('branch_arg')
            if branch is None:
                continue
            arg = command['args'][integer(branch, 'branch_arg')]
            if arg['tag'] not in (1, 4, 5):
                raise ValueError('Branch destination must be an integer literal')
            value = arg['value']
            target = value if value >= 0 else start - value
            if target not in boundaries:
                raise ValueError('Branch destination is not an instruction in its section')
        sections.append({'index': index - 1, 'start': start, 'end': end, 'instructions': decoded})
    return {'tool': 'valkyrie-scripts', 'passed': True, 'profile': 'gta3',
            'input_sha256': hashlib.sha256(data).hexdigest(), 'header': h,
            'sections': sections, 'scope': 'Structural decoding with supplied schema; no execution or mission recovery claim.'}


def main():
    p = parser(__doc__)
    p.add_argument('script', type=Path)
    p.add_argument('--schema', required=True, type=Path)
    a = p.parse_args()
    if a.script.stat().st_size > 64 * 1024 * 1024:
        raise ValueError('SCM exceeds 64 MiB inspection limit')
    return emit(inspect(a.script.read_bytes(), read_json(a.schema)), a.output)


if __name__ == '__main__':
    run(main)
