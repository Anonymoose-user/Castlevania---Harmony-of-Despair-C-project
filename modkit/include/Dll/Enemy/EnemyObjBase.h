// Dll/Enemy/EnemyObjBase.h - base class every enemy-family module links
// (dllfcskl, 310 slots; 0x44C0 bytes, the module's own
// members follow). It implements every IEnemyObj slot (most are plain
// accessors the original game uses to read and write the object's state) and adds
// release() (+0x4D0, pure) and setV0D4() (+0x4D4). The module class supplies
// init/update and the other slots EnemySlots.inc lists as overridden.
//
// The object is mostly a mailbox between the module and the original game: the module
// pushes requests (shots to spawn, motions to play, hit boxes, effects) into
// the vectors below and the original game drains them through the accessor slots.
//
// Names are inferred (most after their offset); member offsets are generated
// from the  layout dump by
// the decompilation project. The element types' fields are only named where
// the library or dllfcskl reads or writes them; the rest are copied as words.
#pragma once

#include "Dll/Enemy/EnemyInterface.h"

#include <stddef.h>
#include <stdint.h>

// --- vector elements ----------------------------------------------------------

struct EnemyIdPos {              // 0x0C, lists +0x0DC / +0x0EC
    int id;
    EnemyVec2 pos;
    EnemyIdPos() {}
    EnemyIdPos(int i, const EnemyVec2& p) : id(i), pos(p) {}
};

struct EnemyNamedPos {           // 0x0C, list +0x0FC: an effect by name at pos
    const char* name;            // e.g. "VX_EN_FC_DRACULA_LAND"
    EnemyVec2 pos;
    EnemyNamedPos() {}
    EnemyNamedPos(const char* n, const EnemyVec2& p) : name(n), pos(p) {}
};

struct EnemyReq28 {              // 0x28, list +0x11C
    EnemyVec2 pos;               // +0x00
    int w08[7];                  // +0x08
    bool active;                 // +0x24
    bool b25;                    // +0x25
};

struct EnemyReq38 {              // 0x38, list +0x12C
    EnemyVec2 a;                 // +0x00
    EnemyVec2 b;                 // +0x08
    int w10[9];                  // +0x10
    bool active;                 // +0x34
    bool b35;                    // +0x35
    bool b36;                    // +0x36
};

struct EnemyReq3C {              // 0x3C, list +0x13C
    EnemyVec2 pos;               // +0x00
    int w08;                     // +0x08
    int i0C;                     // +0x0C
    int w10;                     // +0x10
    int i14;                     // +0x14
    int w18[8];                  // +0x18
    bool active;                 // +0x38
    bool b39;                    // +0x39
    bool b3A;                    // +0x3A
};

struct EnemyReq38b {             // 0x38, list +0x14C
    EnemyVec2 pos;               // +0x00
    int w08;                     // +0x08
    int i0C;                     // +0x0C
    int w10;                     // +0x10
    int i14;                     // +0x14
    int w18[7];                  // +0x18
    bool active;                 // +0x34
    bool b35;                    // +0x35
};

// The next three have single bytes inside the word arrays (the rest of those
// words is left unset by the original: stack garbage). The unions keep the
// word view and name the bytes.
struct EnemyReq64 {              // 0x64, list +0x15C
    union {
        int w00[24];             // +0x00
        struct {
            int w00_[13];
            bool b34;            // +0x34
            unsigned char x35_[3];
        };
    };
    bool b60;                    // +0x60
    bool b61;                    // +0x61
};

struct EnemyReq44 {              // 0x44, list +0x16C
    union {
        int w[17];
        struct {
            int w00_;
            bool b04;            // +0x04
            unsigned char x05_[3];
        };
    };
};

struct EnemyReq58 {              // 0x58, list +0x17C
    union {
        int w[21];
        struct {
            int w00_;
            bool b04;            // +0x04
            unsigned char x05_[3];
            int w08_[13];
            bool b3C;            // +0x3C
            unsigned char x3D_[3];
            int w40_[2];
            bool b48;            // +0x48
            unsigned char x49_[3];
        };
    };
    bool b54;                    // +0x54
};
struct EnemyReq24 { int w[9]; };     // 0x24, queue +0x18C (slot +0x1A4)
struct EnemyReq20 { int w[8]; };     // 0x20, queue +0x1A0 (slot +0x1A8)
struct EnemyReq34 { int w[13]; };    // 0x34, queue +0x1B4 (slot +0x1AC)

