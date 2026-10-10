"""Validate ordered image frames, PCM audio and declared scene events.

Copyright (c) 2026 darkcenturies. BSD-3-Clause; see the collection LICENSE.
"""
from pathlib import Path
import wave
from _common import emit, integer, number, parser, read_json, run, safe_path, sha256


def audit(root, manifest):
    from PIL import Image
    fps = number(manifest['fps'], 'FPS', 0.001)
    width = integer(manifest['width'], 'width', 1)
    height = integer(manifest['height'], 'height', 1)
    frames = manifest['frames']
    if not isinstance(frames, list) or not frames or len(frames) != len(set(frames)):
        raise ValueError('Need unique, ordered frame paths')
    hashes = []
    for name in frames:
        path = safe_path(root, name)
        with Image.open(path) as image:
            if image.size != (width, height):
                raise ValueError('Frame dimensions disagree: ' + name)
            image.load()
        hashes.append({'path': name, 'sha256': sha256(path)})
    audio_name = manifest['audio']
    if audio_name in frames:
        raise ValueError('Audio and frame paths overlap')
    audio_path = safe_path(root, audio_name)
    try:
        with wave.open(str(audio_path), 'rb') as audio:
            if audio.getcomptype() != 'NONE' or audio.getsampwidth() not in (1, 2, 3, 4):
                raise ValueError('Expected uncompressed PCM WAV')
            channels, rate, count = audio.getnchannels(), audio.getframerate(), audio.getnframes()
            if channels not in (1, 2) or not rate:
                raise ValueError('Expected mono or stereo PCM with a positive sample rate')
            width_bytes = audio.getsampwidth()
            non_silent = False
            bytes_read = 0
            while True:
                data = audio.readframes(65536)
                if not data:
                    break
                bytes_read += len(data)
                non_silent |= any(value != (128 if width_bytes == 1 else 0) for value in data)
            if bytes_read != count * channels * width_bytes:
                raise ValueError('Truncated PCM data')
    except (wave.Error, EOFError) as error:
        raise ValueError('Invalid PCM WAV: ' + str(error)) from None
    delta_samples = abs(count - len(frames) * rate / fps)
    events = []
    for event in manifest.get('events', []):
        frame = integer(event['frame'], 'event frame')
        if frame >= len(frames) or not isinstance(event['type'], str) or not event['type']:
            raise ValueError('Event outside capture or missing type')
        events.append({'type': event['type'], 'frame': frame, 'time_s': frame / fps,
                       'provenance': event.get('provenance', 'unspecified')})
    return {'tool': 'valkyrie-capture', 'passed': delta_samples <= 1 and non_silent,
            'fps': fps, 'dimensions': [width, height], 'frame_count': len(frames),
            'video_duration_s': len(frames) / fps, 'audio_duration_s': count / rate,
            'audio_duration_error_samples': delta_samples, 'audio_non_silent': non_silent,
            'audio_channels': channels, 'audio_rate': rate, 'frames': hashes,
            'audio_sha256': sha256(audio_path), 'events': events,
            'scope': 'Declared frame order and timing contract; no independent proof of audio origin, native events or unassisted gameplay.'}


def main():
    p = parser(__doc__)
    p.add_argument('manifest', type=Path)
    p.add_argument('--root', type=Path, required=True)
    a = p.parse_args()
    report = audit(a.root, read_json(a.manifest))
    report['manifest_sha256'] = sha256(a.manifest)
    return emit(report, a.output)


if __name__ == '__main__':
    run(main)
