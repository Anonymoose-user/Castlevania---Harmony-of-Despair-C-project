# C# plugin example (prepared, not shipped yet)

A C# version of `examples/hook_logger`: it logs every `enemyKilled` event.

- `Cvhd.cs` - bindings for `Port/cvhd_api.h`: `CvhdApiNative` mirrors the C `CvhdApi`
  struct field by field (`delegate* unmanaged[Cdecl]<...>`), `Api` wraps the calls
  (Log, HookRegister, players, shots, sound, stage), `HookEvent` wraps a listener's event.
- `ExamplePlugin.cs` - `CvhdExample.CvhdPlugin.CvhdPluginInit(IntPtr api)`.

## How it is loaded

The game only loads native DLLs from `mods/<mod>/plugins/`. The native shim
`csharp_host.dll` (`../csharp_host/csharp_host.cpp`) is such a plugin. In its
`cvhdPluginInit` it:

1. reads `mods/<mod>/plugins/csharp.txt` (`<assembly path> <Namespace.Type> [method]`),
2. finds hostfxr through nethost (`get_hostfxr_path`; a `dotnet/` folder next to cvhd.exe wins),
3. starts the runtime once with `hostfxr_initialize_for_runtime_config(<asm>.runtimeconfig.json)`,
4. gets `load_assembly_and_get_function_pointer` and asks for each type's `CvhdPluginInit`
   with `UNMANAGEDCALLERSONLY_METHOD`,
5. calls it with the game's `const CvhdApi*`. Errors are logged, never fatal.

## Build

    dotnet build -c Release -o out

(no NuGet packages; the restore is offline). Output: `CvhdExample.dll` and
`CvhdExample.runtimeconfig.json`.

## Install

    mods/<mod>/plugins/csharp_host.dll
    mods/<mod>/plugins/csharp.txt          ->  csharp/CvhdExample.dll  CvhdExample.CvhdPlugin
    mods/<mod>/plugins/csharp/CvhdExample.dll
    mods/<mod>/plugins/csharp/CvhdExample.runtimeconfig.json

Players need the .NET 10 x64 runtime (or a `dotnet/` folder shipped next to cvhd.exe).

## Rules

- Entry points and listeners are `[UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]`
  static methods; catch every exception inside them.
- Listeners run on the game's worker threads, possibly two at once: be quick, no blocking.
- Never keep a `HookEvent` after the listener returns; keep `CvhdHandle` (ulong) values, not pointers.
- No F5 reload of C# code yet.
