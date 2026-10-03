# Mod Loader callback integration for Windows x64 re3

## Question and target

Can a plain GTA III re3 installation load the Cowboy-69 Mod Loader fork while
keeping original game content and zero content mods?

The source target was Windows x64 D3D9/OpenAL re3 at
[`9a7fa478578beaba947ea867c15a25e411d641d8`](https://github.com/novawish/re3/tree/9a7fa478578beaba947ea867c15a25e411d641d8),
with librw revision `8b2caf8f86b4f793d07fbc6b7d0bd4aafd22162f`.
The loader source was
[Cowboy-69/modloader](https://github.com/Cowboy-69/modloader/tree/76c127e983069bcb1308b198c11ce8b81147b0bc),
branch `modloader-re3`, revision
`76c127e983069bcb1308b198c11ce8b81147b0bc`. The original Mod Loader author is
LINK/2012; retain its MIT license and dependency notices.

## Observations and method

The fork exposes an engine callback interface in
[`modloader_re3.h`](https://github.com/Cowboy-69/modloader/blob/76c127e983069bcb1308b198c11ce8b81147b0bc/include/modloader/modloader_re3.h).
The pinned stock engine lacks the corresponding host integration. Copying the
loader alone therefore does not supply the engine callbacks.

An engine adapter was built outside this public library. It supplies the
callback table, initialization and per-frame lifecycle, file redirection and
streaming bridges. Inspection also found that the x64 streaming-information
upper bound needed the engine array's 32-byte stride. A packed declaration's
28-byte size is not sufficient evidence of an array's actual stride.

The loader and ten plugin modules compiled with MSVC 19.29 / Visual Studio 2019;
the engine compiled with MSVC 19.51 / Visual Studio 2026. Both used Windows SDK
10.0.26100. The loader build was Release and the engine RelWithDebInfo.
Local original game assets were independently checked against an installed
depot manifest; they were not published here.

## Validation and reproduction limits

The local method used a clean pinned engine worktree, an independently obtained
loader source archive, component-specific CMake builds, and an isolated game
folder with no content mods. Both builds completed. Patches passed reverse
application checks against the built sources. Starting with the working
directory set to the game root produced the log message
`Mod Loader has started up!` and a splash-texture load.

The loader's `std.asi`, `std.bank` and `std.tracks` modules declined this target
under their upstream support checks. Their presence is not evidence that
retail x86 ASIs or San Andreas bank/track replacements work in x64 re3.

This records successful initialization only. New-game gameplay, model and
texture replacement, script replacement, audio replacement and hot refresh
were not validated. Compilation and callback registration cannot establish
complete ABI or streaming correctness. CLEO AI and the SA-specific SDK routes
in the [reference catalog](../docs/workshop/CATALOG.md#native) were consulted
for applicability, not executed; this was a native re3 engine task.

## Publication boundary

This finding is the public-safe return. Runtime adapter source, build patches,
native binaries, local logs and game payloads stay outside this library under
its [publication boundary](../PUBLICATION.md). This note neither distributes a
loader package nor claims a general supported release. Readers need their own
permitted source/assets and an independently reviewed engine integration.
