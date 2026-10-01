"""A backup archive must never override the live world's assets."""
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

class IndexTest(unittest.TestCase):
    def test_named_backups_are_excluded(self):
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            def archive(path):
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_bytes(b'VER2' + struct.pack('<I', 1) +
                    struct.pack('<IHH24s', 1, 1, 1, b'road.dff'))
            live = root / 'models' / 'world.img'
            archive(live)
            archive(root / 'valkyrie-hd-backup-20260905' / 'world.img')
            loose = root / 'modloader' / 'skin-backups'
            loose.mkdir(parents=True)
            (loose / 'road.dff').write_bytes(b'old')
            output = root / 'index.json'
            subprocess.run([sys.executable, str(Path(__file__).with_name('world3d-index.py')),
                            str(root), str(output)], check=True, capture_output=True)
            record = json.loads(output.read_text())['models']['road']
            self.assertEqual(Path(record['src']), live)

if __name__ == '__main__':
    unittest.main()
