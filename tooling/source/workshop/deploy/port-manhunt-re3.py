#!/usr/bin/env python3
"""Retarget Eagle/SP-RP Manhunt ped animations to GTA III's ANPK library.

Requires Python 3 and numpy. Inputs are local game assets, never redistributed
by this tool. Keeps the GTA III animation names, order and untouched chunks.
Run with --help for required source/reference paths. Does not install files.
"""
import argparse
import bisect
import hashlib
import json
import math
import re
import struct
from pathlib import Path

import numpy as np

IDENTITY = np.eye(4)
MAPPING = {'Swaist': 1, 'Smid': 2, 'Storso': 3, 'Shead': 5,
           'Supperarml': 32, 'Slowerarml': 33, 'SLhand': 34,
           'Supperarmr': 22, 'Slowerarmr': 23, 'SRhand': 24,
           'Supperlegl': 41, 'Slowerlegl': 42, 'Sfootl': 43,
           'Supperlegr': 51, 'Slowerlegr': 52, 'Sfootr': 53}


def cstr(b):
    return b.split(b'\0')[0].decode('latin1')


def anpk_chunks(b, start=0, end=None):
    end = len(b) if end is None else end
    while start < end:
        if start + 8 > end:
            raise ValueError('Truncated ANPK chunk header')
        tag, size = struct.unpack_from('<4sI', b, start)
        tail = start + 8 + size
        padded = (tail + 3) & ~3
        if padded > end:
            raise ValueError('Truncated ANPK chunk body')
        yield tag, b[start+8:tail], b[start:padded]
        start = padded


def chunk(tag, body):
    return struct.pack('<4sI', tag, len(body)) + body + b'\0' * (-len(body) % 4)


def read_anpk(b):
    outer = list(anpk_chunks(b))
    if len(outer) != 1 or outer[0][0] != b'ANPK':
        raise ValueError('Expected one GTA III ANPK block')
    children = list(anpk_chunks(outer[0][1]))
    if children[0][0] != b'INFO':
        raise ValueError('Missing block INFO')
    count = struct.unpack_from('<I', children[0][1])[0]
    entries = []
    for i in range(1, len(children), 2):
        name, dgan = children[i:i+2]
        if name[0] != b'NAME' or dgan[0] != b'DGAN':
            raise ValueError('Expected NAME/DGAN pair')
        tracks = {}
        parts = list(anpk_chunks(dgan[1]))
        if len(parts)-1 != struct.unpack_from('<I', parts[0][1])[0]:
            raise ValueError('Wrong sequence count')
        for tag, body, raw in parts[1:]:
            if tag != b'CPAN':
                raise ValueError('Expected CPAN')
            seq = list(anpk_chunks(body))
            header = seq[0][1]
            frames = struct.unpack_from('<I', header, 28)[0]
            values = []
            if frames:
                fmt = {b'KR00': '<5f', b'KRT0': '<8f', b'KRTS': '<11f'}[seq[1][0]]
                size = struct.calcsize(fmt)
                if len(seq[1][1]) != size*frames:
                    raise ValueError('Wrong keyframe size')
                values = [struct.unpack_from(fmt, seq[1][1], j*size) for j in range(frames)]
            tracks[cstr(header)] = values
        entries.append((cstr(name[1]), name[2], dgan[2], tracks))
    if count != len(entries) or len({e[0].lower() for e in entries}) != count:
        raise ValueError('Wrong/duplicate animation count')
    return children[0][2], entries


