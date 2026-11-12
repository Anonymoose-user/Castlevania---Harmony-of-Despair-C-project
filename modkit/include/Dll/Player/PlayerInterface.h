// Dll/Player/PlayerInterface.h - the interface the original game drives a player
// module through (vtable dllsoma, 284 slots, all pure). Each
// player module's factory returns one of these (see Dll/DllMain.h).
// Names are inferred; the slot list lives in PlayerSlots.inc.
#pragma once

#include "Dll/DllRuntime.h"

class PlayerState;
class PlayerInput;
struct PlayerBuff;
struct PlayerEquipStats;

// Host callbacks stored by the player (plain function pointers).
typedef unsigned int (*PlayerRandFunc)(int arg);        // +0x338, result >> 3 is used
typedef int (*PlayerHostFunc)(int a, int b);             // +0x340 / +0x344

struct PlayerInitVitals {        // slot +0x02C
    float hp;
    float mp;
    float attr[5];
};

struct PlayerAnimEntry {         // per-animation entry; slot +0x26C copies 0x10C of them
    unsigned int id;             // 0xFF: animation not available
    unsigned int arg;
};

struct PlayerAttackInfo {        // slot +0x3EC fills one
    int damage;                  // +0x00 scale * (power / 100 + 1)
    int kind;                    // +0x04 always 2
    float f08;                   // +0x08 0.5 or 0.1
    float dir;                   // +0x0C facing, 0 for the 0x2D/0x2E kinds
    float f10;                   // +0x10
    int i14;                     // +0x14 always 50
};

struct PlayerEvent16 {           // element of PlayerBase::m_events
    int a;
    bool b;
    const int* c;                // the petrify state passes the address of a value
    int d;
};

struct PlayerEvent2C {           // element of PlayerBase::m_events2 (0x2C bytes)
    int a0, a1, a2, a3, a4;      // +0x00
    int stateId;                 // +0x14 state that queued it
    int a6, a7;                  // +0x18
    float f;                     // +0x20
    int a8;                      // +0x24
    int a9;                      // +0x28 6 is replaced by PlayerBase::m_i260
};

class IPlayer : public DllObject {
public:
    virtual ~IPlayer();
#define PLAYER_SLOT(off, ret, name, params, base) virtual ret name params = 0;
#define PLAYER_SLOT_BASE(off, ret, name, params, base)
#include "Dll/Player/PlayerSlots.inc"
#undef PLAYER_SLOT
#undef PLAYER_SLOT_BASE
};
