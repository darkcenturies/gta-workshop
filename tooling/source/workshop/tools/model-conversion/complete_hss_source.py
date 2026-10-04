from pathlib import Path
import UnityPy, json, re, hashlib, collections, sys
import numpy as np
from UnityPy.classes import PPtr
from UnityPy.helpers.TypeTreeGenerator import TypeTreeGenerator
from UnityPy.helpers.MeshHelper import MeshHandler
from UnityPy.export.MeshExporter import export_mesh_obj
from UnityPy.files.ObjectReader import ObjectReader
from UnityPy.helpers.PackedBitVector import unpack_ints

assets, out = map(Path, sys.argv[1:3])
previous = json.loads((out/'manifest.json').read_text(encoding='utf-8'))
for folder in ('textures','obj','source-data','hair-rest-data'):
 (out/folder).mkdir(parents=True,exist_ok=True)
env=UnityPy.load(str(assets))
generator=TypeTreeGenerator(str(next(iter(env.objects)).assets_file.unity_version))
generator.load_local_dll_folder(str(assets/'Managed'))
env.typetree_generator=generator

def ident(obj):
 if not isinstance(obj,ObjectReader):obj=obj.object_reader
 return f'{obj.assets_file.name}__{obj.path_id}'
def safe(s):return re.sub(r'[^A-Za-z0-9_.-]+','_',s).strip('_') or 'unnamed'
def dump(path,obj):path.write_text(json.dumps(obj,separators=(',',':')),encoding='utf-8')
textures=previous.get('textures',{}); materials=previous.get('materials',{}); meshdata=previous.get('meshes',{}); parts=previous.get('parts',{}); groups=collections.defaultdict(list); errors=[]
def texture(ptr):
 if not ptr.path_id:return None
 tex=ptr.read();key=ident(tex)
 if key in textures:return textures[key]['file']
 path=f'textures/{safe(tex.m_Name)}__{safe(tex.object_reader.assets_file.name)[:8]}_{tex.object_reader.path_id}.png'
 tex.image.save(out/path)
 textures[key]=dict(name=tex.m_Name,file=path,width=tex.m_Width,height=tex.m_Height)
 return path
def material(ptr):
 mat=ptr.read();key=ident(mat)
 if key in materials:return key
 props=mat.m_SavedProperties
 texenv=[]
 for slot,entry in props.m_TexEnvs:
  texenv.append(dict(slot=slot,file=texture(entry.m_Texture),scale=[entry.m_Scale.x,entry.m_Scale.y],offset=[entry.m_Offset.x,entry.m_Offset.y]))
 colors={k:[v.r,v.g,v.b,v.a] for k,v in props.m_Colors}
 materials[key]=dict(name=mat.m_Name,textures=texenv,colors=colors,floats=dict(props.m_Floats))
 return key
def mesh(asset):
 key=ident(asset)
 if key in meshdata:return key
 h=MeshHandler(asset);h.process()
 # UnityPy 1.25.4 mixes the integer accumulator with normalized floats for
 # implicit fourth influences. Decode the original quantized stream explicitly.
 if asset.m_CompressedMesh.m_Weights.m_NumItems:
  ws=iter(unpack_ints(asset.m_CompressedMesh.m_Weights));js=iter(unpack_ints(asset.m_CompressedMesh.m_BoneIndices))
  weights=[];joints=[]
  for vi in range(len(h.m_Vertices)):
   ww=[0.0]*4;jj=[0]*4;total=0
   for k in range(3):
    raw=next(ws);jj[k]=next(js);ww[k]=raw/31;total+=raw
    if total>=31:break
   else:
    ww[3]=(31-total)/31;jj[3]=next(js)
   if total>31:raise ValueError('Invalid compressed weight total')
   weights.append(ww);joints.append(jj)
  h.m_BoneWeights=weights;h.m_BoneIndices=joints
 triangles=h.get_triangles()
 binds=[[[getattr(m,f'e{i}{j}') for j in range(4)] for i in range(4)] for m in asset.m_BindPose or []]
 item=dict(name=asset.m_Name,source=key,vertices=h.m_Vertices,normals=h.m_Normals,uv=h.m_UV0,submeshes=triangles,bone_indices=h.m_BoneIndices,weights=h.m_BoneWeights,bindposes=binds)
 dump(out/'source-data'/f'{safe(key)}.json',item)
 obj=export_mesh_obj(asset)
 if obj:(out/'obj'/f'{safe(asset.m_Name)}__{safe(key)}.obj').write_text(obj,encoding='utf-8')
 meshdata[key]=dict(name=asset.m_Name,file=f'source-data/{safe(key)}.json',vertices=len(h.m_Vertices or []),triangles=sum(len(t) for t in triangles),bones=len(binds))
 return key
def ancestors(ptr):
 chain=[];seen=set()
 while ptr.path_id:
  t=ptr.read();key=ident(t)
  if key in seen:break
  seen.add(key);chain.append((key,t));ptr=t.m_Father
 return chain
