"""Original synthetic inputs and commands for the nine standalone tools.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
import hashlib
import json
from pathlib import Path
import struct
import subprocess
import sys
import wave

NAMES = ('scripts', 'timing', 'rendering', 'population', 'settings', 'saves',
         'capture', 'diagnostics', 'restoration')


def generate(root):
    root.mkdir(parents=True, exist_ok=False)
    def text(name, value):
        (root / name).write_text(value, encoding='utf-8', newline='\n')
    def document(name, value):
        text(name, json.dumps(value, indent=2) + '\n')
    # Two authored commands and a self-branch in an independently assembled SCM header.
    start = 112
    main = struct.pack('<HBh', 16, 6, 24) + struct.pack('<HBi', 17, 1, start)
    blob = bytearray(start + len(main))
    struct.pack_into('<I', blob, 3, 32)
    struct.pack_into('<I', blob, 35, 68)
    struct.pack_into('<I', blob, 71, start)
    struct.pack_into('<IIH', blob, 76, len(blob), 0, 0)
    blob[start:] = main
    (root / 'authored.scm').write_bytes(blob)
    document('opcodes.json', {'profile': 'gta3', 'opcodes': {
        '0x10': {'name': 'AUTHORED_VALUE', 'args': ['value']},
        '0x11': {'name': 'AUTHORED_BRANCH', 'args': ['value'], 'branch_arg': 0}}})
    text('timing.csv', 'scenario,metric,unit,fps,time_s,value\n' + ''.join(
        f'linear,movement,m,{fps},{t},{2*t}\n' for fps in (30, 60, 165, 240) for t in (0, .5, 1)))
    text('population.csv', 'scenario,time_s,walkers,occupants,vehicles,near_vehicles,far_vehicles,near_walkers,far_walkers\n'
         'extended,0,100,35,45,20,25,40,60\nextended,1,100,35,45,20,25,40,60\n')
    # Solid geometric RGB images, no copied artwork.
    for name, rgb in (('reference.ppm', (10, 20, 30)), ('candidate.ppm', (20, 30, 40))):
        (root / name).write_bytes(b'P6\n2 2\n255\n' + bytes(rgb) * 4)
    meta = {'target_revision': 'synthetic-v1', 'renderer': 'synthetic', 'scene': 'solid-square',
            'camera': [0, 0, 0], 'time_s': 0, 'lighting': 'reference'}
    document('reference-meta.json', meta)
    document('candidate-meta.json', meta | {'lighting': 'candidate'})
    text('before.ini', '[Graphics]\nblur=0\n[Other]\nkeep=original\n')
    text('after.ini', '[Graphics]\nblur=0\nscale=1.5\n[Other]\nkeep=original\n')
    document('settings.json', {'settings': [
        {'section': 'Graphics', 'key': 'blur', 'type': 'bool', 'default': True},
        {'section': 'Graphics', 'key': 'scale', 'type': 'float', 'default': 1.5, 'min': 1, 'max': 3}]})
    save = bytes(range(32))
    (root / 'synthetic.save').write_bytes(save)
    document('save-contract.json', {'profile': 'synthetic-stock', 'input_sha256': hashlib.sha256(save).hexdigest(),
                                   'blocks': [{'name': 'first', 'offset': 0, 'size': 16, 'expected_size': 16},
                                              {'name': 'second', 'offset': 16, 'size': 16, 'expected_size': 16}]})
    with wave.open(str(root / 'authored.wav'), 'wb') as audio:
        audio.setnchannels(1)
        audio.setsampwidth(2)
        audio.setframerate(8000)
        audio.writeframes(struct.pack('<h', 1000) * 8000)
    document('capture.json', {'fps': 2, 'width': 2, 'height': 2,
                              'frames': ['reference.ppm', 'candidate.ppm'], 'audio': 'authored.wav',
                              'events': [{'frame': 1, 'type': 'colour-change', 'provenance': 'authored synthetic'}]})
    document('crash.json', {'target_sha256': 'a' * 64, 'image_base': '0x140000000',
                            'image_size': '0x1000', 'addresses': ['0x140000104', '0x140000300']})
    text('symbols.csv', 'rva,size,name\n0x100,16,AuthoredFunction\n')
    text('evidence.txt', 'Original synthetic evidence fixture. No historical recovery claim.\n')
    document('restoration.json', {'records': [{
        'id': 'synthetic-demo', 'title': 'Authored demo', 'target': 'synthetic',
        'observation': 'A geometric square changes colour.', 'limitations': 'No game behaviour tested.',
        'kind': 'authored-reconstruction', 'validation': 'synthetic-tested',
        'sources': [{'path': 'evidence.txt'}]}]})


def arguments(name, root):
    path = lambda item: str(root / item)
    return {
        'scripts': [path('authored.scm'), '--schema', path('opcodes.json')],
        'timing': [path('timing.csv')],
        'rendering': [path('reference.ppm'), path('candidate.ppm'), '--reference-meta', path('reference-meta.json'),
                      '--candidate-meta', path('candidate-meta.json'), '--allow-condition', 'lighting'],
        'population': [path('population.csv'), '--ped-capacity', '140', '--vehicle-capacity', '110', '--ped-reserve', '10'],
        'settings': [path('before.ini'), path('after.ini'), '--rules', path('settings.json')],
        'saves': [path('synthetic.save'), '--contract', path('save-contract.json'), '--profile', 'synthetic-stock'],
        'capture': [path('capture.json'), '--root', str(root)],
        'diagnostics': [path('crash.json'), '--symbols', path('symbols.csv'), '--target-sha256', 'a' * 64],
        'restoration': [path('restoration.json'), '--root', str(root)],
    }[name]


def demonstrate(family, output):
    name = family.removeprefix('valkyrie-')
    if name not in NAMES:
        raise ValueError('Unsupported standalone demo')
    root = output.resolve() / family
    generate(root)
    command = [sys.executable, str(Path(__file__).parent / ('valkyrie_' + name + '.py')),
               *arguments(name, root), '--output', str(root / 'report.json')]
    subprocess.run(command, check=True)
    print(json.dumps({'tool': family, 'inputs': 'Original synthetic fixtures; no game inputs.',
                      'report': str(root / 'report.json')}, indent=2))
