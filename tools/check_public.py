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
approved = json.loads((root / 'publication/approved-files.json').read_text(encoding='utf-8'))
approved_paths = set(approved['paths'])
for name in filter(None, paths):
    if name not in approved_paths:
        errors.append(name + ': outside reviewed public file allowlist')
for name, expected in approved['implementation_sha256'].items():
    p = root / name
    if not p.is_file() or hashlib.sha256(p.read_bytes().replace(b'\r\n', b'\n')).hexdigest() != expected:
        errors.append(name + ': implementation changed; review release boundary and update approved manifest')
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
    if re.search(r'(?:^|/)(?:valkyrie-fuel|fuel|fuel-system)(?:/|[.-])', name, re.I) or p.name.lower() in {'fuel.cpp', 'fuel.h', 'main_fuel.cpp', 'build-fuel-vehicles.py', 'extract-fuel-stations.py'}:
        errors.append(name + ': private Fuel implementation or tooling')
    if name.startswith(('component/', 'deploy/radar-release/')) or p.name in {'radar3d.cpp', 'radar3d.h', 'main_radar3d.cpp', 'radarbox.h', 'radar_logo.h', 'router.cpp', 'router.h', 'vehgraph.hpp', '3D_RADAR_DEVELOPMENT.md', 'RADAR_REVIEW_2026-09-06.md', 'RADAR3D-STATUS.md', 'RADAR3D-OCCLUSION.md'} or name.startswith('deploy/world3d-'):
        errors.append(name + ': unreleased Radar work')
    if name.startswith(('gamemodes/', 'database/', 'scriptfiles/', 'server/', 'reference/')) or p.suffix.lower() in {'.sql', '.db', '.amx', '.idb', '.i64', '.pem', '.key'} or p.name.startswith('.env'):
        errors.append(name + ': private/vendor artifact path')
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
