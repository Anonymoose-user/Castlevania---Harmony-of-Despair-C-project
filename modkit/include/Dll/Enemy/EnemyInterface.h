// Dll/Enemy/EnemyInterface.h - the interface the original game drives an enemy-family
// module through (dllfcskl, 308 slots, all pure). The
// family: the 43 modules dllfc*, dllfu*, dllps*, dllregion, dllryukotsu,
// dllskeleton. Each module's factory returns one of these.
//
// Unlike the player interface it does not derive from DllObject: there is no
// release() at +0x008; EnemyObjBase declares it at +0x4D0 instead (slot
// +0x02C destroy() of the modules calls it). Names are inferred; the slot
// list lives in EnemySlots.inc.
#pragma once

#include "Dll/DllAllocator.h"
#include "Dll/DllRuntime.h"

#include <vector>

struct EnemyVec2 {
    float x, y;
};

// 11 halfwords at EnemyObjBase +0x208, passed and returned by value (slots
// +0x24C / +0x27C).
struct EnemyShortSet {
    unsigned short s[11];
};

// Host callbacks (plain function pointers). The context
// value set with slot +0x07C is passed as the last argument of the first three.
typedef int (*EnemyQueryFunc)(int ctx);                         // +0x43F0
typedef int (*EnemyRandIntFunc)(int lo, int hi, int ctx);       // +0x43F4
typedef float (*EnemyRandFloatFunc)(float lo, float hi, int ctx); // +0x43F8
// spawns another module's object by name at pos (outId receives its id; 0 on
// success) - dllfcnomi, dllfukyokotsu, dllfuryukibi, dllpsfishh
typedef int (*EnemyHostFunc4)(const char* name, const EnemyVec2* pos, int ctx, int* outId); // +0x4474
typedef int (*EnemyHostFunc2)(EnemyVec2* out, int handle);                    // +0x4478
// casts a ray from `from` along `dir` (dllpskillerf, dllfcfranc)
typedef float (*EnemyHostFuncF)(const EnemyVec2* from, const EnemyVec2* dir);  // +0x449C
// map queries at a point (room / floor / ground; dllfuhannya, dllfuhiguruma,
// dllpsbeel): +0x048, +0x04C, +0x058, +0x05C
typedef int (*EnemyPointQueryFunc)(int x, int y);

struct EnemyIdPos;
struct EnemyNamedPos;
struct EnemyReq28;
struct EnemyReq38;
struct EnemyReq3C;
struct EnemyReq38b;
struct EnemyReq64;
struct EnemyReq44;
struct EnemyReq58;
struct EnemyReq24;
struct EnemyReq20;
struct EnemyReq34;
struct EnemyShotReq;
struct EnemyRect;
struct EnemyHitBox;
struct EnemyEffectReq;
struct EnemyPartRow;
struct EnemyMotion;
struct EnemyLabel;

#define ENEMY_LIST(T) std::vector<T, DllAllocator<T> >
typedef ENEMY_LIST(EnemyIdPos) EnemyIdPosList;
typedef ENEMY_LIST(EnemyNamedPos) EnemyNamedPosList;
typedef ENEMY_LIST(int) EnemyIntList;
typedef ENEMY_LIST(EnemyReq28) EnemyReq28List;
typedef ENEMY_LIST(EnemyReq38) EnemyReq38List;
typedef ENEMY_LIST(EnemyReq3C) EnemyReq3CList;
typedef ENEMY_LIST(EnemyReq38b) EnemyReq38bList;
typedef ENEMY_LIST(EnemyReq64) EnemyReq64List;
typedef ENEMY_LIST(EnemyReq44) EnemyReq44List;
typedef ENEMY_LIST(EnemyReq58) EnemyReq58List;
typedef ENEMY_LIST(EnemyReq24) EnemyReq24List;
typedef ENEMY_LIST(EnemyReq20) EnemyReq20List;
typedef ENEMY_LIST(EnemyReq34) EnemyReq34List;
typedef ENEMY_LIST(EnemyShotReq) EnemyShotReqList;
typedef ENEMY_LIST(EnemyRect) EnemyRectList;
typedef ENEMY_LIST(EnemyHitBox) EnemyHitBoxList;
typedef ENEMY_LIST(EnemyEffectReq) EnemyEffectReqList;
typedef ENEMY_LIST(EnemyMotion) EnemyMotionList;
typedef ENEMY_LIST(EnemyLabel) EnemyLabelList;

class IEnemyObj {
public:
    virtual ~IEnemyObj();
#define ENEMY_SLOT(off, ret, name, params, base) virtual ret name params = 0;
#define ENEMY_SLOT_BASE(off, ret, name, params, base)
#include "Dll/Enemy/EnemySlots.inc"
#undef ENEMY_SLOT
#undef ENEMY_SLOT_BASE
};
