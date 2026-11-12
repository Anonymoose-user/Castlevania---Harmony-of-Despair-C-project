// Dll/Enemy/Fcdracula/EnemyFcdracula.h - dllfcdracula, Dracula, the final
// boss of the Famicom-style ("FC") enemy set (object
// 0x4618 bytes). Names are inferred; the state names describe what each
// state does.
//
// States (m_state): 0 probe (measures the room in 16 px steps), 1 rise,
// 2 fly to a column, 3 dash, 4 spit (fire volleys), 5 split (the head
// comes off: second form), 6 hop, 7 leap, 8 fire ring, 9 jump across the
// room, 10 fireball burst, 11 die. m_form: 0 whole, 1 head and body apart
// (states 1..4), 2 body only (states 6..10).
//
// Hit box 0 (+0x2B4) is the cloak / body motion, 1 the upper body, 2 the
// head; each has a small part state (m_cloakMode, m_bodyMode, m_headMode).
// The +0x2C4 boxes are the six pieces the split state throws.
//
// In online play (+0x440A set) the host instance (+0x4408 set) decides and
// sends every state change as an 8-byte message (m_msg, read by the original game
// through slot +0x154); the others receive them through slot +0x150 into
// m_msgsIn (guarded by an system mutex), move the 0x81 ones to m_moves in
// slot +0x018 and replay one per frame in update(). Message 0x82 is a
// knock-off of the head.
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

#include <list>

// system mutex system calls (0x64 create, 0x65 destroy, 0x66 lock, 0x68 unlock);
// host stand-ins in EnemyFcdracula.cpp.

// The game's mutex wrapper (vtable, 0x38 with the
// alignment; the constructor and lock / unlock are inlined).
class EnemyFcdraculaMutex {
public:
    EnemyFcdraculaMutex()
    {
        DLL_MUTEX_CREATE();
    }
    virtual ~EnemyFcdraculaMutex();
    int lock() { return DLL_MUTEX_LOCK(); }
    int unlock() { return DLL_MUTEX_UNLOCK(); }

    DLL_MUTEX_FIELD
};

// One message (8 bytes; std::list node 0x10). a: the type in bits 24..31
// (0x81 a state change, 0x82 a head knock-off); see EnemyFcdracula::packState.
struct FcdraculaMsg {
    unsigned int a;
    unsigned int b;
};
typedef std::list<FcdraculaMsg, DllAllocator<FcdraculaMsg> > FcdraculaMsgList;

// Member layout of EnemyFcdracula's own fields: the  layout dump.
class EnemyFcdracula : public EnemyObjBase {
public:
    EnemyFcdracula();
    virtual ~EnemyFcdracula();

    // overridden slots
    virtual void v008();                         // +0x008 spawns two default shot requests
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014 the three scales
    virtual void v018();                         // +0x018 drains the received messages
    virtual void v01C(float dt);                 // +0x01C notices the player
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 hit (as +0x084)
    virtual void v084(int part);                         // +0x084 hit
    virtual int onMessage(int a, const int* msg);   // +0x150 queues a received message
    virtual const char* getDataPath(int index);  // +0x174
    virtual const char* v1A0();                  // +0x1A0 the effect set name
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcdracula)
    void setMotionId(bool on, int id);
    void setBox268();
    void setBoxes26A();
    void setBox269();
    bool isHost();
    void sendMsg(unsigned int a, unsigned int b);
    unsigned int packState(unsigned int* extra);
    void setState(int s, bool send);
    void setFacing(bool right, int boxes);
    bool isNotRemote();
    void pickAttack();
    int columnX(int column);
    void pickMove();
    void enterRise();
    void think(float dt);
    void fireShot(const EnemyVec2* pos, const EnemyVec2* vel, bool flag);
    void updateBurst(float dt);
    void updateBody(float dt);
    void updateCloak(float dt);
    void updateHead(float dt);
    void stateDie(float dt);
    void startBurst(const EnemyVec2* pos, int kind, bool cw, bool flat);   // runs on m_burstKind (address in the .cpp)
    void stateFireball(float dt);
    bool isI258Set();
    bool isWallAhead();
    void stateJump(float dt);
    void stateFireRing(float dt);
    void stateLeap(float dt);
    void stateHop(float dt);
    void stateSplit(float dt);
    void fireOrb(const EnemyVec2* pos, const EnemyVec2* vel, bool up, float size);
    void fireSpread(const EnemyVec2* pos, bool up, float dirX);
    void stateSpit(float dt);
    void stateDash(float dt);
    void stateFly(float dt);
    void stateRise(float dt);
    void stateProbe(float dt);
    void runState(float dt);
    void onHit();
    void clearB269();
    bool isI25CSet();
    void clearB268();
    void clearB26AB();
    bool isRemote();

    // the part of setState after the fields (inlined everywhere)
    void sendState();

