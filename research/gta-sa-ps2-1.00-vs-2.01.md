# GTA San Andreas PS2: what version 2.01 removed from version 1.00

## Target

Two retail PS2 discs, compared file by file.

| Disc | Executable | Bytes | SHA-256 |
| --- | --- | ---: | --- |
| Version 1.00, German (2004) | `SLES_529.27` | 5,682,800 | `524da2d381deedce7f22e5115c318d5356760e8bb3ce488df165965b904eddfe` |
| Version 2.01, European (2005) | `SLES_525.41` | 5,684,848 | `67458503d86d3000546cbccc5a7b2746b4c5172e7c787c24d74424ea01a8a85c` |

Full decompilations of both executables are in the archive as
[gta-sa-ps2-1.00-de](../docs/reverse-engineering/generated/gta-sa-ps2-1.00-de/) and
[gta-sa-ps2-2.01-eu](../docs/reverse-engineering/generated/gta-sa-ps2-2.01-eu/).

## Question

Which content did the 2005 re-release remove or change, and does either executable contain
anything behind the common rumours (Bigfoot, ghosts, UFOs, Leatherface)?

## Method and evidence

- Both discs were extracted and compared with [`deploy/ps2-disc-diff.py`](https://github.com/darkcenturies/valkyrie-workshop/blob/archive/gta-public-source-20261001/deploy/ps2-disc-diff.py):
  loose files by MD5, VER2 IMG archives entry by entry, large audio streams by size.
- `AMERICAN.GXT` from both discs was compared string by string with `ps2-disc-diff.py --gxt`.
- `main.scm` and `script.img` were decompiled with Sanny Builder to read the girlfriend scripts.
- Removed models were loaded in Blender 4.5 with DragonFF to identify them. Their placement comes
  from `VEGASE.IPL` and `VEGASE.IDE`.
- Both executables were decompiled with Ghidra 12.1.3 using `deploy/decompile-ssmp-pe.ps1` and
  `deploy/ghidra_scripts/ExportDecompiled.py`, the same pipeline as the rest of the archive.
- The rumour search is a case-insensitive match over each export's `strings.csv`:
  `bigfoot|big.?foot|sasq|yeti|ghost|ufo|alien|myth|monster|creature|beast|hairy|\bape\b|leatherface|chainsaw|\bbf_|\bbfoot|cryptid|legend|mystery|secret|hidden|easter`.

## Result

### Observed

**Files.** Version 2.01 adds French, Italian and Spanish text (`FRENCH.GXT`, `ITALIAN.GXT`,
`SPANISH.GXT`). No file exists only on the 1.00 disc. The executable, the overlay modules
(`*.PM`), `main.scm`, 78 of the scripts in `script.img`, `VEGASE.IDE`, `VEGASE.IPL`,
`VEGASN.IDE`, `CINFO.BIN`, `MINFO.BIN`, `IOPAUDIO.IRX`, `AMERICAN.GXT` and `GERMAN.GXT` differ.
`CUTS.IMG`, `CUTSCENE.IMG`, `CARREC.IMG` and `PLAYER.IMG` are identical.

**27 entries were removed from `GTA3.IMG`** (and its copy `GTA3_1.IMG`). Nothing was added.

| Removed | What it is |
| --- | --- |
| `copgrl1`, `copgrl2`, `crogrl1`, `gangrl1`, `gangrl2`, `gungrl1`, `gungrl2`, `mecgrl1`, `mecgrl2`, `nurgrl1`, `nurgrl2` (`.dff` + `.txd`) | Girlfriend models. `*grl1` is a nude body and `*grl2` the date outfit that `GF_SEX` loads. The ordinary clothed `*grl3` models are on both discs. The prefixes are Barbara (cop), Helena (cro), Denise (gan), Millie (gun), Michelle (mec) and Katie (nur). |
| `sex.ifp` | The minigame's 20 animations, `SEX_1_P` to `SEX_3to1_W` (`P` is the player, `W` the girlfriend). |
| `vgsespray01.dff`, `vgsespdr01.dff`, `lvse_spray1.txd`, `vgsegarage.txd` | A Pay 'n' Spray building and door in east Las Venturas. |

**The east Las Venturas Pay 'n' Spray.** In 1.00, `VEGASE.IPL` defines a garage named `timy1` of
type 5 (respray) with a box from (2389.6, 1483.26, 9.82) to (2398.11, 1497.84, 15.68).
`VEGASE.IDE` defines its models as ID 8955 `vgsEspray01` (texture `lvse_spray1`) and ID 8957
`vgsEspdr01` (texture `vgsegarage`). In 2.01 the garage entry and both models are gone, and
the surrounding IDs are renumbered. The Pay 'n' Spray sign, two gang signs and an auto parts
sign were also removed from `vgsespras.txd`.

**Other changed models.** 258 `GTA3.IMG` entries differ between the discs, mostly Las Venturas
map geometry, textures and collision in the same area. 26 `GTA_INT.IMG` entries differ,
including the police station props: one photo on the noticeboard texture in
`police_props_un.txd` was replaced with a different image.

**Scripts.** In 1.00, `main.scm` sets `$iCensoredVersion = 1` at startup. Only a debug console
command, `UNCENSORED`, sets it to 0, and the retail game has no console to type it into.
`GF_SEX` checks the flag before running the minigame. In 2.01 that check, the minigame code,
and the `SEX` and `SNM` animation requests are gone: the decompiled script drops from about
2,200 lines to about 1,050. The kissing and `BLOWJOBZ` animation requests remain in both.

**Text.** 53 `AMERICAN.GXT` entries differ. They are reworded subtitles, a radio station
frequency (CSR 103.2 became 103.9), shortened tutorial text, and a few swapped button glyphs.
None of them name removed content.

**Rumour search.** Each executable has 9 matching strings: `BF_getin_LHS`, `BF_getin_RHS`,
`BF_getout_LHS`, `BF_getout_RHS` and `BF_injection` are the BF Injection vehicle and its
animations, `chainsaw` and `CHAINSAW` are the weapon, and `MONSTER` is the Monster truck.
Nothing refers to Bigfoot, ghosts, UFOs, Leatherface or any other rumoured content.

### Inferred

- The 2.01 changes follow the Hot Coffee controversy of July 2005. Everything the minigame used
  was removed (models, animations, script paths), and the minigame was already unreachable in
  1.00 without modifying the game.
- Why the east Las Venturas Pay 'n' Spray, its signs and the noticeboard photo were removed is
  not recorded anywhere on the discs.

## Reproduction and limitations

```sh
python deploy/ps2-disc-diff.py path/to/1.00-disc path/to/2.01-disc
python deploy/ps2-disc-diff.py --gxt path/to/1.00-disc/TEXT/AMERICAN.GXT path/to/2.01-disc/TEXT/AMERICAN.GXT
python deploy/ps2-disc-diff.py --img path/to/1.00-disc/MODELS/GTA3.IMG
```

Use your own discs and check the executables against the hashes above. No game files are
included here.

Only these two discs were compared. Other PS2 releases (1.00 US, 1.01, the Greatest Hits
printings) and the PC and Xbox builds were not checked. The 258 changed map entries were not
examined one by one. The rumour search covers executable strings only; model and script names
were checked by eye in the disc comparison, not searched exhaustively.
