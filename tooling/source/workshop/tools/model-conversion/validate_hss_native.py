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
 if list(actual)!=list(table) or skin.num_bones!=32:raise ValueError('Native HAnim binding differs from donor')
 w=np.array(skin.vertex_bone_weights);indices=np.array(skin.vertex_bone_indices)
 if not np.isfinite(w).all() or np.min(w)<0 or np.max(indices)>=32 or np.max(abs(w.sum(1)-1))>=1e-5:raise ValueError('Invalid weights')
 if not np.isfinite(np.array(g.vertices)).all():raise ValueError('Non-finite geometry')
 error=float(np.max(abs(np.array(skin.bone_matrices)-np.array(stock.bone_matrices))))
 if error>=1e-5:raise ValueError('Native inverse binds differ from donor')
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
   if any(indices[v,i]!=5 for i in range(4) if w[v,i]>0):raise ValueError('Hair is not head-bound: '+row['model_name'])
 reports.append(dict(model=row['model_name'],vertices=len(g.vertices),native_bone_table_matches_stock=True,max_skin_bind_matrix_error=error,hair_head_weighted_vertices=len(hair_vertices),diffuse_references_resolved=True))
output.write_text(json.dumps(reports,indent=2),encoding='utf-8')
print('Native checks passed for',len(reports),'geometries; hair vertices',sum(r['hair_head_weighted_vertices'] for r in reports),flush=True)
