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
`f8142f1a7cefcfd6bcd778ed8802e21c93b97c91`. The initial comparison was source-only; the build and integration checks below
were performed in follow-up work.

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
Correction: the method belongs to the derived classes, with implementations in
[Building.cpp](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/buildings/Building.cpp)
and [Dummy.cpp](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/entities/Dummy.cpp).
The earlier search in CEntity incorrectly suggested a missing implementation.
The pin subsequently compiled for Windows x64 D3D9/OpenAL using its matching
librw revision. Its supplied features INI does omit the enabling key, which
defaults to disabled. Compiler success does not establish night rendering,
complete skyline coverage or save compatibility.

The fork's renderer adds sorted building lists, while its all-island loading
route still scans the three big-building lists under the existing HIGH setting.
That distinction matters: island residency, model LOD distance, far clipping
and visible skyline coverage are separate. Native distant lights do not alone
make distant geometry visible. No full-city visibility or FPS improvement was
established by this comparison. Replacing a host also requires revalidating
exact-executable/PDB plugins; source-derived features cannot be assumed to load
as ordinary asset replacements through Mod Loader.

### Follow-up source-feature integration checks

A pinned Windows x64 D3D9/OpenAL build used MSVC 19.51.36257, v145 and SDK
10.0.26100, with matching librw revision
`5501c4fdc7425ff926be59369a13593bb6c81b54`. The reference requires compatible
engine support for its class/layout additions. A native Mod Loader configuration
plugin can select an INI and gate source-function behavior; an asset folder or
retail x86 ASI alone cannot supply those structural changes. Types, pool capacity,
loader routes and save compatibility remain infrastructure even when runtime
features are disabled.

The full guarded inventory extends beyond the README's short list: controls,
aiming/first-person, walking/reload/shutoff, GPS/radar, controller types/vibration/
icons, vehicle/damage/AI, tyre/glass/water/melee interactions, photo/gallery,
particles/moon/radio, replay/cheats, optional vehicle loading, nine gameplay
options and remaining guarded utility/miscellaneous behavior. The integration
compiled 844 variants across 234 functions and exposed 373 boolean switches,
including master/group gates. Malformed keys, duplicate keys and invalid booleans
reject the whole configuration. Priority replacement must tolerate installation
of a new winner before uninstallation of the old file.

Several backend and compatibility details required explicit repairs:

- The native text handler's retail x86 address-patching reload route is invalid
  in an x64 re3 host. A native text-reload entry point avoids that route. Removing
  an old selected GXT must not erase its replacement's mapping.
- Optional vehicle data must be checked before calling a line reader. Missing
  optional input otherwise reaches an invalid file descriptor in the Windows CRT.
- The reference's added sample bank is supported in its Miles backend but needs
  a separate OpenAL route. Missing upstream samples and controller artwork require
  recorded substitutions; availability cannot be inferred from source references.
- The older fork's compatible save layout differs from native x64 saves of the
  compared re3 build. A converted read cache preserves the original. A rename
  inside `assert` must not be relied on when `NDEBUG` removes evaluation.
- Optional statistics must not change the primary save block when toggled.
  A hash-associated sidecar separates that state. Normal EOF is distinct from
  read failure, despite the legacy helper's misleading error-like name.

Strict parser/registry/parent-gate tests, priority/uninstall tests, four synthetic
TXD/GXT preservation tests and installer backup/settings-preservation/rollback/
hash-rejection checks passed. A complete isolated stock-asset fixture initialized
its player/world with all features enabled and with the master disabled. A copied
legacy save loaded via a conversion cache without changing its original; a new
save passed its checksum and reloaded the extra statistic from its sidecar.

INI activation and profile ignore/re-enable produced `0/1/0/1/1` activation.
An explicit timecycle update returned far clips `1150/3500/1150/3500/3500`,
and touching the selected GXT exercised native reload without terminating the
fixture. These are engine/probe and lifecycle checks in an isolated fixture.
They do not establish visible skyline coverage, occlusion correctness, an FPS
gain, complete mission progression, controller hardware behavior or every
photo/gallery interaction. Those remain actual gameplay checks.

The geometry route also retains distant big-building LODs and selects HIGH
island loading while enabled. Stock city and campaign routes were retained;
no replacement map or campaign was part of the mod payload. Native windowed
mode is a host INI preference and does not require another content plugin.

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
artwork, private logs and packages for that original exact-host experiment are withheld under the
[publication boundary](../PUBLICATION.md). This is a public method/evidence
return. The separately authorized standalone port described below has its own
source owner; implementation and release files remain outside this library.

### Standalone build reproduction

