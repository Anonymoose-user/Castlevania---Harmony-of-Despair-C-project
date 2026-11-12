// Dll/Enemy/Pskillerf/EnemyPskillerf.h - dllpskillerf, the killer fish of
// the "PS" (Portrait of Ruin) enemy set (object 0x44E8
// bytes; model data/enemy/DLL_PSkillerf/p_uo.opd). Names are inferred.
//
// States (m_state): 0 start, 1 wait, 2 swim (sub-steps: 0 set-up,
// 1 accelerate, 2 turn round at a wall, 3 brake), 3 die (bubbles, then fade
// out), 4 dead.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyPskillerf's own fields: the  layout dump.
class EnemyPskillerf : public EnemyObjBase {
public:
    EnemyPskillerf();
    virtual ~EnemyPskillerf();

    // overridden slots
    virtual void v008();                         // +0x008 empty
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

    // module helpers (several have no caller in dllpskillerf)
    void setBoxes26A();
    void setFacing(float f);
    void setState(int s);
    bool stateDie(float dt);
    bool isWallAhead();
    float probeAhead();
    bool stateSwim(float dt);

private:
    // the library's callHost449C (module copy ) called with two
    // vector pointers: the probe origin and direction
    float castRay(const EnemyVec2* from, const EnemyVec2* dir);

public:
    // <layout:EnemyPskillerf>
    int m_state;                                    // +0x44C0 0 start, 1 wait, 2 swim, 3 die, 4 dead
    int m_sub;                                      // +0x44C4 step inside the state
    float m_facing;                                 // +0x44C8 -1 left, 1 right (setFacing)
    float m_timer;                                  // +0x44CC time in the state
    float m_speed;                                  // +0x44D0 current swimming speed
    float m_maxSpeed;                               // +0x44D4 set by init (faster when slot +0x044 is set)
    float m_accel;                                  // +0x44D8 set by init
    float m_waitTime;                               // +0x44DC pause between two runs (state 1)
    float m_runTime;                                // +0x44E0 length of one run (2..3 s)
    bool m_wake;                                    // +0x44E4 set by slot +0x080, cleared every update
    bool m_hit;                                     // +0x44E5 set by slot +0x084
    unsigned char _pad44E6[0x2];
    // </layout:EnemyPskillerf>
};

