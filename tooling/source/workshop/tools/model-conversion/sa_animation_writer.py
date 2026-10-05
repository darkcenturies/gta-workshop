"""Strict GTA SA ANP3 writer for locally supplied, retargeted animation samples."""
import math
import struct


def name24(name):
    raw = name.encode('ascii')
    if not raw or len(raw) > 23 or b'\0' in raw:
        raise ValueError('Animation names must be 1..23 ASCII bytes')
    return raw.ljust(24, b'\0')


def quantize(value, scale):
    if not math.isfinite(value):
        raise ValueError('Nonfinite animation component')
    result = round(value * scale)
    if not -32768 <= result <= 32767:
        raise ValueError('Animation component overflows signed 16-bit storage')
    return result


def quantize_rotation(rotation):
    values = [quantize(v, 4096) for v in rotation]
    # Native CalcTheta clamps a dot product above one to zero. Its zero-angle
    # Slerp branch copies the next key, visibly advancing nearly static joints.
    # Rounded quaternions must stay inside the unit sphere after compression.
    while sum(v*v for v in values) > 4096*4096:
        index = max(range(4), key=lambda i: abs(values[i]))
        values[index] -= 1 if values[index] > 0 else -1
    return values


def write_anp3(path, library, animations):
    payload = bytearray(name24(library) + struct.pack('<I', len(animations)))
    seen = set()
    for animation in animations:
        name, bones = animation['name'], animation['bones']
        if name.lower() in seen or not bones or len(bones) > 256:
            raise ValueError('Duplicate animation or invalid bone count')
        seen.add(name.lower())
        data = bytearray()
        data_size = 0
        ids = set()
        for bone in bones:
            bone_id, keys = bone['id'], bone['keys']
            position = bone.get('translation', False)
            if bone_id in ids or not 0 <= bone_id <= 65535 or not 2 <= len(keys) <= 32767:
                raise ValueError('Invalid or duplicate bone ID')
            ids.add(bone_id)
            # ANP3 type 4 is valid for every joint. GTA extracts locomotion
            # velocity only from the clump root; other joints retain their
            # sampled local translations (including humanoid IK stretch).
            data += name24(bone['name']) + struct.pack('<IIi', 4 if position else 3, len(keys), bone_id)
            previous = -1
            for key in keys:
                time = quantize(key['time'], 60)
                if not previous < time <= 32767:
                    raise ValueError('Key times must increase at native 60 Hz ticks')
                previous = time
                q = key['rotation']
                if len(q) != 4 or abs(sum(v * v for v in q) - 1) > .001:
                    raise ValueError('Invalid unit quaternion')
                data += struct.pack('<5h', *quantize_rotation(q), time)
                if position:
                    data += struct.pack('<3h', *(quantize(v, 1024) for v in key['position']))
            data_size += len(keys) * (16 if position else 10)
        payload += name24(name) + struct.pack('<III', len(bones), data_size, 1) + data
    path.write_bytes(b'ANP3' + struct.pack('<I', len(payload)) + payload)
