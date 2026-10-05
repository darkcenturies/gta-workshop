"""Check native SA skin bindings, weights and head-bound hair with DragonFF.

Usage: MODEL_DIR CATALOG_JSON DONOR_DFF SOURCE_PACK TEXTURES_JSON OUTPUT_JSON
DragonFF's gtaLib must be available on PYTHONPATH. No game inputs are bundled.
"""
from pathlib import Path
import json,sys
import numpy as np
from gtaLib import dff
models,catalog,donor_path,source,texture_manifest,output=map(Path,sys.argv[1:7])
rows=json.loads(catalog.read_text(encoding='utf-8'));m=json.loads((source/'manifest.json').read_text(encoding='utf-8'))
textures=json.loads(texture_manifest.read_text(encoding='utf-8'))
donor=dff.dff();donor.load_file(str(donor_path));stock=donor.geometry_list[0].extensions['skin']
table=next(f.bone_data.bones for f in donor.frame_list if f.bone_data and f.bone_data.bones)
reports=[]
for row in rows:
 asset=dff.dff();asset.load_file(str(models/(row['model_name']+'.dff')))
 if len(asset.geometry_list)!=1:raise ValueError('Expected one joined geometry')
 g=asset.geometry_list[0];skin=g.extensions['skin']
 actual=next(f.bone_data.bones for f in asset.frame_list if f.bone_data and f.bone_data.bones)
 source_bind=row.get('source_bind_preserved',False)
 tags=[b.id for b in actual]
 if source_bind:
  if skin.num_bones!=62 or len(actual)!=62 or len(set(tags))!=62 or not set(b.id for b in table)<=set(tags):raise ValueError('Invalid expanded source HAnim binding')
  if [b.index for b in actual]!=list(range(62)):raise ValueError('HAnim node indices do not match skin indices')
  stack=1 # The root has an implicit parent matrix on the native stack.
  for bone in actual:
   if bone.type & ~3:raise ValueError('Invalid HAnim topology flags')
   if bone.type&2:stack+=1
   if bone.type&1:stack-=1
   if stack<0:raise ValueError('Unbalanced HAnim topology')
  if stack:raise ValueError('Unbalanced HAnim topology')
 elif list(actual)!=list(table) or skin.num_bones!=32:raise ValueError('Native HAnim binding differs from donor')
 w=np.array(skin.vertex_bone_weights);indices=np.array(skin.vertex_bone_indices)
 if not np.isfinite(w).all() or np.min(w)<0 or np.max(indices)>=skin.num_bones or np.max(abs(w.sum(1)-1))>=1e-5:raise ValueError('Invalid weights')
 if not np.isfinite(np.array(g.vertices)).all():raise ValueError('Non-finite geometry')
 inverse_binds=np.array(skin.bone_matrices)
 if not np.isfinite(inverse_binds).all() or np.min(abs(np.linalg.det(inverse_binds)))<.001:raise ValueError('Invalid inverse bind matrices')
 error=None if source_bind else float(np.max(abs(inverse_binds-np.array(stock.bone_matrices))))
 if error is not None and error>=1e-5:raise ValueError('Native inverse binds differ from donor')
 for material in g.materials:
  for texture in material.textures:
   if texture.name not in textures:raise ValueError('Unresolved texture: '+texture.name)
 hair_vertices=set()
 if row.get('source_hair'):
  body=m['parts'][row['body_part']];hair=m['parts'][row['hair_part']]
  start=len(body['materials']);end=start+len(hair['materials'])
  for t in g.triangles:
   if start<=t.material<end:hair_vertices.update((t.a,t.b,t.c))
  if not hair_vertices:raise ValueError('No hair material vertices: '+row['model_name'])
  for v in hair_vertices:
   if any(indices[v,i]!=tags.index(5) for i in range(4) if w[v,i]>0):raise ValueError('Hair is not head-bound: '+row['model_name'])
 reports.append(dict(model=row['model_name'],vertices=len(g.vertices),native_bone_table_matches_stock=not source_bind,source_bind_preserved=source_bind,bones=skin.num_bones,max_skin_bind_matrix_error=error,hair_head_weighted_vertices=len(hair_vertices),diffuse_references_resolved=True))
output.write_text(json.dumps(reports,indent=2),encoding='utf-8')
print('Native checks passed for',len(reports),'geometries; hair vertices',sum(r['hair_head_weighted_vertices'] for r in reports),flush=True)
