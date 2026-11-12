// Dll/Enemy/Fukyokotsu/EnemyFukyokotsu.h - dllfukyokotsu, the giant skeleton
// boss "Kyokotsu" (the "Fu" enemy set, data DLL_kyokotsu;,
// object 0x46A0 bytes). Names are inferred; the state names describe what each
// state does.
//
// States (m_state): 0 set-up (probes the room's walls with the four wall
// boxes, lays 16 fire-drop points along the ceiling, spawns its two partners
// DLL_FuDokugan and DLL_FuRyukibi through the original game and waits for their link
// records), 1 idle (until the player is on its layer), 2 fight (walks between
// the room bounds and picks attacks), 3 die, 4 wait (m_waitTime, then
// m_nextState).
//
// Attacks: the slap (the six hand shots, each with a KyoHand record the hand
// module reads and writes through the shot request's +0x1C), the double jump,
// and the fire rain (once two partners are down: drops at m_flamePoints on a
// timetable). The two arms follow the partners while they live and take over
// their position when they fall.
//
// In online play (+0x440A set) the host instance (+0x4408 set) sends each
// choice as a 12-byte message (m_msgId.., slot +0x154); the others get them
// through slot +0x150 into m_msgs (guarded by an system mutex) and replay them.
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

#include <list>
#include <vector>

// system mutex system calls (0x64 create, 0x65 destroy, 0x66 lock, 0x68 unlock).
// The host build gets single-threaded stand-ins (ids only).
namespace FukyokotsuSys {
}   // namespace FukyokotsuSys

// The game's mutex wrapper (vtable, 0x38 with the
// alignment; the constructor and lock / unlock are inlined).
class EnemyFukyokotsuMutex {
public:
    EnemyFukyokotsuMutex()
    {
        DLL_MUTEX_CREATE();
    }
    virtual ~EnemyFukyokotsuMutex();
    int lock() { return DLL_MUTEX_LOCK(); }
    int unlock() { return DLL_MUTEX_UNLOCK(); }

    DLL_MUTEX_FIELD
};

// What a partner module and Kyokotsu publish of themselves (0x0C): Kyokotsu's
// own is at +0x452C (slot +0x09C hands out its address), the partners' are
// reached through m_partnerA / m_partnerB.
struct KyoLink {
    bool dead;                   // +0x00 defeated
    bool ready;                  // +0x01
    float x, y;                  // +0x04 position
};

// One fire-drop point (0x0C; vector +0x450C).
struct KyoPoint {
    float x, y;                  // +0x00
    bool used;                   // +0x08 dropped in this rain
    KyoPoint() {}
    KyoPoint(float px, float py) : x(px), y(py), used(false) {}
};
typedef std::vector<KyoPoint, DllAllocator<KyoPoint> > KyoPointList;

// One received message (12 bytes; std::list node 0x14).
struct KyoMsg {
    unsigned int id;             // +0x00 EnemyObjBase::m_s440C of the sender
    unsigned int bits;           // +0x04 see EnemyFukyokotsu::sendMsg
    float time;                  // +0x08 m_f4498 of the sender
};
typedef std::list<KyoMsg, DllAllocator<KyoMsg> > KyoMsgList;

// One hand (0x1C, six at +0x45A0). The hand shot (shot 0x400010A2, the
// request's +0x1C points here) reads the offset and the command and sets
// `ready`.
struct KyoHand {
    float offX, offY;            // +0x00 spawn offset from the boss (kHandOffsets)
    bool dying;                  // +0x08 the boss died
    bool active;                 // +0x09 spawned
    int cmd;                     // +0x0C 1: slap
    float cmdDir;                // +0x10 slap direction (-1 / 1)
    unsigned char index;         // +0x14 0..5
    bool ready;                  // +0x15 set by the hand shot
    float respawn;               // +0x18 time since it was lost
    KyoHand();
};

// One arm (0x20, at +0x4560 and +0x4580).
struct KyoArm {
    int state;                   // +0x00 0 start, 1 wait for the partner to fall, 2 burn, 3 done, 4 attached
    float timer;                 // +0x04 state 2: 9 s
    float pos[2];                // +0x08 where it is (eases toward the boss)
    float off[2];                // +0x10 rest offset from the boss
    float shotTimer;             // +0x18 state 2: one flame every 0.1 s
    int shots;                   // +0x1C state 2: flames so far (20)
};

// Member layout of EnemyFukyokotsu's own fields: the  layout dump.
class EnemyFukyokotsu : public EnemyObjBase {
public:
    EnemyFukyokotsu();
    virtual ~EnemyFukyokotsu();

    // overridden slots
    virtual void v008();                         // +0x008 spawns the two default shot requests
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018
    virtual void v01C(float dt);                 // +0x01C copies the partners' link records
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const void* v09C();                          // +0x09C the address of the own link record
    virtual int onMessage(int a, const int* msg);   // +0x150 queues a received message
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfukyokotsu)
    void startMotion0();
    void faceDir();
    void setBoxes26A();
    void setFacing(float f);
    void updateHands(float dt);
    void shotAt(float x, float y);
    void shotFrom(EnemyVec2 pos, EnemyVec2 vel);
    void updateArms(float dt);
    void updateLimbs(float dt);
    void setState(int s);
    void stateWait(float dt);
    void stateDie(float dt);
    void fireAt(EnemyVec2 at);
    void updateFlames(float dt);
    void updateJump(float dt);
    void updateSlap(float dt);
    void sendMsg(int kind);
    bool startFlames();
    void collectLabels(EnemyIntList& out);
    bool startJump();
    bool startSlap();
    bool sameLayer();
    void think(float dt);
    void stateFight(float dt);
    void stateIdle(float dt);
    void stateSetup();
    bool handleEvents();
    bool isI258Clear();
    bool isWallAhead();
    bool mustTurn();
    void turnAround();
    void faceTarget();
    void clearB26AB();
    void clearB268();
    void setMotionB1C(bool off);
    int returnOne();

    KyoArm& arm(int i) { return *reinterpret_cast<KyoArm*>(i == 0 ? &m_armA : &m_armB); }

