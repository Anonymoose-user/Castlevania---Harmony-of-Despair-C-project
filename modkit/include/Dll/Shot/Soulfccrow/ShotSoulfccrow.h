// Dll/Shot/Soulfccrow/ShotSoulfccrow.h - dllshotsoulfccrow's shot class
// (vtable ): the crow soul ("FC karasu", ShotInfo
// name). One to three crows (the first spawns the others through ShotElem274
// records, by kind byte) hover in a figure around a point beside the owner,
// ask the host for a target (m_b29D / m_i2B4 / m_b2C4 / m_i2C8 / m_v2CC),
// dive at it, brake and return; they blink out when the owner is hit
// (getB1F1) and die when it is dismissed (getB1F2). The spawned crows
// share the first crow's hit flags through m_ownerLink, which points at
// its m_hitA / m_hitB (the ShotElem274 record carries that guest address). Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfccrow : public ShotBase {
public:
    ShotSoulfccrow();
    virtual ~ShotSoulfccrow();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    void face(float dir);
    float angleTo(const Vec2* from, const Vec2* to);
    float clampDistance(const Vec2* from, const Vec2* to, float maxd);
    void faceSide(int right);

public:
    int m_state;                                 // +0x318 0 init, 1 place, 2 hover, 3 dive, 4 dead
    int m_phase;                                 // +0x31C dive phase 0 aim, 1 wind-up, 2 dive, 3 brake
    Vec2 m_home;                                 // +0x320 hover point
    Vec2 m_target;                               // +0x328 the host's target position
    Vec2 m_aim;                                  // +0x330 dive direction
    float m_f338;                                // +0x338
    float m_f33C;                                // +0x33C
    float m_speed;                               // +0x340
    float m_speedMax;                            // +0x344
    float m_wobble;                              // +0x348 hover figure phase
    float m_timer;                               // +0x34C
    int m_period;                                // +0x350
    float m_angle;                               // +0x354 heading
    float m_cooldown;                            // +0x358
    int m_index;                                 // +0x35C which crow (m_i284)
    int m_count;                                 // +0x360 crows in the group
    bool m_ready;                                // +0x364 faded in
    bool m_leaving;                              // +0x365
    bool m_hasTarget;                            // +0x366
    bool m_searching;                            // +0x367
    int m_targetId;                              // +0x368
    float m_blinkTime;                           // +0x36C
    bool m_visible;                              // +0x370
    bool m_hitA;                                 // +0x371 owner was hit (getB1F1)
    bool m_hitB;                                 // +0x372 owner dismissed it (getB1F2)
};

