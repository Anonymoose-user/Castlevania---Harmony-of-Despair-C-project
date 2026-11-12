// Dll/Enemy/Psfishh/EnemyPsfishh.h - dllpsfishh, the fish-head that rises
// out of the water and spits at the player (Portrait of Ruin-style, "PS"
// set;, object 0x44F0 bytes). Names are inferred.
//
// States (m_state): 0 surface (goes straight to 1), 1 wait for the player
// (within 128 x 80, or woken), 2 act: driven by the motion of hit box 0
// (+0x2B4 u00: 0 wait, 1 spit a shot, 2 back to 1, 3 turn), 3 die (phases
// 0..4: show the remains, wait for the ground, sink, pause, fade out while
// spawning particles), 4 dead.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyPsfishh's own fields: the  layout dump.
class EnemyPsfishh : public EnemyObjBase {
public:
    EnemyPsfishh();
    virtual ~EnemyPsfishh();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014
    virtual void v018();                         // +0x018 empty
    virtual void v01C(float dt);                 // +0x01C snaps to the water surface
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers
    void setFacing(float f);
    void snapToSurface();
    void setState(int s);
    bool stateDie(float dt);
    bool stateAct(float dt);
    void turnToTarget();
    bool inRange();

public:
    // <layout:EnemyPsfishh>
    int m_state;                                    // +0x44C0 0 surface, 1 wait for the player, 2 act (motion driven), 3 die, 4 dead
    int m_phase;                                    // +0x44C4 step inside the die state (0..4)
    float m_facing;                                 // +0x44C8 -1 left, 1 right (setFacing)
    float m_timer;                                  // +0x44CC time in the step / the wait
    float m_waitTime;                               // +0x44D0 wait before the attack (1..1.5 s with +0x230 set, else 1.5..2.5 s)
    float m_shotTimer;                              // +0x44D4 time since the last death particle
    int m_shotCount;                                // +0x44D8 death particles spawned
    bool m_wake;                                    // +0x44DC set by slot +0x080
    bool m_hit;                                     // +0x44DD set by slot +0x084
    bool m_shown;                                   // +0x44DE spawn flags != 0 (slot +0x014): the first +0x2C4 box starts on
    unsigned char _pad44DF[0x1];
    EnemyVec2 m_home;                               // +0x44E0 the target position at start
    EnemyVec2 m_sink;                               // +0x44E8 offset of the +0x2C4 boxes 2 and 3 while dying
    // </layout:EnemyPsfishh>
};

