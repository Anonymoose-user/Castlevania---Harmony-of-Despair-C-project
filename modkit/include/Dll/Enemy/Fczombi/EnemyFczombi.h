// Dll/Enemy/Fczombi/EnemyFczombi.h - dllfczombi, the zombie of the
// Famicom-style ("FC") enemy set that rises out of the ground and shuffles
// back and forth (object 0x44DC bytes). Names are inferred.
//
// States (m_state): 0 idle (waits underground for the player), 1 rise,
// 2 walk, 3 fall (airborne), 4 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFczombi's own fields: the  layout dump.
class EnemyFczombi : public EnemyObjBase {
public:
    EnemyFczombi();
    virtual ~EnemyFczombi();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018
    virtual void update(float dt);               // +0x020
    virtual void v024(const int* a, void* b, bool c); // +0x024
    virtual void destroy();                      // +0x02C
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual void v148();                         // +0x148 reset to the idle state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfczombi)
    void setMotionB1C(bool off);
    void startMotion0();
    void setBoxes26A();
    void faceDir();
    void setFacing(float f);
    void nop069C();
    void clearB26AB();
    void stateDie();
    void setState(int s);
    void stateFall();
    void turnAround();
    bool tickTurnTimer(float dt);
    bool tickEdgeTimer(float dt);
    bool isWallAhead();
    bool isWallAhead2();
    void stateWalk(float dt);
    void stateRise(float dt);
    void faceTarget();
    bool inRange();
    void stateIdle();
    bool handleEvents();
    void clearB268();
    bool isI258Clear();

public:
    // <layout:EnemyFczombi>
    int m_state;                                    // +0x44C0 0 idle (buried), 1 rise, 2 walk, 3 fall, 4 die
    float m_timer;                                  // +0x44C4 time in the state
    float m_facing;                                 // +0x44C8 -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44CC the state has run its entry code
    bool m_dead;                                    // +0x44CD
    bool m_b44CE;                                   // +0x44CE latched by slot +0x018
    bool m_hit;                                     // +0x44CF set by slot +0x084
    bool m_blink;                                   // +0x44D0 toggled every frame while rising
    unsigned char _pad44D1[0x3];
    float m_turnTimer;                              // +0x44D4 delay before turning towards the player again
    float m_edgeTimer;                              // +0x44D8 delay before turning at the +0x4464 / +0x446C bounds
    // </layout:EnemyFczombi>
};