def read_anp3(b):
    if b[:4] != b'ANP3':
        raise ValueError('Expected San Andreas ANP3')
    end = struct.unpack_from('<I', b, 4)[0] + 8
    count = struct.unpack_from('<I', b, 32)[0]
    p = 36
    out = {}
    for _ in range(count):
        name = cstr(b[p:p+24]); bones = struct.unpack_from('<I', b, p+24)[0]; p += 36
        tracks = {}
        for _ in range(bones):
            kind, frames, node = struct.unpack_from('<III', b, p+24); p += 36
            fmt = {3: '<5h', 4: '<8h'}[kind]
            size = struct.calcsize(fmt)
            values = []
            for j in range(frames):
                v = struct.unpack_from(fmt, b, p+j*size)
                q = np.array(v[:4], dtype=float)/4096
                norm = np.linalg.norm(q)
                if norm < 0.5 or norm > 1.5:
                    raise ValueError('Invalid source quaternion')
                q /= norm
                trans = np.array(v[5:8], dtype=float)/1024 if kind == 4 else None
                values.append((v[4]/60, q, trans))
            p += frames*size
            if any(values[i][0] > values[i+1][0] for i in range(len(values)-1)):
                raise ValueError('Nonmonotonic source timestamps')
            tracks[node] = values
        out[name.lower()] = tracks
    if p != end or end > len(b):
        raise ValueError('Wrong ANP3 length')
    return out


def rw_chunks(b, start, end):
    while start < end:
        tag, size, _ = struct.unpack_from('<III', b, start)
        if start+12+size > end:
            raise ValueError('Invalid RenderWare chunk')
        yield tag, start+12, start+12+size
        start += 12+size


def skeleton(b):
    cl = next(rw_chunks(b, 0, len(b)))
    fl = next(c for c in rw_chunks(b, cl[1], cl[2]) if c[0] == 14)
    parts = list(rw_chunks(b, fl[1], fl[2]))
    count = struct.unpack_from('<I', b, parts[0][1])[0]
    out = []
    for i in range(count):
        v = struct.unpack_from('<12fii', b, parts[0][1]+4+56*i)
        name = ''; node = -1
        for tag, s, e in rw_chunks(b, parts[i+1][1], parts[i+1][2]):
            if tag == 0x253f2fe:
                name = cstr(b[s:e])
            elif tag == 0x11e:
                node = struct.unpack_from('<i', b, s+4)[0]
        m = IDENTITY.copy()
        m[:3,:3] = np.array(v[:9]).reshape(3,3).T
        m[:3,3] = v[9:12]
        parent = v[12]
        if parent >= i or parent < -1:
            raise ValueError('Invalid frame hierarchy')
        world = (out[parent]['world'] if parent >= 0 else IDENTITY) @ m
        out.append(dict(name=name, node=node, parent=parent, local=m, world=world))
    return out


def sa_animation_bind(rig):
    """Use SA's animation-space root, not its DFF export-space root.

    SA's separate Root frame carries the model export axis permutation. The
    animation replaces it: a neutral biped root faces +Y with a 90-degree Z
    rotation, while the Pelvis local X axis is vertical. Including the DFF
    Root permutation in the bind correction tips a standing ped sideways.
    Keep the physical pelvis/limb bind rotations and positions unchanged.
    """
    roots = [b for b in rig if b['node'] == 0]
    if len(roots) != 1:
        raise ValueError('Expected one SA Root frame')
    roots[0]['local'] = roots[0]['local'].copy()
    roots[0]['local'][:3,:3] = qmatrix(np.array([0.,0.,math.sqrt(.5),math.sqrt(.5)]))
    for bone in rig:
        parent = bone['parent']
        bone['world'] = (rig[parent]['world'] if parent >= 0 else IDENTITY) @ bone['local']
    return rig


def qmatrix(q):
    x,y,z,w = q/np.linalg.norm(q)
    return np.array([[1-2*(y*y+z*z),2*(x*y-z*w),2*(x*z+y*w)],
                     [2*(x*y+z*w),1-2*(x*x+z*z),2*(y*z-x*w)],
                     [2*(x*z-y*w),2*(y*z+x*w),1-2*(x*x+y*y)]])


