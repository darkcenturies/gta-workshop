"""Asset-free IK regression; run with Blender --background --python-exit-code 1."""
from pathlib import Path
import math, sys
from mathutils import Matrix, Quaternion, Vector
sys.path.insert(0,str(Path(__file__).resolve().parents[1]))
from unity_humanoid_pose import HumanAvatar, ankle_from_sole

# Internal effector +X points from ankle to sole. A turn of the avatar must
# rotate the offset with the effector, rather than add a fixed world-height.
rotation=Quaternion((0,1,0),math.pi/2)
sole=Vector((0,0,-.08))
ankle=ankle_from_sole(sole,rotation,.28)
assert (ankle-Vector((0,0,.2))).length<1e-6
turn=Quaternion((1,0,0),.7)
assert (ankle_from_sole(turn@sole,turn@rotation,.28)-turn@ankle).length<1e-6

avatar=HumanAvatar.__new__(HumanAvatar)
avatar.names=['LeftUpLeg','LeftLeg','LeftFoot']
avatar.nodes=[{'m_ParentId':-1},{'m_ParentId':0},{'m_ParentId':1}]
def pose():
    return {name:Matrix.Translation(Vector(point)) for name,point in zip(avatar.names,[(0,0,1),(0,.3,.6),(0,0,.2)])}
world=pose();lengths=[.5,.5]
error=avatar._solve_limb(world,avatar.names,ankle)
assert error<1e-6
for i,length in enumerate(lengths):
    assert abs((world[avatar.names[i]].translation-world[avatar.names[i+1]].translation).length-length)<1e-6
a,b,c=[world[name].translation for name in avatar.names]
assert abs(math.degrees((a-b).angle(c-b))-106.2602)<.001
wrong=pose();avatar._solve_limb(wrong,avatar.names,sole)
a,b,c=[wrong[name].translation for name in avatar.names]
assert math.degrees((a-b).angle(c-b))>179
print('Sole/ankle regression passed: rotated offset, exact contact, fixed lengths and unlocked knee.')
