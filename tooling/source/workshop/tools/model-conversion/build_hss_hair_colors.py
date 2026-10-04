"""Build hair-only colour textures and material-slot metadata.

Usage: SOURCE_PACK FINAL_CATALOG_JSON TEXTURES_JSON OUTPUT_MAP
The generated PNGs stay in SOURCE_PACK; append their names to TEXTURES_JSON
before writing the TXD. Body/face/accessory materials are never recoloured.
"""
from pathlib import Path
import hashlib,json,sys
import numpy as np
from PIL import Image

PALETTE=[('Black',(35,30,38)),('Brown',(115,68,42)),('Blond',(239,195,102)),
         ('Red',(179,55,33)),('White',(245,244,249)),('Silver',(164,173,191)),
         ('Pink',(243,113,180)),('Purple',(151,89,222)),('Blue',(62,137,232)),
         ('Green',(75,190,111))]

def recolor(image,rgb):
    pixels=np.asarray(image.convert('RGBA')).copy()
    luminance=pixels[:,:,:3].astype(np.float32)@np.array([.2126,.7152,.0722])
    visible=luminance[pixels[:,:,3]>0]
    anchor=max(1,float(np.percentile(visible,90))) if len(visible) else 255
    shade=np.clip(luminance/anchor,.12,1.15)
    pixels[:,:,:3]=np.clip(shade[:,:,None]*np.array(rgb),0,255).astype(np.uint8)
    return Image.fromarray(pixels)

def main():
    source,catalog,texture_path,output=map(Path,sys.argv[1:5])
    manifest=json.loads((source/'manifest.json').read_text(encoding='utf-8'))
    rows=json.loads(catalog.read_text(encoding='utf-8'))
    textures=json.loads(texture_path.read_text(encoding='utf-8'))
    records=[];generated={};proof=[]
    for row in rows:
        if not row.get('hair_part'):continue
        body=manifest['parts'][row['body_part']];hair=manifest['parts'][row['hair_part']]
        for slot,key in enumerate(hair['materials'],len(body['materials'])):
            material=manifest['materials'][key]
            file=next((t['file'] for t in material['textures'] if t['slot']=='_MainTex' and t['file']),None)
            # The native renderer cannot safely identify a solid material by
            # texture name; leave such slots at their original colour.
            if not file:continue
            original='hss_'+hashlib.sha256(file.encode()).hexdigest()[:10]
            if original not in textures:raise ValueError('Unresolved original hair texture')
            if original not in generated:
                image=Image.open(source/file).convert('RGBA');names=[]
                for index,(label,rgb) in enumerate(PALETTE,1):
                    name=f'hc{index}_{original}';relative=f'hair-colors/{name}.png'
                    path=source/relative;path.parent.mkdir(exist_ok=True)
                    changed=recolor(image,rgb)
                    if not np.array_equal(np.asarray(image)[:,:,3],np.asarray(changed)[:,:,3]):raise ValueError('Alpha changed')
                    changed.save(path);textures[name]=relative;names.append(name)
                    proof.append(dict(texture=name,source=file,color=label,alpha_unchanged=True,sha256=hashlib.sha256(path.read_bytes()).hexdigest()))
                generated[original]=names
            records.append(f'{row["model"]}|{slot}|{original}|'+','.join(generated[original]))
    output.write_text('# model ID|hair material slot|original texture|ten palette textures\n'+'\n'.join(records)+'\n',encoding='utf-8')
    texture_path.write_text(json.dumps(textures,indent=2),encoding='utf-8')
    output.with_suffix('.json').write_text(json.dumps(dict(palette=PALETTE,records=len(records),textures=proof),indent=2),encoding='utf-8')
    print('Hair material records',len(records),'colour textures',len(proof),flush=True)

if __name__=='__main__':main()
