"""Run with Blender --background --factory-startup --python-exit-code 1."""
from pathlib import Path
import sys
import unittest
from mathutils import Matrix, Vector

sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from hss_fitting import fit_influence


class TorsoContinuity(unittest.TestCase):
    def test_changing_torso_weights_does_not_move_the_rest_surface(self):
        # Different source/target spine and neck lengths previously moved the
        # same surface point differently as its adjacent weights changed.
        names=[' Pelvis',' Spine',' Spine1',' Neck',' Head','L breast','R breast']
        source=[0,.10,.34,.62,.69,.37,.37]
        donor=[0,0,.28,.55,.69,.41,.41]
        frames={n:(Matrix.Rotation(.1*i,3,'Y'),Vector((s,0,0)),Vector((t,0,0)))
                for i,(n,s,t) in enumerate(zip(names,source,donor))}
        frames[' Pelvis']=(Matrix.Identity(3),Vector((0,1,0)),Vector((0,0,0)))
        for point in [Vector((.1,1,.1)),Vector((.62,1,0)),Vector((.4,1,.2))]:
            expected=point-Vector((0,1,0))
            for left in names:
                for right in names:
                    for weight in [0,.25,.5,.75,1]:
                        result=fit_influence(point,left,frames)*weight+fit_influence(point,right,frames)*(1-weight)
                        self.assertLess((result-expected).length,1e-6)

    def test_limb_rotation_still_fits_the_donor(self):
        # Source arm along +X fits a donor arm along +Y at a displaced joint.
        frames={' L UpperArm':(Matrix.Rotation(1.57079632679,3,'Z'),Vector((1,0,0)),Vector((2,3,4)))}
        result=fit_influence(Vector((2,0,0)),' L UpperArm',frames)
        self.assertLess((result-Vector((2,4,4))).length,1e-6)


suite=unittest.defaultTestLoader.loadTestsFromTestCase(TorsoContinuity)
if not unittest.TextTestRunner(verbosity=2).run(suite).wasSuccessful():
    raise RuntimeError('Torso fitting regression failed')
