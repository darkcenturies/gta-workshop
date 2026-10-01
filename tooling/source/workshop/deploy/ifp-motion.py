#!/usr/bin/env python3
# Report the root-bone MOTION of each object across its whole track: first frame,
# last frame, and the max displacement from frame 0. Tells us which cutscene
# objects are parked (static) vs. actually driving/moving.
import struct, os, sys, math

path = None
for c in (r"C:\Users\YourUser\sp-rp\client-mod\sprp-cutscene-anims\anims\prolog3.ifp",
          r"/mnt/c/Users/YourUser/sp-rp/client-mod/sprp-cutscene-anims/anims/prolog3.ifp"):
    if os.path.isfile(c):
        path = c; break
if len(sys.argv) > 1 and os.path.isfile(sys.argv[1]):
    path = sys.argv[1]
data = open(path, "rb").read()

def tag(o): return data[o:o+4]
def u32(o): return struct.unpack_from("<I", data, o)[0]
def f(o):   return struct.unpack_from("<f", data, o)[0]
def find_tag(t, start):
    o = start
    while o < len(data) - 8:
        if tag(o) == t: return o
        o += 1
    return -1

o = find_tag(b"NAME", 0)
print(f"{'object':14s} {'frames':>6s}  first(x,y,z)                last(x,y,z)                 maxDisp")
while o != -1:
    nsz = u32(o+4)
    name = data[o+8:o+8+nsz].split(b"\x00")[0].decode("latin-1","replace")
    nxt = find_tag(b"NAME", o+8)
    anim = find_tag(b"ANIM", o+8)
    fcount = u32(anim+8+28)
    krt0 = find_tag(b"KRT0", anim)
    kr00 = find_tag(b"KR00", anim)
    if krt0 != -1 and (kr00 == -1 or krt0 < kr00):
        base = krt0 + 8
        stride = 32  # quat(4f)+trans(3f)+time(1f)
        def trans(i):
            b = base + i*stride + 16
            return (f(b), f(b+4), f(b+8))
        n = fcount
        p0 = trans(0); pl = trans(n-1)
        maxd = 0.0
        for i in range(n):
            x,y,z = trans(i)
            d = math.sqrt((x-p0[0])**2 + (y-p0[1])**2 + (z-p0[2])**2)
            if d > maxd: maxd = d
        print(f"{name:14s} {n:6d}  [{p0[0]:7.2f},{p0[1]:7.2f},{p0[2]:6.2f}]   "
              f"[{pl[0]:7.2f},{pl[1]:7.2f},{pl[2]:6.2f}]   {maxd:6.2f}")
    else:
        print(f"{name:14s} {fcount:6d}  (rotation-only root, no translation)")
    o = nxt
