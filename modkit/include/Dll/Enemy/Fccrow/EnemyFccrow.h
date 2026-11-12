// Dll/Enemy/Fccrow/EnemyFccrow.h - dllfccrow, the crow of the FC enemy set
// (object 0x44E8 bytes). Names are inferred; the state
// names describe what each state does.
//
// States (m_state): 0 perch (waits for the player, then picks the label to
// chase), 1 hover (waits 1.5 s, 0.8 s when +0x230 is set), 2 swoop at the
// target, 3 fly off horizontally, 4 die. The target is the label m_label
// when the host has it, else m_playerPos.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFccrow's own fields: the  layout dump.
class EnemyFccrow : public EnemyObjBase {
public:
    EnemyFccrow();
    virtual ~EnemyFccrow();

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

    // module helpers (several have no caller in dllfccrow)
    void startMotion0();
    void setMotionB1Cn(bool off);
    void setFacing(float f);
    void nop0540();
    void stateDie();
    void setState(int s);
    void faceTarget();
    void stateFlyOff(float dt);
    void stateSwoop(float dt);
    bool inRangeNear();
    void stateHover(float dt);
    bool inRangeWake();
    void statePerch(float dt);
    bool handleEvents();
    void turnAround();

public:
    // <layout:EnemyFccrow>
    int m_state;                                    // +0x44C0 0 perch, 1 hover, 2 swoop, 3 fly off, 4 die
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 time in the state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_wake;                                    // +0x44D2 set by slot +0x080
    bool m_hit;                                     // +0x44D3 set by slot +0x084
    bool m_lifted;                                  // +0x44D4 slot +0x018 has moved it up once
    unsigned char _pad44D5[0x3];
    float m_accX;                                   // +0x44D8 flight acceleration / speed (x)
    float m_accY;                                   // +0x44DC flight acceleration (y)
    float m_flyTime;                                // +0x44E0 duration of the fly-off move
    int m_label;                                    // +0x44E4 label the crow chases (-1: none; m_playerPos when it is gone)
    // </layout:EnemyFccrow>
};

