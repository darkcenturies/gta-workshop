# Distant coronas through Mod Loader in Windows x64 re3

## Question and exact target

Can distant city lights follow Mod Loader profiles in re3, rather than requiring
a retail x86 ASI or editing root game assets?

The evaluated target was Windows x64 D3D9 re3 at source revision
`9a7fa478578beaba947ea867c15a25e411d641d8`, with the callback integration
described in [the earlier Mod Loader finding](re3-modloader-callbacks-2026-10-04.md).
Mod Loader was Cowboy-69's callback fork at
`76c127e983069bcb1308b198c11ce8b81147b0bc`, version 0.3.9. Original attribution
belongs to LINK/2012; the C plugin interface carries a public-domain notice.

Exact local host evidence:

| Input | SHA-256 |
| --- | --- |
| Executable | `041d907d13395cca54ffb550bdd34f1ca585e470c1c87a3450de30ac8726732d` |
| Matching PDB | `c133e7c37f73e0794149ad4d44a3f2d325a21476f39d2fd1c5e5bcf3e7453142` |
| Mod Loader | `8ce48a7f686523a62df0f2992f5cfaaa2720eb951c4c21f6d360b1f70b5ab3fa` |

These identities establish the evaluated target, not compatibility with other
engine builds, retail GTA III, reVC or San Andreas.

## Method and observations

