"""Sample Unity 2017 streamed/dense/constant AnimationClip scalar channels.

Input is a locally supplied type tree, not an FBX or engine evaluation. Humanoid
channels remain muscles/IK goals here; they are not mislabeled bone rotations.
Stream coefficients describe a cubic in seconds after the preceding key.
"""
from bisect import bisect_right
import math
import struct


def binding_width(binding):
    if binding.get('isPPtrCurve'):
        raise ValueError('Object-reference animation is not a skeletal channel')
    if binding['typeID'] == 4:
        return {1: 3, 2: 4, 3: 3, 4: 3}[binding['attribute']]
    return 1


class ClipSampler:
    def __init__(self, tree):
        self.tree = tree
        muscle = tree['m_MuscleClip']
        self.start, self.stop = muscle['m_StartTime'], muscle['m_StopTime']
        if not 0 <= self.start <= self.stop < 600:
            raise ValueError('Invalid animation interval')
        clip = muscle['m_Clip']['data']
        streamed = clip['m_StreamedClip']
        self.stream_count = streamed['curveCount']
        self.streams = [[] for _ in range(self.stream_count)]
        words = streamed['data']
        raw = struct.pack('<' + 'I' * len(words), *words)
        offset = 0
        while offset < len(raw):
            if offset + 8 > len(raw):
                raise ValueError('Truncated streamed frame')
            time, count = struct.unpack_from('<fi', raw, offset)
            offset += 8
            if not 0 <= count <= self.stream_count or offset + count * 20 > len(raw):
                raise ValueError('Invalid streamed key count')
            for _ in range(count):
                index, a, b, c, value = struct.unpack_from('<i4f', raw, offset)
                offset += 20
                if not 0 <= index < self.stream_count:
                    raise ValueError('Invalid curve index')
                # Initial/final infinities carry constant initialization/end data.
                # Keep the initial value but never evaluate a cubic from -infinity.
                self.streams[index].append((time, a, b, c, value))
        for keys in self.streams:
            if not keys or any(a[0] > b[0] for a, b in zip(keys, keys[1:])):
                raise ValueError('Missing or unordered streamed curve')
        self.times = [[k[0] for k in keys] for keys in self.streams]
        self.dense = clip['m_DenseClip']
        self.constants = clip['m_ConstantClip']['data']
        dense = self.dense
        if len(dense['m_SampleArray']) != dense['m_FrameCount'] * dense['m_CurveCount']:
            raise ValueError('Invalid dense sample count')
        self.bindings = []
        count = 0
        for binding in tree['m_ClipBindingConstant']['genericBindings']:
            width = binding_width(binding)
            self.bindings.append((binding, count, width))
            count += width
        if count != self.stream_count + dense['m_CurveCount'] + len(self.constants):
            raise ValueError('Binding widths do not match scalar curve storage')

    def sample(self, time):
        if not math.isfinite(time):
            raise ValueError('Nonfinite sample time')
        time = min(self.stop, max(self.start, time))
        values = []
        for keys, times in zip(self.streams, self.times):
            i = max(0, bisect_right(times, time) - 1)
            t, a, b, c, value = keys[i]
            dt = time - t
            if abs(t) < 1e20 and (a or b or c):
                value += ((a * dt + b) * dt + c) * dt
            values.append(value)
        dense = self.dense
        width, frames = dense['m_CurveCount'], dense['m_FrameCount']
        if width:
            f = (time - dense['m_BeginTime']) * dense['m_SampleRate']
            f = min(frames - 1, max(0, f))
            left, right = int(f), min(frames - 1, int(f) + 1)
            alpha = f - left
            samples = dense['m_SampleArray']
            values.extend(samples[left * width + j] * (1 - alpha)
                          + samples[right * width + j] * alpha for j in range(width))
        values.extend(self.constants)
        if not all(math.isfinite(v) for v in values):
            raise ValueError('Nonfinite decoded channel')
        return values

    def humanoid(self, time):
        values = self.sample(time)
        return {b['attribute']: values[i] for b, i, width in self.bindings
                if b['typeID'] == 95 and b.get('customType') == 8}

    def transforms(self, time):
        values = self.sample(time)
        return {(b['path'], b['attribute']): values[i:i + width]
                for b, i, width in self.bindings if b['typeID'] == 4}
