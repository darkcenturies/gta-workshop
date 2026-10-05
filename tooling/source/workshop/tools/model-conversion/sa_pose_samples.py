"""Decode compressed ANP3 samples for independent FK comparison.

Joint translations are absolute local positions, not Blender pose deltas.
The input must first pass validate_sa_animations.validate.
"""
import struct
from validate_sa_animations import validate

def coalesce_native_ticks(keys):
 """Retimed endpoints may share a 60 Hz tick; preserve the endpoint pose."""
 result=[];previous=-1
 for key in keys:
  tick=round(key['time']*60)
  if tick<0 or tick<previous:raise ValueError('Retimed samples are out of order')
  if tick==previous:result[-1]=key
  else:result.append(key)
  previous=tick
 if len(result)<2:raise ValueError('Retimed clip is shorter than one native tick')
 return result


def read_samples(path):
 validate(path)
 raw=path.read_bytes();offset=36;count=struct.unpack_from('<I',raw,32)[0];clips=[]
 for _ in range(count):
  name=raw[offset:offset+24].split(b'\0')[0].decode('ascii');offset+=24
  n,allocation,flags=struct.unpack_from('<III',raw,offset);offset+=12
  bones=[]
  for _ in range(n):
   label=raw[offset:offset+24].split(b'\0')[0].decode('ascii');offset+=24
   kind,frames,tag=struct.unpack_from('<IIi',raw,offset);offset+=12;keys=[]
   for _ in range(frames):
    x,y,z,w,tick=struct.unpack_from('<5h',raw,offset);offset+=10
    position=None
    if kind==4:position=[v/1024 for v in struct.unpack_from('<3h',raw,offset)];offset+=6
    keys.append({'time':tick/60,'rotation':[x/4096,y/4096,z/4096,w/4096],'position':position})
   bones.append({'id':tag,'name':label,'keys':keys})
  clips.append({'name':name,'bones':bones})
 return clips
