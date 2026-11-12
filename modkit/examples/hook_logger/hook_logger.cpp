// hook_logger - an example CVHD plugin (a plain DLL, not a game module).
// Install: mods/<your mod>/plugins/hook_logger.dll (+ the mod enabled in Manage Mods).
// Setting: mods/<your mod>/hook_logger.txt containing "doubleDamage=1" doubles
// the damage players take. Logs every enemy kill to the game log.
//
// Build (Git Bash or cmd, from this folder; include = the kit's include/):
//   clang-cl -nologo -O2 -std:c++17 -I../../include -LD hook_logger.cpp -Fehook_logger.dll
// Uses only Port/cvhd_api.h (plain C ABI), so any CRT works.
#define _CRT_SECURE_NO_WARNINGS
#include "Port/cvhd_api.h"

#include <stdio.h>
#include <string.h>

static const CvhdApi* g_api;
static bool g_double;

static int onEnemyKilled(CvhdHookEvent* ev, void*)
{
    char line[160];
    const char* name = g_api->eventGetString(ev, "name");
    snprintf(line, sizeof line, "hook_logger: %s killed at (%.0f, %.0f) by player %d", name ? name : "?",
             g_api->eventGetFloat(ev, "x", 0), g_api->eventGetFloat(ev, "y", 0), g_api->eventGetInt(ev, "killer", -1));
    g_api->log(line);
    return CVHD_HOOK_CONTINUE;
}

static int onPlayerDamaged(CvhdHookEvent* ev, void*)
{
    g_api->eventSetResult(ev, g_api->eventGetResult(ev) * 2.0f);
    return CVHD_HOOK_CONTINUE;
}

static bool readSetting(const char* dir)
{
    char path[512];
    snprintf(path, sizeof path, "%s/hook_logger.txt", dir ? dir : ".");
    FILE* f = fopen(path, "r");
    if (!f) return false;
    char buf[256];
    bool on = false;
    while (fgets(buf, sizeof buf, f))
        if (strncmp(buf, "doubleDamage=", 13) == 0) on = buf[13] == '1';
    fclose(f);
    return on;
}

extern "C" __declspec(dllexport) int cvhdPluginInit(const CvhdApi* api)
{
    if (api == 0 || api->version < 1) return 1;
    g_api = api;
    g_double = readSetting(api->modDir);
    api->hookRegister("enemyKilled", onEnemyKilled, 0, 0);
    if (g_double) api->hookRegister("playerDamaged", onPlayerDamaged, 0, 0);
    api->log(g_double ? "hook_logger: loaded (double damage on)" : "hook_logger: loaded");
    return 0;
}

extern "C" __declspec(dllexport) void cvhdPluginShutdown(void) {}