def matrixq(m):
    # Largest eigenvector gives a normalized xyzw quaternion, including 180deg.
    a = m
    k = np.array([[a[0,0]-a[1,1]-a[2,2], a[0,1]+a[1,0], a[0,2]+a[2,0], a[2,1]-a[1,2]],
                  [a[0,1]+a[1,0], a[1,1]-a[0,0]-a[2,2], a[1,2]+a[2,1], a[0,2]-a[2,0]],
                  [a[0,2]+a[2,0], a[1,2]+a[2,1], a[2,2]-a[0,0]-a[1,1], a[1,0]-a[0,1]],
                  [a[2,1]-a[1,2], a[0,2]-a[2,0], a[1,0]-a[0,1], np.trace(a)]])/3
    _, v = np.linalg.eigh(k)
    return v[:,-1]


def sample(values, time):
    times = [v[0] for v in values]
    j = max(0, min(len(values)-1, bisect.bisect_right(times, time)-1))
    a = values[j]
    if j == len(values)-1:
        return a[1], a[2]
    b = values[j+1]
    f = 0 if b[0] == a[0] else (time-a[0])/(b[0]-a[0])
    f = max(0, min(1, f))
    qa, qb = a[1], b[1]
    dot = float(qa@qb)
    if dot < 0:
        qb = -qb; dot = -dot
    if dot > .9995:
        q = qa*(1-f)+qb*f; q /= np.linalg.norm(q)
    else:
        angle = math.acos(min(1,dot))
        q = (qa*math.sin((1-f)*angle)+qb*math.sin(f*angle))/math.sin(angle)
    trans = None if a[2] is None else a[2]*(1-f)+b[2]*f
    return q, trans


def animated_world(rig, tracks, time):
    out = []
    for bone in rig:
        m = bone['local'].copy()
        values = tracks.get(bone['node'])
        if values:
            q, trans = sample(values, time)
            # ANP3 already contains runtime rotations; ANPK is conjugated on
            # load. See gta-reversed CAnimManager::LoadAnimFile_ANP23.
            m[:3,:3] = qmatrix(q)
            if trans is not None:
                m[:3,3] = trans
        parent = bone['parent']
        out.append((out[parent] if parent >= 0 else IDENTITY) @ m)
    return out


