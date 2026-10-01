from pathlib import Path
import json,pefile,struct,hashlib,capstone
ROOT=Path(__file__).resolve().parent
import argparse
parser=argparse.ArgumentParser(description='Build the exact-version experimental S&SMP DL adapter; never overwrites the input.')
parser.add_argument('--source',type=Path,required=True,help='Unmodified S&SMP 1.3.1 Patch 1 ssmptw.asi')
source=parser.parse_args().source.resolve()
if source == (ROOT/'ssmptw-dl-test.asi').resolve(): raise SystemExit('Input must not be the output path')
expected='47daa8ce8152de39a25f04aecdf0843a449ed941d5705aa2e087ec0f59cf98eb'
data=bytearray(source.read_bytes());assert hashlib.sha256(data).hexdigest()==expected,'Source must be the unmodified archived S&SMP build'
p=pefile.PE(data=bytes(data));base=p.OPTIONAL_HEADER.ImageBase
inventory=json.loads((ROOT.parent/'full-inventory.json').read_text());mapping=json.loads((ROOT.parent/'combined-mapping.json').read_text());changes=[]
for site in inventory['sites']:
    old=int(site['offset'],16);new=int(mapping[site['offset']]['target'],16);pos=site['operand_file_offset']
    assert struct.unpack_from('<I',data,pos)[0]==old,site
    struct.pack_into('<I',data,pos,new);changes.append(dict(site,new_offset=hex(new)))
# Stored patch destinations consumed by FUN_10014a4b. These are data, not
# instructions, and were absent from the original instruction-only inventory.
table_old=[0xa71d7,0xa718c,0xb3573,0xa0265,0xa71ce,0xb3549,0xb387b,0xb38bb,0xb38fb]
table_new=[0xa7657,0xa760c,0xb3a03,0xa07b5,0xa764e,0xb39d9,0xb3d0b,0xb3d4b,0xb3d8b]
for i,(old,new) in enumerate(zip(table_old,table_new)):
    rva=0x510fc+4*i; pos=p.get_offset_from_rva(rva)
    assert struct.unpack_from('<I',data,pos)[0]==old
    struct.pack_into('<I',data,pos,new)
    changes.append(dict(site=hex(rva),offset=hex(old),new_offset=hex(new),kind='model-table-patch-destination'))
def align(n,a):return (n+a-1)//a*a
section_rva=align(max(s.VirtualAddress+s.Misc_VirtualSize for s in p.sections),p.OPTIONAL_HEADER.SectionAlignment)
code=bytearray();labels={};fixups=[]
def emit(h):code.extend(bytes.fromhex(h))
def u32(v):code.extend(struct.pack('<I',v&0xffffffff))
def label(n):labels[n]=len(code)
def jz(n):emit('0f84');fixups.append((len(code),n,'rel'));u32(0)
def relative_data(op,n):emit(op);fixups.append((len(code),n,'rva'));u32(0)
imports={i.name.decode():i.address-base for e in p.DIRECTORY_ENTRY_IMPORT for i in e.imports if i.name}
def call_import(n):emit('ff93');u32(imports[n])
emit('55 8bec 53 56 57 e8 00000000 5b 81eb');u32(section_rva+11)
emit('ff7508');call_import('GetModuleHandleA');emit('8bf0 85c0');jz('done')
relative_data('39b3','cache');jz('done')
relative_data('8d83','library');emit('50');call_import('LoadLibraryA');emit('85c0');jz('failure')
relative_data('8d8b','symbol');emit('51 50');call_import('GetProcAddress');emit('85c0');jz('failure')
emit('56 ffd0');relative_data('89b3','cache')
label('done');emit('8bc6 5f 5e 5b 8be5 5d c20400')
label('failure');emit('68');u32(0x5045444c);call_import('ExitProcess');emit('cc')
label('cache');u32(0)
label('library');code.extend(b'Valkyrie-DL-Guard.dll\0')
label('symbol');code.extend(b'_ValidateSamp@4\0')
for pos,name,kind in fixups:struct.pack_into('<I',code,pos,(labels[name]-(pos+4) if kind=='rel' else section_rva+labels[name])&0xffffffff)
# Both independently cached module getters must pass through the same guard.
for rva in [0x3ece,0x1784d]:
    pos=p.get_offset_from_rva(rva);assert data[pos:pos+2]==b'\xff\x15'
    assert struct.unpack_from('<I',data,pos+2)[0]==base+imports['GetModuleHandleA']
    data[pos:pos+6]=b'\xe8'+struct.pack('<i',section_rva-(rva+5))+b'\x90'
