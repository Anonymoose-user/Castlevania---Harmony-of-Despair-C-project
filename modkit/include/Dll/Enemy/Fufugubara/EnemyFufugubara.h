// Dll/Enemy/Fufugubara/EnemyFufugubara.h - dllfufugubara, the "fugubara"
// enemy of the Fuma-style ("FU") set: it walks back and forth and spits a
// shot (0x40000042) at the player when he is in front of it (vtable
// object 0x44DC bytes). Names are inferred.
//
// States (m_state): 0 patrol (walk, turn at walls and ledges, look for the
// player once a second), 1 attack (one shot, 1 s), 2 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFufugubara's own fields: the  layout dump.
class EnemyFufugubara : public EnemyObjBase {
public:
    EnemyFufugubara();
    virtual ~EnemyFufugubara();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller)
    void startMotion0();
    void faceDir();
    void setBoxes26A();
    void setFacing(float f);
    void nop664();
    void clearB268();
    void clearB26AB();
    void stateDie();
    void setState(int s);
    void fire();
    void stateAttack(float dt);
    bool inReach();
    void turnAround();
    bool isI258Clear();
    bool isWallAhead();
    bool mustTurn();
    void statePatrol(float dt);
    bool handleEvents();
    void faceTarget();
    void setMotionB1C(bool off);

public:
    // <layout:EnemyFufugubara>
    int m_state;                                    // +0x44C0 0 patrol, 1 attack, 2 die
    float m_timer;                                  // +0x44C4 time in the state
    float m_facing;                                 // +0x44C8 -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44CC the state has run its entry code
    bool m_dead;                                    // +0x44CD
    bool m_b44CE;                                   // +0x44CE set once by slot +0x018
    bool m_wake;                                    // +0x44CF set by slot +0x080
    bool m_hit;                                     // +0x44D0 set by slot +0x084
    unsigned char _pad44D1[0x7];
    int m_i44D8;                                    // +0x44D8 zeroed by the constructor, never used
    // </layout:EnemyFufugubara>
};