public:
    // <layout:EnemyFukyokotsu>
    int m_state;                                    // +0x44C0 0 set-up, 1 idle, 2 fight, 3 die, 4 wait (then m_nextState)
    int m_step;                                     // +0x44C4 state 0: 0 boxes, 1 probe the room, 2..5 spawn the partners, 6 done
    float m_timer;                                  // +0x44C8 time in the state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_b44D2;                                   // +0x44D2 slot +0x018 ran once
    bool m_wake;                                    // +0x44D3 set by slot +0x080 (cleared every update)
    bool m_hit;                                     // +0x44D4 set by slot +0x084
    unsigned char _pad44D5[0x3];
    float m_thinkTimer;                             // +0x44D8 time since the last attack choice
    bool m_busy;                                    // +0x44DC an attack (slap or jump) is running
    unsigned char _pad44DD[0x3];
    int m_bursts;                                   // +0x44E0 state 3: explosions so far
    int m_slapStep;                                 // +0x44E4 slap attack: hands sent so far (6)
    bool m_slapRight[6];                            // +0x44E8 slap attack: each hand slaps to the right
    unsigned char _pad44EE[0x2];
    float m_slapTimer;                              // +0x44F0
    bool m_slapping;                                // +0x44F4
    unsigned char m_slapPattern;                    // +0x44F5 0..3, the hand order (kSlapOrder)
    bool m_slapPending;                             // +0x44F6 started, waiting for m_slapTimer
    unsigned char _pad44F7[0x1];
    float m_jumpTimer;                              // +0x44F8
    bool m_jumping;                                 // +0x44FC
    unsigned char m_jumps;                          // +0x44FD jumps done (2)
    bool m_jumpPending;                             // +0x44FE
    unsigned char _pad44FF[0x1];
    float m_flameWait;                              // +0x4500 time since the last fire rain (3 s between)
    float m_flameTimer;                             // +0x4504
    bool m_flaming;                                 // +0x4508
    bool m_flamePending;                            // +0x4509
    unsigned char m_flamePattern;                   // +0x450A 0..3, the drop times (kFlameTimes*)
    unsigned char _pad450B[0x1];
    KyoPointList m_flamePoints;                     // +0x450C 16 drop points along the ceiling (state 0)
    float m_roomLeft;                               // +0x451C
    float m_roomRight;                              // +0x4520
    float m_roomTop;                                // +0x4524
    float m_roomBottom;                             // +0x4528
    bool m_linkDead;                                // +0x452C own KyoLink (slot +0x09C hands out its address): defeated
    bool m_linkReady;                               // +0x452D both partners were looked for
    unsigned char _pad452E[0x2];
    float m_linkX;                                  // +0x4530 own position (slot +0x018)
    float m_linkY;                                  // +0x4534
    const KyoLink* m_partnerA;                      // +0x4538 DLL_FuDokugan's link (slot +0x49C of the original game)
    const KyoLink* m_partnerB;                      // +0x453C DLL_FuRyukibi's link
    bool m_aDead;                                   // +0x4540 copy of *m_partnerA (slot +0x01C)
    bool m_aReady;                                  // +0x4541
    unsigned char _pad4542[0x2];
    float m_aX;                                     // +0x4544
    float m_aY;                                     // +0x4548
    bool m_bDead;                                   // +0x454C copy of *m_partnerB
    bool m_bReady;                                  // +0x454D
    unsigned char _pad454E[0x2];
    float m_bX;                                     // +0x4550
    float m_bY;                                     // +0x4554
    int m_tries;                                    // +0x4558 state 0: frames spent waiting for a partner (10)
    unsigned char m_partnersDown;                   // +0x455C partners defeated (their arm finished)
    bool m_partnersOn;                              // +0x455D the arms follow the partners
    unsigned char _pad455E[0x2];
    EnemyReq20 m_armA;                              // +0x4560 KyoArm: left arm (hit box 1), follows partner A
    EnemyReq20 m_armB;                              // +0x4580 KyoArm: right arm (hit box 2), follows partner B
    KyoHand m_hands[6];                             // +0x45A0 the six hand shots
    unsigned int m_msgId;                           // +0x4648 outgoing message (12 bytes, slot +0x154): m_s440C
    unsigned int m_msgBits;                         // +0x464C kind (bits 0-1), slap sides (2-7), pattern (8-11)
    float m_msgTime;                                // +0x4650 m_f4498 when sent
    KyoMsgList m_msgs;                              // +0x4654 received messages (onMessage)
    float m_waitTime;                               // +0x4660 state 4 duration
    int m_nextState;                                // +0x4664 state 4 goes on to it
    EnemyFukyokotsuMutex m_msgLock;                 // +0x4668 guards m_msgs
    // </layout:EnemyFukyokotsu>
};

