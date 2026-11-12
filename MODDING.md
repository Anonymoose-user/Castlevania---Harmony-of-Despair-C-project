# Modding Castlevania: Harmony of Despair (PC)

Everything a mod changes lives in its own folder under `mods\`. CVHDEdit (`CVHDEdit.exe`) edits all of
it, but every file is either JSON or a documented game format, so any text editor, image tool or
script can make mods too.

## Turning mods on

`mods\load_order.txt` lists the enabled mods, one folder name per line, highest priority first. A
file in a higher mod replaces the same file in a lower mod and in the game. Settings files (the JSON
files below) are combined across all enabled mods instead: every mod's rows count, and for the same
key the higher mod wins. Most settings reload in game with **F5**.

## Where the game's own files are

The game's data is one file, `data.zip`, next to `cvhd.exe` (made by `CVHDDataBuilder.exe` from your
own copy of the game). The game looks for every file in this order, first wins:

1. the enabled mods (`mods\load_order.txt`),
2. `data\` next to `cvhd.exe`, if you make one: loose files laid out like `data.zip` (quick patches),
3. `data.zip`.

Never edit `data.zip`; to change a file, put the same path in a mod. To look at an original file, open
`data.zip` with any zip tool (or CVHDEdit, which reads it directly and always saves into a mod).

## Folder layout

```
mods\<mod>\
  mod.json                       name and mod ID# (1-112; a mod's own items and characters use it)
  data\...                       replaces game files with the same path (sprites, sounds, tables)
  dlc\dlcNN_<kind>_<name>\data\  a new character / enemy / stage package (as the game's DLC)
  modules\dll<name>.dll          code of a new character or enemy (built by CVHDEdit)
```

## Sprites (`.opd` + `.csr` + `.col`)

- `p_<name>.opd`: frames (image parts, hit boxes, origin) and animations (frame, ticks per key).
  Frames and animations are numbered; the game's code asks for them by number, so keep the order.
- `f_<name>NN.csr`: 128x128 4-bit image banks. `c_<name>.col`: the colour file, 256 blocks of 16
  colours. A part draws with block `layer` plus the chosen character colour (0-7).
- Easiest route outside CVHDEdit: export frames as PNG (Sprites > Export all frames), edit them, and load them
  back with "Replace frame / animation with pictures".

## Settings files (JSON)

CVHDEdit edits all of these under Mods > Game rules and settings. A mod's value replaces the game's; the game's own files are never changed.

| File | What it does | Row fields |
|---|---|---|
| `data\player\damage_boxes.json` | boxes on a player sprite's frames that hurt enemies | sprite (e.g. `p_juste`), frame, x, y, w, h (from the frame origin), damage |
| `data\player\character_slots.json` | equipment slots per character | id, slots (15 x `1`/`0`), equipAll, freeSlots, deny (item ids) |
| `data\player\afterimage.json` | ghost trail per character id | off, window (s), interval (s), scale, color (RRGGBBAA) |
| `data\player\movement.json` | walk / jump / dash tuning, per character section | key = value |
| `data\item\equip_extra.json` | extra items a character may equip | item id: [character ids] |
| `data\item\skill_variants.json` | Skill builder skills (one row per input) | item, input, kind, shot, speed, duration, fly, dash, ... |
| `data\item\drops.json` | mod items dropped by enemies and chests | source (enemy name, `chest`, `chestN`), item, rate, rare |
| `data\shop\shop_stock.json` | items added to the shop and their prices | stock list, prices |
| `data\shot\mod_shots.json` | sprite projectiles and costumes | id: opd, anim, hitW, hitH, damage, life, gravity, pierce |
| `data\difficulty\levels.json` | difficulty levels | name, basedOn, hp, atk, def, levelPlus, unlockAfter, enemySpeed, bossSpeed |
| `data\player\exp.json` | EXP rules | key = value |
| `dataattle
ules.json` | battle rules | damageFormula (`original` or `unity`), critChance (%), critMul, dropMul, goldMul, expMul, mpCostMul, statusMul, coop2 ... coop8 (enemy HP multiplier by online player count) |
| `data\itemadges.json` | movement and other effects of equipped items | item: speedSet, backdashSet, slideSet (bonus %, replaces the item's own), gravity, jump, speed, backdash, slide, defense, airControl, oneHit, moonwalk, voicePitch |
| `dataattle\item_effects.json` | effects of equipped items | item, atk (damage dealt x), taken (damage taken x), enemyDef (enemy defence x), skillAtk, mpRegen, block (%) |
| `dataattle\growth.json` | character growth | character (0 = all), levelAtk (9 numbers by weapon level), crit (9 numbers, %), str (unity) |
| `data\enemy\hard_attacks.json` | extra enemy attacks by difficulty | enemy, level, shot, every, count, pause, dx, dy, xStep, speed, angle, aim, range |

Rows are JSON arrays of objects with the field names above; a field left out keeps the game's value.

## New items

A mod's own items are numbered `1000000 + 1000 x modID# + 64 x kind + n` and live in
`data\item\ext\<kind>set.dat` (the game's table format, one record per item) with their names in
`data\item\ext\names.json`.

## Code

New characters and enemies are copies of a game character's or enemy's code
(`decomp\src\Dll\ModPlayer\<Name>`, `ModEnemy\<Name>`), built into `modules\dll<name>.dll`.
CVHDEdit makes and builds these; the decomp tree and LLVM are needed to change their behaviour.

## Script enemies and bosses (no code)

`data/enemy/script/<name>.json` makes an enemy or boss from states instead of code; a room spawns it as
`SCRIPT_<name>`. Each state plays an animation of the sprite for a time, moves (none / toward / away / forward /
hover / jump), plays a sound, fires timed attacks (sprite shots from `mod_shots.json`, or hit boxes) and picks the
next state by weight and player distance. Phases switch state once when HP falls below a %. CVHDEdit edits them
under Mods > Script enemies and bosses. `mods/script_barlowe` (Barlowe from the Unity remake) is a worked example.
