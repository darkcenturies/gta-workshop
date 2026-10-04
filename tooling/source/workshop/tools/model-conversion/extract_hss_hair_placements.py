"""Recover independent hair prefab placement from locally supplied Unity assets.

Usage: python extract_hss_hair_placements.py UNITY_ASSET_DIRECTORY SOURCE_PACK
Requires UnityPy and an extraction manifest with source_renderer identities.
"""
import json
import sys
from pathlib import Path
import UnityPy
import numpy as np

assets, pack = map(Path, sys.argv[1:3])
manifest = json.loads((pack / 'manifest.json').read_text())
renderers = {p['source_renderer']: p for p in manifest['parts'].values()
             if p['bones'] and ('hair' in p['name'].lower() or
             p['name'] in ('biscuittwin', 'biscuitgirlnejineji', 'fumiko1',
                          'unitychan03', 'unitychan00__UV:unitychan', 'pronama2'))}
placements = {}
rest_directory = pack / 'hair-rest-data'
rest_directory.mkdir(exist_ok=True)
def local_matrix(transform):
    p, q, s = transform.m_LocalPosition, transform.m_LocalRotation, transform.m_LocalScale
    x, y, z, w = q.x, q.y, q.z, q.w
    rotation = np.array([[1-2*(y*y+z*z), 2*(x*y-z*w), 2*(x*z+y*w)],
                         [2*(x*y+z*w), 1-2*(x*x+z*z), 2*(y*z-x*w)],
                         [2*(x*z-y*w), 2*(y*z+x*w), 1-2*(x*x+y*y)]])
    matrix = np.eye(4)
    matrix[:3,:3] = rotation @ np.diag([s.x,s.y,s.z])
    matrix[:3,3] = [p.x,p.y,p.z]
    return matrix
def world_matrix(transform):
    matrix = local_matrix(transform)
    while transform.m_Father.path_id:
        transform = transform.m_Father.read()
        matrix = local_matrix(transform) @ matrix
    return matrix
for obj in UnityPy.load(str(assets)).objects:
    identity = f'{obj.assets_file.name}__{obj.path_id}'
    if obj.type.name != 'SkinnedMeshRenderer' or identity not in renderers:
        continue
    part = renderers[identity]
    renderer = obj.read()
    game_object = renderer.m_GameObject.read()
    for component in game_object.m_Component:
        pointer = component[1] if isinstance(component, tuple) else component.component
        if pointer.type.name != 'Transform':
            continue
        root = pointer.read()
        seen = set()
        while root.m_Father.path_id:
            identity = (root.object_reader.assets_file.name, root.object_reader.path_id)
            if identity in seen:
                raise ValueError('Cyclic prefab hierarchy')
            seen.add(identity)
            root = root.m_Father.read()
        position, rotation, scale = root.m_LocalPosition, root.m_LocalRotation, root.m_LocalScale
        placements[part['name']] = dict(root=root.m_GameObject.read().m_Name,
            position=[position.x, position.y, position.z],
            rotation=[rotation.w, rotation.x, rotation.y, rotation.z],
            scale=[scale.x, scale.y, scale.z])
        if root.m_GameObject.read().m_Name not in ('f01_kumagames_school_00', 'm01_kumagames_school_00'):
            decoded = json.loads((pack / manifest['meshes'][part['mesh']]['file']).read_text())
            vertices = np.column_stack([decoded['vertices'], np.ones(len(decoded['vertices']))])
            matrices = np.array([world_matrix(bone.read()) @ np.array(bind)
                for bone, bind in zip(renderer.m_Bones, decoded['bindposes'])])
            weights, indices = np.array(decoded['weights']), np.array(decoded['bone_indices'])
            if len(matrices) != len(decoded['bindposes']):
                raise ValueError('Incomplete source hair skeleton')
            evaluated = np.zeros((len(vertices),4))
            for influence in range(weights.shape[1]):
                evaluated += np.einsum('nij,nj->ni',matrices[indices[:,influence]],vertices) * weights[:,influence,None]
            old = (local_matrix(root) @ vertices.T).T
            error = float(np.max(np.linalg.norm(evaluated[:,:3]-old[:,:3],axis=1)))
            path = f'hair-rest-data/{part["id"]}.json'
            (pack / path).write_text(json.dumps(evaluated[:,:3].tolist(),separators=(',',':')),encoding='utf-8')
            placements[part['name']].update(attachment_vertices=path,rest_binding_displacement=error)
missing = {p['name'] for p in renderers.values()} - placements.keys()
if missing:
    raise ValueError(f'Missing placement transforms: {sorted(missing)}')
(pack / 'hair-placements.json').write_text(json.dumps(placements, indent=2), encoding='utf-8')
print(f'Recovered {len(placements)} prefab placement transforms.')
