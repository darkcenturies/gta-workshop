#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <wincrypt.h>
#include <cstdio>
#include <cstring>

static HMODULE selfModule;
static uintptr_t* sharedModels;
static uintptr_t originalModels;
static BYTE* dlModule;
static void Log(const char* text);
static int __cdecl InstallSharedLookups() {
    const DWORD version=*reinterpret_cast<DWORD*>(dlModule+0x2ac9b8);
    BYTE* entries=dlModule+(version==1 ? 0x152ae8 : 0x1538b8);
    unsigned normal=0,adapted=0;
    for(unsigned offset=0;offset<0xdcf;offset+=5) {
        uintptr_t address;memcpy(&address,entries+offset,4);
        BYTE* instruction=reinterpret_cast<BYTE*>(address);
        BYTE expectedOpcode=entries[offset+4];
        BYTE* operand=nullptr;
        if(*instruction==expectedOpcode) {
            if(expectedOpcode==0x8b || expectedOpcode==0x89 || expectedOpcode==0x39) operand=instruction+3;
            else if(expectedOpcode==0xbe || expectedOpcode==0xbf) operand=instruction+1;
            if(operand) ++normal;
        }
        if(!operand) continue;
        DWORD previous;
        if(!VirtualProtect(operand,4,PAGE_EXECUTE_READWRITE,&previous)) return 0;
        memcpy(operand,&sharedModels,4);
        VirtualProtect(operand,4,previous,&previous);
        FlushInstructionCache(GetCurrentProcess(),operand,4);
    }
    // FLA moves 286 lookups into generated executable trampolines. Match the
    // original pointer, a complete indexed x4 instruction, and a jump back
    // to a DL-enumerated continuation; do not alter arbitrary pointer data.
    uintptr_t cursor=0;
    MEMORY_BASIC_INFORMATION region={};
    while(cursor<0x80000000u && VirtualQuery(reinterpret_cast<void*>(cursor),&region,sizeof(region))) {
        uintptr_t next=reinterpret_cast<uintptr_t>(region.BaseAddress)+region.RegionSize;
        if(next<=cursor) break;
        if(region.State==MEM_COMMIT && region.Type==MEM_PRIVATE && (region.Protect&0xf0) && !(region.Protect&(PAGE_GUARD|PAGE_NOACCESS))) {
            BYTE* bytes=static_cast<BYTE*>(region.BaseAddress);
            for(size_t n=3;n+9<=region.RegionSize;++n) {
                uintptr_t value;memcpy(&value,bytes+n,4);
                if(value!=originalModels || bytes[n+4]!=0xe9) continue;
                if(bytes[n-3]!=0x8b && bytes[n-3]!=0x89 && bytes[n-3]!=0x39) continue;
                if((bytes[n-2]&0xc7)!=4 || (bytes[n-1]&0xc7)!=0x85) continue;
                int displacement;memcpy(&displacement,bytes+n+5,4);
                uintptr_t continuation=reinterpret_cast<uintptr_t>(bytes+n+9)+displacement;
                bool known=false;
                for(unsigned offset=0;offset<0xdcf;offset+=5) {
                    uintptr_t site;memcpy(&site,entries+offset,4);
                    if(continuation==site+7) {known=true;break;}
                }
                if(!known) continue;
                DWORD previous;
                if(!VirtualProtect(bytes+n,4,PAGE_EXECUTE_READWRITE,&previous)) return 0;
                memcpy(bytes+n,&sharedModels,4);
                VirtualProtect(bytes+n,4,previous,&previous);
                FlushInstructionCache(GetCurrentProcess(),bytes+n,4);
                ++adapted;
            }
        }
        cursor=next;
    }
    *reinterpret_cast<DWORD*>(dlModule+0x1e0444)=1;
    char message[140];sprintf_s(message,"Shared lookup installation: %u native sites, %u PE-changed sites",normal,adapted);Log(message);
    return 1;
}
static uintptr_t __stdcall LookupSharedModel(int id) {
    if (!sharedModels || id < -32768 || id >= 200000) return 0;
    static unsigned skinLogs=0;
    if(id==21999 && sharedModels[id] && skinLogs<4) {
        ++skinLogs;
        auto words=reinterpret_cast<DWORD*>(sharedModels[id]);
        char message[400];
        sprintf_s(message,"Skin21999 info=%08lX words: %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX %08lX",static_cast<unsigned long>(sharedModels[id]),words[0],words[1],words[2],words[3],words[4],words[5],words[6],words[7],words[8],words[9],words[10],words[11],words[12],words[13],words[14],words[15],words[16]); Log(message);
        const BYTE* op=reinterpret_cast<const BYTE*>(0x5e48b2);
        sprintf_s(message,"Ped lookup bytes: %02X %02X %02X %02X %02X %02X %02X",op[0],op[1],op[2],op[3],op[4],op[5],op[6]);Log(message);
    }
    return sharedModels[id];
}
static int __stdcall IsSharedPedModel(int id) {
    auto model=LookupSharedModel(id);
    return id>=0 && model && *reinterpret_cast<DWORD*>(model)==0x85bdc0;
}
static const char expected[] = "bccdb297464bd382625635be25585df07a8fa6668bc0015650708e3eb4ffcd4b";
static void Log(const char* text) {
    wchar_t path[MAX_PATH];
    if (!GetModuleFileNameW(selfModule,path,MAX_PATH)) return;
    wchar_t* slash=wcsrchr(path,L'\\'); if (!slash) return;
    wcscpy_s(slash+1,MAX_PATH-(slash+1-path),L"PE-DL-Guard.log");
    FILE* f=nullptr; _wfopen_s(&f,path,L"ab");
    if(f) { SYSTEMTIME t;GetLocalTime(&t);fprintf(f,"%04u-%02u-%02u %02u:%02u:%02u %s\r\n",t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond,text);fclose(f); }
}
static bool HashFile(const wchar_t* path,char out[65]) {
    HCRYPTPROV provider=0;HCRYPTHASH hash=0;bool ok=false;
    HANDLE f=CreateFileW(path,GENERIC_READ,FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,nullptr,OPEN_EXISTING,0,nullptr);
    if(f==INVALID_HANDLE_VALUE)return false;
    if(CryptAcquireContextW(&provider,nullptr,nullptr,PROV_RSA_AES,CRYPT_VERIFYCONTEXT) && CryptCreateHash(provider,CALG_SHA_256,0,0,&hash)) {
        BYTE buffer[32768],digest[32];DWORD count=0;bool good=true;
        for(;;) {if(!ReadFile(f,buffer,sizeof(buffer),&count,nullptr)){good=false;break;}if(!count)break;if(!CryptHashData(hash,buffer,count,0)){good=false;break;}}
        DWORD len=32;
        if(good&&CryptGetHashParam(hash,HP_HASHVAL,digest,&len,0)&&len==32) { for(unsigned i=0;i<32;i++)sprintf_s(out+i*2,3,"%02x",digest[i]);out[64]=0;ok=true; }
    }
    if(hash)CryptDestroyHash(hash);if(provider)CryptReleaseContext(provider,0);CloseHandle(f);return ok;
}
extern "C" __declspec(dllexport) BOOL __stdcall CheckSamp(HMODULE samp) {
    if(!samp)return FALSE;
    wchar_t path[MAX_PATH];char hash[65]={};
    if(!GetModuleFileNameW(samp,path,MAX_PATH)||!HashFile(path,hash)) {Log("REJECT: could not hash the loaded SA-MP module");return FALSE;}
    char msg[160];sprintf_s(msg,"Loaded SA-MP SHA256=%s",hash);Log(msg);
    if(strcmp(hash,expected)){Log("REJECT: this experimental adapter requires the exact open.mp 0.3.DL client");return FALSE;}
    Log("PASS: exact open.mp 0.3.DL input. Experimental port; gameplay is not yet certified.");
    return TRUE;
}
static void* __cdecl ReadFrameName(void* stream, unsigned length, void* frame) {
    if (!stream || !frame || length > 4096) { Log("REJECT: invalid frame name chunk"); return nullptr; }
    using Read = void* (__cdecl*)(void*, void*, unsigned);
    auto read = reinterpret_cast<Read>(0x7ec9d0);
    char first[24] = {};
    char scratch[256];
    unsigned saved = length < 23 ? length : 23;
    if (saved && !read(stream, first, saved)) return nullptr;
    unsigned remaining = length - saved;
    bool shortened = false;
    while (remaining) {
        unsigned count = remaining < sizeof(scratch) ? remaining : sizeof(scratch);
        if (!read(stream, scratch, count)) return nullptr;
        for (unsigned i=0; i<count; ++i) if (scratch[i]) shortened = true;
        remaining -= count;
    }
    auto offset = *reinterpret_cast<int*>(0xc87c5c);
    memcpy(static_cast<char*>(frame) + offset, first, sizeof(first));
    if (length >= 24) {
        char message[128]; sprintf_s(message, "Frame name: chunk=%u, shortened=%u, stored=%s", length, shortened, first); Log(message);
    }
    return stream;
}
static bool InstallFrameReader(HMODULE samp) {
    BYTE* entry = reinterpret_cast<BYTE*>(samp) + 0xa5c10;
    const BYTE expectedCode[] = {0x55,0x8b,0xec,0x51,0x8b,0x45,0x0c};
    if (memcmp(entry, expectedCode, sizeof(expectedCode))) { Log("REJECT: frame reader bytes differ"); return false; }
    DWORD old;
    if (!VirtualProtect(entry, sizeof(expectedCode), PAGE_EXECUTE_READWRITE, &old)) return false;
    entry[0]=0xe9;
    const DWORD displacement = static_cast<DWORD>(reinterpret_cast<uintptr_t>(&ReadFrameName) - reinterpret_cast<uintptr_t>(entry+5));
    memcpy(entry+1, &displacement, 4); entry[5]=entry[6]=0x90;
    VirtualProtect(entry, sizeof(expectedCode), old, &old);
    FlushInstructionCache(GetCurrentProcess(), entry, sizeof(expectedCode));
    Log("Installed bounded frame-name reader (23 characters plus terminator)");
    return true;
}
static LONG CALLBACK RecordStreamingFault(EXCEPTION_POINTERS* info) {
    if(info && info->ExceptionRecord->ExceptionAddress==reinterpret_cast<void*>(0x5e48cc)) {
        const BYTE* lookup=reinterpret_cast<const BYTE*>(0x5e48b2);
        char message[240];
        sprintf_s(message,"Ped setup fault: id=%08lX info=%08lX shared=%08lX lookup=%02X %02X %02X %02X %02X %02X %02X",info->ContextRecord->Ecx,info->ContextRecord->Edi,static_cast<unsigned long>(reinterpret_cast<uintptr_t>(sharedModels)),lookup[0],lookup[1],lookup[2],lookup[3],lookup[4],lookup[5],lookup[6]); Log(message);
    }
    if (info && info->ExceptionRecord->ExceptionAddress == reinterpret_cast<void*>(0x40c307)) {
        auto c=info->ContextRecord;
        char message[256];
        const BYTE* op=reinterpret_cast<const BYTE*>(0x40c300);
        sprintf_s(message,"Streaming fault: EAX=%08lX EBX=%08lX ECX=%08lX EDX=%08lX ESI=%08lX EDI=%08lX; model lookup bytes=%02X %02X %02X %02X %02X %02X %02X",
            c->Eax,c->Ebx,c->Ecx,c->Edx,c->Esi,c->Edi,op[0],op[1],op[2],op[3],op[4],op[5],op[6]);
        Log(message);
    }
    return EXCEPTION_CONTINUE_SEARCH;
}
static bool ShareModelTable(HMODULE samp) {
    const BYTE* lookup=reinterpret_cast<const BYTE*>(0x40c300);
    if (memcmp(lookup,"\x8b\x1c\x85",3)) { Log("REJECT: model lookup instruction differs"); return false; }
    uintptr_t table=0;
    memcpy(&table,lookup+3,4);
    MEMORY_BASIC_INFORMATION memory = {};
    if (table==0xa9b0c8 || !VirtualQuery(reinterpret_cast<void*>(table),&memory,sizeof(memory)) ||
        memory.State!=MEM_COMMIT || (memory.Protect & (PAGE_GUARD|PAGE_NOACCESS)) ||
        table < reinterpret_cast<uintptr_t>(memory.BaseAddress) ||
        table + 200000u*4u > reinterpret_cast<uintptr_t>(memory.BaseAddress)+memory.RegionSize) {
        Log("REJECT: expanded PE model table not ready or too small"); return false;
    }
    auto slot=reinterpret_cast<uintptr_t*>(reinterpret_cast<BYTE*>(samp)+0x152ae0);
    if (*slot!=reinterpret_cast<uintptr_t>(samp)+0x1c0444) { Log("REJECT: DL model table pointer differs"); return false; }
    // Native DL intentionally indexes negative custom object IDs. Reserve the
    // entire signed 16-bit negative range before PE's positive ID space.
    auto allocation=static_cast<uintptr_t*>(VirtualAlloc(nullptr,(32768u+200000u)*sizeof(uintptr_t),MEM_RESERVE|MEM_COMMIT,PAGE_READWRITE));
    if (!allocation) { Log("REJECT: cannot allocate signed model table"); return false; }
    sharedModels=allocation+32768;
    originalModels=table;
    dlModule=reinterpret_cast<BYTE*>(samp);
    memcpy(sharedModels,reinterpret_cast<void*>(table),200000u*sizeof(uintptr_t));
    *slot=reinterpret_cast<uintptr_t>(sharedModels);
    BYTE* copyCount=reinterpret_cast<BYTE*>(samp)+0xa7606;
    const BYTE oldCount[]={0xb9,0x20,0x4e,0x00,0x00};
    if(memcmp(copyCount,oldCount,sizeof(oldCount))) { Log("REJECT: DL table copy count differs"); return false; }
    DWORD copyProtection;
    if(!VirtualProtect(copyCount,sizeof(oldCount),PAGE_EXECUTE_READWRITE,&copyProtection)) return false;
    const DWORD positiveCount=200000;
    memcpy(copyCount+1,&positiveCount,4);
    VirtualProtect(copyCount,sizeof(oldCount),copyProtection,&copyProtection);
    FlushInstructionCache(GetCurrentProcess(),copyCount,sizeof(oldCount));
    // S&SMP installs this getter over DL's own getter later. Preserve signed
    // indexing there too, otherwise negative IDs still access PE's old table.
    auto ssmp=GetModuleHandleW(L"ssmptw.asi");
    if(!ssmp) return false;
    BYTE* pointerLoad=reinterpret_cast<BYTE*>(ssmp)+0x12de0;
    uintptr_t expectedPointer=reinterpret_cast<uintptr_t>(ssmp)+0x55fdc;
    if(pointerLoad[0]!=0xa1 || memcmp(pointerLoad+1,&expectedPointer,4)) { Log("REJECT: S&SMP model pointer initialization differs"); return false; }
    DWORD pointerProtection;
    if(!VirtualProtect(pointerLoad,5,PAGE_EXECUTE_READWRITE,&pointerProtection)) return false;
    pointerLoad[0]=0xb8;
    memcpy(pointerLoad+1,&sharedModels,4);
    VirtualProtect(pointerLoad,5,pointerProtection,&pointerProtection);
    FlushInstructionCache(GetCurrentProcess(),pointerLoad,5);
    BYTE* getter=reinterpret_cast<BYTE*>(ssmp)+0xed5f;
    const BYTE getterPrefix[]={0x55,0x8b,0xec};
    if(memcmp(getter,getterPrefix,sizeof(getterPrefix))) { Log("REJECT: S&SMP model getter differs"); return false; }
    DWORD getterProtection;
    if(!VirtualProtect(getter,5,PAGE_EXECUTE_READWRITE,&getterProtection)) return false;
    getter[0]=0xe9;
    DWORD relative=static_cast<DWORD>(reinterpret_cast<uintptr_t>(&LookupSharedModel)-reinterpret_cast<uintptr_t>(getter+5));
    memcpy(getter+1,&relative,4);
    VirtualProtect(getter,5,getterProtection,&getterProtection);
    FlushInstructionCache(GetCurrentProcess(),getter,5);
    BYTE* pedCheck=reinterpret_cast<BYTE*>(samp)+0xb39d0;
    const BYTE pedPrefix[]={0x8b,0x44,0x24,0x04,0x85,0xc0};
    if(memcmp(pedCheck,pedPrefix,sizeof(pedPrefix))) {Log("REJECT: DL ped checker differs"); return false;}
    DWORD pedProtection;
    if(!VirtualProtect(pedCheck,6,PAGE_EXECUTE_READWRITE,&pedProtection)) return false;
    pedCheck[0]=0xe9;
    relative=static_cast<DWORD>(reinterpret_cast<uintptr_t>(&IsSharedPedModel)-reinterpret_cast<uintptr_t>(pedCheck+5));
    memcpy(pedCheck+1,&relative,4);pedCheck[5]=0x90;
    VirtualProtect(pedCheck,6,pedProtection,&pedProtection);
    FlushInstructionCache(GetCurrentProcess(),pedCheck,6);
    BYTE* installer=dlModule+0xa7560;
    const BYTE installerPrefix[]={0x56,0x57,0x33,0xff,0x83,0x3d};
    if(memcmp(installer,installerPrefix,sizeof(installerPrefix))) {Log("REJECT: DL lookup installer differs");return false;}
    DWORD installerProtection;
    if(!VirtualProtect(installer,5,PAGE_EXECUTE_READWRITE,&installerProtection)) return false;
    installer[0]=0xe9;
    relative=static_cast<DWORD>(reinterpret_cast<uintptr_t>(&InstallSharedLookups)-reinterpret_cast<uintptr_t>(installer+5));
    memcpy(installer+1,&relative,4);
    VirtualProtect(installer,5,installerProtection,&installerProtection);
    FlushInstructionCache(GetCurrentProcess(),installer,5);
    BYTE* baseLimit=reinterpret_cast<BYTE*>(samp)+0xd56b;
    const BYTE oldLimit[]={0x81,0xf9,0x20,0x4e,0x00,0x00};
    if (memcmp(baseLimit,oldLimit,sizeof(oldLimit))) { Log("REJECT: custom model base limit bytes differ"); return false; }
    DWORD oldProtection;
    if (!VirtualProtect(baseLimit,sizeof(oldLimit),PAGE_EXECUTE_READWRITE,&oldProtection)) return false;
    const DWORD maxBase=199999;
    memcpy(baseLimit+2,&maxBase,4);
    VirtualProtect(baseLimit,sizeof(oldLimit),oldProtection,&oldProtection);
    FlushInstructionCache(GetCurrentProcess(),baseLimit,sizeof(oldLimit));
    char message[160]; sprintf_s(message,"DL signed model table %08lX covers -32768..199999; PE source %08lX copied again at DL initialization",static_cast<unsigned long>(reinterpret_cast<uintptr_t>(sharedModels)),static_cast<unsigned long>(table)); Log(message);
    return true;
}
extern "C" __declspec(dllexport) void __stdcall ValidateSamp(HMODULE samp) {
    if(CheckSamp(samp) && ShareModelTable(samp) && InstallFrameReader(samp)) { AddVectoredExceptionHandler(1,RecordStreamingFault); return; }
    MessageBoxW(nullptr,L"This experimental Eagle adapter requires the verified open.mp 0.3.DL client.\n\nThe game will close before S&SMP applies its patches.\nSee PE-DL-Guard.log or run Restore-Eagle.ps1.",L"Project Eagle DL compatibility",MB_OK|MB_ICONERROR);
    TerminateProcess(GetCurrentProcess(),0x5045444c);
}
BOOL WINAPI DllMain(HINSTANCE h,DWORD reason,LPVOID) {
    if(reason==DLL_PROCESS_ATTACH){selfModule=h;DisableThreadLibraryCalls(h);}
    return TRUE;
}
