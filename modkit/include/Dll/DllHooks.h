// Dll/DllHooks.h - the hook system and C game API for module DLLs (enemy,
// player, shot modules) and plugins. Resolves cvhd.exe's API table once:
//
//   #include "Dll/DllHooks.h"
//   const CvhdApi* api = dllHooks();          // NULL on an exe without hooks
//   if (api) api->hookRegister("enemyKilled", onKill, this, 0);
//
// Plugins get the same table as the argument of cvhdPluginInit and do not
// need this header. Docs: docs/modding_hooks.md, Port/cvhd_api.h.
#pragma once

#include "Port/cvhd_api.h"

#ifndef _WINDOWS_   // <windows.h> declares them already
extern "C" __declspec(dllimport) void* __stdcall GetModuleHandleA(const char* name);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void* module, const char* name);
#endif

inline const CvhdApi* dllHooks()
{
    static const CvhdApi* api = [] {
        typedef const CvhdApi* (*Fn)(void);
        Fn fn = (Fn)GetProcAddress(GetModuleHandleA(0), "cvhdGetApi");
        const CvhdApi* a = fn != 0 ? fn() : 0;
        return (a != 0 && a->version >= 1) ? a : (const CvhdApi*)0;
    }();
    return api;
}
