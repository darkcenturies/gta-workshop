param(
    [Parameter(Mandatory=$true)][string] $Asi,
    [string] $Graph,
    [string] $StockGraph,
    [string] $EagleGraph,
    [Parameter(Mandatory=$true)][string] $Output
)
$ErrorActionPreference = 'Stop'
$asiBytes = [IO.File]::ReadAllBytes((Resolve-Path -LiteralPath $Asi))
$universal = $StockGraph -and $EagleGraph
if (-not $universal -and -not $Graph) { throw 'Pass -Graph, or both -StockGraph and -EagleGraph.' }
$graphs = if ($universal) { @($StockGraph, $EagleGraph) } else { @($Graph) }
$graphBytes = @($graphs | ForEach-Object {
    $bytes = [IO.File]::ReadAllBytes((Resolve-Path -LiteralPath $_))
    if ($bytes.Length -lt 16 -or [Text.Encoding]::ASCII.GetString($bytes, 0, 4) -ne 'SPVG') {
        throw "The road graph is invalid: $_"
    }
    ,$bytes
})
$magic = [Text.Encoding]::ASCII.GetBytes($(if ($universal) { 'VKRGRPH2' } else { 'VKRGRPH1' }))
$pending = "$Output.$([Guid]::NewGuid().ToString('N')).tmp"
$stream = [IO.File]::Open($pending, [IO.FileMode]::CreateNew, [IO.FileAccess]::Write)
try {
    $stream.Write($asiBytes, 0, $asiBytes.Length)
    foreach ($bytes in $graphBytes) { $stream.Write($bytes, 0, $bytes.Length) }
    $stream.Write($magic, 0, $magic.Length)
    foreach ($bytes in $graphBytes) {
        $size = [BitConverter]::GetBytes([uint32]$bytes.Length)
        $stream.Write($size, 0, $size.Length)
    }
} finally {
    $stream.Dispose()
}
Move-Item -LiteralPath $pending -Destination $Output -Force