# The replaced indirect calls had absolute IAT operands. Their HIGHLOW
# relocations must not be applied to the new relative call displacements.
retired_relocations=[]
for block in p.DIRECTORY_ENTRY_BASERELOC:
    for entry in block.entries:
        if entry.rva in (0x3ed0, 0x1784f, 0x14a12):
            assert entry.type == pefile.RELOCATION_TYPE['IMAGE_REL_BASED_HIGHLOW']
            struct.pack_into('<H', data, entry.struct.get_file_offset(), entry.rva & 0xfff)
            retired_relocations.append(entry.rva)
assert sorted(retired_relocations) == [0x3ed0, 0x14a12, 0x1784f]
# Preserve DL's original version string pointer and its matching wire length.
# S&SMP otherwise replaces it with "0.3.7" without adapting DL's length.
version_write=p.get_offset_from_rva(0x14a10)
assert data[version_write:version_write+6] == bytes.fromhex('c706cc110510')
data[version_write:version_write+6] = b'\x90'*6
header=p.sections[-1].get_file_offset()+40
assert header+40<=p.OPTIONAL_HEADER.SizeOfHeaders
assert not any(data[header:header+40]),'No spare PE section header'
raw=align(len(data),p.OPTIONAL_HEADER.FileAlignment);rawsize=align(len(code),p.OPTIONAL_HEADER.FileAlignment)
data.extend(bytes(raw-len(data)));data.extend(code);data.extend(bytes(rawsize-len(code)))
data[header:header+40]=struct.pack('<8sIIIIIIHHI',b'.pedl\0\0\0',len(code),section_rva,rawsize,raw,0,0,0,0,0xe0000060)
struct.pack_into('<H',data,p.FILE_HEADER.get_field_absolute_offset('NumberOfSections'),len(p.sections)+1)
struct.pack_into('<I',data,p.OPTIONAL_HEADER.get_field_absolute_offset('SizeOfImage'),align(section_rva+len(code),p.OPTIONAL_HEADER.SectionAlignment))
struct.pack_into('<I',data,p.OPTIONAL_HEADER.get_field_absolute_offset('CheckSum'),0)
out=ROOT/'ssmptw-dl-test.asi';out.write_bytes(data)
pe=pefile.PE(str(out));assert len(pe.sections)==len(p.sections)+1
assert [(e.name,e.ordinal,e.address) for e in p.DIRECTORY_ENTRY_EXPORT.symbols]==[(e.name,e.ordinal,e.address) for e in pe.DIRECTORY_ENTRY_EXPORT.symbols]
md=capstone.Cs(capstone.CS_ARCH_X86,capstone.CS_MODE_32)
(ROOT/'guard-bootstrap.asm.txt').write_text('\n'.join(hex(i.address)+' '+i.mnemonic+' '+i.op_str for i in md.disasm(code[:labels['cache']],section_rva)))
(ROOT/'patch-manifest.json').write_text(json.dumps({'experimental':True,'source_sha256':expected,'output_sha256':hashlib.sha256(data).hexdigest(),'guard_rva':hex(section_rva),'changes':changes,'limitations':'Address retargeting build. Runtime and class-layout verification ongoing.'},indent=2))
print('Built',out,'address sites:',len(changes),'guard RVA:',hex(section_rva),'SHA256:',hashlib.sha256(data).hexdigest())
