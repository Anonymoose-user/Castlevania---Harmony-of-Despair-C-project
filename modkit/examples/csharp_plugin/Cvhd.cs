// Cvhd.cs - C# bindings for decomp/include/Port/cvhd_api.h (CVHD_API_VERSION 1).
// The CvhdApi table is read in place: every field is a cdecl function pointer
// with the exact C types (int = int, unsigned = uint, float = float,
// CvhdHandle = ulong, CvhdHookHandle = uint, char* = byte* UTF-8,
// CvhdHookEvent* = IntPtr). On x64 cdecl is the one Windows x64 convention.
using System;
using System.Runtime.InteropServices;
using System.Text;

namespace Cvhd;

/// <summary>Mirror of the C struct CvhdApi (x64, sequential, natural alignment).</summary>
[StructLayout(LayoutKind.Sequential)]
public unsafe struct CvhdApiNative
{
    public int version;
    public int size;
    public byte* modDir;
    public delegate* unmanaged[Cdecl]<int> apiVersion;
    public delegate* unmanaged[Cdecl]<byte*, void> log;
    public delegate* unmanaged[Cdecl]<byte*, IntPtr, IntPtr, int, uint> hookRegister;   // (event, CvhdHookFn, user, priority)
    public delegate* unmanaged[Cdecl]<uint, int> hookUnregister;
    public delegate* unmanaged[Cdecl]<IntPtr, byte*> eventName;
    public delegate* unmanaged[Cdecl]<IntPtr, byte*, int> eventHas;
    public delegate* unmanaged[Cdecl]<IntPtr, byte*, int, int> eventGetInt;
    public delegate* unmanaged[Cdecl]<IntPtr, byte*, float, float> eventGetFloat;
    public delegate* unmanaged[Cdecl]<IntPtr, byte*, byte*> eventGetString;
    public delegate* unmanaged[Cdecl]<IntPtr, byte*, ulong> eventGetHandle;
    public delegate* unmanaged[Cdecl]<IntPtr, byte*, int, int> eventSetInt;
    public delegate* unmanaged[Cdecl]<IntPtr, byte*, float, int> eventSetFloat;
    public delegate* unmanaged[Cdecl]<IntPtr, int> eventHasResult;
    public delegate* unmanaged[Cdecl]<IntPtr, float> eventGetResult;
    public delegate* unmanaged[Cdecl]<IntPtr, float, void> eventSetResult;
    public delegate* unmanaged[Cdecl]<IntPtr, int> eventCancel;
    public delegate* unmanaged[Cdecl]<IntPtr, int> eventIsCancelled;
    public delegate* unmanaged[Cdecl]<int> playerCount;
    public delegate* unmanaged[Cdecl]<int, ulong> playerHandle;
    public delegate* unmanaged[Cdecl]<ulong, int> playerSlot;
    public delegate* unmanaged[Cdecl]<int, float*, float*, int> playerPosition;
    public delegate* unmanaged[Cdecl]<int, float> playerHp;
    public delegate* unmanaged[Cdecl]<int, float, float, float, float, ulong, ulong> shotSpawn;
    public delegate* unmanaged[Cdecl]<byte*, int> soundPlay;
    public delegate* unmanaged[Cdecl]<int, int, int> random;
    public delegate* unmanaged[Cdecl]<int> stageId;
    public delegate* unmanaged[Cdecl]<int> stageIndex;
    public delegate* unmanaged[Cdecl]<int> stageActive;
    public delegate* unmanaged[Cdecl]<uint> stageFlags;
    // version 1 ends here; later versions only append
}

public static class HookResult { public const int Continue = 0, Stop = 1; }

/// <summary>Static helpers over the table. Call Init once from CvhdPluginInit.</summary>
public static unsafe class Api
{
    static CvhdApiNative* s_api;

    public static bool Init(IntPtr api)
    {
        var p = (CvhdApiNative*)api;
        if (p == null || p->version < 1 || p->size < sizeof(CvhdApiNative)) return false;
        s_api = p;
        return true;
    }

    public static CvhdApiNative* Raw => s_api;
    public static string? ModDir => Str(s_api->modDir);

