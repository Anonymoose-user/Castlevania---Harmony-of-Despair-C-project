# Modding hooks: events and the C API

The game has one event bus (`decomp/src/Port/Hooks.cpp`). Game code emits named
events; plugins, module DLLs and (later) Lua and C# scripts listen. Everything
crosses a plain C ABI (`decomp/include/Port/cvhd_api.h`), exported from
`cvhd.exe`, so any language that can call C can use it.

## Basics

- Register: `cvhdHookRegister("enemyKilled", fn, user, priority)` returns a handle
  (0 = failed); `cvhdHookUnregister(handle)` removes it.
- Listener: `int fn(CvhdHookEvent* ev, void* user)`. Return `0` (continue) or `1`
  (handled: later listeners do not run). Higher `priority` runs first; equal
  priorities run in register order.
- Fields are read by name: `cvhdEventGetInt / GetFloat / GetString / GetHandle`
  (int and float convert into each other; a missing field gives the default).
  `cvhdEventSetInt / SetFloat` change a field (only useful between listeners; the
  game reads back only the **result** and **cancel**).
- **Result**: events marked "result" carry a number the game uses after the emit
  (`cvhdEventGetResult` / `cvhdEventSetResult`). **Cancel**: `cvhdEventCancel`
  works only on events marked "cancellable"; it also stops later listeners.
- Handles (`CvhdHandle`, 64-bit) are game object handles. Never keep raw pointers.
- **Threads**: the frame runs on 2 worker threads, and a listener runs on the thread
  that emitted the event, possibly at the same time as another call. Keep listeners
  quick, do not block, do not hold your own locks across game calls. A listener removed
  during an emit may still receive that emit.
- Cost: an event nobody listens to costs one atomic load at its call site.

## Events

