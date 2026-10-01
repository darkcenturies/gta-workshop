# GTA component and owner catalog

Source visibility and ownership checked on **2026-10-01**. These are source
states, not live deployment, latest release, or blanket compatibility claims.
Use [the five colored maps](../GTA-WORKSHOP.md) with this catalog. Every entry
returns public-safe findings through a workshop commit, push and PR; private
owners retain full restricted evidence. See [AGENTS.md](../../AGENTS.md).

## Source owners

| Owner | Visibility / role | Start here |
| --- | --- | --- |
| [darkcenturies/gta-workshop](https://github.com/darkcenturies/gta-workshop) | **public** — Workshop intake, approved public mods, research and returned findings | `AGENTS.md` |
| [darkcenturies/valkyrie-phone](https://github.com/darkcenturies/valkyrie-phone) | **public** — Public Phone distribution and its reviewed shared-dependency scope | `MAINTENANCE.md` |
| [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) | **private** — Shared/private native source, native server components, port and asset tools | `AGENTS.md` |
| [darkcenturies/street-racing-girls](https://github.com/darkcenturies/street-racing-girls) | **private** — SRG / GTA Midnight SA conversion; private by explicit owner policy | `AGENTS.md` |
| [darkcenturies/sp-rp](https://github.com/darkcenturies/sp-rp) | **private** — SP-RP gamemode, accounts and server operations | `README.md` |
| [darkcenturies/dlss5-neural-rendering-kit](https://github.com/darkcenturies/dlss5-neural-rendering-kit) | **private** — Rendering integration; only GTA-related work belongs in this catalog | `README.md` |
| [darkcenturies/dc-launcher](https://github.com/darkcenturies/dc-launcher) | **private** — Desktop launcher; only GTA/SP-RP integration belongs in this catalog | `README.md` |
| [darkcenturies/sp-rp-web](https://github.com/darkcenturies/sp-rp-web) | **private** — Website and UCP; public-facing service does not imply public source | `PUBLISHING.md` |
| [darkcenturies/sp-rp](https://github.com/darkcenturies/sp-rp) | **private** — Dedicated Discord integration checkout and production branch | `README.md`; branch `bot/live` |
| [novawish/re3](https://github.com/novawish/re3) | **public-third-party** — External engine input; the owned port patch is owned by private Workshop | `README.md` |

## Component index

| Component | Source state | Owner route |
| --- | --- | --- |
| [Workshop intake and findings](#component-workshop-hub) | `already-public` | `public` |
| [Doctor + Crashfix ASI](#component-doctor) | `already-public` | `public` |
| [Crashfix guard source](#component-crashfix-guards) | `already-public` | `public` |
| [Valkyrie Map](#component-map) | `already-public` | `public` |
| [Valkyrie Repair](#component-repair) | `already-public` | `public` |
| [Winmode Nullfix historical source gap](#component-nullfix) | `source-missing` | `public` |
| [Decompilation and protocol archives](#component-archives) | `already-public` | `public` |
| [Public analysis and findings workflow](#component-analysis-tools) | `already-public` | `public` |
| [Public Phone](#component-phone) | `already-public` | `phone` |
| [Phone trainer/map dependencies](#component-phone-dependencies) | `already-public` | `phone` |
| [Valkyrie Core](#component-core) | `private` | `workshop` |
| [Valkyrie Atmosphere](#component-atmosphere) | `private` | `workshop` |
| [Valkyrie Fuel](#component-fuel) | `private` | `workshop` |
| [Valkyrie Radar](#component-radar) | `private` | `workshop` |
| [Valkyrie Realworld](#component-realworld) | `private` | `workshop` |
| [SP-RP Blips](#component-blips) | `private` | `workshop` |
| [SP-RP Animations](#component-animations) | `private` | `workshop` |
| [SP-RP Overlay](#component-overlay) | `private` | `workshop` |
| [SP-RP RPC](#component-rpc) | `private` | `workshop` |
| [SP-RP Diagnostics](#component-diagnostics) | `private` | `workshop` |
| [SP-RP Stats](#component-stats) | `private` | `workshop` |
| [Standalone Valkyrie Trainer](#component-trainer) | `private` | `workshop` |
| [Valkyrie Flight Controls](#component-flight) | `private` | `workshop` |
| [Valkyrie game-sa compatibility layer](#component-game-sa) | `private` | `workshop` |
| [SP-RP gamemode](#component-server-gamemode) | `private` | `server` |
| [sprp-ai](#component-server-ai) | `private` | `workshop` |
| [sprp-async](#component-server-async) | `private` | `workshop` |
| [sprp-ssmp](#component-server-ssmp) | `private` | `workshop` |
| [SRG / GTA Midnight](#component-srg) | `private` | `srg` |
| [Upstate/re3 compatibility port](#component-upstate) | `private` | `workshop` |
| [External re3 engine](#component-re3-upstream) | `external-public` | `re3` |
| [Asset and animation authoring](#component-assets) | `private` | `workshop` |
| [GTA rendering / DLSS integration](#component-rendering) | `private` | `rendering` |
| [GTA / SP-RP Launcher integration](#component-launcher) | `private` | `launcher` |
| [SP-RP website / UCP](#component-website) | `private` | `web` |
| [SP-RP Discord integration](#component-bot) | `private` | `bot` |

## Already public source and historical source gaps

<a id="component-workshop-hub"></a>

### Workshop intake and findings

**ID:** `workshop-hub` · **Source state:** `already-public` · **Target:** All cataloged GTA targets

**Source owner:** [darkcenturies/gta-workshop](https://github.com/darkcenturies/gta-workshop) · **Entry:** `docs/GTA-WORKSHOP.md`

Agent routing, project catalog and durable returned knowledge.

**Validation route:** Public boundary, links, ownership/visibility, target and status accuracy.

**Reference fit:** No dedicated Dryxio method asserted for this component. Consult the catalog for the actual task and record applicability.

**Required public return:** Reproducible outcome, actual checks, limitations and safe implementation reference.

<a id="component-doctor"></a>

### Doctor + Crashfix ASI

**ID:** `doctor` · **Source state:** `already-public` · **Target:** Classic SA / x86

**Source owner:** [darkcenturies/gta-workshop](https://github.com/darkcenturies/gta-workshop) · **Entry:** `client/valkyrie-asi-suite/doctor-valkyrie`

One artwork-free ASI: crash reports plus signature-checked crash guards.

**Validation route:** Public Windows build, combined-ASI/artwork check, Crashfix tests; gameplay separate.

**Dryxio references:** [ghidra-bridge](https://github.com/Dryxio/ghidra-bridge), [reagent](https://github.com/Dryxio/reagent), [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed).

**Required public return:** Reproducible outcome, actual checks, limitations and safe implementation reference.

<a id="component-crashfix-guards"></a>

### Crashfix guard source

**ID:** `crashfix-guards` · **Source state:** `already-public` · **Target:** Classic SA / x86

**Source owner:** [darkcenturies/gta-workshop](https://github.com/darkcenturies/gta-workshop) · **Entry:** `client/valkyrie-asi-suite/valkyrie-crashfix`

GPL guard source built into Doctor; not a second installed Crashfix ASI.

**Validation route:** Native guard tests and exact-target signature evidence; preserve GPL notices.

**Dryxio references:** [ghidra-bridge](https://github.com/Dryxio/ghidra-bridge), [reagent](https://github.com/Dryxio/reagent), [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed).

**Required public return:** Reproducible outcome, actual checks, limitations and safe implementation reference.

<a id="component-map"></a>

### Valkyrie Map

**ID:** `map` · **Source state:** `already-public` · **Target:** Classic SA / x86

**Source owner:** [darkcenturies/gta-workshop](https://github.com/darkcenturies/gta-workshop) · **Entry:** `client/valkyrie-asi-suite`

Pause-map zoom/pan; public source is earlier 0.2.0 baseline.

**Validation route:** Public Map build; source-version and real-game limits explicit.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [ariane](https://github.com/Dryxio/ariane).

**Withheld / unresolved:** Later exact Map source is unresolved; private Radar additions must stay excluded.

**Required public return:** Reproducible outcome, actual checks, limitations and safe implementation reference.

<a id="component-repair"></a>

### Valkyrie Repair

**ID:** `repair` · **Source state:** `already-public` · **Target:** Windows / C# / SA tooling

**Source owner:** [darkcenturies/gta-workshop](https://github.com/darkcenturies/gta-workshop) · **Entry:** `client/valkyrie-asi-suite/valkyrie-repair`

Repair utility builds and embeds combined Doctor/Crashfix ASI.

**Validation route:** Build and isolated Repair self-tests; GUI/game checks separate.

**Reference fit:** No dedicated Dryxio method asserted for this component. Consult the catalog for the actual task and record applicability.

**Required public return:** Reproducible outcome, actual checks, limitations and safe implementation reference.

<a id="component-nullfix"></a>

### Winmode Nullfix historical source gap

**ID:** `nullfix` · **Source state:** `source-missing` · **Target:** Historical SA binary

**Source owner:** [darkcenturies/gta-workshop](https://github.com/darkcenturies/gta-workshop) · **Entry:** `docs/MODS.md`

Historical binary record; standalone source not located and current Repair retires old payload.

**Validation route:** Provenance and source search before claiming reproducible build.

**Reference fit:** No dedicated Dryxio method asserted for this component. Consult the catalog for the actual task and record applicability.

**Withheld / unresolved:** Binary availability is not source availability.

**Required public return:** Record source/provenance search and any verified recovery; do not relabel old binary as current source.

<a id="component-archives"></a>

### Decompilation and protocol archives

**ID:** `archives` · **Source state:** `already-public` · **Target:** Exact recorded GTA SA / client / server binaries

**Source owner:** [darkcenturies/gta-workshop](https://github.com/darkcenturies/gta-workshop) · **Entry:** `docs/reverse-engineering`

Generated decompilation, disassembly, symbols and historical target evidence.

**Validation route:** Six target / 45-file SHA-256 archive checks; exact product/version/address convention.

**Dryxio references:** [ghidra-bridge](https://github.com/Dryxio/ghidra-bridge), [reagent](https://github.com/Dryxio/reagent), [samp-source](https://github.com/Dryxio/samp-source), [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild).

**Required public return:** Reproducible outcome, actual checks, limitations and safe implementation reference.

<a id="component-analysis-tools"></a>

### Public analysis and findings workflow

**ID:** `analysis-tools` · **Source state:** `already-public` · **Target:** Exact recorded targets / synthetic fixtures

**Source owner:** [darkcenturies/gta-workshop](https://github.com/darkcenturies/gta-workshop) · **Entry:** `deploy`

Bounded extraction/analysis and reusable evidence methods.

**Validation route:** Public boundary, Python syntax, task-specific reproductions; executable inputs remain local.

**Dryxio references:** [ghidra-bridge](https://github.com/Dryxio/ghidra-bridge), [reagent](https://github.com/Dryxio/reagent).

**Required public return:** Reproducible outcome, actual checks, limitations and safe implementation reference.

<a id="component-phone"></a>

### Public Phone

**ID:** `phone` · **Source state:** `already-public` · **Target:** SA / x86

**Source owner:** [darkcenturies/valkyrie-phone](https://github.com/darkcenturies/valkyrie-phone) · **Entry:** `valkyrie-asi-suite`

Phone/camera/contacts/services and reviewed embedded dependencies.

**Validation route:** Phone-owner build/tests and reviewed dependency synchronization; runtime separate.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed).

**Required public return:** Reproducible outcome, actual checks, limitations and safe implementation reference.

<a id="component-phone-dependencies"></a>

### Phone trainer/map dependencies

**ID:** `phone-dependencies` · **Source state:** `already-public` · **Target:** SA / x86

**Source owner:** [darkcenturies/valkyrie-phone](https://github.com/darkcenturies/valkyrie-phone) · **Entry:** `MAINTENANCE.md`

Already-public subset has its own reviewed scope; does not publish private Radar/Core wholesale.

**Validation route:** Review source diff, notices and sync workflow in Phone and Workshop.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [GTA-GPS-Redux](https://github.com/Dryxio/GTA-GPS-Redux).

**Required public return:** Reproducible outcome, actual checks, limitations and safe implementation reference.


## Private native mods and shared source

<a id="component-core"></a>

### Valkyrie Core

**ID:** `core` · **Source state:** `private` · **Target:** SA / x86

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite/valkyrie-core`

Shared support consumed by private suite and SRG; maintain one authoring owner.

**Validation route:** Affected consumer builds and exact-target layout/signature checks.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed), [ghidra-bridge](https://github.com/Dryxio/ghidra-bridge).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-atmosphere"></a>

### Valkyrie Atmosphere

**ID:** `atmosphere` · **Source state:** `private` · **Target:** SA / x86

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite/valkyrie-inventory`

Pause menu, inventory, portrait and optional visual effects; directory name is historical.

**Validation route:** Private suite build and Atmosphere checks; art rights and game behavior separate.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-fuel"></a>

### Valkyrie Fuel

**ID:** `fuel` · **Source state:** `private` · **Target:** SA single-player / x86

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite`

Tanks, pumps and consumption; private implementation.

**Validation route:** Private suite build and Fuel regression rules; in-game pumps/consumption separate.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed).

**Withheld / unresolved:** Private Fuel source/tooling is explicitly excluded from public research imports.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-radar"></a>

### Valkyrie Radar

**ID:** `radar` · **Source state:** `private` · **Target:** SA / experimental x86

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite`

Live 3D radar, navigation and private routing/tile additions; off by default.

**Validation route:** Private build, route/renderer/package checks; runtime and tile provenance separate.

**Dryxio references:** [GTA-GPS-Redux](https://github.com/Dryxio/GTA-GPS-Redux), [Radar-in-style-GTA-SA-The-Definitive-Edition](https://github.com/Dryxio/Radar-in-style-GTA-SA-The-Definitive-Edition), [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa).

**Withheld / unresolved:** Unreleased private Radar implementation and project-specific research are explicitly withheld.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-realworld"></a>

### Valkyrie Realworld

**ID:** `realworld` · **Source state:** `private` · **Target:** SA / x86

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite`

Real-world clock and weather integration.

**Validation route:** Selected native target and its behavior checks; host/network inputs stated.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-blips"></a>

### SP-RP Blips

**ID:** `blips` · **Source state:** `private` · **Target:** SA / x86; verify multiplayer profile

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite`

Server markers.

**Validation route:** Selected ASI build and exact protocol/target evidence; sanitize multiplayer logs.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed), [samp-source](https://github.com/Dryxio/samp-source), [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-animations"></a>

### SP-RP Animations

**ID:** `animations` · **Source state:** `private` · **Target:** SA / x86; verify multiplayer profile

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite`

Movement animation integration.

**Validation route:** Selected ASI build and exact protocol/target evidence; sanitize multiplayer logs.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed), [samp-source](https://github.com/Dryxio/samp-source), [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-overlay"></a>

### SP-RP Overlay

**ID:** `overlay` · **Source state:** `private` · **Target:** SA / x86; verify multiplayer profile

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite`

Server hover details and route overlays.

**Validation route:** Selected ASI build and exact protocol/target evidence; sanitize multiplayer logs.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed), [samp-source](https://github.com/Dryxio/samp-source), [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-rpc"></a>

### SP-RP RPC

**ID:** `rpc` · **Source state:** `private` · **Target:** SA / x86; verify multiplayer profile

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite`

Multiplayer integration.

**Validation route:** Selected ASI build and exact protocol/target evidence; sanitize multiplayer logs.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed), [samp-source](https://github.com/Dryxio/samp-source), [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-diagnostics"></a>

### SP-RP Diagnostics

**ID:** `diagnostics` · **Source state:** `private` · **Target:** SA / x86; verify multiplayer profile

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite`

Passive exception/opcode evidence.

**Validation route:** Selected ASI build and exact protocol/target evidence; sanitize multiplayer logs.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed), [samp-source](https://github.com/Dryxio/samp-source), [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-stats"></a>

### SP-RP Stats

**ID:** `stats` · **Source state:** `private` · **Target:** SA / x86; verify multiplayer profile

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-asi-suite`

Vital-stat panel.

**Validation route:** Selected ASI build and exact protocol/target evidence; sanitize multiplayer logs.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed), [samp-source](https://github.com/Dryxio/samp-source), [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-trainer"></a>

### Standalone Valkyrie Trainer

**ID:** `trainer` · **Source state:** `private` · **Target:** SA / x86

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-trainer`

Travel and testing helper; separate from reviewed Phone embedded subset.

**Validation route:** Waypoint/parser/build checks in owner; historical target evidence needs current GTA recheck.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-flight"></a>

### Valkyrie Flight Controls

**ID:** `flight` · **Source state:** `private` · **Target:** SA / x86

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-flight-controls`

Configurable aircraft steering inputs.

**Validation route:** Build and pitch-input tests; planes/helicopters/Hydra gameplay remains a separate gate.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-game-sa"></a>

### Valkyrie game-sa compatibility layer

**ID:** `game-sa` · **Source state:** `private` · **Target:** SA / x86

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/valkyrie-game-sa`

Static compatibility interfaces; legacy documentation is historical target evidence.

**Validation route:** Consumer builds and target/layout review before assuming current SA support.

**Dryxio references:** [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.


## Private server gameplay and native components

<a id="component-server-gamemode"></a>

### SP-RP gamemode

**ID:** `server-gamemode` · **Source state:** `private` · **Target:** SA multiplayer / owning server host

**Source owner:** [darkcenturies/sp-rp](https://github.com/darkcenturies/sp-rp) · **Entry:** `README.md`

Gameplay, persistence integration, accounts and server operations.

**Validation route:** Owner builds/tests and exact host/protocol contracts; deployment is a separate authorized action.

**Dryxio references:** [samp-source](https://github.com/Dryxio/samp-source), [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild), [mtasa-neon](https://github.com/Dryxio/mtasa-neon).

**Withheld / unresolved:** Private gameplay/operations by owner policy; account and production data never public inputs.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-server-ai"></a>

### sprp-ai

**ID:** `server-ai` · **Source state:** `private` · **Target:** Owning server host

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `component/sprp-ai`

Native server AI component; inspect owner contract for the specific task.

**Validation route:** Owner component build and behavior checks; MTA references are a separate platform.

**Dryxio references:** [mtasa-neon](https://github.com/Dryxio/mtasa-neon), [mtasa-blue](https://github.com/Dryxio/mtasa-blue).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-server-async"></a>

### sprp-async

**ID:** `server-async` · **Source state:** `private` · **Target:** Legacy 32-bit / experimental x64 server host

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `component/sprp-async`

Dedicated SQLite worker; Pawn callbacks/results remain on main tick.

**Validation route:** Ordering/drain/callback tests and exact host/32-bit Pawn-cell contract.

**Reference fit:** No dedicated Dryxio method asserted for this component. Consult the catalog for the actual task and record applicability.

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-server-ssmp"></a>

### sprp-ssmp

**ID:** `server-ssmp` · **Source state:** `private` · **Target:** Exact S&SMP/open.mp compatibility target

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `component/sprp-ssmp`

Protocol/native compatibility component; preserve exact-target historical evidence.

**Validation route:** Exact host/client/protocol tests; R5 references do not establish S&SMP support.

**Dryxio references:** [samp-source](https://github.com/Dryxio/samp-source), [samp-r5-rebuild](https://github.com/Dryxio/samp-r5-rebuild), [ghidra-bridge](https://github.com/Dryxio/ghidra-bridge).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.


## Conversions, worlds and asset workflows

<a id="component-srg"></a>

### SRG / GTA Midnight

**ID:** `srg` · **Source state:** `private` · **Target:** San Andreas conversion

**Source owner:** [darkcenturies/street-racing-girls](https://github.com/darkcenturies/street-racing-girls) · **Entry:** `README.md`

World/Bayview authoring, vehicle imports, runtime, weather/branding and tyre-smoke work.

**Validation route:** Owner runtime build, Core consumer check, format/import checks and matching-game validation.

**Dryxio references:** [ariane](https://github.com/Dryxio/ariane), [gta-scout](https://github.com/Dryxio/gta-scout), [gta-flow](https://github.com/Dryxio/gta-flow), [plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa), [gta-reversed](https://github.com/Dryxio/gta-reversed), [fastman92_limit_adjuster](https://github.com/Dryxio/fastman92_limit_adjuster).

**Withheld / unresolved:** Explicit private-source owner policy; generated game assets and local builds stay out of Git.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-upstate"></a>

### Upstate/re3 compatibility port

**ID:** `upstate` · **Source state:** `private` · **Target:** GTA III / re3 x64 / CLEO Redux

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `client/upstate-re3`

Owned engine patch, pause-map generation and travel script; separate from external re3.

**Validation route:** Pinned engine base and x64 build; map pixel roundtrip; campaign/save limits explicit.

**Dryxio references:** [ariane](https://github.com/Dryxio/ariane), [gta-scout](https://github.com/Dryxio/gta-scout).

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-re3-upstream"></a>

### External re3 engine

**ID:** `re3-upstream` · **Source state:** `external-public` · **Target:** GTA III / external engine

**Source owner:** [novawish/re3](https://github.com/novawish/re3) · **Entry:** `README.md`

Public third-party engine input, not the Workshop-owned Upstate patch.

**Validation route:** Apply owned patch only to its recorded engine revision.

**Reference fit:** No dedicated Dryxio method asserted for this component. Consult the catalog for the actual task and record applicability.

**Required public return:** Return exact upstream/patch revisions and reproduced results with original credits.

<a id="component-assets"></a>

### Asset and animation authoring

**ID:** `assets` · **Source state:** `private` · **Target:** SA / III; source formats vary

**Source owner:** [darkcenturies/valkyrie-workshop](https://github.com/darkcenturies/valkyrie-workshop) · **Entry:** `tools/model-conversion`

Models, peds, vehicles, textures, maps and animation conversions; project-specific work also lives in SRG.

**Validation route:** Format/roundtrip checks, editable authoring handoff and original/synthetic provenance.

**Dryxio references:** [gta-scout](https://github.com/Dryxio/gta-scout), [ariane](https://github.com/Dryxio/ariane), [gta-flow](https://github.com/Dryxio/gta-flow).

**Withheld / unresolved:** Authoring source private; game-derived payloads remain locally supplied, not implicit exports.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.


## Rendering, Launcher and supporting services

<a id="component-rendering"></a>

### GTA rendering / DLSS integration

**ID:** `rendering` · **Source state:** `private` · **Target:** Per-game / host / driver profile

**Source owner:** [darkcenturies/dlss5-neural-rendering-kit](https://github.com/darkcenturies/dlss5-neural-rendering-kit) · **Entry:** `README.md`

GTA graphics integration and reproducibility research.

**Validation route:** Exact host/driver/profile and compatibility evidence; historical local profiles are not universal support.

**Dryxio references:** [skygfx](https://github.com/Dryxio/skygfx).

**Withheld / unresolved:** Integration source private; redistribution terms and reproducible configuration require export review.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-launcher"></a>

### GTA / SP-RP Launcher integration

**ID:** `launcher` · **Source state:** `private` · **Target:** Windows / owner-side server workflow

**Source owner:** [darkcenturies/dc-launcher](https://github.com/darkcenturies/dc-launcher) · **Entry:** `README.md`

Desktop orchestration and packaging; WoW portion excluded.

**Validation route:** Owner build/package checks; release record and anonymous download availability distinguished.

**Reference fit:** No dedicated Dryxio method asserted for this component. Consult the catalog for the actual task and record applicability.

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-website"></a>

### SP-RP website / UCP

**ID:** `website` · **Source state:** `private` · **Target:** Web supporting GTA server

**Source owner:** [darkcenturies/sp-rp-web](https://github.com/darkcenturies/sp-rp-web) · **Entry:** `README.md`

Public-facing website with private implementation and account workflows.

**Validation route:** Owner web checks and clean-main publishing rules; live publication separate.

**Reference fit:** No dedicated Dryxio method asserted for this component. Consult the catalog for the actual task and record applicability.

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

<a id="component-bot"></a>

### SP-RP Discord integration

**ID:** `bot` · **Source state:** `private` · **Target:** GTA supporting service / bot/live

**Source owner:** [darkcenturies/sp-rp](https://github.com/darkcenturies/sp-rp) · **Entry:** `README.md`

Bot source uses its declared separate production branch.

**Validation route:** Bot-owner checks and production-branch rules; messaging requires authorization.

**Reference fit:** No dedicated Dryxio method asserted for this component. Consult the catalog for the actual task and record applicability.

**Withheld / unresolved:** Private owner scope; no source export approved by this catalog.

**Required public return:** Sanitized outcome and validation, withheld scope/reason and remaining review; full evidence committed in private owner.

## Reading source state correctly

- `already-public`: source is in the named public owner; source availability does not establish release or runtime quality.
- `private`: source remains in its private owner; public-safe findings still return here.
- `source-missing`: a historical binary reference exists without located corresponding standalone source.
- `external-public`: third-party source; the owned patch, locally supplied assets and compatibility claims remain distinct.
- Proposed source releases are listed separately in [the publication backlog](PUBLICATION-BACKLOG.md); they are not current source states.

The structured companion is [catalog.json](catalog.json). Keep owner, component, diagram and return-policy updates consistent. Never store credentials, game payloads, private logs or infrastructure details in either format.
