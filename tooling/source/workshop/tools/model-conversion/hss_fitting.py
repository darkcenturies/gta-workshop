"""Continuous torso fitting for a Unity-to-SA wardrobe conversion."""

TORSO = {' Pelvis', ' Spine', ' Spine1', ' Neck', ' Head', 'L breast', 'R breast'}


def fit_influence(point, destination, frames):
    """Keep anatomical torso shape; fit limbs around donor joint frames."""
    if destination in TORSO:
        _, hips, target_hips = frames[' Pelvis']
        return point - hips + target_hips
    rotation, pivot, target = frames[destination]
    return rotation @ (point - pivot) + target
