// Dll/Enemy/Fuketsugan/EnemyFuketsugan.h - dllfuketsugan, the floating blood
// eye of the Getsu Fuma Den ("Fu") enemy set (object
// 0x44F8 bytes). Names are inferred; the state names describe what each state
// does.
//
// States (m_state): 0 start (remembers its home position), 1 hover (waits
// for the label it chases to come near), 2 chase the label, 3 attack (two
// motions, pushes a beam rectangle each frame), 4 fly back home, 5 die. While
// hovering and flying the body hit box wobbles on a circle of radius 8.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFuketsugan's own fields: the  layout dump.
class EnemyFuketsugan : public EnemyObjBase {
public:
    EnemyFuketsugan();
    virtual ~EnemyFuketsugan();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers
    void startMotion0();
    void nop0374();                              // (no caller)
    void stateDie();
    void setState(int s);
    bool isNear();
    void stateReturn(float dt);
    void stateAttack();
    bool isAbove();
    void dirToLabel(EnemyVec2* out);
    void stateChase(float dt);
    void stateHover(float dt);
    void stateStart();
    bool handleEvents();

public:
    // <layout:EnemyFuketsugan>
    int m_state;                                    // +0x44C0 0 start, 1 hover, 2 chase, 3 attack, 4 return home, 5 die
    int m_prevState;                                // +0x44C4
    int m_phase;                                    // +0x44C8 attack phase (state 3): 0 wind-up, 1 firing
    float m_timer;                                  // +0x44CC time in the current wobble step (0.4 s)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_wake;                                    // +0x44D2 set by slot +0x080, cleared every frame
    bool m_hit;                                     // +0x44D3 set by slot +0x084
    float m_attackWait;                             // +0x44D4 time chasing before an attack is allowed (3 s)
    int m_labelId;                                  // +0x44D8 label chased (-1: none)
    float m_from[2];                                // +0x44DC hit-box offset the wobble starts from
    float m_to[2];                                  // +0x44E4 hit-box offset the wobble goes to (radius 8)
    float m_home[2];                                // +0x44EC position taken in state 0, state 4 flies back to it
    float m_lostTimer;                              // +0x44F4 time the label has been on the other side (2 s)
    // </layout:EnemyFuketsugan>
};

