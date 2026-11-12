// Dll/Enemy/Fcfishman/EnemyFcfishman.h - dllfcfishman, the fishman of the
// Famicom-style ("FC") enemy set (object 0x44EC bytes).
// Names are inferred; the state names describe what each state does.
//
// States (m_state): 0 under water (waits for the player 128..144 px away),
// 1 leap out of the water, 2 turn round, 3 walk, 4 spit a fireball, 5 fall,
// 6 back under water (3 s, then 0), 7 die. Touching water (+0x274 bit 3)
// from states 1, 2, 3 and 5 splashes and goes to state 6.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcfishman's own fields: the  layout dump.
class EnemyFcfishman : public EnemyObjBase {
public:
    EnemyFcfishman();
    virtual ~EnemyFcfishman();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual void v148();                         // +0x148 reset: back under water
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcfishman)
    void nop754();                               // empty (no caller)
    void setSoundSet(bool b);
    void startMotion0();
    void setProbe275();
    void setProbes();
    void setFacing(float f);
    void clearSideProbes();
    void stateDie();
    void setState(int s);
    void setMotionHold(bool off);
    void stateSubmerge(float dt);
    void splash();
    bool inWater();
    void stateFall();
    void fire();
    void stateSpit(float dt);
    bool sameRoom();
    bool updateLost(float dt);
    void turnAround();
    bool isWallAhead();
    bool isWallAhead2();
    void faceTarget();
    void stateWalk(float dt);
    bool inRangeNear();
    void stateTurn();
    void setBoxes26A();
    void clearProbes();
    bool isFree();
    void fireUp();
    void stateLeap(float dt);
    bool inRangeLeap();
    void stateIdle();
    bool handleEvents();
    void clearB275();

private:
    void enterWater();                           // the splash exit of states 1, 2, 3 and 5 (inlined)

public:
    // <layout:EnemyFcfishman>
    int m_state;                                    // +0x44C0 0 under water, 1 leap, 2 turn, 3 walk, 4 spit, 5 fall, 6 back to the water, 7 die
    int m_prevState;                                // +0x44C4
    int m_sub;                                      // +0x44C8 step inside the spit state
    float m_timer;                                  // +0x44CC time in the state
    float m_facing;                                 // +0x44D0 -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D4 the state has run its entry code
    bool m_dead;                                    // +0x44D5
    bool m_wake;                                    // +0x44D6 set by slot +0x080
    bool m_hit;                                     // +0x44D7 set by slot +0x084
    bool m_landed;                                  // +0x44D8 has landed after the leap
    unsigned char _pad44D9[0x3];
    float m_lostTimer;                              // +0x44DC time the player has been out of the room
    float m_homeX;                                  // +0x44E0 where it went under water
    float m_homeY;                                  // +0x44E4
    bool m_spatUp;                                  // +0x44E8 fired its upward shot during the leap
    unsigned char _pad44E9[0x3];
    // </layout:EnemyFcfishman>
};