The native/graphics routes and [Dryxio reference catalog](dryxio-catalog.md)
were consulted. [Project2DFX](https://github.com/ThirteenAG/III.VC.SA.IV.Project2DFX)
by ThirteenAG was reviewed as a distant-corona reference. Its retail x86 plugin
was not installed or treated as an x64 re3 module. CLEO AI and San Andreas SDK
tools were evaluated as unsuitable for this native re3 task and were not run.
No public tool-family executable was required for the selected source/PDB route.

A private, independently written native Mod Loader plugin accepts a bounded
text light table. Install and reinstall parse a complete valid pack before
replacing its active snapshot; uninstall removes that pack. One shared file
behavior lets Mod Loader select content according to profile and priority.
The infrastructure DLL loads through Mod Loader's plugin system, while the
content table lives in an ordinary mod folder. No new engine binary is needed.

The table builder reads only active IDE/IPL entries in `gta3.dat`. It finds
light effects and light-bearing instances, applies re3's rotation convention,
keeps RGB/time/blink metadata, removes LOD duplicates and omits special/bridge
modes requiring live predicates. Synthetic evidence confirmed that the engine
rotation uses the negative quaternion angle and ignores the IPL scale fields.
Disabled map entries do not contribute lights. The local active layout yielded
3,544 lights from 1,911 instances, 16 IDE files and 14 IPL files; 41 effects
were excluded. Folder names alone did not identify the active map.

Inspection of the pinned renderer found that ordinary corona rendering checks
the normal far clip. The experimental method uses the native sprite projection
without that check, then clamps render depth inside the far clip while retaining
depth testing, additive blending and restored render states. It fades distant
lights beyond their native ranges and through dusk/dawn. This avoids extending
geometry draw distance. The expected limitation is that geometry beyond the
host clip cannot occlude these clamped-depth sprites; nighttime visual behavior
and performance still require gameplay verification.

## ABI and actual validation

The private implementation compiled with MSVC 19.51.36257, Visual Studio 2026,
Windows SDK 10.0.26100, C++17, optimized x64 and static CRT, with warnings treated
as errors. MinHook was pinned at `c3fcafdc10146beb5919319d0683e44e3c30d537`.
Matching PDB evidence validated function argument counts, types, field sizes
and enum values. Calls use the Microsoft x64 calling convention.

`CCoronas::Render` had RVA `0x1ef980`, no arguments, and this 16-byte prologue:
`48 8b c4 55 53 56 57 41 54 41 55 41 56 41 57 48`.
MinHook detour preparation passed against an offline mapped executable;
the offline check executed no engine gameplay functions.

Validated host functions included `CSprite::CalcScreenCoors` with five arguments,
`RenderBufferedOneXLUSprite` with eleven, `FlushSpriteBuffer` with zero,
`RwTextureGetRaster` with one and `RwRenderStateGet/Set` with two each.
`CVector` and `rw::V3d` were 12 bytes, `CCamera` was 59,968 bytes, `CMatrix`
was 80 bytes and the camera's contiguous position began at offset 56.
The C loader ABI had 64-byte file records with behavior at offset 56 and
168-byte plugin records with the loader pointer at offset 48.

Actual checks passed:

- Native night/time gates, distance fading and invalid format/bounds regressions.
- Synthetic quaternion direction, ignored scale and disabled-map selection.
- Offline PDB binding, detour preparation, DLL dependency/export loading and
  install/reinstall/uninstall callbacks with the generated table.
- Hash-strict package install, removal and reinstall against an isolated fixture;
  a customized table was refused before writes.
- An isolated startup installed all 3,544 lights and remained running.
- Editing the live profile to ignore the mod invoked uninstall; restoring the
  profile reinstalled the pack, and the process remained running.

An initial fixture omitted original model subdirectories and terminated with
`0xc0000409`. It also failed with every content mod disabled and the new DLL
removed. Completing the fixture resolved startup. A fixture failure therefore
needs a baseline comparison before being attributed to a new native mod.

The related [menu-strip asset finding](re3-yellow-menu-bar-2026-10-04.md) was
also migrated to Mod Loader. Standard texture and text handlers recognized
the menu TXD and American GXT. Original root assets were recovered by hash,
and mod-folder removal/reinstall passed. Startup and profile lifecycle evidence
does not establish nighttime appearance, menu navigation or complete gameplay.

## Reproduction and publication boundary

### Follow-up fork comparison

The referenced [x87/gta-extended-2025](https://github.com/x87/gta-extended-2025)
already derives from re3/reVC. Its default branch is `miami`; the relevant GTA III
branch was inspected at `master` revision
`f8142f1a7cefcfd6bcd778ed8802e21c93b97c91`. This was a source-only comparison,
with no fork build, engine replacement or gameplay validation.

Its [config](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/core/config.h)
enables extended controls, vehicle/damage features, photo mode/gallery,
features-INI options and distant-light routes. Its
[photo-mode interface](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/extras/PhotoMode.h)
includes camera, character, weather/time, lighting and effect controls.
These source features are candidates for selective integration, not evidence
that a complete fork port improves performance or preserves save compatibility.

The distant-light route raises the corona pool to 2,000 entries and calls
`ProcessDistantLights` while walking building/dummy pools in
[World.cpp](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/core/World.cpp).
However, the inspected
[Entity.h](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/entities/Entity.h)
does not declare that method, and the inspected entity/corona source files do
not define it. The supplied features INI also omits its enabling key. This is
a source inconsistency requiring review/repair, not a completed build diagnosis.

The fork's renderer adds sorted building lists, while its all-island loading
route still scans the three big-building lists under the existing HIGH setting.
That distinction matters: island residency, model LOD distance, far clipping
and visible skyline coverage are separate. Native distant lights do not alone
make distant geometry visible. No full-city visibility or FPS improvement was
established by this comparison. Replacing a host also requires revalidating
exact-executable/PDB plugins; source-derived features cannot be assumed to load
as ordinary asset replacements through Mod Loader.

### Original reproduction limits

Use independently supplied permitted assets and the exact executable/PDB pair.
Inspect active map entries, verify engine transforms with synthetic coordinates,
hash all source maps, validate the generated table, and exercise loader callbacks
offline before an isolated startup. Compare a complete no-mod baseline if the
fixture fails. Confirm uninstall/reinstall through profile changes before
claiming profile integration. Verify actual night scenes separately.

The builder currently reads root map files; priority-selected Mod Loader map
overrides require a future resolver or explicit regenerated inputs. Static
special-light predicates and broader host compatibility remain unsupported.
Runtime implementation, mod binaries, matching symbols, game-derived tables,
artwork, private logs and packages are withheld under the
[publication boundary](../PUBLICATION.md). This is a public method/evidence
return, not a source export or a mod release.

Primary references: re3 contributors' pinned
[corona renderer](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/render/Coronas.cpp),
[sprite renderer](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/render/Sprite.cpp),
[file loader](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/core/FileLoader.cpp),
and the Mod Loader fork's
[C plugin interface](https://github.com/Cowboy-69/modloader/blob/76c127e983069bcb1308b198c11ce8b81147b0bc/include/modloader/modloader.h).
