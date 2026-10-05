"""Keep source bind positions and full humanoid articulation on SA HAnim tags.

Supplied donor orientations calibrate stock-animation fallback. Imported poses
must use the paired source matrices and full local joint translations.
"""
from mathutils import Matrix, Vector

CORE = {
 'Hips':(' Pelvis',1),'Spine':(' Spine',2),'Spine3':(' Spine1',3),
 'Neck':(' Neck',4),'Head':(' Head',5),'eye_Left':('L Brow',6),
 'eye_Right':('R Brow',7),'jaw':(' Jaw',8),
 'RightShoulder':('Bip01 R Clavicle',21),'RightArm':(' R UpperArm',22),
 'RightForeArm':(' R ForeArm',23),'RightHand':(' R Hand',24),
 'RightHandIndex1':(' R Finger',25),'RightHandIndex2':('R Finger01',26),
 'LeftShoulder':('Bip01 L Clavicle',31),'LeftArm':(' L UpperArm',32),
 'LeftForeArm':(' L ForeArm',33),'LeftHand':(' L Hand',34),
 'LeftHandIndex1':(' L Finger',35),'LeftHandIndex2':('L Finger01',36),
 'LeftUpLeg':(' L Thigh',41),'LeftLeg':(' L Calf',42),'LeftFoot':(' L Foot',43),'LeftToes':(' L Toe0',44),
 'RightUpLeg':(' R Thigh',51),'RightLeg':(' R Calf',52),'RightFoot':(' R Foot',53),'RightToes':(' R Toe0',54),
 'PelvisRoot':('Belly',201),'Spine1':('R breast',301),'Spine2':('L breast',302),
 'LeftArmRoll':('LeftArmRoll',303),'RightArmRoll':('RightArmRoll',304),
 'LeftForeArmRoll':('LeftForeArmRoll',305),'RightForeArmRoll':('RightForeArmRoll',306),
}
for side in ('Left','Right'):
 for digit in ('Thumb','Index','Middle','Ring','Pinky'):
  for segment in range(1,4):
   source=f'{side}Hand{digit}{segment}'
   if source not in CORE:
    CORE[source]=(source,100+sum(100<=tag<200 for _,tag in CORE.values()))

PARENT={'PelvisRoot':None,'Hips':'PelvisRoot','Spine':'Hips','Spine1':'Spine','Spine2':'Spine1','Spine3':'Spine2','Neck':'Spine3','Head':'Neck','eye_Left':'Head','eye_Right':'Head','jaw':'Head'}
CHILD={'Hips':'Spine','Spine':'Spine1','Spine3':'Neck','Neck':'Head'}
for side in ('Left','Right'):
 for source,parent in [('Shoulder','Spine3'),('Arm',side+'Shoulder'),('ArmRoll',side+'Arm'),('ForeArm',side+'ArmRoll'),('ForeArmRoll',side+'ForeArm'),('Hand',side+'ForeArmRoll'),('UpLeg','Hips'),('Leg',side+'UpLeg'),('Foot',side+'Leg'),('Toes',side+'Foot')]:PARENT[side+source]=parent
 CHILD.update({side+'Shoulder':side+'Arm',side+'Arm':side+'ForeArm',side+'ForeArm':side+'Hand',side+'Hand':side+'HandIndex1',side+'HandIndex1':side+'HandIndex2',side+'UpLeg':side+'Leg',side+'Leg':side+'Foot'})
 for digit in ('Thumb','Index','Middle','Ring','Pinky'):
  for segment in range(1,4):PARENT[f'{side}Hand{digit}{segment}']=side+'Hand' if segment==1 else f'{side}Hand{digit}{segment-1}'


def canonical(name):
 if not name.startswith('Bip001 '):return name
 name=name[7:]
 aliases={'Pelvis':'Hips','Spine':'Spine','Spine1':'Spine3','Neck':'Neck','Head':'Head'}
 for side,prefix in [('L','Left'),('R','Right')]:
  for old,new in [('Clavicle','Shoulder'),('UpperArm','Arm'),('Forearm','ForeArm'),('Hand','Hand'),('Finger0','HandIndex1'),('Finger01','HandIndex2'),('Thigh','UpLeg'),('Calf','Leg'),('Foot','Foot'),('Toe0','Toes')]:aliases[side+' '+old]=prefix+new
 return aliases.get(name,name)