// 0x3C, list +0x1C8 (slot +0x058): a shot the original game spawns for the module.
// The defaults are the ones every dllfcskl request starts from.
struct EnemyShotReq {
    float x, y;                  // +0x00
    float vx, vy;                // +0x08
    int i10;                     // +0x10 8
    int i14;                     // +0x14 24
    int i18;                     // +0x18
    const void* p1C;             // +0x1C the address of a module member (dllfcaxe, dllregion, ...)
    int i20;                     // +0x20
    float f24;                   // +0x24 1
    unsigned int shotId;         // +0x28 0x40000042
    float f2C;                   // +0x2C 5
    bool b30;                    // +0x30 true
    float f34;                   // +0x34 -1
    int i38;                     // +0x38 -1
    EnemyShotReq()
        : x(0), y(0), vx(0), vy(0), i10(8), i14(24), i18(0), p1C(0), i20(0), f24(1.0f),
          shotId(0x40000042), f2C(5.0f), b30(true), f34(-1.0f), i38(-1) {}
};

struct EnemyRect {               // 0x10, EnemyHitBox::rects
    float x0, y0, x1, y1;
};

// 0x84, lists +0x2B4 / +0x2C4 (slots +0x2B4..+0x48C).
struct EnemyHitBox {
    unsigned int u00;            // +0x00
    unsigned int u04;            // +0x04
    unsigned int u08;            // +0x08
    unsigned int u0C;            // +0x0C -1
    float f10;                   // +0x10 1
    float f14;                   // +0x14 25000
    unsigned int u18;            // +0x18 3
    bool b1C;                    // +0x1C
    bool b1D;                    // +0x1D
    bool b1E;                    // +0x1E
    bool b1F;                    // +0x1F
    int i20;                     // +0x20
    int i24;                     // +0x24
    bool b28;                    // +0x28
    bool b29;                    // +0x29 true
    bool b2A;                    // +0x2A true
    bool b2B;                    // +0x2B
    bool b2C;                    // +0x2C true
    int i30;                     // +0x30
    int i34;                     // +0x34
    EnemyVec2 scale;             // +0x38 (1, 1)
    EnemyVec2 v40;               // +0x40
    EnemyVec2 v48;               // +0x48
    float f50;                   // +0x50
    float f54;                   // +0x54
    unsigned int u58;            // +0x58
    unsigned short s5C;          // +0x5C
    unsigned short s5E;          // +0x5E
    unsigned int u60;            // +0x60
    bool b64;                    // +0x64
    bool b65;                    // +0x65
    bool b66;                    // +0x66
    unsigned short s68;          // +0x68 0xFFFF
    EnemyRectList rects;         // +0x6C
    unsigned int u7C;            // +0x7C
    unsigned int u80;            // +0x80

    EnemyHitBox(unsigned int a00, bool a2B, unsigned int a58);
    ~EnemyHitBox();
    EnemyHitBox& operator=(const EnemyHitBox& o) { return assign(o); }
    EnemyHitBox& assign(const EnemyHitBox& o);      // the copy assignment operator
};

struct EnemyEffectReq {          // 0x24, list +0x2D4 (slot +0x060)
    int a;                       // +0x00
    int b;                       // +0x04
    EnemyVec2 pos;               // +0x08
    float f10;                   // +0x10
    bool b14;                    // +0x14
    float f18;                   // +0x18
    int i1C;                     // +0x1C
    bool b20;                    // +0x20
};

// 0x40, 16 per EnemyPartRow. Constructor zeroes +0x18..+0x2C.
struct EnemyPart {
    int w00, w04, w08;           // +0x00
    float f0C;                   // +0x0C
    int w10, w14;                // +0x10
    EnemyVec2 a;                 // +0x18
    int w20, w24;                // +0x20
    EnemyVec2 b;                 // +0x28 (position = a + b)
    int w30;                     // +0x30
    int i34;                     // +0x34
    float f38;                   // +0x38
    bool b3C;                    // +0x3C true in bank 1 after construction
    EnemyPart();
};

