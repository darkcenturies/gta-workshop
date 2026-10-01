import struct, os, io

P = "/mnt/c/Games/Project Eagle/models/empire_menu.txd"
OUT = "/mnt/c/Users/YourUser/AppData/Local/Temp/claude/C--Users-Admin/c5bf791a-1425-4fb4-b893-f3e881df0347/scratchpad/empire_icons"
os.makedirs(OUT, exist_ok=True)

d = open(P, "rb").read()

def walk(start, end, out):
    off = start
    while off + 12 <= end:
        sid, size, _ = struct.unpack_from("<III", d, off)
        body = off + 12
        if sid == 0x16:
            walk(body, min(body + size, end), out)
        elif sid == 0x15:
            out.append(body)
        off = body + size
        if size == 0:
            break
    return out

def dds_header(w, h, fourcc, payload_len):
    # Wrap the raw DXT payload in a DDS header so Pillow will decode it.
    hdr = bytearray(128)
    hdr[0:4] = b"DDS "
    struct.pack_into("<I", hdr, 4, 124)
    struct.pack_into("<I", hdr, 8, 0x1 | 0x2 | 0x4 | 0x1000 | 0x80000)  # caps|h|w|pixelformat|linearsize
    struct.pack_into("<I", hdr, 12, h)
    struct.pack_into("<I", hdr, 16, w)
    struct.pack_into("<I", hdr, 20, payload_len)
    struct.pack_into("<I", hdr, 76, 32)
    struct.pack_into("<I", hdr, 80, 0x4)      # DDPF_FOURCC
    hdr[84:88] = fourcc
    struct.pack_into("<I", hdr, 108, 0x1000)  # DDSCAPS_TEXTURE
    return bytes(hdr)

try:
    from PIL import Image
    have_pil = True
except ImportError:
    have_pil = False
    print("Pillow not available - writing .dds instead")

for body in walk(0, len(d), []):
    p = body + 12
    name = d[p+8:p+40].split(b"\0")[0].decode("latin-1", "replace")
    rasterfmt, d3d = struct.unpack_from("<II", d, p+72)
    w, h, depth_, levels, rtype, flags = struct.unpack_from("<HHBBBB", d, p+80)
    q = p + 88
    datasize = struct.unpack_from("<I", d, q)[0]
    payload = d[q+4 : q+4+datasize]
    fourcc = struct.pack("<I", d3d)

    blob = dds_header(w, h, fourcc, datasize) + payload
    if have_pil:
        try:
            im = Image.open(io.BytesIO(blob))
            im = im.convert("RGBA")
            im.save(f"{OUT}/{name}.png")
            print(f"  {name:<12} {w}x{h}  -> {name}.png")
            continue
        except Exception as e:
            print(f"  {name:<12} PIL failed: {e}")
    open(f"{OUT}/{name}.dds", "wb").write(blob)
    print(f"  {name:<12} {w}x{h}  -> {name}.dds")

print("\nwrote to", OUT)
