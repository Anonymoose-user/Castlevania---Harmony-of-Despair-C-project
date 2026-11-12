// Dll/Shot/ShotBase.h - the base class every shot family module links
// (dllshotfcmdaiko, 357 slots; 0x318 bytes). It implements
// every IShot slot: the module hooks (+0x00C..+0x06C) are empty or return 0,
// the rest are the state the original game reads and writes (position and vectors,
// flags, the object lists, point/record lists, host callbacks).
// The module class overrides the hooks and adds members from +0x318.
// Names are inferred; member offsets are generated from
// the  layout dump by the decompilation project.
#pragma once

#include "Dll/Shot/ShotInterface.h"

#include <stddef.h>

// In namespace dll so a native module can include this and the original game
// Game/Shot/ShotBase.h together; define CVHD_DLL_NO_SHOTBASE_ALIAS there
// and write dll::ShotBase. Module sources use the global alias below.
namespace dll {

class ShotBase : public IShot {
public:
    ShotBase();
    virtual ~ShotBase();

#define SHOT_SLOT(off, ret, name, params, base) virtual ret name params;
#define SHOT_DTOR
#include "Dll/Shot/ShotSlots.inc"
#undef SHOT_DTOR
#undef SHOT_SLOT

    // non-virtual helpers of the library (unreferenced in dllshotfcmdaiko;
    // the modules that need them call them directly)
    float distance(const Vec2* a, const Vec2* b) const;
    bool normalize(Vec2* v) const;
    static float wrapAngle(float a);
    static float approachAngle(float from, float to, float step);
    void setMaskBits(int which, unsigned int bits, bool on);
    void setMask(int which, unsigned int v);
    unsigned int getMask(int which) const;

public:
    // <layout:ShotBase>
    float m_f004;                                   // +0x004
    float m_f008;                                   // +0x008
    float m_f00C;                                   // +0x00C
    int m_i010;                                     // +0x010
    bool m_b014;                                    // +0x014
    unsigned char _pad015[0x3];
    int m_i018;                                     // +0x018
    int m_i01C;                                     // +0x01C
    int m_i020;                                     // +0x020
    int m_i024;                                     // +0x024
    int m_i028;                                     // +0x028
    bool m_b02C;                                    // +0x02C
    unsigned char _pad02D[0x3];
    int m_i030;                                     // +0x030
    int m_i034;                                     // +0x034
    int m_i038;                                     // +0x038
    int m_i03C;                                     // +0x03C
    int m_i040;                                     // +0x040
    int m_i044;                                     // +0x044
    Vec2 m_v048;                                    // +0x048
    bool m_b050;                                    // +0x050
    unsigned char _pad051[0x3];
    int m_i054;                                     // +0x054
    bool m_b058;                                    // +0x058
    bool m_b059;                                    // +0x059
    bool m_b05A;                                    // +0x05A
    unsigned char _pad05B[0x1];
    Vec2 m_pos;                                     // +0x05C position (IShot +0x0A0 / +0x0D8)
    Vec2 m_v064;                                    // +0x064 velocity (the modules' start() sets it)
    Vec2 m_v06C;                                    // +0x06C
    Vec2 m_v074;                                    // +0x074
    Vec2 m_v07C;                                    // +0x07C
    Vec2 m_v084;                                    // +0x084
    Vec2 m_v08C;                                    // +0x08C
    Vec2 m_v094;                                    // +0x094
    Vec2 m_v09C;                                    // +0x09C
    Vec2 m_v0A4;                                    // +0x0A4
    float m_rect[4];                                // +0x0AC
    bool m_b0BC;                                    // +0x0BC
    unsigned char _pad0BD[0x3];
    ShotElem24Vec m_elems24;                        // +0x0C0
    float m_f0D0;                                   // +0x0D0
    ShotBlockD4 m_blockD4;                          // +0x0D4
    Vec2 m_v0F0;                                    // +0x0F0
    Vec2 m_v0F8;                                    // +0x0F8
    bool m_hasBounds;                               // +0x100 set with m_v0F0 / m_v0F8 (IShot +0x3DC)
    unsigned char _pad101[0x3];
    ShotPointVec m_points104;                       // +0x104
    ShotPointVec m_points114;                       // +0x114
    ShotNamedPointVec m_points124;                       // +0x124
    ShotIntVec m_ints134;                           // +0x134
    ShotElem144Vec m_elems144;                      // +0x144
    ShotElem154Vec m_elems154;                      // +0x154
    ShotElem164Vec m_elems164;                      // +0x164
    ShotElem174Vec m_elems174;                      // +0x174
    ShotElem184Vec m_elems184;                      // +0x184
    ShotElem194Vec m_elems194;                      // +0x194
    ShotElem1A4Vec m_elems1A4;                      // +0x1A4
    ShotElem1B4Vec m_queue1B4;                      // +0x1B4
    unsigned int m_read1B4;                         // +0x1C4 next element nextElem1B4() returns
    ShotElem1C8Vec m_queue1C8;                      // +0x1C8
    unsigned int m_read1C8;                         // +0x1D8
    ShotElem1DCVec m_queue1DC;                      // +0x1DC
    unsigned int m_read1DC;                         // +0x1EC
    bool m_dead;                                    // +0x1F0 kill() / isDead()
    bool m_b1F1;                                    // +0x1F1
    bool m_b1F2;                                    // +0x1F2
    bool m_b1F3;                                    // +0x1F3
    bool m_b1F4;                                    // +0x1F4
    bool m_b1F5;                                    // +0x1F5
    bool m_b1F6;                                    // +0x1F6
    unsigned char _pad1F7[0x1];
    int m_i1F8;                                     // +0x1F8
    float m_f1FC;                                   // +0x1FC
    float m_f200;                                   // +0x200
    unsigned char m_u204;                           // +0x204 a kind: dllshotfcmdaiko start() tests it for 8
    bool m_b205;                                    // +0x205
    bool m_b206;                                    // +0x206
    bool m_b207;                                    // +0x207
    bool m_b208;                                    // +0x208
    bool m_b209;                                    // +0x209
    bool m_b20A;                                    // +0x20A
    bool m_b20B;                                    // +0x20B
    bool m_b20C;                                    // +0x20C
    bool m_b20D;                                    // +0x20D
    unsigned short m_h20E;                          // +0x20E
    float m_f210;                                   // +0x210
    int m_i214;                                     // +0x214
    bool m_b218;                                    // +0x218
    bool m_b219;                                    // +0x219
    unsigned char _pad21A[0x2];
    int m_facing;                                   // +0x21C nonzero: facing left (start() of the modules)
    float m_f220;                                   // +0x220
    float m_f224;                                   // +0x224
    int m_i228;                                     // +0x228
    int m_i22C;                                     // +0x22C
    bool m_b230;                                    // +0x230
    bool m_b231;                                    // +0x231
    bool m_b232;                                    // +0x232
    bool m_b233;                                    // +0x233
    int m_i234;                                     // +0x234 floor contact (ground offset)
    int m_i238;                                     // +0x238 ceiling / wall contact flags
    int m_i23C;                                     // +0x23C
    int m_i240;                                     // +0x240
    bool m_b244;                                    // +0x244
    unsigned char _pad245[0x3];
    ShotProbeFunc m_pointTest;                      // +0x248 host point test (an OPD); first one set wins (IShot +0x458)
    ShotProbeFunc m_probe;                          // +0x24C host probe (an OPD from the original game); first one set wins
    int m_i250;                                     // +0x250
    ShotObjVec m_objsA;                             // +0x254
    ShotObjVec m_objsB;                             // +0x264
    ShotElem274Vec m_elems274;                      // +0x274
    int m_i284;                                     // +0x284
    void* m_ownerLink;                              // +0x288 guest pointer to the owner's data (a flag byte, a link record: module-specific)
    ShotHostFunc0 m_host28C;                        // +0x28C
    ShotHostFunc2 m_host290;                        // +0x290
    ShotHostFuncF m_host294;                        // +0x294
    int m_hostArg;                                  // +0x298 -1: no host calls
    bool m_b29C;                                    // +0x29C
    bool m_b29D;                                    // +0x29D
    unsigned char _pad29E[0x2];
    Vec2 m_v2A0;                                    // +0x2A0
    float m_f2A8;                                   // +0x2A8
    Vec2 m_v2AC;                                    // +0x2AC
    int m_i2B4;                                     // +0x2B4
    bool m_b2B8;                                    // +0x2B8
    unsigned char _pad2B9[0x3];
    Vec2 m_v2BC;                                    // +0x2BC
    bool m_b2C4;                                    // +0x2C4
    unsigned char _pad2C5[0x3];
    int m_i2C8;                                     // +0x2C8
    Vec2 m_v2CC;                                    // +0x2CC
    bool m_b2D4;                                    // +0x2D4
    bool m_b2D5;                                    // +0x2D5
    bool m_b2D6;                                    // +0x2D6
    bool m_b2D7;                                    // +0x2D7
    unsigned int m_mask6;                           // +0x2D8 masks by testMask() index: 6
    unsigned int m_mask0;                           // +0x2DC
    unsigned int m_mask1;                           // +0x2E0
    unsigned int m_mask7;                           // +0x2E4
    unsigned int m_mask8;                           // +0x2E8
    unsigned int m_mask2;                           // +0x2EC
    unsigned int m_mask3;                           // +0x2F0
    bool m_b2F4;                                    // +0x2F4
    bool m_b2F5;                                    // +0x2F5
    bool m_b2F6;                                    // +0x2F6
    unsigned char _pad2F7[0x1];
    int m_i2F8;                                     // +0x2F8
    bool m_b2FC;                                    // +0x2FC
    unsigned char _pad2FD[0x3];
    Vec2 m_v300;                                    // +0x300
    bool m_b308;                                    // +0x308
    unsigned char _pad309[0x3];
    Vec2 m_v30C;                                    // +0x30C
    bool m_b314;                                    // +0x314
    bool m_hostEnabled;                             // +0x315 host calls allowed (IShot +0x4DC / +0x4E0)
    unsigned char _pad316[0x2];
    // </layout:ShotBase>
};


}  // namespace dll

#ifndef CVHD_DLL_NO_SHOTBASE_ALIAS
using dll::ShotBase;
#endif
