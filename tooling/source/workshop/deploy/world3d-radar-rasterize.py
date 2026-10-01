"""Rasterize packed world3d geometry into lightweight top-down radar tiles."""
import argparse, glob, os, struct
from PIL import Image, ImageDraw
TILE=512.0; SIZE=256
def raster(src,dst,tx,ty):
 raw=open(src,"rb").read(); magic,nv,ni=struct.unpack_from("<4sII",raw,0)
 if magic!=b"R3D1": raise ValueError("bad radar geometry")
 off=12; verts=[struct.unpack_from("<fffI",raw,off+n*16) for n in range(nv)]; off+=nv*16
 inds=struct.unpack_from("<"+"I"*ni,raw,off); tris=[]; ox,oy=tx*TILE,ty*TILE
 for n in range(0,ni-2,3):
  vs=[verts[inds[n+k]] for k in range(3)]; pts=[((v[0]-ox)*SIZE/TILE,(oy+TILE-v[1])*SIZE/TILE) for v in vs]
  area=abs((pts[1][0]-pts[0][0])*(pts[2][1]-pts[0][1])-(pts[1][1]-pts[0][1])*(pts[2][0]-pts[0][0]))
  if area<.02: continue
  z=sum(v[2] for v in vs)/3
  # The stripped world tiles contain grayscale baked occlusion, not material
  # RGB. Convert that signal into a restrained map palette and cap highlights
  # so exposed roofs never become a solid white mass.
  lum=sum(((v[3]>>16)&255)+((v[3]>>8)&255)+(v[3]&255) for v in vs)//9
  shade=0.35+0.45*(lum/255.0)
  if z < 0: base=(38,78,104)       # water / below sea level
  elif z > 14: base=(178,166,145)  # elevated roofs and structures
  else: base=(105,125,112)         # roads and ground cover
  r,g,b=(max(12,min(176,int(c*shade))) for c in base)
  tris.append((z,pts,(r,g,b,255)))
 tris.sort(key=lambda t:t[0]); im=Image.new("RGBA",(SIZE,SIZE),(20,28,35,255)); draw=ImageDraw.Draw(im)
 for _,pts,col in tris: draw.polygon(pts,fill=col)
 os.makedirs(os.path.dirname(dst),exist_ok=True)
 with open(dst,"wb") as f:
  f.write(struct.pack("<4sII",b"R3M1",SIZE,SIZE))
  for r,g,b,a in im.getdata(): f.write(struct.pack("<I",(a<<24)|(r<<16)|(g<<8)|b))
def main():
 ap=argparse.ArgumentParser();ap.add_argument("source");ap.add_argument("output");a=ap.parse_args();done=0
 for src in glob.glob(os.path.join(a.source,"*.r3d")):
  stem=os.path.splitext(os.path.basename(src))[0]
  try: tx,ty=map(int,stem.split("_"))
  except ValueError: continue
  raster(src,os.path.join(a.output,stem+".r3m"),tx,ty);done+=1;print(stem)
 print(f"rasterized {done} tiles")
if __name__=="__main__": main()
