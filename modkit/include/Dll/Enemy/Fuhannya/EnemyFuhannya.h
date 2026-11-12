// Dll/Enemy/Fuhannya/EnemyFuhannya.h - dllfuhannya, the hannya mask of the
// Getsu Fuma Den ("Fu") enemy set (object 0x44E8 bytes).
// Names are inferred; the state names describe what each state does.
//
// It crawls along a floor or ceiling, turning where the room query (the host
// callback at EnemyObjBase +0x048) reports no surface ahead, moves between
// two heights (m_homeY, m_topY) and drops at the player when it passes below.
//
// States (m_state): 0 start, 1 crawl, 2 move to the other height, 3 drop at
// the player and return, 4 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFuhannya's own fields: the  layout dump.
class EnemyFuhannya : public EnemyObjBase {
public:
    EnemyFuhannya();
    virtual ~EnemyFuhannya();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014
    virtual void v018();                         // +0x018 empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfuhannya)
    void startMotion0();
    void setFacing(float f);
    void nop0414();
    void stateDie();
    void setState(int s);
    int surfaceAhead();
    int surfaceAt(float dir);
    void stateDrop(float dt);
    void turnAround();
    void stateMove(float dt);
    bool inRange();
    void stateCrawl(float dt);
    void stateStart();
    bool handleEvents();
    void faceTarget();
    void setMotionB1C(bool off);

public:
    // <layout:EnemyFuhannya>
    int m_state;                                    // +0x44C0 0 start, 1 crawl, 2 move to the other height, 3 drop at the player, 4 die
    int m_phase;                                    // +0x44C4 state 3: 0 drop, 1 crawl back, 2 return to its height (not set by the constructor)
    float m_timer;                                  // +0x44C8
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_wake;                                    // +0x44D2 set by slot +0x080, cleared every frame
    bool m_hit;                                     // +0x44D3 set by slot +0x084
    bool m_atTop;                                   // +0x44D4 at (or going to) m_topY instead of m_homeY
    unsigned char _pad44D5[0x3];
    float m_homeY;                                  // +0x44D8 height taken in state 0
    float m_topY;                                   // +0x44DC m_homeY + 16 * m_steps
    int m_steps;                                    // +0x44E0 spawn flags (slot +0x014): 0 never changes height
    bool m_dropLate;                                // +0x44E4 drop only once the player has come and gone (50 %)
    bool m_seen;                                    // +0x44E5 the player has been below (m_dropLate)
    bool m_rest;                                    // +0x44E6 rests 1.5 s after arriving at a height
    unsigned char _pad44E7[0x1];
    // </layout:EnemyFuhannya>
};