public:
    // <layout:EnemyFcdracula>
    int m_phase;                                    // +0x44C0 think cycle: 0 wait for the state to end, 1 pause, 2 pick the next state
    int m_state;                                    // +0x44C4 -1 none, 0 probe, 1 rise, 2 fly, 3 dash, 4 spit, 5 split, 6 hop, 7 leap, 8 fire ring, 9 jump, 10 fireball, 11 die
    int m_step;                                     // +0x44C8 step inside the state
    float m_timer;                                  // +0x44CC time in the step
    bool m_active;                                  // +0x44D0 the player was seen (or it was hit)
    bool m_running;                                 // +0x44D1 the state has not finished
    unsigned char _pad44D2[0x2];
    float m_pause;                                  // +0x44D4 think pause (0.5 s)
    int m_form;                                     // +0x44D8 0 first form, 1 head and body, 2 body only
    bool m_headHit;                                 // +0x44DC the head was knocked off (message 0x82)
    bool m_otherLayer;                              // +0x44DD the player is on another layer (slot +0x01C)
    unsigned short m_spotX;                         // +0x44DE position the fireball state aims at (x)
    unsigned short m_spotY;                         // +0x44E0 (y, 48 above the player)
    unsigned char _pad44E2[0x2];
    int m_column;                                   // +0x44E4 column (16 px) the dash / fly states go to
    bool m_right;                                   // +0x44E8 face right in the state
    unsigned char _pad44E9[0x3];
    float m_destX;                                  // +0x44EC x the dash / fly states stop at
    int m_spitMode;                                 // +0x44F0 bit 0: which way the spit volley goes, bit 4: a second volley
    float m_jumpDist;                               // +0x44F4 state 9: distance to the far wall
    float m_jumpSpeed;                              // +0x44F8
    float m_jumpRise;                               // +0x44FC
    float m_orbScale;                               // +0x4500 spawn flags bits 0..5 x 0.1 (1.1)
    float m_burstScale;                             // +0x4504 bits 6..11 x 0.1 (1.2)
    float m_jumpScale;                              // +0x4508 bits 12..17 x 0.1 (2)
    unsigned char m_hopPattern;                     // +0x450C index into the hop table
    unsigned char m_hopBits;                        // +0x450D 2 bits per hop (1 forward, 2 back)
    unsigned char m_hitDir;                         // +0x450E octant the head was knocked towards
    unsigned char _pad450F[0x1];
    unsigned short m_hitPower;                      // +0x4510 speed of the knocked-off head
    bool m_headLaunched;                            // +0x4512
    unsigned char _pad4513[0x1];
    float m_headPos[2];                             // +0x4514 head offset from the body
    float m_headVel[2];                             // +0x451C
    bool m_headOff;                                 // +0x4524 the head flies separately
    unsigned char _pad4525[0x3];
    float m_facing;                                 // +0x4528 -1 left, 1 right (setFacing)
    float m_moveDir;                                // +0x452C
    unsigned char _pad4530[0x4];
    int m_probeUp;                                  // +0x4534 state 0: probe offsets
    int m_probeDown;                                // +0x4538
    int m_probeLeft;                                // +0x453C
    int m_probeRight;                               // +0x4540
    int m_roomTop;                                  // +0x4544 room bounds the probe found
    int m_roomBottom;                               // +0x4548
    int m_roomLeft;                                 // +0x454C
    int m_roomRight;                                // +0x4550
    int m_columns;                                  // +0x4554 16 px columns across the room
    int m_headMode;                                 // +0x4558 part state: 1 shown, 2 shown (alt), 3 hidden, 4 blink m_headTimer then go to m_headNext
    int m_headNext;                                 // +0x455C
    float m_headTimer;                              // +0x4560
    bool m_headOn;                                  // +0x4564
    bool m_headAlt;                                 // +0x4565
    bool m_headB;                                   // +0x4566
    unsigned char _pad4567[0x1];
    int m_bodyMode;                                 // +0x4568 the same for the body (hit box 1)
    int m_bodyNext;                                 // +0x456C
    float m_bodyTimer;                              // +0x4570
    bool m_bodyOn;                                  // +0x4574
    bool m_bodyAlt;                                 // +0x4575
    bool m_bodyB;                                   // +0x4576
    unsigned char _pad4577[0x1];
    int m_cloakMode;                                // +0x4578 the same for the cloak (hit box 0)
    int m_cloakNext;                                // +0x457C
    float m_cloakTimer;                             // +0x4580
    bool m_cloakOn;                                 // +0x4584
    bool m_cloakAlt;                                // +0x4585
    bool m_cloakB;                                  // +0x4586
    unsigned char _pad4587[0x1];
    int m_burstKind;                                // +0x4588 fire burst: 0 / 1 ring, 2 fireball
    bool m_burstOn;                                 // +0x458C
    unsigned char _pad458D[0x3];
    float m_burstTimer;                             // +0x4590 time to the next volley
    float m_burstTime;                              // +0x4594 time left
    bool m_burstCw;                                 // +0x4598
    bool m_burstFlat;                               // +0x4599
    unsigned char _pad459A[0x6];
    int m_burstCount;                               // +0x45A0 shots per volley
    float m_burstPos[2];                            // +0x45A4
    float m_burstAngle;                             // +0x45AC
    float m_burstSpin;                              // +0x45B0
    float m_burstSpeed;                             // +0x45B4
    float m_burstInterval;                          // +0x45B8
    unsigned int m_msg[2];                          // +0x45BC outgoing message (slot +0x154 reads +0x4400 = its address)
    unsigned char _pad45C4[0x4];
    EnemyFcdraculaMutex m_msgLock;                  // +0x45C8 guards m_msgsIn
    FcdraculaMsgList m_msgsIn;                      // +0x4600 received messages (onMessage)
    FcdraculaMsgList m_moves;                       // +0x460C received moves (type 0x81), replayed by update
    // </layout:EnemyFcdracula>
};