for obj in env.objects:
 if obj.type.name!='SkinnedMeshRenderer':continue
 try:
  r=obj.read()
  if not r.m_Mesh.path_id:continue
  a=r.m_Mesh.read();mk=mesh(a)
  mats=[material(p) for p in r.m_Materials if p.path_id]
  signature=mk+'|'+ '|'.join(mats)
  pid=hashlib.sha256(signature.encode()).hexdigest()[:12]
  go=r.m_GameObject.read()
  if pid not in parts:
   bone_rows=[]
   for p in r.m_Bones:
    t=p.read();name=t.m_GameObject.read().m_Name
    bone_rows.append(dict(id=ident(t),name=name,parent=ident(t.m_Father.read()) if t.m_Father.path_id else None))
   parts[pid]=dict(id=pid,name=a.m_Name,mesh=mk,materials=mats,bones=bone_rows,active=go.m_IsActive,source_renderer=ident(obj))
  elif not parts[pid]['bones'] and r.m_Bones:
   # Some scene instances omit their rig, while another instance of the same
   # mesh/material combination supplies it. Prefer the complete reference.
   bone_rows=[]
   for p in r.m_Bones:
    t=p.read();bone_rows.append(dict(id=ident(t),name=t.m_GameObject.read().m_Name,parent=ident(t.m_Father.read()) if t.m_Father.path_id else None))
   parts[pid]['bones']=bone_rows;parts[pid]['source_renderer']=ident(obj)
  if r.m_Bones:
   chain=ancestors(r.m_Bones[0]);candidate=None
   for _,t in chain:
    n=t.m_GameObject.read().m_Name
    if n in ('PelvisRoot','Bip001') and t.m_Father.path_id:
     candidate=t.m_Father.read();break
   if candidate is None:candidate=chain[-1][1]
   gid=ident(candidate)
   if pid not in [p['id'] for p in groups[gid]]:groups[gid].append(dict(id=pid,active=go.m_IsActive,root=candidate.m_GameObject.read().m_Name))
 except Exception as e:
  errors.append(dict(object=ident(obj),error=repr(e)))
for obj in env.objects:
 if obj.type.name!='Mesh':continue
 try:
  a=obj.read()
  if a.m_BindPose or re.search(r'hair|ribbon|catear|bunny|wing|horsemask|headphone|vr_headset|^f0[12]_|^m01_',a.m_Name,re.I):
   mk=mesh(a)
   if not any(p['mesh']==mk for p in parts.values()):
    pid=hashlib.sha256(mk.encode()).hexdigest()[:12]
    parts[pid]=dict(id=pid,name=a.m_Name,mesh=mk,materials=[],bones=[],active=True,source_renderer=None)
 except Exception as e:errors.append(dict(object=ident(obj),error=repr(e)))

# Recover static MeshRenderer metadata as well as skinned renderers. Several
# authored hairstyles otherwise appear only as untextured orphan meshes.
def local_matrix(t):
 p,q,s=t.m_LocalPosition,t.m_LocalRotation,t.m_LocalScale
 x,y,z,w=q.x,q.y,q.z,q.w
 r=np.array([[1-2*(y*y+z*z),2*(x*y-z*w),2*(x*z+y*w)],
             [2*(x*y+z*w),1-2*(x*x+z*z),2*(y*z-x*w)],
             [2*(x*z-y*w),2*(y*z+x*w),1-2*(x*x+y*y)]])
 m=np.eye(4);m[:3,:3]=r@np.diag([s.x,s.y,s.z]);m[:3,3]=[p.x,p.y,p.z]
 return m

def world(t):
 m=local_matrix(t)
 for _,parent in ancestors(t.m_Father):m=local_matrix(parent)@m
 return m

static=[]
for obj in env.objects:
 if obj.type.name!='MeshRenderer':continue
 r=obj.read();go=r.m_GameObject.read();mf=None;transform=None
 for c in go.m_Component:
  p=c[1] if isinstance(c,tuple) else c.component
  if p.type.name=='MeshFilter':mf=p.read()
  elif p.type.name=='Transform':transform=p.read()
 if mf is None or not mf.m_Mesh.path_id:continue
 a=mf.m_Mesh.read()
 if not re.search(r'hair|ribbon|catear|bunny|wing|horsemask|headphone|vr_headset|neko:body',a.m_Name,re.I) or a.m_Name=='hairsalon_in':continue
 mk=mesh(a);mats=[material(p) for p in r.m_Materials if p.path_id]
 if not mats:continue
 pid=hashlib.sha256((mk+'|'+'|'.join(mats)).encode()).hexdigest()[:12]
 chain=ancestors(transform.object_reader);top=chain[-1][1]
 head=next((t for _,t in chain if t.m_GameObject.read().m_Name in ('Head','Bip001 Head')),None)
 placement=np.linalg.inv(world(head))@world(transform) if head is not None else world(transform)
 # Prefer isolated prefab references, whose placement does not include a scene
 # character's translation. Head-relative references are safe for attachments.
 isolated=top.m_GameObject.read().m_Name.lower().find('hair')>=0 or head is not None
 row=dict(id=pid,name=a.m_Name,mesh=mk,materials=mats,bones=[],active=go.m_IsActive,
          source_renderer=ident(obj),attachment_matrix=placement.tolist(),attachment_root=top.m_GameObject.read().m_Name)
 if pid not in parts or (isolated and not parts[pid].get('attachment_isolated')):
  row['attachment_isolated']=isolated;parts[pid]=row
 static.append(dict(part=pid,root=top.m_GameObject.read().m_Name,head_relative=head is not None))

