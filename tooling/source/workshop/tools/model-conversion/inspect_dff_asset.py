"""Import a GTA RenderWare DFF with DragonFF and report rig/mesh details."""

from __future__ import annotations

import json
import sys
from pathlib import Path

import bpy


def main() -> None:
    args = sys.argv[sys.argv.index("--") + 1 :]
    if len(args) != 2:
        raise SystemExit("usage: inspect_dff_asset.py INPUT.dff OUTPUT.blend")

    asset_path = Path(args[0]).resolve()
    output_path = Path(args[1]).resolve()
    bpy.ops.preferences.addon_enable(module="DragonFF")
    files = []
    texture_dictionary = asset_path.with_suffix(".txd")
    if texture_dictionary.is_file():
        files.append({"name": texture_dictionary.name})
    files.append({"name": asset_path.name})
    result = bpy.ops.import_scene.dff(
        directory=str(asset_path.parent),
        files=files,
        load_images=False,
        connect_bones=False,
        remove_doubles=False,
    )
    if "FINISHED" not in result:
        raise RuntimeError(f"DragonFF import failed: {result}")

    meshes = []
    for obj in bpy.data.objects:
        if obj.type != "MESH":
            continue
        obj.data.calc_loop_triangles()
        coordinates = [obj.matrix_world @ vertex.co for vertex in obj.data.vertices]
        group_members = {
            group.name: sum(
                1
                for vertex in obj.data.vertices
                if any(membership.group == group.index for membership in vertex.groups)
            )
            for group in obj.vertex_groups
        }
        meshes.append(
            {
                "name": obj.name,
                "vertices": len(obj.data.vertices),
                "triangles": len(obj.data.loop_triangles),
                "materials": len(obj.data.materials),
                "vertex_groups": [group.name for group in obj.vertex_groups],
                "modifiers": [modifier.type for modifier in obj.modifiers],
                "parent": obj.parent.name if obj.parent else None,
                "bounds": {
                    "min": [min(point[axis] for point in coordinates) for axis in range(3)],
                    "max": [max(point[axis] for point in coordinates) for axis in range(3)],
                },
                "weighted_groups": {
                    name: count for name, count in group_members.items() if count
                },
            }
        )
    armatures = [
        {
            "name": obj.name,
            "bones": [
                {
                    "name": bone.name,
                    "head": list(bone.head_local),
                    "tail": list(bone.tail_local),
                    "parent": bone.parent.name if bone.parent else None,
                }
                for bone in obj.data.bones
            ],
        }
        for obj in bpy.data.objects
        if obj.type == "ARMATURE"
    ]
    print(
        "SPRP_DFF_REPORT="
        + json.dumps(
            {
                "asset": str(asset_path),
                "objects": len(bpy.data.objects),
                "meshes": meshes,
                "armatures": armatures,
                "images": [
                    {"name": image.name, "width": image.size[0], "height": image.size[1]}
                    for image in bpy.data.images
                    if image.type == "IMAGE"
                ],
            },
            sort_keys=True,
        )
    )
    output_path.parent.mkdir(parents=True, exist_ok=True)
    bpy.ops.wm.save_as_mainfile(filepath=str(output_path))


if __name__ == "__main__":
    main()
