"""Inspect a combined ASI without executing it or loading it into GTA."""
import argparse
import ctypes
import hashlib
from pathlib import Path
import struct

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('asi', type=Path)
path = parser.parse_args().asi.resolve()
data = path.read_bytes()
pe = struct.unpack_from('<I', data, 0x3c)[0]
assert data[:2] == b'MZ' and data[pe:pe+4] == b'PE\0\0', 'Invalid executable'
assert struct.unpack_from('<H', data, pe+4)[0] == 0x14c, 'Expected x86'
assert b'Doctor & Crashfix' in data, 'Missing combined Doctor identity'
assert b'Valkyrie Crashfix 3.0.0-test starting' in data, 'Missing native Crashfix implementation'
for forbidden in (b'PECore.asi', b'projecteaglemod.games', b'Project Silent Hill', b'valkyrie-phone-silent-hill'):
    assert forbidden not in data, 'Retired product reference: ' + repr(forbidden)
kernel = ctypes.WinDLL('kernel32', use_last_error=True)
kernel.LoadLibraryExW.argtypes = (ctypes.c_wchar_p, ctypes.c_void_p, ctypes.c_uint32)
kernel.LoadLibraryExW.restype = ctypes.c_void_p
kernel.FreeLibrary.argtypes = (ctypes.c_void_p,)
callback_type = ctypes.WINFUNCTYPE(ctypes.c_int, ctypes.c_void_p, ctypes.c_void_p, ctypes.c_ssize_t)
types = []
@callback_type
def collect(module, resource, parameter):
    types.append(resource)
    return 1
kernel.EnumResourceTypesW.argtypes = (ctypes.c_void_p, callback_type, ctypes.c_ssize_t)
module = kernel.LoadLibraryExW(str(path), None, 0x22)  # DATAFILE | IMAGE_RESOURCE; never call DllMain.
if not module:
    raise ctypes.WinError(ctypes.get_last_error())
try:
    if not kernel.EnumResourceTypesW(module, collect, 0):
        raise ctypes.WinError(ctypes.get_last_error())
finally:
    kernel.FreeLibrary(module)
assert not set(types) & {2, 3, 14}, 'Bitmap/icon artwork resource found'
assert 10 in types, 'Missing diagnostic rule resources'
print('Combined x86 Doctor & Crashfix verified; no bitmap/icon resources; SHA-256 ' + hashlib.sha256(data).hexdigest())