def create_source_bind(arm, capture, basis, offset):
 import bpy
 old={b.name:b.matrix_local.copy() for b in arm.data.bones}
 old_by_tag={int(b['bone_id']):b.matrix_local.copy() for b in arm.data.bones}
 rest={canonical(b['name']):Matrix(b['rest']) for b in capture['bones']}
 missing={'Hips','Head','LeftArm','RightArm','LeftFoot','RightFoot'}-set(rest)
 if missing:raise ValueError(f'Missing required source bind joints: {missing}')
 points={name:basis@m.translation+offset for name,m in rest.items()}
 matrices={};parents=dict(PARENT)
 # Use the source hierarchy where the captured bone has a named counterpart.
 for b in capture['bones']:
  name=canonical(b['name']);p=b['parent']
  if name in CORE and p>=0:
   parent=canonical(capture['bones'][p]['name'])
   if parent in CORE:parents[name]=parent
 children={None:['Root']};children['Root']=[]
 for name in CORE:
  parent=parents[name]
  if parent is None:parent='Root'
  children.setdefault(parent,[]).append(name);children.setdefault(name,[])
 order=[]
 def visit(n):
  if n in order:raise ValueError('Cyclic source bind hierarchy')
  order.append(n)
  for c in children[n]:visit(c)
 visit('Root')
 if len(order)!=len(CORE)+1:raise ValueError('Disconnected source bind hierarchy')
 for source in order:
  if source=='Root':matrices[source]=old_by_tag[0];continue
  name,tag=CORE[source];parent=parents[source] or 'Root'
  if source not in points:
   # Missing source helpers have no invented articulation. Retain a stable
   # donor offset or a zero-length pivot attached to the available parent.
   if source.endswith('Toes'):
    foot=source.replace('Toes','Foot');m=rest[foot]
    points[source]=points[foot]+basis@(-m.to_3x3().col[0].normalized()*.077+m.to_3x3().col[1].normalized()*.089)
   elif source=='PelvisRoot':points[source]=offset.copy()
   else:points[source]=matrices[parent].translation.copy()
  donor=old_by_tag.get(tag)
  if donor is not None:
   rotation=donor.to_3x3()
   sc=CHILD.get(source)
   target_child=CORE.get(sc,('',0))[0]
   if source.startswith(('Left','Right')) and 'Foot' not in source and sc in points and target_child in old:
    a=points[sc]-points[source];b=old[target_child].translation-donor.translation
    if a.length>1e-5 and b.length>1e-5:rotation=a.rotation_difference(b).inverted().to_matrix()@rotation
  else:rotation=matrices[parent].to_3x3()
  matrix=rotation.to_4x4();matrix.translation=points[source];matrices[source]=matrix
 bpy.context.view_layer.objects.active=arm;arm.select_set(True);bpy.ops.object.mode_set(mode='EDIT')
 for b in list(arm.data.edit_bones):arm.data.edit_bones.remove(b)
 for source in order:
  name='Root' if source=='Root' else CORE[source][0]
  bone=arm.data.edit_bones.new(name);bone.head=matrices[source].translation;bone.tail=bone.head+Vector((0,.03,0));bone.matrix=matrices[source];bone.length=.03
  parent=(parents[source] or 'Root') if source!='Root' else None
  if parent:bone.parent=arm.data.edit_bones['Root' if parent=='Root' else CORE[parent][0]]
 bpy.ops.object.mode_set(mode='OBJECT')
 for source in order:
  name='Root' if source=='Root' else CORE[source][0];bone=arm.data.bones[name]
  parent=(parents[source] or 'Root') if source!='Root' else None
  siblings=children[parent] if parent else ['Root']
  bone['bone_id']=0 if source=='Root' else CORE[source][1]
  bone['type']=(2 if siblings[-1]!=source else 0)+(1 if not children[source] else 0)
  bone['source_name']=source
  if source in rest:bone['source_bind_matrix']=[v for row in rest[source] for v in row]
 arm['source_avatar']=capture['avatar'];arm['source_basis']=[v for row in basis for v in row];arm['source_offset']=list(offset)
 return {name:target for name,(target,_) in CORE.items()}
