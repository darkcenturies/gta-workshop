$ErrorActionPreference = 'Stop'
$source = $PSScriptRoot
$root = Split-Path $source -Parent
$csc = 'C:\Windows\Microsoft.NET\Framework\v4.0.30319\csc.exe'
$suite = Split-Path $root -Parent
& (Join-Path $suite 'build.ps1') -OnlyTarget doctor-valkyrie -Release
Copy-Item -LiteralPath (Join-Path $suite 'build/doctor-valkyrie.asi') -Destination (Join-Path $source 'doctor-valkyrie.asi')
Copy-Item -LiteralPath (Join-Path $suite 'doctor-valkyrie/doctor-valkyrie.txt') -Destination (Join-Path $source 'doctor-valkyrie.txt')
$common = @(
    '/nologo','/optimize+','/platform:x86',
    '/reference:System.dll','/reference:System.Core.dll',
    '/reference:System.Drawing.dll','/reference:System.Windows.Forms.dll',
    ('/win32manifest:' + (Join-Path $source 'app.manifest'))
)
$names = @('doctor-ssmp.bmp','sprp-logo.png','banner-stop.png','banner-thinking.png','banner-unsure.png','banner-yay.png','doctor-valkyrie.asi','doctor-valkyrie.txt','CrashList.txt')
$resources = $names | ForEach-Object { '/resource:' + (Join-Path $source $_) + ',' + $_ }
$sources = @('Program.cs','DoctorSupport.cs','Engine.cs','CrashfixSupport.cs','MainForm.cs','SelfTests.cs') | ForEach-Object { Join-Path $source $_ }
$output = Join-Path $root 'valkyrie-repair.exe'
& $csc @common '/target:winexe' ('/out:' + $output) @resources @sources
if ($LASTEXITCODE -ne 0) { throw 'Valkyrie Repair build failed' }

$test = Join-Path $suite 'build/valkyrie-repair-self-test.exe'
& $csc @common '/define:VALKYRIE_TEST' '/target:exe' ('/out:' + $test) @resources @sources
if ($LASTEXITCODE -ne 0) { throw 'Valkyrie Repair test build failed' }
& $test --self-test
if ($LASTEXITCODE -ne 0) { throw 'Valkyrie Repair self-tests failed' }
Get-Item $output | Select-Object FullName,Length,LastWriteTime
