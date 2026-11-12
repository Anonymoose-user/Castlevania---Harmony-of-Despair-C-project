// Dll/Enemy/Fuhisyouka/EnemyFuhisyouka.h - dllfuhisyouka, the leaping
// "hisyouka" of the Getsu Fuma Den ("Fu") enemy set (
// object 0x44E8 bytes). Names are inferred.
//
// States (m_state): 0 idle (waits for the player within 128), 1 land / wait
// (0.1 s, back to idle after 5 s on another layer), 2 leap (towards the
// player always when +0x230 is set, else with a 60 % chance), 4 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFuhisyouka's own fields: the  layout dump.
class EnemyFuhisyouka : public EnemyObjBase {
public:
    EnemyFuhisyouka();
    virtual ~EnemyFuhisyouka();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014 empty
    virtual void v018();                         // +0x018
    virtual void v01C(float dt);                 // +0x01C empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfuhisyouka)
    void setState(int s);
    void startMotion0();
    void setBox268();
    void setBox269();
    void setBoxes26A();
    void setFacing(float f);
    void nop0660();
    void clearB268();
    void clearB269();
    void clearB26AB();
    void stateDie();
    bool sameLayer();
    bool tickLost(float dt);
    bool isI25CSet();
    void turnAround();
    bool isWallAhead();
    void faceTarget();
    void stateLeap(float dt);
    void stateLand(float dt);
    bool inRange();
    void stateIdle();
    bool handleEvents();
    bool isI258Set();
    bool isSettled();
    void setMotionB1C(bool off);

public:
    // <layout:EnemyFuhisyouka>
    int m_state;                                    // +0x44C0 0 idle, 1 land / wait, 2 leap, 4 die
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 time in the state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_b44D2;                                   // +0x44D2 set once by slot +0x018
    bool m_wake;                                    // +0x44D3 set by slot +0x080
    bool m_hit;                                     // +0x44D4 set by slot +0x084
    unsigned char _pad44D5[0x7];
    int m_i44DC;                                    // +0x44DC cleared by the constructor only
    int m_i44E0;                                    // +0x44E0 cleared by the constructor only
    float m_lostTimer;                              // +0x44E4 time the player has been on the other layer
    // </layout:EnemyFuhisyouka>
};

