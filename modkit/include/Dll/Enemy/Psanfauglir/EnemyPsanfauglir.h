// Dll/Enemy/Psanfauglir/EnemyPsanfauglir.h - dllpsanfauglir, Anfauglir, the
// wolf of the Portrait-of-Ruin-style ("PS") enemy set (
// object 0x44EC bytes; data file p_fenrai.opd). Names are inferred; the state
// names describe what each state does. Its motions are hit box 0's u00
// (hb0Start / hb0GetU00).
//
// States (m_state): 0 start, 1 idle (waits for the player in range), 2 walk
// (paces around m_home), 3 bite (a lunge), 4 die (fades out, puffing smoke),
// 5 dead.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyPsanfauglir's own fields: the  layout dump.
class EnemyPsanfauglir : public EnemyObjBase {
public:
    EnemyPsanfauglir();
    virtual ~EnemyPsanfauglir();

    // overridden slots
    virtual void v008();                         // +0x008 (empty)
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 updateRect()
    virtual void v01C(float dt);                 // +0x01C (empty)
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                       // +0x080 wake up
    virtual void v084(int part);                       // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual const char* v1A0();                  // +0x1A0 the effect name
    virtual void release();                      // +0x4D0

    // module helpers
    void setFacing(float f);
    void updateRect();
    void setState(int s);
    bool stateDie(float dt);
    bool stateBite(float dt);
    bool inRange(float rx, float ry, float dir);
    bool stateWalk(float dt);
    bool stateIdle(float dt);

public:
    // <layout:EnemyPsanfauglir>
    int m_state;                                    // +0x44C0 0 start, 1 idle, 2 walk, 3 bite, 4 die, 5 dead
    int m_phase;                                    // +0x44C4 step inside the state
    float m_facing;                                 // +0x44C8 -1 left, 1 right (setFacing)
    float m_timer;                                  // +0x44CC time in the phase
    float m_wait;                                   // +0x44D0 phase length
    float m_fxTimer;                                // +0x44D4 state 4: time since the last smoke puff
    float m_dir;                                    // +0x44D8 walking direction
    float m_prevDir;                                // +0x44DC the one before
    float m_home[2];                                // +0x44E0 position at start(), the walk stays within 200 of it
    bool m_wake;                                    // +0x44E8 set by slot +0x080
    bool m_hit;                                     // +0x44E9 set by slot +0x084
    bool m_seen;                                    // +0x44EA the player was in range (inRange keeps it)
    bool m_lunging;                                 // +0x44EB state 3: the lunge has started
    // </layout:EnemyPsanfauglir>
};

