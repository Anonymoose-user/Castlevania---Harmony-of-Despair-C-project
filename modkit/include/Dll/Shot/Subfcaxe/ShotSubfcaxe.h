// Dll/Shot/Subfcaxe/ShotSubfcaxe.h - dllshotsubfcaxe's shot class (vtable
// ): the sub-weapon axe ("サブ　ＦＣ斧", ShotInfo
// name). Thrown in an arc (state 6, velocity by ShotBase::m_i284) until it
// ends after 10 s or on a hit, then plays a second object out and dies.
// The code is dllshotfcaxe's with the boomerang states left out. Names are
// inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSubfcaxe : public ShotBase {
public:
    ShotSubfcaxe();                              // (DllCreate inlines it)
    virtual ~ShotSubfcaxe();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual, unreferenced copies of parts of update() / vanish()
    void tickLifetime(float dt);
    bool takeHit();
    void end();

public:
    int m_state;                                 // +0x318 3 hit, 4 second object, 5 end, 6 flying
    float m_time;                                // +0x31C (only cleared)
    float m_life;                                // +0x320 seconds since start()
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_ending;                               // +0x328 vanish() asked for the end
    bool m_ended;                                // +0x329 end() ran
    unsigned char _pad32A[0x2];
};

