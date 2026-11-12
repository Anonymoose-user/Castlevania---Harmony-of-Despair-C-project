// Dll/Shot/Fcdramaku/ShotFcdramaku.h - dllshotfcdramaku's shot class (vtable
// ): FC Dracula's barrage bullet ("FCドラキュラ：弾幕",
// ShotInfo name). It keeps the direction the owner gave it, starting at
// 50 units/s and speeding up by 400 per second to its given speed; it dies
// after 3 s or on a hit (hits count unless m_i284 is negative). Names are
// inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFcdramaku : public ShotBase {
public:
    ShotFcdramaku();                             // (DllCreate inlines it)
    virtual ~ShotFcdramaku();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void vfunc020();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual, unreferenced
    void setState(int s);
    void end();

public:
    int m_state;                                 // +0x318 0 start, 1 flying, 2 ending, 3 dead
    float m_time;                                // +0x31C (only cleared)
    float m_f320;                                // +0x320 (only cleared)
    bool m_ended;                                // +0x324
    Vec2 m_heading;                              // +0x328 unit direction
    Vec2 m_startPos;                             // +0x330
    float m_maxSpeed;                            // +0x338
    float m_speed;                               // +0x33C
    float m_life;                                // +0x340
    bool m_hittable;                             // +0x344
};

