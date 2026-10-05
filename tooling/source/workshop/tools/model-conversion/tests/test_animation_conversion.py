import copy
import json
from pathlib import Path
import struct
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from unity_animation_curves import ClipSampler
from sa_animation_writer import write_anp3
from sa_animation_writer import quantize_rotation
from validate_sa_animations import validate


class Curves(unittest.TestCase):
    def tree(self):
        # A cubic scalar, a linearly sampled dense scalar, then a constant.
        raw = struct.pack('<fi', 0., 1) + struct.pack('<i4f', 0, 1., 2., 3., 4.)
        raw += struct.pack('<fi', 1., 1) + struct.pack('<i4f', 0, 0., 0., 0., 10.)
        return {'m_MuscleClip': {'m_StartTime': 0., 'm_StopTime': 1., 'm_Clip': {'data': {
            'm_StreamedClip': {'curveCount': 1, 'data': list(struct.unpack('<' + 'I' * (len(raw)//4), raw))},
            'm_DenseClip': {'m_FrameCount': 2, 'm_CurveCount': 1, 'm_SampleRate': 1., 'm_BeginTime': 0., 'm_SampleArray': [2., 6.]},
            'm_ConstantClip': {'data': [7.]},
        }}}, 'm_ClipBindingConstant': {'genericBindings': [
            {'typeID': 95, 'customType': 8, 'attribute': n} for n in (42, 43, 44)]}}

    def test_known_cubic_dense_constant_values(self):
        sampler = ClipSampler(self.tree())
        self.assertEqual(sampler.sample(0), [4, 2, 7])
        self.assertEqual(sampler.sample(.5), [6.125, 4, 7])
        self.assertEqual(sampler.sample(1), [10, 6, 7])
        self.assertEqual(sampler.humanoid(.5), {42: 6.125, 43: 4, 44: 7})

    def test_rejects_width_mismatch_and_truncated_stream(self):
        tree = self.tree();tree['m_ClipBindingConstant']['genericBindings'].pop()
        with self.assertRaises(ValueError): ClipSampler(tree)
        tree = self.tree();tree['m_MuscleClip']['m_Clip']['data']['m_StreamedClip']['data'].pop()
        with self.assertRaises(ValueError): ClipSampler(tree)

    def test_scalar_types_are_not_bone_rotations(self):
        self.assertEqual(ClipSampler(self.tree()).transforms(.5), {})


class Native(unittest.TestCase):
    def test_compression_cannot_trigger_native_zero_angle_slerp(self):
        import math
        # Neighbouring unit samples are close enough that outward rounding
        # previously made their compressed dot product exceed one.
        a=[math.sin(.015),0,0,math.cos(.015)]
        b=[math.sin(.016),0,0,math.cos(.016)]
        aq,bq=quantize_rotation(a),quantize_rotation(b)
        self.assertLessEqual(sum(v*v for v in aq),4096*4096)
        self.assertLessEqual(sum(x*y for x,y in zip(aq,bq)),4096*4096)
        self.assertLess(max(abs(x/4096-y) for x,y in zip(aq,a)),.0005)
    def clip(self):
        return [{'name': 'idle', 'bones': [{'name': 'Root', 'id': 0, 'translation': True,
            'keys': [{'time': i/30, 'rotation': [0, 0, 0, 1], 'position': [0, 0, .1]} for i in range(2)]},
            {'name': 'helper', 'id': 302, 'keys': [{'time': i/30, 'rotation': [0, 0, 0, 1]} for i in range(2)]}]}]

    def test_roundtrip_allocation_compression_and_hanim_tags(self):
        with tempfile.TemporaryDirectory() as folder:
            path=Path(folder)/'test.ifp';write_anp3(path,'test',self.clip())
            result=validate(path,{0,302});self.assertEqual(result['clips'][0]['keys'],4)
            raw=bytearray(path.read_bytes());struct.pack_into('<I',raw,64,0);path.write_bytes(raw)
            with self.assertRaises(ValueError): validate(path)

    def test_rejects_rounded_rotation_that_skips_native_interpolation(self):
        with tempfile.TemporaryDirectory() as folder:
            path=Path(folder)/'test.ifp';write_anp3(path,'test',self.clip())
            raw=bytearray(path.read_bytes());struct.pack_into('<4h',raw,108,0,0,1,4096);path.write_bytes(raw)
            with self.assertRaisesRegex(ValueError,'unit sphere'):validate(path)

    def test_native_sixtieth_second_clock_and_signed_limit(self):
        with tempfile.TemporaryDirectory() as folder:
            path=Path(folder)/'test.ifp';write_anp3(path,'test',self.clip())
            # Header 72, root sequence header 36, each translated key 16.
            self.assertEqual(struct.unpack_from('<h',path.read_bytes(),132)[0],2)
            self.assertAlmostEqual(validate(path)['clips'][0]['duration'],1/30)
            clips=self.clip();clips[0]['bones'][0]['keys'][1]['time']=32768/60
            with self.assertRaises(ValueError): write_anp3(path,'test',clips)

    def test_reports_native_forward_travel_in_units_per_second(self):
        with tempfile.TemporaryDirectory() as folder:
            path=Path(folder)/'test.ifp';clips=self.clip()
            for k in clips[0]['bones'][0]['keys']:k['position'][1]=3*k['time']
            write_anp3(path,'test',clips)
            self.assertAlmostEqual(validate(path)['clips'][0]['root_forward_speed'],3,delta=.02)
            clips[0]['bones'].reverse()
            write_anp3(path,'test',clips)
            self.assertAlmostEqual(validate(path)['clips'][0]['root_forward_speed'],3,delta=.02)

    def test_preserves_nonroot_translation_and_rejects_overflow(self):
        with tempfile.TemporaryDirectory() as folder:
            path=Path(folder)/'test.ifp';clips=self.clip();clips[0]['bones'][1]['translation']=True
            for i,k in enumerate(clips[0]['bones'][1]['keys']):k['position']=[.25,i*.5,1.]
            write_anp3(path,'test',clips)
            from sa_pose_samples import read_samples
            samples=read_samples(path)
            self.assertEqual(samples[0]['bones'][1]['keys'][1]['position'],[.25,.5,1.])
            self.assertEqual(validate(path)['clips'][0]['root_forward_speed'],0)
            clips=self.clip();clips[0]['bones'][0]['keys'][0]['position'][0]=100
            with self.assertRaises(ValueError): write_anp3(path,'test',clips)

    def test_rejects_duplicate_times_tags_and_names(self):
        with tempfile.TemporaryDirectory() as folder:
            path=Path(folder)/'test.ifp';clips=self.clip();clips[0]['bones'][0]['keys'][1]['time']=0
            with self.assertRaises(ValueError): write_anp3(path,'test',clips)
            clips=self.clip();clips[0]['bones'][1]['id']=0
            with self.assertRaises(ValueError): write_anp3(path,'test',clips)
            clips=self.clip();clips.append(copy.deepcopy(clips[0]))
            with self.assertRaises(ValueError): write_anp3(path,'test',clips)


if __name__ == '__main__': unittest.main()
