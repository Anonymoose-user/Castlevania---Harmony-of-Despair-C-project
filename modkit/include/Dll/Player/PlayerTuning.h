// Dll/Player/PlayerTuning.h - global movement tuning for the player modules
// (native modding, not in the original). The original values are the
// literals the state constructors and PlayerParam::getMoveSpeed used; mods
// change them through data/player/movement.txt (docs/modding_player.md).
#pragma once

struct PlayerTuning {
    float jumpSpeed;        // PlayerJumpState::m_jumpSpeed      -290
    float shortHop;         // PlayerJumpState::m_shortHop       0.45
    float apexSpeed;        // PlayerJumpState::m_apexSpeed      -8
    float holdTime;         // PlayerJumpState::m_holdTime       0.05
    float highJumpSpeed;    // PlayerJumpState::m_highJumpSpeed  -203
    float maxRise;          // PlayerJumpState::m_maxRise        -50
    float jumpGravity;      // PlayerJumpState::m_gravity        630
    float fallGravity;      // PlayerState10::m_gravity          627.2
    float moveSpeedScale;   // multiplier on PlayerParam::getMoveSpeed  1
    float personalSkill;    // modules that offer a choice (dllalucard2): 0 bat, 1 mist
    float riseGravity;      // PlayerBase::m_f2C4, 580 for every character; 0 = unchanged
};

// The tuning, read once on first use (the defaults on the original build).
const PlayerTuning& playerTuning();
