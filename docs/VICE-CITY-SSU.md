# Vice City Japanese PC SSU: setup, route and practice diagnosis

Checkpoint: **3 November 2026**. This guide records a converted original-PC
installation, tested practice methods and an unfinished full-route experiment.
It does not describe Definitive Edition, a completed fresh-game run, a new
glitch or a leaderboard-eligible automated performance. See the
[dated findings](../research/vice-city-ssu-2026-11-03.md) for evidence and failures.

## Start with the correct build

Use a legitimately obtained original PC installation and the community
[Japanese converter](https://www.speedrun.com/gtavc/resources/ub42v).
Steam ownership and Japanese executable identity are compatible: conversion
changes the executable and the addresses to use. Follow the converter's own
instructions rather than mixing individual executable/script files.

The tested converter was v5. Its manifest check matched all 1,421 files at
installation. The executable and script identities were checked again at this
checkpoint:

| File | Bytes | MD5 |
| --- | ---: | --- |
| `gta-vc.exe` | 5,157,888 | `9585a7dc4a89dd39e557e3f6c47efe84` |
| `data/main.scm` | 1,277,288 | `f0e8d648fd9e5ca18effe62b2a08789e` |

Steam Verify Files can replace converted files. If restoring through Steam,
repeat the complete conversion and verification before reusing JP addresses.
No reVC executable or gameplay implementation was installed. reVC was consulted
as an engine reference; its behavior still needs comparison with the native JP
binary.

[SpeedrunSilentPatch](https://ssp.gta.run/vice-city/) Build 12 was installed.
The tested configuration is:

```ini
[SilentPatch]
SkipIntroSplashes=0
WindowedMode=Framed
AlwaysOnTop=0
CpuAffinityMask=0
ReplaceDMCAMusic=1
CreateFullMemoryDump=0
```

Native display settings: **2560×1440×32**, widescreen ON, draw distance maximum,
frame limiter ON, subtitles/HUD/radar ON. The hidden capture targets 30 FPS.
A short limiter-OFF bridge comparison also failed; ON was restored before
shutdown. These are the recorded configuration and results, not a claim that
resolution or a patch alone makes SSU reliable.

## Human attempts and diagnostic practice

Check the current [game rules](https://www.speedrun.com/gtavc?rules=game),
[allowed modifications](https://www.speedrun.com/gtavc/forums/w0b2j) and
[top-three recording requirements](https://www.speedrun.com/gtavc/news/y3g51yxg)
before a submission. The recorded rule review called for a complete input
display such as SKeys; the attractive NohBoard practice layout described below
does not establish compliance. Recheck current category timing and recording
requirements rather than inferring them from this research capture.

For an ordinary human attempt, restart the game, close diagnostic memory tools,
create the route's replay during that attempt, and retain continuous source
video from before the start through the ending. Imported saves/replays are
practice fixtures. Label their provenance in records. Runtime-assisted control
and capture is also automated practice, even when every gameplay action is an
ordinary key or mouse input and the installed game files are unchanged.

[Cheat Engine](https://www.cheatengine.org/downloads.php) is optional for
diagnosis; it does not perform SSU for the player. Obtain it from its actual
upstream and verify the package/source. An OfferCore detection is not proof
that a package is harmless or proof that it is unofficial. This investigation
did not disable Defender or restore quarantined components. A separately built
CE executable was observed running, but its UI/live attachment was not validated.

The community [practice pack](https://www.speedrun.com/gtavc/resources/bcpme)
includes a table, saves and replays. For observation, use the unsigned four-byte
**SSU JAPANESE** entry without freezing or editing it. Preserve existing save
slots before installing practice resources; the tested seven slots were empty.

| Executable | SSU absolute virtual address |
| --- | --- |
| Japanese target above | `0x81EFF0` |
| Original Steam | `0x820FF0` |
| International 1.0 | `0x821FE8` |
| International 1.1 | `0x821FF0` |

Only the Japanese target was exercised here. Recheck identities for every other
build. Japanese money is `0x947DD0` (`gta-vc.exe+0x547DD0` with image base
`0x400000`); on-mission is `0x81E76C`. The unchanged community table had address
entries and no Lua/assembler scripts. A separate hash-guarded read-only monitor
also read the JP values successfully.

## Full route to learn

Follow one complete route. The main reference is the community
[SSU tutorial](https://www.youtube.com/watch?v=J8eQxBI8WWE), also linked from
the [guide](https://www.speedrun.com/gtavc/guides/ejews). The
[reference run](https://www.bilibili.com/video/BV1rNtz6nEgX/) helped inspect
movement and bridge inputs. A video title or historical leaderboard lookup is
not a timeless current-record claim.

1. **Replay setup:** start New Game, take the Faggio, start Pizza Boy, return
   to the Faggio, reach Prawn Island, use the known bridge clip, enter VCN and
   take its helicopter. Pizza Boy keeps the on-mission flag active while
   preparing the rampage replay.
2. Prepare a combined **M60 rampage + Skumole property** replay. At the rampage
   the guide uses F2, F3, F3; travel to the property and finish with F2. The
   replay must contain both locations. Its timestamp must allow the two-minute
   rampage timeout plus the time needed for the subsequent setup/dupes.
3. **Start another New Game without resetting the run timer.** Use the replay
   to acquire/fail the rampage. The guide explains why a sufficiently late
   replay can toggle the on-mission state in the new game.
4. Perform the route's **eight Pizza Boy duplications**, using the guide's
   F3, F1, F3 sequence and native mission transitions. Count actual script
   instances/confirmed events, not merely key presses. The tutorial also
   discusses a ten-instance variant; do not mix its assumptions or an older
   The Party practice route into the eight-instance route.
5. Rob the clerk for enough money for the property and final mission
   (at least 2,000 combined in the cited route), accounting for the resulting
   wanted level. Set the clerk despawn/respawn timing to the intended SSU value.
6. Obtain the required police vehicle, trigger the property replay with the
   correct purchase-button edge, manage Caps Lock/submission cancellation,
   and verify that the warp actually enters Keep Your Friends Close.
7. Defeat Lance through his required phases, defeat Sonny, retreat/hide
   immediately and survive until the native ending. Let the final cutscene
   appear in the recording. A dead Sonny alone is not proof of survival/ending.

Stages 2–6 above remain guide-derived instructions, not a claim that the full
fresh route was completed by this controller. Robbery/dupe order must match
the selected guide variant. The provided value spreadsheet spans 53567–53656
but contains crash/warp distinctions **inside that range**. Do not treat all
values in a 53.567–53.656-second interval as interchangeable. JP 53642 was
observed to warp from an imported fixture; a different SSU value can change
behavior or crash. Preserve the exact value and mission/replay state.

### Useful route locations

Coordinates are native world XYZ; some are script spawn coordinates, others
controller approach points. Pedestrian position is approximately 1.04 above
the walking surface. Do not confuse these with teleport instructions.

| Location | XYZ / note |
| --- | --- |
| Opening Faggio | about `128.4, -818.5`; model 192 |
| Pizza Boy | about `413.8, 97.7, 10.5`; model 178 |
| Safer Faggio parking approach | `425.5, 100, 10.6`; actual stop around `427.6, 100.3` |
| Prawn bridge approach | `-75, 1063`; drive stopped near `-75.4, 1065.0` |
| Bridge grass route | via `-91.5,1040`, then `-95,1044` |
| VCN ground entrance | `-410.5,1120.9,10.1`; native script trigger radius 2.5 |
| VCN roof arrival | `-446.9,1128.3,55.6`; return door near `-451.1,1128.1` |
| VCN helicopter | `-469,1123.5,64.7`; model 218 |
| M60 rampage pickup | `-789.41,592.56,11.1`; weapon 32/model 289 |
| Skumole property | `-560.1,703.6,20.5`; main-script globals 600–602 |

## Diagnose a purchase that does nothing

First distinguish a wrong SSU value, a missed purchase input, an unexpected
rampage restart, and an actual crash. They require different evidence.

In the tested JP build, file-replay playback preserves a native pad state.
A held purchase key is not equivalent to the required **rising edge**.
The successful diagnostic sequence observed R in the keyboard state, pressed
F3 at the next suitable input update, then verified pickup New=255, Old=0 and
buffer=6. A nonzero pickup buffer alone expired after a few updates and did not
make a long replay reliable. Caps Lock was held for the required submission
transition and released after purchase confirmation.

| Read-only diagnostic | JP address |
| --- | --- |
| Keyboard R sample | `0x7CE66C` |
| Pickup New / Old | `0x7D8CC0` / `0x7D8CEA` |
| Pickup buffer | `0x9B3A9C` |
| SSU / on-mission / money | `0x81EFF0` / `0x81E76C` / `0x947DD0` |

Observe the transient purchase: cash can drop by 1,000 during replay and then
be restored by replay restoration, while the purchase script still executes.
Checking final cash alone produced a false failure. Sample initial cash before
input; retain event timestamps, native mission/cutscene changes and destination.
A failed late edge can leave Vigilante active; cancelling alone does not prove
the fixture has been restored. Reload an explicit practice fixture between
isolated trials, never silently during a claimed fresh-game run.

Observed counts: 12/12 initial purchases, 9/9 complete initial warps, then
4/4 long-replay purchases/warps and 3/3 short-replay reruns after correcting
the cash verifier. These groups are different tests, not a single statistical
guarantee or a claim that every future attempt will work.

## Final mission tactics and geometry

Keep the Lance checkpoint shots used to advance the route. Do not aim at a
wall simply while waiting for mission time to pass. Clear nearby guards when
needed for survival or to prevent melee interference. Once Sonny appears,
focus him exclusively; after his death release fire and retreat/hide.

The roof has a live invisible `mansion_new_doors` object (model 2562) absent
from the static map. Standing too close can block the firing animation;
standing too far away makes shots hit the door. A tested position near
X=-339.7805 gave approximately 0.475 m separation and three M60 hits reduced
Lance 500 → 305 → 110 → dead. A later approximately 0.608 m gap was ineffective.
These are observations for that scene, not a universal wall-shooting tolerance.

Aim using the game's current aspect value at `0x94AD40`, not the output-video
aspect. An earlier 4:3 aim state was incorrectly treated as 16:9. After native
widescreen setup the observed value was approximately 1.77777779. Crosshair
coordinates are at `0xA0A92C`/`0xA0A934`. Resolution alone did not establish this.

One imported-fixture attempt defeated both bosses and reached FINALE alive.
The latest Sonny-exclusive revision failed earlier at the crowded roof; a
subsequent nearby-guard defence patch passed syntax checks but has not passed
gameplay validation. Retain that distinction when resuming.

## Recording and timer design

The accepted practice composition is minimal and dark, with **heavily blurred
live gameplay behind the whole window**, actual LiveSplit on the right and
the official NohBoard renderer below. There are no extra title/input captions.
Automation provenance stays in metadata and the accompanying report.

| Element | Rectangle X,Y,width,height |
| --- | --- |
| Output | `2560×1440`, 30 FPS |
| Full native game | `0,135,2080,1170`, uniformly scaled from 2560×1440 |
| LiveSplit | `2100,135,440,680`, native size |
| NohBoard | `2104,900,431,237`, native size with transparency |

Background: same game frame reduced to 96×54, Gaussian blur sigma 3, darkened
65%, expanded to the canvas. The game itself is neither cropped nor stretched.
LiveSplit 1.8.37 (source revision
`683cd60a9f3fe2dc31a5054c6d10f5d71f2e6ae1`) has a full-window online Vice City
coastal scenery background, slow two-pixel pan, white labels, pink decimals
and cyan completed times. Segment icons are game textures obtained locally:
save, pizza, gun, property and Tommy. This does not grant redistribution rights.
Scenery provenance is original-PC [Steam app 12110](https://store.steampowered.com/api/appdetails?appids=12110),
screenshot `0000003315`; the logo reference is
[Grand Theft Wiki](https://www.grandtheftwiki.com/File:GTAViceCity-logo-bare.png).
Artwork and original game textures belong to Rockstar Games.

Guide-derived splits: **Replay setup / Pizza Boy dupes / SSU value /
Skumole warp / Keep Your Friends Close**. They are useful milestones, not an
official mandatory list. The [upstream ASL](https://github.com/KZFREW/KZ.Autosplitters/tree/master/Releases/Vice%20City)
is configured for New Game start and final split, with automatic reset disabled.
The four intermediate events still need validated wiring. A final ASL event
cannot compensate for an incorrect current split index. Main timing is real
time; demonstration times are not PBs.

[NohBoard 1.3.0](https://github.com/ThoNohT/NohBoard) uses its original
`GamesLegacy/game_fps1_mm` geometry/render classes, configured with dark keys,
white labels and pink pressed keys. The custom input source reads only the
owned practice controls, not the user's foreground keyboard. The layout omits
F1/F2/F3/Caps; raw input logs contain them. Do not call this complete submission
input coverage or change the accepted visual design to conceal that limitation.

The tested hidden pipeline captures the native D3D8 render target, native
LiveSplit frames and process-only WASAPI audio; it does not capture the desktop
or microphone. FFmpeg/NVENC encodes H.264 High/P5/QP18, YUV420P, BT.709 limited,
AAC 192 kbit/s. Audio starts from a WASAPI QPC timestamp and is trimmed to video
start. Its source was 44.1 kHz; 48 kHz resampling is not implemented. A separate
timer-capture thread and four OpenCV/filter threads resolved an earlier timing
failure. Capture rejects over 0.25-second lag rather than silently accelerating
video. Wait for readiness and one second of warm-up before starting New Game.

A 24-second moving composition test produced 720 frames, 14 held source frames,
maximum scheduling lateness 0.1354 s and passed full decode. This establishes a
short capture test, not uninterrupted full-run performance or listened audio
acceptance. An older OBS 1920×1080/60 profile remains unvalidated and is not the
accepted hidden recording pipeline. Recheck storage before a long take and
retain at least the owner's 100 GB free-space reserve.

## Resume order

1. Reconfirm executable/script hashes and native settings. Start only an owned
   hidden session; never switch desktops or send global input without approval.
2. Solve and repeat the bridge entry **and exit**, then validate VCN access,
   flight/landing and creation of the attempt's own combined replay.
3. Validate fresh-game robbery, actual duplication counts, clerk timing and
   native purchase/cancel events as one chain. Do not substitute imported files.
4. Retest the revised finale controller through survival and FINALE.
5. Wire and verify all timer events, then record a complete fresh route using
   the accepted composition. Check continuous timing, full decode, sound,
   natural-looking controls and ending footage separately.
6. Only compare a completed, correctly timed run to a freshly checked
   leaderboard. No new glitch or record has been demonstrated here.

Sources and evidence boundaries are in the
[checkpoint findings](../research/vice-city-ssu-2026-11-03.md). Runtime adapter
implementation, game-derived geometry, practice payloads and recordings remain
outside this public knowledge repository under its publication policy.
