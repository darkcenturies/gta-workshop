"""Validate native ANP3 allocation sizes, HAnim tags and compressed keyframes."""
import hashlib
import json
from pathlib import Path
import struct
import sys


def validate(path, expected_tags=None):
    raw = Path(path).read_bytes()
    if len(raw) < 36 or raw[:4] != b'ANP3' or struct.unpack_from('<I', raw, 4)[0] != len(raw) - 8:
        raise ValueError('Invalid native header or file size')
    offset = 8
    def name():
        nonlocal offset
        if offset + 24 > len(raw):
            raise ValueError('Truncated native name')
        value = raw[offset:offset + 24]
        offset += 24
        if b'\0' not in value or not value[0]:
            raise ValueError('Empty or unterminated native name')
        return value.split(b'\0')[0].decode('ascii')
    def fields(fmt):
        nonlocal offset
        size = struct.calcsize(fmt)
        if offset + size > len(raw):
            raise ValueError('Truncated native fields')
        result = struct.unpack_from(fmt, raw, offset)
        offset += size
        return result
    library = name()
    count, = fields('<I')
    if not 0 < count < 10000 or len(library) >= 16:
        raise ValueError('Invalid library/count')
    records, names = [], set()
    for _ in range(count):
        label = name()
        if label.lower() in names:
            raise ValueError('Duplicate clip')
        names.add(label.lower())
        bones, allocation, flags = fields('<III')
        if not 0 < bones <= 256 or flags != 1:
            raise ValueError('Invalid native sequence count/compression flag')
        tags, consumed, key_count, end, worst_norm = set(), 0, 0, 0, 0
        root_first, root_last = None, None
        for _ in range(bones):
            bone_name = name()
            kind, frames, tag = fields('<IIi')
            if kind not in (3, 4) or not 2 <= frames <= 32767 or tag in tags or tag < 0:
                raise ValueError('Invalid sequence kind, frames or tag')
            tags.add(tag)
            previous_time, previous_q = -1, None
            for _ in range(frames):
                *q, time = fields('<5h')
                if sum(v*v for v in q)>4096*4096:
                    raise ValueError('Compressed quaternion exceeds native interpolation unit sphere')
                q = [v / 4096 for v in q]
                error = abs(sum(v * v for v in q) - 1)
                if error > .001 or time <= previous_time:
                    raise ValueError('Invalid compressed quaternion or frame order')
                if previous_q and sum(a * b for a, b in zip(q, previous_q)) < -.001:
                    raise ValueError('Quaternion hemisphere flip')
                previous_time, previous_q = time, q
                worst_norm = max(worst_norm, error)
                if kind == 4:
                    position = [v / 1024 for v in fields('<3h')]
                    if tag == 0:
                        if root_first is None: root_first = position
                        root_last = position
            consumed += frames * (16 if kind == 4 else 10)
            key_count += frames
            end = max(end, previous_time)
        if allocation != consumed:
            raise ValueError('Native frame allocation does not match the data written')
        if expected_tags is not None and tags != set(expected_tags):
            raise ValueError('Animation HAnim tags differ from supplied target skeleton')
        records.append({'name': label, 'bones': bones, 'keys': key_count,
                        'duration': end / 60, 'root_forward_speed': ((root_last[1]-root_first[1])/(end/60)) if root_last else 0, 'quaternion_norm_error_max': worst_norm})
    if offset != len(raw):
        raise ValueError('Trailing native data')
    return {'library': library, 'sha256': hashlib.sha256(raw).hexdigest(), 'clips': records,
            'native_time_ticks_per_second': 60, 'native_allocation_verified': True, 'gameplay_tested': False}


if __name__ == '__main__':
    result = validate(sys.argv[1])
    Path(sys.argv[2]).write_text(json.dumps(result, indent=2) + '\n')
    print('Native animations validated:', len(result['clips']))
