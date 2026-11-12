// Dll/Player/Soma/SomaData.h - dllsoma data tables (SomaData.cpp is generated
// by the decompilation project).
#pragma once

#include "Dll/Player/PlayerInterface.h"

enum {
    SOMA_ANIM_COUNT = 0x10C,
    SOMA_VOICE_COUNT = 0x72,
};

extern const PlayerAnimEntry g_somaAnimTable[SOMA_ANIM_COUNT];
extern const unsigned int g_somaCommand0[5];
extern const unsigned int* const g_somaCommands[1];
extern const int g_somaCommandAnims[1];
extern const char* const g_somaVoiceNames[SOMA_VOICE_COUNT];
extern const char g_somaOpdPath[];
extern const char g_somaVoicePathJp[];
extern const char g_somaVoicePath[];
