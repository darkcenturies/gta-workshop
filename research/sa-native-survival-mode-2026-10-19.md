# SA native survival-mode contracts and evidence limits

## Target and question

Classic GTA San Andreas PC 1.0 US, x86, image base 0x400000. Inspected executable
SHA-256: `a559aa772fd136379155efa71f00c47aad34bbfeae6196b0fe1047d0645cbd26`.
The question was how to author a separate new-game survival loop with native
pedestrians, persistent campaign/run state and zombies that can remain alive
after losing their heads.

## Method and observations

- Consulted the [Dryxio native reference route](dryxio-catalog.md) and retained
  [Plugin-SDK revision 15f15b60](https://github.com/DK22Pac/plugin-sdk/tree/15f15b60bbf74c106e1b496ff92c98764abf4605).
  A catalog entry is not an executed native validation tool.
- Compiled an authored missionless bootstrap using Sanny Builder 4.2.0.7333,
  `sa_sbl`, with its bundled stock opcode library. A named active bootstrap
  thread gives the ASI an explicit activation condition separate from story saves.
- Checked `CPed::RemoveBodyPart` at VA 0x5F0140 against the target PE code
  section and the pinned SDK's thiscall wrapper. The head parameter uses the
  pedestrian-node domain, value 2, rather than HAnim bone tag 8.
- Consulted [MTA's SetHeadless call](https://github.com/multitheftauto/mtasa-blue/blob/master/Client/mods/deathmatch/logic/CClientPed.cpp)
  and [gta-reversed's CPed implementation](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Entity/Ped/Ped.cpp).
  These support the call contract; they do not establish the prototype's actual
  living-zombie rendering, locomotion or attack behavior.
- Separate critical-hit immunity, head-removal state and remaining health.
  Prevent the native gun path from applying a second damage result when a custom
  progression layer already owns collision-tested weapon damage.
- Keep saved snapshots independent of native entity pointers and handles.
  Recreate owned entities after loading; persist health, headless state, boss
  identity, cooldowns, telegraphs and pickup values explicitly.

## Checks actually executed

MSVC optimized x86 build and bootstrap compilation passed. Isolated C++ fixtures
passed simulated run clocks at 30/60/165/240 FPS, paused clocks, chained XP
choices, distinct offers, retry and final-boss gating. Save fixtures passed a
binary roundtrip, headless-state retention, checksum rejection, invalid-state
rejection, chapter unlocking and permanent-upgrade purchase behavior.

Exact-target source/PE inspection, compilation and isolated fixtures are separate
evidence. The owner requested a local development installation for their own
testing. No native gameplay or final visual acceptance is claimed here.

## Reproduction and limits

The public methods are to pin the SDK/compiler, compare exact-target code
anchors, compile the bootstrap, and test run/save rules independently before
exercising the complete native loop. Use
[Sanny's CLI](https://docs.sannybuilder.com/editor/cli) and the
[stripped-SCM guide](https://tutorial.sannybuilder.com/stripped-scm/).
CLEO AI was not executed: no CLEO extension script was authored, and a script
validator cannot validate native hooks or pedestrian physics.

Native head removal while alive, navigation, targeting, all authored arenas,
boss balance, controller/pointer behavior, and actual restart/resume remain
gameplay acceptance gates. Installation hashes do not close those gates.

## Follow-up: a loaded ASI can remain inactive

An owner gameplay screenshot showed the ordinary player and HUD after New Game.
Live inspection confirmed that the native module was loaded. The compatibility
guard nevertheless rejected a code anchor before registering game callbacks.
The anchor was CPad::GetSteeringUpDown at VA 0x53FBD0; its live prologue was
`e9cb42a97900000075180fb7810a0100`. Resolving the relative jump led to
0x79FD3EA0 inside the loaded GInputSA.asi image in that process. These module
addresses are one observed load, not stable addresses for other launches.

That steering method was not called by the survival component. Restricting the
guard to its own native contracts avoids treating an unrelated input detour as
an incompatible game executable. Keep multiple independent code anchors and
explicit diagnostics rather than disabling compatibility checks wholesale.
Log module startup, rejected anchors, callback registration, bootstrap detection
and model readiness separately: loading, activation and visible gameplay are
different checkpoints. The revised optimized x86 build and existing run/save
fixtures passed; updated native gameplay acceptance is still pending.

## Follow-up: native combat, pause and presentation contracts

Owner testing reported sparse/passive enemies, continuing animation during
upgrade choices, an inverted menu pointer and an unwanted overhead camera.
Separate the desired behavior from any single internal explanation: repeated
task replacement is a plausible contributor to interrupted pursuit, while
freezing pedestrian translation does not pause the world simulation.

The revision keeps native combat pursuit tasks alive, uses native path following
and collision-tested jump/climb recovery, and retains a bounded pedestrian pool.
Weapon and melee contacts enter a guarded x86 thiscall damage-response adapter
at 0x4B5AC0. In the pinned SDK, the calculator is 0x14 bytes and its response is
0x0C bytes. Calls outside the owned mode retain the original trampoline path.
This separates native hit generation from authored health/progression scaling;
an animation request alone is not evidence that a shot or punch connected.

[CGame::Process](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Game.cpp)
processes input outside its paused-world branch. This permits an owned native
pause to stop AI/animation/fire while menu input continues. Do not return from
the adapter merely because its own pause bit is set, and do not acquire that
pause before initialization/model streaming is ready. A preparation screen was
observed without reaching model-ready; the loading correction uses a native
initial streaming batch, a wall-clock timeout and specific failed-model logging.
Its final native acceptance remains open.

Keep raw mouse coordinates and camera look settings separate. Menu pointer Y
must follow screen direction; native third-person follow and mouse look should
retain camera ownership instead of per-frame scripted coordinates. Compact
menu geometry can be checked independently for pointer direction, content-row
clearance and drag/resize bounds; these checks do not establish visual quality.

Native blood particles and the stock ground-pool texture are available. However,
[CPed::SpawnFlyingComponent](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Entity/Ped/Ped.cpp)
is empty in this target implementation. It does not produce detached arm/leg
geometry. Head removal and a dismemberment-mesh system are separate capabilities.

Optimized x86 run/save fixtures and compilation passed for the combat revision.
Menu/camera/loading corrections also passed geometry/input regression fixtures.
Native crowd
behavior, actual weapon contacts, frozen upgrade-world snapshots, jump/climb
success and final visuals still require owner playtesting. Desktop game control
was stopped after the owner questioned its necessity; no later UI or gameplay
acceptance is claimed.

Mod implementation, runtime binaries, local paths, game inputs and third-party
character/texture payloads are withheld. This finding does not expand the
public tool-source scope or relicense supplied artwork.

## Follow-up: moving auto-fire, civilian reactions and paused poses

The owner subsequently reached gameplay and reported a sidewalk walker,
surrender reactions when aiming, interrupted firing while moving, and models
distorting only during a custom pause and returning to normal on resume.
Those observations do not identify whether a particular pedestrian was owned
by the mode or ambient population, nor establish the distortion's root cause.

Inspect the primary and secondary task controllers together.
[PlayerOnFoot](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Tasks/TaskTypes/TaskSimplePlayerOnFoot.cpp)
can cancel a secondary gun task during movement through its normal manual
weapon path. Gun tasks also have their own movement-animation controller.
Native weapon-info pointer identity and firing-frame processing must survive
any locomotion adaptation. Do not infer native movement/shooting acceptance
from changed weapon flags or a successful build. Filter combat buttons after
pad update and before world/camera use; independently verify movement, sprint,
jump, mouse-look deltas and modal clicks remain available.

[GunAimedAt](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Events/EventGunAimedAt.cpp)
is a distinct civilian reaction event. Restricting that event for owned enemies
is narrower than disabling all events, which could suppress useful damage or
navigation responses. Distinguish random population from mission-created
pedestrians before cleaning up ambient walkers; a reused zombie skin alone
does not establish ownership.

[Ped pre-render](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Entity/Ped/Ped.cpp)
applies bone adjustments outside world simulation. Preserving the last complete
owned pose during an owned modal pause is a candidate mitigation for repeated
adjustments to frozen animation state. The reported distortion has not been
reproduced under agent control, so this remains an inference requiring paused
versus resumed comparisons, including shadows and nearby characters.

The exact-target optimized x86 native build, Sanny bootstrap and run/save/menu/
input-preservation fixtures passed. No new game control or native acceptance
was performed. The install's limit adjuster configured weapon-type capacity;
that setting alone establishes no pedestrian/task pool expansion or huge-horde
support. Stock weapon IDs do not require additional weapon types. New adapters,
runtime payloads, art and private evidence remain withheld under the existing
boundary.

## Follow-up: backwards aiming and reload ownership

Owner testing then reported a reload pose stuck until another animation and
the gun lifting while retreating. An existing runtime log records some native
hit events, so this does not establish complete firing activation failure.
Movement-dependent aim and reload completion remain separate acceptance gates.

The native player weapon controller holds AIM while the weapon is reloading.
Repeatedly issuing RELOAD is not the same contract. A gun task's destructor
detaches its callback; cleanup must also fade its animation and abort aim IK.
Keep a matching task through reload/recovery instead of replacing it at each
scheduled shot, and distinguish native reload state from animation completion.

Inspect exact-target instructions when reconstructed helper ownership is unclear.
In this PE, UseGun::AimGun at VA 0x61ED10 obtains a pedestrian target's selected
bone and offset from the **shooter's** player-data fields (0x70 and 0x74 behind
the 0x480 pointer). The inspected upstream helper suggests different ownership.
Use valid HAnim tags and distinguish them from damage-collision/removal IDs;
do not treat an incomplete reconstruction as stronger evidence than the target.

Separating movement direction from body facing is relevant to the backwards
warning-shot pose. Project camera-relative travel into body-relative gun-move
commands while the native strafe controller faces its selected target. A
synthetic geometry fixture can verify unchanged world travel across facing
angles and input paces. It does not establish animation quality, foot contact,
collision, actual firing direction or reload completion. Scaling stock
directional gun clips is not evidence of newly authored backwards sprint clips.

Two author-published candidates were reviewed:
[Proper Aiming by BirbsLeHecker](https://libertycity.net/files/gta-san-andreas/243973-proper-aiming.html)
describes constant strafing or removal of warning shots;
[SleekMovement by pedrowav](https://www.nexusmods.com/gtasanandreas/mods/3128)
describes a broader movement/pose/camera system. These are consulted candidates,
not installed or executed compatibility evidence, and their redistribution and
source permissions differ. No external implementation or assets were copied.

Optimized x86 compilation, Sanny bootstrap and five isolated run/save/menu/input/
gun-control suites passed, including reload-hold and movement-projection checks.
Seventeen guards match the exact target PE. Native retreating shots, repeated
full reload cycles, target switches, diagonal motion, movement pace and jump
transitions remain owner playtesting. Runtime source and payloads remain private.

## Follow-up: queued selection versus an equipped weapon

A later owner screenshot shows an empty-handed player while the upgrade HUD
reports a pistol rank. A read-only runtime inspection found weapon inventory
and ammunition present, but active/chosen slots both zero, no attached weapon
object and no secondary gun task. The updated runtime log records zero native
enemy hits. A rank label is therefore insufficient evidence of an equipped gun.

For the same hashed SA 1.0 US x86 target, bounded native-code execution under
Unicorn independently confirms that script opcode 01B9's player branch only
queues the chosen slot. It leaves the active slot unchanged. Copying the old
active slot back over that request cancels it; native gun-task initialization
then marks an unarmed task finished. This reproduces a specific ordering error,
rather than attributing the symptom to missing models or ammo.

The typed native selection overload at VA 0x5E6280 delegates to the slot
overload at 0x5E61F0, updates both slots immediately and requests attachment of
the correct weapon model. Distinguish an `eWeaponType` argument from an integer
slot; the overloads use different ID domains. This path preserves a partly used
clip, whereas the player's broader weapon-change routine also refills it.
The pinned SDK and
[native pedestrian selection reconstruction](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Entity/Ped/Ped.cpp)
support the signatures; exact-target instructions establish the observed writes.

The isolated probe executed original selection and initial gun-task code with
synthetic pedestrian/player/weapon data. External script decoding, pool lookup,
player classification, weapon-info/skill lookup and model attachment were
explicit stubs. All three stock firearms reproduced the old rejected task and
passed initialization after synchronous selection. Twelve firearm/start-slot
combinations preserved clip counts and requested expected model removal and
attachment. No game binary was redistributed or game process controlled.

The corrected optimized x86 build, Sanny bootstrap, five existing C++ suites and
nineteen recorded PE signatures passed. These checks establish the bounded
selection contract, not complete firing, model rendering, locomotion quality,
reload completion or compatibility with the loaded plugin stack. Those remain
owner gameplay acceptance. Runtime implementation, the private probe source,
player data and model payloads remain withheld under the existing boundary.

## Correction: reload dispatch, locomotion and competing avoidance tasks

Subsequent owner testing reproduced a frozen weapon pose and firing stopping
after a magazine. Read-only state showed an equipped pistol, empty clip,
native RELOADING state and a frozen FIRE/AIM association rather than a reload.
**The earlier AIM-only reload interpretation above is superseded:** a later
stock PlayerOnFoot branch issues RELOAD (4), overriding its earlier AIM branch.
Native StartAnim uses last-command/burst state to gate repeated reload commands;
issuing RELOAD while the weapon is reloading does not itself establish an
animation restart every frame. Read the whole controller before extracting a
state-machine rule from one branch.

A bounded Unicorn 2.1.4 / pefile 2023.2.7 probe of the same hashed executable
reproduced the old empty-clip deadlock. With RELOAD, two native StartAnim,
CWeapon::Update/Reload, finish-callback and subsequent-fire initialization
cycles passed. Animation lookup/blending, weapon-info/skill and audio were
explicit stubs, with synthetic animation progress. This establishes a bounded
reload lifecycle contract; actual playback and native shot contact remain
separate physical acceptance.

Native PlayerOnFoot dispatch also distinguishes ordinary locomotion from gun
strafing through the arm-aim flag. A scoped primary-controller flag can retain
normal movement while the secondary partial gun task supplies upper-body aim
and no root movement. The native branch dispatch was tested independently.
Removing forced heading and the gun movement controller supersedes the earlier
directional-clip scaling experiment; it does not prove rear-angle torso reach,
foot contact, sprint quality or shot accuracy without game observation.

[GunShot](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Events/EventGunShot.cpp)
and [GunShotWhizzedBy](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Events/EventGunShotWhizzedBy.cpp)
are separate civilian reactions from gun-aim surrender. An aim-event filter
alone cannot establish absence of fear/ducking. Restrict fear filtering to
owned living enemies and preserve damage, collision and obstacle events.

A read-only matching-model task snapshot contained native KillPedOnFoot ->
melee -> seek -> node-route chains, alongside temporary object/building/crowd
avoidance. The native chase task was present; its presence is not evidence
that no other task can interrupt it or that every wall can be traversed.
Fallback logic also prematurely replaced five-second native routes after three
seconds and treated crowd congestion as a stuck-world condition. Confirm world
obstruction before recovery, allow route completion and alternate detour sides.
Low-obstacle clearance and level landing checks are distinct from wall clipping.

The local optimized x86 build, five C++ suites, both bounded native probes and
twenty-two recorded target signatures passed. Actual movement, aim, reload
playback, fear suppression and representative wall traversal remain owner
acceptance. No game controls or process writes were performed. Implementation,
private probes and asset payloads remain withheld under the existing boundary.

## Follow-up: preserve weapon-specific aim and enforce duck-task ownership

Owner feedback narrowed the remaining upward-shot/pose issue: straight-ahead
aim may work, but changing direction still looks wrong. The prior secondary
weapon profile cleared the native arm-aim flag even for a pistol. Exact-target
AimGun dispatch uses that flag to choose native PointArm IK versus torso-only
PointGunAtPosition. Preserving the weapon's original method is distinct from
the temporary primary-controller override used to retain ordinary locomotion.
The previous-frame arm state can affect the separate warning-shot angle check;
do not confuse that check with the subsequent native solver choice.

The bounded probe now captures native AimGun dispatch for front, side and rear
target coordinates, retaining the same entity and HAnim torso tag. The cleared
flag selects torso-only aiming; the native pistol flag selects right-arm IK.
An existing arm chain also needs reference-safe release before changing the
torso/head bone tag on the same target; its in-use flags otherwise skip rebinding.
Native chain release and subsequent head-tag binding passed the bounded probe.
IK solvers, renderer and bone transforms are explicit stubs, so this verifies
dispatch and arguments, not actual hand position or rear-angle accuracy.

Owner testing also still reported crouching despite both fear-event filters
registering. Event acceptance, duck-task creation and duck-task execution are
separate paths. Native SetTaskDuckSecondary can create/process a duck directly;
a higher-level event filter alone does not enforce an owned-enemy invariant.
Guarding the owned living enemy's duck task before execution permits immediate
native cleanup while preserving all non-owned calls and other task classes.
The native immediate abort clears its association/callback and duck flag; a
leisure abort is a different contract. A blocked-task counter helps distinguish
future ducking from hit/kneel poses without assuming every crouch has one cause.

The extended native probe passed aim-method dispatch and immediate duck cleanup,
retaining the previous reload and locomotion checks. Five local C++ suites,
the weapon-selection probe and twenty-five target signatures passed. Physical
pose/aim and actual absence of ducking remain owner acceptance. No game controls
or process writes were used; implementation and private probes remain withheld.
