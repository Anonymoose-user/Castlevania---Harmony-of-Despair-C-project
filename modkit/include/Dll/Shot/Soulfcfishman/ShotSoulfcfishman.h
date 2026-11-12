// Dll/Shot/Soulfcfishman/ShotSoulfcfishman.h - dllshotsoulfcfishman's shot
// class (vtable ): the FC Fishman soul (ShotInfo name
// "Soul L.Hangyojin" in Japanese). Two modes: standing (the owner's spell,
// getI284() == 0 / no getB314()), it spits a spread of fireballs (ShotElem274
// records) and leaves after 1 s; flying (getB314() with a sender), it moves
// along its velocity at 150 and plays out its exit animation when ended or
// after 3 s. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcfishman : public ShotBase {
public:
    ShotSoulfcfishman();                         // (DllCreate inlines it)
    virtual ~ShotSoulfcfishman();

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

    // non-virtual helpers
    // unreferenced copy of vanish
    void end();
    void tickLife(float dt);
    // unreferenced
    bool takeEnd();
    void updateStanding(float dt);
    void updateFlying(float dt);

public:
    int m_state;                                 // +0x318
    float m_time;                                // +0x31C
    float m_life;                                // +0x320 flying: ends after 3 s
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endReq;                               // +0x328 set by the end hooks, taken by update
    bool m_ended;                                // +0x329
    bool m_flying;                               // +0x32A
    bool m_toggle;                               // +0x32B standing: object 0 visibility blink
};

