"""Exercise export preflight failures without touching a real checkout."""
import contextlib
import importlib.util
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location("sync_phone", Path(__file__).with_name("sync-phone.py"))
sync = importlib.util.module_from_spec(spec)
spec.loader.exec_module(sync)

class ExportTests(unittest.TestCase):
    def setUp(self):
        self.temp = tempfile.TemporaryDirectory()
        self.addCleanup(self.temp.cleanup)
        root = Path(self.temp.name)
        self.source, self.target = root / "source", root / "target"
        (self.source / "tools").mkdir(parents=True)
        self.target.mkdir()
        self.entries = []
        for name in ("a.cpp", "b.cpp"):
            (self.source / name).write_bytes(b"new\n")
            (self.target / name).write_bytes(b"old\n")
            self.entries.append(dict(source=name, destination=name,
                sha256=sync.digest(b"new\n"), previous_sha256=sync.digest(b"old\n")))
        self.save()

    def save(self):
        (self.source / "tools/phone-sync.json").write_text(json.dumps({"files": self.entries}))

    def run_export(self, apply=True, dirty=False):
        def git(command, **kwargs):
            if command[1] == "remote":
                return "https://github.com/darkcenturies/valkyrie-phone.git\n"
            return b" M independent.cpp\n" if dirty else b""
        argv = ["sync-phone.py", str(self.target)] + (["--apply"] if apply else [])
        with patch.object(sync, "ROOT", self.source), patch("sys.argv", argv), \
             patch.object(sync.subprocess, "check_output", side_effect=git), contextlib.redirect_stdout(io.StringIO()):
            sync.main()

    def unchanged(self):
        self.assertEqual((self.target / "a.cpp").read_bytes(), b"old\n")

    def test_apply_and_check(self):
        self.run_export()
        self.assertEqual((self.target / "a.cpp").read_bytes(), b"new\n")
        self.run_export(apply=False)

    def test_check_does_not_write(self):
        with self.assertRaises(SystemExit): self.run_export(apply=False)
        self.unchanged()

    def test_independent_change_aborts_entire_plan(self):
        (self.target / "b.cpp").write_bytes(b"another session\n")
        with self.assertRaises(SystemExit): self.run_export()
        self.unchanged()

    def test_source_change_aborts_entire_plan(self):
        (self.source / "b.cpp").write_bytes(b"not reviewed\n")
        with self.assertRaises(SystemExit): self.run_export()
        self.unchanged()

    def test_dirty_checkout_rejected(self):
        with self.assertRaises(SystemExit): self.run_export(dirty=True)
        self.unchanged()

    def test_path_escape_rejected(self):
        self.entries[1]["destination"] = "../outside.cpp"
        self.save()
        with self.assertRaises(ValueError): self.run_export()
        self.unchanged()

if __name__ == "__main__": unittest.main()
