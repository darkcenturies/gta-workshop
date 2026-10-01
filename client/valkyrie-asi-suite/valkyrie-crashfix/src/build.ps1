# Doctor and Crashfix ship as one ASI; this compatibility entry point builds it.
$ErrorActionPreference = 'Stop'
& (Join-Path $PSScriptRoot '../../build.ps1') -OnlyTarget doctor-valkyrie -Release
