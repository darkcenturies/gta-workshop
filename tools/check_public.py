"""Check tracked public files for prohibited paths and obvious credential formats."""
import ast
import json
import hashlib
from pathlib import Path
import re
import subprocess
import sys
root = Path(__file__).resolve().parent.parent
paths = subprocess.check_output(['git', 'ls-files', '-z'], cwd=root).decode().split('\0')
errors = []
ida_root = root / 'docs/reverse-engineering/ida'
ida_manifest = json.loads((ida_root / 'manifest.json').read_text())
ida_allowed = set()
for item in ida_manifest:
    rel = Path(item['path'])
    if rel.is_absolute() or '..' in rel.parts:
        raise SystemExit('Invalid IDA manifest path')
    artifact = ida_root / rel
    data = artifact.read_bytes()
    if len(data) != item['size'] or hashlib.sha256(data).hexdigest() != item['sha256']:
        errors.append(str(rel) + ': IDA archive checksum mismatch')
    ida_allowed.add(artifact.relative_to(root).as_posix())
gitlinks = {}
for entry in subprocess.check_output(['git', 'ls-files', '--stage', '-z'], cwd=root).decode().split('\0'):
    if entry:
        attributes, name = entry.split('\t', 1)
        mode, sha, stage = attributes.split()
        if mode == '160000':
            gitlinks[name] = sha
if gitlinks != {'third_party/plugin-sdk': '15f15b60bbf74c106e1b496ff92c98764abf4605'}:
    errors.append('Unexpected or missing pinned plugin-sdk submodule')
sdk_url = subprocess.check_output(['git', 'config', '-f', '.gitmodules', '--get', 'submodule.third_party/plugin-sdk.url'], cwd=root).decode().strip()
if sdk_url != 'https://github.com/dk22pac/plugin-sdk.git':
    errors.append('Unexpected plugin-sdk upstream URL')
for name in filter(None, paths):
    if name in gitlinks:
        continue
    p = root / name
    if name.startswith(('component/', 'deploy/radar-release/')) or p.name in {'radar3d.cpp', 'radar3d.h', 'main_radar3d.cpp', 'radarbox.h', 'radar_logo.h', 'router.cpp', 'router.h', 'vehgraph.hpp', '3D_RADAR_DEVELOPMENT.md', 'RADAR_REVIEW_2026-09-06.md', 'RADAR3D-STATUS.md', 'RADAR3D-OCCLUSION.md'} or name.startswith('deploy/world3d-'):
        errors.append(name + ': unreleased Radar work')
    if name.startswith(('gamemodes/', 'database/', 'scriptfiles/', 'server/', 'reference/')) or p.suffix.lower() in {'.sql', '.db', '.amx', '.pem', '.key'} or p.name.startswith('.env'):
        errors.append(name + ': private/vendor artifact path')
    if p.suffix.lower() in {'.idb', '.i64'} and name not in ida_allowed:
        errors.append(name + ': unlisted IDA database')
    data = p.read_bytes()
    size_limit = 100_000_000 if name.startswith('docs/reverse-engineering/generated/') else 40_000_000
    if len(data) > size_limit:
        errors.append(name + ': unexpectedly large file')
    if b'\0' in data[:8192]:
        continue
    text = data.decode('utf-8-sig', errors='replace')
    if re.search(r'(?:gh[pousr]_[A-Za-z0-9]{30,}|github_pat_[A-Za-z0-9_]{50,}|-----BEGIN (?:RSA |OPENSSH |EC )?PRIVATE KEY-----)', text):
        errors.append(name + ': possible credential')
    if p.suffix == '.py' and 'third-party/' not in name:
        try:
            ast.parse(text, filename=name)
        except SyntaxError as exc:
            errors.append(name + ': ' + str(exc))
if errors:
    raise SystemExit('\n'.join(errors))
subprocess.run([sys.executable, str(root / 'tools/check_research.py')], check=True, cwd=root)
print('Public boundary and Python syntax checks passed.')
