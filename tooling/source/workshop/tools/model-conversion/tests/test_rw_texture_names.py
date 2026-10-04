from pathlib import Path
import struct,sys,unittest
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from rw_texture_names import replace_texture_name,replace_material_color

def chunk(kind,payload):return struct.pack('<III',kind,len(payload),0x1803FFFF)+payload

def texture(name,mask='old'):
    return chunk(6,chunk(1,b'old opaque data')+chunk(2,name.encode().ljust(16,b'\0'))+chunk(2,mask.encode().ljust(16,b'\0')))

class TextureNames(unittest.TestCase):
    def test_only_texture_name_changes(self):
        opaque=chunk(1,b'old geometry old skin old')
        original=chunk(0x10,opaque+chunk(0xF,chunk(8,chunk(7,texture('old'))))+chunk(3,chunk(0x116,b'old opaque plugin')))
        changed,patches=replace_texture_name(original,'old','new')
        self.assertEqual(len(original),len(changed));self.assertEqual(len(patches),1)
        a,b=patches[0];self.assertEqual(changed[:a],original[:a]);self.assertEqual(changed[b:],original[b:])
        self.assertEqual(changed[a:b],b'new'.ljust(16,b'\0'))
        self.assertIn(b'old geometry old skin old',changed);self.assertIn(b'old opaque plugin',changed)
    def test_all_matching_texture_names_change(self):
        result,patches=replace_texture_name(chunk(7,texture('old')+texture('old')),'old','new')
        self.assertEqual(len(patches),2);self.assertEqual(result.count(b'new'),2)
    def test_missing_name_and_oversize_are_rejected(self):
        with self.assertRaises(ValueError):replace_texture_name(texture('old'),'missing','new')
        with self.assertRaises(ValueError):replace_texture_name(texture('old'),'old','x'*16)
    def test_truncated_chunk_is_rejected(self):
        with self.assertRaises(ValueError):replace_texture_name(texture('old')[:-1],'old','new')

class MaterialColours(unittest.TestCase):
    def fixture(self,refs=(-1,-1),flags=0x40):
        materials=b''.join(chunk(7,chunk(1,struct.pack('<I4BII',0,255,255,255,192,0,0))) for _ in refs)
        table=chunk(8,chunk(1,struct.pack('<I',len(refs))+struct.pack('<'+'i'*len(refs),*refs))+materials)
        return chunk(15,chunk(1,struct.pack('<I',flags))+table)
    def test_only_requested_material_rgb_changes(self):
        original=self.fixture();changed,patches=replace_material_color(original,1,(0,180,255));a,b=patches[0]
        self.assertEqual(changed[:a],original[:a]);self.assertEqual(changed[b:],original[b:]);self.assertEqual(changed[a:b],bytes((0,180,255)))
        self.assertEqual(changed[b],192)
    def test_shared_materials_and_disabled_modulation_are_rejected(self):
        with self.assertRaises(ValueError):replace_material_color(self.fixture(refs=(-1,0)),1,(0,0,0))
        with self.assertRaises(ValueError):replace_material_color(self.fixture(flags=0),1,(0,0,0))
    def test_invalid_colour_and_index_are_rejected(self):
        with self.assertRaises(ValueError):replace_material_color(self.fixture(),2,(0,0,0))
        with self.assertRaises(ValueError):replace_material_color(self.fixture(),0,(256,0,0))

if __name__=='__main__':unittest.main()
