# Japanese Vice City SSU practice and capture checkpoint

## Target and question

Investigate an unreliable SSU final warp, prepare a Japanese PC installation
converted from Steam, develop ordinary-input automated practice in an isolated
Windows desktop, and record a full New Game route. Work was paused by the owner
on 3 November 2026. The [setup/route guide](../docs/VICE-CITY-SSU.md) preserves
the reusable procedure; this record preserves evidence limits and failed work.

Target: original 32-bit Japanese `gta-vc.exe`, image base `0x400000`. Addresses
below are absolute VAs, not offsets applicable to Steam after conversion.

| Input | SHA-256 |
| --- | --- |
| `gta-vc.exe`, 5,157,888 bytes | `d3415027499d15589a33fef4acde90b940d17fd6d47a5b617d791cc361e5aaf8` |
| `main.scm`, 1,277,288 bytes | `878e4b5dda0952af06a9a04dc6c9ac6b8f3166eed9a89966550e8b51e065254d` |
| SpeedrunSilentPatchVC Build 12, 153,600 bytes | `8459f2f4b28467e334517ababaf59e499d6af7437f1f76a560bcb061f1a8ef03` |

These three hashes were reread at handoff. The complete 1,421-file converter
manifest match is earlier installation evidence, not a new full-tree audit.

## Follow-up on 25 November 2026

The Japanese executable and `main.scm` matched the guide's MD5 values. A fresh
automated practice attempt reached Prawn Island with Pizza Boy active and full
health, exited through the bridge deck, crossed to Downtown and entered VCN.
Work ran on an isolated Windows desktop with the frame limiter on.

The entry approached the grass via `(-91.5,1040)` and `(-95,1044)`. From there,
the landing-aware run-and-jump controller aimed at `(-102,1056)`, then used
diagonal W+D with jumps toward `(-104,1058)`. Straight run-and-jump targets
`(-127,1074)` and `(-134,1077)` brought Tommy to approximately
`(-134.52,1077.28,9.67)`. On the next target, `(-167,1083)`, he came out above
the road at `(-140.96,1078.73,12.40)`. Health remained 100 and Pizza Boy stayed
active. Walking west on the road to `(-365.74,1085.01,16.70)` confirmed the
exit. This sequence gives alignment targets for one observed crossing.

A second fresh approach reached the same parking area with 100 health. It
landed farther east and lower in the water on entry at approximately
`(-101.5,1053.3,5.58)`. Health fell to 80 on the next approach and to 57 during
an attempted return to grass. The sequence therefore needs a more precise
takeoff and landing check before it is suitable for an unattended full take.

The route went around the west end of the roadside railing near `(-427,1106)`
before approaching the VCN door. After the roof transition, the first ramp
needed a southerly approach near `Y=1119`. The upper ramp returned west near
`Y=1124`. The player boarded the VCN Maverick through the normal vehicle key.

The flight probe measured W lift, Q increasing world heading and NumPad 9
pitching the nose down. A westbound flight cleared the building by the helipad
before turning south. Static collision showed a building about 191 world units
high on the direct line to the M60, so the controller routed west first. Pizza
Boy expired during the extended probes. A detour to land near the Downtown
pizza shop ended with zero player health and a hospital respawn. The cause of
the death was undetermined. This established flight through Downtown, with the
M60 landing, combined replay and remainder of the fresh route still open.

The capture preflight rejected even a five-second take under the configured
100 GB free-space reserve. This follow-up produced no continuous run video.

### Revised finale practice

The imported practice setup reached Keep Your Friends Close using the native
replay pickup and property warp. The first test stopped on the stairs at 5.3
health, with Lance still alive. The direct roof route had waited until guards
were within four units. The revision responded to visible guards facing the
player within twelve units and kept the M60 equipped on the exposed climb.

On the next practice attempt, Lance went down at 102.79 seconds with 96.05
player health. Sonny went down at 143.28 seconds. Every sampled firing action
during Sonny's combat phase targeted Sonny. The controller released fire and
retreated 7.62 units before `FINALE`, which ran with 100 player health. A still
showed Tommy and Ken on the mansion stairs. The sampled record confirms Lance
fire at phases 5 and 8 and the roof. It showed aim at phase 11 without a
confirmed shot there. The test validates this finale from the imported setup.
Fresh replay creation, the complete New Game route and a timed recording
remain open.

## Method and sources

The Workshop native/analysis/authoring/presentation routes and
[Dryxio inventory](dryxio-catalog.md) were consulted for applicability. No CLEO
script was authored, so CLEO AI was not executed. No public Valkyrie synthetic
demo is claimed to validate this native gameplay experiment.

