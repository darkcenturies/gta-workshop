"""Reconstruct a Unity humanoid FK pose from serialized avatar axes and limits.

Run under Blender (mathutils). This is an offline swing/twist reconstruction;
it does not execute Unity's humanoid IK, stretch, or animator state machine.
Unity 5.6+ channel numbering: root 7..13, four IK goals 14..41, muscles
42..96, fingers 97..136. See UnityCsReference Avatar/HumanTrait bindings and
AssetRipper's HumanoidMuscleType enum for the channel layout.
"""
import math
from mathutils import Vector, Quaternion, Matrix


def vec(value):
    return Vector(tuple(value[k] for k in 'xyz'))


def quat(value):
    return Quaternion(tuple(value[k] for k in 'wxyz')).normalized()


def ankle_from_sole(position, internal_rotation, axis_length):
    return position - internal_rotation @ Vector((axis_length, 0, 0))


# Internal serialized humanoid bone ids, muscle offsets and swing/twist axes.
# Each pair is (muscle offset in the 55 body DOFs, avatar axis).
DOFS = {
    7: [(0, 2), (1, 1), (2, 0)],
    8: [(3, 2), (4, 1), (5, 0)],
    9: [(6, 2), (7, 1), (8, 0)],
    10: [(9, 2), (10, 1), (11, 0)],
    11: [(12, 2), (13, 1), (14, 0)],
    22: [(15, 2), (16, 1)], 23: [(17, 2), (18, 1)],
    24: [(19, 2), (20, 1)],
    1: [(21, 2), (22, 1), (23, 0)],
    3: [(24, 2), (25, 0)], 5: [(26, 2), (27, 1)], 20: [(28, 2)],
    2: [(29, 2), (30, 1), (31, 0)],
    4: [(32, 2), (33, 0)], 6: [(34, 2), (35, 1)], 21: [(36, 2)],
    12: [(37, 2), (38, 1)], 14: [(39, 2), (40, 1), (41, 0)],
    16: [(42, 2), (43, 0)], 18: [(44, 2), (45, 1)],
    13: [(46, 2), (47, 1)], 15: [(48, 2), (49, 1), (50, 0)],
    17: [(51, 2), (52, 0)], 19: [(53, 2), (54, 1)],
}


