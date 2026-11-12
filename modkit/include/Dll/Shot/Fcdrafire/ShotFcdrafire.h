// Dll/Shot/Fcdrafire/ShotFcdrafire.h - dllshotfcdrafire's shot class (vtable
// ): FC Dracula's fireball ("FCドラキュラ：ファイア",
// ShotInfo name). It flies with the velocity the owner gave it, accelerating
// along x (or upwards, when m_i284 is negative) by (m_i284 & 0xFFFF) / 256 *
// 25 per second, capped at its starting speed; after 1.5 s, or a hit once it
// has passed its start, it stops and shows a burst (object A 0) before dying.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFcdrafire : public ShotBase {
public:
    ShotFcdrafire();
    virtual ~ShotFcdrafire();

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
    void end(bool burst);


public:
    int m_state;                                 // +0x318 0 start, 1 flying, 2 ending, 3 burst, 4 kill, 5 dead
    float m_time;                                // +0x31C (only cleared)
    float m_f320;                                // +0x320 (only cleared)
    bool m_vertical;                             // +0x324 accelerate upwards instead of along x
    float m_accel;                               // +0x328
    bool m_ended;                                // +0x32C
    Vec2 m_startVel;                             // +0x330
    Vec2 m_startPos;                             // +0x338
    float m_maxSpeed;                            // +0x340 (not set by the constructor)
    float m_startSpeed;                          // +0x344
    float m_dir;                                 // +0x348 -1 facing left, 1 right
    float m_life;                                // +0x34C
    bool m_passed;                               // +0x350 past its start: hits count
    bool m_burst;                                // +0x351 show the burst when ending
};