The subsequent [re3 Extended source](https://github.com/darkcenturies/re3-extended)
publishes a reviewed standalone port with fresh history and a native Mod Loader
build action. Its initial source revision is
`2516981d4af25e05b380a4a061cd8b14d3f50249`. It pins the GTA III master branch of
x87's fork, librw and the native Mod Loader fork by revision and archive SHA-256.
The generator additionally checks all 564 selected engine source files.

Reproduce on Windows with Visual Studio C++ Build Tools, a Windows SDK and
Python: install the repository's requirements, then run `./build.ps1`. A working
game installation is unnecessary for this build. It compiles the matched host,
native loader/handlers and the registry plugin, runs INI/priority tests, four
synthetic TXD/GXT checks and transactional installer checks, then verifies every
ZIP file against its manifest. The package check rejects game assets, maps,
scripts, saves, PDBs and smoke/test binaries. Testing exports are disabled in
the shipping host. These local checks passed.

The same checks passed on the clean Windows 2022 runner in
[Actions run 37204367965](https://github.com/darkcenturies/re3-extended/actions/runs/37204367965).
The published [artifact 11304112835](https://github.com/darkcenturies/re3-extended/actions/runs/37204367965/artifacts/11304112835)
was downloaded and checked against its manifest and SHA256SUMS. Its inner
`re3-extended-modloader-win-x64.zip` has SHA-256
`c7cb8ba0fef767777449b7b05d2fdac7d906f6b60ca63d357009ab923cae7c5e`.
It contains 26 installation files plus the manifest. CI artifact retention is
90 days; this records an Actions artifact publication, not a website deployment.

The resulting Mod Loader ZIP contains the matched host/foundation, native
handlers, configuration plugin, the complete 373-setting INI, local asset
builder/installer and notices. Textures and GXT are prepared on the user's
computer from independently supplied game files and the pinned reference.
An explicit text-file input preserves another mod's existing text keys. An
isolated local installation exercised this asset preparation and file
replacement successfully; the original source save remained unchanged.
New-foundation installation, existing profile preservation, rollback and hash
rejection also passed in synthetic fixtures.

The complete runtime variants, structural support and gameplay limits are
documented in that source repository. These build and installation results do
not establish complete visual, mission, controller, GPS or photo-mode behavior.
The distribution records `gameplay_validated=false`. No game-derived payload,
private history, personal configuration, symbols or private logs are added to
this methods library.

Primary references: re3 contributors' pinned
[corona renderer](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/render/Coronas.cpp),
[sprite renderer](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/render/Sprite.cpp),
[file loader](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/core/FileLoader.cpp),
and the Mod Loader fork's
[C plugin interface](https://github.com/Cowboy-69/modloader/blob/76c127e983069bcb1308b198c11ce8b81147b0bc/include/modloader/modloader.h).

### Native camera, window focus and photo text regression checks

Owner gameplay screenshots and reports subsequently showed a missing Free camera
option, cursor recentering after Alt+Tab in windowed mode, a missing Photo Mode
menu label and overlapping photo help text. The affected camera was mouse orbit
around the player or vehicle; the flying debug camera was a separate feature.
These observations narrowed the investigation to menu registration, host input
focus and text coverage rather than distant-light rendering.

In the pinned x87 revision `f8142f1a7cefcfd6bcd778ed8802e21c93b97c91`,
[the custom menu](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/core/MenuScreensCustom.cpp)
excludes the original Free camera toggle when extended controls are compiled.
The host's custom-option INI reader depends on registered menu entries, so hiding
the option also skipped an existing FreeCam preference. Restoring that entry and
reading the preference independently preserves the native mouse-orbit choice.

The [Windows backend](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/skel/win/win.cpp)
uses a foreground flag that also tracks rendering availability. A windowed D3D9
device can continue rendering after another application receives focus. Cursor
warping and input polling therefore need the actual foreground-window check;
focus loss also releases capture and unacquires the mouse device. Compilation
and source review establish the new guard, while visible Alt+Tab behavior remains
an owner gameplay check.

The pinned GXT lacks the new Photo Mode, Borderless and PlayStation 5 menu labels
and all 42 text keys used by
[PhotoMode.cpp](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/extras/PhotoMode.cpp).
The long missing-key placeholders overlap the fixed help-bar positions. The local
asset builder supplies 45 compact authored English fallbacks only for absent
keys, preserving existing translations, custom labels and intentionally blank
footer text. Left/right modifier-key prompts use named Shift/Ctrl/Alt icons.
When the pause footer title is blank, Quit game also uses the normal menu color
instead of the fork's black text intended for the yellow footer.

Version 0.1.1's fixes are recorded in
[source revision ec09ebe](https://github.com/darkcenturies/re3-extended/commit/ec09ebe88db9f48a5853717aef0adeb19f9a02f4).
The local `build.ps1` run passed shipping host/loader/plugin compilation, parser
and priority lifecycle tests, six asset checks, transactional installation checks
and package boundaries. The asset checks include every photo text key referenced
by the pinned source and preservation of blank/custom text. An isolated
`TestSmoke.py --scenario compatibility` run retained the orbit option and
FreeCam=1 through Controls on/off/on and master disable. All four snapshots
retained eight audited native entries: brightness, draw distance, subtitles,
resolution, window mode, VSync, frame limiter and island loading. The original
fixture save remained unchanged.

This audit establishes those entries and the saved preference, not every native
feature's gameplay behavior. Actual photo layout, mouse orbit, focus transitions,
controller hardware and campaign progression remain owner checks. Test exports,
probe plugins, game assets, saves, personal configuration, PDBs and private logs
remain excluded from the public package and this research library.
