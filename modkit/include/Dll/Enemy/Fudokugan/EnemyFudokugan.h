// Dll/Enemy/Fudokugan/EnemyFudokugan.h - dllfudokugan, the poison eye (a
// mid-boss of the "Fu" enemy set;, object 0x4670 bytes).
// Names are inferred; the state names describe what each state does.
//
// It floats over the room, sends out two helper modules (DLL_FuKyokotsu and
// DLL_FuRyukibi, created through the original game callback +0x4474) whose link
// blocks it reads every frame, carries two parts (hit boxes 1 and 2) that
// come out one after the other, and shoots at a label. In online play the
// host instance (+0x4408) decides and sends each move as a message (slot
// +0x154 reads m_msgId..); the others receive them through slot +0x150.
//
// States (m_state): 0 set-up (measures the room, links the helpers), 1 wait,
// 2 hidden, 3 appear (bubbles), 4 float (bobbing, shooting), 5 swoop
// (back and forth, shooting forward), 6 die, 7 glide (to m_moveTo, then
// m_nextState).
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

#include <list>


// The game's mutex wrapper (vtable, 0x38 with the
// alignment; the constructor and lock / unlock are inlined).
class EnemyFudokuganMutex {
public:
    EnemyFudokuganMutex()
    {
        DLL_MUTEX_CREATE();
    }
    virtual ~EnemyFudokuganMutex();
    int lock() { return DLL_MUTEX_LOCK(); }
    int unlock() { return DLL_MUTEX_UNLOCK(); }

    DLL_MUTEX_FIELD
};

// A label message (8 bytes; std::list node 0x10).
struct FudokuganLblMsg {
    unsigned int id;                 // +0x00
    unsigned int bits;               // +0x04 kind (0..3), label index (4..7)
};
// A move message (16 bytes; std::list node 0x18).
struct FudokuganMoveMsg {
    unsigned int id;                 // +0x00
    unsigned int bits;               // +0x04 kind (0..3), facing right (4), bit 31
    float time;                      // +0x08 m_f4498 of the sender
    unsigned int pos;                // +0x0C packPos
};
typedef std::list<FudokuganLblMsg, DllAllocator<FudokuganLblMsg> > FudokuganLblMsgList;
typedef std::list<FudokuganMoveMsg, DllAllocator<FudokuganMoveMsg> > FudokuganMoveMsgList;

// The helper modules' link block the original game hands out (getU4480): read only.
struct FudokuganLink {
    bool b0;                         // +0x00 the helper is ready
    bool b1;                         // +0x01
    float pos[2];                    // +0x04
};

// Member layout of EnemyFudokugan's own fields: the  layout dump.
class EnemyFudokugan : public EnemyObjBase {
public:
    EnemyFudokugan();
    virtual ~EnemyFudokugan();

    // overridden slots
    virtual void v008();                         // +0x008 spawns two default shot requests
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018
    virtual void v01C(float dt);                 // +0x01C reads the helpers' link blocks
    virtual void update(float dt);               // +0x020
    virtual void v024(const int* a, void* b, bool c);   // +0x024 drags another object along (state 3)
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                       // +0x080
    virtual void v084(int part);                       // +0x084 hit: go to the die state
    virtual const void* v09C();                  // +0x09C the address of m_b457C
    virtual int onMessage(int a, const int* msg);   // +0x150 queues a received message
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfudokugan)
    void setFacing(float f);
    void fireAt(float x, float y);
    void spawnSpark(EnemyVec2 p, EnemyVec2 v);
    void updateParts(float dt);
    void place(float dt);
    void setState(int s);
    void stateGlide(float dt);
    void stateDie(float dt);
    void sendMove(unsigned int kind);
    void collectLabels(EnemyIntList* out);
    void pickLabel();
    bool sameSide();
    void think(float dt);
    void fireFwd();
    void stateSwoop(float dt);
    void bob(float dt);
    void checkSwoop(float dt);
    void fireAtLabel();
    void stateFloat(float dt);
    void spawnBubble();
    void stateAppear(float dt);
    void stateHidden(float dt);
    void stateWait(float dt);
    void stateSetup();
    bool handleEvents();
    void turnAround();
    void faceTarget();

