"""Browse, run and demonstrate public Valkyrie GTA tooling."""
from pathlib import Path
import argparse
import json
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parent
STANDALONE = ('scripts', 'timing', 'rendering', 'population', 'settings', 'saves',
              'capture', 'diagnostics', 'restoration')


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    commands = parser.add_subparsers(dest="command", required=True)
    listing = commands.add_parser("list", help="List source entry points.")
    listing.add_argument("--family")
    listing.add_argument("--search", default="")
    show = commands.add_parser("show", help="Show an exact registry ID or standalone valkyrie-* command.")
    show.add_argument("tool")
    run = commands.add_parser("run", help="Run an exact source entry point with your inputs.")
    run.add_argument("tool")
    run.add_argument("arguments", nargs=argparse.REMAINDER)
    demo = commands.add_parser("demo", help="Run an original/synthetic example without game inputs.")
    demo.add_argument("family", choices=["valkyrie-content", "valkyrie-signal", "valkyrie-collision"]
                      + ['valkyrie-' + name for name in STANDALONE])
    demo.add_argument("--output", type=Path, default=ROOT / "work" / "demos")
    args = parser.parse_args()
    if args.command == "demo":
        if args.family.removeprefix('valkyrie-') in STANDALONE:
            import importlib.util
            source = ROOT / 'tooling/source/workshop/tools/gta3/_fixtures.py'
            spec = importlib.util.spec_from_file_location('valkyrie_standalone_examples', source)
            module = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(module)
            try:
                module.demonstrate(args.family, args.output)
            except (OSError, ValueError, subprocess.CalledProcessError) as error:
                parser.exit(1, 'Demo error: ' + str(error) + '\n')
        else:
            from tooling.examples import demonstrate
            demonstrate(args.family, args.output)
        return
    entries = json.loads((ROOT / "tooling/registry.json").read_text(encoding="utf-8"))["entries"]
    if args.command == "list":
        if args.family and args.family not in {e["family"] for e in entries}:
            parser.error("Unknown family: " + args.family)
        for entry in entries:
            if args.family and entry["family"] != args.family:
                continue
            if args.search.casefold() not in (entry["id"] + ' ' + entry.get('command', '')).casefold():
                continue
            print(f'{entry["family"]:20} {entry["runtime"]:10} {entry["id"]}')
        return
    matches = [e for e in entries if e["id"] == args.tool or e.get('command') == args.tool]
    if len(matches) != 1:
        parser.error("Unknown tool ID. Use list to find an exact entry.")
    entry = matches[0]
    if args.command == "show":
        print(json.dumps(entry, indent=2))
        return
    runtime = entry["runtime"]
    executable = {"python": sys.executable, "powershell": shutil.which("pwsh"),
                  "bash": shutil.which("bash"), "node": shutil.which("node")}.get(runtime)
    if not executable:
        parser.error("This entry needs its declared runtime or a separate compiler/host. Read tooling/README.md.")
    arguments = args.arguments[1:] if args.arguments[:1] == ["--"] else args.arguments
    prefix = ["-File"] if runtime == "powershell" else []
    # Preserve the caller's working directory; never install dependencies or
    # rewrite inputs implicitly. Script behavior is visible in show/source.
    result = subprocess.run([executable, *prefix, str(ROOT / entry["path"]), *arguments])
    raise SystemExit(result.returncode)


if __name__ == "__main__":
    main()
