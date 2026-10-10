"""Summarize population measurements and shared walker/driver capacity.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
import csv
from pathlib import Path
import statistics
from _common import emit, integer, number, parser, run, sha256


def analyze(rows, ped_capacity, vehicle_capacity, reserve=0):
    ped_capacity = integer(ped_capacity, 'ped capacity', 1)
    vehicle_capacity = integer(vehicle_capacity, 'vehicle capacity', 1)
    reserve = integer(reserve, 'ped reserve')
    if reserve >= ped_capacity:
        raise ValueError('Reserve must be smaller than ped capacity')
    groups = {}
    timestamps = set()
    fields = ('walkers', 'occupants', 'vehicles', 'near_vehicles', 'far_vehicles', 'near_walkers', 'far_walkers')
    for row in rows:
        scenario = row['scenario']
        stamp = (scenario, number(row['time_s'], 'time', 0))
        if not scenario or stamp in timestamps:
            raise ValueError('Scenario/time pairs must be nonempty and unique')
        timestamps.add(stamp)
        values = {key: integer(row[key], key) for key in fields}
        used = values['walkers'] + values['occupants']
        if used > ped_capacity or values['vehicles'] > vehicle_capacity:
            raise ValueError('Observed counts exceed declared capacities')
        if values['near_vehicles'] + values['far_vehicles'] > values['vehicles']:
            raise ValueError('Near/far vehicle counts exceed total')
        if values['near_walkers'] + values['far_walkers'] > values['walkers']:
            raise ValueError('Near/far walker counts exceed total')
        values['ped_free'] = ped_capacity - used
        values['vehicle_free'] = vehicle_capacity - values['vehicles']
        values['driver_reserve_pressure'] = values['ped_free'] <= reserve and values['vehicle_free'] > 0
        groups.setdefault(scenario, []).append(values)
    if not groups:
        raise ValueError('No population measurements')
    results = []
    for scenario, samples in sorted(groups.items()):
        results.append({'scenario': scenario, 'samples': len(samples),
                        'mean_counts': {key: statistics.mean(row[key] for row in samples) for key in fields},
                        'minimum_free_ped_slots': min(row['ped_free'] for row in samples),
                        'reserve_pressure_samples': sum(row['driver_reserve_pressure'] for row in samples)})
    return {'tool': 'valkyrie-population', 'ped_capacity': ped_capacity,
            'vehicle_capacity': vehicle_capacity, 'reserved_ped_slots': reserve, 'scenarios': results,
            'scope': 'Reserve pressure is a candidate cause, not proof of failed spawning, rendering, visibility or performance.'}


def main():
    p = parser(__doc__)
    p.add_argument('measurements', type=Path)
    p.add_argument('--ped-capacity', required=True, type=int)
    p.add_argument('--vehicle-capacity', required=True, type=int)
    p.add_argument('--ped-reserve', type=int, default=0)
    a = p.parse_args()
    with a.measurements.open(encoding='utf-8-sig', newline='') as stream:
        report = analyze(csv.DictReader(stream), a.ped_capacity, a.vehicle_capacity, a.ped_reserve)
    report['input_sha256'] = sha256(a.measurements)
    return emit(report, a.output)


if __name__ == '__main__':
    run(main)
