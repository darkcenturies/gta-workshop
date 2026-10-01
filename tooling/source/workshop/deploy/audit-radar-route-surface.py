"""Measure route height against nearby packed ground triangles."""
from pathlib import Path
import struct
import numpy as np

r = np.genfromtxt('deploy/radar-turn-route.csv', delimiter=',', skip_header=1)
r = r[r[:,3] > r[-1,3]-400][::20]
cache = {}
def triangles(tx,ty):
    key=(tx,ty)
    if key in cache: return cache[key]
    p=Path(f'C:/Games/YourGame/Valkyrie-radar-tiles/{tx}_{ty}.r3g')
    if not p.exists(): return np.empty((0,3,3))
    data=p.read_bytes(); magic,nv,ng=struct.unpack_from('<4sII',data)
    v=np.frombuffer(data,dtype=np.dtype([('p','<f4',3),('c','<u4'),('uv','<f4',2)]),count=nv,offset=12)['p']
    at=12+nv*24; parts=[]
    for _ in range(ng):
        *bounds,flags,ni=struct.unpack_from('<6fII',data,at);at+=32
        idx=np.frombuffer(data,dtype='<u4',count=ni,offset=at);at+=ni*4
        if True: parts.append(v[idx].reshape(-1,3,3))
    cache[key]=np.concatenate(parts) if parts else np.empty((0,3,3))
    return cache[key]
rows=[]
for x,y,z,arc in r:
    heights=[];tx,ty=int(np.floor(x/512)),int(np.floor(y/512))
    for j in range(ty-1,ty+2):
        for i in range(tx-1,tx+2):
            t=triangles(i,j)
            if not len(t):continue
            keep=(t[:,:,0].min(1)<=x)&(t[:,:,0].max(1)>=x)&(t[:,:,1].min(1)<=y)&(t[:,:,1].max(1)>=y)
            t=t[keep]
            if not len(t):continue
            a,b,c=t[:,0],t[:,1],t[:,2]
            d=(b[:,1]-c[:,1])*(a[:,0]-c[:,0])+(c[:,0]-b[:,0])*(a[:,1]-c[:,1])
            ok=abs(d)>1e-7;a,b,c,d=a[ok],b[ok],c[ok],d[ok]
            u=((b[:,1]-c[:,1])*(x-c[:,0])+(c[:,0]-b[:,0])*(y-c[:,1]))/d
            v=((c[:,1]-a[:,1])*(x-c[:,0])+(a[:,0]-c[:,0])*(y-c[:,1]))/d
            hit=(u>=-1e-4)&(v>=-1e-4)&(u+v<=1.0001)
            h=u*a[:,2]+v*b[:,2]+(1-u-v)*c[:,2]
            heights.extend(h[hit & (abs(h-z)<2)].tolist())
    if heights:
        h=max(heights)
        rows.append((x,y,z,arc,h,h-z))
np.savetxt('deploy/radar-turn-surface.csv',rows,delimiter=',',header='x,y,route_z,arc,surface_z,above_route',comments='')
a=np.array(rows)
print('sampled',len(rows),'buried',int((a[:,-1]>0.01).sum()),'height delta range',a[:,-1].min(),a[:,-1].max())
print(a[a[:,-1]>.01][::max(1,len(a[a[:,-1]>.01])//8)].round(3))
