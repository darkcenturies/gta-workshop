/*
 * Complete best-effort Ghidra decompiler export.
 * Binary SHA-256: 100d63366daef700caab4998dfb1dde48bb7c3a5136ac7bca8a912a6237517f3
 * This is reconstructed pseudocode, not original vendor source.
 */

/* ================================================================
 * 00016000  FUN_00016000
 * bytes: 12  status: ok
 * ================================================================ */

void FUN_00016000(void)

{
  (*(code *)PTR_0004dffc)();
  return;
}



/* ================================================================
 * 00016050  <EXTERNAL>::operator.new[]
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * operator_new__(uint param_1)

{
  void *pvVar1;

  pvVar1 = (void *)(*(code *)PTR_operator_new___0004e010)();
  return pvVar1;
}



/* ================================================================
 * 000160c0  <EXTERNAL>::std::__throw_future_error
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_future_error(int param_1)

{
  (*(code *)PTR___throw_future_error_0004e02c)();
  return;
}



/* ================================================================
 * 000160d0  <EXTERNAL>::strerror
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strerror(int __errnum)

{
  char *pcVar1;

  pcVar1 = (char *)(*(code *)PTR_strerror_0004e030)();
  return pcVar1;
}



/* ================================================================
 * 000160e0  <EXTERNAL>::memmove
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memmove(void *__dest,void *__src,size_t __n)

{
  void *pvVar1;

  pvVar1 = (void *)(*(code *)PTR_memmove_0004e034)();
  return pvVar1;
}



/* ================================================================
 * 000160f0  FUN_000160f0
 * bytes: 6  status: ok
 * ================================================================ */

void FUN_000160f0(void)

{
  int unaff_EBX;

                    /* WARNING: Could not recover jumptable at 0x000160f0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBX + 0x44))();
  return;
}



/* ================================================================
 * 00016120  __gnu_cxx::__to_xstring<std::__cxx11::string,char>
 * bytes: 6  status: ok
 * ================================================================ */

void __thiscall
__gnu_cxx::__to_xstring<std::__cxx11::string,char>
          (__gnu_cxx *this,_func_int_char_ptr_uint_char_ptr_char_ptr *param_1,uint param_2,
          char *param_3,...)

{
  (*(code *)PTR___to_xstring<std::__cxx11::string,char>_0004e044)();
  return;
}



/* ================================================================
 * 00016130  std::__cxx11::string::string
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* WARNING: Switch with 1 destination removed at 0x00016130 */

void __thiscall std::__cxx11::string::string(string *this,string *param_1)

{
  uint uVar1;
  char *pcVar2;
  undefined4 uVar3;

  uVar1 = *(uint *)(param_1 + 4);
  *(string **)this = this + 8;
  pcVar2 = *(char **)param_1;
  if (0xf < uVar1) {
    uVar3 = FUN_0001e566();
    *(undefined4 *)this = uVar3;
    *(uint *)(this + 8) = uVar1;
  }
  _S_copy(*(char **)this,pcVar2,uVar1);
  *(uint *)(this + 4) = uVar1;
  *(undefined1 *)(*(int *)this + uVar1) = 0;
  return;
}



/* ================================================================
 * 00016140  <EXTERNAL>::memcpy
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memcpy(void *__dest,void *__src,size_t __n)

{
  void *pvVar1;

  pvVar1 = (void *)(*(code *)PTR_memcpy_0004e04c)();
  return pvVar1;
}



/* ================================================================
 * 00016150  <EXTERNAL>::pthread_cancel
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_cancel(pthread_t __th)

{
  int iVar1;

  iVar1 = (*(code *)PTR_pthread_cancel_0004e050)();
  return iVar1;
}



/* ================================================================
 * 00016170  std::__cxx11::string::_M_dispose
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Switch with 1 destination removed at 0x00016170 */

void std::__cxx11::string::_M_dispose(void)

{
}



/* ================================================================
 * 00016180  FUN_00016180
 * bytes: 6  status: ok
 * ================================================================ */

void FUN_00016180(void)

{
  int unaff_EBX;

                    /* WARNING: Could not recover jumptable at 0x00016180. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBX + 0x68))();
  return;
}



/* ================================================================
 * 000161a0  <EXTERNAL>::std::condition_variable::wait
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::condition_variable::wait(unique_lock *param_1)

{
  (*(code *)PTR_wait_0004e064)();
  return;
}



/* ================================================================
 * 000161c0  std::mutex::lock
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Switch with 1 destination removed at 0x000161c0 */

void std::mutex::lock(void)

{
}



/* ================================================================
 * 000161d0  std::__detail::_Map_base<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>,true>::operator[]
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* WARNING: Switch with 1 destination removed at 0x000161d0 */

int __thiscall
std::__detail::
_Map_base<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>,true>
::operator[](_Map_base<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>,true>
             *this,ushort *param_1)

{
  int *piVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  uint uStack_34;
  char cStack_21;
  uint *puStack_20;
  undefined **ppuStack_10;

  ppuStack_10 = &__DT_PLTGOT;
  uVar2 = *param_1;
  uStack_34 = *(uint *)(this + 4);
  puVar5 = (undefined4 *)FUN_0001809e();
  if ((puVar5 == (undefined4 *)0x0) || (piVar6 = (int *)*puVar5, piVar6 == (int *)0x0)) {
    piVar6 = operator_new(7);
    *piVar6 = 0;
    *(undefined1 *)((int)piVar6 + 6) = 0;
    *(ushort *)(piVar6 + 1) = *param_1;
    std::__detail::_Prime_rehash_policy::_M_need_rehash
              ((uint)&cStack_21,(uint)(this + 0x10),*(uint *)(this + 4));
    if (cStack_21 != '\0') {
      _Hashtable<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>
      ::_M_rehash((uint)this,puStack_20);
      uStack_34 = *(uint *)(this + 4);
    }
    uStack_34 = (uint)uVar2 % uStack_34;
    iVar3 = *(int *)this;
    piVar1 = (int *)(iVar3 + uStack_34 * 4);
    if ((int *)*piVar1 == (int *)0x0) {
      iVar4 = *(int *)(this + 8);
      *(int **)(this + 8) = piVar6;
      *piVar6 = iVar4;
      if (iVar4 != 0) {
        *(int **)(iVar3 + ((uint)*(ushort *)(iVar4 + 4) % *(uint *)(this + 4)) * 4) = piVar6;
      }
      *piVar1 = (int)(this + 8);
    }
    else {
      *piVar6 = *(int *)*piVar1;
      *(int **)*piVar1 = piVar6;
    }
    *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1;
  }
  return (int)piVar6 + 6;
}



/* ================================================================
 * 000161f0  <EXTERNAL>::std::__throw_bad_alloc
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_bad_alloc(void)

{
  (*(code *)PTR___throw_bad_alloc_0004e078)();
  return;
}



/* ================================================================
 * 00016210  std::__cxx11::string::_S_copy
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Switch with 1 destination removed at 0x00016210 */

void std::__cxx11::string::_S_copy(char *param_1,char *param_2,uint param_3)

{
  if (param_3 == 1) {
    *param_1 = *param_2;
  }
  else if (param_3 != 0) {
    for (; param_3 != 0; param_3 = param_3 - 1) {
      *param_1 = *param_2;
      param_2 = param_2 + 1;
      param_1 = param_1 + 1;
    }
  }
  return;
}



/* ================================================================
 * 00016220  FUN_00016220
 * bytes: 6  status: ok
 * ================================================================ */

void FUN_00016220(void)

{
  int unaff_EBX;

                    /* WARNING: Could not recover jumptable at 0x00016220. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBX + 0x90))();
  return;
}



/* ================================================================
 * 00016230  std::__detail::__to_chars_len<unsigned_int>
 * bytes: 6  status: ok
 * ================================================================ */

uint std::__detail::__to_chars_len<unsigned_int>(uint param_1,int param_2)

{
  uint uVar1;

  uVar1 = (*(code *)PTR___to_chars_len<unsigned_int>_0004e088)();
  return uVar1;
}



/* ================================================================
 * 00016240  std::this_thread::sleep_for<long_long,std::ratio<1ll,1000ll>>
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Switch with 1 destination removed at 0x00016240 */

void std::this_thread::sleep_for<long_long,std::ratio<1ll,1000ll>>(duration *param_1)

{
}



/* ================================================================
 * 00016250  <EXTERNAL>::std::__throw_length_error
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_length_error(char *param_1)

{
  (*(code *)PTR___throw_length_error_0004e090)();
  return;
}



/* ================================================================
 * 00016260  <EXTERNAL>::std::__future_base::_Result_base::_Result_base
 * bytes: 6  status: ok
 * ================================================================ */

void __thiscall std::__future_base::_Result_base::_Result_base(_Result_base *this)

{
  (*(code *)PTR__Result_base_0004e094)();
  return;
}



/* ================================================================
 * 00016280  std::__cxx11::string::string<std::allocator<char>>
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Switch with 1 destination removed at 0x00016280 */

void __thiscall
std::__cxx11::string::string<std::allocator<char>>(string *this,char *param_1,allocator *param_2)

{
}



/* ================================================================
 * 00016290  <EXTERNAL>::std::condition_variable::notify_one
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::condition_variable::notify_one(void)

{
  (*(code *)PTR_notify_one_0004e0a0)();
  return;
}



/* ================================================================
 * 000162b0  <EXTERNAL>::std::terminate
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::terminate(void)

{
  (*(code *)PTR_terminate_0004e0a8)();
  return;
}



/* ================================================================
 * 000162c0  std::_Function_base::~_Function_base
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Switch with 1 destination removed at 0x000162c0 */

void __thiscall std::_Function_base::~_Function_base(_Function_base *this)

{
  if (*(code **)(this + 8) != (code *)0x0) {
    (**(code **)(this + 8))(this,this,3);
  }
  return;
}



/* ================================================================
 * 00016300  <EXTERNAL>::nanosleep
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int nanosleep(timespec *__requested_time,timespec *__remaining)

{
  int iVar1;

  iVar1 = (*(code *)PTR_nanosleep_0004e0bc)();
  return iVar1;
}



/* ================================================================
 * 00016330  std::thread::~thread
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Switch with 1 destination removed at 0x00016330 */

void __thiscall std::thread::~thread(thread *this)

{
}



/* ================================================================
 * 00016340  std::__cxx11::string::_M_construct
 * bytes: 6  status: ok
 * ================================================================ */

void __thiscall std::__cxx11::string::_M_construct(string *this,uint param_1,char param_2)

{
  (*(code *)PTR__M_construct_0004e0cc)();
  return;
}



/* ================================================================
 * 00016350  std::operator==
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Switch with 1 destination removed at 0x00016350 */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

bool std::operator==(string *param_1,string *param_2)

{
}



/* ================================================================
 * 00016370  <EXTERNAL>::operator.delete
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void operator_delete(void *param_1,uint param_2)

{
  (*(code *)PTR_operator_delete_0004e0d8)();
  return;
}



/* ================================================================
 * 000163e0  <EXTERNAL>::pthread_once
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_once(pthread_once_t *__once_control,__init_routine *__init_routine)

{
  int iVar1;

  iVar1 = (*(code *)PTR_pthread_once_0004e0f4)();
  return iVar1;
}



/* ================================================================
 * 000163f0  <EXTERNAL>::_Unwind_Resume
 * bytes: 6  status: ok
 * ================================================================ */

void _Unwind_Resume(void)

{
  (*(code *)PTR__Unwind_Resume_0004e0f8)();
  return;
}



/* ================================================================
 * 00016400  std::_Hashtable<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>::_M_rehash
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* WARNING: Switch with 1 destination removed at 0x00016400 */

void std::
     _Hashtable<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>
     ::_M_rehash(uint param_1,uint *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  undefined1 *puVar5;
  uint uVar6;
  byte bVar7;
  undefined1 *puStack_24;

  bVar7 = 0;
  if (param_2 == (uint *)0x1) {
    puStack_24 = (undefined1 *)(param_1 + 0x18);
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  else {
    if ((uint *)0x1fffffff < param_2) {
      if ((uint *)0x3fffffff < param_2) {
        std::__throw_bad_array_new_length();
      }
      std::__throw_bad_alloc();
    }
    uVar4 = (int)param_2 << 2;
    puStack_24 = operator_new(uVar4);
    puVar5 = puStack_24;
    for (; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar5 = 0;
      puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    }
  }
  piVar2 = *(int **)(param_1 + 8);
  *(undefined4 *)(param_1 + 8) = 0;
  uVar4 = 0;
  while (uVar6 = uVar4, piVar3 = piVar2, piVar3 != (int *)0x0) {
    piVar2 = (int *)*piVar3;
    uVar4 = (uint)*(ushort *)(piVar3 + 1) % (uint)param_2;
    piVar1 = (int *)(puStack_24 + uVar4 * 4);
    if ((int *)*piVar1 == (int *)0x0) {
      *piVar3 = *(int *)(param_1 + 8);
      *(int **)(param_1 + 8) = piVar3;
      *piVar1 = param_1 + 8;
      if (*piVar3 != 0) {
        *(int **)(puStack_24 + uVar6 * 4) = piVar3;
      }
    }
    else {
      *piVar3 = *(int *)*piVar1;
      *(int **)*piVar1 = piVar3;
      uVar4 = uVar6;
    }
  }
  if (*(void **)param_1 != (void *)(param_1 + 0x18)) {
    operator_delete(*(void **)param_1,*(int *)(param_1 + 4) << 2);
  }
  *(uint **)(param_1 + 4) = param_2;
  *(undefined1 **)param_1 = puStack_24;
  return;
}



/* ================================================================
 * 00016470  <EXTERNAL>::__cxa_throw_bad_array_new_length
 * bytes: 6  status: ok
 * ================================================================ */

void __cxa_throw_bad_array_new_length(void)

{
  (*(code *)PTR___cxa_throw_bad_array_new_length_0004e118)();
  return;
}



/* ================================================================
 * 00016480  std::unique_lock<std::mutex>::~unique_lock
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Switch with 1 destination removed at 0x00016480 */

void __thiscall std::unique_lock<std::mutex>::~unique_lock(unique_lock<std::mutex> *this)

{
}



/* ================================================================
 * 00016490  <EXTERNAL>::std::__throw_bad_array_new_length
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_bad_array_new_length(void)

{
  (*(code *)PTR___throw_bad_array_new_length_0004e120)();
  return;
}



/* ================================================================
 * 000164c0  <EXTERNAL>::__cxa_atexit
 * bytes: 6  status: ok
 * ================================================================ */

void __cxa_atexit(void)

{
  (*(code *)PTR___cxa_atexit_0004e12c)();
  return;
}



/* ================================================================
 * 000164d0  <EXTERNAL>::std::__detail::_Prime_rehash_policy::_M_need_rehash
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__detail::_Prime_rehash_policy::_M_need_rehash(uint param_1,uint param_2,uint param_3)

{
  (*(code *)PTR__M_need_rehash_0004e130)();
  return;
}



/* ================================================================
 * 00016550  <EXTERNAL>::operator.delete[]
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void operator_delete__(void *param_1)

{
  (*(code *)PTR_operator_delete___0004e150)();
  return;
}



/* ================================================================
 * 00016560  FUN_00016560
 * bytes: 6  status: ok
 * ================================================================ */

void FUN_00016560(void)

{
  int unaff_EBX;

                    /* WARNING: Could not recover jumptable at 0x00016560. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(unaff_EBX + 0x160))();
  return;
}



/* ================================================================
 * 00016580  <EXTERNAL>::__assert_fail
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __assert_fail(char *__assertion,char *__file,uint __line,char *__function)

{
  (*(code *)PTR___assert_fail_0004e15c)();
  return;
}



/* ================================================================
 * 00016590  std::__future_base::_State_baseV2::_M_set_result
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */
/* WARNING: Switch with 1 destination removed at 0x00016590 */

void __thiscall
std::__future_base::_State_baseV2::_M_set_result
          (_State_baseV2 *this,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 auStack_5c [12];
  undefined4 uStack_50;
  char cStack_41;
  _State_baseV2 *p_Stack_40;
  undefined4 uStack_3c;
  char *pcStack_38;
  undefined *puStack_34;
  undefined4 uStack_30;
  undefined **ppuStack_2c;
  _State_baseV2 **pp_Stack_28;
  undefined4 *puStack_24;
  undefined1 **ppuStack_20;
  undefined **ppuStack_10;

  ppuStack_10 = &__DT_PLTGOT;
  puVar4 = auStack_5c;
  uStack_30 = 0;
  cStack_41 = '\0';
  uStack_50 = param_3;
  pcStack_38 = &cStack_41;
  p_Stack_40 = this;
  uStack_3c = param_2;
  puStack_34 = PTR__M_do_set_0004dfec;
  ppuStack_2c = &puStack_34;
  pp_Stack_28 = &p_Stack_40;
  puStack_24 = &uStack_3c;
  ppuStack_20 = &pcStack_38;
  piVar1 = (int *)___tls_get_addr();
  *piVar1 = (int)&ppuStack_2c;
  puVar2 = (undefined4 *)___tls_get_addr();
  *puVar2 = PTR__FUN_0004dfa4;
  iVar3 = pthread_once((pthread_once_t *)(this + 0xd),(__init_routine *)PTR___once_proxy_0004dfac);
  if (iVar3 != 0) {
    puVar4 = &stack0xffffff94;
    std::__throw_system_error(iVar3);
  }
  *(undefined4 *)(puVar4 + -4) = 0x1a2e0;
  puVar2 = (undefined4 *)___tls_get_addr();
  *puVar2 = 0;
  *(undefined4 *)(puVar4 + -4) = 0x1a2f0;
  puVar2 = (undefined4 *)___tls_get_addr();
  *puVar2 = 0;
  if (cStack_41 == '\0') {
    if ((char)uStack_50 == '\0') {
      *(undefined4 *)(puVar4 + -0x10) = 2;
      *(undefined4 *)(puVar4 + -0x14) = 0x1a355;
      std::__throw_future_error(*(int *)(puVar4 + -0x10));
    }
  }
  else {
    this = this + 8;
    LOCK();
    iVar3 = *(int *)this;
    *(int *)this = 1;
    UNLOCK();
    if (iVar3 < 0) {
      *(_State_baseV2 **)(puVar4 + -0x10) = this;
      *(undefined4 *)(puVar4 + -0x14) = 0x1a340;
      std::__atomic_futex_unsigned_base::_M_futex_notify_all(*(uint **)(puVar4 + -0x10));
    }
  }
  return;
}



/* ================================================================
 * 000165e0  <EXTERNAL>::std::__atomic_futex_unsigned_base::_M_futex_notify_all
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__atomic_futex_unsigned_base::_M_futex_notify_all(uint *param_1)

{
  (*(code *)PTR__M_futex_notify_all_0004e174)();
  return;
}



/* ================================================================
 * 000165f0  std::__cxx11::to_string
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* WARNING: Switch with 1 destination removed at 0x000165f0 */

__cxx11 * __thiscall std::__cxx11::to_string(__cxx11 *this,uint param_1)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  undefined1 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined4 uStack_e8;
  undefined **ppuStack_10;

  bVar9 = 0;
  uStack_e8 = 1;
  ppuStack_10 = &__DT_PLTGOT;
  uVar3 = param_1;
  do {
    if (uVar3 < 10) {
LAB_0001efc1:
      *(__cxx11 **)this = this + 8;
      if (0xf < uStack_e8) {
        uVar4 = FUN_0001e566();
        *(undefined4 *)this = uVar4;
        *(uint *)(this + 8) = uStack_e8;
      }
      if (uStack_e8 != 0) {
        puVar7 = *(undefined1 **)this;
        uVar3 = uStack_e8;
        if (uStack_e8 == 1) {
          *puVar7 = 0;
        }
        else {
          for (; uVar3 != 0; uVar3 = uVar3 - 1) {
            *puVar7 = 0;
            puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
          }
        }
      }
      *(uint *)(this + 4) = uStack_e8;
      *(undefined1 *)(*(int *)this + uStack_e8) = 0;
      pcVar1 = *(char **)this;
      puVar7 = &DAT_000399f4;
      puVar8 = &uStack_e8;
      for (iVar5 = 0xc9; iVar5 != 0; iVar5 = iVar5 + -1) {
        *(undefined1 *)puVar8 = *puVar7;
        puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
        puVar8 = (undefined4 *)((int)puVar8 + (uint)bVar9 * -2 + 1);
      }
      pcVar6 = pcVar1 + *(int *)(this + 4);
      while (99 < param_1) {
        iVar5 = (param_1 % 100) * 2;
        pcVar6[-1] = *(char *)((int)&uStack_e8 + iVar5 + 1);
        pcVar6[-2] = *(char *)((int)&uStack_e8 + iVar5);
        pcVar6 = pcVar6 + -2;
        param_1 = param_1 / 100;
      }
      cVar2 = (char)param_1 + '0';
      if (9 < param_1) {
        cVar2 = *(char *)((int)&uStack_e8 + param_1 * 2);
        pcVar1[1] = *(char *)((int)&uStack_e8 + param_1 * 2 + 1);
      }
      *pcVar1 = cVar2;
      return this;
    }
    if (uVar3 < 100) {
      uStack_e8 = uStack_e8 + 1;
      goto LAB_0001efc1;
    }
    if (uVar3 < 1000) {
      uStack_e8 = uStack_e8 + 2;
      goto LAB_0001efc1;
    }
    if (uVar3 < 10000) {
      uStack_e8 = uStack_e8 + 3;
      goto LAB_0001efc1;
    }
    uStack_e8 = uStack_e8 + 4;
    uVar3 = uVar3 / 10000;
  } while( true );
}



/* ================================================================
 * 00016630  std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */
/* WARNING: Switch with 1 destination removed at 0x00016630 */

void __thiscall
std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
          (__shared_count<(__gnu_cxx::_Lock_policy)2> *this)

{
  int *piVar1;
  int *piVar2;
  int iVar3;

  piVar2 = *(int **)this;
  if (piVar2 != (int *)0x0) {
    if (DAT_0004eb38 == '\0') {
      LOCK();
      piVar1 = piVar2 + 1;
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
    }
    else {
      iVar3 = piVar2[1];
      piVar2[1] = iVar3 + -1;
    }
    if (iVar3 == 1) {
      (**(code **)(*piVar2 + 8))(piVar2);
      if (DAT_0004eb38 == '\0') {
        LOCK();
        piVar1 = piVar2 + 2;
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
      }
      else {
        iVar3 = piVar2[2];
        piVar2[2] = iVar3 + -1;
      }
      if (iVar3 == 1) {
                    /* WARNING: Could not recover jumptable at 0x0001a483. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)(*piVar2 + 0xc))();
        return;
      }
    }
  }
  return;
}



/* ================================================================
 * 00016650  <EXTERNAL>::std::thread::detach
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::thread::detach(void)

{
  (*(code *)PTR_detach_0004e190)();
  return;
}



/* ================================================================
 * 00016670  std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::_Async_state_impl<BufferHandles::Process()::{lambda()#2}>
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* WARNING: Switch with 1 destination removed at 0x00016670 */

void __thiscall
std::__future_base::
_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::
_Async_state_impl<BufferHandles::Process()::_lambda()_2_>
          (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
           *this,_lambda___2_ *param_1)

{
  _Result_base *this_00;
  int iVar1;
  _Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
  *p_Var2;
  byte bVar3;
  undefined4 uStack_24;
  undefined4 *apuStack_20 [4];
  undefined **ppuStack_10;

  bVar3 = 0;
  ppuStack_10 = &__DT_PLTGOT;
  *(undefined4 *)(this + 0xd) = 0;
  *(undefined4 *)(this + 0x11) = 0;
  *(undefined4 *)(this + 0x15) = 0;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0;
  this[0xc] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
               )0x0;
  *(undefined **)this = PTR_vtable_0004df8c + 8;
  this_00 = operator_new(8);
  *(undefined4 *)this_00 = 0;
  *(undefined4 *)(this_00 + 4) = 0;
  std::__future_base::_Result_base::_Result_base(this_00);
  *(undefined **)this_00 = PTR_vtable_0004dfd0 + 8;
  *(_Result_base **)(this + 0x19) = this_00;
  p_Var2 = this + 0x1d;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)p_Var2 = *(undefined4 *)param_1;
    param_1 = param_1 + (uint)bVar3 * -8 + 4;
    p_Var2 = p_Var2 + (uint)bVar3 * -8 + 4;
  }
  uStack_24 = 0;
  apuStack_20[0] = operator_new(0x10);
  apuStack_20[0][3] = 0;
  *apuStack_20[0] = PTR_vtable_0004df34 + 8;
  apuStack_20[0][1] = this;
  apuStack_20[0][2] = PTR__M_run_0004df54;
  std::thread::_M_start_thread
            ((thread *)&uStack_24,
             (unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)apuStack_20
             ,PTR__M_thread_deps_never_run_0004df48);
  unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
            ((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)apuStack_20
            );
  if (*(int *)(this + 0x11) == 0) {
    *(undefined4 *)(this + 0x11) = uStack_24;
    uStack_24 = 0;
    thread::~thread((thread *)&uStack_24);
    return;
  }
                    /* WARNING: Subroutine does not return */
  std::terminate();
}



/* ================================================================
 * 00016690  <EXTERNAL>::pthread_mutex_lock
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_lock(pthread_mutex_t *__mutex)

{
  int iVar1;

  iVar1 = (*(code *)PTR_pthread_mutex_lock_0004e1a0)();
  return iVar1;
}



/* ================================================================
 * 000166a0  std::unique_lock<std::mutex>::unlock
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Switch with 1 destination removed at 0x000166a0 */

void std::unique_lock<std::mutex>::unlock(void)

{
}



/* ================================================================
 * 000166e0  <EXTERNAL>::operator.new
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * operator_new(uint param_1)

{
  void *pvVar1;

  pvVar1 = (void *)(*(code *)PTR_operator_new_0004e1b4)();
  return pvVar1;
}



/* ================================================================
 * 000166f0  <EXTERNAL>::__errno_location
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int * __errno_location(void)

{
  int *piVar1;

  piVar1 = (int *)(*(code *)PTR___errno_location_0004e1b8)();
  return piVar1;
}



/* ================================================================
 * 00016700  <EXTERNAL>::atoi
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int atoi(char *__nptr)

{
  int iVar1;

  iVar1 = (*(code *)PTR_atoi_0004e1bc)();
  return iVar1;
}



/* ================================================================
 * 00016710  std::unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Switch with 1 destination removed at 0x00016710 */

void __thiscall
std::unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
          (unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *this)

{
  if (*(int **)this == (int *)0x0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00019813. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(**(int **)this + 4))();
  return;
}



/* ================================================================
 * 00016740  <EXTERNAL>::___tls_get_addr
 * bytes: 6  status: ok
 * ================================================================ */

void ___tls_get_addr(void)

{
  (*(code *)PTR____tls_get_addr_0004e1cc)();
  return;
}



/* ================================================================
 * 00016760  std::__cxx11::string::_M_assign
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Switch with 1 destination removed at 0x00016760 */

void std::__cxx11::string::_M_assign(string *param_1)

{
}



/* ================================================================
 * 00016770  std::__cxx11::string::_M_replace
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Switch with 1 destination removed at 0x00016770 */

void std::__cxx11::string::_M_replace(uint param_1,uint param_2,char *param_3,uint param_4)

{
}



/* ================================================================
 * 00016790  <EXTERNAL>::std::condition_variable::condition_variable
 * bytes: 6  status: ok
 * ================================================================ */

void __thiscall std::condition_variable::condition_variable(condition_variable *this)

{
  (*(code *)PTR_condition_variable_0004e1e0)();
  return;
}



/* ================================================================
 * 000167b0  <EXTERNAL>::std::logic_error::logic_error
 * bytes: 6  status: ok
 * ================================================================ */

void __thiscall std::logic_error::logic_error(logic_error *this,string *param_1)

{
  (*(code *)PTR_logic_error_0004e1e8)();
  return;
}



/* ================================================================
 * 000167c0  std::__detail::__to_chars_10_impl<unsigned_int>
 * bytes: 6  status: ok
 * ================================================================ */

void std::__detail::__to_chars_10_impl<unsigned_int>(char *param_1,uint param_2,uint param_3)

{
  (*(code *)PTR___to_chars_10_impl<unsigned_int>_0004e1ec)();
  return;
}



/* ================================================================
 * 000167f0  std::__cxx11::string::_M_is_local
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Switch with 1 destination removed at 0x000167f0 */

bool __thiscall std::__cxx11::string::_M_is_local(string *this)

{
  return *(string **)this == this + 8;
}



/* ================================================================
 * 00016810  <EXTERNAL>::std::__throw_system_error
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_system_error(int param_1)

{
  (*(code *)PTR___throw_system_error_0004e200)();
  return;
}



/* ================================================================
 * 00016820  <EXTERNAL>::std::thread::_M_start_thread
 * bytes: 6  status: ok
 * ================================================================ */

void std::thread::_M_start_thread(void)

{
  (*(code *)PTR__M_start_thread_0004e204)();
  return;
}



/* ================================================================
 * 00016830  <EXTERNAL>::free
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void free(void *__ptr)

{
  (*(code *)PTR_free_0004e208)();
  return;
}



/* ================================================================
 * 00016848  FUN_00016848
 * bytes: 18  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00016848(void)

{
}



/* ================================================================
 * 000168b1  FUN_000168b1
 * bytes: 3  status: ok
 * ================================================================ */

undefined4 FUN_000168b1(void)

{
  return 0;
}



/* ================================================================
 * 000168b4  _INIT_0
 * bytes: 742  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void _INIT_0(void)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 extraout_ECX;
  undefined4 extraout_EDX;

  puVar1 = PTR__string_0004df98;
  __cxa_atexit(PTR__string_0004df98,&PTR_s_max_speed_0004e460,&DAT_0004f520);
  __cxa_atexit(puVar1,&PTR_s_set_accel_0004e448,&DAT_0004f520);
  __cxa_atexit(puVar1,&PTR_s_set_mass_0004e430,&DAT_0004f520);
  __cxa_atexit(puVar1,&PTR_s_set_gears_0004e418,&DAT_0004f520);
  __cxa_atexit(puVar1,&PTR_s_set_drive_type_0004e400,&DAT_0004f520);
  uVar2 = FUN_00016848();
  __cxa_atexit(puVar1,&DAT_0004ebe4,&DAT_0004f520,uVar2);
  uVar2 = FUN_00016848();
  __cxa_atexit(puVar1,&DAT_0004ebcc,&DAT_0004f520,uVar2);
  uVar2 = FUN_00016848();
  __cxa_atexit(puVar1,&DAT_0004ebb4,&DAT_0004f520,uVar2);
  __cxa_atexit(puVar1,&PTR_s_set_heavy_0004e3e8,&DAT_0004f520);
  uVar2 = FUN_00016848();
  __cxa_atexit(puVar1,&DAT_0004eb9c,&DAT_0004f520,uVar2);
  __cxa_atexit(puVar1,&PTR_s_add_max_speed_0004e3d0,&DAT_0004f520);
  __cxa_atexit(puVar1,&PTR_s_add_accel_0004e3b8,&DAT_0004f520);
  __cxa_atexit(puVar1,&PTR_s_add_mass_0004e3a0,&DAT_0004f520);
  uVar2 = FUN_00016848();
  __cxa_atexit(puVar1,&DAT_0004eb84,&DAT_0004f520,uVar2);
  FUN_00016848();
  __cxa_atexit(puVar1,&DAT_0004eb6c,&DAT_0004f520,extraout_EDX);
  __cxa_atexit(puVar1,&PTR_s_subtract_accel_0004e388,&DAT_0004f520);
  __cxa_atexit(puVar1,&PTR_s_subtract_mass_0004e370,&DAT_0004f520);
  FUN_00016848();
  __cxa_atexit(puVar1,&DAT_0004eb54,&DAT_0004f520,extraout_ECX);
  uVar2 = FUN_00016848();
  __cxa_atexit(puVar1,&DAT_0004eb3c,&DAT_0004f520,uVar2);
  DAT_0004eae4 = 8;
  DAT_0004eae0 = (void *)0x0;
  DAT_0004eae8 = (void *)0x0;
  DAT_0004eaec = (void *)0x0;
  DAT_0004eaf0 = 0;
  DAT_0004eaf4 = (undefined4 *)0x0;
  DAT_0004eaf8 = (void *)0x0;
  DAT_0004eafc = (void *)0x0;
  DAT_0004eb00 = 0;
  DAT_0004eb04 = (undefined4 *)0x0;
  DAT_0004eae0 = operator_new(0x20);
  puVar3 = (undefined4 *)((int)DAT_0004eae0 + (DAT_0004eae4 * 2 - 2U & 0xfffffffc));
  DAT_0004eae8 = operator_new(0x1d4);
  DAT_0004eaf0 = (int)DAT_0004eae8 + 0x1d4;
  DAT_0004eaec = DAT_0004eae8;
  DAT_0004eafc = DAT_0004eae8;
  *puVar3 = DAT_0004eae8;
  DAT_0004eaf4 = puVar3;
  DAT_0004eaf8 = DAT_0004eae8;
  DAT_0004eb00 = DAT_0004eaf0;
  DAT_0004eb04 = puVar3;
  std::condition_variable::condition_variable((condition_variable *)&DAT_0004eb08);
  __cxa_atexit(FUN_0001af24,&DAT_0004eae0,&DAT_0004f520);
  return;
}



/* ================================================================
 * 00016bfe  _INIT_1
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void _INIT_1(void)

{
}



/* ================================================================
 * 00016c76  _INIT_2
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void _INIT_2(void)

{
}



/* ================================================================
 * 00016e71  _INIT_3
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void _INIT_3(void)

{
}



/* ================================================================
 * 0001706c  _INIT_4
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void _INIT_4(void)

{
}



/* ================================================================
 * 00017267  FUN_00017267
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017267(void)

{
}



/* ================================================================
 * 000172e6  FUN_000172e6
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000172e6(void)

{
}



/* ================================================================
 * 0001737a  FUN_0001737a
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001737a(void)

{
}



/* ================================================================
 * 000173d6  __i686.get_pc_thunk.bx
 * bytes: 4  status: ok
 * ================================================================ */

/* WARNING: This is an inlined function */

void __i686_get_pc_thunk_bx(void)

{
  return;
}



/* ================================================================
 * 000173da  FUN_000173da
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000173da(void)

{
}



/* ================================================================
 * 000174e8  FUN_000174e8
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000174e8(void)

{
}



/* ================================================================
 * 00017542  FUN_00017542
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017542(void)

{
}



/* ================================================================
 * 000175a9  FUN_000175a9
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000175a9(void)

{
}



/* ================================================================
 * 0001762a  FUN_0001762a
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001762a(void)

{
}



/* ================================================================
 * 0001769e  FUN_0001769e
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001769e(void)

{
}



/* ================================================================
 * 0001771a  FUN_0001771a
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001771a(void)

{
}



/* ================================================================
 * 00017763  FUN_00017763
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017763(void)

{
}



/* ================================================================
 * 000177be  FUN_000177be
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000177be(void)

{
}



/* ================================================================
 * 0001780f  FUN_0001780f
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001780f(void)

{
}



/* ================================================================
 * 0001786e  FUN_0001786e
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001786e(void)

{
}



/* ================================================================
 * 00017994  FUN_00017994
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017994(void)

{
}



/* ================================================================
 * 000179d4  FUN_000179d4
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000179d4(void)

{
}



/* ================================================================
 * 00017b05  FUN_00017b05
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017b05(void)

{
}



/* ================================================================
 * 00017b3a  FUN_00017b3a
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017b3a(void)

{
}



/* ================================================================
 * 00017b6f  FUN_00017b6f
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_00017b6f(void)

{
  return;
}



/* ================================================================
 * 00017b70  FUN_00017b70
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017b70(void)

{
}



/* ================================================================
 * 00017ba6  FUN_00017ba6
 * bytes: 101  status: ok
 * ================================================================ */

bool FUN_00017ba6(int param_1)

{
  uint uVar1;
  bool bVar2;

  uVar1 = *(uint *)(param_1 + 0x82);
  bVar2 = true;
  if ((((1 < (uVar1 & 0xffffffdf) - 0x219) &&
       (bVar2 = uVar1 == 0x1c1 || uVar1 == 0x506a, uVar1 != 0x1c1 && uVar1 != 0x506a)) &&
      (bVar2 = true, 1 < uVar1 - 0x4f11)) && ((1 < uVar1 - 0x4ea2 && (1 < uVar1 - 0x506b)))) {
    bVar2 = uVar1 - 0x7533 < 2;
  }
  return bVar2;
}



/* ================================================================
 * 00017c0b  FUN_00017c0b
 * bytes: 70  status: ok
 * ================================================================ */

uint FUN_00017c0b(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined3 uVar4;
  uint uVar3;
  undefined4 in_ECX;

  iVar2 = *(int *)(param_1 + 0x82);
  uVar1 = iVar2 - 0x219;
  uVar4 = (undefined3)(uVar1 >> 8);
  uVar3 = CONCAT31(uVar4,uVar1 < 2 || iVar2 == 0x4f11);
  if (uVar1 >= 2 && iVar2 != 0x4f11) {
    uVar3 = CONCAT31(uVar4,iVar2 == 0x4ea2) | CONCAT31((int3)((uint)in_ECX >> 8),iVar2 == 0x506b) |
            CONCAT31((int3)((uint)iVar2 >> 8),iVar2 == 0x7533);
  }
  return uVar3;
}



/* ================================================================
 * 00017c51  FUN_00017c51
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_00017c51(void)

{
  return;
}



/* ================================================================
 * 00017c52  FUN_00017c52
 * bytes: 54  status: ok
 * ================================================================ */

void __regparm3 FUN_00017c52(int param_1)

{
  if ((((param_1 != 0x239) && (param_1 != 0x23a)) && (param_1 != 0x4ea3)) &&
     (((param_1 != 0x4f12 && (param_1 != 0x7534)) && (param_1 != 0x506c)))) {
    return;
  }
  return;
}



/* ================================================================
 * 00017c8a  FUN_00017c8a
 * bytes: 76  status: ok
 * ================================================================ */

void __regparm3 FUN_00017c8a(undefined4 param_1,int param_2)

{
  if (((((param_2 != 0x219) && (param_2 != 0x21a)) && (param_2 != 0x1c1)) &&
      ((param_2 != 0x4ea2 && (param_2 != 0x4f11)))) &&
     ((param_2 != 0x506a && ((param_2 != 0x506b && (param_2 != 0x7533)))))) {
    return;
  }
  return;
}



/* ================================================================
 * 00017cd8  FUN_00017cd8
 * bytes: 275  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

int FUN_00017cd8(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6,undefined4 param_7)

{
  void *pvVar1;
  int iVar2;
  undefined1 *puVar3;
  byte bVar4;
  int local_20;

  bVar4 = 0;
  if ((param_2 - 400U < 0xd4) || (param_2 - 20000U < 0x24f)) {
    local_20 = 1;
  }
  else {
    local_20 = 1;
    if (0x2a7 < param_2 - 30000U) {
      return -1;
    }
  }
  do {
    if (*(int *)(param_1 + 0x2014 + local_20 * 4) == 0) {
      pvVar1 = operator_new(0x130);
      FUN_00037422(pvVar1,param_2,param_3,param_4,param_5,param_6,param_7);
      puVar3 = (undefined1 *)((int)pvVar1 + 0x10b);
      for (iVar2 = 0x25; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = 0;
        puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
      }
      *(undefined4 *)((int)pvVar1 + 0x128) = param_5;
      *(undefined4 *)((int)pvVar1 + 300) = param_6;
      *(short *)((int)pvVar1 + 100) = (short)local_20;
      iVar2 = param_1 + local_20 * 4;
      *(undefined4 *)(iVar2 + 0xd4) = 0;
      *(void **)(iVar2 + 0x3f54) = pvVar1;
      *(undefined4 *)(iVar2 + 0x2014) = 1;
      FUN_0003741a(param_1);
      return local_20;
    }
    local_20 = local_20 + 1;
  } while (local_20 != 2000);
  return -1;
}



/* ================================================================
 * 00017e08  FUN_00017e08
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017e08(void)

{
}



/* ================================================================
 * 00017e8a  FUN_00017e8a
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017e8a(void)

{
}



/* ================================================================
 * 00017eb6  FUN_00017eb6
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017eb6(void)

{
}



/* ================================================================
 * 00017ee6  FUN_00017ee6
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017ee6(void)

{
}



/* ================================================================
 * 00017f12  FUN_00017f12
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017f12(void)

{
}



/* ================================================================
 * 00017f42  FUN_00017f42
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017f42(void)

{
}



/* ================================================================
 * 00017fa4  FUN_00017fa4
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00017fa4(void)

{
}



/* ================================================================
 * 0001804a  FUN_0001804a
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001804a(void)

{
}



/* ================================================================
 * 0001809e  FUN_0001809e
 * bytes: 74  status: ok
 * ================================================================ */

undefined8 __regparm3 FUN_0001809e(int *param_1,uint param_2,short *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 unaff_EBX;
  undefined4 *puVar3;

  puVar3 = *(undefined4 **)(*param_1 + param_2 * 4);
  if (puVar3 != (undefined4 *)0x0) {
    unaff_EBX = CONCAT22(*param_3,(short)unaff_EBX);
    puVar1 = (undefined4 *)*puVar3;
    do {
      puVar2 = puVar1;
      if (*param_3 == *(short *)(puVar2 + 1)) goto LAB_000180e0;
      puVar1 = (undefined4 *)*puVar2;
    } while ((puVar1 != (undefined4 *)0x0) &&
            (puVar3 = puVar2, param_2 == (uint)*(ushort *)(puVar1 + 1) % (uint)param_1[1]));
    puVar3 = (undefined4 *)0x0;
  }
LAB_000180e0:
  return CONCAT44(unaff_EBX,puVar3);
}



/* ================================================================
 * 000180e8  FUN_000180e8
 * bytes: 225  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_000180e8(int param_1,ushort param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  ushort local_140 [9];
  undefined1 local_12d [285];

  local_140[0] = param_2;
  (*(code *)0x80c9ca0)(param_1,param_2,param_3);
  iVar1 = FUN_0001e31d();
  if (*(char *)(*(int *)(*(int *)(iVar1 + 0xc) + 0x5ea8) + (uint)local_140[0]) != '\0') {
    FUN_0003745a(local_12d);
    FUN_00037ae4(local_12d,local_140,0x10,1);
    iVar1 = FUN_0001e31d();
    FUN_00037ae4(local_12d,(uint)local_140[0] * 0xe0 + *(int *)(*(int *)(iVar1 + 0xc) + 0x5e98),
                 0x700,1);
    uVar2 = FUN_0001e31d();
    FUN_0003738e(uVar2,&DAT_0004092a,local_12d,*(undefined2 *)(param_1 + 0x2967),1);
    FUN_00037562(local_12d);
  }
  return;
}



/* ================================================================
 * 000181ef  FUN_000181ef
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000181ef(void)

{
}



/* ================================================================
 * 00018210  FUN_00018210
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00018210(void)

{
}



/* ================================================================
 * 0001825d  FUN_0001825d
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001825d(void)

{
}



/* ================================================================
 * 00018292  FUN_00018292
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00018292(void)

{
}



/* ================================================================
 * 000182e5  FUN_000182e5
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_000182e5(void)

{
                    /* WARNING: Could not recover jumptable at 0x000182ea. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*_DAT_0004e220)();
  return;
}



/* ================================================================
 * 00018345  FUN_00018345
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00018345(void)

{
}



/* ================================================================
 * 0001837a  FUN_0001837a
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001837a(void)

{
}



/* ================================================================
 * 00018469  FUN_00018469
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00018469(void)

{
}



/* ================================================================
 * 00018504  FUN_00018504
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_00018504(void)

{
  return;
}



/* ================================================================
 * 00018506  FUN_00018506
 * bytes: 15  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00018506(void)

{
}



/* ================================================================
 * 0001855c  FUN_0001855c
 * bytes: 15  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001855c(void)

{
}



/* ================================================================
 * 000185b2  FUN_000185b2
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000185b2(void)

{
}



/* ================================================================
 * 00018664  FUN_00018664
 * bytes: 2719  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

char * FUN_00018664(undefined4 param_1,undefined4 param_2)

{
  char local_2c [28];

  std::__cxx11::string::_S_copy(local_2c,"",0);
  local_2c[0] = '\0';
  switch(param_2) {
  case 1:
    FUN_000185b2();
    break;
  case 2:
    FUN_000185b2();
    break;
  case 3:
    FUN_000185b2();
    break;
  case 4:
    FUN_000185b2();
    break;
  case 5:
    FUN_000185b2();
    break;
  case 6:
    FUN_000185b2();
    break;
  case 7:
    FUN_000185b2();
    break;
  case 8:
    FUN_000185b2();
    break;
  case 9:
    FUN_000185b2();
    break;
  case 10:
  case 0xb:
    FUN_000185b2();
    break;
  case 0xc:
  case 0xd:
    FUN_000185b2();
    break;
  case 0xe:
    FUN_000185b2();
    break;
  case 0xf:
    FUN_000185b2();
    break;
  case 0x10:
    FUN_000185b2();
    break;
  case 0x11:
    FUN_000185b2();
    break;
  case 0x12:
    FUN_000185b2();
    break;
  default:
    FUN_000185b2();
    break;
  case 0x16:
    FUN_000185b2();
    break;
  case 0x17:
    FUN_000185b2();
    break;
  case 0x18:
    FUN_000185b2();
    break;
  case 0x19:
    FUN_000185b2();
    break;
  case 0x1a:
    FUN_000185b2();
    break;
  case 0x1b:
    FUN_000185b2();
    break;
  case 0x1c:
    FUN_000185b2();
    break;
  case 0x1d:
    FUN_000185b2();
    break;
  case 0x1e:
    FUN_000185b2();
    break;
  case 0x1f:
    FUN_000185b2();
    break;
  case 0x20:
    FUN_000185b2();
    break;
  case 0x21:
    FUN_000185b2();
    break;
  case 0x22:
    FUN_000185b2();
    break;
  case 0x23:
    FUN_000185b2();
    break;
  case 0x24:
    FUN_000185b2();
    break;
  case 0x25:
    FUN_000185b2();
    break;
  case 0x26:
    FUN_000185b2();
    break;
  case 0x27:
    FUN_000185b2();
    break;
  case 0x28:
    FUN_000185b2();
    break;
  case 0x29:
    FUN_000185b2();
    break;
  case 0x2a:
    FUN_000185b2();
    break;
  case 0x2b:
    FUN_000185b2();
    break;
  case 0x2c:
    FUN_000185b2();
    break;
  case 0x2d:
    FUN_000185b2();
    break;
  case 0x2e:
    FUN_000185b2();
    break;
  case 0x31:
    FUN_000185b2();
    break;
  case 0x35:
    FUN_000185b2();
    break;
  case 0x36:
    FUN_000185b2();
    break;
  case 0x46:
    FUN_000185b2();
    break;
  case 0x47:
    FUN_000185b2();
    break;
  case 0x48:
    FUN_000185b2();
    break;
  case 0x49:
    FUN_000185b2();
    break;
  case 0x4a:
    FUN_000185b2();
    break;
  case 0x4b:
    FUN_000185b2();
    break;
  case 0x4c:
    FUN_000185b2();
    break;
  case 0x4d:
    FUN_000185b2();
    break;
  case 0x4e:
    FUN_000185b2();
    break;
  case 0x4f:
    FUN_000185b2();
    break;
  case 0x50:
    FUN_000185b2();
    break;
  case 0x51:
    FUN_000185b2();
    break;
  case 0x52:
    FUN_000185b2();
    break;
  case 0x53:
    FUN_000185b2();
    break;
  case 0x54:
    FUN_000185b2();
    break;
  case 0x55:
    FUN_000185b2();
    break;
  case 0x56:
    FUN_000185b2();
    break;
  case 0x57:
    FUN_000185b2();
    break;
  case 0x58:
    FUN_000185b2();
    break;
  case 0x59:
    FUN_000185b2();
    break;
  case 0x5a:
    FUN_000185b2();
    break;
  case 0x5b:
    FUN_000185b2();
    break;
  case 0x5c:
    FUN_000185b2();
    break;
  case 99:
    FUN_000185b2();
    break;
  case 100:
    FUN_000185b2();
    break;
  case 0x65:
    FUN_000185b2();
    break;
  case 0x66:
    FUN_000185b2();
    break;
  case 0x67:
    FUN_000185b2();
    break;
  case 0x68:
    FUN_000185b2();
    break;
  case 0x69:
    FUN_000185b2();
    break;
  case 0x6a:
    FUN_000185b2();
    break;
  case 0x6b:
    FUN_000185b2();
    break;
  case 0x6c:
    FUN_000185b2();
    break;
  case 0x6d:
    FUN_000185b2();
    break;
  case 0x6e:
    FUN_000185b2();
    break;
  case 0x6f:
    FUN_000185b2();
    break;
  case 0x70:
    FUN_000185b2();
    break;
  case 0x71:
    FUN_000185b2();
    break;
  case 0x72:
    FUN_000185b2();
    break;
  case 0x73:
    FUN_000185b2();
    break;
  case 0x74:
    FUN_000185b2();
    break;
  case 0x75:
    FUN_000185b2();
    break;
  case 0x76:
    FUN_000185b2();
    break;
  case 0x77:
    FUN_000185b2();
    break;
  case 0x78:
    FUN_000185b2();
    break;
  case 0x79:
    FUN_000185b2();
    break;
  case 0x7a:
    FUN_000185b2();
    break;
  case 0x7b:
    FUN_000185b2();
    break;
  case 0x7c:
    FUN_000185b2();
    break;
  case 0x7d:
    FUN_000185b2();
    break;
  case 0x7e:
    FUN_000185b2();
    break;
  case 0x7f:
    FUN_000185b2();
    break;
  case 0x80:
    FUN_000185b2();
    break;
  case 0x81:
    FUN_000185b2();
    break;
  case 0x82:
    FUN_000185b2();
    break;
  case 0x83:
    FUN_000185b2();
    break;
  case 0x84:
    FUN_000185b2();
    break;
  case 0x85:
    FUN_000185b2();
    break;
  case 0x86:
    FUN_000185b2();
    break;
  case 0x87:
    FUN_000185b2();
    break;
  case 0x88:
    FUN_000185b2();
    break;
  case 0x89:
    FUN_000185b2();
    break;
  case 0x8a:
    FUN_000185b2();
    break;
  case 0x8b:
    FUN_000185b2();
    break;
  case 0x8c:
    FUN_000185b2();
    break;
  case 0x8d:
    FUN_000185b2();
    break;
  case 0x8e:
    FUN_000185b2();
    break;
  case 0x8f:
    FUN_000185b2();
    break;
  case 0x90:
    FUN_000185b2();
    break;
  case 0x91:
    FUN_000185b2();
    break;
  case 0x92:
    FUN_000185b2();
    break;
  case 0x93:
    FUN_000185b2();
    break;
  case 0x94:
    FUN_000185b2();
    break;
  case 0x95:
    FUN_000185b2();
    break;
  case 0x96:
    FUN_000185b2();
    break;
  case 0x97:
    FUN_000185b2();
    break;
  case 0x98:
    FUN_000185b2();
    break;
  case 0x99:
    FUN_000185b2();
    break;
  case 0x9a:
    FUN_000185b2();
    break;
  case 0x9b:
    FUN_000185b2();
    break;
  case 0x9c:
    FUN_000185b2();
    break;
  case 0x9d:
    FUN_000185b2();
    break;
  case 0x9e:
    FUN_000185b2();
    break;
  case 0x9f:
    FUN_000185b2();
    break;
  case 0xa0:
    FUN_000185b2();
    break;
  case 0xa1:
    FUN_000185b2();
    break;
  case 0xa2:
    FUN_000185b2();
    break;
  case 0xa3:
    FUN_000185b2();
    break;
  case 0xa4:
    FUN_000185b2();
    break;
  case 0xa5:
    FUN_000185b2();
    break;
  case 0xa6:
    FUN_000185b2();
    break;
  case 0xa7:
    FUN_000185b2();
    break;
  case 0xa8:
    FUN_000185b2();
    break;
  case 0xa9:
    FUN_000185b2();
    break;
  case 0xaa:
    FUN_000185b2();
    break;
  case 0xab:
    FUN_000185b2();
    break;
  case 0xac:
    FUN_000185b2();
    break;
  case 0xad:
    FUN_000185b2();
    break;
  case 0xae:
    FUN_000185b2();
    break;
  case 0xaf:
    FUN_000185b2();
    break;
  case 0xb1:
    FUN_000185b2();
  }
  std::__cxx11::string::_M_dispose();
  return local_2c;
}



/* ================================================================
 * 0001911c  FUN_0001911c
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001911c(void)

{
}



/* ================================================================
 * 00019165  FUN_00019165
 * bytes: 576  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_00019165(undefined4 *param_1)

{
  short sVar1;
  code *pcVar2;
  uint uVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  undefined8 uVar7;
  thread *local_250;
  int local_24c;
  uint local_248;
  undefined4 local_242;
  int local_23e [2];
  int local_236;
  undefined4 *local_12d [71];

  local_24c = 0;
  FUN_000374d0(local_23e,*param_1,(((uint)param_1[1] >> 3) + 1) - (uint)((param_1[1] & 7) == 0),1);
  (*(code *)0x80b46d0)(param_1);
  local_236 = local_23e[0] + -0x20;
  uVar5 = FUN_0001e31d();
  iVar6 = FUN_000373a8(uVar5);
  pcVar2 = *(code **)(iVar6 + 0xe8);
  sVar1 = *(short *)(param_1 + 3);
  uVar5 = param_1[2];
  uVar7 = FUN_0001e31d();
  local_248 = (*pcVar2)(*(undefined4 *)((int)uVar7 + 0x40),uVar5,(int)sVar1,
                        (int)((ulonglong)uVar7 >> 0x20));
  cVar4 = FUN_0003768a(local_23e,&local_24c,0x20,1);
  uVar3 = local_248;
  if (((cVar4 == '\0') || (local_24c == 0)) || (local_248 == 0xffffffff)) {
    local_242 = 0;
    local_12d[0] = operator_new(8);
    *local_12d[0] = &PTR_FUN_0004dc08;
    local_12d[0][1] = uVar3;
    std::thread::_M_start_thread
              (&local_242,
               (unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_12d
               ,PTR__M_thread_deps_never_run_0004df48);
    std::unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
              ((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_12d
              );
    std::thread::detach();
  }
  else {
    if (local_24c == 0x1fbd2) {
      *(undefined1 *)(DAT_0004ec44 + local_248) = 1;
      FUN_0003745a((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)
                   local_12d);
      local_242 = CONCAT31(local_242._1_3_,0xe7);
      FUN_00037ae4((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)
                   local_12d,&local_248,0x20,1);
      uVar5 = FUN_0001e31d();
      FUN_0003738e(uVar5,&local_242,
                   (unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)
                   local_12d,local_248 & 0xffff,0);
      FUN_00037562((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)
                   local_12d);
      goto LAB_0001938f;
    }
    local_242 = 0;
    local_12d[0] = operator_new(8);
    *local_12d[0] = &PTR_FUN_0004dbf4;
    local_12d[0][1] = uVar3;
    std::thread::_M_start_thread
              (&local_242,
               (unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_12d
               ,PTR__M_thread_deps_never_run_0004df48);
    std::unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
              ((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_12d
              );
    std::thread::detach();
  }
  local_250 = (thread *)&local_242;
  std::thread::~thread(local_250);
LAB_0001938f:
  FUN_00037562(local_23e);
  return;
}



/* ================================================================
 * 00019409  FUN_00019409
 * bytes: 726  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00019409(int param_1,short param_2,undefined4 param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  char *pcVar5;
  undefined8 uVar6;
  ushort *puVar7;
  undefined **ppuVar8;
  undefined **local_144;
  short local_140 [3];
  undefined1 local_13a;
  undefined1 local_139;
  undefined4 local_138;
  undefined4 local_134;
  ushort local_12e [143];

  local_13a = 0x39;
  local_140[0] = param_2;
  local_139 = 0x60;
  local_12e[0] = (ushort)param_3;
  puVar2 = DAT_0004ec20;
  if (DAT_0004ec24 == 0) {
    while( true ) {
      if (puVar2 == (undefined4 *)0x0) {
        return;
      }
      if (local_12e[0] == *(ushort *)(puVar2 + 1)) break;
      puVar2 = (undefined4 *)*puVar2;
    }
  }
  else {
    piVar1 = (int *)FUN_0001809e();
    if (piVar1 == (int *)0x0) {
      return;
    }
    if (*piVar1 == 0) {
      return;
    }
  }
  if (local_140[0] != -1) {
    puVar2 = (undefined4 *)FUN_0001e31d();
    iVar3 = FUN_00037364(*puVar2,local_140[0],*(undefined2 *)(param_1 + 100),param_3);
    if (iVar3 != 0) {
      iVar3 = FUN_0001e31d();
      iVar3 = FUN_00037344(*(undefined4 *)(iVar3 + 4),local_140[0],*(undefined2 *)(param_1 + 100),
                           param_3);
      if (iVar3 != 0) goto LAB_00019594;
    }
    FUN_0003745a(local_12e);
    FUN_00037ae4(local_12e,param_1 + 100,0x10,1);
    FUN_00037ae4(local_12e,&param_3,0x10,1);
    uVar4 = FUN_0001e31d();
    FUN_0003738e(uVar4,&local_13a,local_12e,local_140[0],1);
    FUN_00037562(local_12e);
  }
LAB_00019594:
  local_144 = &__DT_PLTGOT;
  local_12e[0] = (ushort)param_3;
  pcVar5 = (char *)std::__detail::
                   _Map_base<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>,true>
                   ::operator[]((_Map_base<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>,true>
                                 *)&DAT_0004ec18,local_12e);
  uVar4 = param_3;
  if (*pcVar5 != '\b') {
    local_12e[0] = (ushort)param_3;
    puVar7 = local_12e;
    ppuVar8 = local_144;
    pcVar5 = (char *)std::__detail::
                     _Map_base<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>,true>
                     ::operator[]((_Map_base<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>,true>
                                   *)&DAT_0004ec18,local_12e);
    *(char *)(param_1 + 0xb7 + (int)*pcVar5) = (char)uVar4 + '\x19';
    FUN_0003745a(local_12e,puVar7,local_144,ppuVar8);
    FUN_00037ae4(local_12e,local_140,0x10,1);
    local_138 = 2;
    FUN_00037ae4(local_12e,&local_138,0x20,1);
    FUN_00037ae4(local_12e,param_1 + 100,0x20,1);
    local_134 = 0;
    FUN_00037ae4(local_12e,&param_3,0x20,1);
    FUN_00037ae4(local_12e,&local_134,0x20,1);
    uVar6 = FUN_0001e31d();
    uVar4 = (undefined4)((ulonglong)uVar6 >> 0x20);
    FUN_000373d8((int)uVar6,&local_139,local_12e,*(undefined2 *)(param_1 + 100),local_140[0],2,uVar4
                 ,uVar4);
    FUN_00037562(local_12e);
  }
  return;
}



/* ================================================================
 * 00019700  std::thread::_M_thread_deps_never_run
 * bytes: 1  status: ok
 * ================================================================ */

/* std::thread::_M_thread_deps_never_run() */

void std::thread::_M_thread_deps_never_run(void)

{
  return;
}



/* ================================================================
 * 00019702  std::thread::~thread
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::thread::~thread() */

void __thiscall std::thread::~thread(thread *this)

{
}



/* ================================================================
 * 00019723  std::__cxx11::string::_S_copy
 * bytes: 37  status: ok
 * ================================================================ */

/* std::__cxx11::string::_S_copy(char*, char const*, unsigned int) */

void std::__cxx11::string::_S_copy(char *param_1,char *param_2,uint param_3)

{
  if (param_3 == 1) {
    *param_1 = *param_2;
  }
  else if (param_3 != 0) {
    for (; param_3 != 0; param_3 = param_3 - 1) {
      *param_1 = *param_2;
      param_2 = param_2 + 1;
      param_1 = param_1 + 1;
    }
  }
  return;
}



/* ================================================================
 * 00019748  std::this_thread::sleep_for<long_long,std::ratio<1ll,1000ll>>
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* void std::this_thread::sleep_for<long long, std::ratio<1ll, 1000ll> >(std::chrono::duration<long
   long, std::ratio<1ll, 1000ll> > const&) */

void std::this_thread::sleep_for<long_long,std::ratio<1ll,1000ll>>(duration *param_1)

{
}



/* ================================================================
 * 000197b2  std::__cxx11::string::_M_dispose
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__cxx11::string::_M_dispose() */

void std::__cxx11::string::_M_dispose(void)

{
}



/* ================================================================
 * 000197e4  std::__cxx11::string::capacity
 * bytes: 25  status: ok
 * ================================================================ */

/* std::__cxx11::string::capacity() const */

undefined4 __thiscall std::__cxx11::string::capacity(string *this)

{
  undefined4 uVar1;

  uVar1 = 0xf;
  if (*(string **)this != this + 8) {
    uVar1 = *(undefined4 *)(this + 8);
  }
  return uVar1;
}



/* ================================================================
 * 000197fe  std::unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
 * bytes: 25  status: ok
 * ================================================================ */

/* std::unique_ptr<std::thread::_State, std::default_delete<std::thread::_State> >::~unique_ptr() */

void __thiscall
std::unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
          (unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *this)

{
  if (*(int **)this != (int *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00019813. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(**(int **)this + 4))();
    return;
  }
  return;
}



/* ================================================================
 * 00019818  std::_Hashtable<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>::_M_rehash
 * bytes: 250  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* std::_Hashtable<unsigned short, std::pair<unsigned short const, char>,
   std::allocator<std::pair<unsigned short const, char> >, std::__detail::_Select1st,
   std::equal_to<unsigned short>, std::hash<unsigned short>, std::__detail::_Mod_range_hashing,
   std::__detail::_Default_ranged_hash, std::__detail::_Prime_rehash_policy,
   std::__detail::_Hashtable_traits<false, false, true> >::_M_rehash(unsigned int, unsigned int
   const&) */

void std::
     _Hashtable<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>
     ::_M_rehash(uint param_1,uint *param_2)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  uint uVar4;
  undefined1 *puVar5;
  uint uVar6;
  byte bVar7;
  undefined1 *local_24;

  bVar7 = 0;
  if (param_2 == (uint *)0x1) {
    local_24 = (undefined1 *)(param_1 + 0x18);
    *(undefined4 *)(param_1 + 0x18) = 0;
  }
  else {
    if ((uint *)0x1fffffff < param_2) {
      if ((uint *)0x3fffffff < param_2) {
        std::__throw_bad_array_new_length();
      }
      std::__throw_bad_alloc();
    }
    uVar4 = (int)param_2 << 2;
    local_24 = operator_new(uVar4);
    puVar5 = local_24;
    for (; uVar4 != 0; uVar4 = uVar4 - 1) {
      *puVar5 = 0;
      puVar5 = puVar5 + (uint)bVar7 * -2 + 1;
    }
  }
  piVar2 = *(int **)(param_1 + 8);
  *(undefined4 *)(param_1 + 8) = 0;
  uVar4 = 0;
  while (uVar6 = uVar4, piVar3 = piVar2, piVar3 != (int *)0x0) {
    piVar2 = (int *)*piVar3;
    uVar4 = (uint)*(ushort *)(piVar3 + 1) % (uint)param_2;
    piVar1 = (int *)(local_24 + uVar4 * 4);
    if ((int *)*piVar1 == (int *)0x0) {
      *piVar3 = *(int *)(param_1 + 8);
      *(int **)(param_1 + 8) = piVar3;
      *piVar1 = param_1 + 8;
      if (*piVar3 != 0) {
        *(int **)(local_24 + uVar6 * 4) = piVar3;
      }
    }
    else {
      *piVar3 = *(int *)*piVar1;
      *(int **)*piVar1 = piVar3;
      uVar4 = uVar6;
    }
  }
  if (*(void **)param_1 != (void *)(param_1 + 0x18)) {
    operator_delete(*(void **)param_1,*(int *)(param_1 + 4) << 2);
  }
  *(uint **)(param_1 + 4) = param_2;
  *(undefined1 **)param_1 = local_24;
  return;
}



/* ================================================================
 * 00019948  std::__detail::_Map_base<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>,true>::operator[]
 * bytes: 247  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* std::__detail::_Map_base<unsigned short, std::pair<unsigned short const, char>,
   std::allocator<std::pair<unsigned short const, char> >, std::__detail::_Select1st,
   std::equal_to<unsigned short>, std::hash<unsigned short>, std::__detail::_Mod_range_hashing,
   std::__detail::_Default_ranged_hash, std::__detail::_Prime_rehash_policy,
   std::__detail::_Hashtable_traits<false, false, true>, true>::operator[](unsigned short&&) */

int __thiscall
std::__detail::
_Map_base<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>,true>
::operator[](_Map_base<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>,true>
             *this,ushort *param_1)

{
  int *piVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int *piVar6;
  uint local_34;
  char local_21;
  uint *local_20;

  uVar2 = *param_1;
  local_34 = *(uint *)(this + 4);
  puVar5 = (undefined4 *)FUN_0001809e();
  if ((puVar5 == (undefined4 *)0x0) || (piVar6 = (int *)*puVar5, piVar6 == (int *)0x0)) {
    piVar6 = operator_new(7);
    *piVar6 = 0;
    *(undefined1 *)((int)piVar6 + 6) = 0;
    *(ushort *)(piVar6 + 1) = *param_1;
    std::__detail::_Prime_rehash_policy::_M_need_rehash
              ((uint)&local_21,(uint)(this + 0x10),*(uint *)(this + 4));
    if (local_21 != '\0') {
      _Hashtable<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>
      ::_M_rehash((uint)this,local_20);
      local_34 = *(uint *)(this + 4);
    }
    local_34 = (uint)uVar2 % local_34;
    iVar3 = *(int *)this;
    piVar1 = (int *)(iVar3 + local_34 * 4);
    if ((int *)*piVar1 == (int *)0x0) {
      iVar4 = *(int *)(this + 8);
      *(int **)(this + 8) = piVar6;
      *piVar6 = iVar4;
      if (iVar4 != 0) {
        *(int **)(iVar3 + ((uint)*(ushort *)(iVar4 + 4) % *(uint *)(this + 4)) * 4) = piVar6;
      }
      *piVar1 = (int)(this + 8);
    }
    else {
      *piVar6 = *(int *)*piVar1;
      *(int **)*piVar1 = piVar6;
    }
    *(int *)(this + 0xc) = *(int *)(this + 0xc) + 1;
  }
  return (int)piVar6 + 6;
}



/* ================================================================
 * 00019a59  __i686.get_pc_thunk.ax
 * bytes: 4  status: ok
 * ================================================================ */

/* WARNING: This is an inlined function */

undefined4 __i686_get_pc_thunk_ax(void)

{
  undefined4 unaff_retaddr;

  return unaff_retaddr;
}



/* ================================================================
 * 00019a5d  __i686.get_pc_thunk.si
 * bytes: 4  status: ok
 * ================================================================ */

/* WARNING: This is an inlined function */

void __i686_get_pc_thunk_si(void)

{
  return;
}



/* ================================================================
 * 00019a62  FUN_00019a62
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00019a62(void)

{
}



/* ================================================================
 * 00019a8e  FUN_00019a8e
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00019a8e(void)

{
}



/* ================================================================
 * 00019abe  FUN_00019abe
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00019abe(void)

{
}



/* ================================================================
 * 00019b11  AmxLoad
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void AmxLoad(void)

{
}



/* ================================================================
 * 00019b3e  Supports
 * bytes: 6  status: ok
 * ================================================================ */

undefined4 Supports(void)

{
  return 0x10200;
}



/* ================================================================
 * 00019b44  AmxUnload
 * bytes: 3  status: ok
 * ================================================================ */

undefined4 AmxUnload(void)

{
  return 0;
}



/* ================================================================
 * 00019b47  Unload
 * bytes: 1  status: ok
 * ================================================================ */

void Unload(void)

{
  return;
}



/* ================================================================
 * 00019b48  Load
 * bytes: 468  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 Load(undefined4 *param_1)

{
  undefined *puVar1;
  int iVar2;
  undefined1 *puVar3;
  byte bVar4;
  undefined4 local_24;
  undefined4 *local_20 [4];

  bVar4 = 0;
  DAT_0004edd0 = param_1[0x10];
  DAT_0004ec4c = param_1;
  DAT_0004ec44 = operator_new__(1000);
  *DAT_0004ec44 = 0;
  puVar3 = DAT_0004ec44 + 1;
  for (iVar2 = 999; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
  }
  DAT_0004ec40 = operator_new__(1000);
  *DAT_0004ec40 = 0;
  puVar3 = DAT_0004ec40 + 1;
  for (iVar2 = 999; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
  }
  DAT_0004ec34 = *DAT_0004ec4c;
  FUN_0001eb2c();
  FUN_0001837a();
  FUN_0001c792();
  FUN_00018345();
  FUN_00018469();
  FUN_0001c87d();
  FUN_0001c911();
  FUN_0001737a();
  FUN_0001e6e4();
  FUN_0001f80a();
  FUN_00032fa0();
  FUN_0001825d();
  FUN_00018292();
  FUN_000179d4();
  local_24 = 0;
  local_20[0] = operator_new(8);
  *local_20[0] = PTR_vtable_0004df4c + 8;
  local_20[0][1] = FUN_0001e3b7;
  puVar1 = PTR__M_thread_deps_never_run_0004df48;
  std::thread::_M_start_thread
            ((thread *)&local_24,
             (unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_20,
             PTR__M_thread_deps_never_run_0004df48);
  std::unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
            ((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_20);
  std::thread::detach();
  std::thread::~thread((thread *)&local_24);
  local_24 = 0;
  local_20[0] = operator_new(5);
  *local_20[0] = &PTR_FUN_0004dc1c;
  std::thread::_M_start_thread
            ((thread *)&local_24,
             (unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_20,
             puVar1);
  std::unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
            ((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_20);
  std::thread::detach();
  std::thread::~thread((thread *)&local_24);
  return 1;
}



/* ================================================================
 * 00019d5a  FUN_00019d5a
 * bytes: 28  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00019d5a(void)

{
  FUN_0001b390(&DAT_0004eae0);
  return;
}



/* ================================================================
 * 00019d76  std::__future_base::_State_baseV2::_M_complete_async
 * bytes: 1  status: ok
 * ================================================================ */

/* std::__future_base::_State_baseV2::_M_complete_async() */

void std::__future_base::_State_baseV2::_M_complete_async(void)

{
  return;
}



/* ================================================================
 * 00019d78  std::__future_base::_State_baseV2::_M_is_deferred_future
 * bytes: 3  status: ok
 * ================================================================ */

/* std::__future_base::_State_baseV2::_M_is_deferred_future() const */

undefined4 std::__future_base::_State_baseV2::_M_is_deferred_future(void)

{
  return 0;
}



/* ================================================================
 * 00019d7c  std::__future_base::_Result<void>::_M_destroy
 * bytes: 17  status: ok
 * ================================================================ */

/* std::__future_base::_Result<void>::_M_destroy() */

void __thiscall std::__future_base::_Result<void>::_M_destroy(_Result<void> *this)

{
                    /* WARNING: Could not recover jumptable at 0x00019d8b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)this + 8))();
  return;
}



/* ================================================================
 * 00019d8d  std::__exception_ptr::__dest_thunk<std::future_error>
 * bytes: 16  status: ok
 * ================================================================ */

/* void std::__exception_ptr::__dest_thunk<std::future_error>(void*) */

void std::__exception_ptr::__dest_thunk<std::future_error>(void *param_1)

{
                    /* WARNING: Could not recover jumptable at 0x00019d9b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)**(undefined4 **)param_1)();
  return;
}



/* ================================================================
 * 00019d9e  std::_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>::~_Sp_counted_ptr_inplace
 * bytes: 1  status: ok
 * ================================================================ */

/* std::_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>, std::allocator<void>, (__gnu_cxx::_Lock_policy)2>::~_Sp_counted_ptr_inplace() */

void __thiscall
std::
_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
::~_Sp_counted_ptr_inplace
          (_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
           *this)

{
  return;
}



/* ================================================================
 * 00019da0  std::_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>::~_Sp_counted_ptr_inplace
 * bytes: 1  status: ok
 * ================================================================ */

/* std::_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>, std::allocator<void>, (__gnu_cxx::_Lock_policy)2>::~_Sp_counted_ptr_inplace() */

void __thiscall
std::
_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
::~_Sp_counted_ptr_inplace
          (_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
           *this)

{
  return;
}



/* ================================================================
 * 00019da2  std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::_M_is_deferred_future
 * bytes: 3  status: ok
 * ================================================================ */

/* std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>::_M_is_deferred_future() const */

undefined1
std::__future_base::
_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::
_M_is_deferred_future(void)

{
  return 1;
}



/* ================================================================
 * 00019da6  std::_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>::~_Sp_counted_ptr_inplace
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>, std::allocator<void>, (__gnu_cxx::_Lock_policy)2>::~_Sp_counted_ptr_inplace() */

void __thiscall
std::
_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
::~_Sp_counted_ptr_inplace
          (_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
           *this)

{
}



/* ================================================================
 * 00019dca  std::_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>::~_Sp_counted_ptr_inplace
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>, std::allocator<void>, (__gnu_cxx::_Lock_policy)2>::~_Sp_counted_ptr_inplace() */

void __thiscall
std::
_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
::~_Sp_counted_ptr_inplace
          (_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
           *this)

{
}



/* ================================================================
 * 00019dee  std::thread::_State_impl<std::thread::_Invoker<std::tuple<void(*)()>>>::~_State_impl
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)()> > >::~_State_impl() */

void __thiscall
std::thread::_State_impl<std::thread::_Invoker<std::tuple<void(*)()>>>::~_State_impl
          (_State_impl<std::thread::_Invoker<std::tuple<void(*)()>>> *this)

{
}



/* ================================================================
 * 00019e1c  std::thread::_State_impl<std::thread::_Invoker<std::tuple<void(*)()>>>::~_State_impl
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)()> > >::~_State_impl() */

void __thiscall
std::thread::_State_impl<std::thread::_Invoker<std::tuple<void(*)()>>>::~_State_impl
          (_State_impl<std::thread::_Invoker<std::tuple<void(*)()>>> *this)

{
}



/* ================================================================
 * 00019e4c  std::thread::_State_impl<std::thread::_Invoker<std::tuple<void(std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::*)(),std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>*>>>::~_State_impl
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::thread::_State_impl<std::thread::_Invoker<std::tuple<void
   (std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>::*)(),
   std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>*> > >::~_State_impl() */

void __thiscall
std::thread::
_State_impl<std::thread::_Invoker<std::tuple<void(std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::*)(),std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>*>>>
::~_State_impl(_State_impl<std::thread::_Invoker<std::tuple<void(std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>::*)(),std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>*>>>
               *this)

{
}



/* ================================================================
 * 00019e7a  std::thread::_State_impl<std::thread::_Invoker<std::tuple<void(std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::*)(),std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>*>>>::~_State_impl
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::thread::_State_impl<std::thread::_Invoker<std::tuple<void
   (std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>::*)(),
   std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>*> > >::~_State_impl() */

void __thiscall
std::thread::
_State_impl<std::thread::_Invoker<std::tuple<void(std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::*)(),std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>*>>>
::~_State_impl(_State_impl<std::thread::_Invoker<std::tuple<void(std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>::*)(),std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>*>>>
               *this)

{
}



/* ================================================================
 * 00019eaa  std::__future_base::_Async_state_commonV2::_M_complete_async
 * bytes: 167  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */
/* std::__future_base::_Async_state_commonV2::_M_complete_async() */

void __thiscall
std::__future_base::_Async_state_commonV2::_M_complete_async(_Async_state_commonV2 *this)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 auStack_3c [12];
  _Async_state_commonV2 *local_30;
  undefined *local_2c;
  undefined4 local_28;
  undefined **local_24;
  _Async_state_commonV2 **local_20;

  puVar4 = auStack_3c;
  local_30 = this + 0x11;
  local_2c = PTR_join_0004df84;
  local_28 = 0;
  local_24 = &local_2c;
  local_20 = &local_30;
  piVar1 = (int *)___tls_get_addr();
  *piVar1 = (int)&local_24;
  puVar2 = (undefined4 *)___tls_get_addr();
  *puVar2 = PTR__FUN_0004dff0;
  iVar3 = pthread_once((pthread_once_t *)(this + 0x15),(__init_routine *)PTR___once_proxy_0004dfac);
  if (iVar3 != 0) {
    puVar4 = &stack0xffffffb4;
    std::__throw_system_error(iVar3);
  }
  *(undefined4 *)(puVar4 + -4) = 0x19f35;
  puVar2 = (undefined4 *)___tls_get_addr();
  *puVar2 = 0;
  *(undefined4 *)(puVar4 + -4) = 0x19f47;
  puVar2 = (undefined4 *)___tls_get_addr();
  *puVar2 = 0;
  return;
}



/* ================================================================
 * 00019f7e  std::__future_base::_Result<void>::~_Result
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_Result<void>::~_Result() */

void __thiscall std::__future_base::_Result<void>::~_Result(_Result<void> *this)

{
}



/* ================================================================
 * 00019fac  std::__future_base::_Result<void>::~_Result
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_Result<void>::~_Result() */

void __thiscall std::__future_base::_Result<void>::~_Result(_Result<void> *this)

{
}



/* ================================================================
 * 00019fdc  std::thread::_State_impl<std::thread::_Invoker<std::tuple<void(*)()>>>::_M_run
 * bytes: 12  status: ok
 * ================================================================ */

/* std::thread::_State_impl<std::thread::_Invoker<std::tuple<void (*)()> > >::_M_run() */

void __thiscall
std::thread::_State_impl<std::thread::_Invoker<std::tuple<void(*)()>>>::_M_run
          (_State_impl<std::thread::_Invoker<std::tuple<void(*)()>>> *this)

{
                    /* WARNING: Could not recover jumptable at 0x00019fe6. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(this + 4))();
  return;
}



/* ================================================================
 * 00019fe8  std::thread::_State_impl<std::thread::_Invoker<std::tuple<void(std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::*)(),std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>*>>>::_M_run
 * bytes: 31  status: ok
 * ================================================================ */

/* std::thread::_State_impl<std::thread::_Invoker<std::tuple<void
   (std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>::*)(),
   std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>*> > >::_M_run() */

void __thiscall
std::thread::
_State_impl<std::thread::_Invoker<std::tuple<void(std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::*)(),std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>*>>>
::_M_run(_State_impl<std::thread::_Invoker<std::tuple<void(std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>::*)(),std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>*>>>
         *this)

{
  code *UNRECOVERED_JUMPTABLE;

  UNRECOVERED_JUMPTABLE = *(code **)(this + 8);
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    UNRECOVERED_JUMPTABLE =
         *(code **)(UNRECOVERED_JUMPTABLE + *(int *)(*(int *)(this + 0xc) + *(int *)(this + 4)) + -1
                   );
  }
                    /* WARNING: Could not recover jumptable at 0x0001a005. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



/* ================================================================
 * 0001a007  std::_Function_handler<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>(),std::__future_base::_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>,std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>>::_M_manager
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::_Function_handler<std::unique_ptr<std::__future_base::_Result_base,
   std::__future_base::_Result_base::_Deleter> (),
   std::__future_base::_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,
   std::__future_base::_Result_base::_Deleter>,
   std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}> >, void>
   >::_M_manager(std::_Any_data&, std::_Any_data const&, std::_Manager_operation) */

void std::
     _Function_handler<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>(),std::__future_base::_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>,std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>>
     ::_M_manager(void)

{
}



/* ================================================================
 * 0001a04a  std::once_flag::_Prepare_execution::_Prepare_execution<std::call_once<void(std::thread::*)(),std::thread*>(std::once_flag&,void(std::thread::*&&)(),std::thread*&&)::{lambda()#1}()#1}>(void(std::thread::*&)())::{lambda()#1}::_FUN
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* _FUN() */

void std::once_flag::_Prepare_execution::
     _Prepare_execution<std::call_once<void(std::thread::*)(),std::thread*>(std::once_flag&,void(std::thread::*&&)(),std::thread*&&)::{lambda()#1}()#1}>(void(std::thread::*&)())
     ::{lambda()#1}::_FUN(void)

{
}



/* ================================================================
 * 0001a08c  std::once_flag::_Prepare_execution::_Prepare_execution<std::call_once<void(std::__future_base::_State_baseV2::*)(std::function<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>()>*,bool*),std::__future_base::_State_baseV2*,std::function<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>()>*,bool*>(std::once_flag&,void(std::__future_base::_State_baseV2::*&&)(std::function<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>()>*,bool*),std::__future_base::_State_baseV2*&&,std::function<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>()>*&&,bool*&&)::{lambda()#1}()#1}>(void(std::__future_base::_State_baseV2::*&)(std::function<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>()>*,bool*))::{lambda()#1}::_FUN
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* _FUN() */

void std::once_flag::_Prepare_execution::
     _Prepare_execution<std::call_once<void(std::__future_base::_State_baseV2::*)(std::function<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>()>*,bool*),std::__future_base::_State_baseV2*,std::function<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>()>*,bool*>(std::once_flag&,void(std::__future_base::_State_baseV2::*&&)(std::function<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>()>*,bool*),std::__future_base::_State_baseV2*&&,std::function<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>()>*&&,bool*&&)::{lambda()#1}()#1}>(void(std::__future_base::_State_baseV2::*&)(std::function<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>()>*,bool*))
     ::{lambda()#1}::_FUN(void)

{
}



/* ================================================================
 * 0001a0e0  std::_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>::_M_destroy
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>, std::allocator<void>, (__gnu_cxx::_Lock_policy)2>::_M_destroy() */

void std::
     _Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
     ::_M_destroy(void)

{
}



/* ================================================================
 * 0001a104  std::_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>::_M_destroy
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>, std::allocator<void>, (__gnu_cxx::_Lock_policy)2>::_M_destroy() */

void std::
     _Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
     ::_M_destroy(void)

{
}



/* ================================================================
 * 0001a128  std::type_info::operator==
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::type_info::TEMPNAMEPLACEHOLDERVALUE(std::type_info const&) const */

void __thiscall std::type_info::operator==(type_info *this,type_info *param_1)

{
}



/* ================================================================
 * 0001a170  std::_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>::_M_get_deleter
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>, std::allocator<void>, (__gnu_cxx::_Lock_policy)2>::_M_get_deleter(std::type_info
   const&) */

void std::
     _Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
     ::_M_get_deleter(type_info *param_1)

{
}



/* ================================================================
 * 0001a1b0  std::_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>::_M_get_deleter
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>, std::allocator<void>, (__gnu_cxx::_Lock_policy)2>::_M_get_deleter(std::type_info
   const&) */

void std::
     _Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
     ::_M_get_deleter(type_info *param_1)

{
}



/* ================================================================
 * 0001a1f0  std::__exception_ptr::exception_ptr::~exception_ptr
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__exception_ptr::exception_ptr::~exception_ptr() */

void __thiscall std::__exception_ptr::exception_ptr::~exception_ptr(exception_ptr *this)

{
}



/* ================================================================
 * 0001a21a  std::_Function_base::~_Function_base
 * bytes: 28  status: ok
 * ================================================================ */

/* std::_Function_base::~_Function_base() */

void __thiscall std::_Function_base::~_Function_base(_Function_base *this)

{
  if (*(code **)(this + 8) != (code *)0x0) {
    (**(code **)(this + 8))(this,this,3);
  }
  return;
}



/* ================================================================
 * 0001a236  std::__future_base::_State_baseV2::_M_set_result
 * bytes: 250  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */
/* std::__future_base::_State_baseV2::_M_set_result(std::function<std::unique_ptr<std::__future_base::_Result_base,
   std::__future_base::_Result_base::_Deleter> ()>, bool) */

void __thiscall
std::__future_base::_State_baseV2::_M_set_result
          (_State_baseV2 *this,undefined4 param_2,undefined4 param_3)

{
  int *piVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 auStack_5c [12];
  undefined4 local_50;
  char local_41;
  _State_baseV2 *local_40;
  undefined4 local_3c;
  char *local_38;
  undefined *local_34;
  undefined4 local_30;
  undefined **local_2c;
  _State_baseV2 **local_28;
  undefined4 *local_24;
  undefined1 **local_20;

  puVar4 = auStack_5c;
  local_30 = 0;
  local_41 = '\0';
  local_50 = param_3;
  local_38 = &local_41;
  local_40 = this;
  local_3c = param_2;
  local_34 = PTR__M_do_set_0004dfec;
  local_2c = &local_34;
  local_28 = &local_40;
  local_24 = &local_3c;
  local_20 = &local_38;
  piVar1 = (int *)___tls_get_addr();
  *piVar1 = (int)&local_2c;
  puVar2 = (undefined4 *)___tls_get_addr();
  *puVar2 = PTR__FUN_0004dfa4;
  iVar3 = pthread_once((pthread_once_t *)(this + 0xd),(__init_routine *)PTR___once_proxy_0004dfac);
  if (iVar3 != 0) {
    puVar4 = &stack0xffffff94;
    std::__throw_system_error(iVar3);
  }
  *(undefined4 *)(puVar4 + -4) = 0x1a2e0;
  puVar2 = (undefined4 *)___tls_get_addr();
  *puVar2 = 0;
  *(undefined4 *)(puVar4 + -4) = 0x1a2f0;
  puVar2 = (undefined4 *)___tls_get_addr();
  *puVar2 = 0;
  if (local_41 == '\0') {
    if ((char)local_50 == '\0') {
      *(undefined4 *)(puVar4 + -0x10) = 2;
      *(undefined4 *)(puVar4 + -0x14) = 0x1a355;
      std::__throw_future_error(*(int *)(puVar4 + -0x10));
    }
  }
  else {
    this = this + 8;
    LOCK();
    iVar3 = *(int *)this;
    *(int *)this = 1;
    UNLOCK();
    if (iVar3 < 0) {
      *(_State_baseV2 **)(puVar4 + -0x10) = this;
      *(undefined4 *)(puVar4 + -0x14) = 0x1a340;
      std::__atomic_futex_unsigned_base::_M_futex_notify_all(*(uint **)(puVar4 + -0x10));
    }
  }
  return;
}



/* ================================================================
 * 0001a35e  std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::_M_complete_async
 * bytes: 83  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */
/* std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>::_M_complete_async() */

void __thiscall
std::__future_base::
_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::
_M_complete_async(_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                  *this)

{
  _Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
  *local_2c;
  _Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
  *local_28;
  undefined *local_24;
  undefined *local_20;

  local_2c = this + 0x11;
  local_28 = this + 0x15;
  local_20 = PTR__M_invoke_0004df38;
  local_24 = PTR__M_manager_0004df88;
  _State_baseV2::_M_set_result((_State_baseV2 *)this,(_Function_base *)&local_2c,1);
  _Function_base::~_Function_base((_Function_base *)&local_2c);
  return;
}



/* ================================================================
 * 0001a3ca  FUN_0001a3ca
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001a3ca(void)

{
}



/* ================================================================
 * 0001a3e6  FUN_0001a3e6
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001a3e6(void)

{
}



/* ================================================================
 * 0001a412  std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
 * bytes: 122  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */
/* std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count() */

void __thiscall
std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
          (__shared_count<(__gnu_cxx::_Lock_policy)2> *this)

{
  int *piVar1;
  int *piVar2;
  int iVar3;

  piVar2 = *(int **)this;
  if (piVar2 != (int *)0x0) {
    if (DAT_0004eb38 == '\0') {
      LOCK();
      piVar1 = piVar2 + 1;
      iVar3 = *piVar1;
      *piVar1 = *piVar1 + -1;
      UNLOCK();
    }
    else {
      iVar3 = piVar2[1];
      piVar2[1] = iVar3 + -1;
    }
    if (iVar3 == 1) {
      (**(code **)(*piVar2 + 8))(piVar2);
      if (DAT_0004eb38 == '\0') {
        LOCK();
        piVar1 = piVar2 + 2;
        iVar3 = *piVar1;
        *piVar1 = *piVar1 + -1;
        UNLOCK();
      }
      else {
        iVar3 = piVar2[2];
        piVar2[2] = iVar3 + -1;
      }
      if (iVar3 == 1) {
                    /* WARNING: Could not recover jumptable at 0x0001a483. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        (**(code **)(*piVar2 + 0xc))();
        return;
      }
    }
  }
  return;
}



/* ================================================================
 * 0001a48c  std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>::~unique_ptr
 * bytes: 28  status: ok
 * ================================================================ */

/* std::unique_ptr<std::__future_base::_Result_base,
   std::__future_base::_Result_base::_Deleter>::~unique_ptr() */

void __thiscall
std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>::
~unique_ptr(unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>
            *this)

{
  undefined4 *puVar1;

  puVar1 = *(undefined4 **)this;
  if (puVar1 != (undefined4 *)0x0) {
    (**(code **)*puVar1)(puVar1);
  }
  return;
}



/* ================================================================
 * 0001a4a8  std::__future_base::_State_baseV2::~_State_baseV2
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_State_baseV2::~_State_baseV2() */

void __thiscall std::__future_base::_State_baseV2::~_State_baseV2(_State_baseV2 *this)

{
}



/* ================================================================
 * 0001a4da  std::__future_base::_State_baseV2::~_State_baseV2
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_State_baseV2::~_State_baseV2() */

void __thiscall std::__future_base::_State_baseV2::~_State_baseV2(_State_baseV2 *this)

{
}



/* ================================================================
 * 0001a50a  std::__future_base::_Async_state_commonV2::~_Async_state_commonV2
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_Async_state_commonV2::~_Async_state_commonV2() */

void __thiscall
std::__future_base::_Async_state_commonV2::~_Async_state_commonV2(_Async_state_commonV2 *this)

{
}



/* ================================================================
 * 0001a546  std::__future_base::_Async_state_commonV2::~_Async_state_commonV2
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_Async_state_commonV2::~_Async_state_commonV2() */

void __thiscall
std::__future_base::_Async_state_commonV2::~_Async_state_commonV2(_Async_state_commonV2 *this)

{
}



/* ================================================================
 * 0001a576  std::__future_base::_State_baseV2::_M_do_set
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_State_baseV2::_M_do_set(std::function<std::unique_ptr<std::__future_base::_Result_base,
   std::__future_base::_Result_base::_Deleter> ()>*, bool*) */

void std::__future_base::_State_baseV2::_M_do_set(function *param_1,bool *param_2)

{
}



/* ================================================================
 * 0001a5c8  std::unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>::~unique_ptr
 * bytes: 28  status: ok
 * ================================================================ */

/* std::unique_ptr<std::__future_base::_Result<void>,
   std::__future_base::_Result_base::_Deleter>::~unique_ptr() */

void __thiscall
std::unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>::
~unique_ptr(unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>
            *this)

{
  undefined4 *puVar1;

  puVar1 = *(undefined4 **)this;
  if (puVar1 != (undefined4 *)0x0) {
    (**(code **)*puVar1)(puVar1);
  }
  return;
}



/* ================================================================
 * 0001a5e4  std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::~_Async_state_impl
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>::~_Async_state_impl() */

void __thiscall
std::__future_base::
_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::
~_Async_state_impl(_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                   *this)

{
}



/* ================================================================
 * 0001a636  std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::~_Async_state_impl
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>::~_Async_state_impl() */

void __thiscall
std::__future_base::
_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::
~_Async_state_impl(_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                   *this)

{
}



/* ================================================================
 * 0001a666  std::_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>::_M_dispose
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::_Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>, std::allocator<void>, (__gnu_cxx::_Lock_policy)2>::_M_dispose() */

void std::
     _Sp_counted_ptr_inplace<std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
     ::_M_dispose(void)

{
}



/* ================================================================
 * 0001a68c  std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::~_Deferred_state
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>::~_Deferred_state() */

void __thiscall
std::__future_base::
_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::
~_Deferred_state(_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                 *this)

{
}



/* ================================================================
 * 0001a6c8  std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::~_Deferred_state
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>::~_Deferred_state() */

void __thiscall
std::__future_base::
_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::
~_Deferred_state(_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                 *this)

{
}



/* ================================================================
 * 0001a6f8  std::_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>::_M_dispose
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::_Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>, std::allocator<void>, (__gnu_cxx::_Lock_policy)2>::_M_dispose() */

void std::
     _Sp_counted_ptr_inplace<std::__future_base::_Deferred_state<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>,std::allocator<void>,(__gnu_cxx::_Lock_policy)2>
     ::_M_dispose(void)

{
}



/* ================================================================
 * 0001a71e  std::operator==
 * bytes: 15  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* bool std::TEMPNAMEPLACEHOLDERVALUE(std::__cxx11::string const&, std::__cxx11::string const&) */

bool std::operator==(string *param_1,string *param_2)

{
}



/* ================================================================
 * 0001a75e  FUN_0001a75e
 * bytes: 30  status: ok
 * ================================================================ */

int FUN_0001a75e(int param_1)

{
  int iVar1;

  iVar1 = *(int *)(param_1 + 0x18);
  if (iVar1 == *(int *)(param_1 + 0x1c)) {
    iVar1 = *(int *)(*(int *)(param_1 + 0x24) + -4) + 0x1d4;
  }
  return iVar1 + -0x4e;
}



/* ================================================================
 * 0001a77c  FUN_0001a77c
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001a77c(void)

{
}



/* ================================================================
 * 0001a82c  std::unique_lock<std::mutex>::unlock
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::unique_lock<std::mutex>::unlock() */

void std::unique_lock<std::mutex>::unlock(void)

{
}



/* ================================================================
 * 0001a86c  std::unique_lock<std::mutex>::~unique_lock
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::unique_lock<std::mutex>::~unique_lock() */

void __thiscall std::unique_lock<std::mutex>::~unique_lock(unique_lock<std::mutex> *this)

{
}



/* ================================================================
 * 0001a896  std::__cxx11::string::_M_is_local
 * bytes: 16  status: ok
 * ================================================================ */

/* std::__cxx11::string::_M_is_local() const */

bool __thiscall std::__cxx11::string::_M_is_local(string *this)

{
  return *(string **)this == this + 8;
}



/* ================================================================
 * 0001a8a6  std::__cxx11::string::~string
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__cxx11::string::~string() */

void __thiscall std::__cxx11::string::~string(string *this)

{
}



/* ================================================================
 * 0001a8c8  FUN_0001a8c8
 * bytes: 208  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001a8c8(undefined4 *param_1,undefined4 *param_2)

{
  undefined *puVar1;
  undefined4 *puVar2;
  _Result_base *this;
  int iVar3;
  undefined4 *puVar4;
  byte bVar5;

  bVar5 = 0;
  *param_1 = 0;
  puVar2 = operator_new(0x31);
  puVar2[1] = 1;
  puVar2[2] = 1;
  puVar1 = PTR_vtable_0004dfb4;
  *(undefined4 *)((int)puVar2 + 0x19) = 0;
  puVar2[4] = 0;
  *puVar2 = puVar1 + 8;
  puVar2[5] = 0;
  *(undefined1 *)(puVar2 + 6) = 0;
  puVar2[3] = PTR_vtable_0004df1c + 8;
  this = operator_new(8);
  *(undefined4 *)this = 0;
  *(undefined4 *)(this + 4) = 0;
  std::__future_base::_Result_base::_Result_base(this);
  *(undefined **)this = PTR_vtable_0004dfd0 + 8;
  *(_Result_base **)((int)puVar2 + 0x1d) = this;
  puVar4 = (undefined4 *)((int)puVar2 + 0x21);
  for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = *param_2;
    param_2 = param_2 + (uint)bVar5 * -2 + 1;
    puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
  }
  *param_1 = puVar2 + 3;
  param_1[1] = puVar2;
  return;
}



/* ================================================================
 * 0001a9d6  std::__cxx11::string::_M_replace
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__cxx11::string::_M_replace(unsigned int, unsigned int, char const*, unsigned int) */

void std::__cxx11::string::_M_replace(uint param_1,uint param_2,char *param_3,uint param_4)

{
}



/* ================================================================
 * 0001ab66  std::future_error::future_error
 * bytes: 234  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* std::future_error::future_error(std::error_code) */

void __thiscall std::future_error::future_error(future_error *this,undefined4 param_2,int *param_3)

{
  undefined *puVar1;
  char cVar2;
  string *this_00;
  int iVar3;
  string *psVar4;
  string *psVar5;
  byte bVar6;
  string *local_4c;
  undefined4 local_48;
  undefined4 local_44 [4];
  undefined1 local_34 [36];

  bVar6 = 0;
  (**(code **)(*param_3 + 0x10))(local_34,param_3,param_2);
  this_00 = (string *)__cxx11::string::_M_replace((uint)local_34,0,(char *)0x0,0x398ef);
  local_4c = (string *)local_44;
  cVar2 = __cxx11::string::_M_is_local(this_00);
  if (cVar2 == '\0') {
    local_4c = *(string **)this_00;
    local_44[0] = *(undefined4 *)(this_00 + 8);
  }
  else {
    iVar3 = *(int *)(this_00 + 4) + 1;
    if (iVar3 != 0) {
      psVar4 = this_00 + 8;
      psVar5 = (string *)local_44;
      for (; iVar3 != 0; iVar3 = iVar3 + -1) {
        *psVar5 = *psVar4;
        psVar4 = psVar4 + (uint)bVar6 * -2 + 1;
        psVar5 = psVar5 + (uint)bVar6 * -2 + 1;
      }
    }
  }
  local_48 = *(undefined4 *)(this_00 + 4);
  this_00[8] = (string)0x0;
  *(string **)this_00 = this_00 + 8;
  *(undefined4 *)(this_00 + 4) = 0;
  std::logic_error::logic_error((logic_error *)this,(string *)&local_4c);
  __cxx11::string::_M_dispose();
  __cxx11::string::_M_dispose();
  puVar1 = PTR_vtable_0004df78;
  *(undefined4 *)(this + 8) = param_2;
  *(undefined **)this = puVar1 + 8;
  *(int **)(this + 0xc) = param_3;
  return;
}



/* ================================================================
 * 0001ac80  std::__future_base::_State_baseV2::_M_break_promise
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__future_base::_State_baseV2::_M_break_promise(std::unique_ptr<std::__future_base::_Result_base,
   std::__future_base::_Result_base::_Deleter>) */

void std::__future_base::_State_baseV2::_M_break_promise(void)

{
}



/* ================================================================
 * 0001ad78  std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::_M_run
 * bytes: 95  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >, void>::_M_run() */

void __thiscall
std::__future_base::
_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::
_M_run(_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
       *this)

{
  _Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
  *local_2c;
  _Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
  *local_28;
  undefined *local_24;
  undefined *local_20;

  local_2c = this + 0x19;
  local_28 = this + 0x1d;
  local_20 = PTR__M_invoke_0004df38;
  local_24 = PTR__M_manager_0004df88;
  _State_baseV2::_M_set_result((_State_baseV2 *)this,(_Function_base *)&local_2c,0);
  _Function_base::~_Function_base((_Function_base *)&local_2c);
  return;
}



/* ================================================================
 * 0001ae64  FUN_0001ae64
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001ae64(void)

{
}



/* ================================================================
 * 0001aea0  FUN_0001aea0
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001aea0(void)

{
}



/* ================================================================
 * 0001af01  std::_Destroy_aux<false>::__destroy<Commands::Command*>
 * bytes: 35  status: ok
 * ================================================================ */

/* void std::_Destroy_aux<false>::__destroy<Commands::Command*>(Commands::Command*,
   Commands::Command*) */

void std::_Destroy_aux<false>::__destroy<Commands::Command*>(Command *param_1,Command *param_2)

{
  for (; param_1 != param_2; param_1 = param_1 + 0x4e) {
    FUN_0001ae64(param_1);
  }
  return;
}



/* ================================================================
 * 0001af24  FUN_0001af24
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001af24(void)

{
}



/* ================================================================
 * 0001b004  std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::_Async_state_impl<BufferHandles::Process()::{lambda()#2}>
 * bytes: 277  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* std::__future_base::_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>
   >,
   void>::_Async_state_impl<BufferHandles::Process()::{lambda()#2}>(BufferHandles::Process()::{lambda()#2}&&)
    */

void __thiscall
std::__future_base::
_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::
_Async_state_impl<BufferHandles::Process()::_lambda()_2_>
          (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
           *this,_lambda___2_ *param_1)

{
  _Result_base *this_00;
  int iVar1;
  _Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
  *p_Var2;
  byte bVar3;
  undefined4 local_24;
  undefined4 *local_20 [4];

  bVar3 = 0;
  *(undefined4 *)(this + 0xd) = 0;
  *(undefined4 *)(this + 0x11) = 0;
  *(undefined4 *)(this + 0x15) = 0;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0;
  this[0xc] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
               )0x0;
  *(undefined **)this = PTR_vtable_0004df8c + 8;
  this_00 = operator_new(8);
  *(undefined4 *)this_00 = 0;
  *(undefined4 *)(this_00 + 4) = 0;
  std::__future_base::_Result_base::_Result_base(this_00);
  *(undefined **)this_00 = PTR_vtable_0004dfd0 + 8;
  *(_Result_base **)(this + 0x19) = this_00;
  p_Var2 = this + 0x1d;
  for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
    *(undefined4 *)p_Var2 = *(undefined4 *)param_1;
    param_1 = param_1 + (uint)bVar3 * -8 + 4;
    p_Var2 = p_Var2 + (uint)bVar3 * -8 + 4;
  }
  local_24 = 0;
  local_20[0] = operator_new(0x10);
  local_20[0][3] = 0;
  *local_20[0] = PTR_vtable_0004df34 + 8;
  local_20[0][1] = this;
  local_20[0][2] = PTR__M_run_0004df54;
  std::thread::_M_start_thread
            ((thread *)&local_24,
             (unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_20,
             PTR__M_thread_deps_never_run_0004df48);
  unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
            ((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_20);
  if (*(int *)(this + 0x11) != 0) {
                    /* WARNING: Subroutine does not return */
    std::terminate();
  }
  *(undefined4 *)(this + 0x11) = local_24;
  local_24 = 0;
  thread::~thread((thread *)&local_24);
  return;
}



/* ================================================================
 * 0001b171  FUN_0001b171
 * bytes: 372  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* WARNING: Type propagation algorithm not settling */

int * FUN_0001b171(int *param_1,byte param_2,_lambda___2_ *param_3)

{
  char cVar1;
  undefined *puVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  int extraout_EDX;
  _Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
  ***ppp_Var6;
  int *piVar7;
  _Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
  **pp_Var8;
  _Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
  **pp_StackY_60;
  _Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
  *local_34 [9];

  pp_Var8 = local_34;
  for (iVar5 = 2; iVar5 != 0; iVar5 = iVar5 + -1) {
    *pp_Var8 = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                *)0x0;
    pp_Var8 = pp_Var8 + 1;
  }
  if ((param_2 & 1) == 0) {
    pp_StackY_60 = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                    **)0x1b27e;
    FUN_0001a8c8();
    local_34[0] = local_34[2];
    local_34[1] = local_34[3];
    local_34[2] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                   *)0x0;
    ppp_Var6 = &pp_StackY_60;
    pp_StackY_60 = local_34 + 5;
  }
  else {
    local_34[2] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                   *)0x0;
    pp_StackY_60 = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                    **)0x1b1af;
    puVar3 = operator_new(0x39);
    puVar3[1] = 1;
    puVar2 = PTR_vtable_0004dfc4;
    puVar3[2] = 1;
    *puVar3 = puVar2 + 8;
    ppp_Var6 = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                ***)&stack0xffffffa4;
    pp_StackY_60 = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                    **)0x1b1de;
    std::__future_base::
    _Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>
    ::_Async_state_impl<BufferHandles::Process()::_lambda()_2_>
              ((_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                *)(puVar3 + 3),param_3);
    local_34[0] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                   *)(puVar3 + 3);
    local_34[1] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                   *)puVar3;
  }
  local_34[5] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                 *)0x0;
  local_34[4] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                 *)0x0;
  local_34[3] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                 *)0x0;
  ppp_Var6[-1] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                  **)0x1b2a6;
  std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
            ((__shared_count<(__gnu_cxx::_Lock_policy)2> *)*ppp_Var6);
  *ppp_Var6 = local_34 + 3;
  ppp_Var6[-1] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                  **)0x1b2b4;
  std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
            ((__shared_count<(__gnu_cxx::_Lock_policy)2> *)*ppp_Var6);
  *param_1 = (int)local_34[0];
  param_1[1] = (int)local_34[1];
  if (local_34[1] !=
      (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
       *)0x0) {
    if (DAT_0004eb38 == '\0') {
      LOCK();
      *(int *)((int)local_34[1] + 4) = *(int *)((int)local_34[1] + 4) + 1;
      UNLOCK();
    }
    else {
      *(int *)((int)local_34[1] + 4) = *(int *)((int)local_34[1] + 4) + 1;
    }
  }
  iVar5 = *param_1;
  piVar7 = (int *)(ppp_Var6 + 4);
  if (iVar5 == 0) {
    *ppp_Var6 = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                 **)0x3;
    ppp_Var6[-1] = (_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
                    **)0x1b2f4;
    std::__throw_future_error((int)*ppp_Var6);
    iVar5 = extraout_EDX;
    piVar7 = (int *)ppp_Var6;
  }
  LOCK();
  cVar1 = *(char *)(iVar5 + 0xc);
  *(char *)(iVar5 + 0xc) = '\x01';
  UNLOCK();
  if (cVar1 != '\0') {
    *(undefined4 *)((int)piVar7 + -0x10) = 1;
    *(undefined4 *)((int)piVar7 + -0x14) = 0x1b30a;
    uVar4 = std::__throw_future_error(*(int *)((int)piVar7 + -0x10));
    *(int **)((int)piVar7 + -0x20) = param_1 + 1;
    *(undefined4 *)((int)piVar7 + -0x24) = 0x1b31e;
    std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
              (*(__shared_count<(__gnu_cxx::_Lock_policy)2> **)((int)piVar7 + -0x20));
    *(_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
      ***)((int)piVar7 + -0x20) = local_34 + 1;
    *(undefined4 *)((int)piVar7 + -0x24) = 0x1b368;
    std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
              (*(__shared_count<(__gnu_cxx::_Lock_policy)2> **)((int)piVar7 + -0x20));
    *(undefined4 *)((int)piVar7 + -0x20) = uVar4;
                    /* WARNING: Subroutine does not return */
    *(undefined4 *)((int)piVar7 + -0x24) = 0x1b373;
    _Unwind_Resume();
  }
  *(_Async_state_impl<std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
    ***)((int)piVar7 + -0x10) = local_34 + 1;
  *(undefined4 *)((int)piVar7 + -0x14) = 0x1b382;
  std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
            (*(__shared_count<(__gnu_cxx::_Lock_policy)2> **)((int)piVar7 + -0x10));
  return param_1;
}



/* ================================================================
 * 0001b390  FUN_0001b390
 * bytes: 4766  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001b390(int param_1)

{
  uint *puVar1;
  byte bVar2;
  ushort uVar3;
  float fVar4;
  bool bVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  undefined1 *puVar11;
  int *piVar12;
  int *piVar13;
  undefined1 *puVar14;
  undefined4 *puVar15;
  undefined4 *puVar16;
  byte bVar17;
  longdouble lVar18;
  undefined1 auStack_26c [8];
  undefined **local_264;
  undefined **local_260;
  undefined *local_25c;
  float local_258;
  undefined4 **local_254;
  undefined **local_250;
  ushort local_242;
  undefined4 local_240;
  undefined4 local_23c;
  undefined4 local_238;
  undefined4 *local_234;
  undefined1 local_230;
  undefined1 local_22f [4];
  undefined1 local_22b [4];
  undefined4 local_227 [6];
  undefined4 local_20f [56];
  int local_12d;
  undefined4 *local_129;
  undefined4 *local_125;
  undefined4 *local_121;

  bVar17 = 0;
  local_250 = &__DT_PLTGOT;
  puVar14 = auStack_26c;
  local_260 = &PTR_s_max_speed_0004e460;
  local_264 = &PTR_s_add_max_speed_0004e3d0;
  do {
    puVar15 = local_227;
    for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
      *puVar15 = 0;
      puVar15 = puVar15 + (uint)bVar17 * -2 + 1;
    }
    local_234 = local_227;
    local_230 = 0;
    *(undefined4 **)(puVar14 + -0x10) = local_234;
    *(undefined4 *)(puVar14 + -0x14) = 0x1b3fb;
    iVar9 = pthread_mutex_lock(*(pthread_mutex_t **)(puVar14 + -0x10));
    puVar11 = puVar14;
    if (iVar9 != 0) {
      puVar11 = puVar14 + -0x10;
      *(int *)(puVar14 + -0x10) = iVar9;
      *(undefined4 *)(puVar14 + -0x14) = 0x1b411;
      std::__throw_system_error(*(int *)(puVar14 + -0x10));
    }
    local_230 = 1;
    iVar9 = param_1 + 0x28;
    while (local_254 = &local_234, *(int *)(param_1 + 0x18) == *(int *)(param_1 + 8)) {
      *(undefined4 ***)(puVar11 + -4) = local_254;
      *(undefined4 ***)(puVar11 + -8) = local_254;
      *(undefined4 ***)(puVar11 + -0xc) = local_254;
      *(int *)(puVar11 + -0x10) = iVar9;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b449;
      std::condition_variable::wait(*(unique_lock **)(puVar11 + -0x10));
    }
    local_242 = 0;
    puVar15 = local_20f;
    for (iVar10 = 0xe2; iVar10 != 0; iVar10 = iVar10 + -1) {
      *(undefined1 *)puVar15 = 0;
      puVar15 = (undefined4 *)((int)puVar15 + (uint)bVar17 * -2 + 1);
    }
    *(undefined4 *)(puVar11 + -4) = 0x1b46b;
    iVar10 = FUN_0001a3ca();
    iVar10 = *(int *)(iVar10 + 0x5ea8);
    *(int *)(puVar11 + -0x10) = param_1;
    *(undefined4 *)(puVar11 + -0x14) = 0x1b47c;
    iVar6 = FUN_0001a75e();
    if (*(char *)(iVar10 + (uint)*(ushort *)(iVar6 + 0x48)) == '\0') {
      *(undefined4 ***)(puVar11 + -0x10) = local_254;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b49d;
      std::unique_lock<std::mutex>::unlock();
      local_12d = 1;
      local_129 = (undefined4 *)0x0;
      *(int **)(puVar11 + -0x10) = &local_12d;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b4c3;
      std::this_thread::sleep_for<long_long,std::ratio<1ll,1000ll>>(*(duration **)(puVar11 + -0x10))
      ;
      goto LAB_0001c612;
    }
    *(int *)(puVar11 + -4) = iVar9;
    *(int *)(puVar11 + -8) = iVar9;
    *(undefined ***)(puVar11 + -0xc) = local_260;
    *(int *)(puVar11 + -0x10) = iVar6;
    *(undefined4 *)(puVar11 + -0x14) = 0x1b4df;
    bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
    if (bVar5) {
      *(undefined4 *)(puVar11 + -4) = 0x1b4eb;
      iVar9 = FUN_0001a3ca();
      iVar9 = *(int *)(iVar9 + 0x5ea8);
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b4fc;
      iVar10 = FUN_0001a75e();
      if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) == '\0') goto LAB_0001b52e;
      *(int *)(puVar11 + -0x10) = iVar10;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b512;
      lVar18 = (longdouble)FUN_0001a3e6();
      local_258 = (float)lVar18;
      if (0.0 < local_258) {
        *(undefined4 *)(puVar11 + -4) = 0x1b58f;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b5a0;
        iVar10 = FUN_0001a75e();
        *(float *)(iVar9 + 0x84 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) = local_258;
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b5c0;
        uVar8 = FUN_0001a75e();
        *(undefined4 *)(puVar11 + -0x10) = uVar8;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b5c8;
        lVar18 = (longdouble)FUN_0001a3e6();
        local_258 = (float)lVar18;
        *(undefined4 *)(puVar11 + -4) = 0x1b5d6;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b5e7;
        iVar10 = FUN_0001a75e();
        *(float *)(iVar9 + 0x88 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) = local_258;
      }
LAB_0001c4ba:
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c4c2;
      iVar9 = FUN_0001a75e();
      uVar3 = *(ushort *)(iVar9 + 0x48);
LAB_0001c501:
      local_242 = uVar3;
      piVar12 = (int *)(puVar11 + -0x10);
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c509;
      FUN_0001aea0();
LAB_0001c509:
      local_129 = (undefined4 *)0x0;
      *piVar12 = (int)&local_12d;
      local_12d = 600;
      piVar12[-1] = 0x1c533;
      std::this_thread::sleep_for<long_long,std::ratio<1ll,1000ll>>((duration *)*piVar12);
      *piVar12 = (int)&local_12d;
      piVar12[-1] = 0x1c541;
      FUN_0003745a();
      local_22f[0] = 0xe9;
      piVar12[3] = 0x1c550;
      iVar9 = FUN_0001a3ca();
      puVar15 = (undefined4 *)((uint)local_242 * 0xe0 + *(int *)(iVar9 + 0x5e98));
      puVar16 = local_20f;
      for (iVar10 = 0x38; iVar10 != 0; iVar10 = iVar10 + -1) {
        *puVar16 = *puVar15;
        puVar15 = puVar15 + (uint)bVar17 * -2 + 1;
        puVar16 = puVar16 + (uint)bVar17 * -2 + 1;
      }
      piVar12[3] = 1;
      piVar12[2] = 0x10;
      piVar12[1] = (int)&local_242;
      *piVar12 = (int)&local_12d;
      piVar12[-1] = 0x1c58d;
      FUN_00037ae4();
      piVar12[3] = 1;
      piVar12[2] = 0x710;
      piVar12[1] = (int)local_20f;
      *piVar12 = (int)&local_12d;
      piVar12[-1] = 0x1c5aa;
      FUN_00037ae4();
      piVar12[3] = 0x1c5b8;
      uVar8 = FUN_0001e31d();
      *piVar12 = 2;
      piVar12[-1] = 0xffff;
      piVar12[-2] = (int)&local_12d;
      piVar12[-3] = (int)local_22f;
      piVar12[-4] = uVar8;
      piVar12[-5] = 0x1c5d6;
      FUN_000373be();
      *piVar12 = (int)&local_12d;
      piVar12[-1] = 0x1c5e5;
      FUN_00037562();
      *piVar12 = (int)&local_12d;
      local_12d = 500;
      local_129 = (undefined4 *)0x0;
      piVar12[-1] = 0x1c605;
      std::this_thread::sleep_for<long_long,std::ratio<1ll,1000ll>>((duration *)*piVar12);
      piVar13 = piVar12 + 1;
    }
    else {
LAB_0001b52e:
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b539;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_264;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b54d;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1b60b;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b61c;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) == '\0') goto LAB_0001b558;
        *(int *)(puVar11 + -0x10) = iVar10;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b691;
        lVar18 = (longdouble)FUN_0001a3e6();
        local_258 = (float)lVar18;
        *(undefined4 *)(puVar11 + -4) = 0x1b69f;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b6b0;
        iVar10 = FUN_0001a75e();
        iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
        *(float *)(iVar9 + 0x88) = local_258 + *(float *)(iVar9 + 0x88);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b6d7;
        uVar8 = FUN_0001a75e();
        *(undefined4 *)(puVar11 + -0x10) = uVar8;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b6df;
        lVar18 = (longdouble)FUN_0001a3e6();
        local_258 = (float)lVar18;
        *(undefined4 *)(puVar11 + -4) = 0x1b6ed;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b6fe;
        iVar10 = FUN_0001a75e();
        iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
        fVar4 = local_258 + *(float *)(iVar9 + 0x84);
LAB_0001b804:
        *(float *)(iVar9 + 0x84) = fVar4;
        goto LAB_0001c4ba;
      }
LAB_0001b558:
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b563;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0x2de;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b57a;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1b634;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b645;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
          *(int *)(puVar11 + -0x10) = iVar10;
          *(undefined4 *)(puVar11 + -0x14) = 0x1b77e;
          lVar18 = (longdouble)FUN_0001a3e6();
          local_258 = (float)lVar18;
          *(undefined4 *)(puVar11 + -4) = 0x1b78c;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1b79d;
          iVar10 = FUN_0001a75e();
          iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
          *(float *)(iVar9 + 0x88) = *(float *)(iVar9 + 0x88) - local_258;
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1b7c4;
          uVar8 = FUN_0001a75e();
          *(undefined4 *)(puVar11 + -0x10) = uVar8;
          *(undefined4 *)(puVar11 + -0x14) = 0x1b7cc;
          lVar18 = (longdouble)FUN_0001a3e6();
          local_258 = (float)lVar18;
          *(undefined4 *)(puVar11 + -4) = 0x1b7da;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1b7eb;
          iVar10 = FUN_0001a75e();
          iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
          fVar4 = *(float *)(iVar9 + 0x84) - local_258;
          goto LAB_0001b804;
        }
      }
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b661;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0x115;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b678;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1b721;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b732;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
          *(int *)(puVar11 + -0x10) = iVar10;
          *(undefined4 *)(puVar11 + -0x14) = 0x1b86a;
          lVar18 = (longdouble)FUN_0001a3e6();
          local_258 = (float)lVar18;
          if (0.0 < local_258) {
            *(undefined4 *)(puVar11 + -4) = 0x1b88a;
            iVar9 = FUN_0001a3ca();
            iVar9 = *(int *)(iVar9 + 0x5e98);
            *(int *)(puVar11 + -0x10) = param_1;
            *(undefined4 *)(puVar11 + -0x14) = 0x1b89b;
            iVar10 = FUN_0001a75e();
            *(float *)(iVar9 + 0x7c + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) = local_258;
          }
          goto LAB_0001c4ba;
        }
      }
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b74e;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0xf1;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b765;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1b814;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b825;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) == '\0') goto LAB_0001b836;
        *(int *)(puVar11 + -0x10) = iVar10;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b912;
        lVar18 = (longdouble)FUN_0001a3e6();
        local_258 = (float)lVar18;
        *(undefined4 *)(puVar11 + -4) = 0x1b920;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b931;
        iVar10 = FUN_0001a75e();
        iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
        fVar4 = local_258 + *(float *)(iVar9 + 0x7c);
LAB_0001b9dc:
        *(float *)(iVar9 + 0x7c) = fVar4;
        goto LAB_0001c4ba;
      }
LAB_0001b836:
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b841;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0xe5;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b858;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1b8bc;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b8cd;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
          *(int *)(puVar11 + -0x10) = iVar10;
          *(undefined4 *)(puVar11 + -0x14) = 0x1b9a7;
          lVar18 = (longdouble)FUN_0001a3e6();
          local_258 = (float)lVar18;
          *(undefined4 *)(puVar11 + -4) = 0x1b9b5;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1b9c6;
          iVar10 = FUN_0001a75e();
          iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
          fVar4 = *(float *)(iVar9 + 0x7c) - local_258;
          goto LAB_0001b9dc;
        }
      }
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b8e9;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0x10f;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b900;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1b951;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b962;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
          *(int *)(puVar11 + -0x10) = iVar10;
          *(undefined4 *)(puVar11 + -0x14) = 0x1ba46;
          lVar18 = (longdouble)FUN_0001a3e6();
          local_258 = (float)lVar18;
          if (0.0 < local_258) {
            *(undefined4 *)(puVar11 + -4) = 0x1ba66;
            iVar9 = FUN_0001a3ca();
            iVar9 = *(int *)(iVar9 + 0x5e98);
            *(int *)(puVar11 + -0x10) = param_1;
            *(undefined4 *)(puVar11 + -0x14) = 0x1ba77;
            iVar10 = FUN_0001a75e();
            *(float *)(iVar9 + 4 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) = local_258;
            *(int *)(puVar11 + -0x10) = param_1;
            *(undefined4 *)(puVar11 + -0x14) = 0x1ba94;
            uVar8 = FUN_0001a75e();
            *(undefined4 *)(puVar11 + -0x10) = uVar8;
            *(undefined4 *)(puVar11 + -0x14) = 0x1ba9c;
            lVar18 = (longdouble)FUN_0001a3e6();
            local_258 = (float)((longdouble)1 / lVar18);
            *(undefined4 *)(puVar11 + -4) = 0x1baae;
            iVar9 = FUN_0001a3ca();
            iVar9 = *(int *)(iVar9 + 0x5e98);
            *(int *)(puVar11 + -0x10) = param_1;
            *(undefined4 *)(puVar11 + -0x14) = 0x1babf;
            iVar10 = FUN_0001a75e();
            *(float *)(iVar9 + 8 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) = local_258;
            *(undefined4 *)(puVar11 + -4) = 0x1badb;
            iVar9 = FUN_0001a3ca();
            iVar9 = *(int *)(iVar9 + 0x5e98);
            *(int *)(puVar11 + -0x10) = param_1;
            *(undefined4 *)(puVar11 + -0x14) = 0x1baec;
            iVar10 = FUN_0001a75e();
            local_258 = *(float *)(iVar9 + 8 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0);
            *(undefined4 *)(puVar11 + -4) = 0x1bb08;
            iVar9 = FUN_0001a3ca();
            iVar9 = *(int *)(iVar9 + 0x5e98);
            *(int *)(puVar11 + -0x10) = param_1;
            *(undefined4 *)(puVar11 + -0x14) = 0x1bb19;
            iVar10 = FUN_0001a75e();
            local_258 = local_258 *
                        *(float *)(iVar9 + 200 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) *
                        (float)local_250[-0x36ae];
            *(undefined4 *)(puVar11 + -4) = 0x1bb4a;
            iVar9 = FUN_0001a3ca();
            iVar9 = *(int *)(iVar9 + 0x5e98);
            *(int *)(puVar11 + -0x10) = param_1;
            *(undefined4 *)(puVar11 + -0x14) = 0x1bb5b;
            iVar10 = FUN_0001a75e();
            *(float *)(iVar9 + 200 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) = local_258;
          }
          goto LAB_0001c4ba;
        }
      }
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b97e;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0xeb;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1b995;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1b9e9;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1b9fa;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) == '\0') goto LAB_0001ba0b;
        *(int *)(puVar11 + -0x10) = iVar10;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bbdc;
        lVar18 = (longdouble)FUN_0001a3e6();
        local_258 = (float)lVar18;
        if (local_258 <= 0.0) goto LAB_0001c4ba;
        *(undefined4 *)(puVar11 + -4) = 0x1bbfc;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bc0d;
        iVar10 = FUN_0001a75e();
        iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
        *(float *)(iVar9 + 4) = local_258 + *(float *)(iVar9 + 4);
        *(undefined4 *)(puVar11 + -4) = 0x1bc2d;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bc3e;
        iVar10 = FUN_0001a75e();
        iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
        *(float *)(iVar9 + 8) = 1.0 / local_258 + *(float *)(iVar9 + 8);
        *(undefined4 *)(puVar11 + -4) = 0x1bc60;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bc71;
        iVar10 = FUN_0001a75e();
        local_258 = *(float *)(iVar9 + 8 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0);
        *(undefined4 *)(puVar11 + -4) = 0x1bc8d;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bc9e;
        iVar10 = FUN_0001a75e();
        local_258 = local_258 * *(float *)(iVar9 + 200 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) *
                    (float)local_250[-0x36ae];
        *(undefined4 *)(puVar11 + -4) = 0x1bccf;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bce0;
        iVar10 = FUN_0001a75e();
        iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
        fVar4 = local_258 + *(float *)(iVar9 + 200);
LAB_0001be81:
        *(float *)(iVar9 + 200) = fVar4;
        goto LAB_0001c4ba;
      }
LAB_0001ba0b:
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1ba16;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0xdf;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1ba2d;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1bb7f;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bb90;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
          *(int *)(puVar11 + -0x10) = iVar10;
          *(undefined4 *)(puVar11 + -0x14) = 0x1bd62;
          lVar18 = (longdouble)FUN_0001a3e6();
          local_258 = (float)lVar18;
          if (local_258 <= 0.0) goto LAB_0001c4ba;
          *(undefined4 *)(puVar11 + -4) = 0x1bd82;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1bd93;
          iVar10 = FUN_0001a75e();
          iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
          *(float *)(iVar9 + 4) = *(float *)(iVar9 + 4) - local_258;
          *(undefined4 *)(puVar11 + -4) = 0x1bdb3;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1bdc4;
          iVar10 = FUN_0001a75e();
          iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
          *(float *)(iVar9 + 8) = *(float *)(iVar9 + 8) - 1.0 / local_258;
          *(undefined4 *)(puVar11 + -4) = 0x1bde6;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1bdf7;
          iVar10 = FUN_0001a75e();
          local_258 = *(float *)(iVar9 + 8 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0);
          *(undefined4 *)(puVar11 + -4) = 0x1be13;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1be24;
          iVar10 = FUN_0001a75e();
          local_258 = local_258 * *(float *)(iVar9 + 200 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0)
                      * (float)local_250[-0x36ae];
          *(undefined4 *)(puVar11 + -4) = 0x1be55;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1be66;
          iVar10 = FUN_0001a75e();
          iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
          fVar4 = *(float *)(iVar9 + 200) - local_258;
          goto LAB_0001be81;
        }
      }
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1bbac;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0x103;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1bbc3;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1bd05;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bd16;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) == '\0') goto LAB_0001bd27;
        local_240 = 0;
        local_23c = 0;
        *(undefined4 *)(puVar11 + -4) = 0x1befb;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bf0c;
        iVar10 = FUN_0001a75e();
        local_238 = *(undefined4 *)(iVar9 + 0x7c + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bf29;
        iVar9 = FUN_0001a75e();
        bVar2 = **(byte **)(iVar9 + 0x18);
        uVar7 = bVar2 - 0x34;
        if (((byte)uVar7 < 0x1f) && ((0x40040001U >> (uVar7 & 0x1f) & 1) != 0)) {
          *(undefined4 *)(puVar11 + -4) = 0x1bf47;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1bf58;
          iVar10 = FUN_0001a75e();
          *(byte *)(iVar9 + 0x74 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) = bVar2;
        }
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bf74;
        iVar9 = FUN_0001a75e();
        local_242 = *(ushort *)(iVar9 + 0x48);
        *(int **)(puVar11 + -8) = &local_12d;
        *(undefined4 *)(puVar11 + -0xc) = 1;
        local_12d = param_1;
        local_129 = &local_240;
        local_125 = &local_238;
        local_121 = &local_23c;
        *(undefined1 **)(puVar11 + -0x10) = local_22f;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bfc4;
        FUN_0001b171();
        piVar12 = (int *)(puVar11 + -0x14);
        *(int *)(puVar11 + -0x14) = param_1;
        *(undefined4 *)(puVar11 + -0x18) = 0x1bfcc;
        FUN_0001aea0();
        *(undefined1 **)(puVar11 + -0x14) = local_22b;
        *(undefined4 *)(puVar11 + -0x18) = 0x1bfe0;
        std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
                  (*(__shared_count<(__gnu_cxx::_Lock_policy)2> **)(puVar11 + -0x14));
        goto LAB_0001c509;
      }
LAB_0001bd27:
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1bd32;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0x2f6;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1bd49;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1be94;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bea5;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
          *(undefined4 *)(puVar11 + -0x10) = *(undefined4 *)(iVar10 + 0x18);
          *(undefined4 *)(puVar11 + -0x14) = 0x1c048;
          iVar10 = atoi(*(char **)(puVar11 + -0x10));
          *(undefined4 *)(puVar11 + -4) = 0x1c052;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1c063;
          iVar6 = FUN_0001a75e();
          *(int *)(iVar9 + 0xd0 + (uint)*(ushort *)(iVar6 + 0x48) * 0xe0) = iVar10;
          goto LAB_0001c4ba;
        }
      }
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1bec1;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0x2ea;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1bed8;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1bfea;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1bffb;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
          *(undefined4 *)(puVar11 + -4) = 0x1c0d1;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1c0e2;
          iVar10 = FUN_0001a75e();
          uVar3 = *(ushort *)(iVar10 + 0x48);
          *(undefined4 *)(puVar11 + -0x10) = *(undefined4 *)(iVar10 + 0x18);
          *(undefined4 *)(puVar11 + -0x14) = 0x1c0fd;
          uVar7 = atoi(*(char **)(puVar11 + -0x10));
          puVar1 = (uint *)(iVar9 + (uint)uVar3 * 0xe0 + 0xd0);
          *puVar1 = *puVar1 | uVar7;
          goto LAB_0001c4ba;
        }
      }
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c017;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0x2d2;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c02e;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1c07f;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1c090;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
          *(undefined4 *)(puVar11 + -4) = 0x1c160;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1c171;
          iVar10 = FUN_0001a75e();
          uVar3 = *(ushort *)(iVar10 + 0x48);
          *(undefined4 *)(puVar11 + -0x10) = *(undefined4 *)(iVar10 + 0x18);
          *(undefined4 *)(puVar11 + -0x14) = 0x1c18c;
          uVar7 = atoi(*(char **)(puVar11 + -0x10));
          puVar1 = (uint *)(iVar9 + (uint)uVar3 * 0xe0 + 0xd0);
          *puVar1 = *puVar1 & ~uVar7;
          goto LAB_0001c4ba;
        }
      }
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c0ac;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0x2fc;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c0c3;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1c10e;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1c11f;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
          *(int *)(puVar11 + -0x10) = iVar10;
          *(undefined4 *)(puVar11 + -0x14) = 0x1c1f5;
          lVar18 = (longdouble)FUN_0001a3e6();
          local_258 = (float)(lVar18 * (longdouble)(float)local_250[-0x36ad]);
          *(undefined4 *)(puVar11 + -4) = 0x1c20f;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1c220;
          iVar10 = FUN_0001a75e();
          *(float *)(iVar9 + 0x94 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) = local_258;
          goto LAB_0001c4ba;
        }
      }
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c13b;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0x2f0;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c152;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (bVar5) {
        *(undefined4 *)(puVar11 + -4) = 0x1c19f;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1c1b0;
        iVar10 = FUN_0001a75e();
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
          *(int *)(puVar11 + -0x10) = iVar10;
          *(undefined4 *)(puVar11 + -0x14) = 0x1c29c;
          lVar18 = (longdouble)FUN_0001a3e6();
          local_258 = (float)lVar18;
          if (((float)local_250[-0x36ac] < local_258) || (local_258 <= 0.0)) goto LAB_0001c612;
          *(undefined4 *)(puVar11 + -4) = 0x1c2d2;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5e98);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1c2e3;
          iVar10 = FUN_0001a75e();
          *(float *)(iVar9 + 0xa0 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) = local_258;
          goto LAB_0001c4ba;
        }
      }
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c1cc;
      uVar8 = FUN_0001a75e();
      *(undefined ***)(puVar11 + -0xc) = local_250 + 0x2e4;
      *(undefined4 *)(puVar11 + -0x10) = uVar8;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c1e3;
      bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
      if (!bVar5) {
LAB_0001c264:
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1c26f;
        uVar8 = FUN_0001a75e();
        *(undefined ***)(puVar11 + -0xc) = local_250 + 0x2d8;
        *(undefined4 *)(puVar11 + -0x10) = uVar8;
        *(undefined4 *)(puVar11 + -0x14) = 0x1c286;
        bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
        if (bVar5) {
          *(undefined4 *)(puVar11 + -4) = 0x1c305;
          iVar9 = FUN_0001a3ca();
          iVar9 = *(int *)(iVar9 + 0x5ea8);
          *(int *)(puVar11 + -0x10) = param_1;
          *(undefined4 *)(puVar11 + -0x14) = 0x1c316;
          iVar10 = FUN_0001a75e();
          if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) != '\0') {
            *(int *)(puVar11 + -0x10) = iVar10;
            *(undefined4 *)(puVar11 + -0x14) = 0x1c416;
            lVar18 = (longdouble)FUN_0001a3e6();
            local_258 = (float)lVar18;
            if ((local_258 <= (float)local_250[-0x36ac]) && (0.0 < local_258)) {
              *(undefined4 *)(puVar11 + -4) = 0x1c44c;
              iVar9 = FUN_0001a3ca();
              iVar9 = *(int *)(iVar9 + 0x5e98);
              *(int *)(puVar11 + -0x10) = param_1;
              *(undefined4 *)(puVar11 + -0x14) = 0x1c45d;
              iVar10 = FUN_0001a75e();
              if (0.0 <= *(float *)(iVar9 + 0xa0 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0) -
                         local_258) {
                *(undefined4 *)(puVar11 + -4) = 0x1c48a;
                iVar9 = FUN_0001a3ca();
                iVar9 = *(int *)(iVar9 + 0x5e98);
                *(int *)(puVar11 + -0x10) = param_1;
                *(undefined4 *)(puVar11 + -0x14) = 0x1c49b;
                iVar10 = FUN_0001a75e();
                iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
                fVar4 = *(float *)(iVar9 + 0xa0) - local_258;
                goto LAB_0001c4b4;
              }
            }
            goto LAB_0001c612;
          }
        }
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1c332;
        uVar8 = FUN_0001a75e();
        *(undefined ***)(puVar11 + -0xc) = local_250 + 0xfd;
        *(undefined4 *)(puVar11 + -0x10) = uVar8;
        *(undefined4 *)(puVar11 + -0x14) = 0x1c349;
        bVar5 = std::operator==(*(string **)(puVar11 + -0x10),*(string **)(puVar11 + -0xc));
        if (!bVar5) goto LAB_0001c612;
        *(undefined4 *)(puVar11 + -4) = 0x1c4d5;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5ea8);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1c4e6;
        iVar10 = FUN_0001a75e();
        uVar3 = *(ushort *)(iVar10 + 0x48);
        if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) == '\0') goto LAB_0001c612;
        goto LAB_0001c501;
      }
      *(undefined4 *)(puVar11 + -4) = 0x1c242;
      iVar9 = FUN_0001a3ca();
      iVar9 = *(int *)(iVar9 + 0x5ea8);
      *(int *)(puVar11 + -0x10) = param_1;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c253;
      iVar10 = FUN_0001a75e();
      if (*(char *)(iVar9 + (uint)*(ushort *)(iVar10 + 0x48)) == '\0') goto LAB_0001c264;
      *(int *)(puVar11 + -0x10) = iVar10;
      *(undefined4 *)(puVar11 + -0x14) = 0x1c362;
      lVar18 = (longdouble)FUN_0001a3e6();
      local_258 = (float)lVar18;
      local_25c = local_250[-0x36ac];
      if ((lVar18 <= (longdouble)(float)local_25c) && ((longdouble)0 < lVar18)) {
        *(undefined4 *)(puVar11 + -4) = 0x1c39e;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1c3af;
        iVar10 = FUN_0001a75e();
        if ((float)local_25c <=
            local_258 + *(float *)(iVar9 + 0xa0 + (uint)*(ushort *)(iVar10 + 0x48) * 0xe0))
        goto LAB_0001c612;
        *(undefined4 *)(puVar11 + -4) = 0x1c3de;
        iVar9 = FUN_0001a3ca();
        iVar9 = *(int *)(iVar9 + 0x5e98);
        *(int *)(puVar11 + -0x10) = param_1;
        *(undefined4 *)(puVar11 + -0x14) = 0x1c3ef;
        iVar10 = FUN_0001a75e();
        iVar9 = (uint)*(ushort *)(iVar10 + 0x48) * 0xe0 + iVar9;
        fVar4 = local_258 + *(float *)(iVar9 + 0xa0);
LAB_0001c4b4:
        *(float *)(iVar9 + 0xa0) = fVar4;
        goto LAB_0001c4ba;
      }
LAB_0001c612:
      piVar13 = (int *)(puVar11 + -0xc);
    }
    *(undefined4 ***)((int)piVar13 + -4) = local_254;
    *(undefined4 *)((int)piVar13 + -8) = 0x1c626;
    std::unique_lock<std::mutex>::~unique_lock(*(unique_lock<std::mutex> **)((int)piVar13 + -4));
    puVar14 = (undefined1 *)((int)piVar13 + 0xc);
  } while( true );
}



/* ================================================================
 * 0001c66e  std::__future_base::_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>,std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>::operator()
 * bytes: 66  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* std::__future_base::_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,
   std::__future_base::_Result_base::_Deleter>,
   std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}> >,
   void>::TEMPNAMEPLACEHOLDERVALUE() const */

_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>,std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
* __thiscall
std::__future_base::
_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>,std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>
::operator()(_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>,std::thread::_Invoker<std::tuple<BufferHandles::Process()::_lambda()_2_>>,void>
             *this)

{
  undefined4 *puVar1;
  undefined4 *in_stack_00000008;

  FUN_0001a77c(in_stack_00000008[1]);
  puVar1 = (undefined4 *)*in_stack_00000008;
  *(undefined4 *)this = *puVar1;
  *puVar1 = 0;
  return this;
}



/* ================================================================
 * 0001c733  std::_Function_handler<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>(),std::__future_base::_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>,std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>>::_M_invoke
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::_Function_handler<std::unique_ptr<std::__future_base::_Result_base,
   std::__future_base::_Result_base::_Deleter> (),
   std::__future_base::_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,
   std::__future_base::_Result_base::_Deleter>,
   std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}> >, void>
   >::_M_invoke(std::_Any_data const&) */

void std::
     _Function_handler<std::unique_ptr<std::__future_base::_Result_base,std::__future_base::_Result_base::_Deleter>(),std::__future_base::_Task_setter<std::unique_ptr<std::__future_base::_Result<void>,std::__future_base::_Result_base::_Deleter>,std::thread::_Invoker<std::tuple<BufferHandles::Process()::{lambda()#2}>>,void>>
     ::_M_invoke(_Any_data *param_1)

{
}



/* ================================================================
 * 0001c762  FUN_0001c762
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001c762(void)

{
}



/* ================================================================
 * 0001c792  FUN_0001c792
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001c792(void)

{
}



/* ================================================================
 * 0001c87d  FUN_0001c87d
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001c87d(void)

{
}



/* ================================================================
 * 0001c911  FUN_0001c911
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001c911(void)

{
}



/* ================================================================
 * 0001c93c  FUN_0001c93c
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001c93c(void)

{
}



/* ================================================================
 * 0001c968  FUN_0001c968
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001c968(void)

{
}



/* ================================================================
 * 0001c998  FUN_0001c998
 * bytes: 358  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001c998(undefined4 *param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  ushort local_136;
  int local_134;
  undefined1 local_12d [285];

  FUN_000374d0(local_12d,*param_1,((uint)param_1[1] >> 3) + 1,1);
  FUN_0003768a(local_12d,&local_136,0x10,1);
  FUN_0003768a(local_12d,&local_134,0x20,1);
  uVar1 = (uint)local_136;
  *(undefined4 *)(DAT_0004ec3c + uVar1 * 4) = *(undefined4 *)(DAT_0004ec38 + uVar1 * 4);
  *(int *)(DAT_0004ec38 + uVar1 * 4) = local_134;
  if (local_134 != *(int *)(DAT_0004ec3c + uVar1 * 4)) {
    piVar2 = (int *)FUN_0001e31d();
    if (*piVar2 != 0) {
      puVar4 = (undefined4 *)FUN_0001e31d();
      uVar1 = (uint)local_136;
      FUN_0003735c(*puVar4,uVar1,*(undefined4 *)(DAT_0004ec38 + uVar1 * 4),
                   *(undefined4 *)(DAT_0004ec3c + uVar1 * 4));
    }
    iVar3 = FUN_0001e31d();
    if (*(int *)(iVar3 + 4) != 0) {
      iVar3 = FUN_0001e31d();
      uVar1 = (uint)local_136;
      FUN_0003733c(*(undefined4 *)(iVar3 + 4),uVar1,*(undefined4 *)(DAT_0004ec38 + uVar1 * 4),
                   *(undefined4 *)(DAT_0004ec3c + uVar1 * 4));
    }
  }
  FUN_00037562(local_12d);
  return;
}



/* ================================================================
 * 0001cb22  FUN_0001cb22
 * bytes: 268  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001cb22(undefined4 *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  byte bVar5;
  ushort local_212;
  undefined4 local_210 [56];
  undefined1 local_12d [285];

  bVar5 = 0;
  FUN_000374d0(local_12d,*param_1,((uint)param_1[1] >> 3) + 1,1);
  puVar3 = local_210;
  for (iVar1 = 0x38; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
  }
  FUN_0003768a(local_12d,&local_212,0x10,1);
  FUN_0003768a(local_12d,local_210,0x700,1);
  FUN_0001a3ca();
  iVar1 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar1 + 0x5ea8) + (uint)local_212) == '\0') {
    iVar1 = FUN_0001a3ca();
    puVar3 = local_210;
    puVar4 = (undefined4 *)((uint)local_212 * 0xe0 + *(int *)(iVar1 + 0x5e98));
    for (iVar2 = 0x38; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar4 = *puVar3;
      puVar3 = puVar3 + (uint)bVar5 * -2 + 1;
      puVar4 = puVar4 + (uint)bVar5 * -2 + 1;
    }
    iVar1 = FUN_0001a3ca();
    *(undefined1 *)(*(int *)(iVar1 + 0x5ea8) + (uint)local_212) = 1;
  }
  FUN_00037562(local_12d);
  return;
}



/* ================================================================
 * 0001cc52  FUN_0001cc52
 * bytes: 172  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_0001cc52(undefined4 *param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 extraout_ECX;
  undefined4 uVar3;
  undefined8 uVar4;
  int local_134;
  undefined1 local_12d [285];

  FUN_000374d0(local_12d,*param_1,((uint)param_1[1] >> 3) + 1,1);
  local_134 = -1;
  FUN_0003768a(local_12d,&local_134,0x20,1);
  if (local_134 != -1) {
    iVar1 = FUN_0001e31d();
    FUN_00037354(*(undefined4 *)(iVar1 + 4),local_134,extraout_ECX,extraout_ECX);
    piVar2 = (int *)FUN_0001e31d();
    if (*piVar2 != 0) {
      uVar4 = FUN_0001e31d();
      uVar3 = (undefined4)((ulonglong)uVar4 >> 0x20);
      FUN_00037374(*(undefined4 *)uVar4,local_134,uVar3,uVar3);
    }
  }
  FUN_00037562(local_12d);
  return;
}



/* ================================================================
 * 0001cd1d  FUN_0001cd1d
 * bytes: 33  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined1 FUN_0001cd1d(undefined4 param_1,int param_2)

{
  return *(undefined1 *)(DAT_0004ec44 + *(int *)(param_2 + 8));
}



/* ================================================================
 * 0001cd3e  FUN_0001cd3e
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001cd3e(void)

{
}



/* ================================================================
 * 0001d023  FUN_0001d023
 * bytes: 70  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

undefined4 FUN_0001d023(undefined4 param_1,int param_2)

{
  pthread_t __th;

  if ((*(pthread_t **)(param_2 + 4) != (pthread_t *)0x0) &&
     (__th = **(pthread_t **)(param_2 + 4), __th != 0)) {
    pthread_cancel(__th);
  }
  return 1;
}



/* ================================================================
 * 0001d0dc  FUN_0001d0dc
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001d0dc(void)

{
}



/* ================================================================
 * 0001d103  FUN_0001d103
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001d103(void)

{
}



/* ================================================================
 * 0001d12a  FUN_0001d12a
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001d12a(void)

{
}



/* ================================================================
 * 0001d15a  FUN_0001d15a
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001d15a(void)

{
}



/* ================================================================
 * 0001d18b  FUN_0001d18b
 * bytes: 93  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

undefined4 FUN_0001d18b(undefined4 param_1,int param_2)

{
  if (*(undefined **)(param_2 + 4) == &DAT_0004ec00) {
    (*DAT_0004ec34)("Please, use GlobalMutexLock()");
  }
  else if (*(undefined **)(param_2 + 4) != (undefined *)0x0) {
    std::mutex::lock();
  }
  return 1;
}



/* ================================================================
 * 0001d236  FUN_0001d236
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001d236(void)

{
}



/* ================================================================
 * 0001d288  FUN_0001d288
 * bytes: 24  status: ok
 * ================================================================ */

bool FUN_0001d288(undefined4 param_1,int param_2)

{
  bool bVar1;

  bVar1 = false;
  if (*(int **)(param_2 + 4) != (int *)0x0) {
    bVar1 = **(int **)(param_2 + 4) != 0;
  }
  return bVar1;
}



/* ================================================================
 * 0001d2a0  FUN_0001d2a0
 * bytes: 83  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

int * FUN_0001d2a0(undefined4 param_1,int param_2)

{
  int iVar1;
  int *piVar2;

  iVar1 = *(int *)(param_2 + 4);
  if (iVar1 == 0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = operator_new(4);
    *piVar2 = iVar1;
    std::mutex::lock();
  }
  return piVar2;
}



/* ================================================================
 * 0001d367  FUN_0001d367
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001d367(void)

{
}



/* ================================================================
 * 0001d3a6  FUN_0001d3a6
 * bytes: 17  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined * FUN_0001d3a6(void)

{
  return &DAT_0004ec00;
}



/* ================================================================
 * 0001d3b7  FUN_0001d3b7
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001d3b7(void)

{
}



/* ================================================================
 * 0001d3d0  FUN_0001d3d0
 * bytes: 28  status: ok
 * ================================================================ */

undefined1 FUN_0001d3d0(undefined4 param_1,int param_2)

{
  undefined1 uVar1;

  uVar1 = 2;
  if (*(int **)(param_2 + 4) != (int *)0x0) {
    uVar1 = **(int **)(param_2 + 4) != 0;
  }
  return uVar1;
}



/* ================================================================
 * 0001d3ec  FUN_0001d3ec
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001d3ec(void)

{
}



/* ================================================================
 * 0001d439  FUN_0001d439
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001d439(void)

{
}



/* ================================================================
 * 0001d460  FUN_0001d460
 * bytes: 1034  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_0001d460(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  int local_26c;
  int local_258;
  undefined4 local_254;
  undefined4 local_250;
  undefined4 local_24c;
  undefined4 local_248;
  undefined4 local_244;
  undefined1 local_23e [273];
  undefined1 local_12d [285];

  local_250 = *(undefined4 *)(param_2 + 0xc);
  local_258 = *(int *)(param_2 + 4);
  local_254 = *(undefined4 *)(param_2 + 8);
  local_24c = *(undefined4 *)(param_2 + 0x10);
  local_248 = *(undefined4 *)(param_2 + 0x14);
  local_244 = *(undefined4 *)(param_2 + 0x18);
  iVar2 = FUN_0001e31d();
  uVar3 = local_254;
  uVar1 = *(uint *)(*(int *)(*(int *)(iVar2 + 0xc) + 0x3f58) + 0x82);
  if ((((((uVar1 & 0xffffffdf) - 0x219 < 2) || (uVar1 == 0x1c1)) || (uVar1 - 0x4f11 < 2)) ||
      ((uVar1 == 0x506a || (uVar1 - 0x4ea2 < 2)))) || (uVar1 - 0x7533 < 2)) {
    iVar2 = FUN_0001a3ca();
    puVar4 = local_12d;
    *(undefined4 *)(*(int *)(iVar2 + 0x5ea4) + local_258 * 4) = uVar3;
    if ((uVar1 == 0x506a) || (uVar1 == 0x1c1)) {
      FUN_0003745a(puVar4);
      FUN_00037ae4(puVar4,&local_258,0x10,1);
      FUN_00037ae4(puVar4,&local_254,0x20,1);
      FUN_00037ae4(puVar4,&local_250,0x20,1);
      FUN_00037ae4(puVar4,&local_24c,0x20,1);
      FUN_00037ae4(puVar4,&local_248,0x20,1);
      FUN_00037ae4(puVar4,&local_244,0x20,1);
      uVar3 = FUN_0001e31d();
      FUN_000373be(uVar3,&DAT_0004e480,puVar4,0xffff,2);
    }
    else {
      FUN_0003745a(local_23e);
      FUN_00037ae4(local_23e,&local_258,0x10,1);
      FUN_00037ae4(local_23e,&local_254,0x20,1);
      FUN_00037ae4(local_23e,&local_250,0x20,1);
      FUN_00037ae4(local_23e,&local_24c,0x20,1);
      FUN_00037ae4(local_23e,&local_248,0x20,1);
      FUN_00037ae4(local_23e,&local_244,0x20,1);
      uVar3 = FUN_0001e31d();
      FUN_000373be(uVar3,&DAT_0004e480,local_23e,0xffff,2);
      local_26c = 3;
      do {
        local_258 = local_258 + 1;
        FUN_0003745a(puVar4);
        FUN_00037ae4(puVar4,&local_258,0x10,1);
        FUN_00037ae4(puVar4,&local_254,0x20,1);
        FUN_00037ae4(puVar4,&local_250,0x20,1);
        FUN_00037ae4(puVar4,&local_24c,0x20,1);
        FUN_00037ae4(puVar4,&local_248,0x20,1);
        FUN_00037ae4(puVar4,&local_244,0x20,1);
        uVar3 = FUN_0001e31d();
        FUN_000373be(uVar3,&DAT_0004e480,puVar4,0xffff,2);
        FUN_00037562(puVar4);
        local_26c = local_26c + -1;
      } while (local_26c != 0);
      puVar4 = local_23e;
    }
    FUN_00037562(puVar4);
  }
  return 1;
}



/* ================================================================
 * 0001d8ac  FUN_0001d8ac
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001d8ac(void)

{
}



/* ================================================================
 * 0001dbb7  FUN_0001dbb7
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001dbb7(void)

{
}



/* ================================================================
 * 0001dcbc  FUN_0001dcbc
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001dcbc(void)

{
}



/* ================================================================
 * 0001dcf5  FUN_0001dcf5
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001dcf5(void)

{
}



/* ================================================================
 * 0001dd3e  FUN_0001dd3e
 * bytes: 467  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001dd3e(int param_1)

{
  undefined4 **ppuVar1;
  void *pvVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 **ppuVar6;
  int local_48;
  undefined4 *local_3c;
  uint local_38;
  int local_34;
  int local_30;

  if (*(int *)(param_1 + 4) != 0) {
    std::__cxx11::string::string<std::allocator<char>>
              ((string *)&local_34,*(char **)(param_1 + 8),(allocator *)&local_38);
    iVar4 = *(int *)(param_1 + 0xc) * 4;
    for (local_48 = local_30 + local_34; iVar4 = iVar4 + -4, local_34 != local_48;
        local_48 = local_48 + -1) {
      ppuVar6 = (undefined4 **)
                (CONCAT31((int3)((uint)local_48 >> 8),*(undefined1 *)(local_48 + -1)) - 100);
      bVar3 = (byte)ppuVar6;
      if (bVar3 < 0x15) {
        ppuVar1 = (undefined4 **)(1 << (bVar3 & 0x1f));
        if (((uint)ppuVar1 & 0x100025) == 0) {
          if (((uint)ppuVar1 & 0x44000) == 0) {
            if (bVar3 == 0xf) {
              FUN_0001fc8e(*(undefined4 *)(param_1 + 0x14),
                           *(undefined4 *)(*(int *)(param_1 + 4) + iVar4),&local_3c,ppuVar6);
              FUN_0001fe91(local_3c,&local_38);
              pvVar2 = operator_new__(local_38);
              FUN_0001fcda(pvVar2,local_3c,0,local_38 + 1);
              FUN_0001fde4(*(undefined4 *)(param_1 + 0x10),local_3c,0,pvVar2,0,0);
              operator_delete__(pvVar2);
            }
            goto LAB_0001de7b;
          }
          uVar5 = *(undefined4 *)(*(int *)(param_1 + 4) + iVar4);
          ppuVar1 = ppuVar6;
        }
        else {
          ppuVar6 = &local_3c;
          FUN_0001fc8e(*(undefined4 *)(param_1 + 0x10),
                       *(undefined4 *)(*(int *)(param_1 + 4) + iVar4),ppuVar6,ppuVar1);
          uVar5 = *local_3c;
        }
        FUN_0001fdbe(*(undefined4 *)(param_1 + 0x10),uVar5,ppuVar6,ppuVar1);
      }
LAB_0001de7b:
    }
    std::__cxx11::string::_M_dispose();
  }
  if (*(void **)(param_1 + 4) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 4));
  }
  if (*(void **)(param_1 + 0x18) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 0x18));
  }
  if (*(void **)(param_1 + 8) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 8));
  }
  if (*(void **)(param_1 + 0x1c) != (void *)0x0) {
    operator_delete__(*(void **)(param_1 + 0x1c));
  }
  if (*(void **)(param_1 + 0x10) != (void *)0x0) {
    operator_delete(*(void **)(param_1 + 0x10),0x68);
  }
  return;
}



/* ================================================================
 * 0001df2d  FUN_0001df2d
 * bytes: 690  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 * FUN_0001df2d(int *param_1,uint *param_2)

{
  uint uVar1;
  uint uVar2;
  void *pvVar3;
  int iVar4;
  void *pvVar5;
  void *pvVar6;
  int *piVar7;
  int *piVar8;
  uint *puVar9;
  undefined4 *puVar10;
  int iVar11;
  int iVar12;
  int *piVar13;
  byte bVar14;
  undefined8 uVar15;
  undefined4 local_34;
  undefined4 local_30;
  int local_2c;
  int local_28;
  undefined1 local_24 [4];
  undefined4 *local_20 [4];

  bVar14 = 0;
  iVar12 = param_1[1];
  iVar4 = *param_1;
  if (iVar12 == 0) {
    iVar12 = *(int *)(iVar4 + 0x10) + iVar4;
  }
  iVar11 = *(int *)(iVar4 + 0x18) - *(int *)(iVar4 + 0x14);
  pvVar3 = operator_new__(iVar11 + 4);
  for (iVar4 = iVar11 + 3; -1 < iVar4; iVar4 = iVar4 + -1) {
    *(undefined1 *)((int)pvVar3 + ((iVar11 + 3) - iVar4)) = 0;
  }
  local_34 = 0;
  local_30 = 0;
  iVar4 = (int)pvVar3 + (4 - iVar12);
  FUN_0001fc8e(param_1,param_2[1],&local_34,&__DT_PLTGOT);
  FUN_0001fc8e(param_1,param_2[2],&local_30);
  FUN_0001fe91(local_34,&local_2c);
  FUN_0001fe91(local_30,&local_28);
  pvVar5 = operator_new__(local_2c + 1);
  pvVar6 = operator_new__(local_28 + 1);
  FUN_0001fcda(pvVar5,local_34,0,local_2c + 1);
  FUN_0001fcda(pvVar6,local_30,0,local_28 + 1);
  piVar7 = operator_new(0x68);
  piVar8 = param_1;
  piVar13 = piVar7;
  for (iVar12 = 0x1a; iVar12 != 0; iVar12 = iVar12 + -1) {
    *piVar13 = *piVar8;
    piVar8 = piVar8 + (uint)bVar14 * -2 + 1;
    piVar13 = piVar13 + (uint)bVar14 * -2 + 1;
  }
  piVar7[6] = iVar4;
  piVar7[9] = iVar11 + iVar4;
  piVar7[8] = iVar11 + iVar4;
  piVar7[3] = 0;
  piVar7[7] = iVar4;
  piVar7[2] = (int)FUN_0001fbe3;
  FUN_0001fe7b(piVar7,0x68656463,0);
  iVar12 = FUN_0001fc42(piVar7,pvVar5,local_24);
  if (iVar12 == 0) {
    uVar2 = *param_2;
    uVar1 = (uVar2 >> 2) - 2;
    if ((int)uVar1 < 1) {
      piVar8 = (int *)0x0;
    }
    else {
      if (uVar1 < 0x20000000) {
        piVar8 = operator_new__(uVar1 * 4);
        uVar15 = CONCAT44(uVar2 >> 2,piVar8);
      }
      else {
        uVar15 = __cxa_throw_bad_array_new_length();
      }
      do {
        iVar12 = (int)((ulonglong)uVar15 >> 0x20);
        puVar9 = (uint *)uVar15;
        iVar4 = iVar12 + -1;
        uVar15 = CONCAT44(iVar4,puVar9 + 1);
        *puVar9 = param_2[iVar12];
      } while (iVar4 != 2);
    }
    puVar10 = operator_new(4);
    *puVar10 = 0;
    local_20[0] = operator_new(0x20);
    local_20[0][3] = uVar1;
    local_20[0][1] = piVar8;
    local_20[0][4] = piVar7;
    local_20[0][5] = param_1;
    *local_20[0] = &PTR_FUN_0004dc30;
    local_20[0][6] = pvVar3;
    local_20[0][2] = pvVar6;
    local_20[0][7] = pvVar5;
    std::thread::_M_start_thread
              (puVar10,(unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)
                       local_20,PTR__M_thread_deps_never_run_0004df48);
    std::unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
              ((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)local_20)
    ;
  }
  else {
    operator_delete(piVar7,0x68);
    operator_delete__(pvVar3);
    operator_delete__(pvVar6);
    operator_delete__(pvVar5);
    puVar10 = (undefined4 *)0x0;
  }
  return puVar10;
}



/* ================================================================
 * 0001e20e  std::mutex::lock
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::mutex::lock() */

void std::mutex::lock(void)

{
}



/* ================================================================
 * 0001e23e  std::__cxx11::string::string<std::allocator<char>>
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__cxx11::string::string<std::allocator<char> >(char const*, std::allocator<char> const&) */

void __thiscall
std::__cxx11::string::string<std::allocator<char>>(string *this,char *param_1,allocator *param_2)

{
}



/* ================================================================
 * 0001e2d4  std::this_thread::sleep_for<long_long,std::ratio<1ll,1ll>>
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* void std::this_thread::sleep_for<long long, std::ratio<1ll, 1ll> >(std::chrono::duration<long
   long, std::ratio<1ll, 1ll> > const&) */

void std::this_thread::sleep_for<long_long,std::ratio<1ll,1ll>>(duration *param_1)

{
}



/* ================================================================
 * 0001e31d  FUN_0001e31d
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_0001e31d(void)

{
  return _DAT_081ca4bc;
}



/* ================================================================
 * 0001e323  FUN_0001e323
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001e323(void)

{
}



/* ================================================================
 * 0001e3b7  FUN_0001e3b7
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001e3b7(void)

{
}



/* ================================================================
 * 0001e4a6  std::unordered_map<unsigned_short,char,std::hash<unsigned_short>,std::equal_to<unsigned_short>,std::allocator<std::pair<unsigned_short_const,char>>>::~unordered_map
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::unordered_map<unsigned short, char, std::hash<unsigned short>, std::equal_to<unsigned
   short>, std::allocator<std::pair<unsigned short const, char> > >::~unordered_map() */

void __thiscall
std::
unordered_map<unsigned_short,char,std::hash<unsigned_short>,std::equal_to<unsigned_short>,std::allocator<std::pair<unsigned_short_const,char>>>
::~unordered_map(unordered_map<unsigned_short,char,std::hash<unsigned_short>,std::equal_to<unsigned_short>,std::allocator<std::pair<unsigned_short_const,char>>>
                 *this)

{
}



/* ================================================================
 * 0001e514  FUN_0001e514
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001e514(void)

{
}



/* ================================================================
 * 0001e566  FUN_0001e566
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001e566(void)

{
}



/* ================================================================
 * 0001e5ba  FUN_0001e5ba
 * bytes: 74  status: ok
 * ================================================================ */

undefined8 __regparm3 FUN_0001e5ba(int *param_1,uint param_2,short *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined4 unaff_EBX;
  undefined4 *puVar3;

  puVar3 = *(undefined4 **)(*param_1 + param_2 * 4);
  if (puVar3 != (undefined4 *)0x0) {
    unaff_EBX = CONCAT22(*param_3,(short)unaff_EBX);
    puVar1 = (undefined4 *)*puVar3;
    do {
      puVar2 = puVar1;
      if (*param_3 == *(short *)(puVar2 + 1)) goto LAB_0001e5fc;
      puVar1 = (undefined4 *)*puVar2;
    } while ((puVar1 != (undefined4 *)0x0) &&
            (puVar3 = puVar2, param_2 == (uint)*(ushort *)(puVar1 + 1) % (uint)param_1[1]));
    puVar3 = (undefined4 *)0x0;
  }
LAB_0001e5fc:
  return CONCAT44(unaff_EBX,puVar3);
}



/* ================================================================
 * 0001e604  FUN_0001e604
 * bytes: 18  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001e604(void)

{
}



/* ================================================================
 * 0001e66d  FUN_0001e66d
 * bytes: 97  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.cx replaced with injection: get_pc_thunk_cx */

undefined8 FUN_0001e66d(undefined4 param_1)

{
  undefined4 *puVar1;
  undefined4 in_ECX;
  undefined8 uVar2;
  undefined4 local_c;

  local_c = CONCAT22((short)((uint)in_ECX >> 0x10),(short)param_1);
  puVar1 = DAT_0004ec20;
  if (DAT_0004ec24 == 0) {
    for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
      if (*(short *)(puVar1 + 1) == (short)param_1) goto LAB_0001e6c5;
    }
    param_1 = CONCAT31((int3)((uint)param_1 >> 8),0xff);
  }
  else {
    uVar2 = FUN_0001e5ba();
    param_1 = CONCAT31((int3)((ulonglong)uVar2 >> 0x28),0xff);
    if (((undefined4 *)uVar2 != (undefined4 *)0x0) &&
       (puVar1 = (undefined4 *)*(undefined4 *)uVar2, puVar1 != (undefined4 *)0x0)) {
LAB_0001e6c5:
      param_1 = CONCAT31((int3)((uint)param_1 >> 8),*(undefined1 *)((int)puVar1 + 6));
    }
  }
  return CONCAT44(local_c,param_1);
}



/* ================================================================
 * 0001e6ce  FUN_0001e6ce
 * bytes: 22  status: ok
 * ================================================================ */

ulonglong FUN_0001e6ce(undefined4 param_1,int param_2)

{
  undefined2 uVar1;
  char cVar2;

  uVar1 = *(undefined2 *)(param_2 + 4);
  cVar2 = FUN_0001e66d();
  return (ulonglong)CONCAT24(uVar1,(int)cVar2);
}



/* ================================================================
 * 0001e6e4  FUN_0001e6e4
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001e6e4(void)

{
}



/* ================================================================
 * 0001e764  FUN_0001e764
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001e764(void)

{
}



/* ================================================================
 * 0001e9cf  FUN_0001e9cf
 * bytes: 323  status: ok
 * ================================================================ */

void __regparm1 FUN_0001e9cf(int param_1,ushort *param_2,int param_3,undefined1 param_4)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 extraout_EDX;
  undefined1 *puVar6;
  uint auStack_70 [9];
  undefined1 auStack_4c [3];
  undefined1 local_49;
  ushort *local_48;
  int *local_44;
  uint local_40;
  ushort *local_3c;
  uint local_38;
  int local_34;
  int local_30;
  ushort local_2a;
  undefined4 local_28;
  char local_21;
  undefined4 local_20;

  puVar6 = auStack_4c;
  local_49 = param_4;
  local_3c = param_2;
  local_48 = param_2 + param_3;
  piVar1 = (int *)(param_1 + 0xc24);
  local_44 = piVar1;
  local_30 = param_1;
  while (local_48 != local_3c) {
    local_2a = *local_3c;
    local_40 = (uint)local_2a;
    local_34 = CONCAT22(local_34._2_2_,local_2a);
    local_38 = local_40 % *(uint *)(param_1 + 0xc28);
    *(undefined4 *)(puVar6 + -4) = 0x1ea2c;
    puVar4 = (undefined4 *)FUN_0001e5ba();
    if ((puVar4 == (undefined4 *)0x0) || (piVar5 = (int *)*puVar4, piVar5 == (int *)0x0)) {
      *(undefined4 *)(puVar6 + -0x10) = 7;
      *(undefined4 *)(puVar6 + -0x14) = 0x1ea47;
      piVar5 = operator_new(*(uint *)(puVar6 + -0x10));
      *piVar5 = 0;
      *(undefined1 *)((int)piVar5 + 6) = 0;
      *(short *)(piVar5 + 1) = (short)local_34;
      local_28 = *(undefined4 *)(param_1 + 0xc38);
      *(undefined4 *)(puVar6 + -0x10) = 1;
      *(undefined4 *)(puVar6 + -0x14) = *(undefined4 *)(param_1 + 0xc30);
      *(undefined4 *)(puVar6 + -0x18) = *(undefined4 *)(param_1 + 0xc28);
      *(int *)(puVar6 + -0x1c) = param_1 + 0xc34;
      *(char **)(puVar6 + -0x20) = &local_21;
      *(undefined4 *)(puVar6 + -0x24) = 0x1ea7b;
      std::__detail::_Prime_rehash_policy::_M_need_rehash
                (*(uint *)(puVar6 + -0x20),*(uint *)(puVar6 + -0x1c),*(uint *)(puVar6 + -0x18));
      if (local_21 != '\0') {
        *(undefined4 *)(puVar6 + -8) = extraout_EDX;
        *(undefined4 **)(puVar6 + -0xc) = &local_28;
        *(undefined4 *)(puVar6 + -0x10) = local_20;
        *(int **)(puVar6 + -0x14) = piVar1;
        *(undefined4 *)(puVar6 + -0x18) = 0x1ea95;
        std::
        _Hashtable<unsigned_short,std::pair<unsigned_short_const,char>,std::allocator<std::pair<unsigned_short_const,char>>,std::__detail::_Select1st,std::equal_to<unsigned_short>,std::hash<unsigned_short>,std::__detail::_Mod_range_hashing,std::__detail::_Default_ranged_hash,std::__detail::_Prime_rehash_policy,std::__detail::_Hashtable_traits<false,false,true>>
        ::_M_rehash(*(uint *)(puVar6 + -0x14),*(uint **)(puVar6 + -0x10));
        local_38 = local_40 % (uint)local_44[1];
      }
      puVar6 = puVar6 + -4;
      local_34 = *piVar1;
      piVar2 = (int *)(local_34 + local_38 * 4);
      if ((int *)*piVar2 == (int *)0x0) {
        iVar3 = *(int *)(param_1 + 0xc2c);
        *(int **)(param_1 + 0xc2c) = piVar5;
        *piVar5 = iVar3;
        if (iVar3 != 0) {
          *(int **)(local_34 + ((uint)*(ushort *)(iVar3 + 4) % (uint)local_44[1]) * 4) = piVar5;
        }
        *piVar2 = local_30 + 0xc2c;
      }
      else {
        *piVar5 = *(int *)*piVar2;
        *(int **)*piVar2 = piVar5;
      }
      *(int *)(local_30 + 0xc30) = *(int *)(local_30 + 0xc30) + 1;
    }
    local_3c = local_3c + 1;
    *(undefined1 *)((int)piVar5 + 6) = local_49;
  }
  return;
}



/* ================================================================
 * 0001eb2c  FUN_0001eb2c
 * bytes: 33  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001eb2c(void)

{
}



/* ================================================================
 * 0001ef3b  std::dec
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::dec(std::ios_base&) */

ios_base * std::dec(ios_base *param_1)

{
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xffffffb5 | 2;
  return param_1;
}



/* ================================================================
 * 0001ef51  std::hex
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::hex(std::ios_base&) */

ios_base * std::hex(ios_base *param_1)

{
  *(uint *)(param_1 + 0xc) = *(uint *)(param_1 + 0xc) & 0xffffffb5 | 8;
  return param_1;
}



/* ================================================================
 * 0001ef67  std::__cxx11::to_string
 * bytes: 321  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* std::__cxx11::to_string(unsigned int) */

__cxx11 * __thiscall std::__cxx11::to_string(__cxx11 *this,uint param_1)

{
  char *pcVar1;
  char cVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  char *pcVar6;
  undefined1 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined4 local_e8;

  bVar9 = 0;
  local_e8 = 1;
  uVar3 = param_1;
  do {
    if (uVar3 < 10) {
LAB_0001efc1:
      *(__cxx11 **)this = this + 8;
      if (0xf < local_e8) {
        uVar4 = FUN_0001e566();
        *(undefined4 *)this = uVar4;
        *(uint *)(this + 8) = local_e8;
      }
      if (local_e8 != 0) {
        puVar7 = *(undefined1 **)this;
        uVar3 = local_e8;
        if (local_e8 == 1) {
          *puVar7 = 0;
        }
        else {
          for (; uVar3 != 0; uVar3 = uVar3 - 1) {
            *puVar7 = 0;
            puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
          }
        }
      }
      *(uint *)(this + 4) = local_e8;
      *(undefined1 *)(*(int *)this + local_e8) = 0;
      pcVar1 = *(char **)this;
      puVar7 = &DAT_000399f4;
      puVar8 = &local_e8;
      for (iVar5 = 0xc9; iVar5 != 0; iVar5 = iVar5 + -1) {
        *(undefined1 *)puVar8 = *puVar7;
        puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
        puVar8 = (undefined4 *)((int)puVar8 + (uint)bVar9 * -2 + 1);
      }
      pcVar6 = pcVar1 + *(int *)(this + 4);
      while (99 < param_1) {
        iVar5 = (param_1 % 100) * 2;
        pcVar6[-1] = *(char *)((int)&local_e8 + iVar5 + 1);
        pcVar6[-2] = *(char *)((int)&local_e8 + iVar5);
        pcVar6 = pcVar6 + -2;
        param_1 = param_1 / 100;
      }
      cVar2 = (char)param_1 + '0';
      if (9 < param_1) {
        cVar2 = *(char *)((int)&local_e8 + param_1 * 2);
        pcVar1[1] = *(char *)((int)&local_e8 + param_1 * 2 + 1);
      }
      *pcVar1 = cVar2;
      return this;
    }
    if (uVar3 < 100) {
      local_e8 = local_e8 + 1;
      goto LAB_0001efc1;
    }
    if (uVar3 < 1000) {
      local_e8 = local_e8 + 2;
      goto LAB_0001efc1;
    }
    if (uVar3 < 10000) {
      local_e8 = local_e8 + 3;
      goto LAB_0001efc1;
    }
    local_e8 = local_e8 + 4;
    uVar3 = uVar3 / 10000;
  } while( true );
}



/* ================================================================
 * 0001f0a8  std::__cxx11::string::string
 * bytes: 100  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* std::__cxx11::string::string(std::__cxx11::string const&) */

void __thiscall std::__cxx11::string::string(string *this,string *param_1)

{
  uint uVar1;
  char *pcVar2;
  undefined4 uVar3;

  uVar1 = *(uint *)(param_1 + 4);
  *(string **)this = this + 8;
  pcVar2 = *(char **)param_1;
  if (0xf < uVar1) {
    uVar3 = FUN_0001e566();
    *(undefined4 *)this = uVar3;
    *(uint *)(this + 8) = uVar1;
  }
  _S_copy(*(char **)this,pcVar2,uVar1);
  *(uint *)(this + 4) = uVar1;
  *(undefined1 *)(*(int *)this + uVar1) = 0;
  return;
}



/* ================================================================
 * 0001f10c  FUN_0001f10c
 * bytes: 103  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001f10c(string *param_1,string *param_2)

{
  std::__cxx11::string::string(param_1,param_2);
  std::__cxx11::string::string(param_1 + 0x18,param_2 + 0x18);
  std::__cxx11::string::string(param_1 + 0x30,param_2 + 0x30);
  *(undefined2 *)(param_1 + 0x48) = *(undefined2 *)(param_2 + 0x48);
  *(undefined4 *)(param_1 + 0x4a) = *(undefined4 *)(param_2 + 0x4a);
  return;
}



/* ================================================================
 * 0001f1a2  FUN_0001f1a2
 * bytes: 518  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001f1a2(uint *param_1,undefined4 param_2)

{
  uint uVar1;
  int iVar2;
  void *pvVar3;
  uint *extraout_ECX;
  uint *puVar4;
  int iVar5;
  int extraout_EDX;
  undefined **ppuVar6;
  undefined1 *puVar7;
  uint *puVar8;
  undefined1 auStack_3c [12];
  int local_30;
  void *local_2c;
  int local_28;
  uint local_24;
  undefined **local_20;

  puVar7 = auStack_3c;
  ppuVar6 = (undefined **)param_1[9];
  puVar4 = (uint *)param_1[5];
  local_28 = (int)ppuVar6 - (int)puVar4;
  local_2c = (void *)(local_28 >> 2);
  local_20 = &__DT_PLTGOT;
  if (((int)(param_1[6] - param_1[7]) >> 1) * -0x69069069 +
      ((int)local_2c + ((ppuVar6 == (undefined **)0x0) - 1)) * 6 +
      ((int)(param_1[4] - param_1[2]) >> 1) * -0x69069069 == 0x3483483) {
    puVar7 = &stack0xffffffb4;
    std::__throw_length_error("cannot create std::deque larger than max_size()");
    puVar4 = extraout_ECX;
    ppuVar6 = &__DT_PLTGOT;
  }
  local_24 = *param_1;
  uVar1 = param_1[1];
  if (1 < uVar1 - ((int)((int)ppuVar6 - local_24) >> 2)) goto LAB_0001f35f;
  iVar5 = (int)local_2c + 2;
  if ((uint)(iVar5 * 2) < uVar1) {
    puVar8 = (uint *)(local_24 + (uVar1 - iVar5 >> 1) * 4);
    iVar2 = (int)ppuVar6 + (4 - (int)puVar4);
    if (puVar8 < puVar4) {
      if (iVar2 < 5) {
        if (iVar2 == 4) {
          *puVar8 = *puVar4;
        }
      }
      else {
        *(undefined ***)(puVar7 + -4) = ppuVar6;
        *(int *)(puVar7 + -8) = iVar2;
        *(uint **)(puVar7 + -0xc) = puVar4;
        *(uint **)(puVar7 + -0x10) = puVar8;
LAB_0001f27e:
        *(undefined4 *)(puVar7 + -0x14) = 0x1f286;
        memmove(*(void **)(puVar7 + -0x10),*(void **)(puVar7 + -0xc),*(size_t *)(puVar7 + -8));
      }
    }
    else {
      if (4 < iVar2) {
        *(int *)(puVar7 + -4) = iVar5;
        *(int *)(puVar7 + -8) = iVar2;
        *(uint **)(puVar7 + -0xc) = puVar4;
        *(int *)(puVar7 + -0x10) = (int)puVar8 + ((local_28 + 4) - iVar2);
        goto LAB_0001f27e;
      }
      if (iVar2 == 4) {
        *(uint *)((int)puVar8 + local_28) = *puVar4;
      }
    }
  }
  else {
    local_24 = 1;
    if (uVar1 != 0) {
      local_24 = uVar1;
    }
    local_24 = uVar1 + 2 + local_24;
    if (0x1fffffff < local_24) {
      if (0x3fffffff < local_24) {
        *(undefined4 *)(puVar7 + -4) = 0x1f2c2;
        std::__throw_bad_array_new_length();
      }
      *(undefined4 *)(puVar7 + -4) = 0x1f2c7;
      std::__throw_bad_alloc();
      iVar5 = extraout_EDX;
    }
    *(uint *)(puVar7 + -0x10) = local_24 << 2;
    *(undefined4 *)(puVar7 + -0x14) = 0x1f2dc;
    local_30 = iVar5;
    local_2c = operator_new(*(uint *)(puVar7 + -0x10));
    puVar8 = (uint *)((int)local_2c + (local_24 - local_30 >> 1) * 4);
    puVar4 = (uint *)param_1[5];
    pvVar3 = (void *)((param_1[9] + 4) - (int)puVar4);
    if ((int)pvVar3 < 5) {
      if (pvVar3 == (void *)0x4) {
        pvVar3 = (void *)*puVar4;
        *puVar8 = (uint)pvVar3;
      }
    }
    else {
      *(int *)(puVar7 + -4) = local_30;
      *(void **)(puVar7 + -8) = pvVar3;
      *(uint **)(puVar7 + -0xc) = puVar4;
      *(uint **)(puVar7 + -0x10) = puVar8;
      *(undefined4 *)(puVar7 + -0x14) = 0x1f30e;
      pvVar3 = memmove(*(void **)(puVar7 + -0x10),*(void **)(puVar7 + -0xc),*(size_t *)(puVar7 + -8)
                      );
    }
    *(void **)(puVar7 + -4) = pvVar3;
    *(void **)(puVar7 + -8) = pvVar3;
    *(uint *)(puVar7 + -0xc) = param_1[1] << 2;
    *(uint *)(puVar7 + -0x10) = *param_1;
    *(undefined4 *)(puVar7 + -0x14) = 0x1f32c;
    operator_delete(*(void **)(puVar7 + -0x10),*(uint *)(puVar7 + -0xc));
    *param_1 = (uint)local_2c;
    param_1[1] = local_24;
  }
  uVar1 = *puVar8;
  param_1[5] = (uint)puVar8;
  param_1[3] = uVar1;
  param_1[4] = uVar1 + 0x1d4;
  uVar1 = *(uint *)(local_28 + (int)puVar8);
  param_1[9] = (uint)(local_28 + (int)puVar8);
  param_1[7] = uVar1;
  param_1[8] = uVar1 + 0x1d4;
LAB_0001f35f:
  uVar1 = param_1[9];
  *(undefined4 *)(puVar7 + -0x10) = 0x1d4;
  *(undefined4 *)(puVar7 + -0x14) = 0x1f372;
  pvVar3 = operator_new(*(uint *)(puVar7 + -0x10));
  *(void **)(uVar1 + 4) = pvVar3;
  *(undefined4 *)(puVar7 + -0xc) = param_2;
  *(uint *)(puVar7 + -0x10) = param_1[6];
  *(undefined4 *)(puVar7 + -0x14) = 0x1f382;
  FUN_0001f10c();
  uVar1 = *(uint *)(param_1[9] + 4);
  param_1[9] = param_1[9] + 4;
  param_1[7] = uVar1;
  param_1[8] = uVar1 + 0x1d4;
  param_1[6] = uVar1;
  return;
}



/* ================================================================
 * 0001f3ea  FUN_0001f3ea
 * bytes: 86  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_0001f3ea(int param_1,undefined4 param_2)

{
  int iVar1;

  iVar1 = *(int *)(param_1 + 0x20) + -0x4e;
  if (*(int *)(param_1 + 0x18) == iVar1) {
    FUN_0001f1a2(param_1,param_2,iVar1,iVar1);
  }
  else {
    FUN_0001f10c(*(int *)(param_1 + 0x18),param_2,iVar1,iVar1);
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 0x4e;
  }
  std::condition_variable::notify_one();
  return;
}



/* ================================================================
 * 0001f440  std::__cxx11::string::_M_assign
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */
/* std::__cxx11::string::_M_assign(std::__cxx11::string const&) */

void std::__cxx11::string::_M_assign(string *param_1)

{
}



/* ================================================================
 * 0001f4cc  FUN_0001f4cc
 * bytes: 303  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001f4cc(string *param_1,undefined2 param_2,uint param_3)

{
  char cVar1;
  char *pcVar2;
  undefined4 local_48;
  char *local_34;
  uint local_30;
  undefined4 local_2c [7];

  *(undefined4 *)(param_1 + 0x34) = 0;
  *(string **)param_1 = param_1 + 8;
  *(string **)(param_1 + 0x18) = param_1 + 0x20;
  *(undefined4 *)(param_1 + 4) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(string **)(param_1 + 0x30) = param_1 + 0x38;
  param_1[8] = (string)0x0;
  param_1[0x20] = (string)0x0;
  param_1[0x38] = (string)0x0;
  std::__cxx11::to_string((__cxx11 *)&local_34,param_3);
  cVar1 = std::__cxx11::string::_M_is_local((string *)&local_34);
  if (cVar1 == '\0') {
    cVar1 = std::__cxx11::string::_M_is_local(param_1 + 0x18);
    pcVar2 = (char *)0x0;
    if (cVar1 == '\0') {
      local_48 = *(undefined4 *)(param_1 + 0x20);
      pcVar2 = *(char **)(param_1 + 0x18);
    }
    *(char **)(param_1 + 0x18) = local_34;
    *(uint *)(param_1 + 0x1c) = local_30;
    *(undefined4 *)(param_1 + 0x20) = local_2c[0];
    if (pcVar2 == (char *)0x0) {
      local_34 = (char *)local_2c;
    }
    else {
      local_2c[0] = local_48;
      local_34 = pcVar2;
    }
  }
  else if (param_1 + 0x18 != (string *)&local_34) {
    if (local_30 != 0) {
      std::__cxx11::string::_S_copy(*(char **)(param_1 + 0x18),local_34,local_30);
    }
    *(uint *)(param_1 + 0x1c) = local_30;
    *(undefined1 *)(*(int *)(param_1 + 0x18) + local_30) = 0;
  }
  local_30 = 0;
  *local_34 = '\0';
  std::__cxx11::string::_M_dispose();
  *(undefined2 *)(param_1 + 0x48) = param_2;
  std::__cxx11::string::_M_assign(param_1);
  std::__cxx11::string::_M_assign(param_1 + 0x30);
  return;
}



/* ================================================================
 * 0001f62f  __i686.get_pc_thunk.cx
 * bytes: 4  status: ok
 * ================================================================ */

/* WARNING: This is an inlined function */

void __i686_get_pc_thunk_cx(void)

{
  return;
}



/* ================================================================
 * 0001f634  FUN_0001f634
 * bytes: 59  status: ok
 * ================================================================ */

int __regparm1
FUN_0001f634(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  undefined1 *puVar2;
  byte bVar3;

  bVar3 = 0;
  (*(code *)0x814af60)(param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_1);
  puVar2 = (undefined1 *)(param_2 + 0x10b);
  for (iVar1 = 0x25; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + (uint)bVar3 * -2 + 1;
  }
  return param_2;
}



/* ================================================================
 * 0001f670  FUN_0001f670
 * bytes: 44  status: ok
 * ================================================================ */

void __regparm1 FUN_0001f670(undefined4 param_1,int param_2,undefined4 param_3,char param_4)

{
  (*(code *)0x814c2f0)(param_2,param_3,param_4,param_1);
  *(char *)(param_2 + 0x127) = param_4 + '\x01';
  return;
}



/* ================================================================
 * 0001f69c  FUN_0001f69c
 * bytes: 54  status: ok
 * ================================================================ */

void FUN_0001f69c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  (*(code *)0x814c510)(param_1,param_2,param_3,param_4);
  *(undefined4 *)(param_1 + 0x128) = param_3;
  *(undefined4 *)(param_1 + 300) = param_4;
  return;
}



/* ================================================================
 * 0001f6d2  FUN_0001f6d2
 * bytes: 54  status: ok
 * ================================================================ */

void FUN_0001f6d2(int param_1)

{
  int iVar1;
  undefined1 *puVar2;

  puVar2 = (undefined1 *)(param_1 + 0x10b);
  for (iVar1 = 0x25; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar2 = 0;
    puVar2 = puVar2 + 1;
  }
  *(undefined4 *)(param_1 + 0x128) = 0xffffffff;
  *(undefined4 *)(param_1 + 300) = 0xffffffff;
  (*(code *)0x814b4c0)();
  return;
}



/* ================================================================
 * 0001f75c  FUN_0001f75c
 * bytes: 18  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001f75c(void)

{
}



/* ================================================================
 * 0001f7c6  FUN_0001f7c6
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001f7c6(void)

{
}



/* ================================================================
 * 0001f80a  FUN_0001f80a
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001f80a(void)

{
}



/* ================================================================
 * 0001f8ea  FUN_0001f8ea
 * bytes: 18  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001f8ea(void)

{
}



/* ================================================================
 * 0001f940  FUN_0001f940
 * bytes: 452  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

undefined1 FUN_0001f940(int param_1,undefined2 param_2,short param_3)

{
  char cVar1;
  undefined1 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 uVar5;
  undefined1 *local_e4;
  string local_d0 [24];
  undefined1 local_b8 [78];
  undefined1 local_6a [90];

  cVar1 = FUN_0001e66d(param_3);
  *(short *)(param_1 + 0x10b + cVar1 * 2) = param_3 + -999;
  uVar2 = (*(code *)0x814be30)(param_1,param_2,param_3);
  cVar1 = FUN_0001e66d(param_3);
  if (cVar1 == '\x05') {
    uVar3 = FUN_0001f75c();
    puVar4 = &DAT_0004ed70;
    uVar5 = uVar3;
    std::__cxx11::string::string(local_d0,(string *)&DAT_0004ed70);
    FUN_0001f4cc(local_b8,*(undefined2 *)(param_1 + 100),0x80000,local_d0,local_6a,puVar4,uVar3,
                 uVar5);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(local_6a,local_b8);
    FUN_0001f3ea(PTR_DAT_0004dfcc,local_6a);
  }
  else {
    cVar1 = FUN_0001e66d(param_3);
    if (cVar1 != '\t') {
      return uVar2;
    }
    uVar3 = FUN_0001f75c();
    puVar4 = &DAT_0004ed70;
    uVar5 = uVar3;
    std::__cxx11::string::string(local_d0,(string *)&DAT_0004ed70);
    FUN_0001f4cc(local_b8,*(undefined2 *)(param_1 + 100),0x20000,local_d0,local_6a,puVar4,uVar3,
                 uVar5);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(local_6a,local_b8);
    FUN_0001f3ea(PTR_DAT_0004dfcc,local_6a);
  }
  local_e4 = local_b8;
  FUN_0001ae64(local_6a);
  FUN_0001ae64(local_e4);
  return uVar2;
}



/* ================================================================
 * 0001fb80  FUN_0001fb80
 * bytes: 39  status: ok
 * ================================================================ */

int __regparm2 FUN_0001fb80(undefined4 param_1,int param_2,int param_3)

{
  int *piVar1;

  piVar1 = (int *)(param_2 + -0xcb14);
  do {
    if (*piVar1 == param_3) {
      return piVar1[2];
    }
    piVar1 = piVar1 + 3;
  } while (piVar1 != (int *)(param_2 + -0xc088));
  return -1;
}



/* ================================================================
 * 0001fba7  __i686.get_pc_thunk.dx
 * bytes: 4  status: ok
 * ================================================================ */

/* WARNING: This is an inlined function */

void __i686_get_pc_thunk_dx(void)

{
  return;
}



/* ================================================================
 * 0001fbab  FUN_0001fbab
 * bytes: 18  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fbab(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fbbb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*(code *)*DAT_0004edd0)();
  return;
}



/* ================================================================
 * 0001fbbd  FUN_0001fbbd
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fbbd(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fbcd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 4))();
  return;
}



/* ================================================================
 * 0001fbd0  FUN_0001fbd0
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fbd0(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fbe0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0xc))();
  return;
}



/* ================================================================
 * 0001fbe3  FUN_0001fbe3
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fbe3(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fbf3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x10))();
  return;
}



/* ================================================================
 * 0001fbf6  FUN_0001fbf6
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fbf6(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fc06. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x14))();
  return;
}



/* ================================================================
 * 0001fc09  FUN_0001fc09
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fc09(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fc19. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x18))();
  return;
}



/* ================================================================
 * 0001fc1c  FUN_0001fc1c
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fc1c(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fc2c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x1c))();
  return;
}



/* ================================================================
 * 0001fc2f  FUN_0001fc2f
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fc2f(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fc3f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x20))();
  return;
}



/* ================================================================
 * 0001fc42  FUN_0001fc42
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fc42(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fc52. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x24))();
  return;
}



/* ================================================================
 * 0001fc55  FUN_0001fc55
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fc55(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fc65. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x28))();
  return;
}



/* ================================================================
 * 0001fc68  FUN_0001fc68
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fc68(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fc78. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x2c))();
  return;
}



/* ================================================================
 * 0001fc7b  FUN_0001fc7b
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fc7b(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fc8b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x30))();
  return;
}



/* ================================================================
 * 0001fc8e  FUN_0001fc8e
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fc8e(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fc9e. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x34))();
  return;
}



/* ================================================================
 * 0001fca1  FUN_0001fca1
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fca1(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fcb1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x38))();
  return;
}



/* ================================================================
 * 0001fcb4  FUN_0001fcb4
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fcb4(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fcc4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x3c))();
  return;
}



/* ================================================================
 * 0001fcc7  FUN_0001fcc7
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fcc7(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fcd7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x40))();
  return;
}



/* ================================================================
 * 0001fcda  FUN_0001fcda
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fcda(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fcea. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x44))();
  return;
}



/* ================================================================
 * 0001fced  FUN_0001fced
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fced(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fcfd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x48))();
  return;
}



/* ================================================================
 * 0001fd00  FUN_0001fd00
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fd00(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fd10. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x4c))();
  return;
}



/* ================================================================
 * 0001fd13  FUN_0001fd13
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fd13(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fd23. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x50))();
  return;
}



/* ================================================================
 * 0001fd26  FUN_0001fd26
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fd26(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fd36. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x54))();
  return;
}



/* ================================================================
 * 0001fd39  FUN_0001fd39
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fd39(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fd49. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x58))();
  return;
}



/* ================================================================
 * 0001fd4c  FUN_0001fd4c
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fd4c(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fd5c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x5c))();
  return;
}



/* ================================================================
 * 0001fd5f  FUN_0001fd5f
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fd5f(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fd6f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x60))();
  return;
}



/* ================================================================
 * 0001fd72  FUN_0001fd72
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fd72(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fd82. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 100))();
  return;
}



/* ================================================================
 * 0001fd85  FUN_0001fd85
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fd85(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fd95. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x68))();
  return;
}



/* ================================================================
 * 0001fd98  FUN_0001fd98
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fd98(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fda8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x6c))();
  return;
}



/* ================================================================
 * 0001fdab  FUN_0001fdab
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fdab(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fdbb. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x70))();
  return;
}



/* ================================================================
 * 0001fdbe  FUN_0001fdbe
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fdbe(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fdce. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x74))();
  return;
}



/* ================================================================
 * 0001fdd1  FUN_0001fdd1
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fdd1(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fde1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x78))();
  return;
}



/* ================================================================
 * 0001fde4  FUN_0001fde4
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fde4(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fdf4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x7c))();
  return;
}



/* ================================================================
 * 0001fdf7  FUN_0001fdf7
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fdf7(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fe07. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x80))();
  return;
}



/* ================================================================
 * 0001fe23  FUN_0001fe23
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fe23(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fe33. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x88))();
  return;
}



/* ================================================================
 * 0001fe39  FUN_0001fe39
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fe39(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fe49. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x8c))();
  return;
}



/* ================================================================
 * 0001fe4f  FUN_0001fe4f
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fe4f(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fe5f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x90))();
  return;
}



/* ================================================================
 * 0001fe65  FUN_0001fe65
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fe65(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fe75. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x94))();
  return;
}



/* ================================================================
 * 0001fe7b  FUN_0001fe7b
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fe7b(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fe8b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x98))();
  return;
}



/* ================================================================
 * 0001fe91  FUN_0001fe91
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fe91(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fea1. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0x9c))();
  return;
}



/* ================================================================
 * 0001fea7  FUN_0001fea7
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fea7(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001feb7. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0xa0))();
  return;
}



/* ================================================================
 * 0001febd  FUN_0001febd
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001febd(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fecd. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0xa4))();
  return;
}



/* ================================================================
 * 0001fed3  FUN_0001fed3
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fed3(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fee3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0xa8))();
  return;
}



/* ================================================================
 * 0001fee9  FUN_0001fee9
 * bytes: 22  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0001fee9(void)

{
                    /* WARNING: Could not recover jumptable at 0x0001fef9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(DAT_0004edd0 + 0xac))();
  return;
}



/* ================================================================
 * 0001feff  FUN_0001feff
 * bytes: 3  status: ok
 * ================================================================ */

undefined4 FUN_0001feff(void)

{
  return 0;
}



/* ================================================================
 * 0001ff02  FUN_0001ff02
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001ff02(void)

{
}



/* ================================================================
 * 0001ff4b  FUN_0001ff4b
 * bytes: 20  status: ok
 * ================================================================ */

void __regparm3 FUN_0001ff4b(int param_1,int param_2,int param_3)

{
  *(undefined1 *)(param_3 + param_1) = 0xe9;
  *(int *)((undefined1 *)(param_3 + param_1) + 1) = param_2 - (param_1 + 5);
  return;
}



/* ================================================================
 * 0001ff5f  FUN_0001ff5f
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001ff5f(void)

{
}



/* ================================================================
 * 0001ffed  FUN_0001ffed
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0001ffed(void)

{
}



/* ================================================================
 * 00020021  FUN_00020021
 * bytes: 17  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020021(void)

{
}



/* ================================================================
 * 000200e9  FUN_000200e9
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000200e9(void)

{
}



/* ================================================================
 * 00020139  FUN_00020139
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020139(void)

{
}



/* ================================================================
 * 000201a3  FUN_000201a3
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000201a3(void)

{
}



/* ================================================================
 * 0002020d  FUN_0002020d
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002020d(void)

{
}



/* ================================================================
 * 00020273  FUN_00020273
 * bytes: 15  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020273(void)

{
}



/* ================================================================
 * 000202ad  FUN_000202ad
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000202ad(void)

{
}



/* ================================================================
 * 00020364  FUN_00020364
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020364(void)

{
}



/* ================================================================
 * 000203be  FUN_000203be
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000203be(void)

{
}



/* ================================================================
 * 00020415  FUN_00020415
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020415(void)

{
}



/* ================================================================
 * 000204e1  FUN_000204e1
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000204e1(void)

{
}



/* ================================================================
 * 00020537  FUN_00020537
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020537(void)

{
}



/* ================================================================
 * 0002057d  FUN_0002057d
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002057d(void)

{
}



/* ================================================================
 * 000205cb  FUN_000205cb
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000205cb(void)

{
}



/* ================================================================
 * 00020639  FUN_00020639
 * bytes: 68  status: ok
 * ================================================================ */

int __regparm3 FUN_00020639(int param_1,undefined4 param_2,code *param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;

  iVar3 = 0;
  iVar2 = param_1;
  while( true ) {
    if (*(int *)(param_1 + 4) <= iVar3) {
      return -0x16;
    }
    uVar1 = FUN_000205cb(param_1,iVar3,iVar2,iVar2);
    iVar2 = (*param_3)(param_2,uVar1);
    if (iVar2 == 0) break;
    iVar3 = iVar3 + 1;
  }
  return iVar3;
}



/* ================================================================
 * 0002067d  FUN_0002067d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002067d(void)

{
}



/* ================================================================
 * 000206f9  FUN_000206f9
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000206f9(void)

{
}



/* ================================================================
 * 00020813  FUN_00020813
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020813(void)

{
}



/* ================================================================
 * 000208fa  FUN_000208fa
 * bytes: 80  status: ok
 * ================================================================ */

int __regparm3 FUN_000208fa(int param_1,undefined4 param_2,code *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;

  iVar2 = 0;
  uVar1 = param_2;
  while( true ) {
    if (*(int *)(param_1 + 4) <= iVar2) {
      return -0x16;
    }
    uVar1 = FUN_000205cb(param_1,iVar2,uVar1,uVar1);
    uVar3 = (*param_3)(param_2,uVar1);
    uVar1 = (undefined4)((ulonglong)uVar3 >> 0x20);
    if ((int)uVar3 == 0) break;
    iVar2 = iVar2 + 1;
  }
  FUN_00020813(param_1,iVar2,1,0);
  return iVar2;
}



/* ================================================================
 * 0002094a  FUN_0002094a
 * bytes: 22  status: ok
 * ================================================================ */

void FUN_0002094a(int param_1)

{
  FUN_00020813(param_1,0,*(undefined4 *)(param_1 + 4));
  return;
}



/* ================================================================
 * 00020960  FUN_00020960
 * bytes: 147  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

int FUN_00020960(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char *__assertion;
  uint __line;

  if (param_1 == 0) {
    __line = 0x203;
    __assertion = "a != NULL";
  }
  else {
    if (param_2 != 0) {
      if ((*(int *)(param_1 + 4) == *(int *)(param_1 + 8)) &&
         (iVar2 = FUN_000204e1(param_1), iVar2 < 0)) {
        return iVar2;
      }
      iVar1 = *(int *)(param_1 + 4);
      iVar2 = iVar1 + 1;
      *(int *)(param_1 + 4) = iVar2;
      FUN_0002067d(param_1,iVar1,param_2,iVar2);
      return *(int *)(param_1 + 4) + -1;
    }
    __line = 0x204;
    __assertion = "elem != NULL";
  }
                    /* WARNING: Subroutine does not return */
  __assert_fail(__assertion,"/home/yuri/projects/ssmp server plugin (linux)/src/sampgdk.cpp",__line,
                "int sampgdk_array_append(sampgdk_array*, void*)");
}



/* ================================================================
 * 000209f3  FUN_000209f3
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000209f3(void)

{
}



/* ================================================================
 * 00020a37  FUN_00020a37
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020a37(void)

{
}



/* ================================================================
 * 00020a9b  FUN_00020a9b
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020a9b(void)

{
}



/* ================================================================
 * 00020aff  FUN_00020aff
 * bytes: 15  status: ok
 * ================================================================ */

undefined4 FUN_00020aff(void)

{
  FUN_0001ff5f();
  return 0;
}



/* ================================================================
 * 00020b0e  FUN_00020b0e
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_00020b0e(void)

{
  return;
}



/* ================================================================
 * 00020b0f  FUN_00020b0f
 * bytes: 16  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020b0f(void)

{
}



/* ================================================================
 * 00020b5e  FUN_00020b5e
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020b5e(void)

{
}



/* ================================================================
 * 00020bf5  FUN_00020bf5
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020bf5(void)

{
}



/* ================================================================
 * 00020c67  FUN_00020c67
 * bytes: 30  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00020c67(void)

{
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnGameModeExit()");
}



/* ================================================================
 * 00020c8f  FUN_00020c8f
 * bytes: 30  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00020c8f(void)

{
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnGameModeInit()");
}



/* ================================================================
 * 00020cc1  FUN_00020cc1
 * bytes: 457  status: ok
 * ================================================================ */

int __regparm1 FUN_00020cc1(int param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  uint *puVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  bool bVar11;
  uint local_24;

  iVar3 = FUN_00016180(0x13);
  if (iVar3 != 0) {
    FUN_00020273();
    FUN_00020273();
    local_24 = 0;
    do {
      iVar5 = local_24 + param_2;
      puVar6 = (uint *)(param_1 + -0xbe54);
      uVar4 = 0;
      do {
        if ((uint)*(byte *)(iVar5 + uVar4) == *puVar6) {
          uVar4 = uVar4 + 1;
        }
        puVar6 = puVar6 + 1;
      } while (puVar6 != (uint *)(param_1 + -0xbe28));
      uVar9 = (uint)*(byte *)(iVar5 + uVar4);
      puVar6 = (uint *)(param_1 + -0xbfd4);
      while( true ) {
        uVar2 = puVar6[2];
        bVar11 = false;
        if ((uVar9 == *puVar6) && (bVar11 = true, (uVar2 & 2) != 0)) {
          bVar11 = (*(byte *)(iVar5 + 1 + uVar4) >> 3 & 7) == puVar6[1];
        }
        if ((((uVar2 & 0x20) != 0) && (*puVar6 == (uVar9 & 0xf8))) || (bVar11)) break;
        puVar6 = puVar6 + 3;
        if ((uint *)(param_1 + -0xbe6c) == puVar6) goto LAB_00020e0f;
      }
      iVar8 = uVar4 + 1;
      if (uVar9 == 0) {
LAB_00020e0f:
                    /* WARNING: Subroutine does not return */
        FUN_00020b5e(3,param_1 + -0x13fa7,uVar4,uVar4);
      }
      iVar10 = 0;
      if ((uVar2 & 0x40) != 0) {
        iVar10 = iVar8;
      }
      if ((uVar2 & 1) != 0) {
        iVar7 = (int)(uint)*(byte *)(iVar5 + iVar8) >> 6;
        uVar9 = *(byte *)(iVar5 + iVar8) & 7;
        if ((iVar7 == 3) || (iVar8 = uVar4 + 3, uVar9 != 4)) {
          iVar8 = uVar4 + 2;
        }
        if (iVar7 == 1) {
          iVar8 = iVar8 + 1;
        }
        else if (iVar7 == 2) {
          iVar8 = iVar8 + 4;
        }
        if ((iVar7 == 0) && (uVar9 == 5)) {
          iVar8 = iVar8 + 4;
        }
      }
      uVar4 = uVar2 & 4;
      iVar8 = (iVar8 + 1) - (uint)(uVar4 == 0);
      if ((uVar2 & 8) != 0) {
        iVar8 = iVar8 + 2;
      }
      if ((uVar2 & 0x10) != 0) {
        iVar8 = iVar8 + 4;
      }
      if (iVar8 == 0) goto LAB_00020e0f;
      FUN_00016560(iVar3 + local_24,iVar5,iVar8,0x13 - local_24);
      if (iVar10 != 0) {
        piVar1 = (int *)(iVar3 + iVar10 + local_24);
        *piVar1 = *piVar1 - (iVar3 - param_2);
      }
      local_24 = local_24 + iVar8;
    } while (local_24 < 5);
    FUN_0001ff4b();
    FUN_0001ff4b();
  }
  return iVar3;
}



/* ================================================================
 * 00020e9c  FUN_00020e9c
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020e9c(void)

{
}



/* ================================================================
 * 00020ebe  FUN_00020ebe
 * bytes: 8  status: ok
 * ================================================================ */

undefined4 FUN_00020ebe(undefined4 param_1)

{
  return param_1;
}



/* ================================================================
 * 00020ec6  FUN_00020ec6
 * bytes: 34  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00020ec6(void)

{
  FUN_000202ad(&DAT_0004f510,1,4);
  return;
}



/* ================================================================
 * 00020ee8  FUN_00020ee8
 * bytes: 33  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00020ee8(void)

{
  FUN_00020364(&DAT_0004f510);
  return;
}



/* ================================================================
 * 00020f09  FUN_00020f09
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020f09(void)

{
}



/* ================================================================
 * 00020f71  FUN_00020f71
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020f71(void)

{
}



/* ================================================================
 * 00020fbc  FUN_00020fbc
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00020fbc(void)

{
}



/* ================================================================
 * 00021005  FUN_00021005
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021005(void)

{
}



/* ================================================================
 * 0002106b  FUN_0002106b
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002106b(void)

{
}



/* ================================================================
 * 000210ce  FUN_000210ce
 * bytes: 71  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_000210ce(void)

{
  int iVar1;
  undefined4 local_14;
  undefined4 local_10;

  local_14 = 0;
  local_10 = 0;
  iVar1 = FUN_000202ad(&DAT_0004f500,0x80,8);
  if (-1 < iVar1) {
    FUN_00020960(&DAT_0004f500,&local_14,iVar1,iVar1);
  }
  return;
}



/* ================================================================
 * 00021115  FUN_00021115
 * bytes: 33  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00021115(void)

{
  FUN_00020364(&DAT_0004f500);
  return;
}



/* ================================================================
 * 00021136  FUN_00021136
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021136(void)

{
}



/* ================================================================
 * 000211a8  FUN_000211a8
 * bytes: 23  status: ok
 * ================================================================ */

undefined4 FUN_000211a8(int param_1)

{
  undefined4 uVar1;

  if (param_1 != 0) {
    uVar1 = FUN_00021136();
    return uVar1;
  }
  return 0;
}



/* ================================================================
 * 000211bf  FUN_000211bf
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000211bf(void)

{
}



/* ================================================================
 * 0002126d  FUN_0002126d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002126d(void)

{
}



/* ================================================================
 * 00021359  FUN_00021359
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021359(void)

{
}



/* ================================================================
 * 000213c2  FUN_000213c2
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000213c2(void)

{
}



/* ================================================================
 * 00021413  FUN_00021413
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021413(void)

{
}



/* ================================================================
 * 00021464  FUN_00021464
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021464(void)

{
}



/* ================================================================
 * 000214cb  FUN_000214cb
 * bytes: 38  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

undefined4 FUN_000214cb(int *param_1)

{
  if (param_1 != (int *)0x0) {
    *param_1 = DAT_0004f504 + -1;
  }
  return DAT_0004f500;
}



/* ================================================================
 * 000214f1  thunk_FUN_000214cb
 * bytes: 2  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

undefined4 thunk_FUN_000214cb(int *param_1)

{
  if (param_1 != (int *)0x0) {
    *param_1 = DAT_0004f504 + -1;
  }
  return DAT_0004f500;
}



/* ================================================================
 * 000214f3  FUN_000214f3
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000214f3(void)

{
}



/* ================================================================
 * 0002153e  thunk_FUN_000214f3
 * bytes: 2  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void thunk_FUN_000214f3(void)

{
}



/* ================================================================
 * 00021540  FUN_00021540
 * bytes: 19  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021540(void)

{
}



/* ================================================================
 * 00021599  FUN_00021599
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021599(void)

{
}



/* ================================================================
 * 000216a7  FUN_000216a7
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000216a7(void)

{
}



/* ================================================================
 * 00021706  FUN_00021706
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021706(void)

{
}



/* ================================================================
 * 0002180d  FUN_0002180d
 * bytes: 25  status: ok
 * ================================================================ */

void FUN_0002180d(void)

{
  int iVar1;

  iVar1 = FUN_0002020d();
  if (iVar1 != 0) {
    *(undefined4 *)(iVar1 + 8) = 0;
  }
  return;
}



/* ================================================================
 * 00021826  FUN_00021826
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021826(void)

{
}



/* ================================================================
 * 0002188c  FUN_0002188c
 * bytes: 18  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002188c(void)

{
}



/* ================================================================
 * 00021941  FUN_00021941
 * bytes: 33  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00021941(void)

{
  FUN_00020364(&DAT_0004f4e0);
  return;
}



/* ================================================================
 * 00021962  FUN_00021962
 * bytes: 17  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined * FUN_00021962(void)

{
  return &DAT_0004f440;
}



/* ================================================================
 * 00021973  FUN_00021973
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021973(void)

{
}



/* ================================================================
 * 00021a37  FUN_00021a37
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021a37(void)

{
}



/* ================================================================
 * 00021b2b  FUN_00021b2b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021b2b(void)

{
}



/* ================================================================
 * 00021bb2  FUN_00021bb2
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021bb2(void)

{
}



/* ================================================================
 * 00021c13  thunk_FUN_00021bb2
 * bytes: 2  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void thunk_FUN_00021bb2(void)

{
}



/* ================================================================
 * 00021c15  FUN_00021c15
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021c15(void)

{
}



/* ================================================================
 * 00021cd3  FUN_00021cd3
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021cd3(void)

{
}



/* ================================================================
 * 00021d9d  FUN_00021d9d
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021d9d(void)

{
}



/* ================================================================
 * 00021e15  FUN_00021e15
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021e15(void)

{
}



/* ================================================================
 * 00021e8d  FUN_00021e8d
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021e8d(void)

{
}



/* ================================================================
 * 00021f03  FUN_00021f03
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021f03(void)

{
}



/* ================================================================
 * 00021fab  FUN_00021fab
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00021fab(void)

{
}



/* ================================================================
 * 00022039  FUN_00022039
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00022039(void)

{
}



/* ================================================================
 * 00022082  FUN_00022082
 * bytes: 24  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00022082(void)

{
}



/* ================================================================
 * 0002240d  thunk_FUN_00022082
 * bytes: 5  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void thunk_FUN_00022082(void)

{
}



/* ================================================================
 * 00022412  FUN_00022412
 * bytes: 197  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_00022412(undefined4 param_1,char *param_2,double *param_3)

{
  double dVar1;
  char cVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  char *local_1a0;
  undefined4 local_19c [32];
  float local_11c [67];

  if (param_2 == (char *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("format_ptr != NULL",
                  "/home/yuri/projects/ssmp server plugin (linux)/src/sampgdk.cpp",0x60a,
                  "cell sampgdk_native_invoke(AMX_NATIVE, const char*, va_list)");
  }
  pfVar5 = local_11c;
  local_1a0 = param_2;
  iVar3 = 0;
  do {
    cVar2 = *local_1a0;
    if ((cVar2 == '\0') || (iVar3 == 0x20)) {
      FUN_00022082(param_1,param_2,local_19c,iVar3);
      return;
    }
    if (cVar2 < 't') {
      if (cVar2 < 'a') {
        if ((cVar2 != 'A') && (1 < (byte)(cVar2 + 0xaeU))) goto LAB_000224dd;
LAB_000224d0:
        local_19c[iVar3] = *(undefined4 *)param_3;
        pfVar4 = pfVar5;
      }
      else {
        switch(cVar2) {
        case 'a':
        case 'r':
        case 's':
          goto LAB_000224d0;
        case 'b':
          *(bool *)pfVar5 = *(int *)param_3 != 0;
          break;
        default:
          goto LAB_000224dd;
        case 'd':
        case 'i':
          *pfVar5 = *(float *)param_3;
          break;
        case 'f':
          dVar1 = *param_3;
          local_19c[iVar3] = pfVar5;
          param_3 = param_3 + 1;
          pfVar4 = pfVar5 + 2;
          *pfVar5 = (float)dVar1;
          goto code_r0x000224dc;
        }
        local_19c[iVar3] = pfVar5;
        pfVar4 = pfVar5 + 2;
      }
      param_3 = (double *)((int)param_3 + 4);
code_r0x000224dc:
      iVar3 = iVar3 + 1;
      pfVar5 = pfVar4;
    }
LAB_000224dd:
    local_1a0 = local_1a0 + 1;
  } while( true );
}



/* ================================================================
 * 00022503  FUN_00022503
 * bytes: 23  status: ok
 * ================================================================ */

void FUN_00022503(undefined4 param_1,undefined4 param_2)

{
  FUN_00022412(param_1,param_2,&stack0x0000000c);
  return;
}



/* ================================================================
 * 0002251a  thunk_FUN_00022412
 * bytes: 5  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void thunk_FUN_00022412(undefined4 param_1,char *param_2,double *param_3)

{
  double dVar1;
  char cVar2;
  int iVar3;
  float *pfVar4;
  float *pfVar5;
  char *pcStack_1a0;
  undefined4 auStack_19c [32];
  float afStack_11c [67];

  if (param_2 == (char *)0x0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("format_ptr != NULL",
                  "/home/yuri/projects/ssmp server plugin (linux)/src/sampgdk.cpp",0x60a,
                  "cell sampgdk_native_invoke(AMX_NATIVE, const char*, va_list)");
  }
  pfVar5 = afStack_11c;
  pcStack_1a0 = param_2;
  iVar3 = 0;
  do {
    cVar2 = *pcStack_1a0;
    if ((cVar2 == '\0') || (iVar3 == 0x20)) {
      FUN_00022082(param_1,param_2,auStack_19c,iVar3);
      return;
    }
    if (cVar2 < 't') {
      if (cVar2 < 'a') {
        if ((cVar2 != 'A') && (1 < (byte)(cVar2 + 0xaeU))) goto LAB_000224dd;
LAB_000224d0:
        auStack_19c[iVar3] = *(undefined4 *)param_3;
        pfVar4 = pfVar5;
      }
      else {
        switch(cVar2) {
        case 'a':
        case 'r':
        case 's':
          goto LAB_000224d0;
        case 'b':
          *(bool *)pfVar5 = *(int *)param_3 != 0;
          break;
        default:
          goto LAB_000224dd;
        case 'd':
        case 'i':
          *pfVar5 = *(float *)param_3;
          break;
        case 'f':
          dVar1 = *param_3;
          auStack_19c[iVar3] = pfVar5;
          param_3 = param_3 + 1;
          pfVar4 = pfVar5 + 2;
          *pfVar5 = (float)dVar1;
          goto code_r0x000224dc;
        }
        auStack_19c[iVar3] = pfVar5;
        pfVar4 = pfVar5 + 2;
      }
      param_3 = (double *)((int)param_3 + 4);
code_r0x000224dc:
      iVar3 = iVar3 + 1;
      pfVar5 = pfVar4;
    }
LAB_000224dd:
    pcStack_1a0 = pcStack_1a0 + 1;
  } while( true );
}



/* ================================================================
 * 0002251f  FUN_0002251f
 * bytes: 23  status: ok
 * ================================================================ */

int FUN_0002251f(int *param_1)

{
  int iVar1;

  iVar1 = param_1[1];
  if (iVar1 == 0) {
    iVar1 = *param_1 + *(int *)(*param_1 + 0x10);
  }
  return iVar1 + param_1[8];
}



/* ================================================================
 * 00022536  FUN_00022536
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00022536(void)

{
}



/* ================================================================
 * 00022754  FUN_00022754
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00022754(void)

{
}



/* ================================================================
 * 000228cd  FUN_000228cd
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000228cd(void)

{
}



/* ================================================================
 * 0002291e  FUN_0002291e
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_0002291e(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x18101,local_24,local_20[0]);
}



/* ================================================================
 * 0002297a  FUN_0002297a
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_0002297a(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x180bd,local_24,local_20[0]);
}



/* ================================================================
 * 000229d6  FUN_000229d6
 * bytes: 54  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_000229d6(undefined4 param_1)

{
  undefined4 local_10;

  FUN_000228cd(param_1,0,&local_10);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnObjectMoved(%d)",local_10);
}



/* ================================================================
 * 00022a1b  FUN_00022a1b
 * bytes: 99  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_00022a1b(undefined4 param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_28);
  FUN_000228cd(param_1,1,&local_24);
  FUN_000228cd(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerClickPlayer(%d, %d, %d)",local_28,local_24,local_20[0]);
}



/* ================================================================
 * 00022aa3  FUN_00022aa3
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00022aa3(void)

{
}



/* ================================================================
 * 00022b11  FUN_00022b11
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00022b11(void)

{
}



/* ================================================================
 * 00022b7f  FUN_00022b7f
 * bytes: 58  status: ok
 * ================================================================ */

void FUN_00022b7f(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x17f45,local_20[0]);
}



/* ================================================================
 * 00022bd3  FUN_00022bd3
 * bytes: 99  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_00022bd3(undefined4 param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_28);
  FUN_000228cd(param_1,1,&local_24);
  FUN_000228cd(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerDeath(%d, %d, %d)",local_28,local_24,local_20[0]);
}



/* ================================================================
 * 00022c58  FUN_00022c58
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00022c58(void)

{
}



/* ================================================================
 * 00022cc3  FUN_00022cc3
 * bytes: 54  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_00022cc3(undefined4 param_1)

{
  undefined4 local_10;

  FUN_000228cd(param_1,0,&local_10);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerEnterCheckpoint(%d)",local_10);
}



/* ================================================================
 * 00022d08  FUN_00022d08
 * bytes: 54  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_00022d08(undefined4 param_1)

{
  undefined4 local_10;

  FUN_000228cd(param_1,0,&local_10);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerEnterRaceCheckpoint(%d)",local_10);
}



/* ================================================================
 * 00022d4d  FUN_00022d4d
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_00022d4d(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,&UNK_00017dfc + unaff_EDI,local_24,local_20[0]);
}



/* ================================================================
 * 00022da9  FUN_00022da9
 * bytes: 54  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_00022da9(undefined4 param_1)

{
  undefined4 local_10;

  FUN_000228cd(param_1,0,&local_10);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerExitedMenu(%d)",local_10);
}



/* ================================================================
 * 00022dee  FUN_00022dee
 * bytes: 98  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00022dee(undefined4 param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_28);
  FUN_000228cd(param_1,1,&local_24);
  FUN_000228cd(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerInteriorChange(%d, %d, %d)",local_28,local_24,local_20[0]);
}



/* ================================================================
 * 00022e63  FUN_00022e63
 * bytes: 98  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00022e63(undefined4 param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_28);
  FUN_000228cd(param_1,1,&local_24);
  FUN_000228cd(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerKeyStateChange(%d, %d, %d)",local_28,local_24,local_20[0]);
}



/* ================================================================
 * 00022ed8  FUN_00022ed8
 * bytes: 54  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_00022ed8(undefined4 param_1)

{
  undefined4 local_10;

  FUN_000228cd(param_1,0,&local_10);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerLeaveCheckpoint(%d)",local_10);
}



/* ================================================================
 * 00022f1d  FUN_00022f1d
 * bytes: 54  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_00022f1d(undefined4 param_1)

{
  undefined4 local_10;

  FUN_000228cd(param_1,0,&local_10);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerLeaveRaceCheckpoint(%d)",local_10);
}



/* ================================================================
 * 00022f62  FUN_00022f62
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_00022f62(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x17c9c,local_24,local_20[0]);
}



/* ================================================================
 * 00022fbe  FUN_00022fbe
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_00022fbe(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x17c5c,local_24,local_20[0]);
}



/* ================================================================
 * 0002301a  FUN_0002301a
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_0002301a(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x17c1d,local_24,local_20[0]);
}



/* ================================================================
 * 00023076  FUN_00023076
 * bytes: 99  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_00023076(undefined4 param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_28);
  FUN_000228cd(param_1,1,&local_24);
  FUN_000228cd(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerRequestDownload(%d, %d, %d)",local_28,local_24,local_20[0]);
}



/* ================================================================
 * 000230fe  FUN_000230fe
 * bytes: 58  status: ok
 * ================================================================ */

void FUN_000230fe(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x17b7a,local_20[0]);
}



/* ================================================================
 * 00023152  FUN_00023152
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_00023152(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x17b3f,local_24,local_20[0]);
}



/* ================================================================
 * 000231ae  FUN_000231ae
 * bytes: 58  status: ok
 * ================================================================ */

void FUN_000231ae(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,&UNK_00017b03 + unaff_EDI,local_20[0]);
}



/* ================================================================
 * 00023202  FUN_00023202
 * bytes: 98  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00023202(undefined4 param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_28);
  FUN_000228cd(param_1,1,&local_24);
  FUN_000228cd(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerStateChange(%d, %d, %d)",local_28,local_24,local_20[0]);
}



/* ================================================================
 * 00023277  FUN_00023277
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_00023277(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,&UNK_00017a6c + unaff_EDI,local_24,local_20[0]);
}



/* ================================================================
 * 000232d3  FUN_000232d3
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_000232d3(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,&UNK_00017a29 + unaff_EDI,local_24,local_20[0]);
}



/* ================================================================
 * 0002332f  FUN_0002332f
 * bytes: 58  status: ok
 * ================================================================ */

void FUN_0002332f(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,&UNK_000179e7 + unaff_EDI,local_20[0]);
}



/* ================================================================
 * 00023383  FUN_00023383
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00023383(void)

{
}



/* ================================================================
 * 000233ee  FUN_000233ee
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000233ee(void)

{
}



/* ================================================================
 * 0002345c  FUN_0002345c
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_0002345c(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,&UNK_00017909 + unaff_EDI,local_24,local_20[0]);
}



/* ================================================================
 * 000234b8  FUN_000234b8
 * bytes: 99  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_000234b8(undefined4 param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_28);
  FUN_000228cd(param_1,1,&local_24);
  FUN_000228cd(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnVehicleMod(%d, %d, %d)",local_28,local_24,local_20[0]);
}



/* ================================================================
 * 0002353d  FUN_0002353d
 * bytes: 99  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_0002353d(undefined4 param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_28);
  FUN_000228cd(param_1,1,&local_24);
  FUN_000228cd(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnVehiclePaintjob(%d, %d, %d)",local_28,local_24,local_20[0]);
}



/* ================================================================
 * 000235c2  FUN_000235c2
 * bytes: 121  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_000235c2(undefined4 param_1)

{
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_2c);
  FUN_000228cd(param_1,1,&local_28);
  FUN_000228cd(param_1,2,&local_24);
  FUN_000228cd(param_1,3,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnVehicleRespray(%d, %d, %d, %d)",local_2c,local_28,local_24,local_20[0]);
}



/* ================================================================
 * 00023661  FUN_00023661
 * bytes: 98  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00023661(undefined4 param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_28);
  FUN_000228cd(param_1,1,&local_24);
  FUN_000228cd(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnVehicleSirenStateChange(%d, %d, %d)",local_28,local_24,local_20[0]);
}



/* ================================================================
 * 000236d6  FUN_000236d6
 * bytes: 58  status: ok
 * ================================================================ */

void FUN_000236d6(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x17724,local_20[0]);
}



/* ================================================================
 * 0002372a  FUN_0002372a
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_0002372a(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,&UNK_000176e3 + unaff_EDI,local_24,local_20[0]);
}



/* ================================================================
 * 00023786  FUN_00023786
 * bytes: 75  status: ok
 * ================================================================ */

void FUN_00023786(undefined4 param_1)

{
  int unaff_EDI;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_00032e7a();
  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x176a1,local_24,local_20[0]);
}



/* ================================================================
 * 000237e2  FUN_000237e2
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000237e2(void)

{
}



/* ================================================================
 * 00023835  FUN_00023835
 * bytes: 99  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00023835(undefined4 param_1)

{
  undefined1 local_25;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_24);
  FUN_000237e2(param_1,1,&local_25);
  FUN_000228cd(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnEnterExitModShop(%d, %d, %d)",local_24,local_25,local_20[0]);
}



/* ================================================================
 * 000238ab  FUN_000238ab
 * bytes: 99  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_000238ab(undefined4 param_1)

{
  undefined1 local_25;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_24);
  FUN_000228cd(param_1,1,local_20);
  FUN_000237e2(param_1,2,&local_25);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerEnterVehicle(%d, %d, %d)",local_24,local_20[0],local_25);
}



/* ================================================================
 * 00023921  FUN_00023921
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00023921(void)

{
}



/* ================================================================
 * 00023971  FUN_00023971
 * bytes: 141  status: ok
 * ================================================================ */

void FUN_00023971(void)

{
  int unaff_EDI;
  undefined4 uVar1;
  float *pfVar2;
  undefined4 local_2c;
  float local_28;
  float local_24;
  float local_20 [4];

  FUN_00032e7a();
  FUN_000228cd();
  FUN_00023921();
  FUN_00023921();
  pfVar2 = local_20;
  uVar1 = 3;
  FUN_00023921();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,&UNK_0001756f + unaff_EDI,local_2c,(double)local_28,(double)local_24,
               (double)local_20[0],uVar1,pfVar2);
}



/* ================================================================
 * 00023a30  FUN_00023a30
 * bytes: 403  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.cx replaced with injection: get_pc_thunk_cx */

void FUN_00023a30(void)

{
  undefined4 uVar1;
  float *pfVar2;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20 [4];

  FUN_000228cd();
  FUN_000228cd();
  FUN_000228cd();
  FUN_000228cd();
  FUN_000228cd();
  FUN_00023921();
  FUN_00023921();
  FUN_00023921();
  FUN_00023921();
  FUN_00023921();
  FUN_00023921();
  FUN_00023921();
  FUN_00023921();
  pfVar2 = local_20;
  uVar1 = 0xd;
  FUN_00023921();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,
               "OnPlayerEditAttachedObject(%d, %d, %d, %d, %d, %f, %f, %f, %f, %f, %f, %f, %f, %f)",
               local_54,local_50,local_4c,local_48,local_44,(double)local_40,(double)local_3c,
               (double)local_38,(double)local_34,(double)local_30,(double)local_2c,(double)local_28,
               (double)local_24,(double)local_20[0],uVar1,pfVar2);
}



/* ================================================================
 * 00023c29  FUN_00023c29
 * bytes: 290  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_00023c29(undefined4 param_1)

{
  undefined1 local_41;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20 [4];

  FUN_000228cd(param_1,0,&local_40);
  FUN_000237e2(param_1,1,&local_41);
  FUN_000228cd(param_1,2,&local_3c);
  FUN_000228cd(param_1,3,&local_38);
  FUN_00023921(param_1,4,&local_34);
  FUN_00023921(param_1,5,&local_30);
  FUN_00023921(param_1,6,&local_2c);
  FUN_00023921(param_1,7,&local_28);
  FUN_00023921(param_1,8,&local_24);
  FUN_00023921(param_1,9,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerEditObject(%d, %d, %d, %d, %f, %f, %f, %f, %f, %f)",local_40,local_41,
               local_3c,local_38,(double)local_34,(double)local_30,(double)local_2c,(double)local_28
               ,(double)local_24,(double)local_20[0]);
}



/* ================================================================
 * 00023d9d  FUN_00023d9d
 * bytes: 150  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_00023d9d(undefined4 param_1)

{
  undefined4 local_30;
  undefined4 local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_30);
  FUN_000228cd(param_1,1,&local_2c);
  FUN_00023921(param_1,2,&local_28);
  FUN_000228cd(param_1,3,&local_24);
  FUN_000228cd(param_1,4,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerGiveDamage(%d, %d, %f, %d, %d)",local_30,local_2c,(double)local_28,
               local_24,local_20[0]);
}



/* ================================================================
 * 00023e63  FUN_00023e63
 * bytes: 150  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_00023e63(undefined4 param_1)

{
  undefined4 local_30;
  undefined4 local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_30);
  FUN_000228cd(param_1,1,&local_2c);
  FUN_00023921(param_1,2,&local_28);
  FUN_000228cd(param_1,3,&local_24);
  FUN_000228cd(param_1,4,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerGiveDamageActor(%d, %d, %f, %d, %d)",local_30,local_2c,(double)local_28,
               local_24,local_20[0]);
}



/* ================================================================
 * 00023f29  FUN_00023f29
 * bytes: 203  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_00023f29(undefined4 param_1)

{
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  float local_28;
  float local_24;
  float local_20 [4];

  FUN_000228cd(param_1,0,&local_38);
  FUN_000228cd(param_1,1,&local_34);
  FUN_000228cd(param_1,2,&local_30);
  FUN_000228cd(param_1,3,&local_2c);
  FUN_00023921(param_1,4,&local_28);
  FUN_00023921(param_1,5,&local_24);
  FUN_00023921(param_1,6,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerSelectObject(%d, %d, %d, %d, %f, %f, %f)",local_38,local_34,local_30,
               local_2c,(double)local_28,(double)local_24,(double)local_20[0]);
}



/* ================================================================
 * 00024031  FUN_00024031
 * bytes: 150  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_00024031(undefined4 param_1)

{
  undefined4 local_30;
  undefined4 local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_30);
  FUN_000228cd(param_1,1,&local_2c);
  FUN_00023921(param_1,2,&local_28);
  FUN_000228cd(param_1,3,&local_24);
  FUN_000228cd(param_1,4,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerTakeDamage(%d, %d, %f, %d, %d)",local_30,local_2c,(double)local_28,
               local_24,local_20[0]);
}



/* ================================================================
 * 000240f7  FUN_000240f7
 * bytes: 203  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_000240f7(undefined4 param_1)

{
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  float local_28;
  float local_24;
  float local_20 [4];

  FUN_000228cd(param_1,0,&local_38);
  FUN_000228cd(param_1,1,&local_34);
  FUN_000228cd(param_1,2,&local_30);
  FUN_000228cd(param_1,3,&local_2c);
  FUN_00023921(param_1,4,&local_28);
  FUN_00023921(param_1,5,&local_24);
  FUN_00023921(param_1,6,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnPlayerWeaponShot(%d, %d, %d, %d, %f, %f, %f)",local_38,local_34,local_30,
               local_2c,(double)local_28,(double)local_24,(double)local_20[0]);
}



/* ================================================================
 * 000241fc  FUN_000241fc
 * bytes: 267  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */

void FUN_000241fc(void)

{
  undefined4 uVar1;
  float *pfVar2;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20 [4];

  FUN_000228cd();
  FUN_000228cd();
  FUN_000228cd();
  FUN_00023921();
  FUN_00023921();
  FUN_00023921();
  FUN_00023921();
  FUN_00023921();
  pfVar2 = local_20;
  uVar1 = 8;
  FUN_00023921();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnUnoccupiedVehicleUpdate(%d, %d, %d, %f, %f, %f, %f, %f, %f)",local_40,local_3c,
               local_38,(double)local_34,(double)local_30,(double)local_2c,(double)local_28,
               (double)local_24,(double)local_20[0],uVar1,pfVar2);
}



/* ================================================================
 * 00024352  FUN_00024352
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00024352(void)

{
}



/* ================================================================
 * 0002440c  FUN_0002440c
 * bytes: 143  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0002440c(undefined4 param_1)

{
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_30);
  FUN_000228cd(param_1,1,&local_2c);
  FUN_000228cd(param_1,2,&local_28);
  FUN_000228cd(param_1,3,&local_24);
  FUN_00024352(param_1,4,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnDialogResponse(%d, %d, %d, %d, \"%s\")",local_30,local_2c,local_28,local_24,
               local_20[0]);
}



/* ================================================================
 * 000244d8  FUN_000244d8
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000244d8(void)

{
}



/* ================================================================
 * 0002456d  FUN_0002456d
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002456d(void)

{
}



/* ================================================================
 * 000245e8  FUN_000245e8
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000245e8(void)

{
}



/* ================================================================
 * 00024660  FUN_00024660
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00024660(void)

{
}



/* ================================================================
 * 000246c6  FUN_000246c6
 * bytes: 14  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000246c6(void)

{
}



/* ================================================================
 * 0002474d  FUN_0002474d
 * bytes: 96  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_0002474d(undefined4 param_1)

{
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20 [4];

  FUN_000228cd(param_1,0,&local_28);
  FUN_000228cd(param_1,1,&local_24);
  FUN_00024352(param_1,2,local_20);
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"OnHTTPResponse(%d, %d, \"%s\")",local_28,local_24,local_20[0]);
}



/* ================================================================
 * 000247cd  FUN_000247cd
 * bytes: 59  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

int FUN_000247cd(void)

{
  int iVar1;

  iVar1 = FUN_000202ad(&DAT_0004f42c,8,0x20);
  if (-1 < iVar1) {
    FUN_000203be(&DAT_0004f42c);
    iVar1 = 0;
  }
  return iVar1;
}



/* ================================================================
 * 00024808  FUN_00024808
 * bytes: 33  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00024808(void)

{
  FUN_00020364(&DAT_0004f42c);
  return;
}



/* ================================================================
 * 00024829  FUN_00024829
 * bytes: 308  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

undefined4 FUN_00024829(undefined4 param_1,char param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  char *extraout_ECX;
  int iVar4;
  undefined8 uVar5;
  undefined1 local_3c [4];
  undefined4 local_38;
  longlong local_34;
  undefined4 local_2c;
  int local_28;
  undefined4 local_24;
  char local_20;

  if (param_3 == 0) {
                    /* WARNING: Subroutine does not return */
    __assert_fail("callback != NULL",
                  "/home/yuri/projects/ssmp server plugin (linux)/src/sampgdk.cpp",0x972,
                  "int sampgdk_timer_set(int, bool, sampgdk_timer_callback, void*)");
  }
  local_3c[0] = 1;
  local_28 = param_3;
  local_2c = param_1;
  local_20 = param_2;
  local_24 = param_4;
  local_34 = FUN_00020bf5();
  local_38 = FUN_0002106b(param_3);
  iVar2 = DAT_0004f430;
  if (local_34 == 0) {
    return 0;
  }
  pcVar3 = extraout_ECX;
  iVar1 = 0;
  do {
    iVar4 = iVar1;
    if (iVar2 <= iVar4) {
      iVar2 = FUN_00020960(&DAT_0004f42c,local_3c,iVar2,iVar2);
      if (iVar2 < 0) {
        pcVar3 = strerror(-iVar2);
                    /* WARNING: Subroutine does not return */
        FUN_00020b5e(3,"Error setting timer: %s",pcVar3);
      }
      iVar4 = DAT_0004f430 + -1;
      goto LAB_0002492d;
    }
    uVar5 = FUN_000205cb(&DAT_0004f42c,iVar4,pcVar3,pcVar3);
    pcVar3 = (char *)uVar5;
    iVar1 = iVar4 + 1;
  } while (*pcVar3 != '\0');
  FUN_0002067d(&DAT_0004f42c,iVar4,local_3c,(int)((ulonglong)uVar5 >> 0x20));
LAB_0002492d:
  pcVar3 = "false";
  if (param_2 != '\0') {
    pcVar3 = "true";
  }
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"Created timer: ID = %d, interval = %d, repeat = %s",iVar4 + 1,param_1,pcVar3);
}



/* ================================================================
 * 00024963  FUN_00024963
 * bytes: 95  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

undefined4 __regparm2 FUN_00024963(undefined4 param_1,undefined4 param_2,int param_3)

{
  char *pcVar1;

  if ((0 < param_3) && (param_3 <= DAT_0004f430)) {
    pcVar1 = (char *)FUN_000205cb(&DAT_0004f42c,param_3 + -1,param_2,param_2);
    if (*pcVar1 != '\0') {
      *pcVar1 = '\0';
                    /* WARNING: Subroutine does not return */
      FUN_00020b5e(0,"Killed timer %d",param_3,0xffffffea);
    }
  }
  return 0xffffffea;
}



/* ================================================================
 * 000249c7  FUN_000249c7
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000249c7(void)

{
}



/* ================================================================
 * 00024b8b  FUN_00024b8b
 * bytes: 6  status: ok
 * ================================================================ */

undefined4 FUN_00024b8b(void)

{
  return 0x4060400;
}



/* ================================================================
 * 00024b91  FUN_00024b91
 * bytes: 17  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

char * FUN_00024b91(void)

{
  return "4.6.4";
}



/* ================================================================
 * 00024ba2  FUN_00024ba2
 * bytes: 6  status: ok
 * ================================================================ */

undefined4 FUN_00024ba2(void)

{
  return 0x200;
}



/* ================================================================
 * 00024ba8  FUN_00024ba8
 * bytes: 40  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00024ba8(void)

{
  FUN_0002106b(FUN_0002c3fd);
  FUN_000249c7();
  return;
}



/* ================================================================
 * 00024bd0  FUN_00024bd0
 * bytes: 23  status: ok
 * ================================================================ */

void FUN_00024bd0(undefined4 param_1)

{
  FUN_00020b0f(param_1,&stack0x00000008);
  return;
}



/* ================================================================
 * 00024be7  thunk_FUN_00020b0f
 * bytes: 5  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void thunk_FUN_00020b0f(void)

{
}



/* ================================================================
 * 00024bec  FUN_00024bec
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00024bec(void)

{
}



/* ================================================================
 * 00024ca2  thunk_FUN_0001ff02
 * bytes: 5  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void thunk_FUN_0001ff02(void)

{
}



/* ================================================================
 * 00024ca7  FUN_00024ca7
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00024ca7(void)

{
}



/* ================================================================
 * 00024d3a  FUN_00024d3a
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00024d3a(void)

{
}



/* ================================================================
 * 00024da1  FUN_00024da1
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00024da1(void)

{
}



/* ================================================================
 * 00024e11  FUN_00024e11
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00024e11(void)

{
}



/* ================================================================
 * 00024e81  FUN_00024e81
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00024e81(void)

{
}



/* ================================================================
 * 00024ee0  FUN_00024ee0
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00024ee0(void)

{
}



/* ================================================================
 * 00024fe5  FUN_00024fe5
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00024fe5(void)

{
}



/* ================================================================
 * 0002504c  FUN_0002504c
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002504c(void)

{
}



/* ================================================================
 * 000250da  FUN_000250da
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000250da(void)

{
}



/* ================================================================
 * 000251d9  FUN_000251d9
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000251d9(void)

{
}



/* ================================================================
 * 0002524d  FUN_0002524d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002524d(void)

{
}



/* ================================================================
 * 000252e6  FUN_000252e6
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000252e6(void)

{
}



/* ================================================================
 * 0002535a  FUN_0002535a
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002535a(void)

{
}



/* ================================================================
 * 000253f3  FUN_000253f3
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000253f3(void)

{
}



/* ================================================================
 * 00025464  FUN_00025464
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025464(void)

{
}



/* ================================================================
 * 000254cb  FUN_000254cb
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000254cb(void)

{
}



/* ================================================================
 * 00025532  FUN_00025532
 * bytes: 3  status: ok
 * ================================================================ */

undefined4 FUN_00025532(void)

{
  return 0;
}



/* ================================================================
 * 00025535  FUN_00025535
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_00025535(void)

{
  return;
}



/* ================================================================
 * 00025536  FUN_00025536
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025536(void)

{
}



/* ================================================================
 * 0002559d  FUN_0002559d
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002559d(void)

{
}



/* ================================================================
 * 00025629  FUN_00025629
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025629(void)

{
}



/* ================================================================
 * 000256e4  FUN_000256e4
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000256e4(void)

{
}



/* ================================================================
 * 0002574b  FUN_0002574b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002574b(void)

{
}



/* ================================================================
 * 000257bb  FUN_000257bb
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000257bb(void)

{
}



/* ================================================================
 * 000258ba  FUN_000258ba
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000258ba(void)

{
}



/* ================================================================
 * 00025948  FUN_00025948
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025948(void)

{
}



/* ================================================================
 * 000259e1  FUN_000259e1
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000259e1(void)

{
}



/* ================================================================
 * 00025b12  FUN_00025b12
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025b12(void)

{
}



/* ================================================================
 * 00025b86  FUN_00025b86
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025b86(void)

{
}



/* ================================================================
 * 00025c09  FUN_00025c09
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025c09(void)

{
}



/* ================================================================
 * 00025c5d  FUN_00025c5d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025c5d(void)

{
}



/* ================================================================
 * 00025d04  FUN_00025d04
 * bytes: 59  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_00025d04(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"GetVehicleParamsEx(%d, @%p, @%p, @%p, @%p, @%p, @%p, @%p)",param_1,param_2,param_3
               ,param_4,param_5,param_6,param_7,param_8);
}



/* ================================================================
 * 00025ecf  FUN_00025ecf
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025ecf(void)

{
}



/* ================================================================
 * 00025f2e  FUN_00025f2e
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025f2e(void)

{
}



/* ================================================================
 * 00025fba  FUN_00025fba
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00025fba(void)

{
}



/* ================================================================
 * 000260eb  FUN_000260eb
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000260eb(void)

{
}



/* ================================================================
 * 00026177  FUN_00026177
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026177(void)

{
}



/* ================================================================
 * 000262a8  FUN_000262a8
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000262a8(void)

{
}



/* ================================================================
 * 0002630f  FUN_0002630f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002630f(void)

{
}



/* ================================================================
 * 0002637f  FUN_0002637f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002637f(void)

{
}



/* ================================================================
 * 000263ef  FUN_000263ef
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000263ef(void)

{
}



/* ================================================================
 * 0002645f  FUN_0002645f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002645f(void)

{
}



/* ================================================================
 * 000264d9  FUN_000264d9
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000264d9(void)

{
}



/* ================================================================
 * 00026549  FUN_00026549
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026549(void)

{
}



/* ================================================================
 * 000265bd  FUN_000265bd
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000265bd(void)

{
}



/* ================================================================
 * 00026656  FUN_00026656
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026656(void)

{
}



/* ================================================================
 * 000266c6  FUN_000266c6
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000266c6(void)

{
}



/* ================================================================
 * 0002672d  FUN_0002672d
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002672d(void)

{
}



/* ================================================================
 * 00026794  FUN_00026794
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026794(void)

{
}



/* ================================================================
 * 000267f3  FUN_000267f3
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000267f3(void)

{
}



/* ================================================================
 * 00026883  FUN_00026883
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026883(void)

{
}



/* ================================================================
 * 000268e2  FUN_000268e2
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000268e2(void)

{
}



/* ================================================================
 * 0002694a  FUN_0002694a
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002694a(void)

{
}



/* ================================================================
 * 000269a9  FUN_000269a9
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000269a9(void)

{
}



/* ================================================================
 * 00026a10  FUN_00026a10
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026a10(void)

{
}



/* ================================================================
 * 00026b0f  FUN_00026b0f
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026b0f(void)

{
}



/* ================================================================
 * 00026b9d  FUN_00026b9d
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026b9d(void)

{
}



/* ================================================================
 * 00026c2b  FUN_00026c2b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026c2b(void)

{
}



/* ================================================================
 * 00026d5c  FUN_00026d5c
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026d5c(void)

{
}



/* ================================================================
 * 00026de8  FUN_00026de8
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026de8(void)

{
}



/* ================================================================
 * 00026e58  FUN_00026e58
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026e58(void)

{
}



/* ================================================================
 * 00026eb7  FUN_00026eb7
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026eb7(void)

{
}



/* ================================================================
 * 00026fbd  FUN_00026fbd
 * bytes: 3  status: ok
 * ================================================================ */

undefined4 FUN_00026fbd(void)

{
  return 0;
}



/* ================================================================
 * 00026fc0  FUN_00026fc0
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_00026fc0(void)

{
  return;
}



/* ================================================================
 * 00026fc1  FUN_00026fc1
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00026fc1(void)

{
}



/* ================================================================
 * 0002705b  FUN_0002705b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002705b(void)

{
}



/* ================================================================
 * 000270eb  FUN_000270eb
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000270eb(void)

{
}



/* ================================================================
 * 00027185  FUN_00027185
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027185(void)

{
}



/* ================================================================
 * 00027215  FUN_00027215
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027215(void)

{
}



/* ================================================================
 * 0002728f  FUN_0002728f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002728f(void)

{
}



/* ================================================================
 * 00027312  FUN_00027312
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027312(void)

{
}



/* ================================================================
 * 000273ac  FUN_000273ac
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000273ac(void)

{
}



/* ================================================================
 * 0002744f  FUN_0002744f
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002744f(void)

{
}



/* ================================================================
 * 0002749b  FUN_0002749b
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002749b(void)

{
}



/* ================================================================
 * 000274e7  FUN_000274e7
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000274e7(void)

{
}



/* ================================================================
 * 00027569  FUN_00027569
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027569(void)

{
}



/* ================================================================
 * 000275b5  FUN_000275b5
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000275b5(void)

{
}



/* ================================================================
 * 00027601  FUN_00027601
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027601(void)

{
}



/* ================================================================
 * 0002764d  FUN_0002764d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002764d(void)

{
}



/* ================================================================
 * 0002773c  FUN_0002773c
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002773c(void)

{
}



/* ================================================================
 * 000277cc  FUN_000277cc
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000277cc(void)

{
}



/* ================================================================
 * 0002784f  FUN_0002784f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002784f(void)

{
}



/* ================================================================
 * 000278f9  FUN_000278f9
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000278f9(void)

{
}



/* ================================================================
 * 000279c3  FUN_000279c3
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000279c3(void)

{
}



/* ================================================================
 * 00027a57  FUN_00027a57
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027a57(void)

{
}



/* ================================================================
 * 00027adc  FUN_00027adc
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027adc(void)

{
}



/* ================================================================
 * 00027b63  FUN_00027b63
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027b63(void)

{
}



/* ================================================================
 * 00027baf  FUN_00027baf
 * bytes: 45  status: ok
 * ================================================================ */

void FUN_00027baf(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"_ZTISt23_Sp_counted_ptr_inplaceINSt13__future_base17_Async_state_implINSt6thread8_InvokerISt5tupleIJZN13BufferHandles7ProcessEvEUlvE0_EEEEvEESaIvELN9__gnu_cxx12_Lock_policyE2EE"
                 + unaff_EDI + 0xa5,param_1,param_2,param_3);
}



/* ================================================================
 * 00027c55  FUN_00027c55
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027c55(void)

{
}



/* ================================================================
 * 00027cd8  FUN_00027cd8
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027cd8(void)

{
                    /* catch() { ... } // from try @ 00027d57 with catch @ 00027cd8
                       catch() { ... } // from try @ 00027dcf with catch @ 00027cd8 */
}



/* ================================================================
 * 00027d5f  FUN_00027d5f
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027d5f(void)

{
}



/* ================================================================
 * 00027dc6  FUN_00027dc6
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027dc6(void)

{
}



/* ================================================================
 * 00027e92  FUN_00027e92
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027e92(void)

{
}



/* ================================================================
 * 00027f67  FUN_00027f67
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00027f67(void)

{
}



/* ================================================================
 * 0002800f  FUN_0002800f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002800f(void)

{
}



/* ================================================================
 * 000280ca  FUN_000280ca
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000280ca(void)

{
}



/* ================================================================
 * 00028165  FUN_00028165
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028165(void)

{
}



/* ================================================================
 * 00028200  FUN_00028200
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028200(void)

{
}



/* ================================================================
 * 00028267  FUN_00028267
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028267(void)

{
}



/* ================================================================
 * 000282cf  FUN_000282cf
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000282cf(void)

{
}



/* ================================================================
 * 00028336  FUN_00028336
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028336(void)

{
}



/* ================================================================
 * 0002838a  FUN_0002838a
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002838a(void)

{
}



/* ================================================================
 * 000283f1  FUN_000283f1
 * bytes: 45  status: ok
 * ================================================================ */

void FUN_000283f1(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"_ZTSSt11_Mutex_baseILN9__gnu_cxx12_Lock_policyE2EE" + unaff_EDI + 0x2d,param_1,
               param_2,param_3);
}



/* ================================================================
 * 00028497  FUN_00028497
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028497(void)

{
}



/* ================================================================
 * 000284ff  FUN_000284ff
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000284ff(void)

{
}



/* ================================================================
 * 00028553  FUN_00028553
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028553(void)

{
}



/* ================================================================
 * 000285bb  FUN_000285bb
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000285bb(void)

{
}



/* ================================================================
 * 00028622  FUN_00028622
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028622(void)

{
}



/* ================================================================
 * 0002868b  FUN_0002868b
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002868b(void)

{
}



/* ================================================================
 * 000286dd  FUN_000286dd
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000286dd(void)

{
}



/* ================================================================
 * 00028745  FUN_00028745
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028745(void)

{
}



/* ================================================================
 * 000287ac  FUN_000287ac
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000287ac(void)

{
}



/* ================================================================
 * 00028849  FUN_00028849
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028849(void)

{
}



/* ================================================================
 * 000288b1  FUN_000288b1
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000288b1(void)

{
}



/* ================================================================
 * 00028905  FUN_00028905
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028905(void)

{
}



/* ================================================================
 * 00028959  FUN_00028959
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028959(void)

{
}



/* ================================================================
 * 000289c2  FUN_000289c2
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000289c2(void)

{
}



/* ================================================================
 * 00028a16  FUN_00028a16
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028a16(void)

{
}



/* ================================================================
 * 00028a7f  FUN_00028a7f
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028a7f(void)

{
}



/* ================================================================
 * 00028ae8  FUN_00028ae8
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028ae8(void)

{
}



/* ================================================================
 * 00028b92  FUN_00028b92
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028b92(void)

{
}



/* ================================================================
 * 00028bf9  FUN_00028bf9
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028bf9(void)

{
}



/* ================================================================
 * 00028c60  FUN_00028c60
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028c60(void)

{
}



/* ================================================================
 * 00028cc7  FUN_00028cc7
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028cc7(void)

{
}



/* ================================================================
 * 00028d2e  FUN_00028d2e
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028d2e(void)

{
}



/* ================================================================
 * 00028dbe  FUN_00028dbe
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028dbe(void)

{
}



/* ================================================================
 * 00028e45  FUN_00028e45
 * bytes: 45  status: ok
 * ================================================================ */

void FUN_00028e45(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"_ZTVSt23_Sp_counted_ptr_inplaceINSt13__future_base15_Deferred_stateINSt6thread8_InvokerISt5tupleIJZN13BufferHandles7ProcessEvEUlvE0_EEEEvEESaIvELN9__gnu_cxx12_Lock_policyE2EE"
                 + unaff_EDI + 0x31,param_1,param_2,param_3);
}



/* ================================================================
 * 00028eeb  FUN_00028eeb
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00028eeb(void)

{
}



/* ================================================================
 * 00028f89  FUN_00028f89
 * bytes: 45  status: ok
 * ================================================================ */

void FUN_00028f89(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE11_M_is_localEv" +
                 unaff_EDI + 9,param_1,param_2,param_3);
}



/* ================================================================
 * 0002902f  FUN_0002902f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002902f(void)

{
}



/* ================================================================
 * 000290bf  FUN_000290bf
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000290bf(void)

{
}



/* ================================================================
 * 00029146  FUN_00029146
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029146(void)

{
}



/* ================================================================
 * 00029210  FUN_00029210
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029210(void)

{
}



/* ================================================================
 * 00029293  FUN_00029293
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029293(void)

{
}



/* ================================================================
 * 0002931a  FUN_0002931a
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002931a(void)

{
}



/* ================================================================
 * 000293e4  FUN_000293e4
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000293e4(void)

{
}



/* ================================================================
 * 00029467  FUN_00029467
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029467(void)

{
}



/* ================================================================
 * 000294ee  FUN_000294ee
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000294ee(void)

{
}



/* ================================================================
 * 0002953a  FUN_0002953a
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002953a(void)

{
}



/* ================================================================
 * 00029599  FUN_00029599
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029599(void)

{
}



/* ================================================================
 * 000295f8  FUN_000295f8
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000295f8(void)

{
}



/* ================================================================
 * 00029657  FUN_00029657
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029657(void)

{
}



/* ================================================================
 * 000296b6  FUN_000296b6
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000296b6(void)

{
}



/* ================================================================
 * 00029715  FUN_00029715
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029715(void)

{
}



/* ================================================================
 * 00029774  FUN_00029774
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029774(void)

{
}



/* ================================================================
 * 000297d9  FUN_000297d9
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000297d9(void)

{
}



/* ================================================================
 * 00029838  FUN_00029838
 * bytes: 45  status: ok
 * ================================================================ */

void FUN_00029838(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* try { // try from 00029859 to 00039877 has its CatchHandler @ 00029912 */
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"_ZTVNSt13__future_base17_Async_state_implINSt6thread8_InvokerISt5tupleIJZN13BufferHandles7ProcessEvEUlvE0_EEEEvEE"
                 + unaff_EDI + 0x28,param_1,param_2,param_3);
}



/* ================================================================
 * 000298de  FUN_000298de
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000298de(void)

{
}



/* ================================================================
 * 0002999e  FUN_0002999e
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002999e(void)

{
}



/* ================================================================
 * 00029a05  FUN_00029a05
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029a05(void)

{
}



/* ================================================================
 * 00029a9b  FUN_00029a9b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029a9b(void)

{
}



/* ================================================================
 * 00029b35  FUN_00029b35
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029b35(void)

{
}



/* ================================================================
 * 00029ba5  FUN_00029ba5
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029ba5(void)

{
}



/* ================================================================
 * 00029c15  FUN_00029c15
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029c15(void)

{
}



/* ================================================================
 * 00029c7c  FUN_00029c7c
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029c7c(void)

{
}



/* ================================================================
 * 00029ce3  FUN_00029ce3
 * bytes: 6  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029ce3(void)

{
                    /* try { // try from 00029ce4 to 00039ce8 has its CatchHandler @ 00029d1e */
}



/* ================================================================
 * 00029d53  FUN_00029d53
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029d53(void)

{
}



/* ================================================================
 * 00029db2  FUN_00029db2
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029db2(void)

{
}



/* ================================================================
 * 00029e52  FUN_00029e52
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029e52(void)

{
}



/* ================================================================
 * 00029eb9  FUN_00029eb9
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029eb9(void)

{
}



/* ================================================================
 * 00029f3a  FUN_00029f3a
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029f3a(void)

{
}



/* ================================================================
 * 00029fbb  FUN_00029fbb
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00029fbb(void)

{
}



/* ================================================================
 * 0002a02b  FUN_0002a02b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a02b(void)

{
}



/* ================================================================
 * 0002a09b  FUN_0002a09b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a09b(void)

{
}



/* ================================================================
 * 0002a10c  FUN_0002a10c
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a10c(void)

{
}



/* ================================================================
 * 0002a17c  FUN_0002a17c
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a17c(void)

{
}



/* ================================================================
 * 0002a1ec  FUN_0002a1ec
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a1ec(void)

{
}



/* ================================================================
 * 0002a25c  FUN_0002a25c
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a25c(void)

{
}



/* ================================================================
 * 0002a2cc  FUN_0002a2cc
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a2cc(void)

{
}



/* ================================================================
 * 0002a33c  FUN_0002a33c
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a33c(void)

{
}



/* ================================================================
 * 0002a3ad  FUN_0002a3ad
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a3ad(void)

{
                    /* catch() { ... } // from try @ 0002a39c with catch @ 0002a3b1 */
}



/* ================================================================
 * 0002a41e  FUN_0002a41e
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a41e(void)

{
}



/* ================================================================
 * 0002a48e  FUN_0002a48e
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a48e(void)

{
}



/* ================================================================
 * 0002a4fe  FUN_0002a4fe
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a4fe(void)

{
}



/* ================================================================
 * 0002a565  FUN_0002a565
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a565(void)

{
}



/* ================================================================
 * 0002a5cc  FUN_0002a5cc
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a5cc(void)

{
}



/* ================================================================
 * 0002a65c  FUN_0002a65c
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a65c(void)

{
}



/* ================================================================
 * 0002a6cc  FUN_0002a6cc
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a6cc(void)

{
}



/* ================================================================
 * 0002a767  FUN_0002a767
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a767(void)

{
}



/* ================================================================
 * 0002a7e1  FUN_0002a7e1
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a7e1(void)

{
}



/* ================================================================
 * 0002a851  FUN_0002a851
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a851(void)

{
}



/* ================================================================
 * 0002a8b8  FUN_0002a8b8
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a8b8(void)

{
}



/* ================================================================
 * 0002a941  FUN_0002a941
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a941(void)

{
                    /* try { // try from 0002a946 to 0003a94a has its CatchHandler @ 0002a9ac */
}



/* ================================================================
 * 0002a9a8  FUN_0002a9a8
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002a9a8(void)

{
                    /* catch() { ... } // from try @ 0002a946 with catch @ 0002a9ac */
}



/* ================================================================
 * 0002aa22  FUN_0002aa22
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002aa22(void)

{
}



/* ================================================================
 * 0002aa92  FUN_0002aa92
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002aa92(void)

{
}



/* ================================================================
 * 0002ab02  FUN_0002ab02
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ab02(void)

{
}



/* ================================================================
 * 0002ab69  FUN_0002ab69
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ab69(void)

{
}



/* ================================================================
 * 0002abe3  FUN_0002abe3
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002abe3(void)

{
}



/* ================================================================
 * 0002ac53  FUN_0002ac53
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ac53(void)

{
}



/* ================================================================
 * 0002acc3  FUN_0002acc3
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002acc3(void)

{
}



/* ================================================================
 * 0002ad2a  FUN_0002ad2a
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ad2a(void)

{
}



/* ================================================================
 * 0002ae00  FUN_0002ae00
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ae00(void)

{
}



/* ================================================================
 * 0002ae67  FUN_0002ae67
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ae67(void)

{
}



/* ================================================================
 * 0002aefe  FUN_0002aefe
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002aefe(void)

{
}



/* ================================================================
 * 0002af95  FUN_0002af95
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002af95(void)

{
}



/* ================================================================
 * 0002b02f  FUN_0002b02f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002b02f(void)

{
}



/* ================================================================
 * 0002b116  FUN_0002b116
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002b116(void)

{
}



/* ================================================================
 * 0002b186  FUN_0002b186
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002b186(void)

{
}



/* ================================================================
 * 0002b229  FUN_0002b229
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002b229(void)

{
}



/* ================================================================
 * 0002b343  FUN_0002b343
 * bytes: 45  status: ok
 * ================================================================ */

void FUN_0002b343(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int unaff_EDI;

                    /* try { // try from 0002b346 to 0003b34a has its CatchHandler @ 0002b34b */
                    /* catch() { ... } // from try @ 0002b346 with catch @ 0002b34b */
  FUN_00032e7a();
                    /* catch() { ... } // from try @ 0002b279 with catch @ 0002b357 */
                    /* WARNING: Subroutine does not return */
                    /* try { // try from 0002b36e to 0003b372 has its CatchHandler @ 0002b171 */
  FUN_00020b5e(0,"_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJMNSt13__future_base17_Async_state_implINS1_IS2_IJZN13BufferHandles7ProcessEvEUlvE0_EEEEvEEFvvEPS9_EEEEED2Ev"
                 + unaff_EDI + 0x87,param_1,param_2,param_3);
}



/* ================================================================
 * 0002b3e9  FUN_0002b3e9
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002b3e9(void)

{
}



/* ================================================================
 * 0002b4a2  FUN_0002b4a2
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002b4a2(void)

{
}



/* ================================================================
 * 0002b564  FUN_0002b564
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002b564(void)

{
}



/* ================================================================
 * 0002b638  FUN_0002b638
 * bytes: 45  status: ok
 * ================================================================ */

void FUN_0002b638(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"_ZNSt23_Sp_counted_ptr_inplaceINSt13__future_base15_Deferred_stateINSt6thread8_InvokerISt5tupleIJZN13BufferHandles7ProcessEvEUlvE0_EEEEvEESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev"
                 + unaff_EDI + 6,param_1,param_2,param_3);
}



/* ================================================================
 * 0002b6de  FUN_0002b6de
 * bytes: 45  status: ok
 * ================================================================ */

void FUN_0002b6de(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"_ZNSt23_Sp_counted_ptr_inplaceINSt13__future_base17_Async_state_implINSt6thread8_InvokerISt5tupleIJZN13BufferHandles7ProcessEvEUlvE0_EEEEvEESaIvELN9__gnu_cxx12_Lock_policyE2EED0Ev"
                 + unaff_EDI + 0x53,param_1,param_2,param_3);
}



/* ================================================================
 * 0002b784  FUN_0002b784
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002b784(void)

{
}



/* ================================================================
 * 0002b814  FUN_0002b814
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002b814(void)

{
}



/* ================================================================
 * 0002bf38  FUN_0002bf38
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002bf38(void)

{
}



/* ================================================================
 * 0002c26e  FUN_0002c26e
 * bytes: 16  status: ok
 * ================================================================ */

void FUN_0002c26e(void)

{
  FUN_00024829();
  return;
}



/* ================================================================
 * 0002c27e  FUN_0002c27e
 * bytes: 21  status: ok
 * ================================================================ */

uint FUN_0002c27e(undefined4 param_1)

{
  uint uVar1;

  uVar1 = FUN_00024963(param_1);
  return ~uVar1 >> 0x1f;
}



/* ================================================================
 * 0002c293  FUN_0002c293
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002c293(void)

{
}



/* ================================================================
 * 0002c379  FUN_0002c379
 * bytes: 44  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

int FUN_0002c379(void)

{
  int iVar1;

  iVar1 = FUN_00021599("OnHTTPResponse",FUN_0002474d);
  if (0 < iVar1) {
    iVar1 = 0;
  }
  return iVar1;
}



/* ================================================================
 * 0002c3a5  FUN_0002c3a5
 * bytes: 88  status: ok
 * ================================================================ */

int FUN_0002c3a5(void)

{
  int iVar1;

  iVar1 = FUN_00024bec();
  if (-1 < iVar1) {
    iVar1 = FUN_000216a7();
    if (-1 < iVar1) {
      iVar1 = FUN_0002188c();
      if (-1 < iVar1) {
        FUN_0001ff5f();
        iVar1 = FUN_000210ce();
        if (-1 < iVar1) {
          iVar1 = FUN_00020ec6();
          if (-1 < iVar1) {
            iVar1 = FUN_000247cd();
            if (-1 < iVar1) {
              iVar1 = FUN_0002c379();
              if (-1 < iVar1) {
                iVar1 = FUN_0002b814();
                if (0 < iVar1) {
                  iVar1 = 0;
                }
              }
            }
          }
        }
      }
    }
  }
  return iVar1;
}



/* ================================================================
 * 0002c3fd  FUN_0002c3fd
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002c3fd(void)

{
}



/* ================================================================
 * 0002c462  FUN_0002c462
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002c462(void)

{
}



/* ================================================================
 * 0002c50c  FUN_0002c50c
 * bytes: 33  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0002c50c(void)

{
  FUN_0002180d("OnHTTPResponse");
  return;
}



/* ================================================================
 * 0002c52d  FUN_0002c52d
 * bytes: 47  status: ok
 * ================================================================ */

void FUN_0002c52d(void)

{
  FUN_0002bf38();
  FUN_0002c50c();
  FUN_00024808();
  FUN_00020ee8();
  FUN_00021115();
                    /* try { // try from 0002c54b to 0003c5d5 has its CatchHandler @ 0002c62e */
  FUN_00021941();
  FUN_00021540();
  FUN_0001ff02();
  return;
}



/* ================================================================
 * 0002c55c  FUN_0002c55c
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002c55c(void)

{
}



/* ================================================================
 * 0002c5f3  FUN_0002c5f3
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002c5f3(void)

{
}



/* ================================================================
 * 0002c6ad  FUN_0002c6ad
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002c6ad(void)

{
}



/* ================================================================
 * 0002c76b  FUN_0002c76b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002c76b(void)

{
}



/* ================================================================
 * 0002c836  FUN_0002c836
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002c836(void)

{
}



/* ================================================================
 * 0002c8f4  FUN_0002c8f4
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002c8f4(void)

{
}



/* ================================================================
 * 0002c982  FUN_0002c982
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002c982(void)

{
}



/* ================================================================
 * 0002ca81  FUN_0002ca81
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ca81(void)

{
}



/* ================================================================
 * 0002cb0f  FUN_0002cb0f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002cb0f(void)

{
}



/* ================================================================
 * 0002cc0e  FUN_0002cc0e
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002cc0e(void)

{
}



/* ================================================================
 * 0002cc6d  FUN_0002cc6d
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002cc6d(void)

{
}



/* ================================================================
 * 0002ccd4  FUN_0002ccd4
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ccd4(void)

{
}



/* ================================================================
 * 0002cd3b  FUN_0002cd3b
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002cd3b(void)

{
}



/* ================================================================
 * 0002cda2  FUN_0002cda2
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002cda2(void)

{
}



/* ================================================================
 * 0002ce5c  FUN_0002ce5c
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ce5c(void)

{
}



/* ================================================================
 * 0002cec3  FUN_0002cec3
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002cec3(void)

{
}



/* ================================================================
 * 0002cf2a  FUN_0002cf2a
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002cf2a(void)

{
}



/* ================================================================
 * 0002cf9a  FUN_0002cf9a
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002cf9a(void)

{
}



/* ================================================================
 * 0002d00a  FUN_0002d00a
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d00a(void)

{
}



/* ================================================================
 * 0002d071  FUN_0002d071
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d071(void)

{
}



/* ================================================================
 * 0002d0d8  FUN_0002d0d8
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d0d8(void)

{
}



/* ================================================================
 * 0002d19b  FUN_0002d19b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d19b(void)

{
}



/* ================================================================
 * 0002d262  FUN_0002d262
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d262(void)

{
}



/* ================================================================
 * 0002d329  FUN_0002d329
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d329(void)

{
}



/* ================================================================
 * 0002d3c0  FUN_0002d3c0
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d3c0(void)

{
}



/* ================================================================
 * 0002d4c6  FUN_0002d4c6
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d4c6(void)

{
}



/* ================================================================
 * 0002d55d  FUN_0002d55d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d55d(void)

{
}



/* ================================================================
 * 0002d663  FUN_0002d663
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d663(void)

{
                    /* try { // try from 0002d669 to 0003d763 has its CatchHandler @ 0002d87b */
}



/* ================================================================
 * 0002d6cb  FUN_0002d6cb
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d6cb(void)

{
}



/* ================================================================
 * 0002d73b  FUN_0002d73b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d73b(void)

{
}



/* ================================================================
 * 0002d7ab  FUN_0002d7ab
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d7ab(void)

{
}



/* ================================================================
 * 0002d81b  FUN_0002d81b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d81b(void)

{
}



/* ================================================================
 * 0002d8de  FUN_0002d8de
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d8de(void)

{
}



/* ================================================================
 * 0002d94e  FUN_0002d94e
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d94e(void)

{
}



/* ================================================================
 * 0002d9be  FUN_0002d9be
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002d9be(void)

{
}



/* ================================================================
 * 0002da8d  FUN_0002da8d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002da8d(void)

{
}



/* ================================================================
 * 0002db65  FUN_0002db65
 * bytes: 71  status: ok
 * ================================================================ */

void FUN_0002db65(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined1 param_7,undefined4 param_8,
                 undefined4 param_9,undefined4 param_10)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x10883,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
               ,param_9,param_10);
}



/* ================================================================
 * 0002dc5c  FUN_0002dc5c
 * bytes: 74  status: ok
 * ================================================================ */

void FUN_0002dc5c(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined1 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0x107e4,param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
               ,param_9,param_10,param_11);
}



/* ================================================================
 * 0002dd5c  FUN_0002dd5c
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002dd5c(void)

{
}



/* ================================================================
 * 0002ddc4  FUN_0002ddc4
 * bytes: 3  status: ok
 * ================================================================ */

undefined4 FUN_0002ddc4(void)

{
  return 0;
}



/* ================================================================
 * 0002ddc7  FUN_0002ddc7
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_0002ddc7(void)

{
  return;
}



/* ================================================================
 * 0002ddc8  FUN_0002ddc8
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ddc8(void)

{
}



/* ================================================================
 * 0002deae  FUN_0002deae
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002deae(void)

{
}



/* ================================================================
 * 0002df15  FUN_0002df15
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002df15(void)

{
}



/* ================================================================
 * 0002dfa3  FUN_0002dfa3
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002dfa3(void)

{
}



/* ================================================================
 * 0002e031  FUN_0002e031
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e031(void)

{
}



/* ================================================================
 * 0002e130  FUN_0002e130
 * bytes: 5  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e130(void)

{
}



/* ================================================================
 * 0002e1a4  FUN_0002e1a4
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e1a4(void)

{
}



/* ================================================================
 * 0002e23d  FUN_0002e23d
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e23d(void)

{
}



/* ================================================================
 * 0002e2d8  FUN_0002e2d8
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e2d8(void)

{
}



/* ================================================================
 * 0002e364  FUN_0002e364
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e364(void)

{
}



/* ================================================================
 * 0002e3d4  FUN_0002e3d4
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e3d4(void)

{
}



/* ================================================================
 * 0002e444  FUN_0002e444
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e444(void)

{
}



/* ================================================================
 * 0002e4a3  FUN_0002e4a3
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e4a3(void)

{
}



/* ================================================================
 * 0002e517  FUN_0002e517
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e517(void)

{
}



/* ================================================================
 * 0002e5b0  FUN_0002e5b0
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e5b0(void)

{
}



/* ================================================================
 * 0002e624  FUN_0002e624
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e624(void)

{
}



/* ================================================================
 * 0002e6bd  FUN_0002e6bd
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e6bd(void)

{
}



/* ================================================================
 * 0002e737  FUN_0002e737
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e737(void)

{
}



/* ================================================================
 * 0002e796  FUN_0002e796
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e796(void)

{
}



/* ================================================================
 * 0002e7f5  FUN_0002e7f5
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e7f5(void)

{
}



/* ================================================================
 * 0002e854  FUN_0002e854
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e854(void)

{
}



/* ================================================================
 * 0002e8b3  FUN_0002e8b3
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e8b3(void)

{
}



/* ================================================================
 * 0002e923  FUN_0002e923
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e923(void)

{
}



/* ================================================================
 * 0002e982  FUN_0002e982
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e982(void)

{
}



/* ================================================================
 * 0002e9f2  FUN_0002e9f2
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002e9f2(void)

{
}



/* ================================================================
 * 0002ea51  FUN_0002ea51
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ea51(void)

{
}



/* ================================================================
 * 0002eab0  FUN_0002eab0
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002eab0(void)

{
}



/* ================================================================
 * 0002eb20  FUN_0002eb20
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002eb20(void)

{
}



/* ================================================================
 * 0002eb90  FUN_0002eb90
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002eb90(void)

{
}



/* ================================================================
 * 0002ebef  FUN_0002ebef
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ebef(void)

{
}



/* ================================================================
 * 0002ec5f  FUN_0002ec5f
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ec5f(void)

{
}



/* ================================================================
 * 0002ecbe  FUN_0002ecbe
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ecbe(void)

{
}



/* ================================================================
 * 0002ed38  FUN_0002ed38
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ed38(void)

{
}



/* ================================================================
 * 0002ed9f  FUN_0002ed9f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ed9f(void)

{
}



/* ================================================================
 * 0002ee0f  FUN_0002ee0f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ee0f(void)

{
}



/* ================================================================
 * 0002eee0  FUN_0002eee0
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002eee0(void)

{
}



/* ================================================================
 * 0002ef50  FUN_0002ef50
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ef50(void)

{
}



/* ================================================================
 * 0002efb7  FUN_0002efb7
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002efb7(void)

{
}



/* ================================================================
 * 0002f043  FUN_0002f043
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f043(void)

{
}



/* ================================================================
 * 0002f0a2  FUN_0002f0a2
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f0a2(void)

{
}



/* ================================================================
 * 0002f101  FUN_0002f101
 * bytes: 9  status: ok
 * ================================================================ */

void FUN_0002f101(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0xfaab,param_1,param_2,param_3);
}



/* ================================================================
 * 0002f1a7  FUN_0002f1a7
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f1a7(void)

{
}



/* ================================================================
 * 0002f206  FUN_0002f206
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f206(void)

{
}



/* ================================================================
 * 0002f265  FUN_0002f265
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f265(void)

{
}



/* ================================================================
 * 0002f364  FUN_0002f364
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f364(void)

{
}



/* ================================================================
 * 0002f406  FUN_0002f406
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f406(void)

{
}



/* ================================================================
 * 0002f480  FUN_0002f480
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f480(void)

{
}



/* ================================================================
 * 0002f54a  FUN_0002f54a
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f54a(void)

{
}



/* ================================================================
 * 0002f5bb  FUN_0002f5bb
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f5bb(void)

{
}



/* ================================================================
 * 0002f62b  FUN_0002f62b
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f62b(void)

{
}



/* ================================================================
 * 0002f692  FUN_0002f692
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f692(void)

{
}



/* ================================================================
 * 0002f702  FUN_0002f702
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f702(void)

{
}



/* ================================================================
 * 0002f761  FUN_0002f761
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f761(void)

{
}



/* ================================================================
 * 0002f7d1  FUN_0002f7d1
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f7d1(void)

{
}



/* ================================================================
 * 0002f830  FUN_0002f830
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f830(void)

{
}



/* ================================================================
 * 0002f8be  FUN_0002f8be
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f8be(void)

{
}



/* ================================================================
 * 0002f9bd  FUN_0002f9bd
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002f9bd(void)

{
}



/* ================================================================
 * 0002fa37  FUN_0002fa37
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002fa37(void)

{
                    /* try { // try from 0002fa3a to 0003fa3e has its CatchHandler @ 0002fafa */
}



/* ================================================================
 * 0002fb07  FUN_0002fb07
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002fb07(void)

{
}



/* ================================================================
 * 0002fb6e  FUN_0002fb6e
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002fb6e(void)

{
}



/* ================================================================
 * 0002fbfe  FUN_0002fbfe
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002fbfe(void)

{
}



/* ================================================================
 * 0002fc78  FUN_0002fc78
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002fc78(void)

{
}



/* ================================================================
 * 0002fcd7  FUN_0002fcd7
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002fcd7(void)

{
}



/* ================================================================
 * 0002fd36  FUN_0002fd36
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002fd36(void)

{
}



/* ================================================================
 * 0002fdda  FUN_0002fdda
 * bytes: 56  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_0002fdda(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7)

{
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"GetPlayerLastShotVectors(%d, @%p, @%p, @%p, @%p, @%p, @%p)",param_1,param_2,
               param_3,param_4,param_5,param_6,param_7);
}



/* ================================================================
 * 0002ff73  FUN_0002ff73
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0002ff73(void)

{
}



/* ================================================================
 * 0003007f  FUN_0003007f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003007f(void)

{
}



/* ================================================================
 * 000300ef  FUN_000300ef
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000300ef(void)

{
}



/* ================================================================
 * 0003015f  FUN_0003015f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003015f(void)

{
}



/* ================================================================
 * 000301cf  FUN_000301cf
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000301cf(void)

{
}



/* ================================================================
 * 00030278  FUN_00030278
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030278(void)

{
}



/* ================================================================
 * 000302e8  FUN_000302e8
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000302e8(void)

{
}



/* ================================================================
 * 00030372  FUN_00030372
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030372(void)

{
}



/* ================================================================
 * 000303fc  FUN_000303fc
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000303fc(void)

{
}



/* ================================================================
 * 00030476  FUN_00030476
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030476(void)

{
}



/* ================================================================
 * 000304f0  FUN_000304f0
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000304f0(void)

{
}



/* ================================================================
 * 0003056b  FUN_0003056b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003056b(void)

{
}



/* ================================================================
 * 000305e5  FUN_000305e5
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000305e5(void)

{
}



/* ================================================================
 * 0003065f  FUN_0003065f
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003065f(void)

{
}



/* ================================================================
 * 000306d9  FUN_000306d9
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000306d9(void)

{
}



/* ================================================================
 * 00030753  FUN_00030753
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030753(void)

{
}



/* ================================================================
 * 000307cd  FUN_000307cd
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000307cd(void)

{
}



/* ================================================================
 * 00030848  FUN_00030848
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030848(void)

{
}



/* ================================================================
 * 000308c3  FUN_000308c3
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000308c3(void)

{
}



/* ================================================================
 * 00030933  FUN_00030933
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030933(void)

{
}



/* ================================================================
 * 000309a3  FUN_000309a3
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000309a3(void)

{
}



/* ================================================================
 * 00030a3d  FUN_00030a3d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030a3d(void)

{
}



/* ================================================================
 * 00030ab7  FUN_00030ab7
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030ab7(void)

{
}



/* ================================================================
 * 00030b5b  FUN_00030b5b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030b5b(void)

{
}



/* ================================================================
 * 00030bde  FUN_00030bde
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030bde(void)

{
}



/* ================================================================
 * 00030c78  FUN_00030c78
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030c78(void)

{
}



/* ================================================================
 * 00030d04  FUN_00030d04
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030d04(void)

{
}



/* ================================================================
 * 00030db8  FUN_00030db8
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030db8(void)

{
}



/* ================================================================
 * 00030e8b  FUN_00030e8b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030e8b(void)

{
}



/* ================================================================
 * 00030f28  FUN_00030f28
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030f28(void)

{
}



/* ================================================================
 * 00030fb6  FUN_00030fb6
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00030fb6(void)

{
}



/* ================================================================
 * 00031046  FUN_00031046
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031046(void)

{
}



/* ================================================================
 * 000310a5  FUN_000310a5
 * bytes: 48  status: ok
 * ================================================================ */

void FUN_000310a5(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int unaff_EDI;

  FUN_00032e7a();
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,unaff_EDI + 0xe70f,param_1,param_2,param_3,param_4);
}



/* ================================================================
 * 00031154  FUN_00031154
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031154(void)

{
}



/* ================================================================
 * 000311e0  FUN_000311e0
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000311e0(void)

{
}



/* ================================================================
 * 00031291  FUN_00031291
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031291(void)

{
}



/* ================================================================
 * 0003130b  FUN_0003130b
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003130b(void)

{
}



/* ================================================================
 * 0003136a  FUN_0003136a
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003136a(void)

{
}



/* ================================================================
 * 000313c9  FUN_000313c9
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000313c9(void)

{
}



/* ================================================================
 * 00031430  FUN_00031430
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031430(void)

{
}



/* ================================================================
 * 000314a1  FUN_000314a1
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000314a1(void)

{
}



/* ================================================================
 * 00031538  FUN_00031538
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031538(void)

{
}



/* ================================================================
 * 0003164d  FUN_0003164d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003164d(void)

{
}



/* ================================================================
 * 000316be  FUN_000316be
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000316be(void)

{
}



/* ================================================================
 * 0003171d  FUN_0003171d
 * bytes: 50  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_0003171d(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5)

{
                    /* WARNING: Subroutine does not return */
  FUN_00020b5e(0,"GetAnimationName(%d, @%p, %d, @%p, %d)",param_1,param_2,param_3,param_4,param_5);
}



/* ================================================================
 * 00031805  FUN_00031805
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031805(void)

{
}



/* ================================================================
 * 00031864  FUN_00031864
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031864(void)

{
}



/* ================================================================
 * 000318d4  FUN_000318d4
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000318d4(void)

{
}



/* ================================================================
 * 00031945  FUN_00031945
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031945(void)

{
}



/* ================================================================
 * 000319e0  FUN_000319e0
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000319e0(void)

{
}



/* ================================================================
 * 00031a47  FUN_00031a47
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031a47(void)

{
}



/* ================================================================
 * 00031b12  FUN_00031b12
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031b12(void)

{
}



/* ================================================================
 * 00031b79  FUN_00031b79
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031b79(void)

{
}



/* ================================================================
 * 00031c14  FUN_00031c14
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031c14(void)

{
}



/* ================================================================
 * 00031c8e  FUN_00031c8e
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031c8e(void)

{
}



/* ================================================================
 * 00031d09  FUN_00031d09
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031d09(void)

{
}



/* ================================================================
 * 00031dbe  FUN_00031dbe
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031dbe(void)

{
}



/* ================================================================
 * 00031e2e  FUN_00031e2e
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031e2e(void)

{
}



/* ================================================================
 * 00031e9f  FUN_00031e9f
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031e9f(void)

{
}



/* ================================================================
 * 00031f2d  FUN_00031f2d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031f2d(void)

{
}



/* ================================================================
 * 00031fc7  FUN_00031fc7
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00031fc7(void)

{
}



/* ================================================================
 * 0003202e  FUN_0003202e
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003202e(void)

{
}



/* ================================================================
 * 0003212d  FUN_0003212d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003212d(void)

{
}



/* ================================================================
 * 0003222c  FUN_0003222c
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003222c(void)

{
}



/* ================================================================
 * 0003228b  FUN_0003228b
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003228b(void)

{
}



/* ================================================================
 * 000322fc  FUN_000322fc
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000322fc(void)

{
}



/* ================================================================
 * 0003235b  FUN_0003235b
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003235b(void)

{
}



/* ================================================================
 * 000323ba  FUN_000323ba
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000323ba(void)

{
}



/* ================================================================
 * 00032419  FUN_00032419
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032419(void)

{
}



/* ================================================================
 * 00032478  FUN_00032478
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032478(void)

{
}



/* ================================================================
 * 000324dd  FUN_000324dd
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000324dd(void)

{
}



/* ================================================================
 * 00032542  FUN_00032542
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032542(void)

{
}



/* ================================================================
 * 000325b2  FUN_000325b2
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000325b2(void)

{
}



/* ================================================================
 * 00032622  FUN_00032622
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032622(void)

{
}



/* ================================================================
 * 000326ec  FUN_000326ec
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000326ec(void)

{
}



/* ================================================================
 * 000327b6  FUN_000327b6
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000327b6(void)

{
}



/* ================================================================
 * 0003281d  FUN_0003281d
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003281d(void)

{
}



/* ================================================================
 * 0003288d  FUN_0003288d
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003288d(void)

{
}



/* ================================================================
 * 000328f4  FUN_000328f4
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000328f4(void)

{
}



/* ================================================================
 * 0003295b  FUN_0003295b
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003295b(void)

{
}



/* ================================================================
 * 000329c2  FUN_000329c2
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000329c2(void)

{
}



/* ================================================================
 * 00032a32  FUN_00032a32
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032a32(void)

{
}



/* ================================================================
 * 00032a91  FUN_00032a91
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032a91(void)

{
}



/* ================================================================
 * 00032b02  FUN_00032b02
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032b02(void)

{
}



/* ================================================================
 * 00032b6a  FUN_00032b6a
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032b6a(void)

{
}



/* ================================================================
 * 00032bdb  FUN_00032bdb
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032bdb(void)

{
}



/* ================================================================
 * 00032c55  FUN_00032c55
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032c55(void)

{
}



/* ================================================================
 * 00032ccf  FUN_00032ccf
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032ccf(void)

{
}



/* ================================================================
 * 00032d69  FUN_00032d69
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032d69(void)

{
}



/* ================================================================
 * 00032dd0  FUN_00032dd0
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032dd0(void)

{
}



/* ================================================================
 * 00032e76  FUN_00032e76
 * bytes: 3  status: ok
 * ================================================================ */

undefined4 FUN_00032e76(void)

{
  return 0;
}



/* ================================================================
 * 00032e79  FUN_00032e79
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_00032e79(void)

{
  return;
}



/* ================================================================
 * 00032e7a  FUN_00032e7a
 * bytes: 4  status: ok
 * ================================================================ */

void FUN_00032e7a(void)

{
  return;
}



/* ================================================================
 * 00032e7e  FUN_00032e7e
 * bytes: 69  status: ok
 * ================================================================ */

void FUN_00032e7e(int param_1,ushort param_2)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  byte bVar4;

  bVar4 = 0;
  uVar2 = (uint)param_2;
  (*(code *)0x814cc10)(param_1,uVar2);
  puVar3 = (undefined4 *)(uVar2 * 0xe0 + *(int *)(param_1 + 0x5e98));
  for (iVar1 = 0x38; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = 0;
    puVar3 = puVar3 + (uint)bVar4 * -2 + 1;
  }
  *(undefined1 *)(*(int *)(param_1 + 0x5ea8) + uVar2) = 0;
  return;
}



/* ================================================================
 * 00032ec4  FUN_00032ec4
 * bytes: 16  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032ec4(void)

{
}



/* ================================================================
 * 00032f5a  FUN_00032f5a
 * bytes: 18  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032f5a(void)

{
}



/* ================================================================
 * 00032fa0  FUN_00032fa0
 * bytes: 10  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00032fa0(void)

{
}



/* ================================================================
 * 00033040  FUN_00033040
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_00033040(void)

{
  return;
}



/* ================================================================
 * 00033042  FUN_00033042
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_00033042(void)

{
  return;
}



/* ================================================================
 * 00033044  FUN_00033044
 * bytes: 3  status: ok
 * ================================================================ */

undefined1 FUN_00033044(void)

{
  return 1;
}



/* ================================================================
 * 00033048  FUN_00033048
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00033048(void)

{
}



/* ================================================================
 * 0003306c  FUN_0003306c
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003306c(void)

{
}



/* ================================================================
 * 00033090  FUN_00033090
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00033090(void)

{
}



/* ================================================================
 * 000330bc  FUN_000330bc
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000330bc(void)

{
}



/* ================================================================
 * 000330ec  FUN_000330ec
 * bytes: 31  status: ok
 * ================================================================ */

void FUN_000330ec(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;

  UNRECOVERED_JUMPTABLE = *(code **)(param_1 + 8);
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    UNRECOVERED_JUMPTABLE =
         *(code **)(UNRECOVERED_JUMPTABLE +
                   *(int *)(*(int *)(param_1 + 0xc) + *(int *)(param_1 + 4)) + -1);
  }
                    /* WARNING: Could not recover jumptable at 0x00033109. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)();
  return;
}



/* ================================================================
 * 0003310b  FUN_0003310b
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003310b(void)

{
}



/* ================================================================
 * 0003314e  FUN_0003314e
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003314e(void)

{
}



/* ================================================================
 * 000331a2  FUN_000331a2
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000331a2(void)

{
}



/* ================================================================
 * 000331c6  FUN_000331c6
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000331c6(void)

{
}



/* ================================================================
 * 000331ea  FUN_000331ea
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000331ea(void)

{
}



/* ================================================================
 * 0003322a  FUN_0003322a
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003322a(void)

{
}



/* ================================================================
 * 00033269  FUN_00033269
 * bytes: 203  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00033269(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  undefined4 extraout_ECX;
  timespec local_24 [2];

  local_24[0].tv_sec = 0;
  local_24[0].tv_nsec = 160000000;
  puVar1 = (undefined4 *)param_2[1];
  do {
    iVar3 = nanosleep(local_24,local_24);
    if (iVar3 != -1) break;
    piVar4 = __errno_location();
  } while (*piVar4 == 4);
  iVar3 = FUN_0001fc2f(*(undefined4 *)*puVar1,"SetVehicleAcceleration",puVar1[1],&__DT_PLTGOT);
  if (iVar3 == 0) {
    FUN_0001fdbe(*(undefined4 *)*puVar1,*(undefined4 *)puVar1[2],extraout_ECX,extraout_ECX);
    FUN_0001fdbe(*(undefined4 *)*puVar1,*(undefined4 *)puVar1[3]);
    FUN_0001fc1c(*(undefined4 *)*puVar1,puVar1[4],*(undefined4 *)puVar1[1]);
  }
  uVar2 = *(undefined4 *)*param_2;
  *(undefined4 *)*param_2 = 0;
  *param_1 = uVar2;
  return;
}



/* ================================================================
 * 000333b8  FUN_000333b8
 * bytes: 83  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.si replaced with injection: get_pc_thunk_si */

void FUN_000333b8(_State_baseV2 *param_1)

{
  _State_baseV2 *local_2c;
  _State_baseV2 *local_28;
  code *local_24;
  code *local_20;

  local_2c = param_1 + 0x11;
  local_28 = param_1 + 0x15;
  local_20 = FUN_00033269;
  local_24 = FUN_0003310b;
  std::__future_base::_State_baseV2::_M_set_result(param_1,(_Function_base *)&local_2c,1);
  std::_Function_base::~_Function_base((_Function_base *)&local_2c);
  return;
}



/* ================================================================
 * 00033424  FUN_00033424
 * bytes: 18  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00033424(void)

{
}



/* ================================================================
 * 0003348e  FUN_0003348e
 * bytes: 93  status: ok
 * ================================================================ */

void FUN_0003348e(void)

{
  int *piVar1;
  int iVar2;
  uint extraout_ECX;
  undefined8 uVar3;

  uVar3 = FUN_00032e7a();
  piVar1 = (int *)uVar3;
  if (0xf < extraout_ECX) {
    iVar2 = FUN_0003314e();
    *piVar1 = iVar2;
    piVar1[2] = extraout_ECX;
  }
  std::__cxx11::string::_S_copy((char *)*piVar1,(char *)((ulonglong)uVar3 >> 0x20),extraout_ECX);
  piVar1[1] = extraout_ECX;
  *(undefined1 *)(*piVar1 + extraout_ECX) = 0;
  return;
}



/* ================================================================
 * 000334ec  FUN_000334ec
 * bytes: 1  status: ok
 * ================================================================ */

void FUN_000334ec(void)

{
  return;
}



/* ================================================================
 * 000334ed  FUN_000334ed
 * bytes: 6  status: ok
 * ================================================================ */

undefined4 FUN_000334ed(void)

{
  return 1;
}



/* ================================================================
 * 000334f4  FUN_000334f4
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000334f4(void)

{
}



/* ================================================================
 * 00033542  FUN_00033542
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00033542(void)

{
}



/* ================================================================
 * 00033572  FUN_00033572
 * bytes: 13  status: ok
 * ================================================================ */

void FUN_00033572(void)

{
  FUN_000334f4();
  return;
}



/* ================================================================
 * 00033580  FUN_00033580
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00033580(void)

{
}



/* ================================================================
 * 000335ba  FUN_000335ba
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000335ba(void)

{
}



/* ================================================================
 * 000335ea  FUN_000335ea
 * bytes: 10  status: ok
 * ================================================================ */

void FUN_000335ea(void)

{
  FUN_00033580();
  return;
}



/* ================================================================
 * 000335f4  FUN_000335f4
 * bytes: 15  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000335f4(void)

{
}



/* ================================================================
 * 00033691  FUN_00033691
 * bytes: 828  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00033691(undefined4 param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined1 **ppuVar8;
  uint uVar9;
  byte bVar10;
  undefined1 local_243;
  undefined2 local_242;
  string local_23f [48];
  undefined1 *local_20f;
  undefined4 local_20b;
  undefined1 local_207 [16];
  undefined1 *local_1f7;
  undefined4 local_1f3;
  undefined1 local_1ef [16];
  undefined1 *local_1df;
  undefined4 local_1db;
  undefined1 local_1d7 [16];
  undefined2 local_1c7;
  undefined1 *local_12d [2];
  undefined1 local_125 [277];

  bVar10 = 0;
  local_243 = 0xe9;
  iVar1 = *(int *)(param_2 + 4);
  uVar2 = *(uint *)(param_2 + 8);
  uVar9 = 6;
  if ((int)uVar2 < 7) {
    uVar9 = uVar2;
  }
  local_242 = (short)iVar1;
  iVar3 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar3 + 0x5ea8) + iVar1) == '\0') {
    FUN_00033424();
    std::__cxx11::string::string(local_23f,(string *)&PTR_s_set_gears_0004e74c);
    local_20f = local_207;
    local_1f7 = local_1ef;
    local_1df = local_1d7;
    local_20b = 0;
    local_207[0] = 0;
    local_1f3 = 0;
    local_1ef[0] = 0;
    local_1db = 0;
    local_1d7[0] = 0;
    if ((int)uVar2 < 0) {
      uVar9 = -uVar9;
    }
    uVar5 = std::__detail::__to_chars_len<unsigned_int>(uVar9,10);
    local_12d[0] = local_125;
    std::__cxx11::string::_M_construct((string *)local_12d,-((int)uVar2 >> 0x1f) + uVar5,'-');
    std::__detail::__to_chars_10_impl<unsigned_int>
              (local_12d[0] + -((int)uVar2 >> 0x1f),uVar5,uVar9);
    FUN_000335f4();
    std::__cxx11::string::_M_dispose();
    local_1c7 = (short)iVar1;
    std::__cxx11::string::_M_assign((string *)&local_20f);
    std::__cxx11::string::_M_assign((string *)&local_1df);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c((string *)local_12d,(string *)&local_20f);
    FUN_0001f3ea(PTR_DAT_0004dfcc,(string *)local_12d);
    FUN_0001ae64((string *)local_12d);
    FUN_0001ae64((string *)&local_20f);
  }
  else {
    iVar3 = FUN_0001a3ca();
    *(char *)(*(int *)(iVar3 + 0x5e98) + 0x76 + iVar1 * 0xe0) = (char)uVar9;
    FUN_0003745a(local_12d);
    ppuVar8 = &local_20f;
    for (iVar3 = 0xe2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)ppuVar8 = 0;
      ppuVar8 = (undefined1 **)((int)ppuVar8 + (uint)bVar10 * -2 + 1);
    }
    iVar3 = FUN_0001a3ca();
    puVar7 = (undefined4 *)(iVar1 * 0xe0 + *(int *)(iVar3 + 0x5e98));
    ppuVar8 = &local_20f;
    for (iVar6 = 0x38; iVar6 != 0; iVar6 = iVar6 + -1) {
      *ppuVar8 = (undefined1 *)*puVar7;
      puVar7 = puVar7 + (uint)bVar10 * -2 + 1;
      ppuVar8 = ppuVar8 + (uint)bVar10 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_242,0x10,1);
    FUN_00037ae4(local_12d,&local_20f,0x710,1);
    uVar4 = FUN_0001e31d();
    FUN_000373be(uVar4,&local_243,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 00033a7b  FUN_00033a7b
 * bytes: 517  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00033a7b(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined *puVar9;
  undefined4 uVar10;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar8 = 0;
  uVar1 = *(uint *)(param_2 + 4);
  uVar3 = *(undefined4 *)(param_2 + 8);
  local_22a = (undefined2)uVar1;
  iVar2 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar2 + 0x5ea8) + uVar1) == '\0') {
    uVar4 = FUN_00033424();
    puVar9 = &DAT_0004f5b4;
    uVar10 = uVar4;
    std::__cxx11::string::string(local_227,(string *)&DAT_0004f5b4);
    FUN_0001f4cc(local_20f,uVar1 & 0xffff,uVar3,local_227,local_12d,puVar9,uVar4,uVar10);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(local_12d,local_20f);
    FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
    FUN_0001ae64(local_12d);
    FUN_0001ae64(local_20f);
  }
  else {
    iVar2 = FUN_0001a3ca();
    *(undefined4 *)(*(int *)(iVar2 + 0x5e98) + 0xd0 + uVar1 * 0xe0) = uVar3;
    FUN_0003745a(local_12d);
    puVar6 = local_20f;
    for (iVar2 = 0xe2; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar6 = 0;
      puVar6 = (undefined4 *)((int)puVar6 + (uint)bVar8 * -2 + 1);
    }
    local_227[0] = (string)0xe9;
    iVar2 = FUN_0001a3ca();
    puVar6 = (undefined4 *)(uVar1 * 0xe0 + *(int *)(iVar2 + 0x5e98));
    puVar7 = local_20f;
    for (iVar5 = 0x38; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
      puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22a,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar3 = FUN_0001e31d();
    FUN_000373be(uVar3,local_227,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 00033cf9  FUN_00033cf9
 * bytes: 518  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00033cf9(undefined4 param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  byte bVar10;
  undefined *puVar11;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar10 = 0;
  uVar2 = *(uint *)(param_2 + 4);
  uVar3 = *(uint *)(param_2 + 8);
  local_22a = (undefined2)uVar2;
  iVar4 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar4 + 0x5ea8) + uVar2) == '\0') {
    uVar6 = FUN_00033424();
    puVar11 = &DAT_0004f584;
    uVar5 = uVar6;
    std::__cxx11::string::string(local_227,(string *)&DAT_0004f584);
    FUN_0001f4cc(local_20f,uVar2 & 0xffff,uVar3,local_227,local_12d,puVar11,uVar6,uVar5);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(local_12d,local_20f);
    FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
    FUN_0001ae64(local_12d);
    FUN_0001ae64(local_20f);
  }
  else {
    iVar4 = FUN_0001a3ca();
    puVar1 = (uint *)(*(int *)(iVar4 + 0x5e98) + uVar2 * 0xe0 + 0xd0);
    *puVar1 = *puVar1 | uVar3;
    FUN_0003745a(local_12d);
    puVar8 = local_20f;
    for (iVar4 = 0xe2; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined1 *)puVar8 = 0;
      puVar8 = (undefined4 *)((int)puVar8 + (uint)bVar10 * -2 + 1);
    }
    local_227[0] = (string)0xe9;
    iVar4 = FUN_0001a3ca();
    puVar8 = (undefined4 *)(uVar2 * 0xe0 + *(int *)(iVar4 + 0x5e98));
    puVar9 = local_20f;
    for (iVar7 = 0x38; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22a,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar5 = FUN_0001e31d();
    FUN_000373be(uVar5,local_227,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 00033f78  FUN_00033f78
 * bytes: 520  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00033f78(undefined4 param_1,int param_2)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  byte bVar10;
  undefined *puVar11;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar10 = 0;
  uVar2 = *(uint *)(param_2 + 4);
  uVar3 = *(uint *)(param_2 + 8);
  local_22a = (undefined2)uVar2;
  iVar4 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar4 + 0x5ea8) + uVar2) == '\0') {
    uVar6 = FUN_00033424();
    puVar11 = &DAT_0004f524;
    uVar5 = uVar6;
    std::__cxx11::string::string(local_227,(string *)&DAT_0004f524);
    FUN_0001f4cc(local_20f,uVar2 & 0xffff,uVar3,local_227,local_12d,puVar11,uVar6,uVar5);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(local_12d,local_20f);
    FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
    FUN_0001ae64(local_12d);
    FUN_0001ae64(local_20f);
  }
  else {
    iVar4 = FUN_0001a3ca();
    puVar1 = (uint *)(*(int *)(iVar4 + 0x5e98) + uVar2 * 0xe0 + 0xd0);
    *puVar1 = *puVar1 & ~uVar3;
    FUN_0003745a(local_12d);
    puVar8 = local_20f;
    for (iVar4 = 0xe2; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined1 *)puVar8 = 0;
      puVar8 = (undefined4 *)((int)puVar8 + (uint)bVar10 * -2 + 1);
    }
    local_227[0] = (string)0xe9;
    iVar4 = FUN_0001a3ca();
    puVar8 = (undefined4 *)(uVar2 * 0xe0 + *(int *)(iVar4 + 0x5e98));
    puVar9 = local_20f;
    for (iVar7 = 0x38; iVar7 != 0; iVar7 = iVar7 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22a,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar5 = FUN_0001e31d();
    FUN_000373be(uVar5,local_227,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 000341f9  FUN_000341f9
 * bytes: 582  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_000341f9(undefined4 param_1,int param_2)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined **ppuVar10;
  undefined1 local_22b;
  short local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar9 = 0;
  local_22b = 0xe9;
  iVar6 = *(int *)(param_2 + 4);
  fVar1 = DAT_00040548 * *(float *)(param_2 + 8);
  local_22a = (short)iVar6;
  iVar2 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar2 + 0x5ea8) + (int)local_22a) == '\0') {
    uVar4 = FUN_00033424();
    ppuVar10 = &PTR_s_max_speed_0004e794;
    uVar3 = uVar4;
    std::__cxx11::string::string(local_227,(string *)&PTR_s_max_speed_0004e794);
    FUN_0003724c(local_20f,local_22a,fVar1,local_227,local_12d,ppuVar10,uVar4,uVar3);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(local_12d,local_20f);
    FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
    FUN_0001ae64(local_12d);
    FUN_0001ae64(local_20f);
  }
  else if (0.0 < fVar1) {
    iVar2 = FUN_0001a3ca();
    iVar6 = iVar6 * 0xe0;
    *(float *)(*(int *)(iVar2 + 0x5e98) + 0x84 + iVar6) = fVar1;
    iVar2 = FUN_0001a3ca();
    *(float *)(*(int *)(iVar2 + 0x5e98) + 0x88 + iVar6) = fVar1;
    FUN_0003745a(local_12d);
    puVar7 = local_20f;
    for (iVar2 = 0xe2; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar7 = 0;
      puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar9 * -2 + 1);
    }
    iVar2 = FUN_0001a3ca();
    puVar7 = (undefined4 *)(iVar6 + *(int *)(iVar2 + 0x5e98));
    puVar8 = local_20f;
    for (iVar5 = 0x38; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22a,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar3 = FUN_0001e31d();
    FUN_000373be(uVar3,&local_22b,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 000344bb  FUN_000344bb
 * bytes: 646  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_000344bb(undefined4 param_1,int param_2)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  byte bVar10;
  undefined **ppuVar11;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar10 = 0;
  uVar2 = *(uint *)(param_2 + 4);
  fVar1 = *(float *)(param_2 + 8);
  local_22a = (undefined2)uVar2;
  iVar3 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar3 + 0x5ea8) + uVar2) == '\0') {
    if (0.0 < fVar1) {
      fVar1 = fVar1 * DAT_00040548;
      uVar5 = FUN_00033424();
      ppuVar11 = &PTR_s_add_max_speed_0004e704;
      uVar4 = uVar5;
      std::__cxx11::string::string(local_227,(string *)&PTR_s_add_max_speed_0004e704);
      FUN_0003724c(local_20f,uVar2 & 0xffff,fVar1,local_227,local_12d,ppuVar11,uVar5,uVar4);
      std::__cxx11::string::_M_dispose();
      std::__cxx11::string::_M_dispose();
      FUN_0001f10c(local_12d,local_20f);
      FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
      FUN_0001ae64(local_12d);
      FUN_0001ae64(local_20f);
    }
  }
  else if (0.0 < fVar1) {
    local_227[0] = (string)0xe9;
    fVar1 = fVar1 * DAT_00040548;
    iVar3 = FUN_0001a3ca();
    iVar7 = uVar2 * 0xe0;
    iVar3 = *(int *)(iVar3 + 0x5e98) + iVar7;
    *(float *)(iVar3 + 0x84) = fVar1 + *(float *)(iVar3 + 0x84);
    iVar3 = FUN_0001a3ca();
    iVar3 = *(int *)(iVar3 + 0x5e98) + iVar7;
    *(float *)(iVar3 + 0x88) = fVar1 + *(float *)(iVar3 + 0x88);
    FUN_0003745a(local_12d);
    puVar8 = local_20f;
    for (iVar3 = 0xe2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar8 = 0;
      puVar8 = (undefined4 *)((int)puVar8 + (uint)bVar10 * -2 + 1);
    }
    iVar3 = FUN_0001a3ca();
    puVar8 = (undefined4 *)(iVar7 + *(int *)(iVar3 + 0x5e98));
    puVar9 = local_20f;
    for (iVar6 = 0x38; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22a,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar4 = FUN_0001e31d();
    FUN_000373be(uVar4,local_227,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 000347bd  FUN_000347bd
 * bytes: 761  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_000347bd(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined **ppuVar10;
  float fVar11;
  float fVar12;
  uint uVar13;
  undefined1 *puVar14;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar9 = 0;
  uVar13 = *(uint *)(param_2 + 4);
  fVar12 = *(float *)(param_2 + 8);
  local_22a = (undefined2)uVar13;
  iVar1 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar1 + 0x5ea8) + uVar13) == '\0') {
    fVar11 = 0.0;
    if ((0.0 < fVar12) &&
       (iVar1 = FUN_0001a3ca(),
       fVar11 < *(float *)(uVar13 * 0xe0 + *(int *)(iVar1 + 0x5e98) + 0x84) - fVar12)) {
      fVar12 = fVar12 * DAT_00040548;
      uVar3 = FUN_00033424(fVar11,fVar12);
      ppuVar10 = &PTR_s_add_max_speed_0004e704;
      uVar2 = uVar3;
      std::__cxx11::string::string(local_227,(string *)&PTR_s_add_max_speed_0004e704);
      puVar7 = local_20f;
      FUN_0003724c(puVar7,uVar13 & 0xffff,fVar12,local_227,local_12d,ppuVar10,uVar3,uVar2,fVar11,
                   fVar12,puVar7);
      std::__cxx11::string::_M_dispose();
      std::__cxx11::string::_M_dispose();
      FUN_0001f10c(local_12d,puVar7);
      FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
      FUN_0001ae64(local_12d);
      FUN_0001ae64(puVar7);
    }
  }
  else {
    fVar11 = 0.0;
    if (0.0 < fVar12) {
      iVar1 = FUN_0001a3ca();
      iVar5 = uVar13 * 0xe0;
      if (fVar11 < *(float *)(*(int *)(iVar1 + 0x5e98) + 0x84 + iVar5) - fVar12) {
        local_227[0] = (string)0xe9;
        fVar12 = fVar12 * DAT_00040548;
        iVar1 = FUN_0001a3ca();
        iVar1 = *(int *)(iVar1 + 0x5e98) + iVar5;
        *(float *)(iVar1 + 0x84) = *(float *)(iVar1 + 0x84) - fVar12;
        iVar1 = FUN_0001a3ca();
        puVar14 = local_12d;
        iVar1 = *(int *)(iVar1 + 0x5e98) + iVar5;
        *(float *)(iVar1 + 0x88) = *(float *)(iVar1 + 0x88) - fVar12;
        FUN_0003745a(puVar14);
        puVar7 = local_20f;
        for (iVar1 = 0xe2; iVar1 != 0; iVar1 = iVar1 + -1) {
          *(undefined1 *)puVar7 = 0;
          puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar9 * -2 + 1);
        }
        puVar7 = local_20f;
        iVar1 = FUN_0001a3ca();
        puVar6 = (undefined4 *)(iVar5 + *(int *)(iVar1 + 0x5e98));
        puVar8 = puVar7;
        for (iVar4 = 0x38; iVar4 != 0; iVar4 = iVar4 + -1) {
          *puVar8 = *puVar6;
          puVar6 = puVar6 + (uint)bVar9 * -2 + 1;
          puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
        }
        FUN_00037ae4(puVar14,&local_22a,0x10,1);
        FUN_00037ae4(puVar14,puVar7,0x710,1);
        uVar2 = FUN_0001e31d();
        FUN_000373be(uVar2,local_227,puVar14,0xffff,2);
        FUN_00037562(puVar14);
      }
    }
  }
  return 1;
}



/* ================================================================
 * 00034b32  FUN_00034b32
 * bytes: 555  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00034b32(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined **ppuVar9;
  float fVar10;
  undefined4 *puVar11;
  undefined1 *puVar12;
  undefined1 local_22b;
  short local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar8 = 0;
  local_22b = 0xe9;
  uVar1 = *(uint *)(param_2 + 4);
  fVar10 = DAT_0004054c * *(float *)(param_2 + 8) * DAT_00040550;
  local_22a = (short)uVar1;
  iVar2 = FUN_0001a3ca();
  puVar12 = local_12d;
  puVar11 = local_20f;
  if (*(char *)(*(int *)(iVar2 + 0x5ea8) + (int)local_22a) == '\0') {
    uVar4 = FUN_00033424(fVar10,puVar11,puVar12);
    ppuVar9 = &PTR_s_set_accel_0004e77c;
    uVar3 = uVar4;
    std::__cxx11::string::string(local_227,(string *)&PTR_s_set_accel_0004e77c);
    FUN_0003724c(puVar11,uVar1 & 0xffff,fVar10,local_227,puVar12,ppuVar9,uVar4,uVar3);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(puVar12,puVar11);
    FUN_0001f3ea(PTR_DAT_0004dfcc,puVar12);
    FUN_0001ae64(puVar12);
    FUN_0001ae64(puVar11);
  }
  else {
    iVar2 = FUN_0001a3ca();
    *(float *)(*(int *)(iVar2 + 0x5e98) + 0x7c + uVar1 * 0xe0) = fVar10;
    FUN_0003745a(puVar12);
    puVar6 = puVar11;
    for (iVar2 = 0xe2; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar6 = 0;
      puVar6 = (undefined4 *)((int)puVar6 + (uint)bVar8 * -2 + 1);
    }
    iVar2 = FUN_0001a3ca();
    puVar6 = (undefined4 *)(uVar1 * 0xe0 + *(int *)(iVar2 + 0x5e98));
    puVar7 = puVar11;
    for (iVar5 = 0x38; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
      puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
    }
    FUN_00037ae4(puVar12,&local_22a,0x10,1);
    FUN_00037ae4(puVar12,puVar11,0x710,1);
    uVar3 = FUN_0001e31d();
    FUN_000373be(uVar3,&local_22b,puVar12,0xffff,2);
    FUN_00037562(puVar12);
  }
  return 1;
}



/* ================================================================
 * 00034dd9  FUN_00034dd9
 * bytes: 601  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00034dd9(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined **ppuVar9;
  float fVar10;
  undefined4 *puVar11;
  undefined1 *puVar12;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar8 = 0;
  fVar10 = *(float *)(param_2 + 8);
  uVar1 = *(uint *)(param_2 + 4);
  local_22a = (undefined2)uVar1;
  iVar2 = FUN_0001a3ca();
  puVar12 = local_12d;
  puVar11 = local_20f;
  if (*(char *)(*(int *)(iVar2 + 0x5ea8) + uVar1) == '\0') {
    fVar10 = DAT_00040550 * fVar10 * DAT_0004054c;
    uVar4 = FUN_00033424(fVar10,puVar11,puVar12);
    ppuVar9 = &PTR_s_add_accel_0004e6ec;
    uVar3 = uVar4;
    std::__cxx11::string::string(local_227,(string *)&PTR_s_add_accel_0004e6ec);
    FUN_0003724c(puVar11,uVar1 & 0xffff,fVar10,local_227,puVar12,ppuVar9,uVar4,uVar3);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(puVar12,puVar11);
    FUN_0001f3ea(PTR_DAT_0004dfcc,puVar12);
    FUN_0001ae64(puVar12);
    uVar3 = FUN_0001ae64(puVar11);
  }
  else {
    local_227[0] = (string)0xe9;
    fVar10 = DAT_00040550 * fVar10 * DAT_0004054c;
    iVar2 = FUN_0001a3ca();
    iVar2 = *(int *)(iVar2 + 0x5e98) + uVar1 * 0xe0;
    *(float *)(iVar2 + 0x7c) = fVar10 + *(float *)(iVar2 + 0x7c);
    FUN_0003745a(puVar12);
    puVar6 = puVar11;
    for (iVar2 = 0xe2; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar6 = 0;
      puVar6 = (undefined4 *)((int)puVar6 + (uint)bVar8 * -2 + 1);
    }
    iVar2 = FUN_0001a3ca();
    puVar6 = (undefined4 *)(uVar1 * 0xe0 + *(int *)(iVar2 + 0x5e98));
    puVar7 = puVar11;
    for (iVar5 = 0x38; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
      puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
    }
    FUN_00037ae4(puVar12,&local_22a,0x10,1);
    FUN_00037ae4(puVar12,puVar11,0x710,1);
    uVar3 = FUN_0001e31d();
    FUN_000373be(uVar3,local_227,puVar12,0xffff,2);
    uVar3 = FUN_00037562(puVar12);
  }
  FUN_00037562(puVar12);
                    /* WARNING: Subroutine does not return */
  _Unwind_Resume(uVar3);
}



/* ================================================================
 * 00035088  FUN_00035088
 * bytes: 645  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00035088(undefined4 param_1,int param_2)

{
  float fVar1;
  uint uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  byte bVar11;
  undefined **ppuVar12;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar11 = 0;
  fVar1 = *(float *)(param_2 + 8);
  uVar2 = *(uint *)(param_2 + 4);
  local_22a = (undefined2)uVar2;
  iVar5 = FUN_0001a3ca();
  fVar4 = DAT_00040550;
  fVar3 = DAT_0004054c;
  if (*(char *)(*(int *)(iVar5 + 0x5ea8) + uVar2) == '\0') {
    FUN_0001a3ca();
    uVar7 = FUN_00033424();
    ppuVar12 = &PTR_s_add_accel_0004e6ec;
    uVar6 = uVar7;
    std::__cxx11::string::string(local_227,(string *)&PTR_s_add_accel_0004e6ec);
    FUN_0003724c(local_20f,uVar2 & 0xffff,fVar1 * fVar3 * fVar4,local_227,local_12d,ppuVar12,uVar7,
                 uVar6);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(local_12d,local_20f);
    FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
    FUN_0001ae64(local_12d);
    uVar6 = FUN_0001ae64(local_20f);
  }
  else {
    FUN_0001a3ca();
    local_227[0] = (string)0xe9;
    iVar5 = FUN_0001a3ca();
    iVar5 = *(int *)(iVar5 + 0x5e98) + uVar2 * 0xe0;
    *(float *)(iVar5 + 0x7c) = *(float *)(iVar5 + 0x7c) - fVar1 * fVar3 * fVar4;
    FUN_0003745a(local_12d);
    puVar9 = local_20f;
    for (iVar5 = 0xe2; iVar5 != 0; iVar5 = iVar5 + -1) {
      *(undefined1 *)puVar9 = 0;
      puVar9 = (undefined4 *)((int)puVar9 + (uint)bVar11 * -2 + 1);
    }
    iVar5 = FUN_0001a3ca();
    puVar9 = (undefined4 *)(uVar2 * 0xe0 + *(int *)(iVar5 + 0x5e98));
    puVar10 = local_20f;
    for (iVar8 = 0x38; iVar8 != 0; iVar8 = iVar8 + -1) {
      *puVar10 = *puVar9;
      puVar9 = puVar9 + (uint)bVar11 * -2 + 1;
      puVar10 = puVar10 + (uint)bVar11 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22a,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar6 = FUN_0001e31d();
    FUN_000373be(uVar6,local_227,local_12d,0xffff,2);
    uVar6 = FUN_00037562(local_12d);
  }
  FUN_00037562(local_12d);
                    /* WARNING: Subroutine does not return */
  _Unwind_Resume(uVar6);
}



/* ================================================================
 * 00035363  FUN_00035363
 * bytes: 690  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00035363(undefined4 param_1,int param_2)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  byte bVar10;
  undefined **ppuVar11;
  undefined1 local_22b;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar10 = 0;
  local_22b = 0xe9;
  uVar2 = *(uint *)(param_2 + 4);
  fVar1 = *(float *)(param_2 + 8);
  local_22a = (undefined2)uVar2;
  iVar3 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar3 + 0x5ea8) + uVar2) == '\0') {
    if (0.0 < fVar1) {
      uVar5 = FUN_00033424();
      ppuVar11 = &PTR_s_set_mass_0004e764;
      uVar4 = uVar5;
      std::__cxx11::string::string(local_227,(string *)&PTR_s_set_mass_0004e764);
      FUN_0003724c(local_20f,uVar2 & 0xffff,fVar1,local_227,local_12d,ppuVar11,uVar5,uVar4);
      std::__cxx11::string::_M_dispose();
      std::__cxx11::string::_M_dispose();
      FUN_0001f10c(local_12d,local_20f);
      FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
      FUN_0001ae64(local_12d);
      FUN_0001ae64(local_20f);
    }
  }
  else if (0.0 < fVar1) {
    iVar3 = FUN_0001a3ca();
    iVar7 = uVar2 * 0xe0;
    *(float *)(*(int *)(iVar3 + 0x5e98) + 4 + iVar7) = fVar1;
    iVar3 = FUN_0001a3ca();
    *(float *)(*(int *)(iVar3 + 0x5e98) + 8 + iVar7) = 1.0 / fVar1;
    iVar3 = FUN_0001a3ca();
    fVar1 = *(float *)(*(int *)(iVar3 + 0x5e98) + 8 + iVar7);
    iVar3 = FUN_0001a3ca();
    fVar1 = fVar1 * *(float *)(*(int *)(iVar3 + 0x5e98) + 200 + iVar7) * DAT_0004053c;
    iVar3 = FUN_0001a3ca();
    *(float *)(*(int *)(iVar3 + 0x5e98) + 200 + iVar7) = fVar1;
    FUN_0003745a(local_12d);
    puVar8 = local_20f;
    for (iVar3 = 0xe2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar8 = 0;
      puVar8 = (undefined4 *)((int)puVar8 + (uint)bVar10 * -2 + 1);
    }
    iVar3 = FUN_0001a3ca();
    puVar8 = (undefined4 *)(iVar7 + *(int *)(iVar3 + 0x5e98));
    puVar9 = local_20f;
    for (iVar6 = 0x38; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar9 = *puVar8;
      puVar8 = puVar8 + (uint)bVar10 * -2 + 1;
      puVar9 = puVar9 + (uint)bVar10 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22a,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar4 = FUN_0001e31d();
    FUN_000373be(uVar4,&local_22b,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 00035691  FUN_00035691
 * bytes: 678  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00035691(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined **ppuVar10;
  float fVar11;
  undefined4 *puVar12;
  undefined1 *puVar13;
  undefined1 local_22b;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar9 = 0;
  local_22b = 0xe9;
  fVar11 = *(float *)(param_2 + 8);
  uVar1 = *(uint *)(param_2 + 4);
  local_22a = (undefined2)uVar1;
  iVar2 = FUN_0001a3ca();
  puVar13 = local_12d;
  puVar12 = local_20f;
  if (*(char *)(*(int *)(iVar2 + 0x5ea8) + uVar1) == '\0') {
    uVar4 = FUN_00033424(fVar11,puVar12,puVar13);
    ppuVar10 = &PTR_s_add_mass_0004e6d4;
    uVar3 = uVar4;
    std::__cxx11::string::string(local_227,(string *)&PTR_s_add_mass_0004e6d4);
    FUN_0003724c(puVar12,uVar1 & 0xffff,fVar11,local_227,puVar13,ppuVar10,uVar4,uVar3);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(puVar13,puVar12);
    FUN_0001f3ea(PTR_DAT_0004dfcc,puVar13);
    FUN_0001ae64(puVar13);
    uVar3 = FUN_0001ae64(puVar12);
  }
  else {
    iVar2 = FUN_0001a3ca();
    iVar6 = uVar1 * 0xe0;
    iVar2 = *(int *)(iVar2 + 0x5e98) + iVar6;
    *(float *)(iVar2 + 4) = fVar11 + *(float *)(iVar2 + 4);
    iVar2 = FUN_0001a3ca();
    iVar2 = *(int *)(iVar2 + 0x5e98) + iVar6;
    *(float *)(iVar2 + 8) = 1.0 / fVar11 + *(float *)(iVar2 + 8);
    iVar2 = FUN_0001a3ca();
    fVar11 = *(float *)(*(int *)(iVar2 + 0x5e98) + 8 + iVar6);
    iVar2 = FUN_0001a3ca();
    fVar11 = fVar11 * *(float *)(*(int *)(iVar2 + 0x5e98) + 200 + iVar6) * DAT_0004053c;
    iVar2 = FUN_0001a3ca();
    iVar2 = *(int *)(iVar2 + 0x5e98) + iVar6;
    *(float *)(iVar2 + 200) = fVar11 + *(float *)(iVar2 + 200);
    FUN_0003745a(puVar13);
    puVar7 = puVar12;
    for (iVar2 = 0xe2; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar7 = 0;
      puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar9 * -2 + 1);
    }
    iVar2 = FUN_0001a3ca();
    puVar7 = (undefined4 *)(iVar6 + *(int *)(iVar2 + 0x5e98));
    puVar8 = puVar12;
    for (iVar5 = 0x38; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
    }
    FUN_00037ae4(puVar13,&local_22a,0x10,1);
    FUN_00037ae4(puVar13,puVar12,0x710,1);
    uVar3 = FUN_0001e31d();
    FUN_000373be(uVar3,&local_22b,puVar13,0xffff,2);
    uVar3 = FUN_00037562(puVar13);
  }
  FUN_00037562(puVar13);
                    /* WARNING: Subroutine does not return */
  _Unwind_Resume(uVar3);
}



/* ================================================================
 * 0003598a  FUN_0003598a
 * bytes: 688  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0003598a(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined **ppuVar10;
  float fVar11;
  undefined4 *puVar12;
  undefined1 *puVar13;
  undefined1 local_22b;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar9 = 0;
  local_22b = 0xe9;
  fVar11 = *(float *)(param_2 + 8);
  uVar1 = *(uint *)(param_2 + 4);
  local_22a = (undefined2)uVar1;
  iVar2 = FUN_0001a3ca();
  puVar13 = local_12d;
  puVar12 = local_20f;
  if (*(char *)(*(int *)(iVar2 + 0x5ea8) + uVar1) == '\0') {
    FUN_0001a3ca(fVar11,puVar12,puVar13);
    uVar4 = FUN_00033424();
    ppuVar10 = &PTR_s_subtract_mass_0004e6a4;
    uVar3 = uVar4;
    std::__cxx11::string::string(local_227,(string *)&PTR_s_subtract_mass_0004e6a4);
    FUN_0003724c(puVar12,uVar1 & 0xffff,fVar11,local_227,puVar13,ppuVar10,uVar4,uVar3);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(puVar13,puVar12);
    FUN_0001f3ea(PTR_DAT_0004dfcc,puVar13);
    FUN_0001ae64(puVar13);
    uVar3 = FUN_0001ae64(puVar12);
  }
  else {
    FUN_0001a3ca();
    iVar6 = uVar1 * 0xe0;
    iVar2 = FUN_0001a3ca();
    iVar2 = *(int *)(iVar2 + 0x5e98) + iVar6;
    *(float *)(iVar2 + 4) = *(float *)(iVar2 + 4) - fVar11;
    iVar2 = FUN_0001a3ca();
    iVar2 = *(int *)(iVar2 + 0x5e98) + iVar6;
    *(float *)(iVar2 + 8) = *(float *)(iVar2 + 8) - 1.0 / fVar11;
    iVar2 = FUN_0001a3ca();
    fVar11 = *(float *)(*(int *)(iVar2 + 0x5e98) + 8 + iVar6);
    iVar2 = FUN_0001a3ca();
    fVar11 = fVar11 * *(float *)(*(int *)(iVar2 + 0x5e98) + 200 + iVar6) * DAT_0004053c;
    iVar2 = FUN_0001a3ca();
    iVar2 = *(int *)(iVar2 + 0x5e98) + iVar6;
    *(float *)(iVar2 + 200) = *(float *)(iVar2 + 200) - fVar11;
    FUN_0003745a(puVar13);
    puVar7 = puVar12;
    for (iVar2 = 0xe2; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar7 = 0;
      puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar9 * -2 + 1);
    }
    iVar2 = FUN_0001a3ca();
    puVar7 = (undefined4 *)(iVar6 + *(int *)(iVar2 + 0x5e98));
    puVar8 = puVar12;
    for (iVar5 = 0x38; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
    }
    FUN_00037ae4(puVar13,&local_22a,0x10,1);
    FUN_00037ae4(puVar13,puVar12,0x710,1);
    uVar3 = FUN_0001e31d();
    FUN_000373be(uVar3,&local_22b,puVar13,0xffff,2);
    uVar3 = FUN_00037562(puVar13);
  }
  FUN_00037562(puVar13);
                    /* WARNING: Subroutine does not return */
  _Unwind_Resume(uVar3);
}



/* ================================================================
 * 00035c8d  FUN_00035c8d
 * bytes: 597  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00035c8d(undefined4 param_1,int param_2)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined *puVar10;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar9 = 0;
  uVar2 = *(uint *)(param_2 + 4);
  fVar1 = *(float *)(param_2 + 8);
  local_22a = (undefined2)uVar2;
  iVar3 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar3 + 0x5ea8) + uVar2) == '\0') {
    if (0.0 < fVar1) {
      uVar5 = FUN_00033424();
      puVar10 = &DAT_0004f5cc;
      uVar4 = uVar5;
      std::__cxx11::string::string(local_227,(string *)&DAT_0004f5cc);
      FUN_0003724c(local_20f,uVar2 & 0xffff,fVar1,local_227,local_12d,puVar10,uVar5,uVar4);
      std::__cxx11::string::_M_dispose();
      std::__cxx11::string::_M_dispose();
      FUN_0001f10c(local_12d,local_20f);
      FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
      FUN_0001ae64(local_12d);
      FUN_0001ae64(local_20f);
    }
  }
  else if (0.0 < fVar1) {
    fVar1 = DAT_00040540 * fVar1;
    iVar3 = FUN_0001a3ca();
    *(float *)(*(int *)(iVar3 + 0x5e98) + 0x94 + uVar2 * 0xe0) = fVar1;
    FUN_0003745a(local_12d);
    puVar7 = local_20f;
    for (iVar3 = 0xe2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar7 = 0;
      puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar9 * -2 + 1);
    }
    local_227[0] = (string)0xe9;
    iVar3 = FUN_0001a3ca();
    puVar7 = (undefined4 *)(uVar2 * 0xe0 + *(int *)(iVar3 + 0x5e98));
    puVar8 = local_20f;
    for (iVar6 = 0x38; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22a,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar4 = FUN_0001e31d();
    FUN_000373be(uVar4,local_227,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 00035f5e  FUN_00035f5e
 * bytes: 583  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00035f5e(undefined4 param_1,int param_2)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined *puVar10;
  undefined2 local_22a;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar9 = 0;
  uVar2 = *(uint *)(param_2 + 4);
  fVar1 = *(float *)(param_2 + 8);
  local_22a = (undefined2)uVar2;
  iVar3 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar3 + 0x5ea8) + uVar2) == '\0') {
    uVar5 = FUN_00033424();
    puVar10 = &DAT_0004f59c;
    uVar4 = uVar5;
    std::__cxx11::string::string(local_227,(string *)&DAT_0004f59c);
    FUN_0003724c(local_20f,uVar2 & 0xffff,fVar1,local_227,local_12d,puVar10,uVar5,uVar4);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(local_12d,local_20f);
    FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
    FUN_0001ae64(local_12d);
    FUN_0001ae64(local_20f);
  }
  else if ((fVar1 <= DAT_00040544) && (0.0 < fVar1)) {
    iVar3 = FUN_0001a3ca();
    *(float *)(*(int *)(iVar3 + 0x5e98) + 0xa0 + uVar2 * 0xe0) = fVar1;
    FUN_0003745a(local_12d);
    puVar7 = local_20f;
    for (iVar3 = 0xe2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar7 = 0;
      puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar9 * -2 + 1);
    }
    local_227[0] = (string)0xe9;
    iVar3 = FUN_0001a3ca();
    puVar7 = (undefined4 *)(uVar2 * 0xe0 + *(int *)(iVar3 + 0x5e98));
    puVar8 = local_20f;
    for (iVar6 = 0x38; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22a,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar4 = FUN_0001e31d();
    FUN_000373be(uVar4,local_227,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 00036221  FUN_00036221
 * bytes: 646  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00036221(undefined4 param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  byte bVar9;
  undefined *puVar10;
  uint local_22c;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar9 = 0;
  fVar1 = *(float *)(param_2 + 8);
  local_22c = *(uint *)(param_2 + 4);
  iVar3 = FUN_0001a3ca();
  fVar2 = DAT_00040544;
  if (*(char *)(*(int *)(iVar3 + 0x5ea8) + local_22c) == '\0') {
    uVar5 = FUN_00033424();
    puVar10 = &DAT_0004f56c;
    uVar4 = uVar5;
    std::__cxx11::string::string(local_227,(string *)&DAT_0004f56c);
    FUN_0003724c(local_20f,local_22c & 0xffff,fVar1,local_227,local_12d,puVar10,uVar5,uVar4);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(local_12d,local_20f);
    FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
    FUN_0001ae64(local_12d);
    FUN_0001ae64(local_20f);
  }
  else if (((fVar1 <= DAT_00040544) && (0.0 < fVar1)) &&
          (iVar3 = FUN_0001a3ca(),
          fVar1 + *(float *)(local_22c * 0xe0 + *(int *)(iVar3 + 0x5e98) + 0xa0) < fVar2)) {
    iVar3 = FUN_0001a3ca();
    iVar3 = local_22c * 0xe0 + *(int *)(iVar3 + 0x5e98);
    *(float *)(iVar3 + 0xa0) = fVar1 + *(float *)(iVar3 + 0xa0);
    FUN_0003745a(local_12d);
    puVar7 = local_20f;
    for (iVar3 = 0xe2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *(undefined1 *)puVar7 = 0;
      puVar7 = (undefined4 *)((int)puVar7 + (uint)bVar9 * -2 + 1);
    }
    local_227[0] = (string)0xe9;
    iVar3 = FUN_0001a3ca();
    puVar7 = (undefined4 *)(local_22c * 0xe0 + *(int *)(iVar3 + 0x5e98));
    puVar8 = local_20f;
    for (iVar6 = 0x38; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + (uint)bVar9 * -2 + 1;
      puVar8 = puVar8 + (uint)bVar9 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22c,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar4 = FUN_0001e31d();
    FUN_000373be(uVar4,local_227,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 00036523  FUN_00036523
 * bytes: 644  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00036523(undefined4 param_1,int param_2)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  byte bVar8;
  undefined *puVar9;
  uint local_22c;
  string local_227 [24];
  undefined4 local_20f [56];
  undefined1 local_12d [285];

  bVar8 = 0;
  fVar1 = *(float *)(param_2 + 8);
  local_22c = *(uint *)(param_2 + 4);
  iVar2 = FUN_0001a3ca();
  if (*(char *)(*(int *)(iVar2 + 0x5ea8) + local_22c) == '\0') {
    uVar4 = FUN_00033424();
    puVar9 = &DAT_0004f53c;
    uVar3 = uVar4;
    std::__cxx11::string::string(local_227,(string *)&DAT_0004f53c);
    FUN_0003724c(local_20f,local_22c & 0xffff,fVar1,local_227,local_12d,puVar9,uVar4,uVar3);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    FUN_0001f10c(local_12d,local_20f);
    FUN_0001f3ea(PTR_DAT_0004dfcc,local_12d);
    FUN_0001ae64(local_12d);
    FUN_0001ae64(local_20f);
  }
  else if (((fVar1 <= DAT_00040544) && (0.0 < fVar1)) &&
          (iVar2 = FUN_0001a3ca(),
          0.0 <= *(float *)(local_22c * 0xe0 + *(int *)(iVar2 + 0x5e98) + 0xa0) - fVar1)) {
    iVar2 = FUN_0001a3ca();
    iVar2 = local_22c * 0xe0 + *(int *)(iVar2 + 0x5e98);
    *(float *)(iVar2 + 0xa0) = *(float *)(iVar2 + 0xa0) - fVar1;
    FUN_0003745a(local_12d);
    puVar6 = local_20f;
    for (iVar2 = 0xe2; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 *)puVar6 = 0;
      puVar6 = (undefined4 *)((int)puVar6 + (uint)bVar8 * -2 + 1);
    }
    local_227[0] = (string)0xe9;
    iVar2 = FUN_0001a3ca();
    puVar6 = (undefined4 *)(local_22c * 0xe0 + *(int *)(iVar2 + 0x5e98));
    puVar7 = local_20f;
    for (iVar5 = 0x38; iVar5 != 0; iVar5 = iVar5 + -1) {
      *puVar7 = *puVar6;
      puVar6 = puVar6 + (uint)bVar8 * -2 + 1;
      puVar7 = puVar7 + (uint)bVar8 * -2 + 1;
    }
    FUN_00037ae4(local_12d,&local_22c,0x10,1);
    FUN_00037ae4(local_12d,local_20f,0x710,1);
    uVar3 = FUN_0001e31d();
    FUN_000373be(uVar3,local_227,local_12d,0xffff,2);
    FUN_00037562(local_12d);
  }
  return 1;
}



/* ================================================================
 * 00036824  FUN_00036824
 * bytes: 95  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00036824(_State_baseV2 *param_1)

{
  _State_baseV2 *local_2c;
  _State_baseV2 *local_28;
  code *local_24;
  code *local_20;

  local_2c = param_1 + 0x19;
  local_28 = param_1 + 0x1d;
  local_20 = FUN_00033269;
  local_24 = FUN_0003310b;
  std::__future_base::_State_baseV2::_M_set_result(param_1,(_Function_base *)&local_2c,0);
  std::_Function_base::~_Function_base((_Function_base *)&local_2c);
  return;
}



/* ================================================================
 * 00036910  FUN_00036910
 * bytes: 1465  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */
/* WARNING: Type propagation algorithm not settling */

undefined4 FUN_00036910(undefined4 param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int *piVar5;
  _Result_base *this;
  undefined1 uVar6;
  int *extraout_EDX;
  string *psVar7;
  undefined1 *puVar8;
  undefined4 *puVar9;
  int **ppiVar10;
  byte bVar11;
  undefined1 auStack_26c [4];
  string *local_268;
  undefined1 *local_264;
  undefined **local_260;
  undefined1 local_24f;
  undefined2 local_24e;
  int local_24c [4];
  undefined4 local_23b;
  int *local_237;
  int *local_233;
  undefined4 local_22f;
  undefined4 local_22b;
  int *local_227;
  int *local_223 [5];
  undefined1 *local_20f;
  undefined4 local_20b;
  undefined1 local_207 [16];
  undefined1 *local_1f7;
  undefined4 local_1f3;
  undefined1 local_1ef [16];
  undefined1 *local_1df;
  undefined4 local_1db;
  undefined1 local_1d7 [16];
  undefined2 local_1c7;
  undefined4 local_1c5;
  undefined1 local_12d [285];

  bVar11 = 0;
  local_260 = &__DT_PLTGOT;
  local_24c[0] = *(int *)(param_2 + 4);
  iVar3 = *(int *)(param_2 + 8);
  local_24c[1] = 0;
  local_24c[2] = 0;
  local_24e = (undefined2)local_24c[0];
  iVar2 = FUN_0001a3ca();
  local_264 = local_12d;
  local_268 = (string *)&local_20f;
  uVar6 = (undefined1)iVar3;
  if (*(char *)(*(int *)(iVar2 + 0x5ea8) + local_24c[0]) == '\0') {
    FUN_00033424();
    std::__cxx11::string::string((string *)&local_227,(string *)(local_260 + 0x1d0));
    iVar3 = local_24c[0];
    local_20f = local_207;
    local_207[0] = 0;
    local_20b = 0;
    local_1f7 = local_1ef;
    local_1f3 = 0;
    local_1df = local_1d7;
    local_1db = 0;
    local_1ef[0] = 0;
    local_1d7[0] = 0;
    std::__cxx11::string::_M_replace((uint)&local_1f7,0,(char *)0x0,(int)local_260 - 0x146f2);
    *local_1f7 = uVar6;
    local_1c7 = (undefined2)iVar3;
    std::__cxx11::string::_M_assign(local_268);
    std::__cxx11::string::_M_assign((string *)&local_1df);
    std::__cxx11::string::_M_dispose();
    std::__cxx11::string::_M_dispose();
    local_1c5 = param_1;
    FUN_0001f10c();
    FUN_0001f3ea();
    FUN_0001ae64();
    FUN_0001ae64();
  }
  else {
    uVar1 = iVar3 - 0x34;
    if (((byte)uVar1 < 0x1f) && ((0x40040001U >> (uVar1 & 0x1f) & 1) != 0)) {
      iVar3 = FUN_0001a3ca();
      *(undefined1 *)(local_24c[0] * 0xe0 + *(int *)(iVar3 + 0x5e98) + 0x74) = uVar6;
    }
    iVar3 = FUN_0001a3ca();
    local_24c[3] = *(undefined4 *)(local_24c[0] * 0xe0 + *(int *)(iVar3 + 0x5e98) + 0x7c);
    FUN_0003745a();
    local_24f = 0xe9;
    psVar7 = local_268;
    for (iVar3 = 0xe2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *psVar7 = (string)0x0;
      psVar7 = psVar7 + (uint)bVar11 * -2 + 1;
    }
    iVar3 = FUN_0001a3ca();
    puVar9 = (undefined4 *)(local_24c[0] * 0xe0 + *(int *)(iVar3 + 0x5e98));
    psVar7 = local_268;
    for (iVar2 = 0x38; iVar2 != 0; iVar2 = iVar2 + -1) {
      *(undefined1 **)psVar7 = (undefined1 *)*puVar9;
      puVar9 = puVar9 + (uint)bVar11 * -2 + 1;
      psVar7 = psVar7 + (uint)bVar11 * -8 + 4;
    }
    FUN_00037ae4();
    FUN_00037ae4();
    uVar4 = FUN_0001e31d();
    FUN_000373be(uVar4,&local_24f,local_264,0xffff);
    ppiVar10 = &local_237;
    for (iVar3 = 2; iVar3 != 0; iVar3 = iVar3 + -1) {
      *ppiVar10 = (int *)0x0;
      ppiVar10 = ppiVar10 + (uint)bVar11 * -2 + 1;
    }
    local_22f = 0;
    piVar5 = operator_new(0x3d);
    piVar5[1] = 1;
    piVar5[2] = 1;
    piVar5[4] = 0;
    piVar5[5] = 0;
    *piVar5 = (int)(local_260 + -0xe6);
    local_268 = (string *)(piVar5 + 3);
    *(undefined4 *)((int)piVar5 + 0x19) = 0;
    *(undefined4 *)((int)piVar5 + 0x1d) = 0;
    *(undefined4 *)((int)piVar5 + 0x21) = 0;
    *(undefined1 *)(piVar5 + 6) = 0;
    piVar5[3] = (int)(local_260 + -0x68);
    this = operator_new(8);
    *(undefined4 *)this = 0;
    *(undefined4 *)(this + 4) = 0;
    std::__future_base::_Result_base::_Result_base(this);
    *(_Result_base **)((int)piVar5 + 0x25) = this;
    local_23b = 0;
    *(undefined **)this = local_260[-9] + 8;
    *(undefined4 **)((int)piVar5 + 0x29) = &param_1;
    *(int **)((int)piVar5 + 0x2d) = local_24c + 1;
    *(int **)((int)piVar5 + 0x31) = local_24c + 3;
    *(int **)((int)piVar5 + 0x35) = local_24c;
    *(int **)((int)piVar5 + 0x39) = local_24c + 2;
    local_227 = operator_new(0x10);
    *local_227 = (int)(local_260 + -0xdf);
    local_227[1] = (int)local_268;
    local_227[2] = (int)(local_260 + -0x5df4);
    local_227[3] = 0;
    std::thread::_M_start_thread();
    std::unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>>::~unique_ptr
              ((unique_ptr<std::thread::_State,std::default_delete<std::thread::_State>> *)
               &local_227);
    if (*(int *)((int)piVar5 + 0x1d) != 0) {
                    /* WARNING: Subroutine does not return */
      std::terminate();
    }
    *(undefined4 *)((int)piVar5 + 0x1d) = local_23b;
    local_22b = 0;
    local_227 = (int *)0x0;
    local_237 = (int *)local_268;
    local_223[0] = (int *)0x0;
    local_233 = piVar5;
    std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
              ((__shared_count<(__gnu_cxx::_Lock_policy)2> *)local_223);
    std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
              ((__shared_count<(__gnu_cxx::_Lock_policy)2> *)&local_22b);
    local_227 = (int *)local_268;
    if (*(char *)(local_260 + 0x2d1) == '\0') {
      LOCK();
      piVar5[1] = piVar5[1] + 1;
      UNLOCK();
    }
    else {
      piVar5[1] = piVar5[1] + 1;
    }
    psVar7 = local_268;
    puVar8 = auStack_26c;
    local_223[0] = piVar5;
    if (local_268 == (string *)0x0) {
      std::__throw_future_error(3);
      psVar7 = (string *)extraout_EDX;
      puVar8 = &stack0xfffffd84;
    }
    LOCK();
    iVar3 = *(int *)((int)psVar7 + 0xc);
    *(undefined1 *)((int)psVar7 + 0xc) = 1;
    UNLOCK();
    if ((char)iVar3 != '\0') {
      *(undefined4 *)(puVar8 + -0x10) = 1;
      *(undefined4 *)(puVar8 + -0x14) = 0x36d6e;
      uVar4 = std::__throw_future_error(*(int *)(puVar8 + -0x10));
      *(__shared_count<(__gnu_cxx::_Lock_policy)2> **)(puVar8 + -0x20) =
           (__shared_count<(__gnu_cxx::_Lock_policy)2> *)local_223;
      *(undefined4 *)(puVar8 + -0x24) = 0x36d81;
      std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
                (*(__shared_count<(__gnu_cxx::_Lock_policy)2> **)(puVar8 + -0x20));
      *(int ***)(puVar8 + -0x20) = &local_233;
      *(undefined4 *)(puVar8 + -0x24) = 0x36e58;
      std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
                (*(__shared_count<(__gnu_cxx::_Lock_policy)2> **)(puVar8 + -0x20));
      *(undefined1 **)(puVar8 + -0x20) = local_12d;
      *(undefined4 *)(puVar8 + -0x24) = 0x37049;
      FUN_00037562();
      *(undefined4 *)(puVar8 + -0x20) = uVar4;
                    /* WARNING: Subroutine does not return */
      *(undefined **)(puVar8 + -0x24) = &UNK_00037072;
      _Unwind_Resume();
    }
    *(int ***)(puVar8 + -0x10) = &local_233;
    *(undefined4 *)(puVar8 + -0x14) = 0x36d9e;
    std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
              (*(__shared_count<(__gnu_cxx::_Lock_policy)2> **)(puVar8 + -0x10));
    *(__shared_count<(__gnu_cxx::_Lock_policy)2> **)(puVar8 + -0x10) =
         (__shared_count<(__gnu_cxx::_Lock_policy)2> *)local_223;
    *(undefined4 *)(puVar8 + -0x14) = 0x36dac;
    std::__shared_count<(__gnu_cxx::_Lock_policy)2>::~__shared_count
              (*(__shared_count<(__gnu_cxx::_Lock_policy)2> **)(puVar8 + -0x10));
    *(undefined1 **)(puVar8 + -0x10) = local_264;
    *(undefined4 *)(puVar8 + -0x14) = 0x36dbe;
    FUN_00037562();
  }
  return 1;
}



/* ================================================================
 * 00037099  std::__detail::__to_chars_len<unsigned_int>
 * bytes: 86  status: ok
 * ================================================================ */

/* unsigned int std::__detail::__to_chars_len<unsigned int>(unsigned int, int) */

uint std::__detail::__to_chars_len<unsigned_int>(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;

  uVar1 = 1;
  uVar3 = param_2 * param_2 * param_2;
  uVar2 = param_2 * uVar3;
  while( true ) {
    if (param_1 < (uint)param_2) {
      return uVar1;
    }
    if (param_1 < (uint)(param_2 * param_2)) {
      return uVar1 + 1;
    }
    if (param_1 < uVar3) {
      return uVar1 + 2;
    }
    if (param_1 < uVar2) break;
    uVar1 = uVar1 + 4;
    param_1 = param_1 / uVar2;
  }
  return uVar1 + 3;
}



/* ================================================================
 * 000370ef  std::__detail::__to_chars_10_impl<unsigned_int>
 * bytes: 139  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.dx replaced with injection: get_pc_thunk_dx */
/* void std::__detail::__to_chars_10_impl<unsigned int>(char*, unsigned int, unsigned int) */

void std::__detail::__to_chars_10_impl<unsigned_int>(char *param_1,uint param_2,uint param_3)

{
  int iVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  char local_d9 [201];

  pcVar2 =
  "00010203040506070809101112131415161718192021222324252627282930313233343536373839404142434445464748495051525354555657585960616263646566676869707172737475767778798081828384858687888990919293949596979899"
  ;
  pcVar4 = local_d9;
  for (iVar1 = 0xc9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *pcVar4 = *pcVar2;
    pcVar2 = pcVar2 + 1;
    pcVar4 = pcVar4 + 1;
  }
  pcVar2 = param_1 + param_2;
  for (; 99 < param_3; param_3 = param_3 / 100) {
    iVar1 = (param_3 % 100) * 2;
    cVar3 = local_d9[iVar1];
    pcVar2[-1] = local_d9[iVar1 + 1];
    pcVar2[-2] = cVar3;
    pcVar2 = pcVar2 + -2;
  }
  cVar3 = (char)param_3 + '0';
  if (9 < param_3) {
    param_1[1] = local_d9[param_3 * 2 + 1];
    cVar3 = local_d9[param_3 * 2];
  }
  *param_1 = cVar3;
  return;
}



/* ================================================================
 * 0003717a  __gnu_cxx::__to_xstring<std::__cxx11::string,char>
 * bytes: 120  status: ok
 * ================================================================ */

/* std::__cxx11::string __gnu_cxx::__to_xstring<std::__cxx11::string, char>(int (*)(char*, unsigned
   int, char const*, char*), unsigned int, char const*, ...) */

__gnu_cxx * __thiscall
__gnu_cxx::__to_xstring<std::__cxx11::string,char>
          (__gnu_cxx *this,_func_int_char_ptr_uint_char_ptr_char_ptr *param_1,uint param_2,
          char *param_3,...)

{
  int iVar1;
  uint uVar2;
  undefined1 *puVar3;

  for (puVar3 = &stack0xfffffff4; puVar3 != &stack0xfffffff4 + -(param_2 + 0x1b & 0xfffff000);
      puVar3 = puVar3 + -0x1000) {
    *(undefined4 *)(puVar3 + -4) = *(undefined4 *)(puVar3 + -4);
  }
  uVar2 = param_2 + 0x1b & 0xff0;
  iVar1 = -uVar2;
  if (uVar2 != 0) {
    *(undefined4 *)(puVar3 + -4) = *(undefined4 *)(puVar3 + -4);
  }
  *(undefined1 **)(puVar3 + iVar1 + -4) = &stack0x00000014;
  *(char **)(puVar3 + iVar1 + -8) = param_3;
  *(uint *)(puVar3 + iVar1 + -0xc) = param_2;
  *(uint *)(puVar3 + iVar1 + -0x10) = (uint)(puVar3 + iVar1 + 0xf) & 0xfffffff0;
  *(undefined4 *)(puVar3 + iVar1 + -0x14) = 0x371ce;
  (*param_1)(*(char **)(puVar3 + iVar1 + -0x10),*(uint *)(puVar3 + iVar1 + -0xc),
             *(char **)(puVar3 + iVar1 + -8),*(char **)(puVar3 + iVar1 + -4));
  *(__gnu_cxx **)this = this + 8;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(puVar3 + iVar1 + -4) = 0x371e7;
  FUN_0003348e();
  return this;
}



/* ================================================================
 * 000371f2  std::__cxx11::string::_M_construct
 * bytes: 89  status: ok
 * ================================================================ */

/* std::__cxx11::string::_M_construct(unsigned int, char) */

void __thiscall std::__cxx11::string::_M_construct(string *this,uint param_1,char param_2)

{
  undefined4 uVar1;
  uint uVar2;
  char *pcVar3;
  byte bVar4;

  bVar4 = 0;
  if (0xf < param_1) {
    uVar1 = FUN_0003314e();
    *(undefined4 *)this = uVar1;
    *(uint *)(this + 8) = param_1;
  }
  if (param_1 != 0) {
    pcVar3 = *(char **)this;
    uVar2 = param_1;
    if (param_1 == 1) {
      *pcVar3 = param_2;
    }
    else {
      for (; uVar2 != 0; uVar2 = uVar2 - 1) {
        *pcVar3 = param_2;
        pcVar3 = pcVar3 + (uint)bVar4 * -2 + 1;
      }
    }
  }
  *(uint *)(this + 4) = param_1;
  *(undefined1 *)(*(int *)this + param_1) = 0;
  return;
}



/* ================================================================
 * 0003724c  FUN_0003724c
 * bytes: 187  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_0003724c(string *param_1,undefined2 param_2,float param_3)

{
  __gnu_cxx local_34 [36];

  *(undefined4 *)(param_1 + 4) = 0;
  *(string **)param_1 = param_1 + 8;
  *(string **)(param_1 + 0x18) = param_1 + 0x20;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  *(string **)(param_1 + 0x30) = param_1 + 0x38;
  *(undefined4 *)(param_1 + 0x34) = 0;
  param_1[8] = (string)0x0;
  param_1[0x20] = (string)0x0;
  param_1[0x38] = (string)0x0;
  __gnu_cxx::__to_xstring<std::__cxx11::string,char>
            (local_34,(_func_int_char_ptr_uint_char_ptr_char_ptr *)PTR_vsnprintf_0004df44,0x3a,"%f",
             (double)param_3);
  FUN_000335f4();
  std::__cxx11::string::_M_dispose();
  *(undefined2 *)(param_1 + 0x48) = param_2;
  std::__cxx11::string::_M_assign(param_1);
  std::__cxx11::string::_M_assign(param_1 + 0x30);
  return;
}



/* ================================================================
 * 0003733c  FUN_0003733c
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_0003733c(void)

{
  (*(code *)0x80a2390)();
  return;
}



/* ================================================================
 * 00037344  FUN_00037344
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_00037344(void)

{
  (*(code *)0x80a28b0)();
  return;
}



/* ================================================================
 * 0003734c  FUN_0003734c
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_0003734c(void)

{
  (*(code *)0x80a1a80)();
  return;
}



/* ================================================================
 * 00037354  FUN_00037354
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_00037354(void)

{
  (*(code *)0x80a16a0)();
  return;
}



/* ================================================================
 * 0003735c  FUN_0003735c
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_0003735c(void)

{
  (*(code *)0x80a5c80)();
  return;
}



/* ================================================================
 * 00037364  FUN_00037364
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_00037364(void)

{
  (*(code *)0x80a60b0)();
  return;
}



/* ================================================================
 * 0003736c  FUN_0003736c
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_0003736c(void)

{
  (*(code *)0x80a53c0)();
  return;
}



/* ================================================================
 * 00037374  FUN_00037374
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_00037374(void)

{
  (*(code *)0x80a5160)();
  return;
}



/* ================================================================
 * 0003737c  FUN_0003737c
 * bytes: 18  status: ok
 * ================================================================ */

void FUN_0003737c(void)

{
  (*(code *)0x80ae8c0)();
  return;
}



/* ================================================================
 * 0003738e  FUN_0003738e
 * bytes: 25  status: ok
 * ================================================================ */

void FUN_0003738e(void)

{
  (*(code *)0x80ac1d0)();
  return;
}



/* ================================================================
 * 000373a8  FUN_000373a8
 * bytes: 13  status: ok
 * ================================================================ */

undefined4 FUN_000373a8(int param_1)

{
  return **(undefined4 **)(param_1 + 0x40);
}



/* ================================================================
 * 000373b6  FUN_000373b6
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_000373b6(void)

{
  (*(code *)0x80ad590)();
  return;
}



/* ================================================================
 * 000373be  FUN_000373be
 * bytes: 25  status: ok
 * ================================================================ */

void FUN_000373be(void)

{
  (*(code *)0x80abad0)();
  return;
}



/* ================================================================
 * 000373d8  FUN_000373d8
 * bytes: 25  status: ok
 * ================================================================ */

void FUN_000373d8(void)

{
  (*(code *)0x80ac080)();
  return;
}



/* ================================================================
 * 000373f2  FUN_000373f2
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_000373f2(void)

{
  (*(code *)0x80aaf40)();
  return;
}



/* ================================================================
 * 0003741a  FUN_0003741a
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_0003741a(void)

{
  (*(code *)0x814ca20)();
  return;
}



/* ================================================================
 * 00037422  FUN_00037422
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_00037422(void)

{
  (*(code *)0x814af60)();
  return;
}



/* ================================================================
 * 0003743a  FUN_0003743a
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_0003743a(void)

{
  (*(code *)0x814b860)();
  return;
}



/* ================================================================
 * 00037442  FUN_00037442
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_00037442(void)

{
  (*(code *)0x814b700)();
  return;
}



/* ================================================================
 * 0003744a  FUN_0003744a
 * bytes: 7  status: ok
 * ================================================================ */

void FUN_0003744a(void)

{
  (*(code *)0x814b440)();
  return;
}



/* ================================================================
 * 0003745a  FUN_0003745a
 * bytes: 34  status: ok
 * ================================================================ */

void FUN_0003745a(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0x800;
  param_1[2] = 0;
  param_1[3] = (int)param_1 + 0x11;
  *(undefined1 *)(param_1 + 4) = 1;
  return;
}



/* ================================================================
 * 0003747c  FUN_0003747c
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003747c(void)

{
}



/* ================================================================
 * 000374d0  FUN_000374d0
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000374d0(void)

{
}



/* ================================================================
 * 00037554  FUN_00037554
 * bytes: 14  status: ok
 * ================================================================ */

void FUN_00037554(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 4) = param_2;
  return;
}



/* ================================================================
 * 00037562  FUN_00037562
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00037562(void)

{
}



/* ================================================================
 * 00037598  FUN_00037598
 * bytes: 15  status: ok
 * ================================================================ */

void FUN_00037598(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[2] = 0;
  return;
}



/* ================================================================
 * 000375a8  FUN_000375a8
 * bytes: 13  status: ok
 * ================================================================ */

void FUN_000375a8(int param_1)

{
  *(undefined4 *)(param_1 + 8) = 0;
  return;
}



/* ================================================================
 * 000375b6  FUN_000375b6
 * bytes: 12  status: ok
 * ================================================================ */

void FUN_000375b6(undefined4 *param_1)

{
  *param_1 = 0;
  return;
}



/* ================================================================
 * 000375c2  FUN_000375c2
 * bytes: 46  status: ok
 * ================================================================ */

undefined4 FUN_000375c2(int param_1)

{
  byte bVar1;
  int iVar2;
  uint uVar3;

  iVar2 = *(int *)(param_1 + 8);
  bVar1 = *(byte *)(*(int *)(param_1 + 0xc) + (iVar2 >> 3));
  *(int *)(param_1 + 8) = iVar2 + 1;
  uVar3 = 0x80 >> ((byte)iVar2 & 7);
  return CONCAT31((int3)(uVar3 >> 8),(uVar3 & bVar1) != 0);
}



/* ================================================================
 * 000375f0  FUN_000375f0
 * bytes: 25  status: ok
 * ================================================================ */

void FUN_000375f0(int *param_1)

{
  int iVar1;

  iVar1 = *param_1;
  if (iVar1 != 0) {
    *param_1 = (-iVar1 & 7U) + iVar1;
  }
  return;
}



/* ================================================================
 * 0003760a  FUN_0003760a
 * bytes: 27  status: ok
 * ================================================================ */

void FUN_0003760a(int param_1)

{
  int iVar1;

  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 != 0) {
    *(uint *)(param_1 + 8) = (-iVar1 & 7U) + iVar1;
  }
  return;
}



/* ================================================================
 * 00037626  FUN_00037626
 * bytes: 82  status: ok
 * ================================================================ */

undefined4 FUN_00037626(int *param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  undefined1 *puVar2;
  byte bVar3;

  bVar3 = 0;
  if (0 < param_3) {
    FUN_0003760a(param_1);
    iVar1 = param_3 * 8;
    if (param_1[2] + iVar1 <= *param_1) {
      puVar2 = (undefined1 *)((param_1[2] >> 3) + param_1[3]);
      for (; param_3 != 0; param_3 = param_3 + -1) {
        *param_2 = *puVar2;
        puVar2 = puVar2 + (uint)bVar3 * -2 + 1;
        param_2 = param_2 + (uint)bVar3 * -2 + 1;
      }
      param_1[2] = param_1[2] + iVar1;
      return CONCAT31((int3)((uint)iVar1 >> 8),1);
    }
  }
  return 0;
}



/* ================================================================
 * 00037678  FUN_00037678
 * bytes: 18  status: ok
 * ================================================================ */

void FUN_00037678(int param_1,undefined4 param_2)

{
  *(undefined1 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0xc) = param_2;
  return;
}



/* ================================================================
 * 0003768a  FUN_0003768a
 * bytes: 209  status: ok
 * ================================================================ */

undefined4 FUN_0003768a(int *param_1,byte *param_2,int param_3,char param_4)

{
  undefined4 uVar1;
  uint uVar2;
  byte bVar3;
  int iVar4;
  byte *pbVar5;
  byte local_1c;
  sbyte local_14;

  uVar1 = 0;
  if ((0 < param_3) && (param_1[2] + param_3 <= *param_1)) {
    pbVar5 = param_2;
    for (iVar4 = param_3 + 7 >> 3; iVar4 != 0; iVar4 = iVar4 + -1) {
      *pbVar5 = 0;
      pbVar5 = pbVar5 + 1;
    }
    uVar2 = param_1[2] & 7;
    do {
      iVar4 = param_3 + -8;
      local_14 = (sbyte)uVar2;
      bVar3 = *(char *)(param_1[3] + (param_1[2] >> 3)) << local_14 | *param_2;
      *param_2 = bVar3;
      if (uVar2 == 0) {
LAB_00037737:
        if (iVar4 < 0) goto LAB_00037709;
        param_3 = param_1[2] + 8;
      }
      else {
        if ((int)(8 - uVar2) < param_3) {
          local_1c = (byte)(8 - uVar2);
          *param_2 = bVar3 | (byte)((int)(uint)*(byte *)(param_1[3] + 1 + (param_1[2] >> 3)) >>
                                   (local_1c & 0x1f));
          goto LAB_00037737;
        }
LAB_00037709:
        if (param_4 != '\0') {
          *param_2 = (byte)((int)(uint)*param_2 >> (-(char)iVar4 & 0x1fU));
        }
        param_3 = param_3 + param_1[2];
      }
      param_1[2] = param_3;
      param_2 = param_2 + 1;
      param_3 = iVar4;
    } while (0 < iVar4);
    uVar1 = CONCAT31((int3)((uint)param_2 >> 8),1);
  }
  return uVar1;
}



/* ================================================================
 * 0003775c  FUN_0003775c
 * bytes: 80  status: ok
 * ================================================================ */

undefined4 FUN_0003775c(int *param_1,undefined1 *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;

  uVar2 = param_1[2];
  iVar1 = param_3 * 8;
  if ((uVar2 & 7) == 0) {
    uVar3 = 0;
    if ((int)(uVar2 + iVar1) <= *param_1) {
      uVar3 = 1;
      puVar4 = (undefined1 *)(((int)uVar2 >> 3) + param_1[3]);
      for (; param_3 != 0; param_3 = param_3 + -1) {
        *param_2 = *puVar4;
        puVar4 = puVar4 + 1;
        param_2 = param_2 + 1;
      }
      param_1[2] = param_1[2] + iVar1;
    }
  }
  else {
    uVar3 = FUN_0003768a(param_1,param_2,iVar1,1);
  }
  return uVar3;
}



/* ================================================================
 * 000377ac  FUN_000377ac
 * bytes: 205  status: ok
 * ================================================================ */

undefined4 FUN_000377ac(int *param_1,int param_2,int param_3,char param_4)

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  byte *pbVar4;
  int iVar5;
  undefined8 uVar6;
  byte local_30;
  char local_1d [13];

  param_3 = param_3 >> 3;
  local_30 = -(param_4 == '\0') & 0xf0;
  iVar5 = param_3;
  while (iVar5 = iVar5 + -1, 0 < iVar5) {
    uVar6 = FUN_00037e38(param_1,local_1d,param_3,param_3);
    param_3 = (int)((ulonglong)uVar6 >> 0x20);
    if ((char)uVar6 == '\0') {
      return (int)uVar6;
    }
    if (local_1d[0] == '\0') goto LAB_0003785f;
    *(char *)(param_2 + iVar5) = -(param_4 == '\0');
  }
  iVar1 = *param_1;
  if ((param_1[2] < iVar1) && (cVar2 = FUN_00037e38(param_1,local_1d,iVar1,iVar1), cVar2 != '\0')) {
    pbVar4 = (byte *)(param_2 + iVar5);
    if (local_1d[0] == '\0') {
LAB_0003785f:
      uVar3 = FUN_0003768a();
      return uVar3;
    }
    uVar3 = FUN_0003768a(param_1,pbVar4,4,1);
    if ((char)uVar3 != '\0') {
      *pbVar4 = *pbVar4 | local_30;
      return uVar3;
    }
  }
  return 0;
}



/* ================================================================
 * 0003787a  FUN_0003787a
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003787a(void)

{
}



/* ================================================================
 * 0003791c  FUN_0003791c
 * bytes: 149  status: ok
 * ================================================================ */

void FUN_0003791c(uint *param_1,int *param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  byte *pbVar3;
  uint uVar4;

  FUN_0003787a(param_1,param_3);
  while ((0 < param_3 && (iVar1 = param_2[2], iVar1 < *param_2))) {
    uVar2 = *param_1;
    uVar4 = (uint)*(byte *)(param_2[3] + (iVar1 >> 3)) & 0x80 >> ((byte)iVar1 & 7);
    if ((uVar2 & 7) == 0) {
      param_2[2] = iVar1 + 1;
      if (uVar4 == 0) {
        *(undefined1 *)(param_1[3] + ((int)*param_1 >> 3)) = 0;
      }
      else {
        *(undefined1 *)(param_1[3] + ((int)*param_1 >> 3)) = 0x80;
      }
    }
    else {
      param_2[2] = iVar1 + 1;
      if (uVar4 != 0) {
        pbVar3 = (byte *)(((int)*param_1 >> 3) + param_1[3]);
        *pbVar3 = *pbVar3 | (byte)(0x80 >> (sbyte)(uVar2 & 7));
      }
    }
    *param_1 = *param_1 + 1;
    param_3 = param_3 + -1;
  }
  return;
}



/* ================================================================
 * 000379b2  FUN_000379b2
 * bytes: 25  status: ok
 * ================================================================ */

void FUN_000379b2(undefined4 param_1,undefined4 *param_2)

{
  FUN_0003791c(param_1,param_2,*param_2);
  return;
}



/* ================================================================
 * 000379cc  FUN_000379cc
 * bytes: 44  status: ok
 * ================================================================ */

void FUN_000379cc(uint *param_1)

{
  FUN_0003787a(param_1,1);
  if ((*param_1 & 7) == 0) {
    *(undefined1 *)(param_1[3] + ((int)*param_1 >> 3)) = 0;
  }
  *param_1 = *param_1 + 1;
  return;
}



/* ================================================================
 * 000379f8  FUN_000379f8
 * bytes: 63  status: ok
 * ================================================================ */

void __regparm1 FUN_000379f8(undefined4 param_1,uint *param_2)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;

  FUN_0003787a(param_2,1,param_1,param_1);
  iVar2 = (int)*param_2 >> 3;
  uVar3 = *param_2 & 7;
  if (uVar3 == 0) {
    *(undefined1 *)(param_2[3] + iVar2) = 0x80;
  }
  else {
    pbVar1 = (byte *)(param_2[3] + iVar2);
    *pbVar1 = *pbVar1 | (byte)(0x80 >> (sbyte)uVar3);
  }
  *param_2 = *param_2 + 1;
  return;
}



/* ================================================================
 * 00037a38  FUN_00037a38
 * bytes: 171  status: ok
 * ================================================================ */

void __regparm3 FUN_00037a38(uint *param_1,byte *param_2,int param_3,char param_4)

{
  uint uVar1;
  uint uVar2;
  byte *pbVar3;
  byte local_28;
  byte *local_24;
  sbyte local_20;

  FUN_0003787a(param_1,param_3);
  uVar1 = *param_1 & 7;
  local_24 = param_2;
  do {
    if (param_3 < 1) {
      return;
    }
    uVar2 = (uint)*local_24;
    if ((param_3 < 8) && (param_4 != '\0')) {
      uVar2 = uVar2 << (8U - (char)param_3 & 0x1f);
    }
    pbVar3 = (byte *)(((int)*param_1 >> 3) + param_1[3]);
    if (uVar1 == 0) {
      *pbVar3 = (byte)uVar2;
LAB_00037ac3:
      uVar2 = *param_1 + 8;
      if (param_3 < 8) goto LAB_00037acd;
    }
    else {
      local_20 = (sbyte)uVar1;
      *pbVar3 = *pbVar3 | (byte)((int)(uVar2 & 0xff) >> local_20);
      if ((int)(8 - uVar1) < param_3) {
        local_28 = (byte)(8 - uVar1);
        *(char *)(param_1[3] + 1 + ((int)*param_1 >> 3)) =
             (char)((uVar2 & 0xff) << (local_28 & 0x1f));
        goto LAB_00037ac3;
      }
LAB_00037acd:
      uVar2 = *param_1 + param_3;
    }
    local_24 = local_24 + 1;
    param_3 = param_3 + -8;
    *param_1 = uVar2;
  } while( true );
}



/* ================================================================
 * 00037ae4  FUN_00037ae4
 * bytes: 38  status: ok
 * ================================================================ */

void FUN_00037ae4(undefined4 param_1,undefined4 param_2,int param_3,uint param_4)

{
  if (0 < param_3) {
    param_1 = param_4 & 0xff;
    FUN_00037a38();
    return;
  }
  return;
}



/* ================================================================
 * 00037b0a  FUN_00037b0a
 * bytes: 195  status: ok
 * ================================================================ */

void FUN_00037b0a(undefined4 param_1,int param_2,int param_3,char param_4)

{
  byte bVar1;

  param_3 = param_3 >> 3;
  while( true ) {
    param_3 = param_3 + -1;
    bVar1 = *(byte *)(param_2 + param_3);
    if (param_3 < 1) break;
    if ((byte)(param_4 - 1U) != bVar1) {
      FUN_000379cc(param_1);
      FUN_00037ae4();
      return;
    }
    FUN_000379f8(param_1);
  }
  if (param_4 == '\0') {
    if ((~bVar1 & 0xf0) != 0) {
LAB_00037ba5:
      FUN_000379cc(param_1);
      goto LAB_00037bbd;
    }
  }
  else if (0xf < bVar1) goto LAB_00037ba5;
  FUN_000379f8(param_1);
LAB_00037bbd:
  FUN_00037a38();
  return;
}



/* ================================================================
 * 00037bce  FUN_00037bce
 * bytes: 96  status: ok
 * ================================================================ */

void __regparm1 FUN_00037bce(undefined4 param_1,byte *param_2,undefined1 *param_3,int param_4)

{
  int iVar1;
  undefined1 *puVar2;
  byte bVar3;

  bVar3 = 0;
  if ((param_4 != 0) && (param_3 != (undefined1 *)0x0)) {
    iVar1 = param_4 * 8;
    if ((*param_2 & 7) == 0) {
      FUN_0003787a(param_2,iVar1,param_1,param_1);
      puVar2 = (undefined1 *)((*(int *)param_2 + 7 >> 3) + *(int *)(param_2 + 0xc));
      for (; param_4 != 0; param_4 = param_4 + -1) {
        *puVar2 = *param_3;
        param_3 = param_3 + (uint)bVar3 * -2 + 1;
        puVar2 = puVar2 + (uint)bVar3 * -2 + 1;
      }
      *(int *)param_2 = *(int *)param_2 + iVar1;
    }
    else {
      FUN_00037ae4(param_2,param_3,iVar1,1);
    }
  }
  return;
}



/* ================================================================
 * 00037c2e  FUN_00037c2e
 * bytes: 48  status: ok
 * ================================================================ */

void FUN_00037c2e(undefined4 param_1)

{
  FUN_000375f0(param_1);
  FUN_00037bce();
  return;
}



/* ================================================================
 * 00037c5e  FUN_00037c5e
 * bytes: 9  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00037c5e(void)

{
}



/* ================================================================
 * 00037c9c  FUN_00037c9c
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00037c9c(void)

{
}



/* ================================================================
 * 00037d46  FUN_00037d46
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00037d46(void)

{
}



/* ================================================================
 * 00037d92  FUN_00037d92
 * bytes: 14  status: ok
 * ================================================================ */

void FUN_00037d92(int param_1,int param_2)

{
  *(int *)(param_1 + 8) = *(int *)(param_1 + 8) + param_2;
  return;
}



/* ================================================================
 * 00037da0  FUN_00037da0
 * bytes: 13  status: ok
 * ================================================================ */

void FUN_00037da0(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = param_2;
  return;
}



/* ================================================================
 * 00037dae  FUN_00037dae
 * bytes: 11  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00037dae(void)

{
}



/* ================================================================
 * 00037e0c  FUN_00037e0c
 * bytes: 40  status: ok
 * ================================================================ */

void FUN_00037e0c(undefined4 param_1,int param_2,int param_3,int param_4)

{
  int iVar1;

  for (iVar1 = 0; iVar1 < param_4; iVar1 = iVar1 + 1) {
    *(undefined1 *)(param_3 + iVar1) = *(undefined1 *)((param_2 + param_4 + -1) - iVar1);
  }
  return;
}



/* ================================================================
 * 00037e34  FUN_00037e34
 * bytes: 3  status: ok
 * ================================================================ */

undefined4 FUN_00037e34(void)

{
  return 0;
}



/* ================================================================
 * 00037e38  FUN_00037e38
 * bytes: 59  status: ok
 * ================================================================ */

bool FUN_00037e38(int *param_1,undefined4 param_2)

{
  int iVar1;
  byte bVar2;
  int iVar3;

  iVar3 = param_1[2];
  iVar1 = *param_1;
  if (iVar3 < iVar1) {
    bVar2 = *(byte *)(param_1[3] + (iVar3 >> 3));
    param_1[2] = iVar3 + 1;
    *(bool *)param_2 = (0x80 >> ((byte)iVar3 & 7) & (uint)bVar2) != 0;
  }
  return iVar3 < iVar1;
}



/* ================================================================
 * 00037e73  FUN_00037e73
 * bytes: 34  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00037e73(int param_1)

{
  undefined4 uVar1;

  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 4);
  }
  return uVar1;
}



/* ================================================================
 * 00037e95  FUN_00037e95
 * bytes: 34  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00037e95(int param_1)

{
  undefined4 uVar1;

  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 8);
  }
  return uVar1;
}



/* ================================================================
 * 00037eb7  FUN_00037eb7
 * bytes: 34  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00037eb7(int param_1)

{
  undefined4 uVar1;

  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *(undefined4 *)(param_1 + 0x14);
  }
  return uVar1;
}



/* ================================================================
 * 00037ed9  FUN_00037ed9
 * bytes: 33  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00037ed9(undefined4 *param_1)

{
  undefined4 uVar1;

  if (param_1 == (undefined4 *)0x0) {
    uVar1 = 0;
  }
  else {
    uVar1 = *param_1;
  }
  return uVar1;
}



/* ================================================================
 * 00037efa  FUN_00037efa
 * bytes: 25  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_00037efa(undefined4 param_1)

{
  DAT_0004f5e4 = param_1;
  return;
}



/* ================================================================
 * 00037f13  FUN_00037f13
 * bytes: 12  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_00037f13(void)

{
}



/* ================================================================
 * 00037f76  FUN_00037f76
 * bytes: 67  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

int FUN_00037f76(undefined4 param_1,undefined4 param_2)

{
  int iVar1;

  iVar1 = FUN_00016220(0,param_2,7,0x62,0xffffffff,0);
  if (iVar1 == -1) {
    iVar1 = 0;
  }
  return iVar1;
}



/* ================================================================
 * 00037fb9  FUN_00037fb9
 * bytes: 54  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00037fb9(int param_1,undefined4 param_2)

{
  undefined4 uVar1;

  if (param_1 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_000160f0(param_1,param_2);
  }
  return uVar1;
}



/* ================================================================
 * 00037fef  FUN_00037fef
 * bytes: 629  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

int FUN_00037fef(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  byte bVar3;
  byte bVar4;
  bool bVar5;
  int local_14;
  int local_10;
  uint local_c;

  local_10 = 0;
  local_14 = 4;
  bVar5 = false;
  for (local_c = 0; local_c < 0xb; local_c = local_c + 1) {
    if ((*(char *)(param_1 + local_10) == (&DAT_0004e7c0)[local_c]) &&
       (local_10 = local_10 + 1, (&DAT_0004e7c0)[local_c] == 'f')) {
      local_14 = 2;
    }
  }
  local_c = 0;
  do {
    if (0x59 < local_c) {
LAB_0003814b:
      if (bVar5) {
        if ((param_2 != (int *)0x0) && ((*(uint *)(&DAT_0004e7e4 + local_c * 8) & 0x40) != 0)) {
          *param_2 = local_10;
        }
        if ((*(uint *)(&DAT_0004e7e4 + local_c * 8) & 1) != 0) {
          iVar1 = local_10 + 1;
          bVar3 = *(byte *)(param_1 + local_10) >> 6;
          bVar4 = *(byte *)(param_1 + local_10) & 7;
          iVar2 = iVar1;
          if (((bVar3 != 3) && (bVar4 == 4)) &&
             (iVar2 = local_10 + 2, (*(byte *)(param_1 + iVar1) & 7) == 5)) {
            if (bVar3 == 1) {
              iVar2 = local_10 + 3;
            }
            else {
              iVar2 = local_10 + 6;
            }
          }
          local_10 = iVar2;
          if (bVar3 == 1) {
            local_10 = local_10 + 1;
          }
          if ((bVar3 == 2) || ((bVar3 == 0 && (bVar4 == 5)))) {
            local_10 = local_10 + 4;
          }
        }
        if ((*(uint *)(&DAT_0004e7e4 + local_c * 8) & 8) != 0) {
          local_10 = local_10 + 1;
        }
        if ((*(uint *)(&DAT_0004e7e4 + local_c * 8) & 0x10) != 0) {
          local_10 = local_10 + 2;
        }
        if ((*(uint *)(&DAT_0004e7e4 + local_c * 8) & 0x20) != 0) {
          local_10 = local_10 + local_14;
        }
      }
      else {
        local_10 = 0;
      }
      return local_10;
    }
    if (*(char *)(param_1 + local_10) == (&DAT_0004e7e0)[local_c * 8]) {
      if ((*(uint *)(&DAT_0004e7e4 + local_c * 8) & 4) == 0) {
        bVar5 = true;
      }
      else {
        bVar5 = (*(byte *)(param_1 + local_10 + 1) >> 3 & 7) == (&DAT_0004e7e1)[local_c * 8];
      }
    }
    if (((*(uint *)(&DAT_0004e7e4 + local_c * 8) & 2) != 0) &&
       ((*(byte *)(param_1 + local_10) & 0xf8) == (&DAT_0004e7e0)[local_c * 8])) {
      bVar5 = true;
    }
    if (bVar5) {
      local_10 = local_10 + 1;
      goto LAB_0003814b;
    }
    local_c = local_c + 1;
  } while( true );
}



/* ================================================================
 * 00038264  FUN_00038264
 * bytes: 20  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00038264(void)

{
  return 5;
}



/* ================================================================
 * 00038278  FUN_00038278
 * bytes: 66  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_00038278(undefined1 *param_1,int param_2)

{
  *param_1 = 0xe9;
  *(int *)(param_1 + 1) = (param_2 - (int)param_1) + -5;
  return 0;
}



/* ================================================================
 * 000382ba  FUN_000382ba
 * bytes: 29  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

void FUN_000382ba(undefined4 param_1,undefined4 param_2)

{
  FUN_00038278(param_1,param_2);
  return;
}



/* ================================================================
 * 000382d7  FUN_000382d7
 * bytes: 12  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000382d7(void)

{
}



/* ================================================================
 * 0003840b  FUN_0003840b
 * bytes: 13  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_0003840b(void)

{
}



/* ================================================================
 * 000385fc  FUN_000385fc
 * bytes: 12  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.bx replaced with injection: get_pc_thunk_bx */

void FUN_000385fc(void)

{
}



/* ================================================================
 * 00038655  FUN_00038655
 * bytes: 104  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

int FUN_00038655(int *param_1)

{
  int iVar1;

  if (param_1 == (int *)0x0) {
    iVar1 = -0x16;
  }
  else if (*param_1 == 0) {
    iVar1 = FUN_000382ba(param_1[1],param_1[2],param_1[3]);
    if (-1 < iVar1) {
      *param_1 = 1;
      iVar1 = 0;
    }
  }
  else {
    iVar1 = -0x16;
  }
  return iVar1;
}



/* ================================================================
 * 000386bd  FUN_000386bd
 * bytes: 99  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

undefined4 FUN_000386bd(int *param_1)

{
  undefined4 uVar1;

  if (param_1 == (int *)0x0) {
    uVar1 = 0xffffffea;
  }
  else if (*param_1 == 0) {
    uVar1 = 0xffffffea;
  }
  else {
    memcpy((void *)param_1[1],(void *)param_1[4],param_1[6]);
    *param_1 = 0;
    uVar1 = 0;
  }
  return uVar1;
}



/* ================================================================
 * 00038720  FUN_00038720
 * bytes: 57  status: ok
 * ================================================================ */

/* WARNING: Function: __i686.get_pc_thunk.ax replaced with injection: get_pc_thunk_ax */

char * FUN_00038720(char *param_1)

{
  if (*param_1 == -0x17) {
    param_1 = param_1 + *(int *)(param_1 + 1) + 5;
  }
  else {
    param_1 = (char *)0x0;
  }
  return param_1;
}



/* ================================================================
 * 00050000  <EXTERNAL>::std::__cxx11::string::_M_replace_cold
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__cxx11::string::_M_replace_cold
               (char *param_1,uint param_2,char *param_3,uint param_4,uint param_5)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050004  <EXTERNAL>::putchar
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int putchar(int __c)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050008  <EXTERNAL>::clock_gettime
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int clock_gettime(clockid_t __clock_id,timespec *__tp)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005000c  <EXTERNAL>::operator.new[]
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * operator_new__(uint param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050010  <EXTERNAL>::std::operator<<
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ostream * std::operator<<(ostream *param_1,char *param_2)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050018  <EXTERNAL>::__cxa_rethrow
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __cxa_rethrow(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005001c  <EXTERNAL>::__strcpy_chk
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __strcpy_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050020  <EXTERNAL>::sysconf
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

long sysconf(int __name)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050024  <EXTERNAL>::std::future_error::~future_error
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::future_error::~future_error(future_error *this)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050028  <EXTERNAL>::std::__throw_future_error
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_future_error(int param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005002c  <EXTERNAL>::strerror
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strerror(int __errnum)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050030  <EXTERNAL>::memmove
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memmove(void *__dest,void *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050034  <EXTERNAL>::munmap
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int munmap(void *__addr,size_t __len)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050038  <EXTERNAL>::std::ios_base_library_init
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */
/* std::ios_base_library_init() */

void std::ios_base_library_init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005003c  <EXTERNAL>::getenv
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * getenv(char *__name)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050040  <EXTERNAL>::bsearch
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * bsearch(void *__key,void *__base,size_t __nmemb,size_t __size,__compar_fn_t __compar)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050044  <EXTERNAL>::memcpy
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memcpy(void *__dest,void *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050048  <EXTERNAL>::pthread_cancel
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_cancel(pthread_t __th)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005004c  <EXTERNAL>::puts
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int puts(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050054  <EXTERNAL>::malloc
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * malloc(size_t __size)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050058  <EXTERNAL>::__isoc23_strtol
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __isoc23_strtol(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005005c  <EXTERNAL>::std::condition_variable::wait
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::condition_variable::wait(unique_lock *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050064  <EXTERNAL>::std::__throw_bad_alloc
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_bad_alloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050068  <EXTERNAL>::dladdr
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void dladdr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050070  <EXTERNAL>::mmap
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * mmap(void *__addr,size_t __len,int __prot,int __flags,int __fd,__off_t __offset)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050074  <EXTERNAL>::std::__throw_length_error
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_length_error(char *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050078  <EXTERNAL>::std::__future_base::_Result_base::_Result_base
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::__future_base::_Result_base::_Result_base(_Result_base *this)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005007c  <EXTERNAL>::__cxa_end_catch
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __cxa_end_catch(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050080  <EXTERNAL>::std::condition_variable::notify_one
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::condition_variable::notify_one(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050084  <EXTERNAL>::std::terminate
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::terminate(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050088  <EXTERNAL>::std::thread::hardware_concurrency
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::thread::hardware_concurrency(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005008c  <EXTERNAL>::std::_V2::generic_category
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::_V2::generic_category(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050090  <EXTERNAL>::nanosleep
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int nanosleep(timespec *__requested_time,timespec *__remaining)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005009c  <EXTERNAL>::calloc
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * calloc(size_t __nmemb,size_t __size)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500a4  <EXTERNAL>::atof
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

double atof(char *__nptr)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500a8  <EXTERNAL>::operator.delete
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void operator_delete(void *param_1,uint param_2)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500ac  <EXTERNAL>::std::ostream::operator<<
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::ostream::operator<<(ostream *this,_func_ios_base_ptr_ios_base_ptr *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500b0  <EXTERNAL>::__cxa_init_primary_exception
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __cxa_init_primary_exception(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500b4  <EXTERNAL>::pthread_once
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_once(pthread_once_t *__once_control,__init_routine *__init_routine)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500b8  <EXTERNAL>::_Unwind_Resume
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void _Unwind_Resume(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500bc  <EXTERNAL>::std::ostream::operator<<
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::ostream::operator<<(ostream *this,short param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500c0  <EXTERNAL>::std::logic_error::logic_error
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::logic_error::logic_error(logic_error *this,logic_error *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500c4  <EXTERNAL>::std::thread::join
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::thread::join(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500c8  <EXTERNAL>::std::ostream::operator<<
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::ostream::operator<<(ostream *this,int param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500cc  <EXTERNAL>::dlopen
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void dlopen(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500d4  <EXTERNAL>::strncpy
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

char * strncpy(char *__dest,char *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500d8  <EXTERNAL>::__cxa_throw_bad_array_new_length
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __cxa_throw_bad_array_new_length(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500dc  <EXTERNAL>::std::__throw_bad_array_new_length
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_bad_array_new_length(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500e0  <EXTERNAL>::realloc
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * realloc(void *__ptr,size_t __size)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500e4  <EXTERNAL>::__cxa_atexit
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __cxa_atexit(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500e8  <EXTERNAL>::std::__detail::_Prime_rehash_policy::_M_need_rehash
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__detail::_Prime_rehash_policy::_M_need_rehash(uint param_1,uint param_2,uint param_3)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500ec  <EXTERNAL>::memcmp
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int memcmp(void *__s1,void *__s2,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500f0  <EXTERNAL>::__vprintf_chk
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __vprintf_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500f4  <EXTERNAL>::dlsym
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void dlsym(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 000500f8  <EXTERNAL>::std::__throw_logic_error
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_logic_error(char *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050100  <EXTERNAL>::__snprintf_chk
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __snprintf_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050104  <EXTERNAL>::std::__throw_bad_function_call
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_bad_function_call(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050108  <EXTERNAL>::operator.delete[]
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void operator_delete__(void *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005010c  <EXTERNAL>::__memcpy_chk
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __memcpy_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050110  <EXTERNAL>::std::future_category
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::future_category(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050114  <EXTERNAL>::__assert_fail
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void __assert_fail(char *__assertion,char *__file,uint __line,char *__function)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050118  <EXTERNAL>::strcmp
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int strcmp(char *__s1,char *__s2)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005011c  <EXTERNAL>::pthread_mutex_unlock
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_unlock(pthread_mutex_t *__mutex)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050120  <EXTERNAL>::std::condition_variable::~condition_variable
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::condition_variable::~condition_variable(condition_variable *this)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050128  <EXTERNAL>::std::__atomic_futex_unsigned_base::_M_futex_notify_all
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__atomic_futex_unsigned_base::_M_futex_notify_all(uint *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050138  <EXTERNAL>::std::__future_base::_Result_base::~_Result_base
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::__future_base::_Result_base::~_Result_base(_Result_base *this)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005013c  <EXTERNAL>::pthread_self
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

pthread_t pthread_self(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050140  <EXTERNAL>::__cxa_begin_catch
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __cxa_begin_catch(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050144  <EXTERNAL>::std::thread::detach
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::thread::detach(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050148  <EXTERNAL>::__cxa_allocate_exception
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __cxa_allocate_exception(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005014c  <EXTERNAL>::std::endl<char,std::char_traits<char>>
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

ostream * std::endl<char,std::char_traits<char>>(ostream *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050150  <EXTERNAL>::pthread_mutex_lock
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int pthread_mutex_lock(pthread_mutex_t *__mutex)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050154  <EXTERNAL>::__divmoddi4
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __divmoddi4(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005015c  <EXTERNAL>::std::thread::_State::~_State
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::thread::_State::~_State(_State *this)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050160  <EXTERNAL>::operator.new
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * operator_new(uint param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050164  <EXTERNAL>::__errno_location
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int * __errno_location(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005016c  <EXTERNAL>::atoi
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int atoi(char *__nptr)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050170  <EXTERNAL>::__vsnprintf_chk
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __vsnprintf_chk(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050174  <EXTERNAL>::std::__exception_ptr::exception_ptr::_M_release
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__exception_ptr::exception_ptr::_M_release(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050178  <EXTERNAL>::___tls_get_addr
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void ___tls_get_addr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005017c  <EXTERNAL>::strlen
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

size_t strlen(char *__s)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050180  <EXTERNAL>::std::__exception_ptr::exception_ptr::exception_ptr
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall
std::__exception_ptr::exception_ptr::exception_ptr(exception_ptr *this,void *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050184  <EXTERNAL>::std::condition_variable::condition_variable
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::condition_variable::condition_variable(condition_variable *this)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050188  <EXTERNAL>::mprotect
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int mprotect(void *__addr,size_t __len,int __prot)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005018c  <EXTERNAL>::std::logic_error::logic_error
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void __thiscall std::logic_error::logic_error(logic_error *this,string *param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050190  <EXTERNAL>::std::current_exception
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::current_exception(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050194  <EXTERNAL>::std::__throw_system_error
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void std::__throw_system_error(int param_1)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 00050198  <EXTERNAL>::std::thread::_M_start_thread
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */

void std::thread::_M_start_thread(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}



/* ================================================================
 * 0005019c  <EXTERNAL>::free
 * bytes: 1  status: ok
 * ================================================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void free(void *__ptr)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}
