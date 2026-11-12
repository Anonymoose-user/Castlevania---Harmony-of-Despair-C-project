// Dll/Shot/Psberriganshot/ShotPsberriganshot.h - dllshotpsberriganshot's shot
// class (vtable ): Berrigan's shot ("PSベリガン：ショット",
// ShotInfo name). It flies straight ahead at 400 px/s and, after 300 s or on
// any hit/vanish hook, spawns its burst effect, a point and kills itself.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotPsberriganshot : public ShotBase {
public:
    ShotPsberriganshot();                        // (DllCreate inlines it)
    virtual ~ShotPsberriganshot();

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
    float m_time;                                // +0x31C
    float m_dir;                                 // +0x320 -1 facing left, 1 right
};