class HumanAvatar:
    def __init__(self, tree):
        self.tree = tree
        avatar = tree['m_Avatar']
        self.human = avatar['m_Human']['data']
        skeleton = self.human['m_Skeleton']['data']
        self.nodes, self.axes = skeleton['m_Node'], skeleton['m_AxesArray']
        paths = dict(tree['m_TOS'])
        self.names = [paths.get(i, str(i)).split('/')[-1] for i in skeleton['m_ID']]
        self.rest = self.human['m_SkeletonPose']['data']['m_X']
        self.bones = self.human['m_HumanBoneIndex']
        self.muscle_bones = {self.bones[bid]: dofs for bid, dofs in DOFS.items()
                             if bid < len(self.bones) and self.bones[bid] >= 0}
        self.scale = self.human['m_Scale']
        self.root_rest = self.human['m_RootX']
        self.rest_world = self._world([quat(x['q']) for x in self.rest],
                                      [vec(x['t']) for x in self.rest])

    def _world(self, rotations, translations):
        result = []
        for node, q, t in zip(self.nodes, rotations, translations):
            local = Matrix.LocRotScale(t, q, Vector((1, 1, 1)))
            parent = node['m_ParentId']
            result.append(result[parent] @ local if parent >= 0 else local)
        return result

    def pose(self, channels):
        rotations = [quat(x['q']) for x in self.rest]
        translations = [vec(x['t']) for x in self.rest]
        for node_index, dofs in self.muscle_bones.items():
            axes_index = self.nodes[node_index]['m_AxesId']
            if axes_index < 0:
                continue
            axes = self.axes[axes_index]
            angles = [0.0, 0.0, 0.0]
            low, high = vec(axes['m_Limit']['m_Min']), vec(axes['m_Limit']['m_Max'])
            signs = vec(axes['m_Sgn'])
            for muscle, axis in dofs:
                value = channels.get(42 + muscle, 0.0)
                angles[axis] = signs[axis] * value * (high[axis] if value >= 0 else -low[axis])
            swing = Vector((0, angles[1], angles[2]))
            swing_q = Quaternion(swing.normalized(), swing.length) if swing.length > 1e-10 else Quaternion()
            twist_q = Quaternion((1, 0, 0), angles[0])
            rotations[node_index] = quat(axes['m_PreQ']) @ swing_q @ twist_q @ quat(axes['m_PostQ']).inverted()
        hips = self.bones[0]
        body_q = Quaternion((channels.get(13, 1.0), channels.get(10, 0.0),
                             channels.get(11, 0.0), channels.get(12, 0.0))).normalized()
        rotations[hips] = body_q @ quat(self.root_rest['q']).inverted() @ rotations[hips]
        world = self._world(rotations, translations)
        # Keep all joint lengths fixed. Center-of-mass translation is supplied
        # separately for the GTA root; non-root translation channels are omitted.
        masses = self.human['m_HumanBoneMass']
        total = sum(m for i, m in zip(self.bones, masses) if i >= 0)
        rest_center = sum((self.rest_world[i].translation * m for i, m in zip(self.bones, masses) if i >= 0), Vector()) / total
        center = sum((world[i].translation * m for i, m in zip(self.bones, masses) if i >= 0), Vector()) / total
        body_t = Vector(tuple(channels.get(7 + k, vec(self.root_rest['t'])[k] / self.scale) * self.scale for k in range(3)))
        offset = body_t - vec(self.root_rest['t']) + rest_center - center
        result = {name: matrix for name, matrix in zip(self.names, world)}
        for matrix in result.values():
            matrix.translation += offset
        # The serialized goals retain contacts independently of muscle FK.
        # Solve fixed-length limbs using the FK bend direction. This is a
        # two-bone solve, not a claim to reproduce Unity's stretch/anti-pop.
        errors, foot_errors = [], []
        for side, goal, upper, lower, end, human_id in (
            ('Left', 14, 'UpLeg', 'Leg', 'Foot', 5),
            ('Right', 21, 'UpLeg', 'Leg', 'Foot', 6),
            ('Left', 28, 'Arm', 'ForeArm', 'Hand', 18),
            ('Right', 35, 'Arm', 'ForeArm', 'Hand', 19),
        ):
            names = [side + part for part in (upper, lower, end)]
            if not all(n in result for n in names) or not all(goal + i in channels for i in range(7)):
                continue
            node = self.bones[human_id]
            axes = self.axes[self.nodes[node]['m_AxesId']]
            goal_q = Quaternion((channels[goal + 6], channels[goal + 3], channels[goal + 4], channels[goal + 5])).normalized()
            goal_world_q = body_q @ goal_q
            target = body_t + body_q @ Vector(tuple(channels[goal + i] * self.scale for i in range(3)))
            # Serialized foot goals locate the sole, not the ankle bone. The
            # sole displacement is +X in the internal goal rotation frame;
            # invert that displacement before the fixed-length two-bone solve.
            # Hand goals already locate their wrist and need no sole offset.
            if human_id in (5, 6):
                target = ankle_from_sole(target, goal_world_q, axes['m_Length'])
            error = self._solve_limb(result, names, target)
            errors.append(error)
            if human_id in (5, 6):
                foot_errors.append(error)
            old = result[names[-1]].copy()
            desired = (goal_world_q @ quat(axes['m_PostQ']).inverted()).to_matrix().to_4x4()
            desired.translation = old.translation
            delta = desired @ old.inverted()
            self._move_descendants(result, names[-1], delta)
        self.last_goal_errors = errors
        self.last_foot_goal_errors = foot_errors
        # World matrices already include the center translation.
        return result, offset

    def _move_descendants(self, world, name, delta):
        root = self.names.index(name)
        descendants = {root}
        for i, node in enumerate(self.nodes):
            if node['m_ParentId'] in descendants:
                descendants.add(i)
        for i in descendants:
            world[self.names[i]] = delta @ world[self.names[i]]

    def _solve_limb(self, world, names, target):
        a, b, c = (world[n].translation for n in names)
        l1, l2 = (b - a).length, (c - b).length
        direction = target - a
        distance = direction.length
        if min(l1, l2, distance) < 1e-7:
            return distance
        unit = direction.normalized()
        distance = max(abs(l1 - l2) + 1e-6, min(l1 + l2 - 1e-6, distance))
        pole = b - a - unit * (b - a).dot(unit)
        if pole.length < 1e-6:
            pole = Vector((0, 0, 1)) - unit * unit.z
        if pole.length < 1e-6:
            pole = Vector((1, 0, 0)) - unit * unit.x
        along = (l1 * l1 - l2 * l2 + distance * distance) / (2 * distance)
        bend = math.sqrt(max(0, l1 * l1 - along * along))
        knee = a + unit * along + pole.normalized() * bend
        end = a + unit * distance
        upper_delta = (b - a).rotation_difference(knee - a).to_matrix().to_4x4()
        upper_delta.translation = a - upper_delta.to_3x3() @ a
        self._move_descendants(world, names[0], upper_delta)
        current_b, current_c = (world[n].translation for n in names[1:])
        lower_delta = (current_c - current_b).rotation_difference(end - current_b).to_matrix().to_4x4()
        lower_delta.translation = current_b - lower_delta.to_3x3() @ current_b
        self._move_descendants(world, names[1], lower_delta)
        return (world[names[2]].translation - target).length