public:
    // <layout:EnemyFudokugan>
    int m_state;                                    // +0x44C0 0 set-up, 1 wait, 2 hidden, 3 appear, 4 float, 5 swoop, 6 die, 7 glide
    int m_phase;                                    // +0x44C4 step inside the state
    float m_timer;                                  // +0x44C8 time in the phase
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_wake;                                    // +0x44D2 set by slot +0x080, cleared every frame
    bool m_hit;                                     // +0x44D3 set by slot +0x084
    int m_eyeDir;                                   // +0x44D4 hit box 0's i30 while looking at the label (2 after construction)
    float m_lookTimer;                              // +0x44D8 0.3 after construction
    float m_spawnPos[2];                            // +0x44DC where the bubbles start (state 0)
    float m_blend;                                  // +0x44E4 state 3: 0..1, slot +0x024 blends with it
    float m_base[2];                                // +0x44E8 position without the bobbing
    float m_off[2];                                 // +0x44F0 bobbing offset (position = m_base + m_off)
    float m_bobPhase;                               // +0x44F8 0..1.5 s
    int m_i44FC;                                    // +0x44FC -1 after construction
    int m_count;                                    // +0x4500 state 3: bubbles spawned
    bool m_labelPending;                            // +0x4504 a label to shoot at was chosen
    unsigned char _pad4505[0x3];
    int m_labelIdx;                                 // +0x4508 index of that label (99: none)
    unsigned int m_prevMotion;                      // +0x450C hit box 0's u08 last frame
    float m_allDoneTimer;                           // +0x4510 time since both parts are out
    float m_swoopTimer;                             // +0x4514 time left before the swoop
    bool m_swoopGo;                                 // +0x4518
    bool m_swoopPending;                            // +0x4519
    unsigned char _pad451A[0x2];
    float m_saveOff[2];                             // +0x451C state 5: offset at the start
    float m_shotTimer;                              // +0x4524 state 5: time since the last shot
    unsigned char m_partsDone;                      // +0x4528 parts that have come out
    bool m_partsActive;                             // +0x4529 the two parts are running
    unsigned char _pad452A[0x2];
    int m_aState;                                   // +0x452C part A (hit box 1): 0 wait, 1 linked, 2 sparking, 3 out, 4 following
    float m_aTimer;                                 // +0x4530
    float m_aPos[2];                                // +0x4534
    float m_aOff[2];                                // +0x453C
    float m_aSparkTimer;                            // +0x4544
    int m_aSparks;                                  // +0x4548
    int m_bState;                                   // +0x454C part B (hit box 2), the same fields
    float m_bTimer;                                 // +0x4550
    float m_bPos[2];                                // +0x4554
    float m_bOff[2];                                // +0x455C
    float m_bSparkTimer;                            // +0x4564
    int m_bSparks;                                  // +0x4568
    float m_minX;                                   // +0x456C room bounds found in state 0
    float m_maxX;                                   // +0x4570
    float m_top;                                    // +0x4574
    float m_bottom;                                 // +0x4578
    bool m_b457C;                                   // +0x457C set when dying; slot +0x09C returns its address
    bool m_haveRyukibi;                             // +0x457D the second helper module was linked
    unsigned char _pad457E[0x2];
    float m_f4580[2];                               // +0x4580 slot +0x018 copies the position here
    uintptr_t    m_link0;                           // +0x4588 original game address of the first helper's link block (getU4480)
    uintptr_t    m_link1;                           // +0x458C the second helper's
    bool m_l0b0;                                    // +0x4590 copy of the first link block (slot +0x01C)
    bool m_l0b1;                                    // +0x4591
    unsigned char _pad4592[0x2];
    float m_l0pos[2];                               // +0x4594
    bool m_l1b0;                                    // +0x459C copy of the second link block
    bool m_l1b1;                                    // +0x459D
    unsigned char _pad459E[0x2];
    float m_l1pos[2];                               // +0x45A0
    int m_retry;                                    // +0x45A8 state 0: frames waited for a helper
    unsigned int m_lblMsgId;                        // +0x45AC outgoing label message (8 bytes)
    unsigned int m_lblMsgBits;                      // +0x45B0
    FudokuganLblMsgList m_lblMsgs;                  // +0x45B4 received label messages (bit 31 clear)
    unsigned int m_msgId;                           // +0x45C0 outgoing move message (16 bytes)
    unsigned int m_msgBits;                         // +0x45C4 kind (0..3), facing right (4), bit 31
    float m_msgTime;                                // +0x45C8
    unsigned int m_msgPos;                          // +0x45CC packPos
    FudokuganMoveMsgList m_moveMsgs;                // +0x45D0 received move messages (bit 31 set)
    bool m_sent;                                    // +0x45DC a move message went out this frame (slot +0x01C clears it)
    unsigned char _pad45DD[0x3];
    float m_moveTime;                               // +0x45E0 state 7
    float m_moveFacing;                             // +0x45E4
    float m_moveTo[2];                              // +0x45E8
    float m_moveFrom[2];                            // +0x45F0
    int m_nextState;                                // +0x45F8 state 7 goes on to it (3 after construction)
    bool m_poll;                                    // +0x45FC think() reads the move messages
    unsigned char _pad45FD[0x3];
    EnemyFudokuganMutex m_lblLock;                  // +0x4600 guards m_lblMsgs
    EnemyFudokuganMutex m_moveLock;                 // +0x4638 guards m_moveMsgs
    // </layout:EnemyFudokugan>
};

