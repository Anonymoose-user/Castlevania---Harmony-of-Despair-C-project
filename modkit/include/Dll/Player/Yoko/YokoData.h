// Dll/Player/Yoko/YokoData.h - dllyoko data tables (YokoData.cpp is generated
// by the decompilation project).
#pragma once

#include "Dll/Player/PlayerInterface.h"

enum {
    YOKO_ANIM_COUNT = 0x10C,
    YOKO_VOICE_COUNT = 0x72,
};

extern const PlayerAnimEntry g_yokoAnimTable[YOKO_ANIM_COUNT];
extern const char* const g_yokoVoiceNames[YOKO_VOICE_COUNT];
extern const char g_yokoOpdPath[];
extern const char g_yokoVoicePathJp[];
extern const char g_yokoVoicePath[];
