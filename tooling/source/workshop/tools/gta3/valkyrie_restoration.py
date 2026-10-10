"""Validate restoration evidence records and export a searchable catalogue.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
from pathlib import Path
from urllib.parse import urlsplit
from _common import emit, parser, read_json, run, safe_path, sha256

KINDS = {'recovered-asset', 'retained-code', 'platform-difference', 'upstream-feature',
         'documented-proposal', 'authored-reconstruction', 'unsupported'}
STATES = {'not-tested', 'inspected', 'synthetic-tested', 'native-tested', 'gameplay-tested', 'failed'}


def catalogue(data, root, search='', kind=None):
    records = data['records']
    if not isinstance(records, list) or not records:
        raise ValueError('No restoration records')
    identifiers = set()
    verified = []
    for record in records:
        for key in ('id', 'title', 'target', 'observation', 'limitations', 'kind', 'validation'):
            if not isinstance(record[key], str) or not record[key].strip():
                raise ValueError('Missing restoration field: ' + key)
        if record['id'] in identifiers or record['kind'] not in KINDS or record['validation'] not in STATES:
            raise ValueError('Duplicate identity or unknown evidence category')
        identifiers.add(record['id'])
        if not isinstance(record['sources'], list) or not record['sources']:
            raise ValueError('Every record needs evidence references, including unsupported claims')
        sources = []
        for source in record['sources']:
            if 'url' in source:
                url = source['url']
                parsed = urlsplit(url)
                if parsed.scheme != 'https' or not parsed.hostname or parsed.username or parsed.password:
                    raise ValueError('Use a public HTTPS evidence URL without credentials')
                sources.append({'url': url, 'checked_by_tool': False})
            elif 'path' in source:
                path = safe_path(root, source['path'])
                sources.append({'path': source['path'], 'sha256': sha256(path)})
            else:
                raise ValueError('Evidence source needs path or url')
        verified.append({key: record[key] for key in
                         ('id', 'title', 'target', 'observation', 'limitations', 'kind', 'validation')} | {'sources': sources})
    matched = [record for record in verified if
               (kind is None or record['kind'] == kind) and
               search.casefold() in ' '.join(str(v) for v in record.values()).casefold()]
    return {'tool': 'valkyrie-restoration', 'passed': True, 'total_records': len(verified),
            'matched_records': len(matched), 'records': matched,
            'scope': 'Evidence-category and reference validation; no URL retrieval, authenticity judgment or automatic promotion of validation levels.'}


def main():
    p = parser(__doc__)
    p.add_argument('catalogue', type=Path)
    p.add_argument('--root', type=Path, required=True)
    p.add_argument('--search', default='')
    p.add_argument('--kind', choices=sorted(KINDS))
    a = p.parse_args()
    report = catalogue(read_json(a.catalogue), a.root, a.search, a.kind)
    report['input_sha256'] = sha256(a.catalogue)
    return emit(report, a.output)


if __name__ == '__main__':
    run(main)
