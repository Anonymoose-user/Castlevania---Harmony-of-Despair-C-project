// Dll/Enemy/Fcdeath/EnemyFcdeath.h - dllfcdeath, Death, the boss of the
// Famicom-style ("FC") enemy set (object 0x45E8 bytes).
// Names are inferred; the state names describe what each state does.
//
// States (m_state): 0 probe (moves its position in 16-unit steps to find the
// room's walls), 1 wait (until the player comes near), 2 appear (flickers in,
// rising), 3 fight (throws sickles, picks the next move), 4 swoop, 5 die,
// 6 glide (to m_moveTo, then m_nextState).
//
// In online play (+0x440A set) the host instance decides and sends each move
// as a 16-byte message (m_msgId.., read by the original game through slot +0x154);
// the other instances (+0x4408 clear) get them through slot +0x150 into
// m_glideMsgs and replay them. Sickles go through m_sickleMsgs on every
// instance. Both lists are guarded by an system mutex.
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

#include <list>


// The game's mutex wrapper (vtable, 0x38 with the
// alignment; the constructor and lock / unlock are inlined).
class EnemyFcdeathMutex {
public:
    EnemyFcdeathMutex()
    {
        DLL_MUTEX_CREATE();
    }
    virtual ~EnemyFcdeathMutex();
    int lock() { return DLL_MUTEX_LOCK(); }
    int unlock() { return DLL_MUTEX_UNLOCK(); }

    DLL_MUTEX_FIELD
};

// One message (16 bytes; std::list node 0x18).
struct FcdeathMsg {
    unsigned int id;                 // +0x00 EnemyObjBase::m_s440C of the sender
    float time;                      // +0x04 when (m_f4498, or m_clock + 1 for a sickle)
    unsigned int pos;                // +0x08 packPos
    unsigned int bits;               // +0x0C see EnemyFcdeath::sendMove
};
typedef std::list<FcdeathMsg, DllAllocator<FcdeathMsg> > FcdeathMsgList;

// Member layout of EnemyFcdeath's own fields: the  layout dump.
class EnemyFcdeath : public EnemyObjBase {
public:
    EnemyFcdeath();
    virtual ~EnemyFcdeath();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014 (empty)
    virtual void v018();                         // +0x018 clears m_busy
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                       // +0x080
    virtual void v084(int part);                       // +0x084 hit: go to the die state
    virtual int onMessage(int a, const int* msg);   // +0x150 queues a received message
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcdeath)
    void startMotion0();
    void setV238();
    void setMotionOff(bool off);
    void setFacing(float f);
    void nop080C();
    void setState(int s);
    void fire(EnemyVec2 at);
    void updateSickles(float dt);
    void stateGlide(float dt);
    void clearB268x();
    void stateDie();
    bool onGround();
    void stateSwoop(float dt);
    void sendMove(unsigned int angle);
    int angleOf(const EnemyVec2* v);
    void dirTo(EnemyVec2* out, const EnemyVec2* p);
    void dirToLabel(EnemyVec2* out, int id);
    int findTarget();
    bool targetNear();
    void think();
    void stateFight(float dt);
    void stateAppear(float dt);
    void stateWait();
    void stateProbe();
    bool handleEvents();

public:
    // <layout:EnemyFcdeath>
    int m_state;                                    // +0x44C0 0 probe, 1 wait, 2 appear, 3 fight, 4 swoop, 5 die, 6 glide
    int m_prevState;                                // +0x44C4
    int m_probeStep;                                // +0x44C8 state 0: 0 down, 1 up, 2 right, 3 left, 4 done
    float m_timer;                                  // +0x44CC time in the state
    float m_facing;                                 // +0x44D0 -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D4 the state has run its entry code
    bool m_dead;                                    // +0x44D5
    bool m_wake;                                    // +0x44D6 set by slot +0x080, cleared every frame
    bool m_hit;                                     // +0x44D7 set by slot +0x084
    bool m_blink;                                   // +0x44D8 state 2: body hit box shown every other frame
    unsigned char _pad44D9[0x3];
    int m_nextState;                                // +0x44DC state 6 goes on to it (7 after construction)
    float m_probeStart[2];                          // +0x44E0 position state 0 starts from
    bool m_inRoom;                                  // +0x44E8 the room bounds were measured (true after construction)
    unsigned char _pad44E9[0x3];
    float m_roomBottom;                             // +0x44EC
    float m_roomTop;                                // +0x44F0
    float m_roomRight;                              // +0x44F4
    float m_roomLeft;                               // +0x44F8
    float m_roomCenterX;                            // +0x44FC
    float m_roomCenterY;                            // +0x4500
    float m_swoopDir;                               // +0x4504 -1 / 1: side of the last swoop
    float m_dirX;                                   // +0x4508 cosine of the swoop angle
    float m_dirY;                                   // +0x450C sine of the swoop angle
    float m_swoopTime;                              // +0x4510 state 4 without room bounds: flight time
    int m_i4514;                                    // +0x4514
    int m_i4518;                                    // +0x4518
    int m_moveKind;                                 // +0x451C sent in the glide message (bits 20..23)
    float m_sickleTimer;                            // +0x4520 time since the last sickle
    float m_clock;                                  // +0x4524 0..60 s, stamps the sickle messages
    bool m_fighting;                                // +0x4528 state 3 was entered: sickles are thrown
    unsigned char _pad4529[0x3];
    int m_targetLabel;                              // +0x452C label chased (-1: none)
    unsigned int m_msgId;                           // +0x4530 the outgoing / current message (16 bytes, slot +0x154)
    float m_msgTime;                                // +0x4534
    unsigned int m_msgPos;                          // +0x4538 packPos
    unsigned int m_msgBits;                         // +0x453C angle, next state, kind, facing, room flag; bit 31: a sickle
    FcdeathMsgList m_glideMsgs;                     // +0x4540 received glide messages (onMessage, bit 31 clear)
    FcdeathMsgList m_sickleMsgs;                    // +0x454C sickles to throw (bit 31 set)
    bool m_hasMsg;                                  // +0x4558 a glide message was taken from m_glideMsgs
    unsigned char _pad4559[0x3];
    float m_moveTime;                               // +0x455C state 6 duration
    float m_moveFrom[2];                            // +0x4560
    float m_moveTo[2];                              // +0x4568
    float m_moveFacing;                             // +0x4570
    bool m_moveInRoom;                              // +0x4574 m_inRoom after the glide
    bool m_busy;                                    // +0x4575 a glide / sickle is pending (cleared by slot +0x018)
    bool m_lerp;                                    // +0x4576 state 6 moves from m_moveFrom to m_moveTo
    unsigned char _pad4577[0x1];
    EnemyFcdeathMutex m_glideLock;                  // +0x4578 guards m_glideMsgs
    EnemyFcdeathMutex m_sickleLock;                 // +0x45B0 guards m_sickleMsgs
    // </layout:EnemyFcdeath>
};

