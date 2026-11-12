# CVHD Modding Kit (module DLLs)

This kit lets you build **game modules** without the game's full source code. Modules are the
small DLLs that hold one playable character, one enemy/boss, or one projectile ("shot"). The
game loads them from `modules/<name>.dll`. A mod can add a new module or replace one by putting a
DLL in `mods/<mod>/modules/<name>.dll`. Mod folders are searched first.

The game's own data is one file, `data.zip` next to `cvhd.exe` (stored, read in place). Game
files are looked up in this order, first wins: `mods/<mod>/...` (by `mods/load_order.txt`),
then the optional loose override folder `<game>/data/` (laid out like the zip), then `data.zip`.
A mod never changes `data.zip`; it ships the same relative path in its own folder. To look at a
base file, open `data.zip` with any zip tool (or CVHDEdit, which reads it directly).

## What is in the kit

| Path | What |
|---|---|
| `include/` | The headers a module can use (base classes, interfaces, helpers) |
| `lib/cvhd_player.lib`, `cvhd_enemy.lib`, `cvhd_shot.lib` | The shared base code for each family (`PlayerBase`, `EnemyObjBase`, `dll::ShotBase`, plus `DllRuntime`) |
| `src/PlayerTuning.cpp` | Movement tuning reader; compiled into every player module by the build script |
| `templates/player` | A complete character (Juste, from Simon's code) |
| `templates/enemy` | A complete boss (Barlowe) |
| `templates/shot` | A complete projectile (Fuma's guard drum, `Fcmdaiko`) |
| `build_module.bat` / `build_module.sh` | Build one module (cmd.exe / Git Bash) |
| `examples/hook_logger` | A plugin DLL using the hook system (`include/Port/cvhd_api.h`) |
| `kit_version.txt` | Which `cvhd.exe` this kit matches |

## Requirements

- **LLVM** for Windows (clang-cl, lld-link, llvm-nm), installed to `C:\Program Files\LLVM`, or
  with its `bin` folder on `PATH` (or set `LLVM_BIN` to that folder).
- **Visual Studio 2022 Build Tools** with "Desktop development with C++" (the MSVC libraries and
  the Windows SDK). The link needs `libcmtd.lib`, `libcpmtd.lib` and `kernel32.lib`. lld-link
  finds an installed Visual Studio by itself; you do not need a developer command prompt.

## Important rules

1. **One game build only.** A module only works with the exact `cvhd.exe` this kit was made
   from (see `kit_version.txt`). The game calls modules through C++ virtual functions and reads
   their objects directly, so the order of virtual slots and every struct layout must match.
   After a game update, get the new kit and rebuild your modules.
2. **Do not change the interface headers.** Never add, remove or reorder virtual functions or
   members in `include/Dll/...` (`PlayerSlots.inc`, `EnemySlots.inc`, `ShotSlots.inc`,
   `PlayerBase.h`, `EnemyObjBase.h`, `ShotBase.h`, ...). Your own class (derived from the base)
   may add members and override the existing virtual functions.
3. **Debug CRT.** The game uses the static debug C runtime (`-MTd`). Modules must too, because
   `std::` containers cross between game and module. The build scripts already do this.
4. **Memory.** Create objects with `DLL_NEW` (it allocates from the game's heap and zero-fills).
   Plain `new` does not zero-fill.
5. Module code is plain Windows C++17. No console/PS3 calls.

## Step by step

1. Copy a template folder somewhere of your own, for example `templates\enemy` to
   `C:\mymod\Grim`.
2. Rename the files and the class (for example `EnemyBarlowe` -> `EnemyGrim`). Keep the module
   glue at the top of the `.cpp` (`DllCreate`, `DllGetFactory`, `cvhdModuleInit`, and for players
   `DLL_IMPLEMENT_FACTORY(...)` / `DLL_IMPLEMENT_MODULE_START()`).
3. Edit the behaviour.
4. Build (the DLL name is lower case and decides how the game finds it, see below):

   ```
   build_module.bat enemy C:\mymod\Grim grim C:\mymod\out
   ```
   or in Git Bash:
   ```
   sh build_module.sh enemy /c/mymod/Grim grim /c/mymod/out
   ```
   This writes `grim.dll` and `grim.pdb` (debug symbols). Arguments: family (`player`, `enemy`
   or `shot`), source folder (every `.cpp` in it is compiled; its headers are on the include
   path), DLL name, output folder (optional, default: current folder).
5. Copy the DLL (and the `.pdb` if you want readable crash stacks) to
   `<game>\mods\<yourmod>\modules\`, and enable the mod in `mods\load_order.txt`.

## How the game finds a module

- **Enemies:** a stage spawn / enemy row named `DLL_<Name>` loads `modules/<name>.dll` (the text
  after `DLL_`, lower case). In the constructor set `m_name = "DLL_<Name>"`. A new enemy also
  needs a stats row named `DLL_<Name>` in a package `EnemyParamNN.dat` and its sprite under
  `data/enemy/DLL_<Name>/`. CVHDEdit's "new enemy" tool sets all of this up; you can then
  replace its DLL with one from this kit.
- **Players:** the character's `.def` record has a module field (16 bytes at `+0x68`), for
  example `dllsoma` -> `modules/soma.dll` (a leading `dll` is dropped). CVHDEdit's character
  cloner writes it.
- **Shots:** the game builds its shot table by scanning DLC package file lists for paths
  containing `dllshot`, for example `dlc/<package>/dll/dllshot/dllshotfcaxe.dll`, which loads
  `modules/shotfcaxe.dll`. On PC these paths come from `modules.txt` files (one path below
  `/game/` per line; the game's own is inside `data.zip`); a mod can ship its own `mods/<mod>/modules.txt` to add a marker. The
  module's `getInfo` gives the shot's skill ID, category, side and name. Replacing an existing
  shot only needs a DLL with the same name (e.g. `shotfcmdaiko.dll`).
- Replacing any game module: ship a DLL with the same file name in `mods/<mod>/modules/`.

## The interfaces

- Startup protocol: `include/Dll/DllMain.h`, `include/Dll/DllRuntime.h`.
- Players: `include/Dll/Player/PlayerInterface.h` (slots in `PlayerSlots.inc`), base class
  `PlayerBase.h`, states `PlayerState.h` / `PlayerStates.h`, data `PlayerParam.h`, input
  `PlayerInput.h`, tuning `PlayerTuning.h`.
- Enemies: `include/Dll/Enemy/EnemyInterface.h` (slots in `EnemySlots.inc`), base class
  `EnemyObjBase.h`. Mutex helper `DllMutex.h`, STL allocator `DllAllocator.h`.
- Shots: `include/Dll/Shot/ShotInterface.h` (slots in `ShotSlots.inc`), base class
  `ShotBase.h` (namespace `dll`), records in `ShotTypes.h`.
- `include/` also has the headers of all of the game's own modules (`Dll/Player/Soma`,
  `Dll/Enemy/Fczombi`, ...) for reference; their `.cpp` files are not in the kit.

## Mod hooks a module can reach

- **Badges:** player modules get badge effects every frame through the exe export
  `cvhdPlayerBadges` (see `Port/BadgeEffects.h`); `PlayerBase` already does this.
- **Movement tuning:** `PlayerTuning.cpp` reads `mods/<mod>/data/player/movement.txt` (or
  `.json`), with `[name]` sections for one module. Read once per module load.
- **Enemy difficulty:** `EnemyObjBase` reads `cvhdEnemyDifficultyLevel` /
  `cvhdEnemyDifficultyFactors` exported by the exe.
- **Hook system:** `include/Port/cvhd_api.h` is the game's plain C API (events such as
  `enemyKilled`, `playerDamaged`, `frame`, plus player/shot/sound/random/stage functions). A
  module gets it with `#include "Dll/DllHooks.h"` and `dllHooks()`. Full list:
  `docs/modding_hooks.md` in the game source, summarised in `cvhd_api.h`.
- **Plugins:** a plain DLL (not a module) in `mods/<mod>/plugins/<name>.dll` exporting
  `int cvhdPluginInit(const CvhdApi* api)` is loaded on the first frame. See
  `examples/hook_logger` (logs enemy kills; doubles player damage when the mod's
  `hook_logger.txt` says `doubleDamage=1`). Build it with
  `clang-cl -nologo -O2 -std:c++17 -I../../include -LD hook_logger.cpp -Fehook_logger.dll`.
- **Lua:** event scripts (`data/scripts/*.lua`) and Lua enemies (`data/enemy/script/<name>.lua`,
  spawned as `LUA_<name>`) need no compiler. Guide: `docs/modding_lua.md`; a ready mod:
  `templates/lua` (copy it into `mods/`, see its `README.txt`).
- Your own exe lookups: `GetProcAddress(GetModuleHandleA(0), "<export>")`.
- Your own data files: read them from `mods/<mod>/...` with normal file I/O (the game's current
  folder is the game folder; `mods/load_order.txt` lists the enabled mods).
