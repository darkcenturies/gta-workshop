"""Retarget invariants independent of licensed game assets."""
import importlib.util
from pathlib import Path
import unittest

import numpy as np

spec = importlib.util.spec_from_file_location('port',Path(__file__).with_name('port-manhunt-re3.py'))
port = importlib.util.module_from_spec(spec)
spec.loader.exec_module(port)


def rig(source):
    bones = []
    for i,(name,node) in enumerate(port.MAPPING.items()):
        parent = -1 if i == 0 else 0
        matrix = np.eye(4)
        axis = np.array([1.,2.,3.]); axis /= np.linalg.norm(axis)
        angle = (i+1)*(.17 if source else -.29)
        q = np.r_[axis*np.sin(angle/2),np.cos(angle/2)]
        matrix[:3,:3] = port.qmatrix(q)
        matrix[:3,3] = [i*.01,0,i*.07]
        world = (bones[parent]['world'] if parent >= 0 else np.eye(4)) @ matrix
        bones.append(dict(name=name,node=node,parent=parent,local=matrix,world=world))
    return bones


class RetargetTests(unittest.TestCase):
    def test_rest_pose_survives_different_bone_axes(self):
        sa,gta = rig(True),rig(False)
        tracks = {b['node']:[(t,port.matrixq(b['local'][:3,:3]),None) for t in (0.,1.)] for b in sa}
        encoded = port.convert(tracks,sa,gta,sa[0]['world'][:3,3],gta[0]['local'][:3,3],
                               {name:[(0,0,0,1,0)] for name in port.MAPPING})
        blob = port.chunk(b'ANPK',port.chunk(b'INFO',b'\x01\0\0\0ped\0')+
                          port.chunk(b'NAME',b'rest\0')+encoded)
        result = port.read_anpk(blob)[1][0][3]
        for bone in gta:
            for frame in result[bone['name']]:
                np.testing.assert_allclose(port.qmatrix(np.array(frame[:4])).T,
                                           bone['local'][:3,:3],atol=1e-6)
        self.assertEqual(result['Swaist'][-1][-1],1)

    def test_partial_animation_does_not_add_leg_tracks(self):
        sa,gta = rig(True),rig(False)
        tracks = {b['node']:[(t,port.matrixq(b['local'][:3,:3]),None) for t in (0.,1.)] for b in sa}
        encoded = port.convert(tracks,sa,gta,np.zeros(3),np.zeros(3),{'Shead':[(0,0,0,1,0)]})
        blob = port.chunk(b'ANPK',port.chunk(b'INFO',b'\x01\0\0\0ped\0')+
                          port.chunk(b'NAME',b'partial\0')+encoded)
        self.assertEqual(list(port.read_anpk(blob)[1][0][3]),['Shead'])

    def test_rotation_interpolation_handles_opposite_quaternion_signs(self):
        q = np.array([0.,0.,.707106781,.707106781])
        sampled,_ = port.sample([(0,q,None),(1,-q,None)],.5)
        np.testing.assert_allclose(port.qmatrix(sampled),port.qmatrix(q),atol=1e-9)

    def test_rejects_truncated_library(self):
        with self.assertRaises(ValueError):
            port.read_anpk(b'ANPK\xff\xff\xff\xff')


if __name__ == '__main__':
    unittest.main()
