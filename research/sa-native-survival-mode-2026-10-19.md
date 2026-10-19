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


## Follow-up: existing zombie scripts are references, not a routing replacement

Classic SA zombie-mod comparison, 19 October 2026. No foreign runtime or animation
pack was installed or executed. A pinned public source inspection is distinct
from physical gameplay testing.

[JACKARPANJACK's Leon Kennedy / Resident Evil Mercenaries source](https://github.com/JACKARPANJACK/Leon-Kennedy-resident-evil_GTASA/tree/766c2a49818d9b3c27c383fa99c41bc556ecf0a7)
is available under repository GPL-3.0. MERCENARIES_MISSION.sc assigns native
kill-on-foot and a scripted decision-maker handle, then starts a dispatcher per
actor. Its actor arrays contain eight slots; the archetype count is different.
ZOMBIE_DISPATCHER.sc's regular-swarm branch reissues pursuit outside attack range
and applies some close attacks by animation plus direct health subtraction.
Other branches have fixed per-loop timer decrements. These are not evidence of
stable high-frame-rate, native-contact-only combat or superior wall routing.
Behavior states and ownership are useful comparisons; copying an entire
controller would also import its timing, attack and license contracts.

Original author [ZAZ / BeeswaX Zombie Alarm](https://zazmahall.de/ZAZGTASANATORIUM/zazmoddat00100/Cleo_ZombieAlarm.htm)
archive SHA-256 is
`32aca12011855ae1d576cbebf4aac04af437cef98baad81e5e98bf641702c934`.
The original package has compiled mission/launcher, replacement ped.ifp and data
configuration. Sanny Builder 4.2.0 decompiled the mission locally with exit 0 for
inspection only. Actor setup includes upper-body damage reactions and a decision
maker; pursuit includes straight-to-coordinate movement. No general climbing or
new navigation solution was established. The author warns about performance at
50 actors and shop-script interactions. No explicit reuse license was found in
the inspected readme, and no script or animation is redistributed here.

[Tamilll's Infected Zone author upload](https://www.gtainside.com/sanandreas/mods/135335-infected-zone)
describes custom AI and climbing, but its implementation was not evaluated.
The page's mixed attribution does not establish a clean reusable source/asset
permission. Treat those features as upstream claims until source and behavior
are inspected.

A key ID-domain check follows from the primary
[character command implementation](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Scripts/Commands/CharacterCommands.cpp):
SET_CHAR_DECISION_MAKER resolves its script reference before calling native
intelligence. A script literal such as 65542 or 32 is not interchangeable with a
native eDecisionMakerType. Compare task/event state and initialized decision
makers on a passive actor; do not copy magic values or continually replace a
persistent kill task. Preserve collision/navigation and require real contact
rather than disguising passivity with radius damage.

Native weather review used the pinned SDK's FOGGY_SF enum value 9 and
ForceWeatherNow short/cdecl contract. World clock and active-run duration are
separate clocks. Midnight/fog source configuration and compilation do not
establish rendered visibility, frame pacing or readable enemy silhouettes.
Runtime implementation, native probes, asset payloads and owner logs remain
withheld. This return contains source applicability and methodological findings.

## Follow-up: emission gates, isolated decisions and crash context

Target remains classic SA PC 1.0 US x86, executable SHA-256
`a559aa772fd136379155efa71f00c47aad34bbfeae6196b0fe1047d0645cbd26`, with
Plugin-SDK `15f15b60bbf74c106e1b496ff92c98764abf4605`. Checks used MSVC
optimized x86, Sanny Builder 4.2.0, pefile 2023.2.7 and Unicorn 2.1.4.
No game controls or process writes were used for this follow-up.

A task's scheduled target is insufficient to establish a valid firing-frame
target. Recheck entity lifetime, fresh plausible bone position, world obstruction
and native gun readiness at actual emission. Native Fire accepts an explicit
entity and point, while some player rifle camera branches use camera-only rays.
The bounded exact-target probe captured native instant-hit/projectile/area
dispatch for 23 ranged/throwable types and preserved the explicit target
arguments. Front, side, rear and elevated vector cases followed the supplied
point; an unready gun took the rejection branch. Partial comparative source
suggesting player RPG fire always fails was contradicted by this executable's
actual dispatch. These checks do not prove collision hits, projectile trajectories
or rendered hand/weapon alignment.

The native gun task distinguishes FIRE from FIREBURST and uses burst counters;
ordinary fight control uses command 11. Gun replacement also needs native stance,
callback and IK cleanup, beyond simply destroying a secondary task. SA's native
gun movement can lose smoothed input below its per-frame deadzone at high FPS.
Directional movement projection and task dispatch can be tested independently
from actual root motion and blending. Earlier forced-partial/ordinary-locomotion
experiments above remain historical; no single source flag establishes correct
whole-body movement. Native projectile removal may itself explode grenades or
rockets: cleanup is not automatically a harmless deletion. The bounded probe
confirmed a grenade explosion branch and a non-exploding satchel cleanup branch,
with world/audio/destructor helpers explicitly stubbed.

The pinned SDK's AddDecisionMaker second parameter misleadingly uses a profile
enum. Comparative upstream declares a PED/GROUP decision category; exact x86
code stores its low byte as that category. In this target, mission allocation
uses free slots 15–19 through an executable entry jump. A script reference, native
profile index and PED/GROUP category are three separate domains. A cloned tough
profile can remove ambient fear/body-investigation responses without editing
shared profiles or discarding damage/obstacle responses. Exact native copy,
flush, full-capacity failure, removal and reuse passed synthetic-memory checks;
removal used an explicitly empty pedestrian pool. This establishes lifecycle
contracts, not aggressive behavior or successful traversal in a live crowd.

Damage-response calculation is idempotent: a response already marked calculated
returns without applying health changes again. This branch passed a bounded
probe. A fault observed in ntdll cannot by itself be assigned to this contract.
Matching Microsoft symbols resolved the repeated fault site to
RtlpWaitOnCriticalSection; no matching game dump identified the caller. A later
failure below the population cap and before player damage is counterevidence
to treating maximum density or contact as necessary triggers. First-chance
minidump capture can preserve the actual exception context while continuing
normal exception handling; a caught synthetic exception verified this behavior.
It is diagnostic evidence, not a crash fix, and may capture a handled exception.

Seven local fixture suites and bounded selection/reload/emission/task/profile
probes passed. Save-layout expansion was checked with a frozen legacy schema,
checksum validation, migration and new-schema roundtrip; no owner data is
published. Full animation, targeting under movement, every weapon's physical
behavior, obstacle routing and repeated crash-free gameplay remain acceptance.
Runtime implementation, private test harnesses, dumps, logs and game/model
payloads remain withheld. These findings describe reusable contract checks.

Primary references: [decision manager declaration](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/DecisionMakers/DecisionMakerTypes.h),
[decision manager native wrappers](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/DecisionMakers/DecisionMakerTypes.cpp),
[pinned SDK declaration](https://github.com/DK22Pac/plugin-sdk/blob/15f15b60bbf74c106e1b496ff92c98764abf4605/plugin_sa/game_sa/CDecisionMakerTypes.h),
[gun task](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Tasks/TaskTypes/TaskSimpleUseGun.cpp),
[MiniDumpWriteDump documentation](https://learn.microsoft.com/en-us/windows/win32/api/minidumpapiset/nf-minidumpapiset-minidumpwritedump).
These sources explain interfaces; exact-target execution and explicitly bounded
stubs define the actual evidence limits above.

## Runtime counterevidence: loaded patches and weapon-specific lifecycles

Owner testing exposed a startup gap despite an unmodified executable signature
audit: fastman92 Limit Adjuster7.6's enabled weapon-type loader patched inside
the newly guarded projectile-removal routine. The guard rejected loaded code
before callback registration, leaving the ordinary player and no mode UI.
Upstream WeaponLimits.cpp redirects0x7388F5, inside the inspected entry bytes.
Disabling that unused feature, without removing the guard, restored registration,
model/menu setup and native enemy/player hit events in the next owner-controlled
run. This is observed activation, not proof of rendered aiming or stability.
Installation preflight now rejects the conflicting enabled setting. A stock
weapon roster does not require expanded type IDs; pool expansion is separate.

Further owner testing rejected constrained gun movement and reported no grenade
or extinguisher effect. The pinned SDK misnames native throw byte9 as finished;
exact callback0x61F890 sets it after wind-up, then sets byte8 only after the
release clip. Treating byte9 as final completion can cancel a throw prematurely.
The bounded callback probe reproduced both phases. Native FireAreaEffect also
emits an extinguisher shot/effect with arm readiness false; imposing an
instant-hit readiness invariant on it was incorrect. The extended probe executes
the native direction/shot/effect path with explicit manager/renderer stubs.

The exact executable's gun/reload and grenade descriptors already mark their
associations partial. Controller dispatch, native metadata and upper-body
weapon clips must be considered separately from gun-stance/root animations.
Returning primary movement/heading to ordinary locomotion and suppressing owned
gun-stance creation is a candidate correction; rendered free movement and all
weapon effects remain owner acceptance. No new physical pass is claimed from
these bounded checks, and no game control or process writes were performed.

Primary comparison: [FLA weapon loader source at646abb109014714ea6e64bf8e3f1d2bf9b63a3fd](https://github.com/fastman92/fastman92_limit_adjuster/blob/646abb109014714ea6e64bf8e3f1d2bf9b63a3fd/fastman92%20limit%20adjuster/fastman92%20limit%20adjuster/Source%20files/Modules/WeaponLimits.cpp).
Executable/game inputs, private implementation/probes and owner logs remain
withheld; this record returns the failed verification assumptions and limits.

## Further counterevidence: movement controllers can cancel melee commands

Further owner testing found intermittent fire mainly while fleeing, and a pool
cue that did not attack. Ordinary locomotion turning away from rear targets is
consistent with native arm-reach limits; selecting an arm-aim controller alone
does not establish all-angle moving fire. A candidate uses native directional
root clips with camera-world input projected against the actual body matrix,
leaving gradual body rotation to native control. Projecting against a requested
future heading and forcing the body there each frame are different contracts.
When no target exists, movement must still receive the player's travel request.

For classic SA PC 1.0 US x86, bounded execution reproduced the primary Fighter
controller submitting passive commands with a null target after manual attack
input was filtered. Native ControlFight erases the prior target and prioritizes
the larger command, so a valid automatic strike request can be overwritten before
its animation begins. Check the complete primary/secondary task sequence, not
only constructor/control arguments. Also distinguish native weapon attack range
from authored selection range: the stock pool cue uses the bat combo and a 1.6 m
weapon range. Retaining one strike through its finish callback avoids a fixed
short replacement window or every-frame commands that chain more attacks.

The extended exact-target probe executes bat attack start, a single native
collision-backend dispatch at the hit-frame crossing and finish-callback release
at 30/60/165/240 FPS. It separately selects native forward/back/left/right gun root
clips at those rates; matrix projection reconstruction passed an x86 fixture.
Animation allocation/time, contact-point transform, final collision and audio
are synthetic. These are dispatch and lifecycle checks, not proof of physical
hits, rendered root motion, freedom of movement, backward sprint quality or
loaded-plugin compatibility. Held-fire/reacquisition changes preserve real
reload and target/range/path/readiness checks. Full gameplay and stability remain
owner acceptance; no game control or process writes were performed. Private
implementation, probes, logs and game/model assets remain withheld.

Primary interfaces: [pinned Fight layout](https://github.com/DK22Pac/plugin-sdk/blob/15f15b60bbf74c106e1b496ff92c98764abf4605/plugin_sa/game_sa/CTaskSimpleFight.h),
[primary on-foot controller comparison](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Tasks/TaskTypes/TaskSimplePlayerOnFoot.cpp).
Upstream incomplete wrappers are interface comparisons; exact-target execution
and the stated synthetic boundaries define the evidence above.

## Simultaneous native volleys and firing-clock checks

Classic SA PC 1.0 US x86 separates the animation firing gate from native Fire's
weapon-state/ammunition path. Bounded execution confirmed that READY and FIRING
states can each accept Fire calls at the same timestamp. Base plus zero through
five additional calls preserved explicit entity/point arguments and consumed
native clip/ammunition on each attack. A two-round clip accepted two calls,
entered native reload and rejected the rest. This supports a bounded simultaneous
volley without rewinding timers, refilling ammo or inventing damage events.
The collision/FX/audio emission backend was explicitly stubbed; actual hits,
spread, weapon sound mixing and full task behavior remain gameplay acceptance.

For native unsynchronized firing associations, UpdateTimeStep uses association
speed. Executing native UpdateTimeStep/UpdateTime followed by the actual UseGun
fire-frame gate produced approximately 20/24/28/32/36/40 trigger crossings in ten
synthetic seconds for multipliers 1.0/1.2/1.4/1.6/1.8/2.0 at 30/60/165/240 FPS.
This validates clock/gate scaling, not the full live task loop or unlimited
continuous-fire rates. Keep reload, locomotion and other attack associations
outside the modifier's ownership. Capture the original speed so repeated frames
do not compound a multiplier; native continuous-fire/frame caps still apply.

Every additional target-dependent emission needs fresh ownership, live target,
range and path checks; a previous ray can kill the target before the next one.
Clip exhaustion and absent targets are early-stop conditions. Persistent new
upgrade fields require frozen legacy layouts, validated migration, new-schema
roundtrip and a read-only check of permitted actual data. No owner data is
included here. New native/source probes passed with these stated synthetic
boundaries; rendered combat, ammunition HUD, reload transitions, saved choices
and stability remain unaccepted. Private code/probes, logs and game assets are
withheld.

Primary interfaces: [pinned weapon declaration](https://github.com/DK22Pac/plugin-sdk/blob/15f15b60bbf74c106e1b496ff92c98764abf4605/plugin_sa/game_sa/CWeapon.h),
[pinned animation time methods](https://github.com/DK22Pac/plugin-sdk/blob/15f15b60bbf74c106e1b496ff92c98764abf4605/plugin_sa/game_sa/CAnimBlendAssociation.cpp).
Exact executable probes, rather than interface names, establish the bounded
state/clock observations above. No game control or process writes were used.

## Primary locomotion ownership and shared chase gait

Classic SA PC 1.0 US x86 separates ordinary player travel from target-facing
weapon movement. Bounded exact-executable execution confirmed ordinary input
travel heading, acceleration and sprint-state selection at 30/60/165/240 FPS.
Pad, surface and stamina inputs were synthetic. Selecting that branch is not
sufficient by itself: native gun stance cleanup resets primary and cached move
state to standing even when no gun stance association exists. Secondary attack
processing and cleanup must respect the primary movement controller's ownership.
This supersedes treating directional weapon-root clips as ordinary GTA running.

Shared animation names alone do not guarantee matching chase pace. Native NPC
movement chooses walk/run/sprint separately, and its animation-rate calculation
varies with the pedestrian's random seed and base movement rate. Bounded tests
reproduced both clip selection and seed variation. The stock gang1 movement set
contains walk_gang1, run_gang1 and sprint_panic. A shared gait contract must
specify the group, requested movement state and playback rate while preserving
native collision, routing, jump/climb and attack transitions. Equal unobstructed
gait capability does not imply identical ground speed in crowds or while turning.
Do not use position or velocity rubber-banding as evidence of matched locomotion.

Native arm reach still limits firing behind a body that faces travel. Ordinary
movement does not establish unrestricted backward fire or rendered upper-body
blending. Exact-target probes and source builds passed with synthetic animation
allocation and external boundaries; physical displacement, rendered gait,
complete combat/task behavior and stability remain unaccepted. No game control
or process writes were used. Private implementation/probes, logs and game assets
remain withheld.

Primary interfaces: [pinned pedestrian movement declarations](https://github.com/DK22Pac/plugin-sdk/blob/15f15b60bbf74c106e1b496ff92c98764abf4605/plugin_sa/game_sa/CPed.cpp),
[pinned animation groups](https://github.com/DK22Pac/plugin-sdk/blob/15f15b60bbf74c106e1b496ff92c98764abf4605/plugin_sa/game_sa/enums/eAnimations.h),
[primary on-foot controller comparison](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Tasks/TaskTypes/TaskSimplePlayerOnFoot.cpp).
These declarations and comparisons support interface interpretation; exact-target
execution with the stated synthetic boundaries defines the observations above.

## Blocked gun poses, cached aim bindings and reload recovery

Classic SA PC 1.0 US x86 has distinct gun-obstruction responses. Bounded exact
ProcessPed execution reproduced a stopped/fading non-arm firing association,
a blocked-state flag and LastCommand becoming AIM. Clearing the obstruction
alone did not resume that association. Native ClearAnim detached its callback,
cleared the association and command, and allowed original processing to start
a new playing FIRE. The arm-aiming pistol branch instead set SkipAim and did
not call AimGun; removing the obstruction restored entity/bone aim dispatch.

UseGun also caches whether arm/look aiming is bound. Native arm-task lookup can
return absent while that cached bit remains set, preventing a new binding attempt.
Check actual task presence rather than interpreting the cached bit as successful
allocation or a solved pose. Retrying a missing binding does not establish aim
readiness; keep the actual native readiness result and world muzzle path checks.

The new bounded probe executes two blocked-pose -> native RELOAD/refill -> finish
callback release -> FIRE transitions. It verifies native command/association and
ammo state, with synthetic animation allocation/progress and external IK solver,
render/collision and audio boundaries. This is stronger than testing a constructor
or command alone, but does not prove a rendered pose or the complete live loop.
The native obstruction response is a candidate mechanism; a firing stall with
ammo remaining does not by itself identify its live internal cause.

Preserve primary movement while recovering secondary attacks. Select a visible
living target within the current pose's native aiming reach rather than retaining
an unreachable target indefinitely. With no eligible target, finish a reload and
retire the attack through its native lifetime; do not delete a task from its own
processing stack, manufacture readiness or rotate the player's travel heading.
Full aiming/reload usability and stability remain acceptance gates. Private
implementation/probes, player logs/data and game assets remain withheld.

Primary comparison interfaces: [native gun task](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Tasks/TaskTypes/TaskSimpleUseGun.cpp),
[IK task binding manager](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Ragdoll/IKChainManager.cpp).
Upstream comparisons are not proof of the owner's executable; the exact-target
execution and explicit synthetic boundaries define the observations above.


## Full-bearing arm reach, reserve ammunition and separate HUD commands

For classic SA PC 1.0 US x86, extending target selection alone does not extend
native arm reach. An isolated exact-executable probe created the native arm task,
then executed the articulated four-node arm solver and its real facing-target
query. A synthetic rig reached fifteen front/side/rear bearings including both
representations of 180 degrees when only its arm joint bounds were temporarily
extended. Original bounds were restored after each solve; body pivot position
was preserved. This is solver evidence, not a rendered character acceptance test.
Two-handed grip, skin deformation, live animation/collision and complete gameplay
remain open. Matrix/vector math and the target bone provider were explicit
synthetic boundaries; native quaternion rotation and clamping executed.

Exact target evidence matters when a comparison implementation differs. The
inspected native arm creation selected pivot tag 4, whereas the current upstream
comparison selected 5. Verify actual argument domains, bone order, entity target,
slot, sizes and offsets against the supported executable before choosing a hook.
Keep changes scoped to the owned player, active target and expected arm chain;
do not broaden shared global bone tables or manufacture a readiness result.

The stock weapon fire path preserves a reserve count of 99999 while depleting
the magazine and entering its normal reload state. Exact native execution
reproduced this for all thirteen bullet gun types with the no-reload cheat off.
A reserve maintenance policy therefore need not refill magazines or overwrite
reload deadlines. An ammunition count alone cannot identify every firing stall.

Sanny Builder 4.2.0 distinguishes DISPLAY_RADAR (0581) from DISPLAY_HUD (0826).
Exact native handlers confirmed that radar visibility writes an inverse hide
flag, while HUD visibility writes a direct display flag. Reversing these commands
can hide health/weapon/ammo/money while leaving radar visible. Test both commands
and their actual consumers independently; a source symbol or successful build
is insufficient visual proof.

Restricting an upgrade pool also need not shrink historical save arrays. Preserve
stable identifiers and validate the old save before normalizing newly excluded
pending offers. Source fixtures covered retained ranks/cash/progression and fresh
eligible offers. This records compatibility method, not player data.

The optimized x86 build, ten source/Windows fixtures, installation regression and
nine bounded native probes passed locally. No desktop/game control or process
writes were used. Private implementation/probes, logs, player data and game
assets remain withheld. Full visual/gameplay acceptance remains pending.

Primary comparisons: [arm task](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Tasks/TaskTypes/TaskSimpleIKPointArm.cpp),
[arm chain](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Ragdoll/IKChain.cpp),
[bone node](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Ragdoll/BoneNode.cpp),
[Sanny opcode library](https://github.com/sannybuilder/library).
Upstream comparisons support interpretation; they do not override exact-target
observations or establish permission to redistribute the game executable.


### Native paired rendering, item art and run persistence boundaries

Classic PC weapon rendering has a separate local twin-weapon branch from gun
task animation/targeting. Bounded native execution submitted the same weapon
model at right/left hand bone matrices (tags 24/34); paired aiming bound the same
entity/bone to both arms, and frame dispatch called both native FireGun hands.
Stock paired group selection passed reload -> refill -> callback release -> fire
with synthetic animation time/allocation. Renderer/transform/lighting providers
were synthetic: submission count and matrix choice do not establish a rendered
paired pose, deformation, muzzle appearance or live reload usability. Arbitrary
long-gun pairing remains a separate animation/model compatibility question.

The native HUD's icon route appends ICON to the model key and searches its loaded
texture dictionary. Exact hash/search execution, including a missing-icon return,
passed against synthetic dictionaries; CRT ASCII uppercase was substituted.
Borrow texture identity for a draw without deleting or retaining it. Do not equip
a weapon or alter inventory just to show its icon. Native player jump input has
an independent disable flag; a bounded query reproduced suppression and recovery
when the original flag was restored. NPC scripted traversal is a separate owner.

A temporary build, deliberate suspended run and permanent campaign have distinct
lifetimes. Decision rarity can be derived from saved decision state without
advancing RNG on redraw; displayed gains must match applied capped gains. Stable
legacy layouts can migrate to a new schema carrying per-weapon paired state.
Source fixtures covered rarity weights/caps, save stability and retiring only a
starter weapon while keeping other unlocked attacks. Removing timed checkpoints
need not remove quiet result/purchase persistence or the atomic writer.

Ten bounded native probes and ten source/Windows fixtures passed locally after
these additions. Menu layout previews were checked at desktop/narrow sizes; they
are authored previews, not native gameplay screenshots. Full paired appearance,
rear grip, menu usability, movement and crash stability remain physical acceptance.
No game control/process writes were used. Private implementation/probes, logs,
player records and game assets remain withheld.

Primary comparisons: [weapon-list renderer](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/VisibilityPlugins.cpp),
[native HUD](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Hud.cpp),
[pinned input layout](https://github.com/DK22Pac/plugin-sdk/blob/15f15b60bbf74c106e1b496ff92c98764abf4605/plugin_sa/game_sa/CPad.h).


### Unsupported reload animation domains and sustained automatic attacks

A captured classic PC1.0 US x86 fault was an invalid animation hierarchy read
inside native uncompression. The native caller requested reload animation226
from group29; its stock descriptor contains only fire224. Static association
lookup indexes by animation ID minus group offset without a retail bounds check.
A bounded exact-executable reproduction with a one-entry synthetic association
array and invalid adjacent hierarchy reproduced the same failing instruction.
This establishes the missing-animation failure mechanism, not every reported
crash cause. Captured dumps/registers and private implementation remain withheld.

Do not interpret every weapon's RELOADING ammo state as a request for a reload
animation. Check both native weapon flags and the target group's animation domain.
The original native weapon Update/Reload also supports timed refill without a
reload clip. Probes parsed the permitted local stock weapon data and executable
descriptors for seventeen enabled gun types, then executed empty clip -> valid
animation request -> native refill -> fire. Shotgun/flame/spray groups without a
reload clip were covered alongside normal and paired reloads. Animation time/
allocation, audio and rendering remain synthetic; full gameplay is separate.

Native AIM1, FIRE2, FIREBURST3 and RELOAD4 are different command domains. Held FIRE2
frame requests passed repeated synthetic loops with an exhausted burst counter.
The earlier FIREBURST3 command also passed that bounded loop: it is not established
as the cause of live intermittent firing. Keep a usable current attack until a
replacement can obtain the required native task reserve. Preserve target/readiness/
world-path checks and log allocation pressure rather than forcing aimless shots.

Defensive offer checks belong at loading, live selection and presentation boundaries,
including enabled IDs, uniqueness and conditional eligibility. Reject unknown IDs
before indexing card arrays. A previously reported forbidden card was not reproduced
by the generator; record that uncertainty and log actual displayed names/IDs so the
next report has evidence. Do not treat changing a filter as proof of the original
cause. Per-weapon unlock masks remain independent of rarity labels or colors.

Local optimized x86 build, ten source/Windows fixtures and eleven bounded native
probes passed. No desktop/game control or process writes were used. Physical
animation, sustained movement/fire and crash-free runs remain acceptance gates.


### Whole-skeleton visual facing over unchanged locomotion

A 20 October 2026 investigation separates a requested visual facing direction from
the ordinary classic PC1.0 US movement controller. Changing a pedestrian's
physical heading or installing an aim-owned locomotion task would change travel
behavior. A temporary root pose rotation during skeleton-matrix evaluation can
instead turn all visible descendants while restoring the original pose data
before movement/animation processing resumes. The existing gait is retained;
this alone does not supply backwards/sideways footstep clips or guarantee grip.

The target uses a custom 28-byte skinned blend frame beginning with a quaternion;
it is not the standard RenderWare frame with an interpolation header. Validate
frame stride, callback identity, hierarchy/node domains and lifecycle before
using a pose pointer. Restrict changes to the intended pedestrian and restore
the original quaternion after every evaluation; do not retain model pointers
across replacement or teardown. Arms can still use their independent native
chains against the newly evaluated torso matrix. Paused evaluation and target
loss need explicit behavior and live acceptance, rather than stale pointer reuse.

A compiled pose-helper fixture supplied quaternion samples to exact native
entity/hierarchy/custom-frame routines running in isolated x86 emulation.
A seven-node synthetic branched rig covered 13 yaw angles and 3 repeated evaluations;
all descendant matrices, including both legs, rotated as expected. Both native
arm chains reached 5 front/side/rear bearings per body yaw. Entity/player bytes
and root translation remained unchanged. Source checks verified exact quaternion
restoration. A separate ordinary locomotion probe still passed at 30/60/165/240 FPS.
Clump/skin/hierarchy providers, rig and selected matrix/math boundaries were
synthetic. These results do not verify actual skin deformation, foot contact,
paused appearance, camera feel or sustained gameplay. No game control/process
writes were used. Eleven source/Windows fixtures, twelve bounded native probes
and the local package regression passed; runtime acceptance remains open.
Private implementation/probes, player data, logs and assets remain withheld.

Primary comparisons: [entity hierarchy update](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Entity/Entity.cpp),
[custom frame layout](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/RpHAnimBlendInterpFrame.h),
[bone-node operations](https://github.com/gta-reversed/gta-reversed/blob/master/source/game_sa/Ragdoll/BoneNode.cpp),
[pinned SDK frame layout](https://github.com/DK22Pac/plugin-sdk/blob/15f15b60bbf74c106e1b496ff92c98764abf4605/plugin_sa/game_sa/AnimBlendFrameData.h).
Upstream interpretation was checked against the locally permitted target, not
used as a substitute for exact-target evidence or redistribution permission.
