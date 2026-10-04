"""Write native D3D9 RGBA texture dictionaries from a local extraction pack.

  python write_hss_txd.py SOURCE_PACK textures.json OUTPUT.txd
No third-party payloads or texture data are embedded in this script.
"""
from pathlib import Path
import sys,json,struct
from PIL import Image

source,texture_manifest,output=map(Path,sys.argv[1:4])
LIBRARY=0x1803FFFF
def chunk(kind,payload):return struct.pack('<III',kind,len(payload),LIBRARY)+payload
def texture(name,path):
    if not name.isascii() or len(name)>31:raise ValueError('Invalid native texture name')
    im=Image.open(path).convert('RGBA');im.thumbnail((512,512),Image.Resampling.LANCZOS)
    width=1<<(im.width-1).bit_length();height=1<<(im.height-1).bit_length()
    im=im.resize((width,height),Image.Resampling.LANCZOS);alpha=im.getchannel('A').getextrema()[0]<255
    levels=[];current=im
    while True:
        pixels=current.tobytes('raw','BGRA');levels.append(struct.pack('<I',len(pixels))+pixels)
        if current.size==(1,1):break
        current=current.resize((max(1,current.width//2),max(1,current.height//2)),Image.Resampling.LANCZOS)
    native=struct.pack('<IHH32s32sIIHHBBBB',9,6,0x11,name.encode().ljust(32,b'\0'),bytes(32),0x8500,21,width,height,32,len(levels),4,int(alpha))+b''.join(levels)
    return chunk(0x15,chunk(1,native)+chunk(3,b''))
textures=json.loads(texture_manifest.read_text());records=[texture(name,source/file) for name,file in textures.items()]
output.parent.mkdir(parents=True,exist_ok=True);output.write_bytes(chunk(0x16,chunk(1,struct.pack('<HH',len(records),2))+b''.join(records)+chunk(3,b'')))
print('TXD textures:',len(records),'bytes:',output.stat().st_size)
