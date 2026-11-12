// Dll/Enemy/Fcfranc/EnemyFcfranc.h - dllfcfranc, Frankenstein's monster of
// the Famicom-style ("FC") enemy set (object 0x4570
// bytes). Names are inferred; the state names describe what each state does.
//
// States (m_state): 0 start, 1 and 2 decide (pick the next move: walk or
// charge, at the nearest label), 3 walk, 4 charge, 5 die, 6 leap (the move
// every decision starts with; it then goes to m_nextState).
//
// In an online game (+0x440A) the host side (+0x4408) decides and sends each
// decision as a 16-byte message (m_msg, handed out through +0x4400 / +0x4404);
// the other side receives them through slot +0x150 into m_msgs (guarded by a
// kernel mutex) and replays them.
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

#include <list>

// One sync message (16 bytes, the elements of EnemyFcfranc::m_msgs).
struct FrancMsg {
    unsigned int w[4];
};
typedef std::list<FrancMsg, DllAllocator<FrancMsg> > FrancMsgList;

// A recursive mutex owned by an object (vtable ). The
// constructor, lock() and unlock() are inlined everywhere.
class FrancMutex {
public:
    FrancMutex();
    virtual ~FrancMutex();
    int lock();
    int unlock();

    DLL_MUTEX_FIELD
};

// Member layout of EnemyFcfranc's own fields: the  layout dump.
class EnemyFcfranc : public EnemyObjBase {
public:
    EnemyFcfranc();
    virtual ~EnemyFcfranc();

    // overridden slots
    virtual void v008();                         // +0x008 empty
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014 empty
    virtual void v018();                         // +0x018
    virtual void v01C(float dt);                 // +0x01C
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const void* v09C();                          // +0x09C &m_b44F4
    virtual int onMessage(int a, const int* msg); // +0x150 queues a sync message
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcfranc)
    void startMotion0();
    void faceDir();
    void setBoxes26A();
    void setFacing(float f);
    void nop0930();
    void setState(int s);
    void stateLeap(float dt);
    void stateDie();
    bool isFloorGone();
    bool isWallAhead();
    bool mustTurn();
    void stateCharge(float dt);
    void stateWalk(float dt);
    void sendSync();
    float dirToLabel(int id, float* dist);
    int findTarget();
    bool isSameSide();
    void decide();
    void stateDecide2();
    void stateDecide1();
    void toState1();
    bool handleEvents();
    void turnAround();
    void faceTarget();
    void clearB26AB();
    void clearB268();
    void probe449C();
    void setMotionB1C(bool off);

public:
    // <layout:EnemyFcfranc>
    int m_state;                                    // +0x44C0 0 start, 1/2 decide, 3 walk, 4 charge, 5 die, 6 leap
    int m_prevState;                                // +0x44C4
    int m_phase;                                    // +0x44C8 state 4: 0 wind-up, 1 charging
    float m_timer;                                  // +0x44CC time in the state
    float m_facing;                                 // +0x44D0 -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D4 the state has run its entry code
    bool m_dead;                                    // +0x44D5
    bool m_landed;                                  // +0x44D6 slot +0x018 has run once on the ground
    bool m_wake;                                    // +0x44D7 set by slot +0x080, cleared every frame
    bool m_hit;                                     // +0x44D8 set by slot +0x084
    unsigned char _pad44D9[0x3];
    int m_nextState;                                // +0x44DC state after the leap (7 after construction)
    float m_walkTime;                               // +0x44E0 how long state 3 walks
    float m_moveDir;                                // +0x44E4 walking direction
    int m_turnCount;                                // +0x44E8 walks that turned away from a close label in a row (< 3)
    int m_walkCount;                                // +0x44EC walks in a row (< 7)
    int m_labelId;                                  // +0x44F0 label chased (-1: none)
    bool m_b44F4;                                   // +0x44F4 slot +0x01C copies slot +0x088 here; slot +0x09C returns its address
    unsigned char _pad44F5[0x3];
    float m_f44F8;                                  // +0x44F8 slot +0x264 at start
    unsigned int m_msg[4];                          // +0x44FC the sync message: +0x440C, time * 1000, packed position, state / time / direction bits
    FrancMsgList m_msgs;                            // +0x450C messages received (slot +0x150), under m_mutex
    bool m_hasMsg;                                  // +0x4518 m_msg holds a received message not yet acted on
    unsigned char _pad4519[0x3];
    float m_moveTime;                               // +0x451C leap duration
    float m_from[2];                                // +0x4520 leap start
    float m_to[2];                                  // +0x4528 leap end
    float m_faceDir;                                // +0x4530 facing for the leap
    bool m_lerp;                                    // +0x4534 the leap moves the position (the received end is 8 or more away)
    unsigned char _pad4535[0x3];
    FrancMutex m_mutex;                             // +0x4538
    // </layout:EnemyFcfranc>
};

