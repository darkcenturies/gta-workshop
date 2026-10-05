"""Bake supplied engine-evaluated poses on their paired source-bind rig.

Run in Blender: -- CAPTURE.hsp PAIRED_MODEL.blend OUTPUT.ifp [LIBRARY]
Every joint retains translation. Source-derived files are supplied locally.
"""
import hashlib,json,math,re,sys
from pathlib import Path
import bpy
from mathutils import Matrix,Quaternion,Vector
sys.path.insert(0,str(Path(__file__).resolve().parent))
from unity_runtime_pose import read_capture
from source_bind_rig import canonical
from sa_animation_writer import write_anp3
from validate_sa_animations import validate


def bake(capture_file, model_file, output, library='hss_anim'):
 capture=read_capture(capture_file)
 bpy.ops.wm.open_mainfile(filepath=str(model_file))
 arm=next(o for o in bpy.data.objects if o.type=='ARMATURE')
 if arm.get('source_avatar')!=capture['avatar']:raise ValueError('Capture and paired source bind avatar differ')
 basis=Matrix([arm['source_basis'][i:i+3] for i in range(0,9,3)])
 offset=Vector(arm['source_offset'])
 root=next(b for b in arm.data.bones if int(b['bone_id'])==0)
 root_q=Quaternion((math.sqrt(.5),0,0,math.sqrt(.5)))
 rotate=(root_q@root.matrix_local.to_quaternion().inverted()).to_matrix().to_4x4()
 rotate.translation=root.head_local-rotate.to_3x3()@root.head_local
 basis=rotate.to_3x3()@basis;offset=rotate@offset
 inverse=basis.inverted()
 rest={canonical(b['name']):Matrix(b['rest']) for b in capture['bones']}
 for b in arm.data.bones:
  if 'source_bind_matrix' in b:
   values=b['source_bind_matrix'];rest[b['source_name']]=Matrix([values[i:i+4] for i in range(0,16,4)])
 native_rest={b.name:rotate@b.matrix_local for b in arm.data.bones}
 animations=[];records=[];max_scale_error=0.
 for clip in capture['clips']:
  label=re.sub('[^A-Za-z0-9_]+','_',clip['name']).strip('_')[:23]
  bones={b.name:{'name':b.name,'id':int(b['bone_id']),'translation':True,'keys':[]} for b in arm.data.bones}
  previous={};position_error=rotation_error=0.
  for frame, matrices in enumerate(clip['matrices']):
   posed={canonical(b['name']):Matrix(m) for b,m in zip(capture['bones'],matrices)}
   desired={}
   for bone in arm.data.bones:
    source=bone['source_name'];parent=desired.get(bone.parent.name) if bone.parent else None
    if bone.name==root.name:
     matrix=root_q.to_matrix().to_4x4();matrix.translation=native_rest[root.name].translation
    elif source in posed:
     actual=posed[source];max_scale_error=max(max_scale_error,max(abs(v-1) for v in actual.to_scale()))
     rotation=basis@actual.to_quaternion().to_matrix()@rest[source].to_quaternion().inverted().to_matrix()@inverse@native_rest[bone.name].to_3x3()
     matrix=rotation.to_4x4();matrix.translation=basis@actual.translation+offset
    else:
     local=bone.parent.matrix_local.inverted()@bone.matrix_local
     matrix=parent@local
    desired[bone.name]=matrix
    local=parent.inverted()@matrix if parent else matrix
    q=local.to_quaternion().normalized()
    if bone.name in previous and q.dot(previous[bone.name])<0:q.negate()
    previous[bone.name]=q.copy()
    key={'time':clip['times'][frame],'rotation':[q.x,q.y,q.z,q.w],'position':list(local.translation)}
    bones[bone.name]['keys'].append(key)
  animations.append({'name':label,'bones':list(bones.values())})
  records.append({'source_id':clip['source_id'],'name':label,'frames':len(clip['times']),'duration':clip['times'][-1],'source_foot_ik':clip['foot_ik']})
 if max_scale_error>.001:raise ValueError('Native rigid bones cannot preserve evaluated nonunit scale')
 write_anp3(output,library,animations)
 report={'unity_engine_evaluated':True,'source_avatar':capture['avatar'],'unity_version':capture['unity_version'],
         'capture_sha256':hashlib.sha256(capture_file.read_bytes()).hexdigest(),'model_sha256':hashlib.sha256(model_file.read_bytes()).hexdigest(),
         'source_scale_error_max':max_scale_error,'bones':len(arm.data.bones),'clips':records,'native':validate(output),
         'original_game_pose_fidelity_validated':False,'gameplay_tested':False}
 output.with_suffix('.json').write_text(json.dumps(report,indent=2)+'\n')
 print('ENGINE_BAKE',capture['avatar'],len(animations),'bones',len(arm.data.bones),'scaleError',max_scale_error,flush=True)
 return animations,report


if __name__=='__main__':
 args=sys.argv[sys.argv.index('--')+1:]
 bake(*[Path(p).resolve() for p in args[:3]],*(args[3:4]))
