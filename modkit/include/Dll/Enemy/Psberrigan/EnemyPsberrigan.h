// Dll/Enemy/Psberrigan/EnemyPsberrigan.h - dllpsberrigan ("DLL_PSberrigan",
// object 0x4500 bytes): an armoured enemy that walks back
// and forth around its start position and lunges at the player; when half of
// its hit points are gone (slot +0x080 with +0x1E8 < +0x1EC / 2) its helmet
// flies off and it switches to its second motion set. Names are inferred.
//
// States (m_state): 0 begin, 1 idle, 2 walk, 3 attack (step 1 swing and shot,
// step 2 lunge), 4 lose the helmet, 5 die (fades out, effect bursts), 6 dead.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyPsberrigan's own fields: the  layout dump.
class EnemyPsberrigan : public EnemyObjBase {
public:
    EnemyPsberrigan();
    virtual ~EnemyPsberrigan();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 updates the body box event
    virtual void v01C(float dt);                 // +0x01C empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 damaged
    virtual void v084(int part);                         // +0x084 killed
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllpsberrigan)
    void setFacing(float f);
    void bodyBoxEvent();
    void setState(int s);
    int motionId(int k);
    void playMotion(int k, bool b2B);
    bool stateDie(float dt);
    bool stateLoseHelmet();
    bool stateAttack(float dt);
    bool inRange(float rx, float ry, float dir);
    bool stateWalk(float dt);
    bool stateIdle(float dt);
    void updateHelmet(float dt);
    void dropHelmet();

public:
    // <layout:EnemyPsberrigan>
    int m_state;                                    // +0x44C0 0 begin, 1 idle, 2 walk, 3 attack, 4 lose the armour, 5 die, 6 dead
    int m_step;                                     // +0x44C4 step inside the state
    float m_facing;                                 // +0x44C8 -1 left, 1 right
    float m_timer;                                  // +0x44CC time in the step
    float m_duration;                               // +0x44D0 length of the current step
    float m_fxTimer;                                // +0x44D4 time since the last death effect burst
    bool m_armored;                                 // +0x44D8 still wearing the helmet (motion table 0, else 1)
    bool m_inRange;                                 // +0x44D9 the player was in range (inRange keeps it)
    bool m_lunged;                                  // +0x44DA the attack lunge has started
    unsigned char _pad44DB[0x1];
    float m_home[2];                                // +0x44DC position at start
    bool m_damaged;                                 // +0x44E4 set by slot +0x080 for one frame
    bool m_killed;                                  // +0x44E5 set by slot +0x084
    unsigned char _pad44E6[0x2];
    float m_helmTimer;                              // +0x44E8 age of the falling helmet (hit box 1 of list 1)
    float m_helmPos[2];                             // +0x44EC its offset
    float m_helmVel[2];                             // +0x44F4 its velocity
    float m_helmRot;                                // +0x44FC its rotation
    // </layout:EnemyPsberrigan>
};

