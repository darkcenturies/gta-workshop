"""Shared input and report contracts for public, offline GTA research tools.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
import argparse
import hashlib
import json
import math
from pathlib import Path, PurePosixPath
import re
import sys


def _pairs(items):
    result = {}
    for key, value in items:
        if key in result:
            raise ValueError('Duplicate JSON key: ' + key)
        result[key] = value
    return result


def read_json(path):
    def invalid(value):
        raise ValueError('Nonfinite JSON constant: ' + value)
    return json.loads(Path(path).read_text(encoding='utf-8-sig'),
                      object_pairs_hook=_pairs, parse_constant=invalid)


def number(value, label, minimum=None):
    if isinstance(value, bool):
        raise ValueError(label + ' must be numeric')
    value = float(value)
    if not math.isfinite(value) or (minimum is not None and value < minimum):
        raise ValueError('Invalid ' + label)
    return value


def integer(value, label, minimum=0):
    result = number(value, label, minimum)
    if result != int(result):
        raise ValueError(label + ' must be an integer')
    return int(result)


def sha256(path):
    digest = hashlib.sha256()
    with Path(path).open('rb') as stream:
        for block in iter(lambda: stream.read(1024 * 1024), b''):
            digest.update(block)
    return digest.hexdigest()


def safe_path(root, name):
    if not isinstance(name, str) or not name or '\\' in name:
        raise ValueError('Use a nonempty relative POSIX path')
    relative = PurePosixPath(name)
    if relative.is_absolute() or '..' in relative.parts or ':' in name:
        raise ValueError('Path escapes the supplied root')
    if relative.as_posix() != name or name == '.':
        raise ValueError('Path must be normalized')
    root = Path(root).resolve()
    result = (root / name).resolve()
    if not result.is_relative_to(root):
        raise ValueError('Path resolves outside the supplied root')
    return result


def identity(value, label='sha256'):
    if not isinstance(value, str) or not re.fullmatch('[0-9a-f]{64}', value):
        raise ValueError(label + ' must be a lowercase SHA-256')
    return value


def parser(description):
    result = argparse.ArgumentParser(description=description)
    result.add_argument('--output', type=Path, help='New JSON report; never overwrite.')
    return result


def emit(report, output=None):
    report = {'schema_version': 1, **report, 'gameplay_tested_by_this_tool': False}
    data = json.dumps(report, indent=2, sort_keys=True, allow_nan=False) + '\n'
    if output is not None:
        output.parent.mkdir(parents=True, exist_ok=True)
        with output.open('x', encoding='utf-8', newline='\n') as stream:
            stream.write(data)
    else:
        print(data, end='')
    return report


def run(main):
    try:
        result = main()
    except (ValueError, OSError, KeyError, TypeError, IndexError, OverflowError, ImportError) as error:
        print('Input/report error: ' + str(error), file=sys.stderr)
        raise SystemExit(1) from None
    raise SystemExit(2 if result.get('passed') is False else 0)