def convert(tracks, sa, gta, source_idle_pos, target_idle_pos, target_tracks):
    source_index = {b['node']: i for i,b in enumerate(sa) if b['node'] >= 0}
    target_index = {b['name']: i for i,b in enumerate(gta)}
    times = sorted({v[0] for values in tracks.values() for v in values})
    if len(times) < 2 or times[-1] <= 0:
        raise ValueError('Animation has no duration')
    if any(name not in MAPPING for name in target_tracks):
        raise ValueError('Unknown target bone track')
    # Partial animations must retain their track mask so a chat/weapon pose
    # cannot replace the legs of a simultaneously playing movement animation.
    out = {name: [] for name,values in target_tracks.items() if values}
    # Validate both reference skeletons before converting keyframes.
    for name,node in MAPPING.items():
        if node not in source_index or name not in target_index:
            raise ValueError('Reference skeleton is missing '+name)
    for time in times:
        sw = animated_world(sa, tracks, time)
        desired = {}
        for name,node in MAPPING.items():
            si,ti = source_index[node],target_index[name]
            desired[ti] = sw[si][:3,:3] @ np.linalg.inv(sa[si]['world'][:3,:3]) @ gta[ti]['world'][:3,:3]
        for name,node in MAPPING.items():
            if name not in out:
                continue
            ti = target_index[name]; parent = gta[ti]['parent']
            parent_rotation = desired.get(parent, gta[parent]['world'][:3,:3] if parent >= 0 else np.eye(3))
            rot = np.linalg.inv(parent_rotation) @ desired[ti]
            q = matrixq(rot).copy(); q[:3] *= -1  # inverse for ANPK
            previous = out[name]
            if previous and np.array(previous[-1][:4])@q < 0:
                q = -q
            if name == 'Swaist':
                si = source_index[node]
                pos = target_idle_pos + sw[si][:3,3] - source_idle_pos
                value = (*q, *pos, time)
            else:
                value = (*q, time)
            if not all(math.isfinite(float(v)) for v in value):
                raise ValueError('Nonfinite converted keyframe')
            out[name].append(value)
    body = chunk(b'INFO', struct.pack('<II',len(out),0))
    for name,values in out.items():
        header = name.encode().ljust(28,b'\0') + struct.pack('<III',len(values),0,0)
        fmt = '<8f' if name == 'Swaist' else '<5f'
        tag = b'KRT0' if name == 'Swaist' else b'KR00'
        body += chunk(b'CPAN', chunk(b'ANIM',header)+chunk(tag,b''.join(struct.pack(fmt,*v) for v in values)))
    return chunk(b'DGAN',body)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('source','target','sa-rig','iii-rig','pairs','out'):
        parser.add_argument('--'+name, type=Path, required=True)
    args = parser.parse_args()
    if args.out.resolve() in {args.source.resolve(),args.target.resolve()}:
        parser.error('Output must differ from input files')
    source = read_anp3(args.source.read_bytes())
    info, target = read_anpk(args.target.read_bytes())
    pairs = re.findall(r'\{"([^"]+)",\s*"([^"]+)"\}', args.pairs.read_text())
    if len(pairs) != 70:
        raise ValueError('Expected the SP-RP 70-animation manifest')
    sa = sa_animation_bind(skeleton(args.sa_rig.read_bytes()))
    gta = skeleton(args.iii_rig.read_bytes())
    src_idle = source.get('midle_stance', source.get('idle_stance'))
    pelvis = next(i for i,b in enumerate(sa) if b['node'] == 1)
    source_idle_pos = animated_world(sa,src_idle,0)[pelvis][:3,3]
    dest_idle = next(e for e in target if e[0].lower() == 'idle_stance')[3]['Swaist'][0]
    target_idle_pos = np.array(dest_idle[4:7])
    wanted = {name.lower(): source.get(merged.lower(), source.get(name.lower())) for name,merged in pairs}
    converted = []; skipped = []; output = info
    for name,raw_name,raw_dgan,tracks in target:
        selected = wanted.get(name.lower())
        if selected is not None:
            dgan = convert(selected,sa,gta,source_idle_pos,target_idle_pos,tracks)
            converted.append(name)
        else:
            dgan = raw_dgan
        output += raw_name+dgan
    for name,_ in pairs:
        if name.lower() not in {e[0].lower() for e in target}:
            skipped.append(name)
    result = chunk(b'ANPK',output)
    _, check = read_anpk(result)
    if [e[0] for e in check] != [e[0] for e in target]:
        raise ValueError('Changed target animation order')
    for before,after in zip(target,check):
        if before[0] not in converted and before[2] != after[2]:
            raise ValueError('Changed an unrelated animation')
        for values in after[3].values():
            if any(not math.isfinite(v) for frame in values for v in frame):
                raise ValueError('Nonfinite output')
            if any(values[i][-1] > values[i+1][-1] for i in range(len(values)-1)):
                raise ValueError('Nonmonotonic output')
    if not converted:
        raise ValueError('No Manhunt animations matched the target')
    args.out.parent.mkdir(parents=True,exist_ok=True)
    args.out.write_bytes(result)
    report = {'converted':converted,'no_gta3_equivalent':skipped,'target_animation_count':len(target),
              'sha256':hashlib.sha256(result).hexdigest(),
              'inputs':{k:{'path':str(getattr(args,k)), 'sha256':hashlib.sha256(getattr(args,k).read_bytes()).hexdigest()}
                        for k in ('source','target','sa_rig','iii_rig','pairs')},
              'validation':'ANPK parsed; names/order retained; unrelated animation chunks byte-identical. Gameplay not verified.',
              'limitations':'Shared GTA III clips affect NPCs too. No SA-only actions or knife/fight_e combat integration. Retarget uses supplied bind skeletons; check shoulders, feet, vehicle contacts in game.'}
    args.out.with_suffix('.json').write_text(json.dumps(report,indent=2)+'\n')
    print(json.dumps({k:report[k] for k in ('converted','no_gta3_equivalent','target_animation_count','sha256')},indent=2))


if __name__ == '__main__':
    main()
