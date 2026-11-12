// Dll/Enemy/Psgaibon/EnemyPsgaibon.h - dllpsgaibon, Gaibon, the winged
// fire-spitting demon of the "PS" (Portrait of Ruin) enemy set (vtable
// object 0x44FC bytes; model
// data/enemy/DLL_PSgaibon/p_gyaibo.opd). Names are inferred.
//
// States (m_state): 0 start, 1 wait for the player, 2 fly to a point beside
// the player, 3 fire a volley of fireballs, 4 rage (once, below half health),
// 5 die (smoke, then fade out), 6 dead.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyPsgaibon's own fields: the  layout dump.
class EnemyPsgaibon : public EnemyObjBase {
public:
    EnemyPsgaibon();
    virtual ~EnemyPsgaibon();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default fireball request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 empty
    virtual void v01C(float dt);                 // +0x01C empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllpsgaibon)
    void setFacing(float f);
    void setState(int s);
    bool stateDie(float dt);
    bool stateRage(float dt);
    bool lockTarget(float rangeX, float rangeY);
    bool stateFire(float dt);
    bool stateFly(float dt);
    bool stateWait(float dt);

public:
    // <layout:EnemyPsgaibon>
    int m_state;                                    // +0x44C0 0 start, 1 wait, 2 fly at the player, 3 fire, 4 rage, 5 die, 6 dead
    int m_sub;                                      // +0x44C4 step inside the state
    int m_targetId;                                 // +0x44C8 the target (+0x44BC) it locked on to, -1 none
    unsigned int m_shots;                           // +0x44CC fireballs fired in the volley
    float m_facing;                                 // +0x44D0 -1 left, 1 right (setFacing)
    float m_timer;                                  // +0x44D4 time in the state
    float m_waitTime;                               // +0x44D8 pause before it flies (state 1)
    float m_speed;                                  // +0x44DC flying speed
    float m_maxSpeed;                               // +0x44E0
    float m_angle;                                  // +0x44E4 flying direction (radians)
    float m_offX;                                   // +0x44E8 side of the player it aims for (+-50)
    float m_turnTimer;                              // +0x44EC time since it last turned the body
    float m_fireTimer;                              // +0x44F0 time since the last fireball
    float m_smokeTimer;                             // +0x44F4 time since the last smoke puffs (die state)
    bool m_wake;                                    // +0x44F8 set by slot +0x080, cleared every update
    bool m_hit;                                     // +0x44F9 set by slot +0x084
    bool m_rage;                                    // +0x44FA below half health: the faster volley
    bool m_engaged;                                 // +0x44FB has left the wait state once
    // </layout:EnemyPsgaibon>
};

