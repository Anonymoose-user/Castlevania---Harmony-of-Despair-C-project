// Dll/Enemy/Fcaxe/EnemyFcaxe.h - dllfcaxe, the axe armor of the Famicom-style
// ("FC") enemy set (object 0x44EC bytes; data
// DLL_FCarmor). Names are inferred.
//
// States (m_state): 0 idle (waits for the player to come near), 1 walk back
// and forth and throw axes (high or low), 2 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcaxe's own fields: the  layout dump.
class EnemyFcaxe : public EnemyObjBase {
public:
    EnemyFcaxe();
    virtual ~EnemyFcaxe();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default axe request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcaxe)
    void startMotion0();
    void faceDir0308();
    void setBoxes26A();
    void setFacing(float f);
    void faceDir();
    void clearB268();
    void clearB26AB();
    void stateDie();
    void throwAxe(int kind);
    void setState(int s);
    bool inRange();
    void faceTarget();
    bool isI258Clear();
    bool isWallAhead();
    bool mustTurn();
    float dxToTarget();
    void stateWalk(float dt);
    void stateIdle();
    bool handleEvents();
    void turnAround();
    void setMotionB1C(bool off);
    int returnOne();

public:
    // <layout:EnemyFcaxe>
    int m_state;                                    // +0x44C0 0 idle, 1 walk and throw, 2 die
    int m_step;                                     // +0x44C4 walk step: 0 stand, 1 step right, 2 step left
    float m_timer;                                  // +0x44C8 time in the step
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    float m_dir;                                    // +0x44D0 walking direction (the head box follows it)
    bool m_stateInit;                               // +0x44D4 the state has run its entry code
    bool m_dead;                                    // +0x44D5
    bool m_b44D6;                                   // +0x44D6 slot +0x018 ran once
    bool m_wake;                                    // +0x44D7 set by slot +0x080
    bool m_hit;                                     // +0x44D8 set by slot +0x084
    unsigned char _pad44D9[0x3];
    int m_nextStep;                                 // +0x44DC step forced after a wall or ledge (0: choose)
    float m_throwTimer;                             // +0x44E0 time to the next axe
    float m_lostTimer;                              // +0x44E4 time the player has been out of range
    bool m_dying;                                   // +0x44E8 set by the die state; every axe holds its address
    unsigned char _pad44E9[0x3];
    // </layout:EnemyFcaxe>
};

