// Dll/Enemy/Fcmedusa/EnemyFcmedusa.h - dllfcmedusa, Medusa, a boss of the
// Famicom-style ("FC") enemy set (object 0x4580 bytes).
// Names are inferred; the state names describe what each state does.
//
// States (m_state): 0 idle (until the player comes near), 1 wait (picks the
// next glide), 2 shoot (snake shots after 1 s) then drift, 3 die, 4 glide
// (to m_moveTo, then state 2). The body bobs up and down all the time.
//
// In online play (+0x440A set) the host instance (+0x4408 set) picks each
// glide and sends it as a 20-byte message (m_msgId.., read by the original game
// through slot +0x154); the other instances get it through slot +0x150 into
// m_msgs (guarded by an system mutex) and replay it.
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

#include <list>


// The game's mutex wrapper (vtable, 0x38 with the
// alignment; the constructor and lock / unlock are inlined).
class EnemyFcmedusaMutex {
public:
    EnemyFcmedusaMutex()
    {
        DLL_MUTEX_CREATE();
    }
    virtual ~EnemyFcmedusaMutex();
    int lock() { return DLL_MUTEX_LOCK(); }
    int unlock() { return DLL_MUTEX_UNLOCK(); }

    DLL_MUTEX_FIELD
};

// One glide message (20 bytes; std::list node 0x1C).
struct FcmedusaMsg {
    unsigned int id;                 // +0x00 EnemyObjBase::m_s440C of the sender
    float time;                      // +0x04 EnemyObjBase::m_f4498 when sent
    unsigned int pos;                // +0x08 packPos of the position
    float phase;                     // +0x0C the sender's bobbing phase
    unsigned int bits;               // +0x10 see EnemyFcmedusa::sendMove
};
typedef std::list<FcmedusaMsg, DllAllocator<FcmedusaMsg> > FcmedusaMsgList;

// Member layout of EnemyFcmedusa's own fields: the  layout dump.
class EnemyFcmedusa : public EnemyObjBase {
public:
    EnemyFcmedusa();
    virtual ~EnemyFcmedusa();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014 (empty)
    virtual void v018();                         // +0x018 (empty)
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual int onMessage(int a, const int* msg);   // +0x150 queues a received message
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcmedusa)
    void startMotion0();
    void setMotionOff(bool off);
    void bob();
    void setState(int s);
    void stateGlide(float dt);
    void stateDie();
    void fire();
    void stateShoot(float dt);
    void sendMove(unsigned int angle, unsigned int time);
    int angleOf(const EnemyVec2* v);
    void dirTo(EnemyVec2* out, const EnemyVec2* p);
    void dirToLabel(EnemyVec2* out, int id, bool level);
    int findTarget();
    bool targetNear();
    void think(float dt);                        // (dt unused)
    void stateWait(float dt);
    void stateIdle(float dt);
    bool handleEvents();
    void labelPos(EnemyVec2* out, int id);

public:
    // <layout:EnemyFcmedusa>
    int m_state;                                    // +0x44C0 0 idle, 1 wait, 2 shoot and drift, 3 die, 4 glide
    int m_prevState;                                // +0x44C4
    int m_step;                                     // +0x44C8 state 2: 0 shoot, 1 drift
    float m_timer;                                  // +0x44CC time in the state (step)
    int m_i44D0;                                    // +0x44D0
    bool m_stateInit;                               // +0x44D4 the state has run its entry code
    bool m_dead;                                    // +0x44D5
    bool m_wake;                                    // +0x44D6 set by slot +0x080, cleared every frame
    bool m_hit;                                     // +0x44D7 set by slot +0x084
    bool m_keepSide;                                // +0x44D8 state 2 leaves the drift when the player changes sides (true after construction)
    unsigned char _pad44D9[0x3];
    float m_home[2];                                // +0x44DC position on entering state 0
    float m_phase;                                  // +0x44E4 bobbing phase, 0..period (1.5 s, 1 s with +0x230)
    float m_dirX;                                   // +0x44E8 cosine of the glide angle
    float m_dirY;                                   // +0x44EC sine of the glide angle
    float m_moveTime;                               // +0x44F0 state 2 drift time (randInt / 100)
    int m_i44F4;                                    // +0x44F4
    int m_i44F8;                                    // +0x44F8
    int m_targetLabel;                              // +0x44FC label chased (-1: none)
    unsigned int m_msgId;                           // +0x4500 the outgoing / current message (20 bytes, slot +0x154)
    float m_msgTime;                                // +0x4504
    unsigned int m_msgPos;                          // +0x4508 packPos
    float m_msgPhase;                               // +0x450C m_phase of the sender
    unsigned int m_msgBits;                         // +0x4510 bits 0..3 time / 100, 4..19 angle, 20 m_sameSide
    FcmedusaMsgList m_msgs;                         // +0x4514 received messages (slot +0x150)
    bool m_hasMsg;                                  // +0x4520 a message was taken from m_msgs
    unsigned char _pad4521[0x3];
    float m_glideTime;                              // +0x4524 state 4 duration
    float m_moveFrom[2];                            // +0x4528
    float m_moveTo[2];                              // +0x4530
    float m_phaseFrom;                              // +0x4538
    float m_phaseTo;                                // +0x453C
    bool m_lerp;                                    // +0x4540 state 4 moves from m_moveFrom to m_moveTo
    bool m_sameSide;                                // +0x4541 the target is on this side (true after construction)
    unsigned char _pad4542[0x6];
    EnemyFcmedusaMutex m_lock;                      // +0x4548 guards m_msgs
    // </layout:EnemyFcmedusa>
};

