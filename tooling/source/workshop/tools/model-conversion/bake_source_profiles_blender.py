"""Bake a partition of locally supplied, engine-evaluated wardrobe profiles.

Blender -- JOBS.json OUTPUT_DIR [PARTITION PARTITIONS]
Each job supplies capture/model paths and a six-entry locomotion recipe.
Derived sprint tempos are explicit; original trainer clips retain their timing.
"""
import copy,json,statistics,sys
from pathlib import Path
sys.path.insert(0,str(Path(__file__).resolve().parent))
from bake_runtime_poses_blender import bake
from sa_animation_writer import write_anp3
from unity_runtime_pose import read_capture
from sa_pose_samples import coalesce_native_ticks


def ground_speed(clip):
    # Original clips are in place. Estimate forward travel from a planted
    # foot's backwards velocity, using only low contacts moving backwards.
    values=[]
    for index,bone in enumerate(clip['_bones']):
        if bone['name'] not in ('LeftFoot','RightFoot','Bip001 L Foot','Bip001 R Foot'):continue
        points=[m[index] for m in clip['matrices']]
        heights=sorted(m[1][3] for m in points)
        threshold=heights[len(heights)//3]+.015
        for a,b in zip(points,points[1:]):
            speed=-(b[2][3]-a[2][3])*30
            if max(a[1][3],b[1][3])<=threshold and .08<speed<8:values.append(speed)
    return statistics.median(values) if len(values)>=4 else None


def build(jobs_file,out,partition=0,partitions=1):
    jobs=json.loads(jobs_file.read_text());out.mkdir(parents=True,exist_ok=True)
    if not 0<=partition<partitions:raise ValueError('Invalid partition')
    for i,job in enumerate(jobs):
        if i%partitions!=partition:continue
        bank=out/(job['profile']+'.ifp')
        animations,report=bake(Path(job['capture']),Path(job['model']),bank)
        capture=read_capture(Path(job['capture']))
        sources={c['source_id']:dict(c,_bones=capture['bones']) for c in capture['clips']}
        by_id={record['source_id']:a for record,a in zip(report['clips'],animations)}
        movement=[];recipe=[]
        for slot,entry in enumerate(job['movement']):
            source=entry['source_id'];tempo=entry.get('tempo',1.)
            if not .25<=tempo<=3:raise ValueError('Invalid movement tempo')
            speed=ground_speed(sources[source]) if slot in (0,1,2,5) else 0.
            speed=(speed or entry.get('fallback_speed',0.))*tempo
            if slot in (0,1,2,5) and not .08<=speed<=10:raise ValueError('Invalid locomotion travel')
            a=copy.deepcopy(by_id[source]);a['name']=job['profile']+'_'+('w','r','s','i','b','f')[slot]
            for bone in a['bones']:
                for key in bone['keys']:
                    key['time']/=tempo
                    if bone['id']==0:key['position'][1]+=speed*key['time']
                bone['keys']=coalesce_native_ticks(bone['keys'])
            movement.append(a);recipe.append(dict(entry,name=a['name'],speed=speed))
        write_anp3(out/(job['profile']+'-move.ifp'),'hss_move',movement)
        report['movement']=recipe
        bank.with_suffix('.json').write_text(json.dumps(report,indent=2)+'\n')


if __name__=='__main__':
    args=sys.argv[sys.argv.index('--')+1:]
    build(Path(args[0]).resolve(),Path(args[1]).resolve(),*[int(n) for n in args[2:]])