    internal static byte[] Utf8(string s)
    {
        var b = new byte[Encoding.UTF8.GetByteCount(s) + 1];   // + NUL
        Encoding.UTF8.GetBytes(s, 0, s.Length, b, 0);
        return b;
    }
    internal static string? Str(byte* p) => p == null ? null : Marshal.PtrToStringUTF8((IntPtr)p);

    public static void Log(string text) { fixed (byte* b = Utf8(text)) s_api->log(b); }
    public static int ApiVersion() => s_api->apiVersion();

    /// <summary>Register a listener: pass &amp;Method of an
    /// [UnmanagedCallersOnly(CallConvs = new[] { typeof(CallConvCdecl) })] static int Method(IntPtr ev, IntPtr user).
    /// Returns the handle, 0 on failure.</summary>
    public static uint HookRegister(string evName, delegate* unmanaged[Cdecl]<IntPtr, IntPtr, int> fn, IntPtr user = default, int priority = 0)
    {
        fixed (byte* b = Utf8(evName)) return s_api->hookRegister(b, (IntPtr)fn, user, priority);
    }
    public static bool HookUnregister(uint h) => s_api->hookUnregister(h) == 1;

    public static int PlayerCount() => s_api->playerCount();
    public static ulong PlayerHandle(int slot) => s_api->playerHandle(slot);
    public static int PlayerSlot(ulong player) => s_api->playerSlot(player);
    public static float PlayerHp(int slot) => s_api->playerHp(slot);
    public static bool PlayerPosition(int slot, out float x, out float y)
    {
        float fx = 0, fy = 0;
        int ok = s_api->playerPosition(slot, &fx, &fy);
        x = fx; y = fy;
        return ok == 1;
    }
    public static ulong ShotSpawn(int id, float x, float y, float speed, float angleDeg, ulong owner = 0)
        => s_api->shotSpawn(id, x, y, speed, angleDeg, owner);
    public static bool SoundPlay(string name) { fixed (byte* b = Utf8(name)) return s_api->soundPlay(b) == 1; }
    public static int Random(int low, int high) => s_api->random(low, high);
    public static int StageId() => s_api->stageId();
    public static int StageIndex() => s_api->stageIndex();
    public static bool StageActive() => s_api->stageActive() != 0;
    public static uint StageFlags() => s_api->stageFlags();
}

/// <summary>Wraps the opaque CvhdHookEvent* given to a listener. Valid only inside that call.</summary>
public readonly unsafe struct HookEvent
{
    public readonly IntPtr Ptr;
    public HookEvent(IntPtr p) { Ptr = p; }
    static CvhdApiNative* A => Api.Raw;

    public string? Name => Api.Str(A->eventName(Ptr));
    public bool Has(string f) { fixed (byte* b = Api.Utf8(f)) return A->eventHas(Ptr, b) != 0; }
    public int GetInt(string f, int def = 0) { fixed (byte* b = Api.Utf8(f)) return A->eventGetInt(Ptr, b, def); }
    public float GetFloat(string f, float def = 0) { fixed (byte* b = Api.Utf8(f)) return A->eventGetFloat(Ptr, b, def); }
    public string? GetString(string f) { fixed (byte* b = Api.Utf8(f)) return Api.Str(A->eventGetString(Ptr, b)); }
    public ulong GetHandle(string f) { fixed (byte* b = Api.Utf8(f)) return A->eventGetHandle(Ptr, b); }
    public bool SetInt(string f, int v) { fixed (byte* b = Api.Utf8(f)) return A->eventSetInt(Ptr, b, v) == 1; }
    public bool SetFloat(string f, float v) { fixed (byte* b = Api.Utf8(f)) return A->eventSetFloat(Ptr, b, v) == 1; }
    public bool HasResult => A->eventHasResult(Ptr) != 0;
    public float Result { get => A->eventGetResult(Ptr); set => A->eventSetResult(Ptr, value); }
    public bool Cancel() => A->eventCancel(Ptr) != 0;
    public bool IsCancelled => A->eventIsCancelled(Ptr) != 0;
}