| Event | Fields | Result / cancel | Where it is emitted |
|---|---|---|---|
| `frame` | `dt` float (seconds) | - | `GameApp::update` (`Game/GameMain.cpp`), once per frame on the main thread after the frame's tasks finish (via `hookFrame`, which loads plugins on the first frame) |
| `roomEnter` | `room` int (stage id), `index` int, `player` int (always -1) | - | `Stage_selectRoom` (`Game/Stage/Stage.cpp`). In this game a "room" is a whole stage, so this fires when a stage is chosen, before loading |
| `stageStart` | `stage` int (id), `index` int | - | `Stage` update, load state 2 -> 3 after `Stage_spawnObjects` (stage loaded and running) |
| `stageEnd` | `stage` int, `result` int (-1 quit, -2 all down, -3 aborted, 1 cleared, 2-4 survival) | - | `Stage` update, unload request, before resources are released |
| `enemySpawn` | `name` string, `enemy` handle, `x` `y` float (spawn point), `boss` int | - | `enemyManagerSpawn` (`Game/Enemy/EnemyRegistry.cpp`); stage/boss/script spawns, not parts built inside an enemy |
| `enemyKilled` | `name` string, `enemy` handle, `x` `y` float, `killer` int (player slot, -1 unknown), `boss` int | - | `EnemyBase::onKilled` (`Game/Enemy/EnemyBase.cpp`), where drops are rolled |
| `damageCalc` | `enemy` handle, `name` string, `attacker` int (player slot or -1), `amount` float, `power` int, `flags` int (attack flags) | result = damage (default: the game's), cancellable (the hit does nothing) | `EnemyBase::takeDamage` right after the damage formula and the player's attack bonus |
| `playerDamaged` | `player` int (slot), `handle` handle, `amount` float, `attacker` handle (object that hit), `flags` int, `direct` int | result = damage power (default: the attack's), cancellable (hit refused). A result of 0 or less refuses the hit | `PlayerObject::takeHit` (`Game/Player/PlayerObjectDamage.cpp`) after the invulnerability checks, before guard/defence |
| `itemPicked` | `player` int, `handle` handle, `item` int (item id), `category` int | - | `PlayerObject::onItemPickup` (`Game/Player/PlayerObjectUpdate.cpp`) after the item is added (dropped category-8 items) |
| `shotSpawn` | `category` int, `skill` int, `owner` handle, `player` int (owner's slot or -1), `x` `y` float, `level` int | cancellable (no shot is made) | `CShot_Dll::create` (`Game/Shot/Shot_Dll.cpp`), every shot made by (category, skill), incl. mod sprite shots (category 12) |

Not covered yet: gold/chest pickups, enemy damage done by DLL enemy families that
override `takeDamage`, per-screen room changes (the game has none).

## C API (`Port/cvhd_api.h`, version 1)

| Function | What |
|---|---|
| `int cvhdApiVersion()` | `CVHD_API_VERSION` (1) |
| `void cvhdLog(const char*)` | a line in the game log (stderr), prefixed `[mod]` |
| `CvhdHookHandle cvhdHookRegister(event, fn, user, priority)` / `int cvhdHookUnregister(h)` | listeners |
| `cvhdEventName`, `cvhdEventHas`, `cvhdEventGetInt/Float/String/Handle`, `cvhdEventSetInt/Float` | fields |
| `cvhdEventHasResult`, `cvhdEventGetResult`, `cvhdEventSetResult` | result slot |
| `cvhdEventCancel`, `cvhdEventIsCancelled` | cancel |
| `int cvhdPlayerCount()` | players in the game |
| `CvhdHandle cvhdPlayerHandle(slot)`, `int cvhdPlayerSlot(handle)` | slot (0-5) <-> handle |
| `int cvhdPlayerPosition(slot, float* x, float* y)` | world position; 1 = ok |
| `float cvhdPlayerHp(slot)` | current HP, -1 = no player |
| `CvhdHandle cvhdShotSpawn(id, x, y, speed, angleDeg, owner)` | a `mod_shots` sprite shot (`data/shot/mod_shots.txt` id), angle 0 = right, 90 = down |
| `int cvhdSoundPlay(name)` | a sound effect by name (`soundPlaySEByNameNoPos`) |
| `int cvhdRandom(low, high)` | `[low, high)` from the game's LCG (`me::random`), on its own stream so the game's streams are untouched |
| `int cvhdStageId()`, `int cvhdStageIndex()`, `int cvhdStageActive()` | the selected stage |
| `unsigned cvhdStageFlags()` | `Stage::flags` (bit 5 cleared, 9 all down, 10 ended, 11 cleared result, 12 timer stopped); read only |
| `const CvhdApi* cvhdGetApi()` | all of the above as one table of function pointers |

## Who can use it

- **Plugins**: a plain DLL in `mods/<mod>/plugins/<name>.dll` of an enabled mod. Loaded on
  the first frame (mods in load order, DLLs by name) and kept until exit. Exports:
  - `int cvhdPluginInit(const CvhdApi* api)` (required; 0 = ok). `api->modDir` is the
    mod's folder, for its own settings files.
  - `void cvhdPluginShutdown(void)` (optional, at exit).
  Example: `tools/modkit/examples/hook_logger`.
- **Module DLLs** (enemy/player/shot): `#include "Dll/DllHooks.h"`, then `dllHooks()`
  returns the table (resolved once through `GetProcAddress(GetModuleHandleA(0), "cvhdGetApi")`).
  Unregister in the module's destructor/unload: a module can be unloaded while its
  listener is registered.
- **Lua**: `data/scripts/*.lua` of enabled mods, through `events.on(name, fn)`; the Lua
  layer (`Port/LuaScripts.cpp`) registers C listeners with these same functions. Guide:
  `docs/modding_lua.md`.

## C# plugins (prepared, not yet shipped)

Status: example code exists and is tested outside the game with a fake `CvhdApi`
(host starts .NET 10, calls the C# init, the C# listener runs). Not yet run in the
game and not in the modkit.

- `tools/modkit/examples/csharp_plugin/` - `Cvhd.cs` (bindings: `CvhdApiNative` mirrors
  `CvhdApi` as `delegate* unmanaged[Cdecl]` fields; `Api` and `HookEvent` helpers),
  `ExamplePlugin.cs` (logs `enemyKilled`, like `hook_logger`), `.csproj`, README.
- `tools/modkit/examples/csharp_host/csharp_host.cpp` - the native shim plugin: nethost ->
  hostfxr -> `hostfxr_initialize_for_runtime_config` -> `load_assembly_and_get_function_pointer`
  (`UNMANAGEDCALLERSONLY_METHOD`) -> calls each C# `CvhdPluginInit(const CvhdApi*)`.
  Build commands are in its header (clang-cl + lld-link, static `libnethost.lib`).

**Build:** `dotnet build -c Release -o out` in the plugin folder (no NuGet packages, offline).

**Install** (per mod):

    mods/<mod>/plugins/csharp_host.dll
    mods/<mod>/plugins/csharp.txt            # "csharp/<Asm>.dll <Namespace.Type> [method]" per line
    mods/<mod>/plugins/csharp/<Asm>.dll
    mods/<mod>/plugins/csharp/<Asm>.runtimeconfig.json

The C# files can also sit directly in `plugins/`; the game then tries them as native
plugins, logs "no cvhdPluginInit export, unloaded" and moves on, so a subfolder is cleaner.

**Players** need the .NET 10 x64 runtime installed, or a private runtime shipped as a
`dotnet/` folder next to cvhd.exe (csharp_host looks there first).

**Limits:** one runtime per process, started by the first C# plugin's runtimeconfig, so all
C# plugins must target net10.0. No F5 reload of C# code yet: the plan is a collectible
`AssemblyLoadContext` per mod, with its hooks unregistered before unload. Exceptions must be
caught inside every `[UnmanagedCallersOnly]` method (one escaping kills the process).

**Threads:** listeners are called from the game's 2 worker threads, maybe at the same time;
keep them quick, no blocking or locks across calls, no Task/async work that touches the API
after the listener returns. `HookEvent` is only valid during the call.

## Using the C API from C# (design note)

The API is plain C ABI, so C# needs no C++ glue:

- **P/Invoke**: the functions are exports of `cvhd.exe`, e.g.
  `[DllImport("cvhd.exe")] static extern int cvhdApiVersion();` works from a C# assembly
  running inside the game process (the exe is already loaded).
- **Function pointers** (preferred): the C# host (started through nethost/hostfxr, see
  `docs/SCRIPTING_RESEARCH.md` section 3) passes `cvhdGetApi()` to the managed side, which
  reads the `CvhdApi` struct as a `[StructLayout(Sequential)]` of
  `delegate* unmanaged[Cdecl]<...>` fields. No marshalling layer, no lookups by name.
- **Listeners**: C# methods marked `[UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]`
  are passed as `CvhdHookFn` (`&OnEnemyKilled`). `CvhdHookEvent*` stays an opaque `IntPtr`;
  strings come back as UTF-8 `byte*` (`Marshal.PtrToStringUTF8`).
- **Planned C# plugin entry point**: an assembly in `mods/<mod>/plugins/<name>.dll` with a
  `<name>.runtimeconfig.json`, and a static method
  `[UnmanagedCallersOnly] public static int CvhdPluginInit(IntPtr api)` in a class named
  `CvhdPlugin` (same contract as the native `cvhdPluginInit`). The host tells it apart from a
  native plugin by the runtimeconfig file. Mod assemblies go in a collectible
  `AssemblyLoadContext` so F5 can unload them; their hooks must be unregistered first.
- Same thread rules as native listeners; never keep managed references to game objects,
  only `CvhdHandle` values.
