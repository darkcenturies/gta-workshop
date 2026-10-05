import io,math,struct,sys,tempfile,unittest
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from unity_runtime_pose import Reader,read_capture,read_bind
from sa_pose_samples import coalesce_native_ticks

def text(value):
    raw=value.encode();count=len(raw);prefix=bytearray()
    while count>=128:prefix.append((count&127)|128);count>>=7
    return bytes(prefix)+bytes([count])+raw

def fixture(times=(0.,1.),matrix=None):
    matrix=matrix or (1.,0.,0.,0.,0.,1.,0.,0.,0.,0.,1.,0.)
    m=struct.pack('<12f',*matrix)
    raw=b'HSSPOS01'+struct.pack('<i',1)+text('2017.4.17f1')+text('SyntheticAvatar')+struct.pack('<i',1)
    raw+=text('Hips')+text('Hips')+struct.pack('<i',-1)+m+struct.pack('<ii',1,12)+text('SyntheticWalk')+struct.pack('<2fiB',1.,30.,2,1)
    return raw+b''.join(struct.pack('<f',t)+m for t in times)

class RuntimePoseStream(unittest.TestCase):
    def read(self,raw,bind=False):
        with tempfile.TemporaryDirectory() as directory:
            p=Path(directory)/'synthetic.hsp';p.write_bytes(raw)
            return read_bind(p) if bind else read_capture(p)
    def test_full_engine_matrix_and_metadata(self):
        capture=self.read(fixture());self.assertEqual(capture['avatar'],'SyntheticAvatar')
        self.assertEqual(capture['clips'][0]['times'],[0.,1.]);self.assertTrue(capture['clips'][0]['foot_ik'])
        self.assertEqual(capture['bones'][0]['rest'][3],(0.,0.,0.,1.))
        self.assertNotIn('clips',self.read(fixture(),True))
    def test_bounds_and_malformed_streams(self):
        for raw in (fixture()[:-1],fixture()+b'x',fixture(times=(0.,0.)),fixture(times=(-.1,1.)),fixture(times=(0.,1.1)),b'BADPOS01'+fixture()[8:]):
            with self.assertRaises(ValueError):self.read(raw)
        for matrix in ((-1.,0.,0.,0.,0.,1.,0.,0.,0.,0.,1.,0.),(math.nan,0.,0.,0.,0.,1.,0.,0.,0.,0.,1.,0.)):
            with self.assertRaises(ValueError):self.read(fixture(matrix=matrix))
    def test_multibyte_dotnet_lengths(self):
        value='joint'*70;self.assertEqual(Reader(io.BytesIO(text(value))).text(),value)
        with self.assertRaises(ValueError):Reader(io.BytesIO(b'\x80'*5)).text()
    def test_retimed_endpoint_preserved_at_shared_tick(self):
        keys=[{'time':0.,'position':[0,0,0]},{'time':.034,'position':[0,1,0]},{'time':.037,'position':[0,2,0]}]
        self.assertEqual(coalesce_native_ticks(keys),[keys[0],keys[-1]])
        with self.assertRaises(ValueError):coalesce_native_ticks([{'time':.1},{'time':0.}])
        with self.assertRaises(ValueError):coalesce_native_ticks([{'time':-.01},{'time':0.}])
        with self.assertRaises(ValueError):coalesce_native_ticks([{'time':0.},{'time':.001}])

if __name__=='__main__':unittest.main()
