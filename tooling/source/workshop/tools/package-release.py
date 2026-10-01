#!/usr/bin/env python3
"""Create an identifiable, checksummed mod artifact from an exact source tree."""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import zipfile

ROOT = Path(__file__).resolve().parents[1]


def git(*args):
    return subprocess.check_output(
        ['git', '-c', f'safe.directory={ROOT.as_posix()}', '-C', str(ROOT), *args],
        text=True).strip()


def sha256(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--component', required=True)
    parser.add_argument('--version', required=True)
    parser.add_argument('--artifact', action='append', required=True,
                        help='repository-relative file; repeat for every shipped file')
    parser.add_argument('--symbol', action='append', default=[],
                        help='private symbol file; archived separately from player files')
    parser.add_argument('--status', choices=('unverified', 'test', 'accepted'),
                        default='unverified')
    parser.add_argument('--source', action='append', default=[],
                        help='repository-relative source file shipped for review; kept under '
                             'source/ at its repository path, apart from the player files')
    parser.add_argument('--acceptance', help='repository-relative completed acceptance JSON')
    parser.add_argument('--output', type=Path, default=ROOT/'build'/'releases')
    parser.add_argument('--allow-dirty', action='store_true')
    args = parser.parse_args()

    commit = git('rev-parse', 'HEAD')
    dirty_paths = [line for line in git('status', '--porcelain').splitlines() if line]
    if dirty_paths and not args.allow_dirty:
        raise SystemExit('source tree is dirty; commit it or pass --allow-dirty for an explicitly marked local test')

    name = f'{args.component}-{args.version}'
    stage = args.output.resolve() / name
    archive = args.output.resolve() / f'{name}.zip'
    symbol_archive = args.output.resolve() / f'{name}.symbols.zip'
    if stage.exists():
        shutil.rmtree(stage)
    stage.mkdir(parents=True)

    files = {}
    for raw in args.artifact:
        source = (ROOT / raw).resolve()
        if not source.is_relative_to(ROOT) or not source.is_file():
            raise SystemExit(f'invalid artifact: {raw}')
        destination = stage / source.name
        if destination.exists():
            raise SystemExit(f'duplicate artifact name: {source.name}')
        shutil.copy2(source, destination)
        files[destination.name] = {
            'bytes': destination.stat().st_size,
            'sha256': sha256(destination),
        }

    # Source for players to read, not to install: it goes in its own folder so
    # nobody copies .cpp files into the game directory with the rest.
    for raw in args.source:
        source = (ROOT / raw).resolve()
        if not source.is_relative_to(ROOT) or not source.is_file():
            raise SystemExit(f'invalid source: {raw}')
        relative = source.relative_to(ROOT).as_posix()
        if git('ls-files', '--', relative) != relative:
            raise SystemExit(f'source is not a tracked file: {raw}')
        destination = stage / 'source' / relative
        destination.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(source, destination)
        files[f'source/{relative}'] = {
            'bytes': destination.stat().st_size,
            'sha256': sha256(destination),
        }

    acceptance = None
    if args.acceptance:
        source = (ROOT / args.acceptance).resolve()
        if not source.is_relative_to(ROOT) or not source.is_file():
            raise SystemExit(f'invalid acceptance record: {args.acceptance}')
        acceptance = json.loads(source.read_text(encoding='utf-8'))
        shutil.copy2(source, stage/'acceptance.json')
    if args.status == 'accepted':
        if acceptance is None:
            raise SystemExit('accepted status requires --acceptance')
        results = list(acceptance.get('environments', {}).values()) + \
                  list(acceptance.get('checks', {}).values())
        if any(result not in ('pass', 'na') for result in results):
            raise SystemExit('accepted status requires every acceptance result to be pass or na')

    symbols = {}
    symbol_paths = []
    for raw in args.symbol:
        source = (ROOT / raw).resolve()
        if not source.is_relative_to(ROOT) or not source.is_file():
            raise SystemExit(f'invalid symbol: {raw}')
        symbol_paths.append(source)
        symbols[source.name] = {'bytes': source.stat().st_size,
                                'sha256': sha256(source)}

    manifest = {
        'schema': 1,
        'component': args.component,
        'version': args.version,
        'status': args.status,
        'source': {'commit': commit, 'dirty': bool(dirty_paths),
                   'dirty_paths': dirty_paths},
        'build': {'configuration': 'release', 'architecture': 'x86',
                  'private_symbols': symbols},
        'acceptance': acceptance,
        'files': files,
    }
    (stage/'manifest.json').write_text(json.dumps(manifest, indent=2)+'\n', encoding='utf-8')
    (stage/'SHA256SUMS.txt').write_text(
        ''.join(f"{value['sha256']}  {name}\n" for name, value in sorted(files.items())),
        encoding='utf-8')

    args.output.resolve().mkdir(parents=True, exist_ok=True)
    with zipfile.ZipFile(archive, 'w', zipfile.ZIP_DEFLATED, compresslevel=9) as output:
        for path in sorted(p for p in stage.rglob('*') if p.is_file()):
            output.write(path, f'{name}/{path.relative_to(stage).as_posix()}')
    with zipfile.ZipFile(archive) as packaged:
        if packaged.testzip() is not None:
            raise SystemExit('archive verification failed')
    if symbol_paths:
        with zipfile.ZipFile(symbol_archive, 'w', zipfile.ZIP_DEFLATED,
                             compresslevel=9) as output:
            output.write(stage/'manifest.json', f'{name}/manifest.json')
            for source in symbol_paths:
                output.write(source, f'{name}/{source.name}')
    print(archive)
    print('SHA256', sha256(archive))
    if symbol_paths:
        print(symbol_archive)
        print('SYMBOLS SHA256', sha256(symbol_archive))


if __name__ == '__main__':
    main()
