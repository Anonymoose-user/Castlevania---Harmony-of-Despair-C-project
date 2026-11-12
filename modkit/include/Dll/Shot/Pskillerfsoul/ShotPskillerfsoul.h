// Dll/Shot/Pskillerfsoul/ShotPskillerfsoul.h - dllshotpskillerfsoul's shot
// class (vtable ): the Killer Fish soul (ShotInfo
// name "PS Killer Fish: Soul" in Japanese). Spawned 14 px up; if the host's
// point test (the getI248() callback) says it is in water, it fades in and
// swims, homing on a target the host finds (getI2B4() / getI2C8()), until
// it leaves the water or its life (1-2 s by kind) runs out; out of water it
// just flops and fades. Kinds 8+ leave a trail (a ShotElem174 record).
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

// ShotBase +0x248 (setOnceI248) holds an original game callback here: a point test
// called with the shot's integer position (nonzero: inside water).
typedef int (*ShotPointTestFunc)(int x, int y);

class ShotPskillerfsoul : public ShotBase {
public:
    ShotPskillerfsoul();                         // (DllCreate inlines it)
    virtual ~ShotPskillerfsoul();

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
    void track();
    // unreferenced; inlined in update
    void tickLife(float dt);

public:
    int m_state;                                 // +0x318 0 start, 1 fade in, 2 swim, 3 fade out, 4 dead
    unsigned char m_inWater;                     // +0x31C the point test at start
    unsigned char _pad31D[0x3];
    float m_life;                                // +0x320
    float m_lifeLimit;                           // +0x324 1..2 s
    float m_dir;                                 // +0x328 -1 facing left, 1 right
    float m_time;                                // +0x32C fade time
    float m_bubbleTime;                          // +0x330
    float m_angle;                               // +0x334 swim direction (radians)
    int m_trail;                                 // +0x338 trail record (addElem174), -1 none
    int m_target;                                // +0x33C the host's target handle, -1 none
    Vec2 m_targetPos;                            // +0x340
};

