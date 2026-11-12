// Dll/Shot/Fumaryukotsushot/ShotFumaryukotsushot.h - dllshotfumaryukotsushot's
// shot class (vtable ): the bone dragon Ryukotsuki's
// shot ("Getsu Fuma Den Ryukotsuki: shot", ShotInfo name). The spawn word
// m_i284 packs kind (byte 0), angle in degrees (byte 1), bounce count
// (byte 2) and "play the sound" (byte 3). Kinds 0/1 fly straight (kind 0
// also queues its follow-up), 2 is a straight object-B shot, 3..5 fly at the
// angle and bounce off walls (3 and 4 blinking). Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFumaryukotsushot : public ShotBase {
public:
    ShotFumaryukotsushot();                      // (DllCreate inlines it)
    virtual ~ShotFumaryukotsushot();

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

    void end();
    bool bounce();
    bool isEnding();
    bool tickEnd();
    void blink();
    void tickLife(float dt);

public:
    int m_state;                                 // +0x318 0 flying, 1 ending
    int m_kind;                                  // +0x31C m_i284 byte 0
    int m_angle;                                 // +0x320 m_i284 byte 1, degrees
    unsigned int m_bounces;                      // +0x324
    unsigned int m_maxBounces;                   // +0x328 m_i284 byte 2
    float m_time;                                // +0x32C
    float m_life;                                // +0x330
    float m_dir;                                 // +0x334 -1 left, 1 right
    int m_i338;                                  // +0x338 (unused)
    unsigned short m_blink;                      // +0x33C 0..6
};

