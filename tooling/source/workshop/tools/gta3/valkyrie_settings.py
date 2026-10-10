"""Audit INI values and migration preservation against explicit rules.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
import configparser
from pathlib import Path
from _common import emit, number, parser, read_json, run, sha256


def load(path):
    config = configparser.ConfigParser(interpolation=None, strict=True)
    try:
        config.read_string(path.read_text(encoding='utf-8-sig'))
    except configparser.Error as error:
        raise ValueError('Ambiguous or invalid INI: ' + str(error)) from None
    if config.defaults():
        raise ValueError('DEFAULT inheritance is outside this explicit-section contract')
    return {(section, key): value for section in config.sections() for key, value in config[section].items()}


def value(raw, rule):
    kind = rule['type']
    if kind == 'bool':
        if isinstance(raw, bool):
            result = raw
        elif str(raw).casefold() in ('0', '1', 'true', 'false', 'on', 'off', 'yes', 'no'):
            result = str(raw).casefold() in ('1', 'true', 'on', 'yes')
        else:
            raise ValueError('Invalid boolean')
    elif kind in ('int', 'float'):
        result = number(raw, 'setting')
        if kind == 'int':
            if result != int(result):
                raise ValueError('Setting must be an integer')
            result = int(result)
        if result < rule.get('min', float('-inf')) or result > rule.get('max', float('inf')):
            raise ValueError('Setting outside declared range')
    elif kind == 'string':
        result = str(raw)
    else:
        raise ValueError('Unknown setting type')
    if 'choices' in rule and result not in rule['choices']:
        raise ValueError('Setting outside declared choices')
    return result


def audit(before, after, rules, allowed=(), defaults=False):
    observed = set()
    results = []
    for rule in rules['settings']:
        key = (rule['section'], rule['key'].lower())
        if key in observed or not all(key):
            raise ValueError('Duplicate or empty setting identity')
        observed.add(key)
        name = '.'.join(key)
        default = value(rule['default'], rule)
        expected = default
        prior_valid = False
        if key in before and not defaults:
            try:
                expected = value(before[key], rule)
                prior_valid = True
            except ValueError:
                pass
        try:
            actual = value(after[key], rule)
            valid = True
            error = None
        except (KeyError, ValueError) as issue:
            actual, valid, error = None, False, str(issue)
        passed = valid and (actual == expected or name in allowed)
        results.append({'setting': name, 'expected': expected, 'actual': actual,
                        'prior_value_valid': prior_valid, 'restart_required': bool(rule.get('restart_required', False)),
                        'passed': passed, 'error': error})
    if not results:
        raise ValueError('No setting rules')
    unrelated = []
    for key in sorted(before.keys() | after.keys()):
        if key in observed:
            continue
        if before.get(key) != after.get(key):
            name = '.'.join(key)
            unrelated.append({'setting': name, 'before': before.get(key), 'after': after.get(key),
                              'allowed': name in allowed})
    return {'tool': 'valkyrie-settings', 'passed': all(row['passed'] for row in results)
            and all(row['allowed'] for row in unrelated), 'settings': results, 'unrelated_changes': unrelated,
            'scope': 'INI contract and migration audit; no native menu input, device recreation or runtime selection is exercised.'}


def main():
    p = parser(__doc__)
    p.add_argument('before', type=Path)
    p.add_argument('after', type=Path)
    p.add_argument('--rules', type=Path, required=True)
    p.add_argument('--allow-change', action='append', default=[], help='Section.lowercasekey')
    p.add_argument('--expect-defaults', action='store_true')
    a = p.parse_args()
    report = audit(load(a.before), load(a.after), read_json(a.rules), a.allow_change, a.expect_defaults)
    report['input_sha256'] = {'before': sha256(a.before), 'after': sha256(a.after), 'rules': sha256(a.rules)}
    return emit(report, a.output)


if __name__ == '__main__':
    run(main)
