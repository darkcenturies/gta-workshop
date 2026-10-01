"""Small original/synthetic examples that execute the published tool functions."""
from pathlib import Path
import importlib.util
import json
import struct
import wave

ROOT = Path(__file__).resolve().parents[1]


def load(relative):
    spec = importlib.util.spec_from_file_location("valkyrie_example_tool", ROOT / relative)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def demonstrate(family, output):
    folder = output.resolve() / family
    folder.mkdir(parents=True, exist_ok=True)
    if family == "valkyrie-content":
        import numpy as np
        from PIL import Image, ImageDraw
        tones = load("tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/generate-phone-tones.py")
        samples = tones.sine(440, .25)
        pcm = (np.clip(samples, -1, 1) * 32767).astype("<i2")
        with wave.open(str(folder / "tone.wav"), "wb") as wav:
            wav.setnchannels(1)
            wav.setsampwidth(2)
            wav.setframerate(tones.RATE)
            wav.writeframes(pcm.tobytes())
        image = Image.new("RGBA", (64, 64), (0, 0, 0, 0))
        ImageDraw.Draw(image).rounded_rectangle((8, 8, 56, 56), radius=10, fill="#245fa8")
        image.save(folder / "icon.png")
        result = {"family": family, "sample_rate": tones.RATE, "samples": len(samples),
                  "image_size": [64, 64], "inputs": "Original 440 Hz synthesis and geometric drawing; no game/web inputs."}
    elif family == "valkyrie-signal":
        import numpy as np
        coverage = load("tooling/source/phone/valkyrie-asi-suite/valkyrie-phone/tools/signal-coverage/coverage.py")
        coverage.X0, coverage.Y1, coverage.RES = 0, 800, 100
        class SyntheticTerrain:
            h = w = 8
            ground = np.full((8, 8), 20, dtype=np.float32)
            cx = np.arange(8) * 100 + 50
            cy = 800 - (np.arange(8) * 100 + 50)
        first = coverage.path_loss(SyntheticTerrain(), 350, 450, 70, 900, reach=1000)
        second = coverage.path_loss(SyntheticTerrain(), 350, 450, 70, 900, reach=1000)
        assert np.array_equal(first, second), "Synthetic calculation is not repeatable"
        finite = first[np.isfinite(first)]
        assert finite.size > 0
        np.save(folder / "estimated-loss.npy", first)
        result = {"family": family, "shape": list(first.shape), "finite_cells": int(finite.size),
                  "repeatable": True, "frequency_mhz": 900,
                  "inputs": "Synthetic flat terrain; 100 m grid, 20 m ground and 70 m transmitter top.",
                  "limits": "Demonstrates the implementation, not measured reception or scientific validation."}
    else:
        compare = load("tooling/source/workshop/tools/compare-cadb-models.py")
        def fixture(path, ids):
            path.write_bytes(b"cadf" + struct.pack("<HHI", 2, len(ids), 0)
                             + b"".join(struct.pack("<HHHH", model, 0, 0, 0) for model in ids))
        old, new = folder / "old.cadb", folder / "new.cadb"
        fixture(old, [1, 2])
        fixture(new, [2, 3])
        a, b = compare.keys(old), compare.keys(new)
        assert a - b == {1} and b - a == {3}
        result = {"family": family, "missing": sorted(a - b), "added": sorted(b - a),
                  "inputs": "Two synthetic empty-geometry CADB v2 records; no game assets."}
    (folder / "result.json").write_text(json.dumps(result, indent=2) + "\n", encoding="utf-8")
    print(json.dumps({"output": str(folder), **result}, indent=2))
