> Historical research snapshot imported on 2026-09-10. Generated output is now included in this repository. Paths to private inputs, screenshots and server code remain historical context; those files are not distributed here. Later dated observations supersede earlier claims. Revalidate against your exact binary.

# How peds get spawned, and what PECore does about it

Written to answer one question: how does Project Eagle put pedestrians on the
pavements of Vice City and Liberty City, when the game's own pedestrian path
network stops at the edge of San Andreas?

## What was done

`PECore.asi` (2,977,792 bytes, SHA-256 `a81c69ef…fff7`) was decompiled with the
existing Ghidra pipeline: **7,617 functions, none failed**. Output is in
`generated/project-eagle-core-current/`. The binary is stripped, so every
function comes out as `FUN_…` and the useful signal is elsewhere.

## What PECore hooks

PECore uses the `injector` library, whose `function_hooker` templates leave their
target address in the RTTI type name. Decoding those and resolving each address
to the function containing it, using `reference/gta-reversed`:

| Area | Hooked sites |
|---|---|
| Frame loop | `CGame::Process` +0x102, +0x197; `CGame::Init1` |
| Rendering and UI | `CCredits::Render`, `CLoadingScreen`, `CDraw::DoFade` (×4), `CMenuManager::DrawFrontEnd`, `CRadar::DrawRadarMap`, `CVisibilityPlugins::AddWeaponPedForPC`, `CMovingThings::Render_BeforeClouds` |
| Gameplay data | `CTaskSimpleFight::LoadMeleeData`, `CStats::ConstructStatLine` |
| Physics and vehicles | `CBuoyancy::ProcessBuoyancy`, `CRideAnimData`, `CAutoPilot` |

Thirty-six sites in total; a dozen more sit in ranges `gta-reversed` has not
named yet. Reproduce with the snippet in "Method" below.

**There is no hook on `CPopulation`, `CPedPlacement` or `CPathFind`.** PECore
does not replace the game's pedestrian population system, and does not need to:
it ships a bigger world and a bigger node set and lets the stock system run.

The loose `data/Paths/NODES*.DAT` are byte-identical to stock, all 64 of them,
and `pecore_gps_graph.pegg` is a road network. Both of those led me to conclude,
wrongly and twice, that no pedestrian data existed beyond San Andreas. The real
data is in an IMG archive, in a non-stock format, with wrapped coordinates.

What Eagle *does* change is the world size. `fastman92limitAdjuster` is
configured with `Apply paths limit patch = 1` and `Paths map size = 48000`
against a stock 6000, which stretches the path area grid over the expanded map.

Peds reach the pavements of the added cities because **Eagle ships pedestrian
path nodes for all of them**, in `S&S/CDimages/default/paths.img`: 4096 tiles,
508 populated, 141,434 pedestrian nodes with 73.5% outside San Andreas. PECore
needs no population hook because the stock system, pointed at a bigger node set
and a bigger world, does the job unchanged. See
`../parity/GTA_PARITY_WORKBOOK.md` and `deploy/extract-eagle-ped-paths.py`.

## The part that is fully established

The spawn and despawn policy is stock San Andreas, unhooked by PECore, and it is
exactly the behaviour we want to reproduce server-side. From
`reference/gta-reversed/source/game_sa/Population.cpp`:

### Spawning — `CPopulation::Update`

```
pcdm = PedCreationDistMultiplier()
gdm  = TheCamera.m_fGenerationDistMultiplier

AddToPopulation(
    pcdm * gdm * 42.5,     // outer band, near edge
    pcdm * gdm * 50.5,     // outer band, far edge
    pcdm * 25.0 - 10.0,    // inner band, near edge
    pcdm * 25.0            // inner band, far edge
)
```

Peds are created in a shell roughly 42.5–50.5 m out, with a second band at
15–25 m. Creation is skipped entirely during a cutscene. `CanCameraSeeAPedHere`
prevents a ped appearing in view.

### Despawning — `CPopulation::ManagePed`

- Removal distance is **54.5 m**, or **65 m** for a ped flagged
  `bCullExtraFarAway`, scaled by the camera's generation multiplier.
- **Gang peds get 30 m of extra leash**, so they persist noticeably longer than
  ordinary civilians.
- Past that distance: **fade out if on screen, delete immediately if not**.
- Inside it, being within 25 m *or* on screen refreshes a keep-alive timer of
  **4 seconds**, or **10 seconds** for police.
- Once that timer lapses and the ped is off screen, it is deleted — unless the
  camera is a sniper/camera mode or is looking left, right or behind, in which
  case it is kept.
- Dead peds fade after **30 s**, **15 s** during a frenzy, **8 s** during a gang
  war.

That last group of rules is what makes the game feel like it never despawns
anything in front of you: it is not distance alone, it is distance plus
visibility plus a grace period plus what the camera is doing.

## Method

Hook addresses are recoverable without a decompiler at all:

1. Pull ASCII strings from `PECore.asi` and keep those containing
   `function_hooker`, `PatchAll` or `scoped_`.
2. In each, find `$0([A-P]+)@`. That is MSVC's template integer encoding, base
   16 with `A`=0 through `P`=15.
3. Keep values in `0x400000..0x900000`, the game's code range.
4. Resolve each against the `RH_ScopedInstall(name, 0x…)` and `// 0x…` markers
   throughout `reference/gta-reversed`, taking the nearest preceding entry point
   within 0x800 bytes as the containing function.

## The game executable

`gta_sa.exe` 1.0 US (14,383,616 bytes, SHA-256 `f01a00ce…43ac`) is decompiled in
`generated/gta-sa-1.0-us/`: 20,820 functions of 20,823, three failed. It is
stripped, so `deploy/name-decompiled.py` matches entry points against the
addresses gta-reversed records and names **4,735** of them, about a fifth.

It was decompiled to answer the questions the parity audit could not:

| Wanted | State |
|---|---|
| `CPopulation::AddToPopulation` | Found at `0x614720`, 4,668 bytes. Not yet read |
| `CTaskSimpleFight` | Found at `0x61c470`. Its constructor clamps a duration argument to **60,000 ms**. Which field that is, most likely `m_nIdlePeriod`, is not certain enough to use |
| `CTaskSimpleBeHit` | Found at `0x620780`. Sets a field to `0xbf`; meaning unknown |
| `CPed::GetWeaponSkill` | Not located. It has no body in gta-reversed either, so there is no address to match against |
| `CTaskComplexReactToAttack` | Not located. No known address anywhere; finding it means identifying its vtable by the task number `GetTaskType` returns |

**Nothing from this has been applied to the gamemode yet.** Reading a value out
of unsymbolised pseudocode and being *fairly sure* what it means is the same
mistake as inventing it, only harder to spot later. The named index is the
durable result; the values come after somebody can say what they are.
