# GTA III development methods and public findings — 2026-10-11

## Question, target and evidence boundary

Which lessons from source-integrated GTA III development can become reproducible
public tools without distributing game inputs or runtime implementations?
This return covers source, formats, menus, assets, worlds, saves, rendering,
population, timing, recordings and publication. It supplements existing
[character-rig](re3-sa-character-rigs-2026-10-04.md),
[renderer](re3-distant-coronas-2026-10-04.md),
[loader](re3-modloader-callbacks-2026-10-04.md),
[script-assertion](gta3-pager-extension-2026-10-03.md) and
[historical restoration](gta3-darkel-reconstruction-2026-10-03.md) findings.

Source reviewed: public gta3-faithful revision
[`ed918ec17d37149bb639d272846cd35dc191ea7e`](https://github.com/darkcenturies/gta3-faithful/commit/ed918ec17d37149bb639d272846cd35dc191ea7e).
Its source integration pins Extended engine
`f8142f1a7cefcfd6bcd778ed8802e21c93b97c91`.
Descriptions of prior native/installation checks below come from committed
developer records, not a new game run in this contribution. The nine new
[standalone tools](../docs/VALKYRIE-DEVELOPMENT-TOOLS.md) execute offline analysis
and synthetic checks. Their reports always distinguish that from gameplay.
The [searchable record set](gta3-public-findings.json) uses `inspected` for this
source/documentation review and preserves separate limitations for each subject.

The required [Dryxio routes](dryxio-catalog.md) were consulted for scripting,
engine, graphics and authoring applicability. CLEO AI was not executed: these
commands analyze supplied SCM/schema or measured records rather than authoring
a CLEO source program. No new adoption or execution of those external tools is
claimed. Original upstream notices and the existing evidence ledger are retained.

## Scripts, worlds and restoration

1. **SCM format must match the interpreter.** GTA III tagged float literals use
   signed 16-bit fixed point divided by 16. Debug declarations can omit variable
   argument tails or differ at particular opcodes. Decoding must bound every
   section/argument and validate branches against actual instruction starts.
   A text search, a decoded name or a retained engine function does not establish
   a surviving character mission. See the pinned
   [SCM helper](https://github.com/darkcenturies/gta3-faithful/blob/ed918ec17d37149bb639d272846cd35dc191ea7e/tools/scm_gta3.py)
   and the existing assertion finding. `valkyrie-scripts` requires a supplied
   exact-target schema and does not bundle the interpreter or extracted scripts.

2. **An optional conversion is a separate world contract.** World files should
   stay outside paths where a disabled world could activate through ordinary
   mod loading. Validate referenced files, retain the complete supplied script,
   freeze selection before streaming, and fall back when the pack is incomplete.
   The pinned [Upstate records](https://github.com/darkcenturies/gta3-faithful/blob/ed918ec17d37149bb639d272846cd35dc191ea7e/docs/UPSTATE.md)
   describe hash verification and separate save profiles; they explicitly leave
   full gameplay verification with the owner.

3. **Expanded capacities do not imply stock save compatibility.** Static runtime
   capacities, serialized stock lengths and an optional world's block lengths
   are separate contracts. Validate length/profile before calling native loaders
   and retain stock cull/cache shapes when stock mode is selected. Historical
   retail conversion saves are not automatically valid for the source host.
   `valkyrie-saves` validates supplied bounds/lengths; it does not discover them.

4. **Texture/name/ID resolution requires its own audit.** The
   [campaign adaptation](https://github.com/darkcenturies/gta3-faithful/blob/ed918ec17d37149bb639d272846cd35dc191ea7e/docs/GTA3D-CAMPAIGN.md)
   records displayed model names disagreeing with actual IDs and special actor
   geometry needing its matching texture dictionary. Some old DFFs contain valid
   trailing data outside inaccurate outer sizes; blindly trimming at that size
   can lose required content. Preserve original inputs and audit format context.

5. **Radar artwork has a measurable round-trip contract.** The locally supplied
   world's 28 radar overrides are combined with 64 base tiles, retaining the
   declared world bounds, then composed into nine pause-map textures. Decoding
   the produced native TXD must reproduce the intended pixels. Successful map
   generation does not prove world alignment or navigation in gameplay.

6. **Recovery and authorship remain different categories.** The historical
   catalogue documents retained assets, disabled code, platform differences,
   existing upstream features, proposals and reconstruction separately. Camera
   pickups/mines retain mechanics, but chosen world placement is authored.
   Busker models can survive while performances, audio and tipping rules are
   authored. No authentic missing Darkel missions or dialogue were recovered.
   Existing [world-cleanup findings](gta3-darkel-reconstruction-2026-10-03.md)
   also require removing owned objects before object-pool serialization and
   preserving unrelated script pickups. Preflight available slots before native
   allocators can evict unrelated pickups.

## Timing, populations and visibility

7. **Measure actual routines over equal elapsed time.** The pinned
   [native timing records](https://github.com/darkcenturies/gta3-faithful/blob/ed918ec17d37149bb639d272846cd35dc191ea7e/docs/SOURCE-INTEGRATION.md)
   describe 30/60/165/240 FPS fixtures and disabled-control reproduction of the
   original differences. Held-walk acceleration and damping require one affine
   composition; changing damping alone changes steady speed. Fractional vibration
   milliseconds must survive integer countdowns. Flames, smoke and cached flicker
   need a shared reference emission clock. Helicopter/aircraft statements and
   collision/damage need routine-specific checks, not blanket physics claims.
   `valkyrie-timing` analyzes supplied traces; sparse samples can hide short events.

8. **Native regression drivers need owned, isolated fixtures.** Testing hooks,
   temporary state and captures stay outside production packages. Source-site
   checks should stop when a pinned statement/site count changes rather than
   silently applying a patch to a different revision. Compilation, formula tests,
   controlled engine runs and complete gameplay answer different questions.

9. **Walkers and drivers compete for a shared pool.** The
   [population correction](https://github.com/darkcenturies/gta3-faithful/commit/0a846fca77943e849459d7a6afb4815a2cd39093)
   records extended walkers exhausting driver reserve with spare vehicle slots.
   Increasing that target's ped capacity from 140 to 256 retains replay's uint8
   index range; it does not create unlimited capacity or increase every quota.
   Source records report greater distant counts in one controlled sample. They
   do not promise equal nearby counts or frame-time cost everywhere.

10. **Spawn, retention, density and detail are independent controls.** Native
    nearby attempts/quotas should survive while distant attempts get their own
    budget and scaled acceptance gates. Distant vehicles must not satisfy local
    traffic quotas or block emergency dispatch. A successful spawn, a screen
    projection and an atomic submission do not establish visible pixels: buildings
    can occlude them. Use native counts and captures together. See
    [distance controls](https://github.com/darkcenturies/gta3-faithful/blob/ed918ec17d37149bb639d272846cd35dc191ea7e/docs/DISTANCE-CONTROLS.md).

## Rigs, menus, graphics and platforms

11. **Vehicle poses are more than a readable IFP.** Actual bind rigs, SA animation
    Root, III quaternion conventions, seated origins and unchanged target masks
    matter. Sparse actions inherit missing base tracks. A partial waist can
    suppress the base translation: the vehicle-specific left drive-by needed an
    explicit translated waist track. Seat shifts are quantized at 1/128 m and
    should persist through action blending. The existing
    [vehicle-pose return](../docs/VALKYRIE-TOOLING.md#valkyrie-animation)
    includes loader/rig checks; wheel contact, NPC fit and entry/exit still need
    gameplay review. A common offset is not per-vehicle fitting.

12. **Contact metrics can conceal unsuitable visible shapes.** Previous character
    checks found matching palm centres despite an open detonator hand. Grip shape,
    source deformation, compactness, camera orientation and actual close-ups need
    independent checks. Existing rig findings also document MSAA corrupting an
    isolated offscreen depth pair: inspect stock geometry and render state before
    blaming conversion. Preserve these useful negative outcomes.

13. **Settings tests must exercise the correct layer.** Missing/new keys should
    receive declared defaults without replacing valid old OFF choices. Native
    streaming and auxiliary indices must latch the same optional-asset selection
    against the same absolute game root. Restore Defaults affects its own page;
    resolution/screen mode/MSAA require a valid device-recreation phase. Key labels,
    scrolling, layout scaling and settings persistence require their own checks.
    [Display/Graphics records](https://github.com/darkcenturies/gta3-faithful/blob/ed918ec17d37149bb639d272846cd35dc191ea7e/docs/DISPLAY-GRAPHICS.md)
    describe those checks. `valkyrie-settings` covers supplied INIs, not native UI.

14. **Graphics comparisons require matching actual pipelines and inputs.** Source
    now exposes MatFX/Neo/Spec/Env vehicle selections. Lighting records distinguish
    coronas, point lights, vehicle reflections, world ambient, dynamic-object
    ambient, filter and weather interpolation. A menu value or executable name
    does not prove a GPU contribution. Driver AO must be isolated independently.
    Compare loaded texture/effect values, render state and matched captures.
    [Alpha lighting](https://github.com/darkcenturies/gta3-faithful/blob/ed918ec17d37149bb639d272846cd35dc191ea7e/docs/ALPHA-LIGHTING.md)
    describes authored calibration, not recovered original alpha parameters.

15. **Silhouette shadows have budgets and fallbacks.** The recorded native renderer
    projects animated geometry onto collision surfaces, uses a bounded mask cache
    and limits refresh frequency independently of display FPS. Missing geometry,
    allocation or upload can fall back to stock projections. Ground projection
    does not imply building-wall shadow maps, and extending range cannot create
    shadows for unloaded objects. Pipeline selection, shadow mode and driver AO
    remain separate operations.

16. **Screenshot reconstruction is measured adaptation.** HUD positions and ink
    bounds can be measured against an exact-resolution reference; a different
    image resolution invalidates those gates. Retained stock artwork, a fan
    reconstruction font, authored armour treatment and user-selected punctuation
    must retain their own provenance. Pixel similarity cannot authenticate unseen
    behaviour, typography, map artwork or missing original code.

17. **Platform fixes have platform-specific proof.** The
    [Mac records](https://github.com/darkcenturies/gta3-faithful/blob/ed918ec17d37149bb639d272846cd35dc191ea7e/docs/MAC-FINDINGS.md)
    distinguish Retina pixels from Cocoa points, initial framebuffer size,
    focus/cursor release, native fullscreen and render-resource shutdown order.
    Headless MSAA can be explicitly skipped when no context is available; a
    present context with a failed sample count remains a failure. Build/architecture
    checks do not establish every platform's gameplay. Dummy textures with empty
    rasters need dimension validation before accepting them as station artwork.

## Recordings, diagnostics and publishing

18. **Record against simulation time and keep provenance.** Committed chase/Dodo
    records use a fixed 30 FPS testing clock and 48 kHz OpenAL loopback so capture
    overhead cannot change motion or recorded duration. Native contacts/events
    are measured separately from authored routes/camera cuts and triggered
    explosions. A building-contact gate before a scripted explosion is not an
    unassisted flight or historical footage. Non-silent audio, event frames and
    stream metadata are distinct gates. `valkyrie-capture` audits supplied frames
    and PCM; it cannot independently prove event or audio origin.

19. **Diagnostics need matching identities and explicit extents.** Resolve loaded
    VA to RVA against the exact image base, image bounds and target hash. An
    address beyond a supplied symbol's range stays unresolved; nearest-name
    guessing is not proof. Compiler-derived interfaces, SDK layout comparisons
    and COFF extraction are useful future work but the unfinished project-specific
    module/host generators are not exported in this update. No live dump or
    private stack is a public example.

20. **Publication and installation need separate integrity contracts.** Verify
    source revision, dependency pins, architecture, allowlisted package scope and
    each payload hash. A recognized upgrade may replace only known identities;
    unknown binaries, unrelated ASIs, settings, saves and original archives need
    preservation or explicit compatibility investigation. Rechecking output
    hashes does not substitute for runtime tests. Public tool demos use original
    fixtures; shipping source hosts and game-derived packs follows their own rules.

## Public reproduction, withholding and completed checks

### Opening props and restart lifetime checks, 2026-10-12

In a source-integrated GTA III Windows x64 D3D9 target, the opening bridge
wrecks were static props with authored grey/teal material RGB. Their original
model bytes and decoded texture colours matched the locally supplied reference.
The Neo world callback forced material RGB to white, including untextured paint.
Honouring geometry modulation restored the colours in native captures. Inspect
the object's actual model/render path before changing a vehicle colour palette
or replacing textures. A vehicle-looking prop can use the world pipeline.

The same target reproduced `0xc0000374` heap corruption during the second
New Game restart. Matching symbols placed the detected failure in vehicle
MatFX texture/raster destruction. Detection during a free does not by itself
identify the earlier lifetime error. Source-order review found that level
loading could bind vehicle materials before new reflection textures loaded,
while shutdown retained the previous texture pointers. Loading those resources
before models and clearing released pointers passed six opening sequences,
five actual shutdown/reinitialisation cycles, twelve world-renderer on/off
captures and clean process exit. The tested repair moves from version 0.2.134
to 0.2.135; OpenGL has source-level integration checks only.

Use `valkyrie-rendering` to compare captures with explicit camera, scene,
renderer, revision and simulation-time metadata; declare the renderer/revision
changes you intend to compare. Its pixel report cannot determine whether paint
is correct. Use `valkyrie-diagnostics` only with independently supplied exact
image identities and symbol ranges. It does not decode PDBs or minidumps; those
were evaluated separately with a native debugger. A small dump can omit the
texture object, so do not invent its fields or infer an owning texture from a
nearest symbol. Repeat resource teardown as well as cold startup.

This return publishes the reusable methods and observed validation counts.
Game-derived props, textures, captures, private dumps, addresses, configuration,
symbols and runtime implementation remain withheld. It establishes the sampled
opening/restart repair, not every mission, renderer, vehicle or GPU combination.

### Radio-off artwork legibility, 2026-10-12

A small radio-off pictogram used more shading and detail than neighbouring
station logos, and its crossed-out device did not communicate the state clearly.
An authored 32-pixel, two-colour `RADIO OFF` wordmark makes the state explicit.
Judge both meaning and visual detail beside the real neighbouring icons at the
rendered size; a large nearest-neighbour preview only establishes the pixel design.
Keep one authored input for the packed texture and native fallback so an active
fallback cannot silently restore older artwork. Check which source the game
actually draws before editing an external texture dictionary.

Windows x64 D3D9 checks for source target 0.2.136 passed seventeen HUD stages
at each of 1280×720 and 640×480, including nine stations, radio off, wanted
levels 0–6 and HUD restart. Actual captured off-state pixels, centering and
clearance passed; manual review compared the wordmark with all nine rendered
station logos. This establishes the sampled HUD presentation, not every
language, UI scaling mode, renderer or subjective style preference.

Use `valkyrie-rendering` for controlled capture comparisons and
`valkyrie-restoration` for the evidence catalogue. Pixel differences and texture
resolution alone cannot establish legibility or stylistic fit. Native game
captures and neighbouring game-derived logos remain private.

### Trainer input and wanted-level controls, 2026-10-12

A visible label does not establish a unique Dear ImGui widget ID. A quick
wanted slider and registered section shared an ID, producing the native conflict
warning. Give independent control groups explicit scopes and retain diagnostics.
Removing duplicate controls also makes the interaction clearer; an immediate
Clear/1–6 choice avoids a separate, easily missed Apply action.

Observe gameplay events without clearing the engine's keyboard, mouse or pad
state each overlay frame. Forward both press and release events, including raw
motion. Closing, focus loss and closing during a drag must release UI capture
and clear UI state; restoring a saved cursor clip can restore an obsolete lock.
State clearly when gameplay remains live, including typing and mouse clicks.
Intentional game pauses and scripted restrictions remain separate behaviors.

Explicit trainer stars need a different policy from natural crime progression.
Temporarily allowing selection is insufficient when subsequent native wanted
updates clamp it again. Keep any override local to the current player/chase,
restore both global story limits immediately and drop it when wanted is cleared.
Show actual state and resolve conflicts with a Never wanted toggle explicitly.
Forty-nine requested-star/story-cap combinations survived ten native updates
each, with FBI/army response checks, clearing back to natural story caps and
Never wanted conflict handling. Actual UI clicks also applied 5, 6 and Clear.

Render a trainer after the HUD's final font pass so mission text cannot cover
its controls. Inspect actual captures at supported resolutions. Native test
clicks must enter after backend polling, which can overwrite a test position,
and assertions must wait for queued game-thread actions to execute. A fixture
must select its intended probe rather than silently passing another scenario.

Use `valkyrie-rendering` for controlled capture comparisons and
`valkyrie-restoration` for the evidence catalogue. Neither tool performs native
GUI input tests. Private runtime implementation, native test instrumentation,
game-derived captures, personal configuration and logs remain withheld.

The 640×480 native test exposed a feedback-layout failure: inserting a two-line
confirmation pushed the star buttons partly outside the content clipping area.
Reserve stable feedback space and remove unnecessary blank rows, then click the
real controls again. Knowing a widget's ID and nominal bounds does not establish
that its visible area accepts a click. The corrected candidate passed at both
1280×720 and 640×480, with 289 and 276 hover-ID checks across eight pages and
scrolled controls, health/wanted search checks and 60 frames each of movement
and mouse-camera updates while open. A near-vertical camera view can make yaw
rotation appear tiny when comparing forward vectors; initialize an ordinary
player view and also verify consumed native mouse offsets before accepting a
camera test. These checks cover the sampled fixture, not every device or mission.

Run the nine demos and regression suite in the
[tool guide](../docs/VALKYRIE-DEVELOPMENT-TOOLS.md#reproduce-the-tool-checks),
then search the included evidence catalogue with `valkyrie-restoration`.
The new commands intentionally need explicit schemas, contracts, capacities,
conditions or symbol tables rather than inventing those inputs.

Public scope includes original offline tool source, helpers, synthetic fixtures,
tests, structured findings and these methods. Game binaries/models/textures/audio,
full extracted scripts, native runtime adapters, production hooks, personal
configuration, original saves, installation receipts and private logs are excluded.
Existing generated research and its checksums are unchanged. Prior visual/game
checks are attributed to committed records; new synthetic results are recorded
by this contribution's tests and CI. No installation, mod release or deployment
is performed to validate this knowledge return.

### Script-sound pool exhaustion and rejected ownership, 2026-10-12

A Windows x64 D3D9/OpenAL source-host crash was resolved against an exact
executable identity and matching PDB GUID/age. The faulting sound helper used
an allocation after the bounded script-object pool returned null. The small
dump omitted pool heap contents; it identifies the failing operation but cannot
establish which earlier sounds filled the pool.

Source inspection at [x87/gta-extended-2025 revision
f8142f1](https://github.com/x87/gta-extended-2025/tree/f8142f1a7cefcfd6bcd778ed8802e21c93b97c91)
found a separate ownership problem: rejected audio-entity creation and full
one-shot queues left objects outside normal service cleanup. In a controlled
native comparison, the pinned submission body with allocation guards retained
increased used object slots from 15 to all 256 after rejected requests. Restoring
rejection cleanup kept usage at 15 after 5,000 such requests. This proves the
tested leak mechanism, not the unrecorded sequence before the owner's crash.

The corrected candidate passed native tests at verified engine caps of 60 and
165. Each run exhausted the object pool, tested unavailable audio, rejected
invalid events and submitted 30 gameplay-frame bursts of 1,000 sounds. The
native 40-entry queue accepted its capacity, rejected overflow without leaking
objects/entities and reclaimed accepted objects through next-frame service.
The ownership lesson applies to bounded pools generally: allocation, submission
and successful enqueue are separate steps. Keep ownership until the recipient
accepts the object; explicitly reclaim failures and guard every allocator caller.
Increasing capacity alone does not repair a leak.

For reproduction with independently permitted native inputs, record the initial
pool usage, exhaust audio entities, submit more sounds than the object capacity,
then compare used slots. Separately fill the per-frame queue, verify excess
requests leave no allocated objects/entities, and allow a normal gameplay frame
to verify accepted objects are reclaimed. Preserve existing looping sounds and
use an owned fixture rather than the player's installation.

`valkyrie-diagnostics` was inspected and its synthetic demo executed with
`python valkyrie.py demo valkyrie-diagnostics --output work/audio-crash-diagnostics-demo`.
Its supplied-address/symbol-range contract does not decode minidumps or PDBs;
the native matching-symbol investigation used separate private instrumentation.
No private dump, PDB, address, runtime repair, test driver, game-derived fixture
or personal configuration is exported here. These results cover sampled sound
resource pressure, not every mission or all possible crash causes.
