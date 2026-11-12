// Dll/ModPlayer/Testguy/TestguyData.h - dlltestguy data tables (TestguyData.cpp is generated
// by the decompilation project).
#pragma once

#include "Dll/Player/PlayerInterface.h"

enum {
    TESTGUY_ANIM_COUNT = 0x10C,
    TESTGUY_VOICE_COUNT = 0x72,
};

extern const PlayerAnimEntry g_testguyAnimTable[TESTGUY_ANIM_COUNT];
extern const unsigned int g_testguyCommand0[5];
extern const unsigned int* const g_testguyCommands[1];
extern const int g_testguyCommandAnims[1];
extern const char* const g_testguyVoiceNames[TESTGUY_VOICE_COUNT];
extern const char g_testguyOpdPath[];
extern const char g_testguyVoicePathJp[];
extern const char g_testguyVoicePath[];
