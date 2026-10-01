#!/usr/bin/env python3
import json
from pathlib import Path
import subprocess
import tempfile
import zipfile

ROOT = Path(__file__).resolve().parents[1]
(ROOT/'build').mkdir(exist_ok=True)
with tempfile.TemporaryDirectory(dir=ROOT/'build') as temporary:
    folder = Path(temporary)
    artifact = folder/'probe.asi'
    artifact.write_bytes(b'MZ release-package-probe')
    relative = artifact.relative_to(ROOT)
    subprocess.run([
        'python', str(ROOT/'tools'/'package-release.py'),
        '--component', 'packager-test', '--version', '0',
        '--artifact', str(relative), '--output', str(folder/'out'), '--allow-dirty'
    ], check=True)
    manifest = json.loads((folder/'out'/'packager-test-0'/'manifest.json').read_text())
    assert manifest['component'] == 'packager-test'
    assert manifest['source']['commit']
    assert manifest['files']['probe.asi']['bytes'] == len(b'MZ release-package-probe')

    # Source goes under source/ at its repository path, never beside the
    # player files, and only tracked files are accepted.
    subprocess.run([
        'python', str(ROOT/'tools'/'package-release.py'),
        '--component', 'packager-test', '--version', '1',
        '--artifact', str(relative), '--source', 'tools/package-release.py',
        '--output', str(folder/'out'), '--allow-dirty'
    ], check=True)
    manifest = json.loads((folder/'out'/'packager-test-1'/'manifest.json').read_text())
    assert 'source/tools/package-release.py' in manifest['files']
    with zipfile.ZipFile(folder/'out'/'packager-test-1.zip') as packaged:
        names = packaged.namelist()
    assert 'packager-test-1/source/tools/package-release.py' in names
    assert 'packager-test-1/package-release.py' not in names
    untracked = subprocess.run([
        'python', str(ROOT/'tools'/'package-release.py'),
        '--component', 'packager-test', '--version', '2',
        '--artifact', str(relative), '--source', str(relative),
        '--output', str(folder/'out'), '--allow-dirty'
    ])
    assert untracked.returncode != 0
print('release packager test passed')