// 0x410; the object holds 16 (two banks of 8). Constructor.
struct EnemyPartRow {
    bool active;                 // +0x000
    int id;                      // +0x004
    int w008;                    // +0x008
    EnemyPart parts[16];         // +0x00C
    int count;                   // +0x40C parts in use
    EnemyPartRow();
};

// 0x34: the current motion (+0x442C, set with setMotion) and the queued ones
// (+0x441C, queueMotion).
struct EnemyMotion {
    int i00;                     // +0x00 -1
    int id;                      // +0x04
    bool loop;                   // +0x08
    int i0C;                     // +0x0C
    int i10;                     // +0x10
    float f14;                   // +0x14 EnemyObjBase::m_f1EC when set
    float f18;                   // +0x18 EnemyObjBase::m_f1E8 when set
    bool b1C;                    // +0x1C
    bool b1D;                    // +0x1D
    int i20;                     // +0x20
    int i24;                     // +0x24
    bool b28;                    // +0x28
    int i2C;                     // +0x2C
    bool b30;                    // +0x30
    bool b31;                    // +0x31
};

struct EnemyLabel {              // 0x10, list +0x4488; copied as 15 bytes
    int id;                      // +0x00 -1: none
    EnemyVec2 pos;               // +0x04
    bool b0C, b0D;               // +0x0C
    uint8_t b0E;                 // +0x0E stage area id (compared with m_b21F)
    EnemyLabel() : id(-1) { pos.x = 0; pos.y = 0; b0C = false; b0D = false; b0E = false; }
};

// --- the base class -----------------------------------------------------------

class EnemyObjBase : public IEnemyObj {
public:
    EnemyObjBase();
    virtual ~EnemyObjBase();

#define ENEMY_DECL_1(ret, name, params) virtual ret name params;
#define ENEMY_DECL_0(ret, name, params)
#define ENEMY_SLOT(off, ret, name, params, base) ENEMY_DECL_##base(ret, name, params)
#define ENEMY_PURE_1(ret, name, params) virtual ret name params;
#define ENEMY_PURE_0(ret, name, params) virtual ret name params = 0;
#define ENEMY_SLOT_BASE(off, ret, name, params, base) ENEMY_PURE_##base(ret, name, params)
#include "Dll/Enemy/EnemySlots.inc"
#undef ENEMY_SLOT
#undef ENEMY_SLOT_BASE
#undef ENEMY_DECL_0
#undef ENEMY_DECL_1
#undef ENEMY_PURE_0
#undef ENEMY_PURE_1

