// Dll/Enemy/Fuhiguruma/EnemyFuhiguruma.h - dllfuhiguruma, the rolling fire
// wheel ("hi-guruma") of the Getsu Fuma Den ("Fu") enemy set (vtable
// object 0x44DC bytes). Names are inferred.
//
// States (m_state): 0 start (goes straight to 1), 1 roll (turns at walls and
// where the map query at +0x048 reports another layer; hops when the ground
// ends), 2..4 hop (-200, -260, -80 px/s up; back to 1 on landing), 5 die.
//
// EnemyObjBase::m_once048[0] (+0x048) and m_once048[5] (+0x05C), set once
// through slots +0x1B4 / +0x1C8, are host callbacks here (OPD pointers on
// the original): a map query (x, y) -> layer and a ground probe (x, y) -> the
// distance to the floor. The library declares them as int.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

typedef EnemyPointQueryFunc EnemyMapFunc;

// Member layout of EnemyFuhiguruma's own fields: the  layout dump.
class EnemyFuhiguruma : public EnemyObjBase {
public:
    EnemyFuhiguruma();
    virtual ~EnemyFuhiguruma();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfuhiguruma)
    void startMotion0();
    void faceDir();
    void setBox269();
    void setBoxes26A();
    void setFacing(float f);
    void nop64C();
    void clearB268Tu();
    void clearB26ABOwn();
    void stateDie();
    void setState(int s);
    bool isI25CSet();
    void turnAround();
    bool isWallAhead();
    int queryAhead();
    void stateHop80();
    void stateHop260();
    void stateHop200();
    bool isDropShallow();
    bool isI258Clear();
    void stateRoll();
    void stateStart();
    bool handleEvents();
    bool isBlocked();
    void faceTarget();
    void clearB269Tu();
    float targetDx();
    bool inRangeNear();
    bool inRangeLow();
    void setMotionB1CTu(bool off);

    // the two host callbacks (see the file comment)
    EnemyMapFunc mapFunc() const { return m_query048; }
    EnemyMapFunc groundFunc() const { return m_query05C; }

public:
    // <layout:EnemyFuhiguruma>
    int m_state;                                    // +0x44C0 0 start, 1 roll, 2..4 hop (-200, -260, -80 px/s up), 5 die
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 cleared by the die state only
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_b44D2;                                   // +0x44D2 set once by slot +0x018
    bool m_wake;                                    // +0x44D3 set by slot +0x080
    bool m_hit;                                     // +0x44D4 set by slot +0x084
    unsigned char _pad44D5[0x3];
    int m_i44D8;                                    // +0x44D8
    // </layout:EnemyFuhiguruma>
};

