// Dll/Enemy/Fcbigbat/EnemyFcbigbat.h - dllfcbigbat, the giant bat of the
// Famicom-style ("FC") enemy set (object 0x454C bytes).
// Names are inferred; the state names describe what each state does.
//
// States (m_state): 0 idle (hangs until the player comes near), 1 seek
// (picks the player label to go for), 2 fly (straight at it), 3 dive (hover,
// then swoop down at it), 4 spit (three shots), 5 die, 6 sync move (glides to
// the position of a move message, then goes on to its next state).
//
// The boss version (spawn flag 1, m_big) plays online: the host (+0x440A
// set and +0x4408 set, or +0x440A clear) decides and sends each move as a
// 0x20-byte message (m_msgId.., read by the original game through slots +0x154 /
// +0x158 once slot +0x164 flags it); a client (+0x440A set, +0x4408 clear)
// queues the messages it receives (onMessage) and replays them.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

#include <list>

// One move message (0x20 bytes; std::list node 0x28).
struct BigbatMsg {
    unsigned int id;                 // +0x00 EnemyObjBase::m_s440C of the sender
    float time;                      // +0x04 its m_f4498
    unsigned int pos;                // +0x08 packPos of its m_selfPos
    EnemyVec2 goal;                  // +0x0C
    EnemyVec2 dir;                   // +0x14
    unsigned int bits;               // +0x1C next state (bits 0-3), same side (bit 4)
};
typedef std::list<BigbatMsg, DllAllocator<BigbatMsg> > BigbatMsgList;

// Member layout of EnemyFcbigbat's own fields: the  layout dump.
class EnemyFcbigbat : public EnemyObjBase {
public:
    EnemyFcbigbat();
    virtual ~EnemyFcbigbat();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014
    virtual void v018();                         // +0x018 (empty)
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual int onMessage(int a, const int* msg);   // +0x150 queues a received move message
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcbigbat)
    void startMotion0();
    void setMotionB1C(bool off);
    void clearWoken();
    void setState(int s);
    void stateSync(float dt);
    void stateDie();
    void dirTo(EnemyVec2* out, const EnemyVec2* p);
    void fireSpread();
    void stateSpit(float dt);
    void stateDive(float dt);
    void stateFly(float dt);
    void aimAt(EnemyVec2* out, int id);
    void randomDir(EnemyVec2* out);
    bool inDiveRange(int id);
    bool inNear();
    void sendMsg(int unused, EnemyVec2 dir, EnemyVec2 goal);
    int pickLabel();
    void think(float dt);
    void stateSeek(float dt);
    void stateIdle(float dt);
    bool handleEvents();
    static int sameCodeOne();

public:
    // <layout:EnemyFcbigbat>
    int m_state;                                    // +0x44C0 0 idle, 1 seek, 2 fly, 3 dive, 4 spit, 5 die, 6 sync move
    int m_prevState;                                // +0x44C4
    int m_phase;                                    // +0x44C8 state 3: 0 hover, 1 dive
    float m_timer;                                  // +0x44CC time in the state
    float m_f44D0;                                  // +0x44D0 side of the spat shots (never set by the module)
    bool m_stateInit;                               // +0x44D4 the state has run its entry code
    bool m_dead;                                    // +0x44D5
    bool m_wake;                                    // +0x44D6 set by slot +0x080
    bool m_hit;                                     // +0x44D7 set by slot +0x084
    bool m_canTurn;                                 // +0x44D8 a move ends early when the player changes side
    bool m_woken;                                   // +0x44D9 woken this frame (makes state 0 start without the player near)
    unsigned char _pad44DA[0x2];
    float m_diveAy;                                 // +0x44DC state 3: vertical acceleration of the dive
    EnemyVec2 m_dir;                                // +0x44E0 direction of the move
    float m_speed;                                  // +0x44E8 speed of the move (states 2 / 3)
    float m_moveTime;                               // +0x44EC length of the state 2 flight
    EnemyVec2 m_goal;                               // +0x44F0 position of the label chased
    int m_labelId;                                  // +0x44F8 label chased (-1: none)
    bool m_big;                                     // +0x44FC spawn flag 1 (slot +0x014): the boss version
    unsigned char _pad44FD[0x3];
    unsigned int m_msgId;                           // +0x4500 the outgoing / current move message (0x20 bytes, slot +0x154)
    float m_msgTime;                                // +0x4504 m_f4498 of the sender
    unsigned int m_msgPos;                          // +0x4508 packPos of the sender's m_selfPos
    EnemyVec2 m_msgGoal;                            // +0x450C
    EnemyVec2 m_msgDir;                             // +0x4514
    unsigned int m_msgBits;                         // +0x451C next state (bits 0-3), same side (bit 4)
    BigbatMsgList m_msgs;                           // +0x4520 received move messages (onMessage)
    bool m_hasMsg;                                  // +0x452C m_msg* holds a message still to apply
    unsigned char _pad452D[0x3];
    float m_syncTime;                               // +0x4530 state 6 duration
    EnemyVec2 m_syncFrom;                           // +0x4534
    int m_nextState;                                // +0x453C state 6 goes on to it (7 after construction)
    EnemyVec2 m_syncTo;                             // +0x4540
    bool m_syncLerp;                                // +0x4548 state 6 moves from m_syncFrom to m_syncTo
    bool m_sameSide;                                // +0x4549 m_canTurn after the move (true after construction)
    unsigned char _pad454A[0x2];
    // </layout:EnemyFcbigbat>
};

