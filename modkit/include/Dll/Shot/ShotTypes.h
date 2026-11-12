// Dll/Shot/ShotTypes.h - the records a shot keeps in its lists (std::vector
// members of ShotBase that the original game reads through the IShot getters) and the
// small structs the interface passes. Names and field meanings are inferred;
// fields are named by their offset (original layout, sizes checked below).
// Unknown words are kept as int arrays: the library only copies them.
//
// The int arrays hold the values of the original's big-endian words (the test
// converts them word by word). A byte field inside such a word is the
// word's first byte on the original, i.e. the HIGH-order byte of the value: write
// it as w[k] = v << 24 (the other three bytes are padding the original never
// writes; the test does not compare them). Real bool members (b24, b38, ...)
// are plain bytes at their offsets.
#pragma once

#include "Dll/DllAllocator.h"
#include "System/MathTypes.h"

#include <stddef.h>
#include <vector>

// Host callbacks (plain function pointers, IShot +0x4C0..+0x4C8).
// Each also gets ShotBase::m_hostArg as its last argument.
typedef int (*ShotHostFunc0)(int arg);
typedef int (*ShotHostFunc2)(int a, int b, int arg);
typedef float (*ShotHostFuncF)(float a, float b, int arg);
// Probe the original game registers once (IShot +0x45C): a query at an integer
// position (e.g. a collision lookup), no extra argument.
typedef int (*ShotProbeFunc)(int x, int y);

struct ShotInfo {                // IShot +0x068 fills one (0x20 bytes)
    int i00;
    int i04;
    unsigned int u08;
    float f0C;
    union {
        float f10;               // +0x10 a float in most modules (3.0f, 0.2f, 1.0f)
        int i10;                 // the same bits, as the first modules wrote it
    };
    bool b14;
    int i18;
    const char* name;            // +0x1C UTF-8 display name
};

struct ShotBlockD4 {             // ShotBase +0x0D4 (IShot +0x3E0 returns its address)
    float f00, f04, f08, f0C;
    float f10;                   // -1 after construction
    int i14;
    bool b18;
};

struct ShotPoint {               // 12 bytes: ShotBase +0x104 / +0x114 / +0x124
    int id;
    Vec2 pos;
};

struct ShotNamedPoint {          // ShotBase +0x124: a sound by name (pointer-sized natively)
    const char* name;
    Vec2 pos;
};

struct ShotElem24 {                              // +0x0C0 (0x24): a sprite
    const char* tex;                             // texture name, e.g. "dchd_notex"
    int w[8];
};
struct ShotElem144 {                             // +0x144 (0x28)
    Vec2 pos;
    int w08[7];
    bool b24;                                    // set with pos (IShot +0x484)
    bool b25;
};
struct ShotElem154 {                             // +0x154 (0x38)
    Vec2 a;
    Vec2 b;
    int w10[9];
    bool b34;                                    // set with a/b (IShot +0x48C)
    bool b35;
};
struct ShotElem164 {                             // +0x164 (0x3C)
    Vec2 pos;
    int i08;
    int i0C;
    int i10;
    int i14;
    int w18[5];
    float f2C;
    int w30[2];
    bool b38;                                    // set by IShot +0x494
    bool b39;                                    // set by IShot +0x498
    bool b3A;
};
struct ShotElem174 {                             // +0x174 (0x38)
    Vec2 pos;
    int i08;
    int i0C;
    int i10;
    int i14;
    int w18[5];
    float f2C;
    int i30;
    bool b34;                                    // set by IShot +0x4A0
    bool b35;                                    // set by IShot +0x4A4
    bool b36;                                    // +0x37 padding (never written)
};
struct ShotElem184 {                             // +0x184 (0x64)
    int w[24];                                   // +0x34 is a byte field (w[13] >> 24; see
                                                 // above), +0x35..+0x37 padding
    bool b60;                                    // set by IShot +0x4AC
    bool b61;
};
struct ShotElem194 { int w[17]; };               // +0x194 (0x44)
struct ShotElem1A4 {                             // +0x1A4 (0x58)
    int w[21];                                   // +0x04, +0x3C, +0x48 are byte fields
                                                 // (w[1], w[15], w[18] >> 24; see above)
    bool b54;
};
struct ShotElem1B4 { int w[9]; };                // +0x1B4 (0x24), read back in order
struct ShotElem1C8 { int w[8]; };                // +0x1C8 (0x20), read back in order
struct ShotElem1DC { int w[13]; };               // +0x1DC (0x34), read back in order
struct ShotElem274 {                             // +0x274 (0x3C); +0x30 is a byte field
    int w[15];
    // Word 7's address (setLink), as a real pointer natively; the host reads
    // it as DllShotSpawn::link.
    const void* link = nullptr;
    void setLink(const void* p) { link = p; w[7] = p != nullptr; }
};
static_assert(sizeof(ShotElem274) == 0x48, "ShotElem274 matches the host's DllShotSpawn natively");
                                                 // (w[12] >> 24; see above); w[7] can hold an
                                                 // address (soulfcbat / soulfcghost: the
                                                 // lead's +0x371); the test compares it for
                                                 // nullness only

