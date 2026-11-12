// ExamplePlugin.cs - C# version of examples/hook_logger: logs every enemy kill.
using System;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using Cvhd;

namespace CvhdExample;

public static unsafe class CvhdPlugin
{
    // Called by csharp_host with the game's const CvhdApi*. 0 = ok.
    [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
    public static int CvhdPluginInit(IntPtr api)
    {
        try
        {
            if (!Api.Init(api)) return 1;
            if (Api.HookRegister("enemyKilled", &OnEnemyKilled) == 0)
                Api.Log("csharp example: enemyKilled register failed");
            Api.Log("csharp example: loaded (mod dir " + (Api.ModDir ?? "?") + ")");
            return 0;
        }
        catch { return 1; }   // never let an exception cross into native code
    }

    // Runs on a game worker thread: keep it quick, hold no locks across calls.
    [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })]
    static int OnEnemyKilled(IntPtr evPtr, IntPtr user)
    {
        try
        {
            var ev = new HookEvent(evPtr);
            Api.Log($"csharp example: {ev.GetString("name") ?? "?"} killed at ({ev.GetFloat("x"):F0}, {ev.GetFloat("y"):F0}) by player {ev.GetInt("killer", -1)}");
        }
        catch { }
        return HookResult.Continue;
    }
}
