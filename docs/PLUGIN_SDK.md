# GTA plugin-sdk

[DK22Pac/plugin-sdk](https://github.com/dk22pac/plugin-sdk) provides GTA classes, functions, hooking helpers and example plugins for developing ASIs. It is included unchanged as a Git submodule at `third_party/plugin-sdk`, pinned to `15f15b60bbf74c106e1b496ff92c98764abf4605`.

## Get the source

```powershell
git clone --recurse-submodules https://github.com/darkcenturies/gta-workshop.git sp-rp-public-research
cd sp-rp-public-research
# For an existing checkout:
git submodule update --init --recursive
git -C third_party/plugin-sdk rev-parse HEAD
```

GitHub links to the pinned upstream revision. ZIP downloads and clones without submodule initialization do not populate the SDK. Agents should initialize it before searching its source. This downloads files without running the upstream installer.

## Source map for agents

Paths below are inside `third_party/plugin-sdk`:

| Path | Purpose |
| --- | --- |
| `README.md`, `README_breaking_changes.md` | Overview and API changes |
| `plugin_sa/plugin_sa.h` | San Andreas entry header |
| `plugin_sa/game_sa/` | San Andreas classes and function wrappers |
| `shared/` | Common infrastructure |
| `hooking/`, `injector/`, `safetyhook/` | Hooking helpers |
| `examples/CreateCar/`, `examples/PlayerWeapon/` | Example plugins |
| `tools/` | Upstream setup and project generation |
| `LICENSE` | Upstream zlib license |

Search for relevant classes/functions rather than loading all files. Compare SDK interfaces with the [research index](reverse-engineering/generated/index.json). The SDK does not establish S&SMP or Project Eagle layouts. Confirm target executable version, calling conventions, layouts and original bytes before changing hooks. Upstream examples do not imply that SP-RP shipped those features.

## Build setup

Follow upstream's [setup guide](https://github.com/DK22Pac/plugin-sdk/wiki/Set-up-plugin-sdk) and [new plugin guide](https://github.com/DK22Pac/plugin-sdk/wiki/Creating-a-new-plugin-in-plugin-sdk). Upstream documents Visual Studio with C++, its installer/project generator and a solution configured for the desired game. SDK setup can configure game paths and is a separate developer setup step.

The root `build.ps1` builds existing public Map, Doctor, Crashfix and Repair snapshots. Their current recipes do not link plugin-sdk; the wrapper does not build SDK libraries or examples. For new SDK-based ASIs, document project generation, libraries, build commands and supported executable revisions. See [BUILDING.md](BUILDING.md) for existing builds.

The SDK retains its zlib license and credits to Dmitry K., fastman92 and LINK/2012. Preserve additional bundled dependency notices. SP-RP's BSD license does not replace these terms.

The parent repository records only the submodule commit. Update the pin deliberately, together with the expected revision in `tools/check_public.py`. Keep SP-RP integration outside the upstream source where practical; uncommitted edits inside a submodule are not published by committing the parent.

## Additional comparison reference

[Dryxio/plugin-sdk-sa](https://github.com/Dryxio/plugin-sdk-sa) is a separate SA-focused fork. Our [dated review](../research/dryxio-workflow.md) records its stated Compact/Hoodlum Win32 targets and a proposed declaration-comparison workflow. Its claims must be checked against our exact input binary before accepting a layout, signature or address correction. It is an evaluation reference; this repository continues to use the DK22Pac revision above.
