// Dll/Enemy/Fcbonep/EnemyFcbonep.h - dllfcbonep, the fire-breathing bone pillar
// of the Famicom-style ("FC") enemy set (object 0x44E4
// bytes). Names are inferred; the state names describe what each state does.
//
// States (m_state): 0 idle (waits for the player to come near), 1 wait
// (faces the player for 3 s, 1.5 s when +0x230 is set), 2 breathe fire (two
// volleys 0.5 s apart), 3 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcbonep's own fields: the  layout dump.
class EnemyFcbonep : public EnemyObjBase {
public:
    EnemyFcbonep();
    virtual ~EnemyFcbonep();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                       // +0x080 wake up
    virtual void v084(int part);                       // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcbonep)
    void startMotion0();
    void setFacing(float f);
    void nop0684();
    void stateDie();
    void setState(int s);
    void fire();
    void setHitBox0(unsigned int u00, bool b2B);
    void faceTarget();
    void stateFire(float dt);
    bool inRange();
    void stateWait(float dt);
    void stateIdle();
    bool handleEvents();
    void turnAround();
    void setMotionB1Cq(bool off);

public:
    // <layout:EnemyFcbonep>
    int m_state;                                    // +0x44C0 0 idle, 1 wait, 2 breathe fire, 3 die
    int m_prevState;                                // +0x44C4
    int m_phase;                                    // +0x44C8 sub-step of state 2
    float m_timer;                                  // +0x44CC time in the state / phase
    float m_facing;                                 // +0x44D0 -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D4 the state has run its entry code
    bool m_dead;                                    // +0x44D5
    bool m_b44D6;                                   // +0x44D6
    bool m_wake;                                    // +0x44D7 set by slot +0x080
    bool m_hit;                                     // +0x44D8 set by slot +0x084
    unsigned char _pad44D9[0x3];
    float m_lostTimer;                              // +0x44DC time the player has been out of range
    int m_shotsFired;                               // +0x44E0 volleys fired in state 2
    // </layout:EnemyFcbonep>
};

