"""Check maintained GTA Workshop navigation and catalog facts without network access."""
import json
from pathlib import Path
import re
import sys
from urllib.parse import unquote, urlsplit

ROOT = Path(__file__).resolve().parent.parent
PAGES = (
    'README.md', 'AGENTS.md', 'CONTRIBUTING.md', 'PUBLICATION.md',
    'docs/README.md', 'docs/STRUCTURE.md', 'docs/AGENT_START.md',
    'docs/GTA-WORKSHOP.md', 'docs/REPOSITORIES.md', 'docs/MODS.md',
    'docs/BUILDING.md', 'docs/PLUGIN_SDK.md', 'docs/RESEARCH_WORKFLOW.md',
    'docs/INTEGRATION.md', 'docs/workshop/README.md',
    'docs/workshop/CATALOG.md', 'docs/workshop/EXAMPLES.md',
    'docs/workshop/PUBLICATION-BACKLOG.md', 'research/README.md',
    'research/finding-template.md', 'research/dryxio-catalog.md',
)
MAPS = ('ownership', 'task-flow', 'dependencies', 'dryxio-routes', 'publication')


def visible_markdown(text):
    """Skip fenced examples so illustrative paths are not treated as navigation."""
    return re.sub(r'^(`{3,}|~{3,})[^\n]*\n.*?^\1\s*$', '', text,
                  flags=re.MULTILINE | re.DOTALL)


def anchors(text):
    found = set(re.findall(r'<a\s+id=["\']([^"\']+)["\']', text))
    seen = {}
    for heading in re.findall(r'^#{1,6}\s+(.+?)\s*#*$', visible_markdown(text), re.MULTILINE):
        label = re.sub(r'\[([^]]+)\]\([^)]*\)', r'\1', heading).lower()
        slug = re.sub(r'[^\w\s-]', '', label, flags=re.UNICODE).replace(' ', '-')
        duplicate = seen.get(slug, 0)
        seen[slug] = duplicate + 1
        found.add(slug + (f'-{duplicate}' if duplicate else ''))
    return found


def check():
    errors = []
    link_count = 0
    for name in PAGES:
        page = ROOT / name
        text = page.read_text(encoding='utf-8-sig')
        for raw in re.findall(r'\]\(([^)\n]+)\)', visible_markdown(text)):
            target = raw.split(' "', 1)[0].strip().strip('<>')
            url = urlsplit(target)
            if url.scheme or url.netloc:
                continue  # Private/external URLs need contextual review, not anonymous probing.
            dest = (page.parent / unquote(url.path)).resolve() if url.path else page
            link_count += 1
            if not dest.is_relative_to(ROOT) or not dest.exists():
                errors.append(f'{name}: missing/outside local target {target}')
            elif url.fragment and dest.suffix == '.md':
                if unquote(url.fragment) not in anchors(dest.read_text(encoding='utf-8-sig')):
                    errors.append(f'{name}: missing anchor {target}')

    catalog = json.loads((ROOT / 'docs/workshop/catalog.json').read_text(encoding='utf-8'))
    dryxio = json.loads((ROOT / 'research/dryxio-catalog.json').read_text(encoding='utf-8'))
    components = catalog['components']
    ids = [item['id'] for item in components]
    if len(ids) != len(set(ids)):
        errors.append('catalog.json: duplicate component IDs')
    readable = (ROOT / 'docs/workshop/CATALOG.md').read_text(encoding='utf-8')
    component_anchors = set(re.findall(r'<a id="component-([^"]+)"></a>', readable))
    if component_anchors != set(ids):
        errors.append('CATALOG.md: component records do not match catalog.json IDs')
    references = {item['name'] for item in dryxio['projects']}
    for item in components:
        owner = item['owner']
        if owner not in catalog['owners']:
            errors.append(f"{item['id']}: unknown source owner {owner}")
        else:
            record = re.search(
                rf'<a id="component-{re.escape(item["id"])}"></a>(.*?)(?=<a id="component-|\Z)',
                readable, re.DOTALL)
            if record:
                for value in (item['name'], item['source_path'], item['source_status'],
                              item['target'], catalog['owners'][owner]['repository']):
                    if value not in record.group(1):
                        errors.append(f"{item['id']}: human catalog differs from structured record")
        if owner == 'public':
            source = (ROOT / item['source_path']).resolve()
            if not source.is_relative_to(ROOT) or not source.exists():
                errors.append(f"{item['id']}: missing public entrypoint")
        for ref in item['dryxio_references']:
            if ref not in references:
                errors.append(f"{item['id']}: unknown Dryxio reference {ref}")
    if catalog['owners']['public']['repository'] != 'darkcenturies/gta-workshop':
        errors.append('catalog.json: public owner uses the wrong repository')
    readme = (ROOT / 'README.md').read_text(encoding='utf-8')
    for pattern, expected, label in (
        (r'(\d+) components with owners', len(components), 'component'),
        (r"Dryxio's (\d+) cataloged GTA repositories", len(references), 'Dryxio'),
    ):
        match = re.search(pattern, readme)
        if not match or int(match.group(1)) != expected:
            errors.append(f'README.md: {label} count differs from its inventory')
    for name in MAPS:
        for suffix in ('mmd', 'svg'):
            if not (ROOT / f'docs/workshop/{name}.{suffix}').is_file():
                errors.append(f'Missing {name}.{suffix} atlas artifact')
    return errors, link_count, len(components), len(references)


if __name__ == '__main__':
    errors, links, components, references = check()
    if errors:
        sys.exit('\n'.join(errors))
    print(f'Workshop verified: {len(PAGES)} entry-point pages, {links} local links, '
          f'{components} components, {references} Dryxio references, five map pairs.')