for obj in env.objects:
 if obj.type.name!='SkinnedMeshRenderer':continue
 # A one-bone wearable can have dropped-item and player instances. Recover
 # the player instance relative to Head, including the original skin bind.
 r=obj.read()
 if len(r.m_Bones)==1 and r.m_Mesh.path_id:
  chain=ancestors(r.m_Bones[0]);head=next((t for _,t in chain if t.m_GameObject.read().m_Name in ('Head','Bip001 Head')),None)
  isolated_player=bool(chain and chain[-1][1].m_GameObject.read().m_Name.startswith('PlayerItem'))
  if head is not None or isolated_player:
   mk=ident(r.m_Mesh.read());mats=[material(p) for p in r.m_Materials if p.path_id]
   pid=hashlib.sha256((mk+'|'+'|'.join(mats)).encode()).hexdigest()[:12]
   if pid in parts:
    d=json.loads((out/meshdata[mk]['file']).read_text());t=r.m_Bones[0].read()
    origin=np.linalg.inv(world(head)) if head is not None else np.eye(4)
    parts[pid].update(bones=[],attachment_matrix=(origin@world(t)@np.array(d['bindposes'][0])).tolist(),attachment_root='Head' if head is not None else chain[-1][1].m_GameObject.read().m_Name,attachment_isolated=True,source_renderer=ident(obj))
    continue
 key=ident(obj)
 p=next((p for p in parts.values() if p.get('source_renderer')==key and not p['bones']),None)
 if p is None or p['name']=='neko:body':continue
 r=obj.read();go=r.m_GameObject.read()
 for c in go.m_Component:
  ptr=c[1] if isinstance(c,tuple) else c.component
  if ptr.type.name=='Transform':
   t=ptr.read();p['attachment_matrix']=world(t).tolist()
   p['attachment_root']=ancestors(ptr)[-1][1].m_GameObject.read().m_Name

face_options={};component_audit=[]
for obj in env.objects:
 if obj.type.name!='MonoBehaviour':continue
 try:h=obj.parse_monobehaviour_head();script=h.m_Script.read()
 except Exception:continue
 if script.m_ClassName not in ('FaceTextureChange','NpcFaceTexChange','EyeColorChange'):continue
 data=obj.read_typetree(nodes=obj.generate_monobehaviour_node());go=h.m_GameObject.read()
 models=[]
 for c in go.m_Component:
  p=c[1] if isinstance(c,tuple) else c.component
  if p.type.name=='SkinnedMeshRenderer':
   renderer=p.read();models.append(renderer.m_Mesh.read().m_Name)
 options=[]
 for ref in data.get('TexList',[]):
  ptr=PPtr(**ref,assetsfile=obj.assets_file);decoded=ptr.read()
  options.append(dict(name=decoded.m_Name,file=texture(ptr)))
 row=dict(component=script.m_ClassName,models=models,slot=data.get('matno',data.get('EyeMatNo')),gender=data.get('gender'),skin_slot=data.get('SkinMatNo'),options=options)
 if row not in component_audit:component_audit.append(row)
 for model in models:
  if options:
   candidate=dict(slot=data['matno'],options=options)
   if model in face_options and face_options[model]!=candidate:raise ValueError('Conflicting authored face mappings: '+model)
   face_options[model]=candidate
# Eye-colour inputs and body resources loaded by script rather than referenced
# by a renderer are inventoried without interpreting preview icons as models.
for obj in env.objects:
 if obj.type.name=='Texture2D':
  a=obj.read()
  if re.fullmatch(r'eye_(black|blue|red|green|yellow|white|purple|orange)',a.m_Name) and a.m_Width>=128:
   texture(PPtr(m_FileID=0,m_PathID=obj.path_id,assetsfile=obj.assets_file))

manifest=dict(previous,UnityPy=UnityPy.__version__,meshes=meshdata,parts=parts,materials=materials,textures=textures,errors=errors)
manifest['face_options']=face_options
manifest['component_audit']=component_audit
manifest['static_renderer_audit']=static
(out/'manifest.json').write_text(json.dumps(manifest,indent=2),encoding='utf-8')
print('Meshes',len(meshdata),'parts',len(parts),'textures',len(textures),'face-enabled meshes',len(face_options),'static references',len(static),'errors',errors)
