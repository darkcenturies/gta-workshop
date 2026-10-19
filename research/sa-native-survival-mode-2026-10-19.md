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

Mod implementation, runtime binaries, local paths, game inputs and third-party
character/texture payloads are withheld. This finding does not expand the
public tool-source scope or relicense supplied artwork.
