// Dll/Player/Fuma/FumaData.h - dllfuma data tables (FumaData.cpp is generated
// by the decompilation project).
#pragma once

#include "Dll/Player/PlayerInterface.h"

enum {
    FUMA_ANIM_COUNT = 0x10C,
    FUMA_VOICE_COUNT = 0x72,
};

extern const PlayerAnimEntry g_fumaAnimTable[FUMA_ANIM_COUNT];
extern const char* const g_fumaVoiceNames[FUMA_VOICE_COUNT];
extern const char g_fumaOpdPath[];
