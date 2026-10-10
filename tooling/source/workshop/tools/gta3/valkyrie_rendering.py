"""Measure matched image captures with explicit comparison conditions.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
from pathlib import Path
from _common import emit, number, parser, read_json, run, sha256


def compare(reference, candidate, reference_meta, candidate_meta, allowed=(), threshold=0):
    from PIL import Image, ImageChops, ImageStat
    required = ('target_revision', 'renderer', 'scene', 'camera', 'time_s')
    for meta in (reference_meta, candidate_meta):
        if any(key not in meta or meta[key] is None or meta[key] == '' for key in required):
            raise ValueError('Capture metadata needs target_revision, renderer, scene, camera and time_s')
        number(meta['time_s'], 'simulation time', 0)
    changes = {key: {'reference': reference_meta.get(key), 'candidate': candidate_meta.get(key)}
               for key in reference_meta.keys() | candidate_meta.keys()
               if reference_meta.get(key) != candidate_meta.get(key)}
    if set(changes) - set(allowed):
        raise ValueError('Unapproved condition changes: ' + ', '.join(sorted(set(changes) - set(allowed))))
    threshold = number(threshold, 'pixel threshold', 0)
    if threshold > 255:
        raise ValueError('Pixel threshold exceeds 255')
    with Image.open(reference) as a, Image.open(candidate) as b:
        if a.size != b.size or not a.width or not a.height:
            raise ValueError('Capture dimensions differ or are empty')
        # Preserve visible alpha differences by compositing both over the same black canvas.
        def visible(image):
            rgba = image.convert('RGBA')
            background = Image.new('RGBA', rgba.size, (0, 0, 0, 255))
            return Image.alpha_composite(background, rgba).convert('RGB')
        delta = ImageChops.difference(visible(a), visible(b))
        changed = sum(max(pixel) > threshold for pixel in delta.getdata())
        mean = ImageStat.Stat(delta).mean
        return {'tool': 'valkyrie-rendering', 'dimensions': list(a.size),
                'mean_absolute_rgb_error': mean, 'changed_pixel_fraction': changed / (a.width * a.height),
                'pixel_threshold': threshold, 'condition_changes': changes,
                'reference_sha256': sha256(reference), 'candidate_sha256': sha256(candidate),
                'scope': 'Pixel differences, not visual quality, effect activation, geometry visibility or historical authenticity.'}


def main():
    p = parser(__doc__)
    p.add_argument('reference', type=Path)
    p.add_argument('candidate', type=Path)
    p.add_argument('--reference-meta', required=True, type=Path)
    p.add_argument('--candidate-meta', required=True, type=Path)
    p.add_argument('--allow-condition', action='append', default=[])
    p.add_argument('--pixel-threshold', type=float, default=0)
    a = p.parse_args()
    return emit(compare(a.reference, a.candidate, read_json(a.reference_meta),
                        read_json(a.candidate_meta), a.allow_condition, a.pixel_threshold), a.output)


if __name__ == '__main__':
    run(main)
