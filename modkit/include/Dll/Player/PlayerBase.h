// Dll/Player/PlayerBase.h - player base class every player module links
// (vtable dllsoma, 289 slots; 0x348 bytes). It implements almost
// all of IPlayer; the module's own class supplies the character data slots
// (+0x244..+0x270, +0x298, +0x450..+0x458, +0x474) and the state objects.
// Names are inferred; member offsets are generated from
// the  layout dump by the decompilation project.
#pragma once

#include "Dll/DllAllocator.h"
#include "Dll/Player/PlayerInterface.h"
#include "Dll/Player/PlayerParam.h"

#include <stddef.h>
#include <vector>

class PlayerBase : public IPlayer {
public:
    enum { STATE_COUNT = 0x36 };

    PlayerBase();
    virtual ~PlayerBase();

#define PLAYER_DECL_1(ret, name, params) virtual ret name params;
#define PLAYER_DECL_0(ret, name, params)
#define PLAYER_SLOT(off, ret, name, params, base) PLAYER_DECL_##base(ret, name, params)
#define PLAYER_PURE_1(ret, name, params) virtual ret name params;
#define PLAYER_PURE_0(ret, name, params) virtual ret name params = 0;
#define PLAYER_SLOT_BASE(off, ret, name, params, base) PLAYER_PURE_##base(ret, name, params)
#include "Dll/Player/PlayerSlots.inc"
#undef PLAYER_SLOT
#undef PLAYER_SLOT_BASE
#undef PLAYER_DECL_0
#undef PLAYER_DECL_1
#undef PLAYER_PURE_0
#undef PLAYER_PURE_1

