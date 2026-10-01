#define DllMain BaselineDllMain
#include "GuardBaseline.cpp"
#undef DllMain
#include <intrin.h>
#include "minhook/include/MinHook.h"
#include "AddressPatches.h"

static decltype(&GetModuleHandleA) originalGetModuleHandleA;
static volatile LONG decision=0;
static SRWLOCK initializationLock=SRWLOCK_INIT;
static const char originalSsmpHash[]="47daa8ce8152de39a25f04aecdf0843a449ed941d5705aa2e087ec0f59cf98eb";
static const char r3Hash[]="9c9b2cc31a4ced6967420b1880c096b5c4e7630e227aa379be4019c21b6fddc1";
static bool ModuleHash(HMODULE module,char result[65]) {
    wchar_t path[MAX_PATH];
    return GetModuleFileNameW(module,path,MAX_PATH) && HashFile(path,result);
}
static void Reject(const char* reason) {
    Log(reason);
    MessageBoxA(nullptr,reason,"PE DL adapter stopped initialization",MB_OK|MB_ICONERROR);
    TerminateProcess(GetCurrentProcess(),0x5045444c);
}
static bool WriteBytes(BYTE* dest,const void* source,SIZE_T size) {
    DWORD protection;
    if(!VirtualProtect(dest,size,PAGE_EXECUTE_READWRITE,&protection)) return false;
    memcpy(dest,source,size);
    DWORD unused;
    bool restored=VirtualProtect(dest,size,protection,&unused)!=FALSE;
    FlushInstructionCache(GetCurrentProcess(),dest,size);
    return restored;
}
static void ApplyRuntimeAdapter(HMODULE ssmp,HMODULE samp) {
    char hash[65]={};
    if(!ModuleHash(ssmp,hash) || strcmp(hash,originalSsmpHash)) {
        Reject("Unsupported or already patched ssmptw.asi. This adapter requires the original S&SMP 1.3.1 Patch 1 file."); return;
    }
    if(!ModuleHash(samp,hash)) {Reject("Cannot identify the loaded SA-MP DLL.");return;}
    if(!strcmp(hash,r3Hash)) {Log("R3-1 detected: original S&SMP behavior retained; no DL patches applied.");InterlockedExchange(&decision,2);return;}
    if(strcmp(hash,expected)) {Reject("Unsupported SA-MP version. Select the verified open.mp 0.3.DL client or R3-1.");return;}
    BYTE* base=reinterpret_cast<BYTE*>(ssmp);
    for(const auto& patch:patches) {
        DWORD current;memcpy(&current,base+patch.rva,4);
        if(current!=patch.before) {Reject("S&SMP memory differs from the verified address inventory. No address edits were applied.");return;}
    }
    BYTE* version=base+0x14a10;
    uintptr_t versionText=reinterpret_cast<uintptr_t>(ssmp)+0x511cc;
    if(version[0]!=0xc7 || version[1]!=0x06 || memcmp(version+2,&versionText,4)) {Reject("S&SMP version initialization differs.");return;}
    // This runs synchronously inside the original S&SMP module lookup, before
    // its returned module base is used to install hooks or direct patches.
    for(const auto& patch:patches) {
        if(!WriteBytes(base+patch.rva,&patch.after,4)) {Reject("Cannot apply a runtime address edit; stopping before S&SMP continues.");return;}
    }
    const BYTE nops[]={0x90,0x90,0x90,0x90,0x90,0x90};
    if(!WriteBytes(version,nops,sizeof(nops))) {Reject("Cannot preserve DL version initialization.");return;}
    ValidateSamp(samp);
    Log("Standalone ASI: applied 303 runtime address edits and tested DL guard. Original S&SMP file unchanged.");
    InterlockedExchange(&decision,2);
}
static HMODULE WINAPI InterceptGetModuleHandleA(LPCSTR name) {
    void* caller=_ReturnAddress();
    HMODULE result=originalGetModuleHandleA(name);
    if(!result || !name || decision==2) return result;
    HMODULE ssmp=GetModuleHandleW(L"ssmptw.asi");
    if(!ssmp) return result;
    uintptr_t offset=reinterpret_cast<uintptr_t>(caller)-reinterpret_cast<uintptr_t>(ssmp);
    if(offset!=0x3ed4 && offset!=0x17853) return result;
    if(result!=GetModuleHandleW(L"samp.dll")) return result;
    AcquireSRWLockExclusive(&initializationLock);
    if(decision==0) {decision=1;ApplyRuntimeAdapter(ssmp,result);}
    ReleaseSRWLockExclusive(&initializationLock);
    return result;
}
BOOL WINAPI DllMain(HINSTANCE module,DWORD reason,LPVOID reserved) {
    if(reason!=DLL_PROCESS_ATTACH) return TRUE;
    BaselineDllMain(module,reason,reserved);
    HMODULE ssmp=GetModuleHandleW(L"ssmptw.asi");
    if(ssmp && *reinterpret_cast<uintptr_t*>(reinterpret_cast<BYTE*>(ssmp)+0x55ff8)) {
        Reject("PE DL adapter loaded after S&SMP initialization. Keep the filename !PE-DL-Adapter.asi and use the supported ASI loader.");return FALSE;
    }
    MH_STATUS init=MH_Initialize();
    if(init!=MH_OK && init!=MH_ERROR_ALREADY_INITIALIZED) return FALSE;
    auto target=reinterpret_cast<void*>(&GetModuleHandleA);
    if(MH_CreateHook(target,reinterpret_cast<void*>(&InterceptGetModuleHandleA),reinterpret_cast<void**>(&originalGetModuleHandleA))!=MH_OK || MH_EnableHook(target)!=MH_OK) {
        Reject("Cannot install the S&SMP initialization interceptor.");return FALSE;
    }
    Log("Standalone ASI armed before S&SMP module lookup.");
    return TRUE;
}
