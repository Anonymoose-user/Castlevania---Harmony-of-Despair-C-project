// Dll/Enemy/Ryukotsu/EnemyRyukotsu.h - dllryukotsu, the bone dragon boss of
// the Fuma-style set (object 0x4588 bytes). Names are
// inferred; the state names describe what each state does.
//
// States (m_state): 0 appear (waits for the player), 2 / 6 / 10 the three
// fight phases (+0x1E8 above m_hp1, above m_hp2, below), 3 / 7 rise into the
// next phase (bones fly up), 4 / 8 rest, 1 / 5 / 9 wait for the host's next
// move (online client), 11 die, 12 dead. Each fight state picks an action
// (m_step) and plays it out.
//
// Online (+0x440A set) the host instance (+0x4408 set, nothing queued:
// isMaster()) decides and sends each action as a 12-byte message (m_msgBits..,
// read by the original game through slots +0x154 / +0x158 once slot +0x164 flags it);
// the others queue what they receive (onMessage, under an system mutex) and
// replay it (applyMsg). m_cur holds four bytes in original byte order (byte k is
// bits 31-8k..24-8k of the word) since they travel in the message as they are.
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"


// The game's mutex wrapper (vtable, 0x38 with the
// alignment; the constructor and lock / unlock are inlined).
class RyukotsuMutex {
public:
    RyukotsuMutex()
    {
        DLL_MUTEX_CREATE();
    }
    virtual ~RyukotsuMutex();
    int lock() { return DLL_MUTEX_LOCK(); }
    int unlock() { return DLL_MUTEX_UNLOCK(); }

    DLL_MUTEX_FIELD
};

// One message (12 bytes).
struct RyukotsuMsg {
    unsigned int bits;               // +0x00 see EnemyRyukotsu::m_msgBits (byte 0: the state)
    unsigned int bytes;              // +0x04 m_cur of the sender
    unsigned int pos;                // +0x08 packPos of its +0x0A4
};
typedef ENEMY_LIST(RyukotsuMsg) RyukotsuMsgList;

// Member layout of EnemyRyukotsu's own fields: the  layout dump.
class EnemyRyukotsu : public EnemyObjBase {
public:
    EnemyRyukotsu();
    virtual ~EnemyRyukotsu();

    // overridden slots
    virtual void v008();                         // +0x008 spawns default shot requests
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 takes received moves, attack boxes
    virtual void v01C(float dt);                 // +0x01C
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 hit this frame
    virtual void v084(int part);                         // +0x084 (empty)
    virtual int onMessage(int a, const int* msg);   // +0x150 queues a received move
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllryukotsu)
    void updateMarkers();
    void hideBones();
    void stopBlink();
    bool isMaster();
    void changeState(unsigned int s, bool fromMsg);
    void setFacing(float f);
    void clampHp();
    void pushAttackBoxes();
    void applyMsg();
    void blinkTick();
    bool boneAttack(float dt);
    void sendState();
    void startBones(int n);
    bool stateDie(float dt);
    bool attackBreath(float dt);
    void stepX();
    bool attackFlame(float dt);
    bool attackStomp(float dt);
    void beginBreath();
    void beginFlame(bool walk);
    void beginWalk(bool walk);
    bool stateFight3(float dt);
    bool stateRest3(float dt);
    bool stateRise3(float dt);
    bool wallAhead();
    void setBoxes26A(float w, float h);
    bool stateFight2(float dt);
    bool stateRest2(float dt);
    bool stateRise2(float dt);
    void startBlink();
    bool stateFight1(float dt);
    bool stateAppear(float dt);
    static int sameCodeOne();

public:
    // <layout:EnemyRyukotsu>
    unsigned int m_state;                           // +0x44C0 0 appear, 1 / 5 / 9 wait for the host, 2 / 6 / 10 fight, 3 / 7 rise (bones), 4 / 8 rest, 11 die, 12 dead
    int m_step;                                     // +0x44C4 step inside the state (the fight states: the action)
    int m_lastAct;                                  // +0x44C8 action of the last fight step
    int m_act;                                      // +0x44CC action sent / received in the message
    int m_repeat;                                   // +0x44D0 times the same action came in a row
    unsigned int m_blinkCount;                      // +0x44D4 frames blinked
    unsigned int m_boneCount;                       // +0x44D8 bones (hit boxes 1..4) thrown up
    int m_boneTable;                                // +0x44DC first row of the bone offset table
    unsigned int m_cur;                             // +0x44E0 four bytes (original order): attack variant, three flame angles (sent in the message)
    unsigned int m_prev;                            // +0x44E4 four bytes: byte 0 the variant of the last action
    float m_facing;                                 // +0x44E8 -1 left, 1 right
    float m_timer;                                  // +0x44EC time in the step
    float m_actTimer;                               // +0x44F0 time in the action
    float m_waitTime;                               // +0x44F4 rest after an action (by +0x230)
    float m_boneTimer;                              // +0x44F8
    float m_boneTick;                               // +0x44FC time since the last bone spark
    float m_par[6];                                 // +0x4500 walk speed, jump speed, charge speed, -, step length, - (by +0x230)
    float m_hp1;                                    // +0x4518 +0x1E8 limit of states 0..3 (+0x1EC * 0.8)
    float m_hp2;                                    // +0x451C +0x1E8 limit of states 4..7 (+0x1EC * 0.6)
    bool m_hitFlag;                                 // +0x4520 set by slot +0x080, cleared every frame
    bool m_b4521;                                   // +0x4521
    bool m_awake;                                   // +0x4522 the player came in (sent in the message)
    unsigned char _pad4523[0x1];
    bool m_blinking;                                // +0x4524 the body hit box blinks
    bool m_fired;                                   // +0x4525 the action's shot / step happened
    bool m_fired2;                                  // +0x4526
    unsigned char _pad4527[0x1];
    EnemyVec2 m_home;                               // +0x4528 +0x0A4 at start
    unsigned int m_msgBits;                         // +0x4530 the outgoing message (12 bytes, slot +0x154): state (bits 24-31), facing left (23), awake (22), +0x040 (21), action (13-20)
    unsigned int m_msgBytes;                        // +0x4534 m_cur
    unsigned int m_msgPos;                          // +0x4538 packPos of +0x0A4
    RyukotsuMsgList m_msgs;                         // +0x453C received messages (onMessage)
    unsigned char _pad454C[0x4];
    RyukotsuMutex m_lock;                           // +0x4550 guards m_msgs
    // </layout:EnemyRyukotsu>
};