struct ShotObjSub { int w[4]; };

// IShot +0x03C fills a vertex buffer (0x3A8 bytes: 18 of these) using a
// 16-byte aligned 4x4 matrix.
struct ShotVertex { float f[13]; };              // 0x34
struct ShotMatrix4 {
    alignas(16) float m[16];
};                 // element of ShotObj::subs (0x10)

typedef std::vector<ShotObjSub, DllAllocator<ShotObjSub> > ShotObjSubVec;

// One entry of the two object lists (ShotBase +0x254 and +0x264, 0x84 bytes).
// Defaults: the temporary IShot +0x2D4 / +0x2D8 push.
struct ShotObj {
    int i00;
    int i04;
    int i08;
    int i0C;
    float f10;
    float f14;
    int i18;
    bool b1C, b1D, b1E, b1F;
    int i20;
    int i24;
    bool b28, b29, b2A, b2B, b2C;
    int i30;
    int i34;
    float f38;
    float f3C;
    Vec2 v40;
    Vec2 v48;
    float f50;
    float f54;
    int i58;
    unsigned short h5C;
    unsigned short h5E;
    float f60;
    bool b64, b65, b66;
    unsigned short h68;
    ShotObjSubVec subs;          // +0x6C
    int i7C;
    int i80;

    ~ShotObj();                  // (frees subs)
};

typedef std::vector<int, DllAllocator<int> > ShotIntVec;
typedef std::vector<ShotPoint, DllAllocator<ShotPoint> > ShotPointVec;
typedef std::vector<ShotNamedPoint, DllAllocator<ShotNamedPoint> > ShotNamedPointVec;
typedef std::vector<ShotElem24, DllAllocator<ShotElem24> > ShotElem24Vec;
typedef std::vector<ShotElem144, DllAllocator<ShotElem144> > ShotElem144Vec;
typedef std::vector<ShotElem154, DllAllocator<ShotElem154> > ShotElem154Vec;
typedef std::vector<ShotElem164, DllAllocator<ShotElem164> > ShotElem164Vec;
typedef std::vector<ShotElem174, DllAllocator<ShotElem174> > ShotElem174Vec;
typedef std::vector<ShotElem184, DllAllocator<ShotElem184> > ShotElem184Vec;
typedef std::vector<ShotElem194, DllAllocator<ShotElem194> > ShotElem194Vec;
typedef std::vector<ShotElem1A4, DllAllocator<ShotElem1A4> > ShotElem1A4Vec;
typedef std::vector<ShotElem1B4, DllAllocator<ShotElem1B4> > ShotElem1B4Vec;
typedef std::vector<ShotElem1C8, DllAllocator<ShotElem1C8> > ShotElem1C8Vec;
typedef std::vector<ShotElem1DC, DllAllocator<ShotElem1DC> > ShotElem1DCVec;
typedef std::vector<ShotElem274, DllAllocator<ShotElem274> > ShotElem274Vec;
typedef std::vector<ShotObj, DllAllocator<ShotObj> > ShotObjVec;

