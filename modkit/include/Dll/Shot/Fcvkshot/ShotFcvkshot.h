// Dll/Shot/Fcvkshot/ShotFcvkshot.h - dllshotfcvkshot's shot class (vtable
// ): the Vampire Killer whip shot
// ("FCヴァンパイアキラーショット", ShotInfo name). It flies at 150 px/s in its
// launch direction (or ahead of the owner), shows two sprites and after one
// second (or any hit/vanish hook) plays its end animation, then dies.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFcvkshot : public ShotBase {
public:
    ShotFcvkshot();                              // (DllCreate inlines it)
    virtual ~ShotFcvkshot();

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

    // non-virtual, unreferenced copies of the update logic
    void end();
    void tickEnd(float dt);
    bool takeEnd();

public:
    int m_state;                                 // +0x318 0 flying, 1 end requested, 2 end animation, 3 done
    int m_i31C;                                  // +0x31C cleared, never read
    float m_time;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endPending;                           // +0x328 set by end(), taken by update()
    bool m_ended;                                // +0x329 end() ran once
};

