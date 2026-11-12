// Dll/Enemy/Fcbat/EnemyFcbat.h - dllfcbat, the swooping bat of the
// Famicom-style ("FC") enemy set (object 0x44EC bytes).
// Names are inferred; the state names describe what each state does.
//
// States (m_state): 0 idle (hangs until the player comes near), 1 swoop (a
// parabola down to the player's height), 2 fly (straight on, bobbing), 3 fade
// out (blinks for 0.3 s, then is gone), 4 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcbat's own fields: the  layout dump.
class EnemyFcbat : public EnemyObjBase {
public:
    EnemyFcbat();
    virtual ~EnemyFcbat();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014
    virtual void v018();                         // +0x018 (empty)
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcbat)
    void setShotKind(bool b);
    void startMotion0();
    void setMotionB1C(bool off);
    void setFacing(float f);
    void copyBob();
    void stateDie();
    void stateFade(float dt);
    void setState(int s);
    bool otherSide();
    void stateFly(float dt);
    void faceTarget();
    void stateSwoop(float dt);
    bool inSwoopRange();
    void stateIdle();
    bool handleEvents();
    void turnAround();
    static int sameCodeOne();

public:
    // <layout:EnemyFcbat>
    int m_state;                                    // +0x44C0 0 idle, 1 swoop, 2 fly, 3 fade out, 4 die
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 time in the state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_wake;                                    // +0x44D2 set by slot +0x080
    bool m_hit;                                     // +0x44D3 set by slot +0x084
    float m_cycle;                                  // +0x44D4 phase of the flapping bob (fly / fade out)
    float m_swoopTime;                              // +0x44D8 length of the swoop
    float m_swoopAx;                                // +0x44DC swoop acceleration (x)
    float m_swoopAy;                                // +0x44E0 swoop acceleration (y)
    bool m_blink;                                   // +0x44E4 toggled every frame while fading out
    unsigned char _pad44E5[0x3];
    int m_variant;                                  // +0x44E8 0 normal, 1 no bobbing (spawn flag 1, slot +0x014)
    // </layout:EnemyFcbat>
};