- Community [converter](https://www.speedrun.com/gtavc/resources/ub42v),
  [practice pack](https://www.speedrun.com/gtavc/resources/bcpme),
  [SSU troubleshooting](https://www.speedrun.com/gtavc/forums/55lp1),
  [address discussion](https://www.speedrun.com/gtavc/forums/v5z8q).
- [Tutorial](https://www.youtube.com/watch?v=J8eQxBI8WWE) and
  [reference run](https://www.bilibili.com/video/BV1rNtz6nEgX/).
  Bridge source interval 675–691 seconds was reviewed, including visible keys.
- [reVC Ped](https://github.com/mrxenginner/reVC/blob/miami/src/peds/Ped.cpp),
  [PlayerPed](https://github.com/mrxenginner/reVC/blob/miami/src/peds/PlayerPed.cpp),
  [Vehicle](https://github.com/mrxenginner/reVC/blob/miami/src/vehicles/Vehicle.cpp)
  and controller/collision/file-loader source. These were downloaded branch
  references, not a pinned replacement engine or proof of exact JP equivalence.
- DK22Pac [plugin-sdk](https://github.com/DK22Pac/plugin-sdk/tree/master/plugin_vc/game_vc)
  layouts, pool and collision declarations; native observations used to check
  the actual target. No universal offset compatibility is claimed.
- [LiveSplit](https://livesplit.org/downloads/),
  [ASL](https://github.com/KZFREW/KZ.Autosplitters/tree/master/Releases/Vice%20City),
  [NohBoard](https://github.com/ThoNohT/NohBoard), FFmpeg 9.0.1, Python 3.11,
  NumPy/SciPy/Pillow/OpenCV/pywin32/pefile; native C++ and C# helper builds.

Public-safe reproduction is: obtain the exact permitted game target and
community fixtures, observe the JP table without writes, execute the tutorial
inputs, and record SSU/on-mission/purchase transitions, destination and result.
The local automated harness is not published or presented as a portable tool.
Its start-up injects a temporary input/render adapter and modifies runtime
instructions. Gameplay telemetry is read-only; ordinary keys/mouse perform
movement, firing, replay/menu actions. No player/health/position/SSU/mission
values are written. Native world queries update normal engine query caches.
This is distinct from an entirely unmodified process or a human submission.

## Initial observations and incomplete work on 3 November

| Area | Evidence | Remaining limitation |
| --- | --- | --- |
| Installation | Converter manifest matched; JP binary/script/patch hashes retained | Future Steam verification can undo conversion |
| Purchase timing | 12/12 initial purchases; 9/9 complete initial warps; later 4/4 long and 3/3 short reruns | Different groups/fixtures; no guarantee |
| Finale | Lance at 91.644 s, Sonny at 141.617 s; FINALE reached alive | Imported fixture; edited-out verification pause is disclosed |
| New Game opening | Native menu start, Faggio, Pizza Boy, return and Prawn arrival exercised | Traffic can knock rider off or block driver; recovery not integrated |
| Bridge | One revised entry reached the interior without health loss | Repeated exits stuck at collision/launch obstruction; full crossing unverified |
| Presentation | Accepted moving 24-second native composition; full decode passed | Full-run capture, complete input coverage and listened audio acceptance pending |
| Latest finale revision | Sonny-only target selection and nearby-roof-guard defence in source | Latest regression failed before Sonny; subsequent guard fix syntax-only |

The successful finale video is 168.267 seconds, 1080p/30, H.264/AAC. Its local
result record establishes the observed ending, not completion of the fresh
setup route. The final cutscene helper's later scripted-pass check returned
false; that does not erase the visually observed FINALE, nor establish credits
or every mission-completion global. Keep the actual acceptance condition clear.

The controller uses classical geometry/A*/utility/feedback methods. It is not
a trained neural agent or a vision-only player. Bounded smoothed mouse input
does not, by itself, establish natural-looking human performance.

## Failure details worth retaining

### Replay purchase

Long replay playback needs a preserved purchase rising edge (New=255/Old=0),
not merely a nonzero six-update pickup buffer. A held key can miss the purchase.
Cash restoration after replay caused one false verifier failure; the start
sample was also initially taken too late. Verify the transient deduction and
native mission/cutscene transition. An intentionally late edge was rejected
and left Vigilante active, requiring explicit fixture recovery.

The combined M60/property fixture once purchased successfully but restarted a
rampage instead of producing the desired warp. Later native combined-replay
pickup/fail followed by the short property replay resolved imported fixture
preparation. This does not validate a self-created combined replay in a fresh run.

### Roof obstruction and aim

Static collision missed a live mission door. Native queries identified model
2562 at the mansion roof doorway. First-person rays hit it; extremely close
third-person firing could be blocked by the attack obstruction test; close
guards could cause melee instead of gunfire. Approximately 0.475 m separation
worked in the tested scene. Read native aiming aspect instead of assuming the
video aspect. Keep Lance checkpoint shots, avoid idle wall aim and focus only
Sonny once he appears. Native script restoration of health/armour at that phase
must not be misreported as controller health writes.

### Initial bridge crossing failures on 3 November

The known Prawn Island clip was investigated, not discovered here. Grass
arrival near `(-94.46,1043.26,9.20)` is player center. A landing-aware normal-run
probe moved to `(-98.11,1047.12,7.76)` and then
`(-102.27,1056.59,7.11)` without health loss. Earlier fixed-interval probes
sometimes landed short, and continuing blindly led to water and health loss.

Inside the bridge, attempts repeatedly stopped around X=-135 to -142,
Y=1068–1088, center Z≈10.0–10.45. The road is `road_downtown16` (2057);
the underside is `doontoon76` (1992). Read-only native rays found a sloped
collision face blocking forward movement near the feet, as well as road
collision above. Jump state 41 with zero vertical speed and landing flags
matched an aborted launch, not an actual ascending jump.

reVC's `FinishLaunchCB` checks two small spheres above/forward of the ped and
plays a hit-head animation if blocked. That is a useful hypothesis for the
observed abort, not a complete root-cause proof for all JP attempts. Fixed
intervals, landing-aware jumps, normal run, sprint, W+D diagonal input,
backtracking, different interior lines, stationary jump and a short frame
limiter-OFF comparison did not produce a verified exit. ON was restored.
The last position before stopping was about `(-140.18,1069.86,10.16)`, health
97.10, SSU 122672, on-mission 1. This process state was not saved and is not a
resume fixture. The process was closed on request.

Do not keep presenting a launch-position theory as a solved crossing. Flight,
fresh replay creation, robbery, duplication and clerk timing still need their
own runtime validation after this blocker is solved.

### Capture timing

An initial moving composition could not sustain real time (about 16 FPS) and
was rejected. Separate native timer capture from the video thread; use bounded
thread counts and a real-time lag guard. The accepted test had 720 frames,
14 held frames, maximum lateness 0.1354215 s; after the first second maximum
0.0928586 s and 95th percentile 0.0789189 s. A decoded short test does not prove
hours of continuous recording. Retain QPC audio alignment and raw input logs.

## Read-only telemetry reference

These were used for the exact JP hash above. Validate data layout and semantics
before reusing them. Pointers must be checked during loads and pool changes.

| Domain | VA or offset |
| --- | --- |
| Player pointer | `0x947D30` |
| Player position / forward / velocity | ped `+0x34` / `+0x14` / `+0x70` |
| Ped state / health / armour | `+0x244` / `+0x354` / `+0x358` |
| Vehicle pointer / weapon array / current slot | `+0x3A8` / `+0x408` (24-byte entries) / `+0x504` |
| Wanted pointer / level | ped `+0x5F4`, then wanted `+0x20` |
| Ped pool / vehicle pool | `0x97C2B4` / `0xA0CDF4`; tested strides `0x6D8` / `0x5DC` |
| Script space | `0x81E288`; global index × 4 |
| Lance phase / handle | globals 5019 / 5017 |
| Sonny phase / handle | globals 5025 / 5023 |
| Mission clock / boss deadlines | globals 4811 / 5018 / 5024 |
| Camera | `0x7E1690 + 0x188 + activeByte(0x7E1690+0x76) × 0x1CC` |
| Camera mode / front / source / up / FOV | `+0xC` / `+0x168` / `+0x174` / `+0x18C` / `+0xB4` |
| Aim aspect / crosshair | `0x94AD40` / `0xA0A92C` / `0xA0A934` |
| Native frame limiter setting | byte `0x86665D` |

Static extraction covered 4,131 collision models, 9,114 placements, 381,421
triangles and 9,216 spheres without unmatched placement names. Paths contained
14,732 nodes and 15,266 links; the driving graph is undirected and does not
establish correct lane use or traffic handling. Mansion navigation had 41,159
candidate floor nodes. Script-byte comparison matched 37/40 explicit actor
spawn sites and 23/23 trigger volumes; the three unmatched sites were credits
civilians. Dynamic/offscreen/random conditions prevent treating spawn maps as
a deterministic enemy schedule.

## Preservation, scope and next acceptance

The local checkpoint retains source, inputs, binaries, configuration, logs,
maps and recordings in place, with a hashed manifest and operational restart
instructions. No duplicate game tree or precautionary archive was created.
Public publication is documentation only: runtime adapters, copied game assets,
practice payloads, game-derived geometry and media are withheld under
[PUBLICATION.md](../PUBLICATION.md). Source references retain their original
attribution and rights; source consultation does not relicense vendor content.

At pause, owned game/timer/input/capture processes were stopped and the foreground
desktop and user-owned Cheat Engine were not controlled. The guide records the
approved composition; redesign is not the next task. Solve the bridge, validate
the fresh setup chain and revised finale, wire the four intermediate splits,
then capture and inspect a complete run. No record/top-ten result or new faster
glitch is claimed.
