// Dll/Shot/Soulfcdeath/ShotSoulfcdeath.h - dllshotsoulfcdeath's shot class
// (vtable ): the Death soul (ShotInfo name
// "L. Shinigami" in Japanese). Level 0 is an invisible spawner that follows
// the owner and queues a sickle (a ShotElem274 record, level 1) at a random
// spot near him every few seconds (4 s at kind 0 down to 1 s at kind 8),
// until the owner's flag 1. Level 1 is a spinning sickle: it blinks in, asks
// the original game for a target within 160 px, flies at it (or a random way) at
// 60 px/s for a second, pauses, and repeats; after 10 s (or a hit/vanish
// hook) it plays its vanish sprite and dies. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcdeath : public ShotBase {
public:
    ShotSoulfcdeath();                           // (DllCreate inlines it)
    virtual ~ShotSoulfcdeath();

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

    // non-virtual (end, tickEnd and takeEnd are unreferenced)
    void updateSpawner(float dt);
    void spin(float dt);
    void end();
    void tickEnd(float dt);
    bool takeEnd();
    void updateSickle(float dt);

public:
    int m_state;                                 // +0x318 sickle: 0 new, 1 placed, 2 blinking in, 3 paused, 4 aiming, 5 flying, 6 ending, 7 vanishing, 8 done
    float m_timer;                               // +0x31C
    float m_dir;                                 // +0x320 -1 facing left, 1 right
    float m_time;                                // +0x324 sickle life
    bool m_endPending;                           // +0x328
    bool m_ended;                                // +0x329
    bool m_sickle;                               // +0x32A level 1
    bool m_visible;                              // +0x32B blink phase
    bool m_hitEarly;                             // +0x32C hit while being placed: move it
    int m_spinFrame;                             // +0x330 0..3, a quarter turn each
    float m_spinTime;                            // +0x334
};

