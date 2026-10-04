import importlib.util
from pathlib import Path
import unittest
import numpy as np
from PIL import Image

spec=importlib.util.spec_from_file_location('hair_colors',Path(__file__).parents[1]/'build_hss_hair_colors.py')
module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)

class HairColors(unittest.TestCase):
    def test_dark_source_can_become_blond_with_alpha_and_shading_preserved(self):
        source=np.array([[[4,3,2,0],[10,8,6,128],[40,30,20,255]]],dtype=np.uint8)
        changed=np.asarray(module.recolor(Image.fromarray(source),(239,195,102)))
        np.testing.assert_array_equal(changed[:,:,3],source[:,:,3])
        self.assertGreater(int(changed[0,2,0]),200)
        self.assertLess(int(changed[0,1,0]),int(changed[0,2,0]))
    def test_empty_alpha_is_finite_and_retained(self):
        source=np.zeros((2,2,4),dtype=np.uint8)
        changed=np.asarray(module.recolor(Image.fromarray(source),(255,255,255)))
        self.assertEqual(changed.dtype,np.uint8)
        np.testing.assert_array_equal(changed[:,:,3],source[:,:,3])

if __name__=='__main__':unittest.main()
