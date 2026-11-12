// Dll/Enemy/Fclance/EnemyFclance.h - dllfclance, the spear-carrying armor
// knight of the Famicom-style ("FC") enemy set (object
// 0x44DC bytes; its model is DLL_FCarmor). Names are inferred.
//
// States (m_state): 0 patrol (walks, turning at walls and ledges and every
// 3..5 s), 1 chase (walks at the player, turning towards it every second),
// 2 die. It walks twice as fast when EnemyObjBase +0x230 is set.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFclance's own fields: the  layout dump.
class EnemyFclance : public EnemyObjBase {
public:
    EnemyFclance();
    virtual ~EnemyFclance();

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

    // module helpers (several have no caller in dllfclance)
    void startMotion0();
    void faceDir();
    void setBoxes26A();
    void setFacing(float f);
    void nop6B4();
    void clearB268Tu();
    void clearB26ABTu();
    void stateDie();
    void setState(int s);
    bool inRange();
    void faceTarget();
    void turnAround();
    bool isI258Clear();
    bool isWallAhead();
    bool isBlocked();
    void stateChase(float dt);
    void statePatrol(float dt);
    bool handleEvents();
    void setMotionB1CTu(bool off);

public:
    // <layout:EnemyFclance>
    int m_state;                                    // +0x44C0 0 patrol, 1 chase, 2 die
    float m_timer;                                  // +0x44C4 time since the last turn
    float m_facing;                                 // +0x44C8 -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44CC the state has run its entry code
    bool m_dead;                                    // +0x44CD
    bool m_b44CE;                                   // +0x44CE set once by slot +0x018
    bool m_wake;                                    // +0x44CF set by slot +0x080
    bool m_hit;                                     // +0x44D0 set by slot +0x084
    unsigned char _pad44D1[0x3];
    float m_turnTime;                               // +0x44D4 patrol: time until the next turn (3..5 s)
    float m_lostTimer;                              // +0x44D8 chase: time the player has been out of range
    // </layout:EnemyFclance>
};

