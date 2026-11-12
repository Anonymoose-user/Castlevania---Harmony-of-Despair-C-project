// Dll/Shot/Psberrigansoul/ShotPsberrigansoul.h - dllshotpsberrigansoul's shot
// class (vtable ): the Berrigan soul ("PS Berrigan:
// Soul" in katakana, the ShotInfo name). One object thrown forward and up,
// falling under gravity and turned along its velocity; on a hit it stops and
// ends after 0.5 s, and it ends anyway after 30 s; ending fades it out over
// 0.5 s. At soul level 8+ it drags a trail element (addElem164). Names are
// inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotPsberrigansoul : public ShotBase {
public:
    ShotPsberrigansoul();                        // (DllCreate inlines it)
    virtual ~ShotPsberrigansoul();

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

    void aim();
    // non-virtual, unreferenced copies of parts of update()
    void end();
    void tickLife(float dt);
    bool checkFade();

    // the SDK's Dinkumware atan2f (Psberrigansoul/PsberrigansoulMath.cpp)
    static float atan2f(float y, float x);
    static float atanReduced(float x, unsigned int idx);
    static short fdtest(const float* p);

public:
    int m_state;                                 // +0x318 0 flying, 1 stuck, 2 fading, 3 dead
    float m_time;                                // +0x31C time in states 1 and 2
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    float m_angle;                               // +0x328 heading (atan2 of the velocity)
    bool m_fadeReq;                              // +0x32C end() asks for the fade
    bool m_ended;                                // +0x32D
    unsigned char _pad32E[2];
    int m_trail;                                 // +0x330 addElem164 index (soul level 8+)
};

