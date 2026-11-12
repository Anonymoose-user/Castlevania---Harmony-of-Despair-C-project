// Dll/Shot/Psgaibonsoul/ShotPsgaibonsoul.h - dllshotpsgaibonsoul's shot class
// (vtable ): the Gaibon soul (ShotInfo name
// "PS Gaibon: Soul" in Japanese), a familiar that rises in behind the owner,
// follows it (home point 50 px behind, 60 px up from getV048()), hovers,
// and when the host reports a target (getI2B4() / getB29D() / getV2AC())
// swoops at it with a fireball trail (a ShotElem174 record), then returns.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotPsgaibonsoul : public ShotBase {
public:
    ShotPsgaibonsoul();                          // (DllCreate inlines it)
    virtual ~ShotPsgaibonsoul();

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

    // non-virtual helpers (states and sub-steps of update)
    // unreferenced
    void setState(int state);
    // unreferenced; inlined in update
    bool fadeOut(float dt);
    bool attack(float dt);
    // unreferenced; inlined
    void tickCooldown(float dt);
    bool hover(float dt);
    bool findTarget();
    bool approach(float dt);
    // unreferenced; inlined in update
    bool rise(float dt);
    // unreferenced
    void leave();

public:
    int m_state;                                 // +0x318 0 rise, 1 follow, 2 hover, 3 attack, 4 fade, 5 dead
    int m_sub;                                   // +0x31C step within the state
    int m_trail;                                 // +0x320 fireball trail record (addElem174), -1 none
    float m_time;                                // +0x324
    float m_dir;                                 // +0x328 -1 facing left, 1 right
    float m_speed;                               // +0x32C
    float m_alpha;                               // +0x330 0..1
    float m_angle;                               // +0x334 flight direction (radians)
    float m_coolTime;                            // +0x338
    float m_coolLimit;                           // +0x33C 1.5..3 s, shorter for higher kinds
    bool m_cooling;                              // +0x340 after an attack
    unsigned char _pad341[0x3];
    Vec2 m_anchor;                               // +0x344 getV048() last frame
    Vec2 m_target;                               // +0x34C
};

