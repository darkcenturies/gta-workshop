"""Verify public tool source, hashes, Python syntax and the approved inventory."""
import ast
import hashlib
import json
from pathlib import Path
import re
import subprocess

ROOT = Path(__file__).resolve().parents[1]
def main():
    registry = json.loads((ROOT / "tooling/registry.json").read_text())
    ids = set()
    for entry in registry["entries"]:
        assert entry["id"] not in ids
        ids.add(entry["id"])
        path = ROOT / entry["path"]
        assert path.resolve().is_relative_to(ROOT / "tooling/source")
        data = path.read_bytes()
        assert hashlib.sha256(data).hexdigest() == entry["sha256"], entry["path"]
        text = data.decode("utf-8-sig")
        assert not re.search(r'(?:gh[pousr]_|github_pat_)[A-Za-z0-9_]{20,}|-----BEGIN [A-Z ]*PRIVATE KEY', text), entry["path"]
        if path.suffix == ".py":
            ast.parse(text, filename=entry["path"])
    assert {e["path"] for e in registry["entries"]} == {
        p.relative_to(ROOT).as_posix() for p in (ROOT / "tooling/source").rglob("*")
        if p.is_file() and p.name != "LICENSE" and "__pycache__" not in p.parts
    }
    catalog = json.loads((ROOT / "docs/workshop/catalog.json").read_text())
    families = catalog["method_families"]
    assert len(families) == 10
    assert {entry["family"] for entry in registry["entries"]} == {family["id"] for family in families}
    for family in families:
        assert set(family["source_paths"]) == {
            e["path"] for e in registry["entries"] if e["family"] == family["id"]
        }
    approved = json.loads((ROOT / "publication/approved-files.json").read_text())["paths"]
    tracked = subprocess.check_output(["git", "ls-files"], cwd=ROOT, text=True).splitlines()
    assert set(approved) == set(tracked), "Stage new public paths before this check."
    assert not any(p.startswith(("client/", "deploy/", "third_party/")) for p in tracked)
    print(f'{len(ids)} tool/support entries: hashes, Python syntax and approved paths passed.')

if __name__ == "__main__":
    main()
