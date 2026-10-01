"""Stress-pose a converted GTA SA skin and report deformation quality.

Run with the converted build .blend open. An optional argument after ``--``
writes a front render of the posed model. The numerical edge-stretch report is
useful for catching bad bind weights before copying a DFF into the live game.
"""

from __future__ import annotations

import json
import math
import sys
from pathlib import Path

import bpy
from mathutils import Vector


STRESS_POSE_DEGREES = {
    " L UpperArm01": (38.0, -24.0, 62.0),
    " L ForeArm01": (12.0, 8.0, 88.0),
    " L Hand01": (18.0, -12.0, 8.0),
    " R UpperArm01": (-42.0, 28.0, -58.0),
    " R ForeArm01": (-10.0, -12.0, -82.0),
    " R Hand01": (-16.0, 10.0, -8.0),
    " L Thigh01": (58.0, -16.0, 12.0),
    " L Calf01": (-82.0, 4.0, 0.0),
    " L Foot01": (24.0, 0.0, 0.0),
    " R Thigh01": (-34.0, 18.0, -10.0),
    " R Calf01": (68.0, -6.0, 0.0),
    " R Foot01": (-20.0, 0.0, 0.0),
    " Spine02": (8.0, -12.0, 6.0),
    " Spine03": (-5.0, 18.0, -8.0),
}


def apply_stress_pose(armature: bpy.types.Object) -> None:
    for pose_bone in armature.pose.bones:
        pose_bone.rotation_mode = "XYZ"
        pose_bone.rotation_euler = (0.0, 0.0, 0.0)
    for name, degrees in STRESS_POSE_DEGREES.items():
        pose_bone = armature.pose.bones.get(name)
        if pose_bone is None:
            raise RuntimeError(f"Missing GTA SA pose bone: {name}")
        pose_bone.rotation_euler = tuple(math.radians(value) for value in degrees)
    bpy.context.view_layer.update()


def percentile(values: list[float], fraction: float) -> float:
    ordered = sorted(values)
    return ordered[min(len(ordered) - 1, round((len(ordered) - 1) * fraction))]


def deformation_report(obj: bpy.types.Object) -> dict[str, object]:
    depsgraph = bpy.context.evaluated_depsgraph_get()
    evaluated = obj.evaluated_get(depsgraph)
    posed_mesh = evaluated.to_mesh()
    try:
        rest = [obj.matrix_world @ vertex.co for vertex in obj.data.vertices]
        posed = [evaluated.matrix_world @ vertex.co for vertex in posed_mesh.vertices]
        ratios = []
        for edge in obj.data.edges:
            first, second = edge.vertices
            rest_length = (rest[first] - rest[second]).length
            if rest_length > 1e-7:
                ratios.append((posed[first] - posed[second]).length / rest_length)
        bounds_min = [min(point[axis] for point in posed) for axis in range(3)]
        bounds_max = [max(point[axis] for point in posed) for axis in range(3)]
        return {
            "vertices": len(posed),
            "max_edge_stretch": round(max(ratios), 4),
            "p99_edge_stretch": round(percentile(ratios, 0.99), 4),
            "posed_dimensions": [
                round(bounds_max[axis] - bounds_min[axis], 4) for axis in range(3)
            ],
        }
    finally:
        evaluated.to_mesh_clear()


def point_camera(camera: bpy.types.Object, point: Vector) -> None:
    camera.rotation_euler = (point - camera.location).to_track_quat("-Z", "Y").to_euler()


def render_preview(obj: bpy.types.Object, output: Path) -> None:
    scene = bpy.context.scene
    obj.hide_render = False
    for other in bpy.data.objects:
        if other.type == "MESH" and other != obj:
            other.hide_render = True
    world = scene.world or bpy.data.worlds.new("Pose QA World")
    scene.world = world
    world.color = (0.035, 0.045, 0.06)

    camera_data = bpy.data.cameras.new("Pose QA Camera")
    camera = bpy.data.objects.new("Pose QA Camera", camera_data)
    scene.collection.objects.link(camera)
    camera.location = (2.65, -4.8, 0.45)
    camera_data.lens = 58.0
    point_camera(camera, Vector((0.0, 0.0, -0.05)))
    scene.camera = camera

    for name, location, energy, size in (
        ("Key", (-2.5, -3.5, 4.0), 1100.0, 4.0),
        ("Fill", (3.0, -1.5, 1.5), 700.0, 3.0),
        ("Rim", (0.0, 2.5, 3.0), 900.0, 2.5),
    ):
        light_data = bpy.data.lights.new(name, "AREA")
        light_data.energy = energy
        light_data.shape = "DISK"
        light_data.size = size
        light = bpy.data.objects.new(name, light_data)
        scene.collection.objects.link(light)
        light.location = location
        point_camera(light, Vector((0.0, 0.0, -0.05)))

    scene.render.engine = "BLENDER_EEVEE_NEXT"
    scene.render.resolution_x = 900
    scene.render.resolution_y = 900
    scene.render.resolution_percentage = 100
    scene.render.image_settings.file_format = "PNG"
    scene.render.filepath = str(output.resolve())
    scene.render.film_transparent = False
    bpy.ops.render.render(write_still=True)


def main() -> None:
    obj = next((item for item in bpy.data.objects if item.type == "MESH" and item.name != "Cube"), None)
    armature = next((item for item in bpy.data.objects if item.type == "ARMATURE"), None)
    if obj is None or armature is None:
        raise RuntimeError("Converted mesh and GTA SA armature were not found")
    apply_stress_pose(armature)
    report = deformation_report(obj)
    print("SPRP_POSE_QA=" + json.dumps(report, sort_keys=True))
    args = sys.argv[sys.argv.index("--") + 1 :] if "--" in sys.argv else []
    if args:
        render_preview(obj, Path(args[0]))


if __name__ == "__main__":
    main()
