// Dll/Enemy/Fcskl/EnemyFcskl.h - dllfcskl, the bone-throwing skeleton of the
// Famicom-style ("FC") enemy set (object 0x44F4 bytes).
// Names are inferred; the state names describe what each state does.
//
// States (m_state): 0 idle (waits for the player to come near), 1 approach,
// 2 walk / turn at walls, 3 throw a volley of bones, 4 jump, 5 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcskl's own fields: the  layout dump.
class EnemyFcskl : public EnemyObjBase {
public:
    EnemyFcskl();
    virtual ~EnemyFcskl();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014
    virtual void v018();                         // +0x018
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcskl)
    void startMotion0();
    void faceDir0308();
    void setBoxes26A();
    void setBox269();
    void setFacing(float f);
    void faceDir();
    void stateDie();
    void setState(int s);
    bool isI25CSet();
    bool isWallAhead();
    void stateJump();
    void fire();
    void faceTarget();
    void stateThrow(float dt);
    bool inRangeNear();
    bool isI258Clear();
    void targetDelta(EnemyVec2* out);
    void stateWalk(float dt);
    bool inRangeThrow();
    void stateApproach(float dt);
    void stateIdle();
    bool handleEvents();
    bool canMove();
    void turnAround();

public:
    // <layout:EnemyFcskl>
    int m_state;                                    // +0x44C0 0 idle, 1 approach, 2 walk, 3 throw, 4 jump, 5 die
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 time in the state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    float m_dir;                                    // +0x44D0 walking direction
    float m_dir2;                                   // +0x44D4 direction chosen on entering the walk state
    bool m_stateInit;                               // +0x44D8 the state has run its entry code
    bool m_dead;                                    // +0x44D9
    bool m_b44DA;                                   // +0x44DA
    bool m_wake;                                    // +0x44DB set by slot +0x080
    bool m_hit;                                     // +0x44DC set by slot +0x084
    unsigned char _pad44DD[0x3];
    float m_f44E0;                                  // +0x44E0
    int m_i44E4;                                    // +0x44E4
    int m_shotsLeft;                                // +0x44E8 bones left in the volley
    float m_lostTimer;                              // +0x44EC time the player has been out of range
    bool m_turnAtWalls;                             // +0x44F0 spawn flag 1 (slot +0x014)
    unsigned char _pad44F1[0x3];
    // </layout:EnemyFcskl>
};

