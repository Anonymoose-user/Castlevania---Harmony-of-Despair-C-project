// Dll/Enemy/Fcmummy/EnemyFcmummy.h - dllfcmummy, the mummy of the FC enemy set
// (object 0x4578 bytes). Names are inferred; the state
// names describe what each state does.
//
// States (m_state): 0 start (goes to 1), 1 / 2 decide (pick a label to walk
// to, a walk time and a direction), 7 move (to the spot the decision or a
// received message planned), 3 walk (turning at walls and ledges), 4 turn and
// throw, 5 throw (one bandage, three with +0x230), 6 die.
//
// In multiplayer (+0x440A) one instance decides (+0x4408 set) and sends each
// decision as a message (m_msgId.., sendMove); the others receive them
// through slot +0x150 into m_msgs (guarded by an system mutex) and replay them.
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

#include <list>


// The game's mutex wrapper (vtable, 0x38 with the
// alignment; the constructor and lock / unlock are inlined).
class EnemyFcmummyMutex {
public:
    EnemyFcmummyMutex()
    {
        DLL_MUTEX_CREATE();
    }
    virtual ~EnemyFcmummyMutex();
    int lock() { return DLL_MUTEX_LOCK(); }
    int unlock() { return DLL_MUTEX_UNLOCK(); }

    DLL_MUTEX_FIELD
};

// One move message (0x14 bytes; std::list node 0x1C), the same five words as
// EnemyFcmummy::m_msgId..m_msgNext.
struct FcmummyMsg {
    unsigned int id;                 // +0x00 sender (+0x440C)
    unsigned int time;               // +0x04 send time in ms
    unsigned int pos;                // +0x08 packPos of the start
    int dist;                        // +0x0C walk time in ms, negative walking left
    int next;                        // +0x10 state after the move
};
typedef std::list<FcmummyMsg, DllAllocator<FcmummyMsg> > FcmummyMsgList;

// Member layout of EnemyFcmummy's own fields: the  layout dump.
class EnemyFcmummy : public EnemyObjBase {
public:
    EnemyFcmummy();
    virtual ~EnemyFcmummy();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014
    virtual void v018();                         // +0x018
    virtual void v01C(float dt);                 // +0x01C (empty)
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const void* v09C();                          // +0x09C the address of m_i44EC
    virtual int onMessage(int a, const int* msg);   // +0x150 queues a received move message
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcmummy)
    void startMotion0();
    void faceDir();
    void setBoxes26A();
    void setFacing(float f);
    void nop0968();
    void setState(int s);
    void stateMove(float dt);
    void stateDie();
    void fire();
    void stateThrow(float dt);
    void stateTurnThrow(float dt);
    void turnAround();
    bool isI258Clear();
    bool isWallAhead();
    bool canMove();
    void stateWalk(float dt);
    void sendMove();
    float dirToLabel(int label);
    int pickLabel();
    bool sameSide();
    void decide();
    void stateDecide2(float dt);
    void stateDecide1(float dt);
    void setState1();
    bool handleEvents();
    void faceTarget();
    void clearBoxes26AB();
    void clearB268m();
    void setMotionOff(bool off);

public:
    // <layout:EnemyFcmummy>
    int m_state;                                    // +0x44C0 0 start, 1 / 2 decide, 3 walk, 4 turn and throw, 5 throw, 6 die, 7 move to the planned spot
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 time in the state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_placed;                                  // +0x44D2 slot +0x018 has run its one-time set-up
    bool m_wake;                                    // +0x44D3 set by slot +0x080 (only cleared)
    bool m_hit;                                     // +0x44D4 set by slot +0x084
    unsigned char _pad44D5[0x3];
    int m_nextState;                                // +0x44D8 state after the move (state 7): 4 or 1
    int m_spawnArg;                                 // +0x44DC 12; spawn flags & 0xF, negated when any flag is set
    int m_i44E0;                                    // +0x44E0 -1
    int m_i44E4;                                    // +0x44E4
    float m_f44E8;                                  // +0x44E8 +0x1E8 at start
    int m_i44EC;                                    // +0x44EC slot +0x09C returns its address
    bool m_b44F0;                                   // +0x44F0 +0x040 at start
    unsigned char _pad44F1[0x3];
    float m_walkTime;                               // +0x44F4 how long the walk (state 3) lasts
    int m_label;                                    // +0x44F8 label the mummy walks toward (-1: none)
    unsigned int m_msgId;                           // +0x44FC move message: sender (+0x440C); the original game reads it at +0x4400
    unsigned int m_msgTime;                         // +0x4500 move message: send time in ms (+0x4498)
    unsigned int m_msgPos;                          // +0x4504 move message: packPos of the start
    int m_msgDist;                                  // +0x4508 move message: walk time in ms, negative walking left
    int m_msgNext;                                  // +0x450C move message: state after the move
    FcmummyMsgList m_msgs;                          // +0x4510 received move messages (slot +0x150)
    bool m_hasMsg;                                  // +0x451C a message was taken from m_msgs
    unsigned char _pad451D[0x3];
    float m_period;                                 // +0x4520 duration of the move (state 7)
    float m_moveFrom[2];                            // +0x4524
    float m_moveTo[2];                              // +0x452C
    float m_walkDir;                                // +0x4534 -1 / 1
    bool m_lerp;                                    // +0x4538 state 7 moves from m_moveFrom to m_moveTo
    unsigned char _pad4539[0x7];
    EnemyFcmummyMutex m_lock;                       // +0x4540 guards m_msgs
    // </layout:EnemyFcmummy>
};

