// Dll/Shot/Subfcholywater/ShotSubfcholywater.h - dllshotsubfcholywater's
// shot class (vtable ): the FC holy water sub-weapon
// (ShotInfo name "Sub FC Holy Water" in Japanese). The thrown vial (getI284()
// a multiple of 100) falls until it hits something and then spawns the first
// flame (a ShotElem274 record); each flame (getI284() % 100 != 0, generation
// getI284() / 100) burns and, while the kind's generation limit allows,
// spawns the next one 14 px ahead along the floor. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSubfcholywater : public ShotBase {
public:
    ShotSubfcholywater();                        // (DllCreate inlines it)
    virtual ~ShotSubfcholywater();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual helpers
    void updateFlame(float dt);
    // unreferenced copy of vanish
    void end();
    // unreferenced
    void tickLife(float dt);
    // unreferenced
    bool takeEnd();
    void updateVial(float dt);

public:
    int m_state;                                 // +0x318 vial 0-4, flame 5 (burning) / 4 (dead)
    int m_spawn;                                 // +0x31C flame: next-flame search state
    float m_time;                                // +0x320
    float m_life;                                // +0x324 the vial ends after 30 s
    float m_dir;                                 // +0x328 -1 facing left, 1 right
    bool m_endReq;                               // +0x32C
    bool m_ended;                                // +0x32D
    bool m_flame;                                // +0x32E
    bool m_spread;                               // +0x32F the flame spawns another
    float m_nextX;                               // +0x330 where the next flame goes
    float m_nextY;                               // +0x334
    int m_gen;                                   // +0x338 flame generation
};

