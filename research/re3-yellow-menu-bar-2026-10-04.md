# GTA III re3 main/pause menu yellow strip

## Question and target

Can the wide yellow strip behind the bottom pause-menu page title be removed
without replacing the engine executable or changing menu navigation?

Inspected re3 source revision
`9a7fa478578beaba947ea867c15a25e411d641d8`, Windows x64 D3D9, with
independently supplied GTA III menu assets. The local executable SHA-256 was
`041d907d13395cca54ffb550bdd34f1ca585e470c1c87a3450de30ac8726732d`.
This exact target observation does not establish original GTA III binary-hook
compatibility, other re3 builds, PS2-style menus or other language files.

## Observations

The main/pause background is the texture named `mainmenu24` in `menu.txd`.
The yellow strip is baked into its pixels. Merely suppressing a rectangle
draw does not remove the strip. There is also an explicit yellow rectangle
in the frontend's red delete-background branch, which is a different case.

Page titles are drawn separately through `CFont::PrintString`. The pause and
start screens reference GXT keys `FET_PAU` and `FEM_MM`. The engine's American
English language loads `AMERICAN.GXT`; an accompanying legacy `ENGLISH.GXT`
can have a different key set and is not selected by this frontend.

The inspected native texture had platform ID 8, raster format `0x600`,
512 by 512 pixels, 32-bit raw BGRA, one level, raster type 4 and no compression.
GXT key entries were 12 bytes: a 32-bit TDAT offset and an eight-byte key.
Blanking each target's first UTF-16 code unit retains dictionary lengths,
key offsets and the menu's header-layout branch.

## Method and actual validation

The graphics/native routes and Dryxio reference catalog were consulted.
The exact-target re3 frontend and text loader provided applicable evidence.
CLEO AI, San Andreas SDKs, Ghidra and native hook tools were not executed;
the selected route was an asset edit with no runtime hook or engine rebuild.
The texture method family was consulted, but its legacy tools were not run.

A private builder parsed bounded RenderWare chunks, identified exactly one
mainmenu24 texture, checked its original payload hash and encoding, replaced
its RGB pixel payload, and preserved all alpha bytes and every other byte of
the dictionary. It also validated unshared GXT text offsets before blanking
the two titles. No game inputs or mod implementation are included here.

Two built-in image generation edits were evaluated. Cropping a generated
43-pixel restoration into the original texture left visible palette and
contour seams. The final version used the complete retouched background;
it has small artwork differences and is an approximation, not recovery of
the obscured original source art. The other textures, including nine map
tiles, stayed byte-identical. This negative result matters when pixel-exact
preservation is required: generated inpainting must be checked after actual
asset composition, not just as a standalone image.

Python 3.11 and Pillow package generation passed. The 10,244,648-byte TXD
changed at 747,275 byte positions, all inside the selected texture's RGB
payload. The 220,708-byte American GXT changed at only two byte positions.
Python compilation and PowerShell syntax parsing passed. Installation and
restoration against copied local fixtures recovered both original file
hashes exactly. A repeated restore and a different artwork input were
refused before writing. The exported texture was visually inspected.

The initial package used direct root-file replacement. A subsequent owner
instruction required all content mods to load through Mod Loader. The asset
package was revised to use an ordinary mod folder, restoring the original root
TXD/GXT from verified backups. The texture and text handlers recognized and
installed both replacements, and an isolated startup remained running.
Mod-folder removal and reinstall also passed. See the
[distant-corona finding](re3-distant-coronas-2026-10-04.md) for the shared loader
target and profile experiment. Menu navigation, final in-game appearance and
other language variants remain untested; startup does not prove gameplay.

## Reproduction and publication boundary

With permitted local game inputs, inspect only the named texture's native
chunk and the two GXT entries. Compare dictionary length, all non-target
bytes, all alpha values and GXT changes before installation. Exercise the
installer against copies and compare original hashes after restoration.
Inspect the decoded final texture for repair seams before packaging.

The mod implementation, reconstructed game-derived artwork, complete text
dictionaries, release package and installation paths are withheld from this
public library. Their private implementation owner retains the source and
full validation. This note returns reusable methods and limits only.

Primary references: re3 contributors' pinned
[frontend](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/core/Frontend.cpp),
[menu definitions](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/core/MenuScreensCustom.cpp),
and [text loader](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/text/Text.cpp).
Original GTA III artwork belongs to Rockstar. Consulted route:
[Dryxio reference catalog](dryxio-catalog.md).
