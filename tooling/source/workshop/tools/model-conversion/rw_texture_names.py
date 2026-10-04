"""Replace RenderWare texture-name strings without rewriting geometry or skin.

Inputs are ordinary, non-native DFF streams. Only the first string child of a
Texture chunk is eligible; opaque structs and plugin payloads are untouched.
Names must fit the existing string allocation. No game inputs are bundled.
"""
import re
import struct

CONTAINERS={0x10,0x0E,0x1A,0x0F,0x08,0x07,0x06,0x03,0x14}

def replace_texture_name(data,old,new):
    for name in (old,new):
        if not re.fullmatch(r'[A-Za-z0-9_]+',name):raise ValueError('Invalid texture name')
    result=bytearray(data);patches=[]
    def walk(start,end):
        offset=start
        while offset<end:
            if end-offset<12:raise ValueError('Truncated chunk header')
            kind,size,version=struct.unpack_from('<III',data,offset)
            a=offset+12;b=a+size
            if b>end:raise ValueError('Chunk exceeds parent boundary')
            if kind==0x06:
                child=a;found=False
                while child<b:
                    if b-child<12:raise ValueError('Truncated texture child')
                    ck,cs,cv=struct.unpack_from('<III',data,child);ca=child+12;cb=ca+cs
                    if cb>b:raise ValueError('Texture child exceeds boundary')
                    if ck==0x02 and not found:
                        found=True
                        payload=data[ca:cb];value=payload.split(b'\0',1)[0]
                        if value==old.encode('ascii'):
                            encoded=new.encode('ascii')
                            if len(encoded)>=cs:raise ValueError('Replacement exceeds string allocation')
                            result[ca:cb]=encoded+b'\0'*(cs-len(encoded));patches.append((ca,cb))
                    child=cb
            elif kind in CONTAINERS:walk(a,b)
            offset=b
    walk(0,len(data))
    if not patches:raise ValueError('Texture name not found: '+old)
    return bytes(result),patches


def replace_material_color(data,material_index,rgb):
    """Patch one unique material's RGB, retaining its authored alpha.

    The material list must declare independent entries (all indices -1), as
    emitted by the evaluated exporter. Geometry modulation must already be on.
    """
    if material_index<0 or len(rgb)!=3 or any(not isinstance(v,int) or not 0<=v<=255 for v in rgb):
        raise ValueError('Invalid material index or RGB')
    materials=[];lists=[];geometry_flags=[]
    def walk(start,end,parent=None):
        offset=start
        while offset<end:
            if end-offset<12:raise ValueError('Truncated chunk header')
            kind,size,version=struct.unpack_from('<III',data,offset);a=offset+12;b=a+size
            if b>end:raise ValueError('Chunk exceeds parent boundary')
            if kind==1 and parent==7:
                if size<16:raise ValueError('Truncated material struct')
                materials.append(a+4)
            if kind==1 and parent==8:
                if size<4:raise ValueError('Truncated material list')
                count=struct.unpack_from('<I',data,a)[0]
                if size!=4+4*count:raise ValueError('Invalid material list')
                refs=struct.unpack_from('<'+'i'*count,data,a+4)
                if any(i!=-1 for i in refs):raise ValueError('Shared material references are unsupported')
                lists.append(count)
            if kind==1 and parent==15:
                if size<4:raise ValueError('Truncated geometry struct')
                geometry_flags.append(struct.unpack_from('<I',data,a)[0])
            if kind in CONTAINERS:walk(a,b,kind)
            offset=b
    walk(0,len(data))
    if len(lists)!=1 or len(geometry_flags)!=1 or not geometry_flags[0]&0x40:
        raise ValueError('Expected one modulated geometry/material list')
    if lists[0]!=len(materials) or material_index>=len(materials):raise ValueError('Material index out of bounds')
    a=materials[material_index];result=bytearray(data);result[a:a+3]=bytes(rgb)
    return bytes(result),[(a,a+3)]
