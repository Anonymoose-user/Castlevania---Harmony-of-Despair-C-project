// Dll/Enemy/Fcredskl/EnemyFcredskl.h - dllfcredskl, the red skeleton of the
// Famicom-style ("FC") enemy set: it collapses when hit and gets up again
// (object 0x44EC bytes). It loads dllfcskl's data
// (getDataPath). Names are inferred.
//
// States (m_state): 0 buried (waits for the player), 1 rise, 2 walk (wait /
// hop steps), 3 sink back (player out of sight for 5 s), 4 collapse (hit).
// The hit-box "u00" values set through the hb0Start pattern are motion ids.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcredskl's own fields: the  layout dump.
class EnemyFcredskl : public EnemyObjBase {
public:
    EnemyFcredskl();
    virtual ~EnemyFcredskl();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: collapse
    virtual void v148();                         // +0x148 revive where it collapsed
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (most have no caller in dllfcredskl)
    void startMotion0();
    void faceDir0308();
    void setBoxes26A();
    void setFacing(float f);
    void nop060C();
    void clearB268();
    void clearB26AB();
    void setMotionB1C(bool off);
    void stateCollapse();
    void setState(int s);
    void stateSink();
    bool sameLayer();
    void faceTarget();
    void turnAround();
    bool isI258Clear();
    bool isWallAhead();
    bool mustTurn();
    void stateWalk(float dt);
    void stateRise();
    bool inRange();
    void stateBuried();
    bool handleEvents();
    int returnOne();

public:
    // <layout:EnemyFcredskl>
    int m_state;                                    // +0x44C0 0 buried, 1 rise, 2 walk, 3 sink, 4 collapse
    int m_prevState;                                // +0x44C4
    int m_step;                                     // +0x44C8 walk sub-step: 0 wait, 1 hop
    float m_timer;                                  // +0x44CC time in the state / step
    float m_facing;                                 // +0x44D0 -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D4 the state has run its entry code
    bool m_collapsed;                               // +0x44D5 set when the collapse motion ends; v148 revives
    bool m_b44D6;                                   // +0x44D6 slot +0x018 ran once
    bool m_wake;                                    // +0x44D7 set by slot +0x080
    bool m_hit;                                     // +0x44D8 set by slot +0x084
    unsigned char _pad44D9[0x3];
    float m_lostTimer;                              // +0x44DC time the player has been out of sight
    float m_saveX;                                  // +0x44E0 target position when it collapsed
    float m_saveY;                                  // +0x44E4
    float m_saveFacing;                             // +0x44E8 facing when it collapsed
    // </layout:EnemyFcredskl>
};

