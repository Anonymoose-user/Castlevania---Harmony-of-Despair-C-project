// Dll/Enemy/Furyukibi/EnemyFuryukibi.h - dllfuryukibi ("DLL_FuRyukibi",
// object 0x45E8 bytes): the Getsu Fuma Den dragon-skull
// boss. It spawns its two heads (DLL_FuKyokotsu / DLL_FuDokugan, through the
// host callback +0x4474), hovers between the room bounds it measures with the
// wall probes, and picks attacks: move to one of 16 slots, sink and reappear
// upside down, charge across, dash and fire a ring. In multiplayer (+0x440A)
// one instance decides (+0x4408) and sends each choice as a message
// (m_msg, sendMsg); the others receive them through slot +0x150 into m_msgs
// (guarded by an system mutex). Names are inferred.
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

#include <list>

// The game's mutex wrapper (vtable; the constructor
// and lock / unlock are inlined).
class EnemyFuryukibiMutex {
public:
    EnemyFuryukibiMutex()
    {
        DLL_MUTEX_CREATE();
    }
    virtual ~EnemyFuryukibiMutex();
    int lock() { return DLL_MUTEX_LOCK(); }
    int unlock() { return DLL_MUTEX_UNLOCK(); }

    DLL_MUTEX_FIELD
};

// One decision message (0x0C bytes; std::list node 0x14): m_msg's words.
struct FuryukibiMsg {
    unsigned int id;                 // +0x00 sender (+0x440C)
    unsigned int kind;               // +0x04 low nibble the attack, next nibble its argument
    float time;                      // +0x08 send time (+0x4498)
};
typedef std::list<FuryukibiMsg, DllAllocator<FuryukibiMsg> > FuryukibiMsgList;

// What the original game exposes of a head object (getU4480 hands out its address).
struct FuryukibiChild {
    bool ready;                      // +0x00
    bool b01;                        // +0x01
    float x, y;                      // +0x04
};

// Member layout of EnemyFuryukibi's own fields: the  layout dump.
class EnemyFuryukibi : public EnemyObjBase {
public:
    EnemyFuryukibi();
    virtual ~EnemyFuryukibi();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 remembers the position
    virtual void v01C(float dt);                 // +0x01C copies the heads' state
    virtual void update(float dt);               // +0x020
    virtual void v024(const int* a, void* b, bool c); // +0x024 squashes the sprite (state 5)
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const void* v09C();                          // +0x09C the address of m_b4560
    virtual int onMessage(int a, const int* msg);   // +0x150 queues a received decision
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfuryukibi)
    void startMotion0();
    void setFacing(float f);
    void fireAt(float x, float y);
    void fireHeadShot(EnemyVec2 pos, EnemyVec2 vel);
    void updateHeads(float dt);
    void fireLow();
    void fireHigh();
    void autoFire(float dt);
    void autoFireAndHeads(float dt);
    void setState(int s);
    void stateWait(float dt);
    void stateDie(float dt);
    void fireRing(int i);
    void stateDash(float dt);
    void stateCharge(float dt);
    void stateSink(float dt);
    void stateSlot(float dt);
    void sendMsg(unsigned int kind);
    bool sameRoom();
    void decide();
    void stateDecide3();
    void stateRise(float dt);
    void stateDecide1();
    void stateSetup();
    bool handleEvents();
    void turnAround();

public:
    // <layout:EnemyFuryukibi>
    int m_state;                                    // +0x44C0 0 set up, 1 / 3 decide, 2 rise, 4 move to a slot, 5 sink and reappear, 6 charge, 7 dash and fire a ring, 8 die, 9 wait (m_waitTime) then m_nextState
    int m_step;                                     // +0x44C4 step inside the state
    float m_timer;                                  // +0x44C8 time in the step
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_wake;                                    // +0x44D2 set by slot +0x080
    bool m_hit;                                     // +0x44D3 set by slot +0x084
    float m_vdir;                                   // +0x44D4 1 / -1: upright or upside down (state 5 flips it)
    int m_burstCount;                               // +0x44D8 explosions in the die state
    float m_savedPos[2];                            // +0x44DC
    float m_baseY;                                  // +0x44E4 floor height of the hover
    int m_slot;                                     // +0x44E8 slot 0..15 state 4 moves to
    float m_goalX;                                  // +0x44EC x of that slot
    float m_fireTimer;                              // +0x44F0
    bool m_autoFire;                                // +0x44F4 fire every 2 s
    bool m_fireOk;                                  // +0x44F5
    unsigned char _pad44F6[0x2];
    float m_boundL;                                 // +0x44F8 room bounds (state 0)
    float m_boundR;                                 // +0x44FC
    bool m_side;                                    // +0x4500 the charge / dash starts on the left
    unsigned char _pad4501[0x3];
    int m_ringIdx;                                  // +0x4504 ring shots fired (state 7)
    int m_pattern;                                  // +0x4508 attack counter for the second phase
    unsigned char m_kills;                          // +0x450C heads destroyed
    bool m_headsOn;                                 // +0x450D the two heads are active
    unsigned char _pad450E[0x2];
    int m_h1State;                                  // +0x4510 head 1: 0..2 wait / fire, 3 dying, 4 dead
    float m_h1Timer;                                // +0x4514
    float m_h1Pos[2];                               // +0x4518
    float m_h1Off[2];                               // +0x4520
    float m_h1ShotTimer;                            // +0x4528
    int m_h1Shots;                                  // +0x452C
    int m_h2State;                                  // +0x4530 head 2, as head 1
    float m_h2Timer;                                // +0x4534
    float m_h2Pos[2];                               // +0x4538
    float m_h2Off[2];                               // +0x4540
    float m_h2ShotTimer;                            // +0x4548
    int m_h2Shots;                                  // +0x454C
    float m_slotMin;                                // +0x4550 slot range
    float m_slotMax;                                // +0x4554
    float m_roomTop;                                // +0x4558
    float m_roomBottom;                             // +0x455C
    bool m_b4560;                                   // +0x4560 slot +0x09C hands out its address
    bool m_b4561;                                   // +0x4561
    unsigned char _pad4562[0x2];
    float m_lastPos[2];                             // +0x4564 slot +0x018
    FuryukibiChild* m_child1;                       // +0x456C head objects from the original game (getU4480)
    FuryukibiChild* m_child2;                       // +0x4570
    bool m_c1Ready;                                 // +0x4574 copy of head 1's state (slot +0x01C)
    bool m_c1B1;                                    // +0x4575
    unsigned char _pad4576[0x2];
    float m_c1Pos[2];                               // +0x4578
    bool m_c2Ready;                                 // +0x4580 copy of head 2's state
    bool m_c2B1;                                    // +0x4581
    unsigned char _pad4582[0x2];
    float m_c2Pos[2];                               // +0x4584
    int m_retry;                                    // +0x458C
    unsigned int m_msg[3];                          // +0x4590 message the original game sends (+0x4400)
    FuryukibiMsgList m_msgs;                        // +0x459C received messages (slot +0x150)
    float m_waitTime;                               // +0x45A8 state 9
    int m_nextState;                                // +0x45AC state 9
    EnemyFuryukibiMutex m_lock;                     // +0x45B0 guards m_msgs
    // </layout:EnemyFuryukibi>
};

