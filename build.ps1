# Public build entry point. Calls only the released projects listed below.
[CmdletBinding()]
param(
    [ValidateSet('all', 'map', 'doctor', 'crashfix', 'repair')]
    [string] $Target = 'all',
    [switch] $Release,
    [switch] $CheckEnvironment,
    [switch] $List
)

$ErrorActionPreference = 'Stop'
$targets = if ($Target -eq 'all') { @('map', 'doctor', 'repair') } else { @(if ($Target -eq 'crashfix') { 'doctor' } else { $Target }) }
$outputs = @{
    map = 'client/valkyrie-asi-suite/build/valkyrie-map.asi'
    doctor = 'client/valkyrie-asi-suite/build/doctor-valkyrie.asi'
    crashfix = 'client/valkyrie-asi-suite/build/doctor-valkyrie.asi'
    repair = 'client/valkyrie-asi-suite/valkyrie-repair/valkyrie-repair.exe'
}
if ($List) {
    $targets | ForEach-Object { [pscustomobject]@{Target = $_; Output = $outputs[$_]} }
    return
}

if ([Environment]::OSVersion.Platform -ne [PlatformID]::Win32NT) {
    throw 'Building the mods requires Windows. Research and archive checks also run on Linux/macOS.'
}
if (@($targets | Where-Object { $_ -ne 'repair' }).Count -gt 0) {
    $vswhere = Join-Path ${env:ProgramFiles(x86)} 'Microsoft Visual Studio/Installer/vswhere.exe'
    if (-not (Test-Path -LiteralPath $vswhere)) {
        throw 'Install Visual Studio Build Tools with Desktop development with C++ and a Windows SDK; see docs/BUILDING.md.'
    }
    $vs = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
    if (-not $vs -or -not (Test-Path -LiteralPath (Join-Path $vs 'VC/Auxiliary/Build/vcvarsall.bat'))) {
        throw 'The MSVC x86/x64 C++ tools are missing. Modify the installation using Visual Studio Installer; see docs/BUILDING.md.'
    }
    Write-Host "C++ toolchain found: $vs"
}
if ('repair' -in $targets) {
    $csc = Join-Path $env:WINDIR 'Microsoft.NET/Framework/v4.0.30319/csc.exe'
    if (-not (Test-Path -LiteralPath $csc)) { throw 'Repair requires .NET Framework 4.x with csc.exe; see docs/BUILDING.md.' }
    Write-Host "Repair compiler found: $csc"
}
if ($CheckEnvironment) {
    Write-Host 'Compiler entry points found. A build verifies Windows SDK headers, libraries and resource tools.'
    return
}

# Existing compilers/tests can write intermediate files into their working directory.
$scratch = Join-Path $PSScriptRoot 'work/build-run'
New-Item -ItemType Directory -Path $scratch -Force | Out-Null
Push-Location $scratch
try {
    foreach ($item in $targets) {
        Write-Host "[public-build] $item"
        switch ($item) {
            'map' { & (Join-Path $PSScriptRoot 'client/valkyrie-asi-suite/build.ps1') -OnlyTarget valkyrie-map -Release:$Release }
            'doctor' { & (Join-Path $PSScriptRoot 'client/valkyrie-asi-suite/build.ps1') -OnlyTarget doctor-valkyrie -Release:$Release }
            'crashfix' { & (Join-Path $PSScriptRoot 'client/valkyrie-asi-suite/valkyrie-crashfix/src/build.ps1') }
            'repair' { & (Join-Path $PSScriptRoot 'client/valkyrie-asi-suite/valkyrie-repair/src/build.ps1') }
        }
        $artifact = Join-Path $PSScriptRoot $outputs[$item]
        if (-not (Test-Path -LiteralPath $artifact -PathType Leaf)) { throw "Missing build output: $artifact" }
        Write-Host "[public-build] output: $artifact"
    }
} finally {
    Pop-Location
}
