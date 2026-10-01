"""Import a GTA V drawable with Sollumz and report scene complexity.

Run through Blender, for example:
  blender --background --factory-startup --python inspect_gtav_asset.py -- \
    input.ydd output.blend
"""

from __future__ import annotations

import json
import sys
from pathlib import Path

import bpy


def main() -> None:
    args = sys.argv[sys.argv.index("--") + 1 :]
    if len(args) != 2:
        raise SystemExit("usage: inspect_gtav_asset.py INPUT.ydd OUTPUT.blend")

    asset_path = Path(args[0]).resolve()
    output_path = Path(args[1]).resolve()
    if not asset_path.is_file():
        raise FileNotFoundError(asset_path)

    bpy.ops.preferences.addon_enable(module="Sollumz")
    # Import the matching texture dictionary first. Sollumz will discover the
    # matching fragment as the external skeleton dependency for ped YDDs.
    files = []
    texture_dictionary = asset_path.with_suffix(".ytd")
    if texture_dictionary.is_file():
        files.append({"name": texture_dictionary.name})
    files.append({"name": asset_path.name})

    result = bpy.ops.sollumz.import_assets(
        directory=str(asset_path.parent),
        files=files,
    )
    if "FINISHED" not in result:
        raise RuntimeError(f"Sollumz import failed: {result}")

    meshes = []
    total_vertices = 0
    total_triangles = 0
    for obj in bpy.data.objects:
        if obj.type != "MESH":
            continue
        obj.data.calc_loop_triangles()
        vertices = len(obj.data.vertices)
        triangles = len(obj.data.loop_triangles)
        total_vertices += vertices
        total_triangles += triangles
        meshes.append(
            {
                "name": obj.name,
                "vertices": vertices,
                "triangles": triangles,
                "materials": len(obj.data.materials),
                "vertex_groups": len(obj.vertex_groups),
            }
        )

    armatures = [
        {"name": obj.name, "bones": len(obj.data.bones)}
        for obj in bpy.data.objects
        if obj.type == "ARMATURE"
    ]
    images = [
        {
            "name": image.name,
            "width": image.size[0],
            "height": image.size[1],
            "packed": image.packed_file is not None,
        }
        for image in bpy.data.images
        if image.type == "IMAGE"
    ]

    report = {
        "asset": str(asset_path),
        "objects": len(bpy.data.objects),
        "meshes": meshes,
        "mesh_count": len(meshes),
        "vertices": total_vertices,
        "triangles": total_triangles,
        "armatures": armatures,
        "materials": len(bpy.data.materials),
        "images": images,
    }
    print("SPRP_MODEL_REPORT=" + json.dumps(report, sort_keys=True))

    output_path.parent.mkdir(parents=True, exist_ok=True)
    bpy.ops.wm.save_as_mainfile(filepath=str(output_path))


if __name__ == "__main__":
    main()
