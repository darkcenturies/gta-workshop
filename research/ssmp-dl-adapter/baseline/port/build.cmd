@echo off
setlocal
where cl >nul 2>nul
if errorlevel 1 exit /b 1
if /I not "%VSCMD_ARG_TGT_ARCH%"=="x86" exit /b 1
if not exist "%~dp0build" mkdir "%~dp0build"
pushd "%~dp0build"
cl /nologo /O2 /MT /EHsc /W4 /LD ..\Guard.cpp /Fe:Valkyrie-DL-Guard.dll /link advapi32.lib user32.lib
set "buildResult=%errorlevel%"
popd
exit /b %buildResult%
