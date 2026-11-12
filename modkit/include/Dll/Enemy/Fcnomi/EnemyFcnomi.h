// Dll/Enemy/Fcnomi/EnemyFcnomi.h - dllfcnomi, the flea man ("nomi") of the
// Famicom-style ("FC") enemy set (object 0x4598 bytes).
// Alone it hops at the player; with spawn flag 1 an eagle ("DLL_FCaltair")
// carries it and drops it; with spawn flag 0x10 it is Igor, Frankenstein's
// companion ("DLL_FCfranc"), riding him and jumping off to throw fireballs.
// Names are inferred; the state names describe what each state does.
//
// States (m_state), alone: 0 wait (until the player is near), 1 crouch,
// 2 big hop, 3 small hop, 4 carried by the eagle, 5 fall (until on the
// ground), 6 die; with Frankenstein: 7 wait for him, 8 ride, 9 on the ground,
// 10 jump and throw, 11 hurt pause, 12 glide (to m_moveTo, then
// m_nextState).
//
// In online play (+0x440A set) the host instance (+0x4408 set) decides each
// glide and sends it as a 20-byte message (m_msgId.., read by the original game
// through slot +0x154); the other instances get it through slot +0x150 into
// m_msgs (guarded by an system mutex) and replay it.
//
// The original game objects are reached through host callbacks that take 32-bit
// pointers (the name, a position, out-parameters) and through a record
// pointer from slot +0x49C (m_francRec); the record pointer is pointer-sized
// natively.
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

#include <list>


// The game's mutex wrapper (vtable, 0x38 with the
// alignment; the constructor and lock / unlock are inlined).
class EnemyFcnomiMutex {
public:
    EnemyFcnomiMutex()
    {
        DLL_MUTEX_CREATE();
    }
    virtual ~EnemyFcnomiMutex();
    int lock() { return DLL_MUTEX_LOCK(); }
    int unlock() { return DLL_MUTEX_UNLOCK(); }

    DLL_MUTEX_FIELD
};

// One glide message (20 bytes; std::list node 0x1C).
struct FcnomiMsg {
    unsigned int id;                 // +0x00 EnemyObjBase::m_s440C of the sender
    unsigned int time;               // +0x04 EnemyObjBase::m_f4498 in ms
    unsigned int pos;                // +0x08 packPos of the position
    int label;                       // +0x0C the sender's target label
    unsigned int bits;               // +0x10 see EnemyFcnomi::sendMove
};
typedef std::list<FcnomiMsg, DllAllocator<FcnomiMsg> > FcnomiMsgList;

// Member layout of EnemyFcnomi's own fields: the  layout dump.
class EnemyFcnomi : public EnemyObjBase {
public:
    EnemyFcnomi();
    virtual ~EnemyFcnomi();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014 1: on the eagle, 0x10: with Frankenstein
    virtual void v018();                         // +0x018 places it on the ground once
    virtual void v01C(float dt);                 // +0x01C follows the eagle / Frankenstein
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual int onMessage(int a, const int* msg);   // +0x150 queues a received message
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcnomi)
    void setState(int s);
    void startMotion0();
    void setV238();
    void setV240();
    void setBoxes26A();
    void setFacing(float f);
    void linkEagle();
    void clearB268();
    void clearB269();
    void clearB26AB();
    void stateDie();
    void stateGlide(float dt);
    void setMotionOff(bool off);
    void stateHurt(float dt);
    void turnAround();
    bool isWallAhead();
    bool sideTimer(float dt);
    bool onGround();
    void fire();
    void stateThrow(float dt);
    void sendMove();
    int findTarget();
    bool playerNear();
    void think(float dt);                        // (dt unused)
    void stateGround(float dt);
    void stateRide(float dt);
    void stateWaitFranc(float dt);
    bool handleEvents();
    void updateFranc(float dt);
    void nop2AEC();
    void stateFall();
    bool canLand();
    bool playerBelow();
    void stateCarried();
    bool sameSide();
    bool keepChasing(float dt);
    void faceTarget();
    void stateSmallHop(float dt);
    void stateBigHop(float dt);
    bool playerClose();
    void stateCrouch(float dt);
    void stateWait(float dt);
    void updateAlone(float dt);
    bool isWallAhead2();
    bool isI258Set();

public:
    // <layout:EnemyFcnomi>
    int m_state;                                    // +0x44C0 alone 0..6, with Frankenstein 6..12 (see the header)
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 time in the state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_placed;                                  // +0x44D2 slot +0x018 has moved it onto the ground once
    bool m_wake;                                    // +0x44D3 set by slot +0x080
    bool m_hit;                                     // +0x44D4 set by slot +0x084
    unsigned char _pad44D5[0x3];
    float m_turnTimer;                              // +0x44D8 state 10: time before it may turn to the player again
    float m_home[2];                                // +0x44DC position on entering state 7
    bool m_onEagle;                                 // +0x44E4 spawn flag 1: carried by an eagle (the original game object "DLL_FCaltair")
    unsigned char _pad44E5[0x3];
    int m_eagleId;                                  // +0x44E8 the eagle found through host callback +0x4474
    float m_eaglePos[2];                            // +0x44EC its position (host callback +0x4478)
    float m_prevTarget[2];                          // +0x44F4 m_selfPos before following the eagle
    bool m_keepFacing;                              // +0x44FC the next hop keeps the facing
    bool m_turnNext;                                // +0x44FD the next hop turns around (landed at a wall)
    bool m_smallHop;                                // +0x44FE the next hop is a small one (state 3)
    unsigned char _pad44FF[0x1];
    float m_lostTimer;                              // +0x4500 time the player has been on the other side
    int m_targetLabel;                              // +0x4504 label chased (-1: none)
    bool m_withFranc;                               // +0x4508 spawn flag 0x10: Igor, Frankenstein's companion
    bool m_hurt;                                    // +0x4509 hurt (blinks, no shots; set when +0x1E8 < +0x1EC)
    unsigned char _pad450A[0x2];
    int m_nextState;                                // +0x450C state 12 goes on to it (13 after construction)
    bool m_blink;                                   // +0x4510 hit box shown every other frame while m_hurt
    unsigned char _pad4511[0x3];
    float m_shotTimer;                              // +0x4514 state 10: time since the last shot
    uintptr_t    m_francRec;                        // +0x4518 Frankenstein's record (a pointer from slot +0x49C)
    int m_francId;                                  // +0x451C Frankenstein ("DLL_FCfranc", host callback +0x4474), -1: none
    unsigned int m_msgId;                           // +0x4520 the outgoing / current message (20 bytes, slot +0x154)
    unsigned int m_msgTime;                         // +0x4524 EnemyObjBase::m_f4498 in ms
    unsigned int m_msgPos;                          // +0x4528 packPos
    int m_msgLabel;                                 // +0x452C m_targetLabel of the sender
    unsigned int m_msgBits;                         // +0x4530 bits 0..3 m_nextState, 4 facing right
    FcnomiMsgList m_msgs;                           // +0x4534 received messages (slot +0x150)
    bool m_hasMsg;                                  // +0x4540 a message was taken from m_msgs
    unsigned char _pad4541[0x3];
    float m_glideTime;                              // +0x4544 state 12 duration
    float m_moveFrom[2];                            // +0x4548
    float m_moveTo[2];                              // +0x4550
    float m_moveFacing;                             // +0x4558
    bool m_lerp;                                    // +0x455C state 12 moves from m_moveFrom to m_moveTo
    unsigned char _pad455D[0x3];
    EnemyFcnomiMutex m_lock;                        // +0x4560 guards m_msgs
    // </layout:EnemyFcnomi>
};

