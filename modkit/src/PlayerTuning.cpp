// Dll/Player/PlayerTuning.cpp - data/player/movement.txt (native modding,
// not in the original; format in docs/modding_player.md).
//
// The modules have no host call for files, so this reads the mods folder
// the way native/platform/fs.cpp does: $CVHD_MODS_DIR or <exe dir>/mods,
// enabled mods from load_order.txt (first = highest priority). Lower
// priority mods apply first, so the highest-priority mod has the last word.
// Lines: `<key> <value>`, '#' comments.
#include "Port/JsonSettings.h"
#include "Dll/Player/PlayerTuning.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h>

namespace {

PlayerTuning g_tuning = { -290.0f, 0.45f, -8.0f, 0.05f, -203.0f, -50.0f, 630.0f, 627.2f, 1.0f, 0.0f, 0.0f };

struct Key { const char* name; float PlayerTuning::* field; };
const Key kKeys[] = {
    { "jumpSpeed", &PlayerTuning::jumpSpeed },         { "shortHop", &PlayerTuning::shortHop },
    { "apexSpeed", &PlayerTuning::apexSpeed },         { "holdTime", &PlayerTuning::holdTime },
    { "highJumpSpeed", &PlayerTuning::highJumpSpeed }, { "maxRise", &PlayerTuning::maxRise },
    { "jumpGravity", &PlayerTuning::jumpGravity },     { "fallGravity", &PlayerTuning::fallGravity },
    { "moveSpeedScale", &PlayerTuning::moveSpeedScale },
    { "personalSkill", &PlayerTuning::personalSkill },
    { "riseGravity", &PlayerTuning::riseGravity },
};

// This module's character name: the module file name (soma.dll -> soma),
// matched against [section] lines.
char g_self[64];

void findSelf()
{
    HMODULE m = 0;
    GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCSTR)&g_tuning, &m);
    char path[MAX_PATH];
    if (m == 0 || GetModuleFileNameA(m, path, sizeof(path)) == 0) return;
    const char* b = strrchr(path, '\\');
    b = b ? b + 1 : path;
    snprintf(g_self, sizeof(g_self), "%s", b);
    char* dot = strrchr(g_self, '.');
    if (dot) *dot = 0;
}

// Lines before any [section] apply to everyone; a [name] section applies
// only to that character's module.
void applyFile(const char* path)
{
    std::string text;
    if (!jsonsettings::readFile(path, text)) return;   // movement.json (sections), else movement.txt
    char line[256], key[64];
    float v;
    bool on = true;
    size_t pos = 0;
    while (pos < text.size()) {
        size_t eol = text.find('\n', pos);
        if (eol == std::string::npos) eol = text.size();
        snprintf(line, sizeof(line), "%s", text.substr(pos, eol - pos).c_str());
        pos = eol + 1;
        char sec[64];
        if (sscanf(line, " [%63[^]]]", sec) == 1) { on = _stricmp(sec, g_self) == 0; continue; }
        if (!on) continue;
        if (sscanf(line, " %63s %f", key, &v) != 2 || key[0] == '#') continue;
        for (const Key& k : kKeys)
            if (_stricmp(key, k.name) == 0) g_tuning.*k.field = v;
    }
}

void load()
{
    findSelf();
    char root[MAX_PATH];
    const char* env = getenv("CVHD_MODS_DIR");
    if (env && *env) {
        snprintf(root, sizeof(root), "%s", env);
    } else {
        GetModuleFileNameA(0, root, sizeof(root));
        char* s = strrchr(root, '\\');
        if (s) *s = 0;
        strncat(root, "\\mods", sizeof(root) - strlen(root) - 1);
    }
    char path[MAX_PATH * 2];
    snprintf(path, sizeof(path), "%s\\load_order.txt", root);
    FILE* f = fopen(path, "r");
    if (f == 0) return;
    char names[64][64];
    int n = 0;
    char line[256];
    while (n < 64 && fgets(line, sizeof(line), f)) {
        if (sscanf(line, " %63[^\r\n]", names[n]) != 1 || names[n][0] == '#') continue;
        for (char* e = names[n] + strlen(names[n]); e > names[n] && (e[-1] == ' ' || e[-1] == '\t'); ) *--e = 0;
        n++;
    }
    fclose(f);
    for (int i = n - 1; i >= 0; i--) {
        snprintf(path, sizeof(path), "%s\\%s\\data\\player\\movement.txt", root, names[i]);
        applyFile(path);
    }
}

}  // namespace

const PlayerTuning& playerTuning()
{
    static bool loaded = false;
    if (!loaded) { loaded = true; load(); }
    return g_tuning;
}
