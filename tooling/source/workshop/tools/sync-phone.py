"""Check/apply the reviewed phone export; never mirror a repository or delete files.

python tools/sync-phone.py C:/Users/YourUser/valkyrie-phone [--apply]
The default reports drift. Changes outside the explicit, hashed manifest are
never exported. Public build scripts and notices are maintained separately.
"""
from pathlib import Path, PurePosixPath
import argparse
import hashlib
import json
import subprocess

ROOT = Path(__file__).resolve().parents[1]

def digest(data):
    # Git checkouts may differ in text line endings; binary content stays exact.
    if b"\0" not in data:
        data = data.replace(b"\r\n", b"\n")
    return hashlib.sha256(data).hexdigest()

def contained(root, relative):
    part = PurePosixPath(relative)
    if part.is_absolute() or ".." in part.parts or ":" in relative:
        raise ValueError(f"Unsafe export path: {relative}")
    path = (root / relative).resolve()
    if not path.is_relative_to(root.resolve()):
        raise ValueError(f"Export escapes checkout: {relative}")
    return path

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("phone", type=Path)
    parser.add_argument("--apply", action="store_true")
    args = parser.parse_args()
    target = args.phone.resolve()
    remote = subprocess.check_output(["git", "remote", "get-url", "origin"], cwd=target, text=True).strip()
    if remote.removesuffix(".git").split(":")[-1].removeprefix("//github.com/") != "darkcenturies/valkyrie-phone" and remote != "https://github.com/darkcenturies/valkyrie-phone.git":
        raise SystemExit("Destination must be the existing darkcenturies/valkyrie-phone checkout.")
    manifest = json.loads((ROOT / "tools/phone-sync.json").read_text())
    changes = []
    # Validate the whole plan before writing anything.
    for entry in manifest["files"]:
        source = contained(ROOT, entry["source"])
        destination = contained(target, entry["destination"])
        data = source.read_bytes()
        if digest(data) != entry["sha256"]:
            raise SystemExit(f"Source changed since export review: {entry['source']}")
        current = digest(destination.read_bytes()) if destination.exists() else None
        if current != entry["sha256"]:
            if args.apply and current != entry["previous_sha256"]:
                raise SystemExit(f"Destination has independent changes: {entry['destination']}")
            changes.append((destination, data))
    if args.apply:
        if subprocess.check_output(["git", "status", "--porcelain", "--untracked-files=normal"], cwd=target):
            raise SystemExit("Destination must be clean. Commit/review existing work first.")
        for path, data in changes:
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_bytes(data)
    for path, _ in changes:
        print(("UPDATED " if args.apply else "DRIFT ") + path.relative_to(target).as_posix())
    print(f"{len(manifest['files'])} reviewed files; {len(changes)} {'updated' if args.apply else 'different'}")
    if changes and not args.apply:
        raise SystemExit(1)

if __name__ == "__main__":
    main()
