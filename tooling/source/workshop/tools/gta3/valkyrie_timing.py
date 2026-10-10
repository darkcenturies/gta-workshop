"""Compare equal-time measurement traces across frame rates.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
import bisect
import csv
from pathlib import Path
from _common import emit, number, parser, run, sha256


def analyze(rows, baseline=30, absolute=0.001, relative=0.001):
    baseline = number(baseline, 'baseline FPS', 0.001)
    absolute = number(absolute, 'absolute tolerance', 0)
    relative = number(relative, 'relative tolerance', 0)
    groups = {}
    for row in rows:
        key = (row['scenario'], row['metric'], row['unit'])
        if not all(key):
            raise ValueError('Scenario, metric and unit are required')
        fps = number(row['fps'], 'FPS', 0.001)
        time = number(row['time_s'], 'time', 0)
        value = number(row['value'], 'measurement')
        groups.setdefault(key, {}).setdefault(fps, []).append((time, value))
    if not groups:
        raise ValueError('No timing measurements')
    comparisons = []
    for key, rates in sorted(groups.items()):
        if baseline not in rates or len(rates) < 2:
            raise ValueError('Every metric needs the baseline and another FPS')
        for trace in rates.values():
            trace.sort()
            if len(trace) < 2 or any(a[0] >= b[0] for a, b in zip(trace, trace[1:])):
                raise ValueError('Need at least two unique timestamps per trace')
        base = rates[baseline]
        for fps, trace in sorted(rates.items()):
            if fps == baseline:
                continue
            if abs(trace[0][0] - base[0][0]) > 1e-9 or abs(trace[-1][0] - base[-1][0]) > 1e-9:
                raise ValueError('Traces must cover the same elapsed-time interval')
            times = [item[0] for item in trace]
            errors = []
            failed = 0
            for time, expected in base:
                right = min(max(bisect.bisect_right(times, time), 1), len(trace) - 1)
                t0, v0 = trace[right - 1]
                t1, v1 = trace[right]
                actual = v0 + (v1 - v0) * (time - t0) / (t1 - t0)
                error = abs(actual - expected)
                errors.append(error)
                failed += error > absolute + relative * abs(expected)
            comparisons.append({'scenario': key[0], 'metric': key[1], 'unit': key[2],
                                'fps': fps, 'max_absolute_error': max(errors),
                                'failed_samples': failed, 'samples': len(base)})
    return {'tool': 'valkyrie-timing', 'passed': all(c['failed_samples'] == 0 for c in comparisons),
            'baseline_fps': baseline, 'absolute_tolerance': absolute,
            'relative_tolerance': relative, 'comparisons': comparisons,
            'scope': 'Linear interpolation at baseline timestamps; caller establishes measurement provenance and adequate sampling.'}


def main():
    p = parser(__doc__)
    p.add_argument('measurements', type=Path)
    p.add_argument('--baseline-fps', type=float, default=30)
    p.add_argument('--absolute-tolerance', type=float, default=0.001)
    p.add_argument('--relative-tolerance', type=float, default=0.001)
    a = p.parse_args()
    with a.measurements.open(encoding='utf-8-sig', newline='') as stream:
        report = analyze(csv.DictReader(stream), a.baseline_fps, a.absolute_tolerance, a.relative_tolerance)
    report['input_sha256'] = sha256(a.measurements)
    return emit(report, a.output)


if __name__ == '__main__':
    run(main)
