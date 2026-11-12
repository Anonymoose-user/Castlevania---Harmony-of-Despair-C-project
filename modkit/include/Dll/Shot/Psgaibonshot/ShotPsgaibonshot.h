// Dll/Shot/Psgaibonshot/ShotPsgaibonshot.h - dllshotpsgaibonshot's shot class
// (vtable ): Gaibon's fireball ("PSギャイボン：ショット",
// ShotInfo name). Level 0: a small tilted fireball living 3 s. Higher levels:
// a big one that grows, cycles five frames every 0.1 s and fades out over its
// last 1.75 s (2 s life). It ends with a burst effect while still visible.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotPsgaibonshot : public ShotBase {
public:
    ShotPsgaibonshot();                          // (DllCreate inlines it)
    virtual ~ShotPsgaibonshot();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void vfunc04C();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual, unreferenced
    void end();
    void tickEnd(float dt);

public:
    int m_state;                                 // +0x318 0 flying, 1 ending
    int m_frame;                                 // +0x31C sprite frame (0..4)
    float m_time;                                // +0x320
    float m_life;                                // +0x324 3 s (small) or 2 s (big)
    float m_dir;                                 // +0x328 -1 facing left, 1 right
    float m_scale;                               // +0x32C big fireball's scale
    float m_alpha;                               // +0x330
    float m_frameTime;                           // +0x334
    bool m_big;                                  // +0x338 level > 0
};

