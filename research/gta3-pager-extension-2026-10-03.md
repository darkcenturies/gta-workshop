# Extending GTA III's pager without replacing its identity

## Question and exact target

Can a pager provide app-like functions while retaining GTA III's original HUD
and period? Investigated 2026-10-03 against owner-supplied GTA III assets and
Windows x64 D3D9/OpenAL re3 source at
[`9a7fa478578beaba947ea867c15a25e411d641d8`](https://github.com/novawish/re3/tree/9a7fa478578beaba947ea867c15a25e411d641d8),
with a separately maintained world-conversion compatibility patch.
librw revision: `8b2caf8f86b4f793d07fbc6b7d0bd4aafd22162f`.
Retail GTA III executables, mobile/Anniversary and Definitive Edition were
not validated by this investigation.

## Device identity and evidence limits

The locally supplied classic-style `pager` texture visibly labels the device
**SUMO WORDMAN**. It has a purple/blue case, amber display and two visible
front buttons. [Grand Theft Wiki](https://www.grandtheftwiki.com/Sumo_Wordman)
corroborates the fictional product name. The
[GTA Wiki description](https://gta.fandom.com/wiki/Sumo_Wordman) suggests
Motorola Memo Classic or Instinct 200 inspiration; this is a resemblance
claim, not established Rockstar design attribution. No evidence here identifies
one exact real Motorola model. A Motorola Advisor is a functional reference,
not a confirmed identification of GTA III's prop.

[GTA III's setting is 2001](https://www.gtabase.com/gta-3/). A reference describing
1994 pager features should not change the game's date.
[Motorola's Advisor II guide](https://www.motorolasolutions.com/content/dam/msi/docs/business/_documents/user_guides/static_files/advisor_ii_en.pdf)
documents message storage/locking, a function menu, time and alarm, and
maildrop/information-service messages. Those concepts support a plausible
pager interface, but that model's display, controls and nineteen-message
capacity are not specifications of the fictional Sumo Wordman.

## Source observations and method

Bounded inspection of the pinned
[Pager implementation](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/text/Pager.cpp),
[queue declaration](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/text/Pager.h)
and [HUD renderer](https://github.com/novawish/re3/blob/9a7fa478578beaba947ea867c15a25e411d641d8/src/render/Hud.cpp)
found eight native queue entries and eight visible scrolling text cells.
Messages interpolate numeric arguments, use priority ordering, and also enter
the PreviousBrief history. The HUD already provides the sprite, pager font,
slide animation and pager sound.

These are source observations for this pin, not recovered ABI proof for a
retail executable or another re3 build. The implementation route selected was
source integration, with separate engine-independent state and a game adapter.
No SA x86 addresses, handset poses or smartphone UI were assumed portable.

The exact locally inspected `hud.txd` is 171816 bytes, SHA-256
`ae8b151367929a3ae809bb54dead099a29c181fc3aa8aac1a2d5f0a33d4520d4`.
It contains 38 native textures. `pager` is 128x128, platform 8, PAL8, one mip,
with `pagerm` named as its mask and no DXT compression. This does not claim
that every stock edition has the same dictionary hash.

Started with the [catalog](../docs/workshop/CATALOG.md),
[Dryxio routes](dryxio-catalog.md), native/research workflow and
[texture methods](../docs/VALKYRIE-TOOLING.md#valkyrie-textures).

| Tool/reference | Actual evaluation |
| --- | --- |
| `valkyrie-textures`, `workshop/deploy/txd-merge.py` | Executed read-only texture inventory; 38 declared/found |
| `workshop/deploy/txd2png.py` | Source-reviewed; unsuitable unchanged for this platform-8 PAL8 texture because it assumes a DXT-style DDS payload and fixed paths |
| Existing palette inspection | Bounded local decode with the texture parser and Pillow; pixels withheld as game-derived evidence |
| Dryxio CLEO AI | Applicability reviewed, not executed: this task is native re3 C++, not SA CLEO |
| Ghidra/ReAgent, SA-specific SDK fork | Not executed: matching re3 source was available; unrelated SA evidence cannot establish this target |

Inventory source SHA-256:
`bd014492f5e061c77a494ca92157c0c6fb5e52595a1317535e73f3907f78092e`.
Runtime: Python 3.11.8; local visual inspection used Pillow 12.1.1.
Use independently permitted game inputs and the documented launcher:

```powershell
python valkyrie.py show workshop/deploy/txd-merge.py
python valkyrie.py run workshop/deploy/txd-merge.py -- --list PATH_TO_HUD.txd
```

The inventory command reads only; do not invoke the merge mode to investigate
a pager. The public generated archive index has no GTA III target, so no
unrelated large binary archive was loaded as a substitute.

## Tested design and reusable findings

A private test implementation uses the original eight-cell display for
messages, saved/locked pages, original fictional news, current game weather,
clock, daily alarm and alert settings. Twenty archive slots are an authored
extension choice, separate from the engine's eight queued notifications.
Information channels represent app-like functions without implying web
browsing, free-text replies or smartphone hardware.

Important invariants for other implementations:

- Native story pages preempt the interactive menu and retain their alerts.
- Deep-copy message text after numeric substitution; a display buffer or GXT
  pointer is not an archive. Remove formatting tokens before cell scrolling.
- Preserve locked history under overflow; explicitly report full memory when
  all slots are locked. Archive limits must not block the native queue.
- Release only the input-control state owned by the extension. Exercise pause,
  cutscenes, death/arrest, vehicles, replay, hidden HUD and new/load-game resets.
- Per-save sidecars can preserve messages/settings without modifying GTA's
  save format. Bind a sidecar to the actual save contents, reject malformed
  or stale data, and do not turn an optional sidecar failure into a failed save.
- Treat game-clock midnight wrap separately from backward or large scripted
  time changes. An alarm should wait for native pager traffic instead of
  replacing it.

An additional build finding: the older bundled CMake revision helper's
detached-HEAD branch copied the primary repository HEAD when used in a
worktree. Using the previously resolved/copied worktree HEAD fixes its version
identity. Check the generated revision against `git rev-parse HEAD`; compiler
success alone does not validate provenance.

## Actual validation and withheld material

Full Windows x64 D3D9/OpenAL RelWithDebInfo compilation passed with MSVC
19.51.36257.0, Windows SDK 10.0.26100.0 and CMake 4.3.1-msvc1. Existing upstream
pointer-width warnings remain. State/storage tests and actual-adapter fixture
tests passed as optimized `/W4 /WX` builds. They exercised overflow/read locks,
scrolling, clock edge cases, storage roundtrips and corruption/stale-save
rejection, native-message priority, owned controls and deferred alarms.
Fresh patch application and repeat read-only preflight passed; Python syntax
passed. No actual CLEO script validator or gameplay test was reported as run.

The initial validation did not include game installation, an in-game visual test, campaign/save roundtrip in the
game, language/font test or mod coexistence pass occurred. Compatibility is
still a test-build claim limited to compilation and isolated behavior.
Implementation source/glue, engine binaries/PDBs, game assets and local
game-derived inspection images stay outside this public library. This finding
returns methods, target identities, useful negative results and validation
limits without exporting those materials or private project navigation.

## Device behavior and LCD games follow-up

A follow-up on 2026-10-03 compared documented pager controls with the initial
test implementation. Motorola's
[Memo Express guide](https://americanmessaging.net/wp-content/uploads/2019/10/Memo_Express_User_Guide.pdf)
documents standby indicators, backlight, 12/24-hour clock/date settings,
automatic power and low-battery/optional reception indicators. These are
functional references, not proof of a specific fictional device's hardware.

The private implementation subsequently added a timed LCD lighting layer,
rotating eight-cell standby views, an independent pager-clock offset and
optional user-set civil date, manual/scheduled power, and simulated hardware
status. The date begins unset; an editable 2001 setting default does not
assert a canonical campaign day. Game-clock edits rebase timer observation.
Normal midnight crossing advances a valid user-set date, with leap-year rules.
Schedule evaluation preserves the last transition when a forward step crosses
both on/off times. Original mission messages bypass virtual power and coverage.

Battery drain and optional altitude-based coverage are authored simulation,
not measured hardware/network behavior. Reception-error diagnostics display
a status without corrupting or discarding game messages. Distinguish
simulated indicators from actual communication failures when documenting a mod.
New device fields use a bounded versioned sidecar; the previous version migrates
with safe defaults. Running games, light timers and open screens are transient.

Original optional Snake/Pong games were added on a 24x8 block grid using native
HUD rectangles inside the retained display. This is a gameplay extension;
neither consulted Motorola guide establishes games on the fictional Wordman.
Snake tests cover turns/reversal, food, growth, wall/body collisions and timer
wrap. Pong tests cover bounded rendering, held-key movement, scoring and
first-to-five completion. Native story pages close games and release owned
controls. A successfully compiled renderer does not establish LCD legibility
or comfortable input timing in the actual game.

The same pinned re3/librw revisions and Windows toolchain above passed full
x64 compilation. Optimized /W4 /WX device/game/storage tests and actual-adapter
fixtures passed. Additional checks exercised light timeout, battery exhaustion,
calendar boundaries, scheduled power, isolated clock editing, version-one
sidecar migration, every truncated prefix and malformed device fields,
powered-off mission capture and game interruption. Fresh patch application and
repeat preflight passed. Catalog applicability was reused; CLEO AI, binary
analysis and asset conversion were not executed for these native source changes.

The initial compiled pair was later installed locally with verified backups;
that operation did not establish gameplay validation. The follow-up build has
no in-game visual, campaign/save roundtrip, language/resolution or mod coexistence
pass. Implementation, engine binaries/symbols, game textures and local deployment
records remain withheld under their existing private/local boundaries.

## Unified LCD texture and functional status strip

A further 2026-10-03 correction retained the shell while composing the entire
LCD surface, letters, tiny status indicators and games at the source texture
resolution. The earlier separate rectangle game renderer and translucent
lighting layer did not guarantee visual parity with the pager's letters.

Read-only texture inventory of an independently supplied fonts.txd found
three textures. Its SHA-256 is
`d037658489b87d270c80de89d607ceaeddc0c6da28d727706b39f3aef9a6a59d`.
The pager font is platform-8 PAL8, 256x256, one mip and no DXT, with pager_mask.
Bounded local decoding found only transparent-black and opaque-black texels,
including 3945 ink pixels. The existing reviewed texture parser and Pillow
were used; the original texels and inspection images remain withheld.

The pinned Font.cpp draws a 16x16 glyph-cell atlas and modulates its texels
with the HUD pager color (32,162,66,205). Black texture RGB remains black under
this multiplication. Thus the tint's green RGB is not evidence that visible
letters are green. Compare texture pixels, color multiplication and alpha
blending together when matching HUD style.

An initial flat amber compositor preview was rejected: it erased the source
LCD grain/glare, while nearest enlargement exaggerated the glyph treatment.
The corrected renderer reads the loaded surface and preserves its textured
amber pixels. It composes at the original 128x128 texture resolution and keeps
the original 160x80 HUD proportions. A bounded clean plate exists only beneath
the dark stock indicator pixels, allowing their shaded masks to become active.
Signal changes columns of the leftmost mark; the adjacent narrow battery
mark fills/drains its middle column while preserving its stock rim/cap. Low charge and receiver errors use blinking as
alerts. These are authored adaptations, not measured hardware behavior or a
definitive interpretation of symbols in the original texture. Added unread,
alarm, silent and locked-page symbols remain small; counts/percentages use menus.

Font placement retains the native fractional HUD scale and samples the original
alpha mask linearly. Pinned sprite/font source shows linear font filtering;
texture filter metadata alone does not set the global sprite render state.
The adapter explicitly sets/restores linear filtering during drawing. Baking
text at texture resolution can differ from direct font draws at other output
resolutions; runtime comparison remains required. Dimming scales the preserved
surface instead of substituting a flat palette color. Story priority remains.

Unchanged frames skip upload; HUD shutdown releases generated textures/caches.
Unsupported shell/font dimensions and allocation failure use native text.
Source checks and compilation do not establish GPU reset or language behavior.

Optimized /W4 /WX CPU and actual-adapter tests passed. Synthetic checks exercise
clipping, preserved surface detail, native ink opacity, original signal pixels
and segment removal, battery drain with retained contours, continuous continuous continuous game strokes,
dimming and low-charge blink. Seven frames were exported using independently
supplied shell/font pixels, including full/half/empty battery states. Local
visual inspection used original HUD proportions and linear enlargement; a
pixel check confirmed the shell outside the LCD unchanged. These previews are
not in-game screenshots. Full x64 D3D9/OpenAL compilation, fresh application
and repeat preflight passed with the previously recorded pins/toolchain.
Runtime appearance, GPU reset, language/resolution behavior, save roundtrip
and mod coexistence remain unverified. Game pixels, implementation/glue,
binaries/symbols and owner-local previews remain withheld under existing boundaries.

An owner correction before the local installation separated the two adjacent
left-hand marks. The initial interpretation incorrectly grouped them as one
signal mark and assigned battery to the far-right artwork. Signal/battery now
use the requested adjacent positions; the unidentified far-right mark remains
unchanged. Reinspection of the linked Memo Express manual's printed pages 2-3
and 6 shows its continuation triangle and separate battery/reception symbols,
but does not establish an exact meaning for the fictional HUD's far-right mark.
Bundled Poppler rendered the relevant pages with font-substitution warnings;
visual comparison is insufficient to assert an exact model or icon match.
Synthetic tests now explicitly preserve the unrelated far-right texel while
exercising signal columns, adjacent battery fill/rim and low-charge blink.
