param(
    [Parameter(Mandatory = $true)] [string] $Source,
    [Parameter(Mandatory = $true)] [string] $Output
)

$ErrorActionPreference = "Stop"

# ProperRadar's 96x96 dictionary is ideal while streets are large on screen,
# but its full-map hook issues thousands of tiny draws at overview scale. On
# expanded maps that renderer eventually emits the flickering black columns we
# have captured. The source textures themselves are healthy, so preserve their
# DXT1 blocks exactly and pack them into one overview texture. No resampling and
# no lossy recompression happens here.
$tilesAcross = 96
$tilePixels = 32
$blocksPerTile = $tilePixels / 4
$atlasPixels = $tilesAcross * $tilePixels
$atlasBlocks = $atlasPixels / 4
$blockBytes = 8
$tileBytes = $blocksPerTile * $blocksPerTile * $blockBytes
$atlasBytes = $atlasBlocks * $atlasBlocks * $blockBytes

$sourceBytes = [IO.File]::ReadAllBytes($Source)
if ($sourceBytes.Length -lt 0x300 -or
    [BitConverter]::ToUInt32($sourceBytes, 0) -ne 0x16) {
    throw "Not a RenderWare texture dictionary: $Source"
}

$count = [BitConverter]::ToUInt16($sourceBytes, 0x18)
if ($count -ne $tilesAcross * $tilesAcross) {
    throw "ProperRadar atlas has $count textures; expected 9216"
}

$atlas = New-Object byte[] $atlasBytes
$seen = New-Object bool[] $count
$chunk = 0x1C

for ($entry = 0; $entry -lt $count; $entry++) {
    if ([BitConverter]::ToUInt32($sourceBytes, $chunk) -ne 0x15) {
        throw ("Texture chunk {0} is invalid at 0x{1:X}" -f $entry, $chunk)
    }

    $name = [Text.Encoding]::ASCII.GetString($sourceBytes, $chunk + 0x20, 32).TrimEnd([char]0)
    if ($name -notmatch '^radar([0-9]+)$') {
        throw "Unexpected ProperRadar texture name '$name'"
    }
    $index = [int] $Matches[1]
    if ($index -lt 0 -or $index -ge $count -or $seen[$index]) {
        throw "Duplicate or invalid ProperRadar texture index $index"
    }

    $width = [BitConverter]::ToUInt16($sourceBytes, $chunk + 0x68)
    $height = [BitConverter]::ToUInt16($sourceBytes, $chunk + 0x6A)
    $size = [BitConverter]::ToUInt32($sourceBytes, $chunk + 0x70)
    if ($width -ne $tilePixels -or $height -ne $tilePixels -or $size -ne $tileBytes) {
        throw "Texture $name is not a 32x32 DXT1 tile"
    }

    $tileX = $index % $tilesAcross
    $tileY = [Math]::Floor($index / $tilesAcross)
    $sourceData = $chunk + 0x74
    for ($blockY = 0; $blockY -lt $blocksPerTile; $blockY++) {
        $sourceRow = $sourceData + $blockY * $blocksPerTile * $blockBytes
        $destRow = (($tileY * $blocksPerTile + $blockY) * $atlasBlocks +
                    $tileX * $blocksPerTile) * $blockBytes
        [Array]::Copy($sourceBytes, $sourceRow, $atlas, $destRow,
                      $blocksPerTile * $blockBytes)
    }

    $seen[$index] = $true
    $chunk += 12 + [BitConverter]::ToUInt32($sourceBytes, $chunk + 4)
}

if ($seen -contains $false) {
    throw "ProperRadar atlas is missing one or more numbered textures"
}

# Reuse the original dictionary/native-texture headers and extension chunks so
# every RenderWare flag stays byte-for-byte compatible with Eagle. Only the
# count, chunk sizes, name, dimensions, and DXT payload change.
$header = New-Object byte[] 0x90
[Array]::Copy($sourceBytes, 0, $header, 0, $header.Length)
$nativeExtension = New-Object byte[] 12
[Array]::Copy($sourceBytes, 0x90 + $tileBytes,
              $nativeExtension, 0, $nativeExtension.Length)
$dictionaryExtension = New-Object byte[] 12
[Array]::Copy($sourceBytes, $sourceBytes.Length - 12,
              $dictionaryExtension, 0, $dictionaryExtension.Length)

$totalSize = $header.Length + $atlas.Length +
             $nativeExtension.Length + $dictionaryExtension.Length
[BitConverter]::GetBytes([uint32]($totalSize - 12)).CopyTo($header, 4)
[BitConverter]::GetBytes([uint16]1).CopyTo($header, 0x18)
[BitConverter]::GetBytes([uint32]($atlas.Length + 0x74)).CopyTo($header, 0x20)
[BitConverter]::GetBytes([uint32]($atlas.Length + 0x5C)).CopyTo($header, 0x2C)

[Array]::Clear($header, 0x3C, 64)
$nameBytes = [Text.Encoding]::ASCII.GetBytes("sprp_overview")
[Array]::Copy($nameBytes, 0, $header, 0x3C, $nameBytes.Length)
[BitConverter]::GetBytes([uint16]$atlasPixels).CopyTo($header, 0x84)
[BitConverter]::GetBytes([uint16]$atlasPixels).CopyTo($header, 0x86)
[BitConverter]::GetBytes([uint32]$atlas.Length).CopyTo($header, 0x8C)

$parent = Split-Path -Parent $Output
if ($parent -and -not (Test-Path -LiteralPath $parent)) {
    New-Item -ItemType Directory -Path $parent | Out-Null
}

$stream = [IO.File]::Open($Output, [IO.FileMode]::Create,
                          [IO.FileAccess]::Write, [IO.FileShare]::None)
try {
    $stream.Write($header, 0, $header.Length)
    $stream.Write($atlas, 0, $atlas.Length)
    $stream.Write($nativeExtension, 0, $nativeExtension.Length)
    $stream.Write($dictionaryExtension, 0, $dictionaryExtension.Length)
} finally {
    $stream.Dispose()
}

Write-Host "[build] $Output  ($atlasPixels x $atlasPixels, one DXT1 overview texture)" -ForegroundColor Green
