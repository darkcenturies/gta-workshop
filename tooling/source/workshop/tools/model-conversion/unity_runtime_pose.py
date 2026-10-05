"""Read an explicit, locally captured Unity humanoid matrix stream.

Matrices are source coordinates, row-major 3x4 affine transforms relative to
the Animator root. This reader never approximates muscle channels or IK.
No engine, avatar, animation or captured data is bundled with the tool.
"""
from pathlib import Path
import math
import struct


class Reader:
    def __init__(self, stream):
        self.stream = stream

    def raw(self, size):
        value = self.stream.read(size)
        if len(value) != size:
            raise ValueError('Truncated evaluated pose stream')
        return value

    def fields(self, fmt):
        return struct.unpack(fmt, self.raw(struct.calcsize(fmt)))

    def integer(self, low, high):
        value, = self.fields('<i')
        if not low <= value <= high:
            raise ValueError('Evaluated pose count/index out of range')
        return value

    def text(self):
        count = 0
        for shift in range(0, 35, 7):
            value = self.raw(1)[0]
            count |= (value & 127) << shift
            if not value & 128:
                break
        else:
            raise ValueError('Invalid .NET string length')
        if count > 4096:
            raise ValueError('Evaluated pose string too long')
        value = self.raw(count).decode('utf-8')
        if '\0' in value:
            raise ValueError('Embedded null in evaluated pose name')
        return value

    def matrix(self):
        values = self.fields('<12f')
        if not all(math.isfinite(x) for x in values):
            raise ValueError('Nonfinite evaluated pose matrix')
        a, b, c, _, d, e, f, _, g, h, i, _ = values
        determinant = a*(e*i-f*h)-b*(d*i-f*g)+c*(d*h-e*g)
        if not .01 < determinant < 100:
            raise ValueError('Singular/reflected evaluated pose matrix')
        return (values[:4], values[4:8], values[8:12], (0., 0., 0., 1.))


def read_bind(path):
    return read_capture(path, bind_only=True)


def read_capture(path, bind_only=False):
    with Path(path).open('rb') as stream:
        r = Reader(stream)
        if r.raw(8) != b'HSSPOS01' or r.integer(1, 1) != 1:
            raise ValueError('Unknown evaluated pose format')
        version, avatar = r.text(), r.text()
        count = r.integer(1, 256)
        bones, names = [], set()
        for index in range(count):
            name, bone_path = r.text(), r.text()
            parent = r.integer(-1, index-1)
            if index == 0 and not name and not bone_path:
                name = 'AnimatorRoot'
            if not name or name in names or (bone_path and not bone_path.endswith(name)):
                raise ValueError('Invalid/duplicate evaluated bone name')
            names.add(name)
            bones.append({'name': name, 'path': bone_path, 'parent': parent, 'rest': r.matrix()})
        if bind_only:
            return {'unity_version': version, 'avatar': avatar, 'bones': bones,
                    'unity_engine_evaluated': True}
        clips, ids = [], set()
        for _ in range(r.integer(1, 10000)):
            source_id, name = r.integer(1, 2147483647), r.text()
            length, fps = r.fields('<2f')
            frames, ik = r.integer(2, 32767), r.raw(1)[0]
            if source_id in ids or ik not in (0, 1) or not math.isfinite(length) or not 0 < length < 546 or not 1 <= fps <= 120:
                raise ValueError('Invalid evaluated clip metadata')
            ids.add(source_id)
            times, matrices, previous = [], [], -1.
            for frame in range(frames):
                time, = r.fields('<f')
                if not 0 <= time or not previous < time <= length + .0001:
                    raise ValueError('Invalid evaluated sample time')
                previous = time
                times.append(time)
                matrices.append([r.matrix() for _ in bones])
            clips.append({'source_id': source_id, 'name': name, 'length': length,
                          'fps': fps, 'foot_ik': bool(ik), 'times': times, 'matrices': matrices})
        if stream.read(1):
            raise ValueError('Trailing evaluated pose data')
    return {'unity_version': version, 'avatar': avatar, 'bones': bones, 'clips': clips,
            'unity_engine_evaluated': True}
