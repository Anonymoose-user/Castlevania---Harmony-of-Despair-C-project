// Dll/Enemy/Fcghost/EnemyFcghost.h - dllfcghost, the ghost of the
// Famicom-style ("FC") enemy set that fades in and drifts towards a label
// (object 0x44DC bytes). Names are inferred.
//
// States (m_state): 0 idle (waits for the player near the label), 1 appear
// (blinks for 1 s), 2 drift, 3 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcghost's own fields: the  layout dump.
class EnemyFcghost : public EnemyObjBase {
public:
    EnemyFcghost();
    virtual ~EnemyFcghost();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual void v148();                         // +0x148 reset to the idle state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcghost)
    void startMotion0();
    void setMotionB1C(bool off);
    void setFacing(float f);
    void nop04DC();
    void stateDie();
    void faceLabel();
    void dirToLabel(EnemyVec2* out);
    void stateDrift(float dt);
    void setState(int s);
    void stateAppear(float dt);
    bool inRange();
    void stateIdle();
    bool handleEvents();
    void turnAround();

public:
    // <layout:EnemyFcghost>
    int m_state;                                    // +0x44C0 0 idle, 1 appear, 2 float towards the label / player, 3 die
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 time in the state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_wake;                                    // +0x44D2 set by slot +0x080
    bool m_hit;                                     // +0x44D3 set by slot +0x084
    bool m_blink;                                   // +0x44D4 toggled every frame while appearing
    unsigned char _pad44D5[0x3];
    int m_labelId;                                  // +0x44D8 label it homes on (-1: none; the own position stands in)
    // </layout:EnemyFcghost>
};