    // non-virtual helpers (the modules call them directly)
    void pushShotReq(const EnemyShotReq& r);
    // Native: the difficulty being played (0 Normal, 1 Hard, 2+ a mod level
    // such as Expert or Hell) and its enemy HP / ATK+INT / DEF+MND factors,
    // asked of the game (Port/DifficultyLevels.h). Stats the host gives the
    // module are already scaled; a module setting its own stats applies them.
    static int  difficultyLevel();
    static void difficultyFactors(float* hp, float* atk, float* def);
    void pushFC(const char* name, const EnemyVec2* pos);
    void pushIdPos(int id, const EnemyVec2* pos, bool toDC);
    void push10C(int v);
    void pushQueue24(const EnemyReq24& r);
    void pushQueue20(const EnemyReq20& r);
    void pushQueue34(const EnemyReq34& r);
    unsigned int push11C(const EnemyReq28& r);
    void set11C(int i, const EnemyVec2* pos);
    unsigned int push12C(const EnemyReq38& r);
    void set12C(int i, const EnemyVec2* a, const EnemyVec2* b);
    unsigned int push13C(const EnemyReq3C& r);
    void set13C(int i, const EnemyVec2* pos, int i0C, int i14);
    void mark13C(int i);
    unsigned int push14C(const EnemyReq38b& r);
    void set14C(int i, const EnemyVec2* pos, int i0C, int i14);
    void mark14C(int i);
    unsigned int push15C(const EnemyReq64& r);
    void mark15C(int i);
    void push16C(const EnemyReq44& r);
    void push17C(const EnemyReq58& r);
    void setMotion(int id, bool loop);
    int queueMotion(int id, bool loop);
    void setPartF0C(float v, int part, int rowId, bool bank1);
    void setPartI34(int v, int part, int rowId, bool bank1);
    void setPartF38(float v, int part, int rowId, bool bank1);
    bool getPartPos(EnemyVec2* out, int part, int rowId, bool bank1);
    void pushEffectReq(int a, int b, const EnemyVec2* pos, float f10, bool b14, float f18,
                       int i1C, bool b20);
    int query();
    int randInt(int lo, int hi);
    float randFloat(float lo, float hi);
    float distance(const EnemyVec2* a, const EnemyVec2* b);
    bool normalize(EnemyVec2* v);
    static float wrapAngle(float a);
    static float approachAngle(float from, float to, float step);
    int callHost4474(const char* name, const EnemyVec2* pos, int ctx, int* outId);
    int callHost4478(EnemyVec2* out, int handle);
    bool findLabel(EnemyLabel* out, int id);
    int labelCount();
    unsigned int labelId(unsigned int i);
    bool hasLabel(int id);
    bool getLabelPos(EnemyVec2* out, int id);
    bool getLabelB0C(int id);
    bool getLabelB0D(int id);
    uint8_t getLabelB0E(int id);
    float callHost449C(const EnemyVec2* from, const EnemyVec2* dir);
    void packPos(unsigned int* out, const EnemyVec2* p);
    void unpackPos(EnemyVec2* out, const unsigned int* in);
    void setFlags(int set, unsigned int mask, bool on);
    void setFlagSet(int set, unsigned int v);
    unsigned int getFlagSet(int set);
    // small helpers emitted in the module's own unit (inline in the original
    // header, shared by 5..14 modules)
    void clearB268();
    void clearB26AB();
    void clearB269();
    void setMotionB1C(bool off);                                // (stores !off)

protected:
    void reset();                // inlined in the constructor and destructor

public:
    // <layout:EnemyObjBase>
    int m_i004;                                     // +0x004 slot +0x104 returns its address
    int m_i008;                                     // +0x008
    int m_i00C;                                     // +0x00C
    int m_i010;                                     // +0x010
    float m_f014;                                   // +0x014 -1 after construction
    int m_i018;                                     // +0x018
    bool m_b01C;                                    // +0x01C
    unsigned char _pad01D[0x3];
    EnemyVec2 m_v020;                               // +0x020 slot +0x100
    EnemyVec2 m_v028;                               // +0x028 slot +0x100
    bool m_b030;                                    // +0x030 set by slot +0x100
    unsigned char _pad031[0x3];
    int m_i034;                                     // +0x034 slot +0x05C takes it (sets -1)
    const char* m_name;                             // +0x038 module name ("DLL_FCskl"), set by the module constructor
    unsigned char _pad03C[0x1];
    bool m_b03D;                                    // +0x03D
    bool m_b03E;                                    // +0x03E
    bool m_b03F;                                    // +0x03F
    bool m_b040;                                    // +0x040
    bool m_b041;                                    // +0x041
    bool m_b042;                                    // +0x042
    bool m_b043;                                    // +0x043 checked by the dllfcskl states
    bool m_b044;                                    // +0x044
    unsigned char _pad045[0x3];
    EnemyPointQueryFunc m_query048;                 // +0x048 map query (set once, slot +0x1B4; dllfuhannya, dllfuhiguruma: room)
    EnemyPointQueryFunc m_query04C;                 // +0x04C map query (set once, slot +0x1B8; dllpsbeel: room)
    EnemyPointQueryFunc m_i050;                                  // +0x050 set once (slot +0x1BC)
    EnemyPointQueryFunc m_i054;                                  // +0x054 set once (slot +0x1C0)
    EnemyPointQueryFunc m_query058;                 // +0x058 map query (set once, slot +0x1C4; dllpsbeel: floor)
    EnemyPointQueryFunc m_query05C;                 // +0x05C map query (set once, slot +0x1C8; dllfuhiguruma: ground)
    int m_i060;                                     // +0x060
    bool m_b064;                                    // +0x064
    unsigned char _pad065[0x3];
    int m_i068[5];                                  // +0x068
    bool m_b07C;                                    // +0x07C
    unsigned char _pad07D[0x3];
    int m_i080[6];                                  // +0x080
    float m_f098;                                   // +0x098
    float m_playerPos[2];                           // +0x09C the player's position (x, y), slots +0x1F8 / +0x210
    float m_selfPos[2];                             // +0x0A4 the object's own position (x, y), slots +0x1EC / +0x204
    float m_vel[2];                                 // +0x0AC velocity (x, y), slots +0x1F0 / +0x208
    float m_f0B4[2];                                // +0x0B4
    float m_f0BC[2];                                // +0x0BC
    float m_f0C4[2];                                // +0x0C4
    int m_i0CC;                                     // +0x0CC
    int m_i0D0;                                     // +0x0D0
    EnemyVec2 m_v0D4;                               // +0x0D4 slots +0x4D4 / +0x29C
    EnemyIdPosList m_listDC;                        // +0x0DC
    EnemyIdPosList m_listEC;                        // +0x0EC
    EnemyNamedPosList m_listFC;                     // +0x0FC
    EnemyIntList m_list10C;                         // +0x10C
    EnemyReq28List m_list11C;                       // +0x11C
    EnemyReq38List m_list12C;                       // +0x12C
    EnemyReq3CList m_list13C;                       // +0x13C
    EnemyReq38bList m_list14C;                      // +0x14C
    EnemyReq64List m_list15C;                       // +0x15C
    EnemyReq44List m_list16C;                       // +0x16C
    EnemyReq58List m_list17C;                       // +0x17C
    EnemyReq24List m_queue24;                       // +0x18C read with slot +0x1A4
    unsigned int m_queue24Pos;                      // +0x19C
    EnemyReq20List m_queue20;                       // +0x1A0 read with slot +0x1A8
    unsigned int m_queue20Pos;                      // +0x1B0
    EnemyReq34List m_queue34;                       // +0x1B4 read with slot +0x1AC
    unsigned int m_queue34Pos;                      // +0x1C4
    EnemyShotReqList m_shotReqs;                    // +0x1C8 shots to spawn, slot +0x058
    int m_i1D8;                                     // +0x1D8
    unsigned int m_u1DC;                            // +0x1DC
    float m_f1E0;                                   // +0x1E0
    bool m_b1E4;                                    // +0x1E4 true after construction
    unsigned char _pad1E5[0x3];
    float m_f1E8;                                   // +0x1E8
    float m_f1EC;                                   // +0x1EC
    float m_f1F0;                                   // +0x1F0
    float m_f1F4;                                   // +0x1F4
    float m_f1F8;                                   // +0x1F8
    float m_f1FC;                                   // +0x1FC
    float m_f200;                                   // +0x200
    float m_f204;                                   // +0x204
    EnemyShortSet m_shortSet;                       // +0x208 slots +0x24C / +0x27C
    bool m_b21E;                                    // +0x21E
    uint8_t m_b21F;                                 // +0x21F
    uint8_t m_b220;                                 // +0x220
    uint8_t m_b221;                                 // +0x221
    unsigned short m_s222;                          // +0x222
    int m_i224;                                     // +0x224
    bool m_b228;                                    // +0x228
    bool m_b229;                                    // +0x229
    unsigned char _pad22A[0x2];
    float m_f22C;                                   // +0x22C
    bool m_b230;                                    // +0x230
    bool m_b231;                                    // +0x231
    bool m_b232;                                    // +0x232
    unsigned char _pad233[0x1];
    float m_f234;                                   // +0x234 1 after construction
    float m_f238[2];                                // +0x238 slot +0x0E0 / +0x0F0
    float m_f240[2];                                // +0x240
    float m_f248[2];                                // +0x248
    float m_f250[2];                                // +0x250
    int m_i258;                                     // +0x258
    int m_i25C;                                     // +0x25C
    int m_i260;                                     // +0x260
    int m_i264;                                     // +0x264
    bool m_b268;                                    // +0x268
    bool m_b269;                                    // +0x269
    bool m_b26A;                                    // +0x26A
    bool m_b26B;                                    // +0x26B
    float m_f26C[2];                                // +0x26C
    unsigned char m_flags274;                       // +0x274 flag byte (slot +0x0B4; dllfcfishman tests bit 3)
    bool m_b275;                                    // +0x275
    unsigned char _pad276[0x2];
    int m_i278;                                     // +0x278
    int m_i27C;                                     // +0x27C
    EnemyVec2 m_v280;                               // +0x280 slot +0x108 hands it out and clears m_has280
    EnemyVec2 m_v288;                               // +0x288
    EnemyVec2 m_v290;                               // +0x290
    unsigned short m_s298;                          // +0x298
    unsigned char _pad29A[0x2];
    int m_rect29C[4];                               // +0x29C slot +0x128
    bool m_has280;                                  // +0x2AC
    bool m_has288;                                  // +0x2AD
    bool m_has290;                                  // +0x2AE
    bool m_has298;                                  // +0x2AF
    bool m_hasRect29C;                              // +0x2B0
    bool m_b2B1;                                    // +0x2B1
    bool m_b2B2;                                    // +0x2B2
    unsigned char _pad2B3[0x1];
    EnemyHitBoxList m_hitBoxes0;                    // +0x2B4
    EnemyHitBoxList m_hitBoxes1;                    // +0x2C4
    EnemyEffectReqList m_effectReqs;                // +0x2D4 slot +0x060
    EnemyPartRow m_partRows[16];                    // +0x2E4 two banks of 8 rows, slot +0x064
    EnemyPartRow* m_partBank0;                      // +0x43E4 &m_partRows[0]
    EnemyPartRow* m_partBank1;                      // +0x43E8 &m_partRows[8]
    float m_f43EC;                                  // +0x43EC 100 after construction
    EnemyQueryFunc m_queryFunc;                     // +0x43F0
    EnemyRandIntFunc m_randIntFunc;                 // +0x43F4
    EnemyRandFloatFunc m_randFloatFunc;             // +0x43F8
    int m_hostContext;                              // +0x43FC -1 until set; the three callbacks above are only called once it is set
    const void* m_msgAddr;                          // +0x4400 the module's sync message (set in init when +0x440A), slot +0x154
    int m_i4404;                                    // +0x4404
    bool m_b4408;                                   // +0x4408
    bool m_b4409;                                   // +0x4409
    bool m_b440A;                                   // +0x440A
    bool m_b440B;                                   // +0x440B
    unsigned short m_s440C;                         // +0x440C
    bool m_b440E;                                   // +0x440E
    unsigned char _pad440F[0x1];
    EnemyVec2 m_v4410;                              // +0x4410
    bool m_motionChanged;                           // +0x4418
    unsigned char _pad4419[0x3];
    EnemyMotionList m_motionQueue;                  // +0x441C
    EnemyMotion m_motion;                           // +0x442C
    bool m_has4464;                                 // +0x4460
    unsigned char _pad4461[0x3];
    EnemyVec2 m_v4464;                              // +0x4464
    EnemyVec2 m_v446C;                              // +0x446C
    EnemyHostFunc4 m_hostFunc4474;                  // +0x4474
    EnemyHostFunc2 m_hostFunc4478;                  // +0x4478
    unsigned int m_u447C;                           // +0x447C -1 after construction
    uintptr_t    m_u4480;                           // +0x4480
    bool m_b4484;                                   // +0x4484
    unsigned char _pad4485[0x3];
    EnemyLabelList m_labels;                        // +0x4488
    float m_f4498;                                  // +0x4498
    EnemyHostFuncF m_hostFunc449C;                  // +0x449C
    unsigned int m_flags4;                          // +0x44A0 flag set 4 (testFlags / setFlagSet index 4)
    unsigned int m_flags0;                          // +0x44A4
    unsigned int m_flags1;                          // +0x44A8
    unsigned int m_flags2;                          // +0x44AC
    unsigned int m_flags3;                          // +0x44B0
    unsigned int m_flags5;                          // +0x44B4
    bool m_b44B8;                                   // +0x44B8
    bool m_b44B9;                                   // +0x44B9
    unsigned char _pad44BA[0x2];
    int m_i44BC;                                    // +0x44BC -1 after construction
    // </layout:EnemyObjBase>
};

