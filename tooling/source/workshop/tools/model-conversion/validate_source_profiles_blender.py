"""Compare compressed FK joint positions with supplied original engine poses.

Blender -- JOBS.json BANK_DIR REPORT.json [NATIVE_FIXTURE.txt]
All clips, three nonperiodic samples, all available source joints per profile.
This reads ANP3 directly: nonroot translations are absolute local positions.
"""
import json,math,sys
from pathlib import Path
import bpy
from mathutils import Matrix,Quaternion,Vector
sys.path.insert(0,str(Path(__file__).resolve().parent))
from sa_pose_samples import read_samples
from source_bind_rig import canonical
from unity_runtime_pose import read_capture

def validate_jobs(jobs_file,banks,report_file,fixture=None):
    reports=[];output=fixture.open('w') if fixture else None
    for job in json.loads(jobs_file.read_text()):
        bpy.ops.wm.open_mainfile(filepath=job['model'])
        arm=next(o for o in bpy.data.objects if o.type=='ARMATURE')
        capture=read_capture(job['capture'])
        root=next(b for b in arm.data.bones if b['bone_id']==0)
        rotate=(Quaternion((math.sqrt(.5),0,0,math.sqrt(.5)))@root.matrix_local.to_quaternion().inverted()).to_matrix().to_4x4()
        rotate.translation=root.head_local-rotate.to_3x3()@root.head_local
        basis=rotate.to_3x3()@Matrix([arm['source_basis'][i:i+3] for i in range(0,9,3)])
        offset=rotate@Vector(arm['source_offset'])
        source={c['source_id']:c for c in capture['clips']};worst=0.;samples=joints=0
        clips=read_samples(banks/(job['profile']+'.ifp'))
        for clip in clips:
            original=source[int(clip['name'].split('_')[0][1:])]
            frames=len(original['times']);by_tag={b['id']:b for b in clip['bones']}
            for frame in sorted({0,frames//3,2*frames//3}):
                poses={};actual={canonical(b['name']):Matrix(m) for b,m in zip(capture['bones'],original['matrices'][frame])}
                for bone in arm.data.bones:
                    key=by_tag[bone['bone_id']]['keys'][frame];x,y,z,w=key['rotation']
                    local=Quaternion((w,x,y,z)).normalized().to_matrix().to_4x4();local.translation=Vector(key['position'])
                    poses[bone.name]=poses[bone.parent.name]@local if bone.parent else local
                    if bone['source_name'] in actual:
                        expected=basis@actual[bone['source_name']].translation+offset
                        worst=max(worst,(poses[bone.name].translation-expected).length);joints+=1
                samples+=1
                if output and len(reports)==0:
                    values=[];origin=poses[root.name].translation
                    for bone in arm.data.bones:
                        m=poses[bone.name]
                        for column in range(3):values.extend(m[row][column] for row in range(3))
                        values.extend(m.translation-origin)
                    output.write(clip['name']+' '+str(key['time'])+' '+str(len(poses))+' '+' '.join(format(v,'.8g') for v in values)+'\n')
        if worst>.006:raise ValueError(f"Source FK fidelity failed {job['source_body']}: {worst}")
        reports.append(dict(profile=job['profile'],source_body=job['source_body'],source_avatar=capture['avatar'],clips=len(clips),samples=samples,joints=joints,source_position_error_max=worst))
        print('SOURCE_PROFILE_VALID',job['profile'],worst,flush=True)
    if output:output.close()
    report_file.write_text(json.dumps(reports,indent=2)+'\n')

if __name__=='__main__':
    args=[Path(p).resolve() for p in sys.argv[sys.argv.index('--')+1:]]
    validate_jobs(*args)
