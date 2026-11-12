// Dll/Enemy/Fcpanther/EnemyFcpanther.h - dllfcpanther, the leaping panther of
// the Famicom-style ("FC") enemy set (object 0x44DC
// bytes). Names are inferred; the state names describe what each state does.
//
// States (m_state): 0 idle (waits for the player to come near), 1 run (turns
// at walls and when the player crosses over, hops off ledges, leaps at a
// player above it), 2 hop, 3 leap, 4 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcpanther's own fields: the  layout dump.
class EnemyFcpanther : public EnemyObjBase {
public:
    EnemyFcpanther();
    virtual ~EnemyFcpanther();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcpanther)
    void startMotion0();
    void faceBox238();
    void setBox269();
    void setBoxes26A();
    void setFacing(float f);
    void empty0714();
    void clearB268();
    void clearB269();
    void clearB26AB();
    void stateDie();
    void setState(int s);
    bool isGrounded();
    bool isWallAhead();
    void stateLeap();
    void stateHop();
    bool inLeapRange();
    bool isI258Clear();
    void turnAround();
    bool tickTurnTimer(float dt);
    void stateRun(float dt);
    bool inRangeNear();
    void stateIdle();
    bool handleEvents();
    bool canMove();
    void faceTarget();
    float targetDx();
    void setMotionB1C(bool off);
    static int sameCodeOne();

public:
    // <layout:EnemyFcpanther>
    int m_state;                                    // +0x44C0 0 idle, 1 run, 2 hop, 3 leap, 4 die
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 cleared by the die state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_b44D2;                                   // +0x44D2 set by slot +0x018
    bool m_wake;                                    // +0x44D3 set by slot +0x080
    bool m_hit;                                     // +0x44D4 set by slot +0x084
    bool m_turned;                                  // +0x44D5 turned round once after the first hop
    unsigned char _pad44D6[0x2];
    float m_turnTimer;                              // +0x44D8 time before it may turn again when the player crosses over
    // </layout:EnemyFcpanther>
};

