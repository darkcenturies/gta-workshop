"""Inspect locally supplied DFFs with native compressed SA animations.

Requires Blender with INU_tools 2.3.1, which imports rig and animation using one
coordinate convention. Inputs and game-derived clips are supplied locally.
Usage after --: MODEL_DIR ANP3_IFP OUTPUT_JSON [COMMA_SEPARATED_MODEL_STEMS] [COMMA_SEPARATED_CLIPS]
"""
from pathlib import Path
import hashlib,json,math,sys
import bpy
import numpy as np

args=sys.argv[sys.argv.index('--')+1:]
models,ifp,output=[Path(p).resolve() for p in args[:3]]
selection=set(args[3].split(',')) if len(args)>3 else None
bpy.ops.preferences.addon_enable(module='INU_tools')
from INU_tools.ops.dff_import import import_dff
from INU_tools.ops.ifp_import import import_ifp,apply_ifp_action,_ifp_cache
from INU_tools.core.ifp import read_ifp

sys.path.insert(0,str(Path(__file__).resolve().parent))
from validate_sa_animations import validate
native=validate(ifp)
clips=read_ifp(str(ifp))
names=args[4].split(',') if len(args)>4 else [a.name.lower() for a in clips.animations]
durations={a.name.lower():max(k.time for b in a.bones for k in b.keyframes)/2 for a in clips.animations}
reports=[]
for path in sorted(models.glob('*.dff')):
 if selection is not None and path.stem not in selection:continue
 bpy.ops.wm.read_factory_settings(use_empty=True)
 bpy.context.scene.render.fps=30
 bpy.context.scene.render.fps_base=1
 bpy.ops.preferences.addon_enable(module='INU_tools')
 objects=import_dff(str(path))
 arm=next(o for o in objects if o.type=='ARMATURE')
 meshes=[o for o in objects if o.type=='MESH']
 import_ifp(str(ifp))
 # INU_tools 2.3.1 divides native 60 Hz ticks by 30; fix its local cache.
 for a in _ifp_cache[str(ifp)].animations:
  for b in a.bones:
   for k in b.keyframes:k.time /= 2
 for name in names:
  first_joints=None;motion=0
  action=next(a.name for a in bpy.data.actions if a.name.lower()==name)
  ok,message=apply_ifp_action(action,arm)
  if not ok:raise RuntimeError(message)
  for fraction in [0,.21,.46,.73]:
   time=durations[name]*fraction
   bpy.context.scene.frame_set(round(time*30))
   bpy.context.view_layer.update()
   root=next(p for p in arm.pose.bones if p.bone.get('bone_id')==0)
   joints={p.name:p.head-root.head for p in arm.pose.bones}
   if first_joints is None:first_joints=joints
   else:motion=max(motion,max((joints[n]-first_joints[n]).length for n in joints))
   stretches=[];bounds=[]
   for obj in meshes:
    rest=np.array([v.co[:] for v in obj.data.vertices])
    evaluated=obj.evaluated_get(bpy.context.evaluated_depsgraph_get())
    mesh=evaluated.to_mesh();posed=np.array([v.co[:] for v in mesh.vertices])
    if not np.isfinite(posed).all():raise RuntimeError(f'{path.name}: non-finite pose')
    edges=np.array([e.vertices[:] for e in obj.data.edges])
    if len(edges):
     before=np.linalg.norm(rest[edges[:,0]]-rest[edges[:,1]],axis=1)
     after=np.linalg.norm(posed[edges[:,0]]-posed[edges[:,1]],axis=1)
     stretches.extend((after[before>1e-4]/before[before>1e-4]).tolist())
    points=[evaluated.matrix_world@v.co for v in mesh.vertices]
    bounds.extend(p.z for p in points)
    evaluated.to_mesh_clear()
   height=max(bounds)-min(bounds)
   if not .2<height<3:raise RuntimeError(f'{path.name}: collapsed or invalid pose {height}')
   reports.append({'model':path.stem,'clip':name,'time_seconds':time,'height':height,
                   'edge_stretch_p99':float(np.percentile(stretches,99)),
                   'edge_stretch_max':float(max(stretches))})
  reports[-1]['relative_joint_motion_max']=motion
 print('POSE_QA='+json.dumps({'model':path.stem,'clips':len(names),'samples':len(reports)}),flush=True)
if not reports:raise RuntimeError('No models validated')
output.write_text(json.dumps({'ifp_sha256':hashlib.sha256(ifp.read_bytes()).hexdigest(),
 'method':'paired INU_tools 2.3.1 DFF/IFP import with native 60 Hz cache correction; four samples per clip',
 'native_time_ticks_per_second':60,'gameplay_tested':False,'samples':reports},indent=2)+'\n',encoding='utf-8')
