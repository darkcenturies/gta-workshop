@echo off
setlocal
where cl >nul 2>nul
if errorlevel 1 (
  echo Use an x86 Visual Studio Native Tools Command Prompt.
  exit /b 1
)
if /I not "%VSCMD_ARG_TGT_ARCH%"=="x86" (
  echo Select the x86 compiler environment.
  exit /b 1
)
if not exist "%~dp0build" mkdir "%~dp0build"
pushd "%~dp0build"
cl /nologo /O2 /MT /W4 /c /I..\minhook\include ..\minhook\src\buffer.c ..\minhook\src\hook.c ..\minhook\src\trampoline.c ..\minhook\src\hde\hde32.c
if errorlevel 1 goto failed
cl /nologo /O2 /MT /EHsc /W4 /LD ..\Adapter.cpp buffer.obj hook.obj trampoline.obj hde32.obj /Fe:!PE-DL-Adapter.asi /link advapi32.lib user32.lib
if errorlevel 1 goto failed
popd
exit /b 0
:failed
popd
exit /b 1
