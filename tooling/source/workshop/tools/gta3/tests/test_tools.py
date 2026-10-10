"""Behaviour and failure regressions for public standalone analysis commands."""
import csv
import importlib
import json
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

SOURCE = Path(__file__).resolve().parents[1]
REPO = SOURCE.parents[4]
sys.path.insert(0, str(SOURCE))
from _common import read_json, safe_path
from _fixtures import NAMES, arguments, generate


class PublicTools(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name) / 'inputs'
        generate(self.root)

    def module(self, name):
        return importlib.import_module('valkyrie_' + name)

    def data(self, name):
        return read_json(self.root / name)

    def rows(self, name):
        with (self.root / name).open(newline='') as stream:
            return list(csv.DictReader(stream))

    def test_all_nine_commands_through_public_launcher(self):
        for name in NAMES:
            with self.subTest(tool=name):
                process = subprocess.run([sys.executable, str(REPO / 'valkyrie.py'), 'run', 'valkyrie-' + name,
                                          '--', *arguments(name, self.root)], capture_output=True, text=True)
                self.assertEqual(process.returncode, 0, process.stderr)
                report = json.loads(process.stdout)
                self.assertEqual(report['tool'], 'valkyrie-' + name)
                self.assertFalse(report['gameplay_tested_by_this_tool'])

    def test_reports_never_overwrite(self):
        output = self.root / 'report.json'
        output.write_text('retained')
        process = subprocess.run([sys.executable, str(SOURCE / 'valkyrie_timing.py'),
                                  *arguments('timing', self.root), '--output', str(output)], capture_output=True)
        self.assertEqual(process.returncode, 1)
        self.assertEqual(output.read_text(), 'retained')

    def test_json_duplicate_and_nonfinite_rejected(self):
        for text in ('{"a":1,"a":2}', '{"a":NaN}'):
            (self.root / 'bad.json').write_text(text)
            with self.assertRaises(ValueError):
                read_json(self.root / 'bad.json')

    def test_input_paths_cannot_escape(self):
        for name in ('../outside', '/absolute', 'C:/outside', 'a\\b', 'a/../b', './a'):
            with self.subTest(path=name), self.assertRaises(ValueError):
                safe_path(self.root, name)

    def test_scripts_decode_fixed_point_and_self_branch(self):
        result = self.module('scripts').inspect((self.root / 'authored.scm').read_bytes(), self.data('opcodes.json'))
        self.assertEqual(result['sections'][0]['instructions'][0]['args'][0]['value'], 1.5)
        self.assertEqual(result['sections'][0]['instructions'][1]['name'], 'AUTHORED_BRANCH')

    def test_scripts_reject_truncation_bad_branch_and_schema(self):
        source = bytearray((self.root / 'authored.scm').read_bytes())
        with self.assertRaises(ValueError):
            self.module('scripts').inspect(source[:-1], self.data('opcodes.json'))
        struct.pack_into('<i', source, len(source) - 4, 113)
        with self.assertRaises(ValueError):
            self.module('scripts').inspect(source, self.data('opcodes.json'))
        with self.assertRaises(ValueError):
            self.module('scripts').inspect(source, {'profile': 'sa', 'opcodes': {}})

    def test_script_tail_stops_at_section_boundary(self):
        source = bytearray((self.root / 'authored.scm').read_bytes())
        schema = self.data('opcodes.json')
        schema['opcodes']['0x11']['args'] = ['tail']
        schema['opcodes']['0x11'].pop('branch_arg')
        source[-4:] = b'\x01\x01\x01\x01'
        with self.assertRaises(ValueError):
            self.module('scripts').inspect(source, schema)

    def test_timing_exposes_rate_drift(self):
        rows = self.rows('timing.csv')
        rows[-1]['value'] = '2.1'
        result = self.module('timing').analyze(rows)
        self.assertFalse(result['passed'])
        self.assertGreater(result['comparisons'][-1]['max_absolute_error'], .09)

    def test_timing_rejects_unequal_intervals_and_duplicate_times(self):
        for field, bad in (('time_s', '0.5'), ('value', 'nan')):
            rows = self.rows('timing.csv')
            rows[-1][field] = bad
            with self.assertRaises(ValueError):
                self.module('timing').analyze(rows)
        rows = self.rows('timing.csv')
        rows[-1]['time_s'] = '2'
        with self.assertRaises(ValueError):
            self.module('timing').analyze(rows)

    def test_rendering_measurement_and_camera_guard(self):
        meta = self.data('reference-meta.json')
        other = self.data('candidate-meta.json')
        result = self.module('rendering').compare(self.root / 'reference.ppm', self.root / 'candidate.ppm',
                                                meta, other, ['lighting'])
        self.assertEqual(result['mean_absolute_rgb_error'], [10, 10, 10])
        self.assertEqual(result['changed_pixel_fraction'], 1)
        other['camera'] = [1, 0, 0]
        with self.assertRaises(ValueError):
            self.module('rendering').compare(self.root / 'reference.ppm', self.root / 'candidate.ppm', meta, other, ['lighting'])

    def test_population_shared_pool_pressure_and_impossible_counts(self):
        rows = self.rows('population.csv')
        result = self.module('population').analyze(rows, 140, 110, 10)
        self.assertEqual(result['scenarios'][0]['reserve_pressure_samples'], 2)
        rows[0]['occupants'] = '60'
        with self.assertRaises(ValueError):
            self.module('population').analyze(rows, 140, 110)

    def test_settings_preserve_existing_off_and_add_default(self):
        module = self.module('settings')
        result = module.audit(module.load(self.root / 'before.ini'), module.load(self.root / 'after.ini'), self.data('settings.json'))
        self.assertTrue(result['passed'])
        self.assertFalse(result['settings'][0]['actual'])

    def test_settings_unrelated_loss_and_duplicate_keys_fail(self):
        module = self.module('settings')
        before = module.load(self.root / 'before.ini')
        after = module.load(self.root / 'after.ini')
        after.pop(('Other', 'keep'))
        self.assertFalse(module.audit(before, after, self.data('settings.json'))['passed'])
        (self.root / 'bad.ini').write_text('[Graphics]\nblur=0\nBLUR=1\n')
        with self.assertRaises(ValueError):
            module.load(self.root / 'bad.ini')

    def test_settings_invalid_saved_value_uses_declared_default(self):
        module = self.module('settings')
        before = {('Graphics', 'blur'): 'invalid'}
        after = {('Graphics', 'blur'): '1', ('Graphics', 'scale'): '1.5'}
        self.assertTrue(module.audit(before, after, self.data('settings.json'))['passed'])

    def test_saves_profile_identity_and_overlaps(self):
        module = self.module('saves')
        contract = self.data('save-contract.json')
        self.assertEqual(module.audit(self.root / 'synthetic.save', contract, 'synthetic-stock')['uninspected_bytes'], 0)
        with self.assertRaises(ValueError):
            module.audit(self.root / 'synthetic.save', contract, 'other-world')
        contract['blocks'][1]['offset'] = 8
        with self.assertRaises(ValueError):
            module.audit(self.root / 'synthetic.save', contract, 'synthetic-stock')

    def test_saves_wrong_block_size_produces_failed_report(self):
        contract = self.data('save-contract.json')
        contract['blocks'][0]['expected_size'] = 12
        self.assertFalse(self.module('saves').audit(self.root / 'synthetic.save', contract, 'synthetic-stock')['passed'])

    def test_capture_audio_timing_and_event_bounds(self):
        manifest = self.data('capture.json')
        result = self.module('capture').audit(self.root, manifest)
        self.assertTrue(result['passed'])
        self.assertEqual(result['events'][0]['time_s'], .5)
        manifest['fps'] = 3
        self.assertFalse(self.module('capture').audit(self.root, manifest)['passed'])
        manifest['events'][0]['frame'] = 2
        with self.assertRaises(ValueError):
            self.module('capture').audit(self.root, manifest)

    def test_diagnostics_resolves_only_inside_real_ranges(self):
        result = self.module('diagnostics').symbolize(self.data('crash.json'), self.rows('symbols.csv'), 'a' * 64)
        self.assertEqual(result['frames'][0]['symbol'], 'AuthoredFunction')
        self.assertEqual(result['frames'][0]['symbol_offset'], 4)
        self.assertIsNone(result['frames'][1]['symbol'])
        with self.assertRaises(ValueError):
            self.module('diagnostics').symbolize(self.data('crash.json'), self.rows('symbols.csv'), 'b' * 64)

    def test_diagnostics_keeps_full_64bit_addresses(self):
        crash = self.data('crash.json')
        crash.update(image_base='0xffff000000000000', addresses=['0xffff000000000104'])
        result = self.module('diagnostics').symbolize(crash, self.rows('symbols.csv'), 'a' * 64)
        self.assertEqual(result['frames'][0]['rva'], '0x104')

    def test_restoration_requires_evidence_and_does_not_promote_states(self):
        data = self.data('restoration.json')
        result = self.module('restoration').catalogue(data, self.root, 'demo')
        self.assertEqual(result['matched_records'], 1)
        self.assertEqual(result['records'][0]['validation'], 'synthetic-tested')
        data['records'][0]['sources'] = []
        with self.assertRaises(ValueError):
            self.module('restoration').catalogue(data, self.root)

    def test_failure_exit_code_keeps_report(self):
        rows = (self.root / 'timing.csv').read_text().replace('240,1,2', '240,1,4')
        (self.root / 'timing.csv').write_text(rows)
        process = subprocess.run([sys.executable, str(SOURCE / 'valkyrie_timing.py'),
                                  *arguments('timing', self.root)], capture_output=True, text=True)
        self.assertEqual(process.returncode, 2)
        self.assertFalse(json.loads(process.stdout)['passed'])


if __name__ == '__main__':
    unittest.main()
