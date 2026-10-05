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

### Shared submenu background correction

A subsequent owner screenshot showed the Language submenu's black footer title
over bare artwork. The clean main/pause mod changes only `mainmenu24`, but
[DrawFrontEndNormal](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/core/Frontend.cpp)
also selects that background for multiple submenus. Preserving other named
textures alone therefore does not preserve every submenu's appearance.

The corrected route prepares an additional unretouched stock mainmenu24 copy
locally in the frontend dictionary. With both main/pause title strings blank,
submenus sharing that background select the original copy; main and pause retain
the cleaned texture. Previous and current backgrounds each use their own page
selection during fades. The extra sprite is released before its dictionary is
removed. No artwork copy is present in the public build artifact.

Seven synthetic asset checks passed, including preservation of all original
pixel/native-payload bytes outside the copied texture's renamed name field.
The isolated compatibility fixture loaded the extra texture and selected it
for Language but not Main across all four Controls/master snapshots. The orbit
preference and eight audited display entries remained intact. These are source,
asset-boundary and engine-selection checks; an actual in-game screenshot remains
necessary to establish the final submenu appearance.

The combined 0.1.2 corrections are merged in
[main revision 2f2ba5b](https://github.com/darkcenturies/re3-extended/commit/2f2ba5b856122a41b064a7fc101c17be2bd10ae6).
The complete build and checks passed on Windows 2022 in
[Actions run 37218204306](https://github.com/darkcenturies/re3-extended/actions/runs/37218204306).
The published [artifact 11309168186](https://github.com/darkcenturies/re3-extended/actions/runs/37218204306/artifacts/11309168186)
was downloaded; all 27 entries matched the manifest, sizes and SHA256SUMS. Native
x64 host/loader/plugin exports were checked offline, and the shipping host has
no testing export. The inner install ZIP's SHA-256 is
`6e0b0bd56f61e3cc78fd1f67320b9d567330ac4ef4269cde5bc665833969ce20`.
No TXD/GXT, maps, saves, symbols or probe DLLs are present. Local installation
preserved current native/Extended INIs, the existing save, the root menu texture
and the cleaned menu texture. This records an Actions publication and a verified
local installation; it does not establish the owner's final visual check.

### Offline packages and native platform evidence

The 0.1.2 ZIP was subsequently published unchanged to
[GitHub Releases](https://github.com/darkcenturies/re3-extended/releases/tag/v0.1.2).
An Actions artifact and a Release asset are separate publication mechanisms;
uploading an artifact alone does not create a release.

The 0.1.3 route builds directly extractable offline game-folder packages for
Windows x64, Linux x64 and native macOS Apple Silicon ARM64. Only authored text
icons, MP3/OFF icons and three synthesized PCM effects are built by CI. Stock
artwork and text stay in the installed game; native missing-key and menu-texture
fallbacks remove the local generation requirement. The ZIP carries default INI
settings outside the user's overwrite path. First launch copies them only if
needed; upgrading an existing Features section adds CleanMenu with a backup and
preserves prior choices. No interpreter, setup helper or first-launch download
is shipped or required.

Windows retains the upstream native Mod Loader/DLL configuration path. Linux
and macOS use an authored folder loader with profile priorities, ignore lists,
case-aware stock fallback, file redirects and selected-INI reload. This does not
implement the Windows ASI/DLL or loose-model streaming plugin ABI. Linux targets
an Ubuntu 22.04/glibc 2.35 baseline and retains system graphics drivers. macOS
targets macOS 14+ and bundles ARM64 libraries in an ad-hoc-signed app; it is not
notarized. Actual gameplay on those systems remains unverified.

The initial POSIX CI preparation exposed Windows separators in the compiler
manifest. Normalizing file access while preserving original registry identities
gave the same 374-setting fingerprint on both platforms:
`16496533c731429a7d1fe8bc9c756315d04a257e207e5580dd39811eaf1e888d`.
GL3 vertex-color access and photo/keyboard platform assumptions also needed
portability changes. Native Linux compilation, settings/folder tests, ten asset
tests and archive checks passed locally. Native ARM64 compilation, bundled-library
architecture checks, app signature verification and archive hashes passed in CI.
These establish build/package properties, not controller or campaign parity.

An owned Windows stock-artwork/text fixture passed CleanMenu on/off/master
selection, orbit/menu compatibility and loader ignore/re-enable/reload checks.
Its far clip followed activation between 1150 and 3500, and its original save
was unchanged. The [menu finding](re3-yellow-menu-bar-2026-10-04.md) records the
approximate image fallback and title/submenu limits. Reproduction uses the public
build.ps1 or build_posix.py with pinned source inputs; runtime tests additionally
require independently permitted game assets in an owned fixture.

README organization was informed by Dryxio's project documentation: a concise
intro and download link, grouped features, short installation steps and credits.
This is documentation review, not execution of a CLEO tool. No game-derived art,
private inputs/history, symbols, saves or probe logs return to this library.

The owner also asked about visible ghost trails. The pinned
[post-processing implementation](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/extras/postfx.cpp)
uses a prior-frame buffer when MotionBlur is enabled; its Normal filter selects
the blurred overlay path. These remain native Graphics preferences, separate
from the Extended feature INI. Since blending occurs per rendered frame, a shorter
visible trail at high frame rates is an inference from the implementation; a
controlled visual comparison at different limits was not performed. The screenshot
alone does not establish a particular filter or strength.

Follow-up: the owner reports no visible trail at 165 FPS. A read-only preference
check found MotionBlur and Trails enabled, ColourFilter 2 (Normal), FrameLimiter
disabled and MaxFPS 30. The stored limit is inactive while FrameLimiter is off.
The generated shipping postfx.cpp matched the pristine build input byte for byte,
so this port did not replace that implementation. The custom menu binds MotionBlur
to CPostFX::MotionBlurOn; Normal uses the prior-frame overlay and the buffer is
updated every rendered frame. The interval at 165 FPS is about 6.06 ms, versus
33.33 ms at 30 FPS. Shorter visible trail persistence is inferred from that
sampling and feedback, not measured by a controlled capture. Temporarily enabling
the existing 30 FPS limiter and repeating the same camera movement is a useful
comparison; no user preference or installed binary was changed here. Preserving
comparable persistence at high FPS would require an optional time-based blur
implementation and visual verification, rather than another enable switch.

### Optional time-based blur implemented

The owner confirmed that the trail appears with the 30 FPS limiter and requested
the effect at 165 FPS. The optional FrameRateIndependentBlur feature is merged
in [revision dbe5c120](https://github.com/darkcenturies/re3-extended/commit/dbe5c1209a5b006d47b1038be56ab90842001a8e)
for version 0.1.4. It is appended to the registry without shifting existing
indices, bringing the complete INI to 375 booleans and 37 feature groups.

For each colour channel, the original two overlays can be reduced to a
current-frame contribution B and history retention H. The new retention is
`H^(30 * elapsed_seconds)`; scaling B by `(1 - new_H) / (1 - H)` preserves the
original tinted steady-state brightness. The authored D3D9/GL3 shader reads
separate current/history textures and combines them in one floating-point draw.
The initial fixed-function approach exposed rounding error in its numerical
checks and was replaced before release. No runtime shader compiler is required;
Windows build checks reproduce the authored bytecode from its accompanying HLSL.
Both installed Windows SDK compiler versions produced identical bytecode.

Only Normal-filter motion blur uses the new path. Feature/master deactivation
restores the native renderer; other filters and sniper effects keep their native
paths. History resets on camera cuts, activation/effect changes, raster recreation
and frame gaps longer than 250 ms. Real elapsed time comes from a monotonic clock,
independent of game simulation timing or the selected FPS cap. Existing INI
choices are preserved when the new editable key is added, with a backup.

Numerical tests passed for 30/60/120/165/240 FPS, mixed frame times, tinted
equilibrium, zero/opaque cases and reset transitions. The full Windows build,
settings/plugin/folder/asset/installer and archive-boundary checks passed.
Windows/Linux/Apple Silicon PR builds passed for the shipping implementation.
An owned hidden Windows fixture used a separate test-only camera pass because
its frontend remained active after focus loss. This exercised the actual D3D9
shader and texture samplers without altering production focus/menu behavior.
Synthetic RGB readback exactly matched expected values: 70/115/167 at 30 FPS and
49/90/132 at 165 FPS. Paired draw counters verified feature on/off/on and master
off, with about 6.06 ms between test samples. Original fixture configuration and
its original save were retained. This establishes backend execution and timing,
not a measured gameplay FPS or a final visual comparison. Native POSIX gameplay
and final appearance/performance remain owner checks. No game assets, private
fixture files, symbols or logs return to this library.

The final main workflow
[37231214179](https://github.com/darkcenturies/re3-extended/actions/runs/37231214179)
passed all Windows/Linux/macOS and release jobs, publishing
[v0.1.4](https://github.com/darkcenturies/re3-extended/releases/tag/v0.1.4).
Each manifest identifies main revision dbe5c120 and registry fingerprint
`a17b5421e2c770ccb33a8c6bb7d04be53908941da62be42cd4e099fc872b408a`.
Independent downloads matched the Actions artifacts byte for byte; all file
hashes, native architectures, package boundaries and Mac bundled-library paths
and executable permissions passed. The earlier 0.1.3 downloads are unchanged.

| Platform | Actions artifact | ZIP SHA-256 |
| --- | --- | --- |
| Windows x64 | 11313747769 | `ba3875b432c5d925f6e917c0fe5803b7f2992693bff24751168d63aa8a7d31f3` |
| Linux x64 | 11314236118 | `f5d29203b069faf650110986b97b9041329208ff77c56ff4e4547e637b8e171c` |
| macOS ARM64 | 11313712209 | `bbf6d29a27a3d14a8ece9b47a6fc2c7a4e38a8622449025e2fb8d6b16d9c7c01` |

A matching local Windows host/symbol pair was rebuilt from clean merged main and
installed after the game closed. All 374 previous setting values, native FPS/
camera preferences, menu art/text and saves were retained; the new blur key is
enabled. This local compiler build and the separately verified CI download share
the reviewed source revision, rather than an assertion of identical binary bytes.
The owner performs the final visual check at 165 FPS.

### Released 0.1.3 evidence

The offline changes are merged as
[main revision 3e537411](https://github.com/darkcenturies/re3-extended/commit/3e53741101d17c3b591c808ed663baa675a743f6).
All three platform jobs and the release job passed in
[Actions run 37225055341](https://github.com/darkcenturies/re3-extended/actions/runs/37225055341).
[Release v0.1.3](https://github.com/darkcenturies/re3-extended/releases/tag/v0.1.3)
contains Windows x64, Linux x64 and macOS ARM64 ZIPs plus platform hash files.
The release tag and every package manifest identify that same main commit.

| Platform | Install files | ZIP SHA-256 |
| --- | --- | --- |
| Windows x64 | 31 | `78681bfd0bc165bd55b5a0fd7e63a775156706921a3787bab917cecf9a902790` |
| Linux x64 | 42 | `ce8e6fb7192a40778bbffdd25a57eda16bc783948dcd3cb681134047d7178dd0` |
| macOS ARM64 | 24 | `d347d25d2818fabb08b4c0efb6e9424e0585c664f58e42d87978bd17f88c7b42` |

The three Actions artifacts and Release assets were downloaded independently;
their ZIP hashes matched, as did every manifest file hash and size. The Mac
executable and all three bundled dylibs were independently checked as ARM64;
load commands reference system libraries or present app-bundled libraries, and
ZIP executable permissions are preserved. CI also verified the ad-hoc signature.
Native ELF/PE architecture and shipping registry/test-export boundaries passed.
The 31/42/24 counts exclude each ZIP's manifest file. This is verified release
publication, with actual Linux/macOS gameplay still untested.

A matching local Windows host/symbol pair from clean merged main was installed.
The existing save, native preferences, prior Extended toggle values, root menu
and both old Clean Menu source files were preserved. The exact retouched payload
was imported into the Extended frontend; CleanMenu was added to its INI and the
legacy two-file folder was ignored through the active profile. Neither Upstate
content nor a testing host/plugin was installed. Final visual quality remains
an owner check.

### Native installation requirements clarified

The [installation guide](https://github.com/darkcenturies/re3-extended/blob/main/README.md#installation)
now separates shared game data from platform-specific executables. Every 0.1.3
ZIP contains its matching host and folder integration; macOS users need the
ARM64 package, not a Windows base executable or an older Intel-only Mac build.
The same original/classic GTA III PC data is required across all three platforms.
The guide links the classic
[Rockstar Trilogy store](https://store.rockstargames.com/game/buy-grand-theft-auto-the-trilogy),
and explains copying an owned installation's data when its installer requires
Windows. Definitive Edition, console and mobile data are outside this target.

The Mac package includes its native dependencies. Windows 0.1.3 still requires
separate x64 OpenAL/mpg123 DLLs if absent from an existing installation; the guide
links their exact pinned upstream files and Microsoft's x64 runtime installer.
Both DLL downloads matched the build SDK byte for byte. All seven installation
links returned HTTP 200, and the three ZIP names matched the published Release
asset inventory. This was documentation/link verification, not a new gameplay
test. The guide correction is merged in
[revision d0a0de40](https://github.com/darkcenturies/re3-extended/commit/d0a0de4039b54de0d4450301b1d40d9db478639a).
Previously published 0.1.3 ZIPs, their embedded README and the release evidence
above remain unchanged. No game assets or runtime implementation were returned.

### Matching mission marker and GPS colours

On 2026-10-05 the owner showed a bright pink triangular radar marker and matching
GPS route. The pinned GTA III branch's DrawGPS mission-blip path obtains each
route colour from GetRadarTraceColour for the destination blip. Its magenta
entry returns RGBA 255, 0, 255, 255 in the bright state. This preserves the
mission target's colour on its route. Manually placed waypoints use a separate
WaypointColor, whose absent-config default is RGB 180, 24, 24.

The screenshot is consistent with a magenta mission target; it alone does not
identify the active mission script or blip state. Matching pink is not evidence
of a missing texture. These observations come from the locally verified pinned
[Radar.cpp](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/core/Radar.cpp)
and
[re3.cpp](https://github.com/x87/gta-extended-2025/blob/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91/src/core/re3.cpp),
not from a new gameplay test. The question did not request recolouring; no
marker, mission or GPS colour was changed.

### Combining native Mac fixes with an existing asset release

On 2026-10-05 a requested repack found the Apple Silicon fixes in
[PR 7](https://github.com/darkcenturies/re3-extended/pull/7), still separate from
the exact-menu release. The branches conflicted in the menu loader, package
manifest, archive tests and documentation. The combined
[PR 8](https://github.com/darkcenturies/re3-extended/pull/8) keeps the approved
one-texture menu payload and the 375-setting registry while incorporating the
Mac display, focus/input, file-loading, exit and app-installation work.

An app installed in Applications needs its mod assets inside Resources as well
as in the extractable game-folder layout. Archive checks compare those copies
byte for byte, check the icon declaration and ARM64 architecture, and verify
every manifest file hash. The native app can select and copy locally owned
classic game files offline; existing configuration is retained. No setup
interpreter or first-launch download is required.

The earlier Mac CI failure occurred in the MSAA readback test when its OpenGL
context could not be created. The revised test first requests a baseline core
context with zero samples. Only unavailable CI graphics produce an explicit
skip; a sample-count mismatch on an available context still fails. Level zero
requests zero samples. This follows GLFW's
[window hints](https://www.glfw.org/docs/latest/window)
and [macOS context requirements](https://www.glfw.org/docs/latest/compat_guide.html).
The combined Apple Silicon branch passed compilation, Cocoa window/focus tests,
settings/folder/blur regressions, ten asset tests and package checks; hardware
MSAA readback was explicitly skipped on that runner. The Mac author's M2
observations are separately attributed in
[Mac findings](https://github.com/darkcenturies/re3-extended/blob/391455185ca11ccf71a11eff5adadf3603f3e43b/MAC-FINDINGS.md).
CI success does not establish all gameplay or native fullscreen transitions.

The pinned GTA III master engine remains
f8142f1a7cefcfd6bcd778ed8802e21c93b97c91. This library receives the method and
validation limits; implementation, artwork and release packages remain in the
separately approved destination.

The combined change merged as
[39145518](https://github.com/darkcenturies/re3-extended/commit/391455185ca11ccf71a11eff5adadf3603f3e43b).
Both branch push and PR workflows
[37237008867](https://github.com/darkcenturies/re3-extended/actions/runs/37237008867)
and [37237027800](https://github.com/darkcenturies/re3-extended/actions/runs/37237027800)
passed Windows, Linux and Apple Silicon. Publication from the merged revision
uses a separate main run and immutable version 0.1.6 packages.

Main run
[37237634159](https://github.com/darkcenturies/re3-extended/actions/runs/37237634159)
passed all platform and release jobs and published
[v0.1.6](https://github.com/darkcenturies/re3-extended/releases/tag/v0.1.6).
Independently downloaded Release ZIPs matched their Actions artifacts byte for
byte. Every manifest file hash, source revision, registry fingerprint, native
architecture and exact menu pixel check passed. Mac app Resources matched the
root mod assets; its native library paths and executable permissions passed.
CI verified its ad-hoc signature after bundling Resources. The main Mac run
again explicitly skipped MSAA hardware readback while its hidden Cocoa
display/focus tests passed. The Windows shipping host had no testing export.

| Platform | Actions artifact | Files excluding manifest | Release ZIP SHA-256 |
| --- | --- | --- | --- |
| Windows x64 | 11315484630 | 34 | `e7a8aba3119b2fe4198aeecef92b4cf5487560203ae4e77a43aa2ffa9956c850` |
| Linux x64 | 11316680850 | 45 | `45b59121215bb2a9c1b3a39e444aac6cf0cc74f7b498321d76d4183273e4beef` |
| macOS ARM64 | 11315718236 | 40 | `abaf4ef2daaaeb34164a44da1b3618c870ccc1d77f94385c60d5d76e55d0bd6f` |

The exact retouched TXD hash remains
`ff379957b520be1fa5d78425f63d9f14fb96e92c2816dc714dfbc11b6498780c`.
All 375 setting identities remain at fingerprint
`a17b5421e2c770ccb33a8c6bb7d04be53908941da62be42cd4e099fc872b408a`.
These are compilation and package verification results, not complete gameplay
testing. Earlier release ZIPs were retained unchanged.

### One installation guide and a maintainable source layout

The 2026-10-05 follow-up identified duplicated platform installation documents
and a flat source/tool/test tree. The root README now covers every platform's
download, prerequisites, installation, configuration, updates and common
blur/orbit controls. Detailed settings stay in docs/FEATURES.md; contributor
build and validation records stay in the repository. Each package carries the
same README and settings guide, with no separate Mac installation guide or
developer findings.

Organizing a native port requires updating build inputs, generated-source
copies, Python package imports, test fixture paths, pinned-manifest lookups and
Mac Resources staging together. Runtime code, tests, tooling, manifests,
authored assets and extended documents now have separate directories. Root
build entry points and the existing installation section link are retained.
Archive checks verify README byte parity with the source, local documentation
links, the included settings guide and exclusion of developer/platform notes.

Local Windows build, native settings/plugin/folder/blur regressions, eleven asset
tests, installer checks and package/document checks passed. Source preparation
still produced 375 settings, 37 feature groups and 844 variants of 234 functions
from the same pinned GTA III master. Shader reproduction and local document
links passed. This was build/layout/package validation, not a new gameplay or
visual test. This library receives the method and results only.

### Complete mod payloads and researched attribution

The follow-up requested the same complete mod on Windows, Linux and Apple
Silicon, including audio dependencies and nine map tiles. A matched engine is a
source dependency: changes inside rendering, input and frontend code cannot be
represented honestly as a retail ASI for an arbitrary existing host. The mod's
assets and settings still obey folder-loader activation rules.

Fresh classic game data can lack the upstream menu's nine map textures. Package
only those native texture chunks in a separate dictionary, keep existing map
textures first, then fill missing textures through the active mod folder.
An isolated Windows fixture compared all nine renderer pixel hashes against
the existing upstream map. All matched; ignoring the mod removed the fallback.
Native mouse-orbit controls and original submenu behavior also passed their
activation checks. These findings do not establish Linux/Mac map rendering.

Windows audio is built from OpenAL Soft 1.21.0 and mpg123 1.26.3 source archives
with exact SHA-256 pins. Both decode/render checks and archive PE import checks
passed. A failed Windows CI attempt exposed the official prebuilt Yasm 1.3.0
assembler's dependency on an older Visual C++ runtime. Building the assembler
from its pinned source with a static runtime removes that hidden build-machine
dependency. Modern CMake requires four old target-location lookups to use
generator expressions and static-runtime policy initialization before the
project declaration. The assembler is build-only; it is not a user dependency.

License research must follow actual components, not apply one convenient SPDX
label to the whole engine pack. The [extensive attribution record](https://github.com/darkcenturies/re3-extended/blob/main/THIRD-PARTY-NOTICES.md)
distinguishes the re3 contributors, Cowboy69's Liberty Extended feature work,
x87's hosting fork, librw, the Windows Mod Loader and its nested libraries,
OpenAL/mpg123/GLFW and platform package dependencies. The [original Liberty Extended source commit](https://github.com/x87/gta-extended-2025/commit/ff1604da083e2f454e1d58074d1cd272660546d3)
supports Cowboy69's attribution. Current reference-project license snapshots
are distinguished from unknown original import revisions.

The audit corrected injector and plugin-sdk to zlib terms and retained nested
Boost, cereal, RapidJSON, RapidXML, UTF8-CPP and other source notices. OpenAL's
BSD portions credit Archontis Politis and Christopher Robinson; the actual Mac
1.25.2 notice also credits Anis A. Hireche. Its default
HRTF data also requires citation of Bill Gardner and Keith Martin, copyright
1994 MIT Media Laboratory; this is not the MIT software license. The [original KEMAR dataset page](https://sound.media.mit.edu/resources/KEMAR.html)
and the source definition establish that attribution. The engine's inherited
README declines an engine license; no blanket MIT/GPL grant is inferred.
Individual map artists and a separate artwork grant were not identified and
are not invented. Original game artwork remains separately attributed.

Every installation archive carries component license texts and an actual
runtime version/source inventory. Separate source archives contain the exact
Windows audio sources/build changes, Linux source packages and distro patches,
or Mac source archives and Homebrew formulae. They are optional for players and
verified against the installation manifest. This avoids unidentified prebuilt
DLLs, mismatched upstream source substitutes, and source bundles that obscure
the installation instructions. No implementation, artwork, local game inputs
or private test logs are exported to this reference library.

The complete-package change merged through [PR 10](https://github.com/darkcenturies/re3-extended/pull/10) as [c98ee37c](https://github.com/darkcenturies/re3-extended/commit/c98ee37ca0ab36e37a5975249c9a78f795e845ff). Main [run 37244212453](https://github.com/darkcenturies/re3-extended/actions/runs/37244212453) passed Windows, Linux, Apple Silicon and release jobs and published [v0.1.8](https://github.com/darkcenturies/re3-extended/releases/tag/v0.1.8). Independently downloaded installation and runtime-source ZIPs matched their Actions artifacts. Every manifest/source hash, native architecture, unchanged 375-setting fingerprint, exact menu pixels and nine native map chunks passed. Mac resource parity, bundled dylib paths and executable permissions passed; hardware MSAA readback remained explicitly skipped while Cocoa focus/window tests passed. Prior releases were retained. This is compiled/package and isolated Windows fixture evidence, not complete gameplay certification.

| Platform | Actions artifact | Files excluding manifest | Installation ZIP SHA-256 |
| --- | --- | --- | --- |
| linux-x64 | 11318995664 | 54 | `dc5276737dda1890510e1722ed04cc1f738d6c8a3127a4ddfe7ee8ae47a5487b` |
| macos-arm64 | 11318662148 | 60 | `72330f005ca5b419c7bbeca201077688455eac8473d495fb3eb4334c9e9092ec` |
| win-x64 | 11318034694 | 52 | `970d5a60b80585c2a5f9e14a65c7da8c78095fc52362d81215e8381442545bf6` |

The public inventory, three synthetic tool-family examples, all 54 research checksum records and relevant Markdown checks passed. Those synthetic demonstrations are separate tooling evidence; no CLEO compiler or asset-authoring tool validates this native port. Implementation and approved artwork remain in their separately authorized repository.

### A real-time FPS display in the native debug menu

The pinned re3 debug menu already has a frame limit control, but a standalone
counter needs its own display preference. The owner-requested change adds
**Ctrl+M > Render > Show FPS**, saved immediately in the native `re3.ini` as
`[General] ShowFPS=0/1`. It starts disabled. The bottom-right overlay uses a
monotonic real-time clock and a half-second sample window; a long frame gap or
disable/re-enable resets the sample. Game speed and paused simulation time do
not provide suitable clocks for measuring presented frame intervals.

The display runs in the final HUD pass shared by gameplay and frontend menus,
and restores the previous font state. It is independent of the extension's
master switch and leaves the 375-setting registry unchanged. The feature is
engine code in this source-based port, while its native preference remains a
regular user setting; putting an INI in a mod folder alone would not implement
the display.

[PR 12](https://github.com/darkcenturies/re3-extended/pull/12) merged as
[cb4d71fd](https://github.com/darkcenturies/re3-extended/commit/cb4d71fd7bd2db66fae32f442f265c846369e25b).
The complete Windows build passed, including numerical measurements at
30/60/165/240 FPS, alternating frame intervals, stale-sample resets, existing
loader/settings/blur/bind-pose checks, asset checks, installer preservation and
package hashes. Linux and Apple Silicon passed their native builds and the
same counter checks in [main run 37284348140](https://github.com/darkcenturies/re3-extended/actions/runs/37284348140).
All three platform and release jobs passed and published
[v0.1.10](https://github.com/darkcenturies/re3-extended/releases/tag/v0.1.10).
The independently downloaded installation archives passed every manifest hash,
retain the unchanged registry fingerprint, and contain the native counter/menu
labels. Published ZIPs match their Actions artifacts and published SHA-256 sums.
These are compilation, numerical and package checks; no new visual/gameplay
certification or physical Mac test is claimed.
This reference library receives the method and evidence only, without runtime
source, game inputs or private installation details.
