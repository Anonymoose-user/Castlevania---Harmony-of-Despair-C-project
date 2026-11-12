// Dll/Enemy/Fcmeduhead/EnemyFcmeduhead.h - dllfcmeduhead, the Medusa head of
// the Famicom-style ("FC") enemy set (object 0x44E8
// bytes). It flies across the room between the two bounds +0x4464 / +0x446C
// while its body hit box bobs on a sine wave. Names are inferred.
//
// States (m_state): 0 enter (moves to one bound, waits), 1 appear (blinks for
// 1 s), 2 fly (until past the far bound), 3 turn (blinks 0.3 s, then picks a
// side and a height and appears again), 4 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcmeduhead's own fields: the  layout dump.
class EnemyFcmeduhead : public EnemyObjBase {
public:
    EnemyFcmeduhead();
    virtual ~EnemyFcmeduhead();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual void v148();                         // +0x148 restart in state 0
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcmeduhead)
    void setMotionKind(bool fly);
    void startMotion0();
    void setMotionB1C(bool off);
    void setFacing(float f);
    void syncBox1();
    void stateDie();
    void setState(int s);
    void waveBody(float dt);
    void stateTurn(float dt);
    bool isPastBound();
    void stateFly(float dt);
    void stateAppear(float dt);
    void stateEnter(float dt);
    bool handleEvents();

public:
    // <layout:EnemyFcmeduhead>
    int m_state;                                    // +0x44C0 0 enter, 1 appear (blinking), 2 fly, 3 turn (blinking), 4 die
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 time in the state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_wake;                                    // +0x44D2 set by slot +0x080
    bool m_hit;                                     // +0x44D3 set by slot +0x084
    float m_enterTime;                              // +0x44D4 length of state 0
    float m_phase;                                  // +0x44D8 position in the wave period (waveBody)
    bool m_blink;                                   // +0x44DC hit box shown / hidden while blinking
    unsigned char _pad44DD[0x3];
    float m_startPos[2];                            // +0x44E0 position chosen on entering state 0
    // </layout:EnemyFcmeduhead>
};