    // non-virtual helpers
    void clearList();
    void clearTimers();
    void setB28D(bool v);
    void tickF304(float dt);
    void updateRegenExtra();
    void resetI25C();
    void changeState(int id);
    void tickTimers(float dt);
    int  getI22C() const;
    unsigned int random() const;
    void setF31C(float v);
    int  getI2D8() const;
    bool isTimerActive(int i) const;
    void setI284(int a, int b);
    int  getI148() const;
    void raiseTimer(unsigned int i, float v);
    bool commitWarp();
    void setF014(bool on, float v);
    int  callHost344(int a, int b);
    int  callHost340(int a, int b);
    void addFlags210(unsigned int bits);
    void clearFlags210(unsigned int bits);
    PlayerParam* getParam() const;
    bool isAction10();
    void setVoice(int v);
    void pushList(int v);
    void pushEvent(int a, bool b, const int* c, int d);

public:
    // <layout:PlayerBase>
    bool m_b004;                                    // +0x004
    bool m_b005;                                    // +0x005 cleared on state change
    bool m_hasF014;                                 // +0x006
    bool m_b007;                                    // +0x007
    bool m_b008;                                    // +0x008
    unsigned char _pad009[0x3];
    float m_f00C;                                   // +0x00C
    float m_f010;                                   // +0x010
    float m_f014;                                   // +0x014
    bool m_b018;                                    // +0x018
    unsigned char _pad019[0x3];
    int m_i01C;                                     // +0x01C
    int m_i020;                                     // +0x020
    float m_f024;                                   // +0x024
    float m_f028;                                   // +0x028
    bool m_b02C;                                    // +0x02C kept across a change to state 0x20
    bool m_b02D;                                    // +0x02D
    unsigned char _pad02E[0x2];
    float m_f030;                                   // +0x030
    float m_f034;                                   // +0x034
    bool m_b038;                                    // +0x038
    unsigned char _pad039[0x3];
    int m_i03C;                                     // +0x03C
    int m_i03CPrev;                                 // +0x040
    int m_i044;                                     // +0x044
    int m_i048;                                     // +0x048
    unsigned int m_flags04C;                        // +0x04C
    float m_f050;                                   // +0x050
    float m_f054;                                   // +0x054
    PlayerParam* m_param;                           // +0x058
    PlayerState* m_states[54];                      // +0x05C indexed by state id 1..53
    int m_i134;                                     // +0x134 0 or 1, compared all over (slot +0x294)
    int m_action;                                   // +0x138
    int m_i13C;                                     // +0x13C
    int m_weapon;                                   // +0x140
    unsigned int m_weaponFlags;                     // +0x144
    int m_i148;                                     // +0x148
    const unsigned int* const* m_commands;          // +0x14C input command list (0-terminated direction/button masks)
    const int* m_commandStates;                     // +0x150
    unsigned int m_commandCount;                    // +0x154
    int m_commandMode;                              // +0x158 10: commands cost skill points (host query 0xC)
    const int* m_commandArgs;                       // +0x15C
    bool m_pendingCommand;                          // +0x160
    unsigned char _pad161[0x3];
    int m_pendingState;                             // +0x164
    int m_i168;                                     // +0x168
    int m_i16C;                                     // +0x16C
    int m_i170;                                     // +0x170
    int m_i174;                                     // +0x174
    float m_f178;                                   // +0x178
    int m_i17C;                                     // +0x17C
    std::vector<PlayerEvent16, DllAllocator<PlayerEvent16> > m_events;// +0x180
    PlayerEvent16 m_curEvent;                       // +0x190
    unsigned int m_eventIndex;                      // +0x1A0
    std::vector<PlayerEvent2C, DllAllocator<PlayerEvent2C> > m_events2;// +0x1A4
    PlayerEvent2C m_curEvent2;                      // +0x1B4
    unsigned int m_event2Index;                     // +0x1E0
    float m_f1E4;                                   // +0x1E4
    float m_f1E8;                                   // +0x1E8
    float m_f1EC;                                   // +0x1EC
    float m_f1F0;                                   // +0x1F0
    float m_f1F4;                                   // +0x1F4
    float m_timers[6];                              // +0x1F8
    unsigned int m_flags210;                        // +0x210
    int m_i214;                                     // +0x214
    float m_f218;                                   // +0x218
    float m_f21C;                                   // +0x21C
    int m_i220;                                     // +0x220
    float m_f224;                                   // +0x224
    float m_f228;                                   // +0x228
    int m_i22C;                                     // +0x22C
    bool m_stateEntered;                            // +0x230
    unsigned char _pad231[0x3];
    float m_dt;                                     // +0x234
    float m_stateTime;                              // +0x238
    int m_stateId;                                  // +0x23C
    int m_prevStateId;                              // +0x240
    int m_nextStateId;                              // +0x244
    int m_i248;                                     // +0x248
    int m_i24C;                                     // +0x24C
    int m_facing;                                   // +0x250 1 = facing left
    bool m_b254;                                    // +0x254
    bool m_b255;                                    // +0x255
    bool m_b256;                                    // +0x256
    bool m_b257;                                    // +0x257
    unsigned int m_u258;                            // +0x258
    int m_i25C;                                     // +0x25C
    int m_i260;                                     // +0x260 0-1 ground, 2-5 air, 6 none (inferred)
    int m_i264;                                     // +0x264
    float m_f268;                                   // +0x268
    float m_f26C;                                   // +0x26C
    float m_f270;                                   // +0x270
    float m_f274;                                   // +0x274
    int m_i278;                                     // +0x278
    bool m_b27C;                                    // +0x27C
    bool m_b27D;                                    // +0x27D
    unsigned char _pad27E[0x2];
    int m_i280;                                     // +0x280
    int m_i284;                                     // +0x284
    int m_i288;                                     // +0x288
    bool m_b28C;                                    // +0x28C
    bool m_b28D;                                    // +0x28D
    bool m_b28E;                                    // +0x28E
    bool m_b28F;                                    // +0x28F
    bool m_b290;                                    // +0x290
    unsigned char _pad291[0x3];
    float m_f294;                                   // +0x294
    float m_f298;                                   // +0x298
    int m_i29C;                                     // +0x29C
    float m_f2A0;                                   // +0x2A0
    int m_i2A4;                                     // +0x2A4
    int m_i2A8;                                     // +0x2A8
    float m_f2AC;                                   // +0x2AC
    int m_i2B0;                                     // +0x2B0
    int m_i2B4;                                     // +0x2B4
    bool m_b2B8;                                    // +0x2B8
    unsigned char _pad2B9[0x3];
    float m_f2BC;                                   // +0x2BC
    PlayerInput* m_input;                           // +0x2C0
    float m_f2C4;                                   // +0x2C4
    float m_f2C8;                                   // +0x2C8
    int m_i2CC;                                     // +0x2CC
    int m_i2D0;                                     // +0x2D0
    bool m_slow;                                    // +0x2D4
    unsigned char _pad2D5[0x3];
    int m_i2D8;                                     // +0x2D8
    int m_i2DC;                                     // +0x2DC
    bool m_hasF2E4;                                 // +0x2E0
    unsigned char _pad2E1[0x3];
    float m_f2E4;                                   // +0x2E4
    float m_f2E8;                                   // +0x2E8
    bool m_b2EC;                                    // +0x2EC
    bool m_regenExtra;                              // +0x2ED
    unsigned char _pad2EE[0x2];
    int m_i2F0;                                     // +0x2F0
    int m_i2F4;                                     // +0x2F4
    int m_i2F8;                                     // +0x2F8
    int m_i2FC;                                     // +0x2FC
    int m_i300;                                     // +0x300
    float m_f304;                                   // +0x304
    int m_i308;                                     // +0x308
    int m_i30C;                                     // +0x30C
    int m_i310;                                     // +0x310
    int m_i314;                                     // +0x314
    int m_i318;                                     // +0x318
    float m_f31C;                                   // +0x31C
    int m_voice;                                    // +0x320 voice request: index into the module voice names (slot +0x458)
    unsigned int m_listIndex;                       // +0x324
    std::vector<int, DllAllocator<int> > m_list;    // +0x328
    PlayerRandFunc m_randFunc;                      // +0x338
    int m_randArg;                                  // +0x33C
    PlayerHostFunc m_hostFunc340;                   // +0x340
    PlayerHostFunc m_hostFunc344;                   // +0x344
    // </layout:PlayerBase>
};

