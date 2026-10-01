"""Stock/FLA4 format regression tests for the release graph builder."""
import pathlib
import struct
import subprocess
import sys
import tempfile
import unittest

BUILDER = pathlib.Path(__file__).resolve().parents[1] / 'build-vehicle-graph.py'


def tile(extended):
    header = (b'\0\0\0\0FLA4' if extended else b'') + struct.pack('<5i', 2, 2, 0, 2, 2)
    nodes = bytearray()
    cars = bytearray()
    for i in range(2):
        node = bytearray(44 if extended else 28)
        struct.pack_into('<3i' if extended else '<3h', node, 28 if extended else 8, (10+i*10)*8, 20*8, 3*8)
        struct.pack_into('<hHH', node, 16, i, 2080 if extended else 0, i)
        node[24] = 1
        nodes += node
        car = bytearray(24 if extended else 14)
        struct.pack_into('<HHbbBBH', car, 4, 2080 if extended else 0, i, 100, 0, 32, 9, 2)
        cars += car
    links = struct.pack('<4H', 2080 if extended else 0, 1, 2080 if extended else 0, 0)
    return header + nodes + cars + links


class GraphFormats(unittest.TestCase):
    def test_stock_and_fla4_match(self):
        outputs = []
        with tempfile.TemporaryDirectory() as tmp:
            root = pathlib.Path(tmp)
            for extended in (False, True):
                source = root / str(extended)
                source.mkdir()
                (source / ('NODES2080.DAT' if extended else 'NODES0.DAT')).write_bytes(tile(extended))
                output = root / f'{extended}.bin'
                subprocess.run([sys.executable, str(BUILDER), str(source), '-o', str(output)], check=True, capture_output=True)
                outputs.append(output.read_bytes())
            self.assertEqual(outputs[0], outputs[1])
            self.assertEqual(struct.unpack_from('<4sIII', outputs[0]), (b'SPVG', 1, 2, 2))
            self.assertEqual(struct.unpack_from('<3f', outputs[0], 16), (10, 20, 3))
            self.assertEqual(struct.unpack_from('<2I', outputs[0], 88), (1, 0))

    def test_truncated_stock_rejected(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = pathlib.Path(tmp)
            (root / 'NODES0.DAT').write_bytes(tile(False)[:-1])
            output = root / 'graph.bin'
            result = subprocess.run([sys.executable, str(BUILDER), str(root), '-o', str(output)], capture_output=True)
            self.assertNotEqual(result.returncode, 0)
            self.assertFalse(output.exists())


if __name__ == '__main__':
    unittest.main()
