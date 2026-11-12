// Dll/Enemy/Fcaltair/EnemyFcaltair.h - dllfcaltair, the eagle of the
// Famicom-style ("FC") enemy set (it carries the flea man; its model is
// DLL_FCnomi) (object 0x44E0 bytes). Names are inferred.
//
// States (m_state): 0 start (goes straight to 1), 1 fly (straight across at
// 130 px/s, now and then hovering for up to 0.5 s; turns when it changes
// layer, EnemyObjBase +0x21F against +0x221), 2 fade out (0.3 s of a
// flickering hit box, then gone; no transition leads here in this module),
// 3 die.
//
// This module has no out-of-line constructor: DllCreate holds the only copy.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcaltair's own fields: the  layout dump.
class EnemyFcaltair : public EnemyObjBase {
public:
    EnemyFcaltair();             // inlined in DllCreate only
    virtual ~EnemyFcaltair();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers
    void setFacing(float f);
    void stateDie();
    void stateFade(float dt);
    void stateFly(float dt);

public:
    // <layout:EnemyFcaltair>
    int m_state;                                    // +0x44C0 0 start, 1 fly, 2 fade out, 3 die
    int m_prevState;                                // +0x44C4
    int m_flyMode;                                  // +0x44C8 state 1: 0 flying, 1 hovering
    float m_timer;                                  // +0x44CC time in the fly mode / the fade
    float m_facing;                                 // +0x44D0 -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D4 the state has run its entry code
    bool m_dead;                                    // +0x44D5
    bool m_wake;                                    // +0x44D6 set by slot +0x080
    bool m_hit;                                     // +0x44D7 set by slot +0x084
    bool m_blink;                                   // +0x44D8 state 2: the hit box flickers
    unsigned char _pad44D9[0x3];
    float m_turnDelay;                              // +0x44DC state 1: no new turn until it runs out
    // </layout:EnemyFcaltair>
};

