// Dll/Enemy/Psbeel/EnemyPsbeel.h - dllpsbeel, Beelzebub of the Portrait of
// Ruin ("Ps") enemy set (object 0x4B78 bytes). Names are
// inferred.
//
// A boss made of 11 body parts (m_parts: a hit box each, wobbling and swinging
// on its parent, breaking off and falling when its motion's health runs out
// or the body's health passes a threshold) and three flies (m_wings, hit
// boxes 9..11 of list 1). It fights in modes (m_mode): 0 measure the room
// with the room query (EnemyObjBase +0x04C), 1 a shot volley, 2 an attack
// pattern, 3 die; think() picks modes 1 and 2. Online (+0x440A) the host side
// (+0x4408) decides and sends 8-byte messages (m_msgOut); the other side
// receives them through slot +0x150 into m_in (under a kernel mutex).
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

#include <list>

// One body part. Constructor (inlined).
struct BeelPart {
    unsigned int flags;          // +0x00 1 wobble, 2 follows its parent, 4 swings (off), 8 broken, 0x10 gone
    bool useMain;                // +0x04 its health is the main motion's (EnemyObjBase +0x442C)
    bool inHb0;                  // +0x05 its hit box is in list 0 (else list 1)
    int hbIndex;                 // +0x08
    int motion;                  // +0x0C its motion in the queue (EnemyObjBase +0x441C)
    int parent;                  // +0x10
    float base[2];               // +0x14 position on the body
    float amp[2];                // +0x1C wobble amplitude
    float off[2];                // +0x24 offset swung by the angle
    float pos[2];                // +0x2C current position (hit box +0x40)
    float world[2];              // +0x34 where its children hang
    float angle;                 // +0x3C (hit box +0x50)
    float angleAmp;              // +0x40
    float hurtTimer;             // +0x44
    float prio;                  // +0x48 hit box +0x14
    float hpSaved;               // +0x4C its motion's health last frame
    float hpLost;                // +0x50 health lost, still to be sent
    float damage;                // +0x54 health lost on the other side, still to be taken
    float phase;                 // +0x58
    float period;                // +0x5C
    float alpha;                 // +0x60 1 until it fades after breaking
    float fallVel;               // +0x64
    float gravScale;             // +0x68
    float smokeTimer;            // +0x6C
    BeelPart();
};

// One fly. Constructor (inlined).
struct BeelWing {
    float x, y;                  // +0x00 hit box +0x40
    int hbIndex;                 // +0x08 in hit box list 1
    float prio;                  // +0x0C hit box +0x14
    float len;                   // +0x10
    float angle;                 // +0x14 hit box +0x50
    bool still;                  // +0x18 no swinging
    float t;                     // +0x1C
    float sign;                  // +0x20
    float amp;                   // +0x24
    BeelWing();
};

// A point; the room points' constructor.
struct BeelPoint {
    float x, y;
    BeelPoint();
};

// One sync message (8 bytes).
struct BeelMsg {
    unsigned int w[2];
};
typedef std::list<BeelMsg, DllAllocator<BeelMsg> > BeelMsgList;

// A recursive mutex owned by an object (vtable ); the
// constructor, lock() and unlock() are inlined.
class BeelMutex {
public:
    BeelMutex();
    virtual ~BeelMutex();
    int lock();
    int unlock();

    DLL_MUTEX_FIELD
};

// Member layout of EnemyPsbeel's own fields: the  layout dump.
class EnemyPsbeel : public EnemyObjBase {
public:
    EnemyPsbeel();
    virtual ~EnemyPsbeel();

    // overridden slots
    virtual void v008();                         // +0x008 a default shot
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014
    virtual void v018();                         // +0x018 takes the received messages
    virtual void v01C(float dt);                 // +0x01C
    virtual void update(float dt);               // +0x020
    virtual void v024(const int* a, void* b, bool c); // +0x024
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 (the original reads an int as its first parameter: wakePart)
    virtual int onMessage(int a, const int* msg); // +0x150 queues a sync message
    virtual const char* getDataPath(int index);  // +0x174
    virtual const char* v1A0();                  // +0x1A0 its effect name
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllpsbeel)
    void setupParts();
    void setSpeed(float s);
    void breakChain(int from, int parent);
    void updateParts(float dt);
    void placeWings();
    bool isHost();
    void sendCmd(unsigned int v);
    unsigned int modeCmd();
    void setMode(int mode, bool send);
    bool isMaster();
    void updateWings(float dt);
    void syncDamage(float dt);
    void think(float dt);
    void modeDie(float dt);
    void fireShot(int kind);
    void shotEffect();
    void modeAttack(float dt);
    void modeVolley(float dt);
    void modeMeasure();
    void updateMode(float dt);
    void wakePart(int id);
    bool isClient();

public:
    // <layout:EnemyPsbeel>
    int m_thinkStep;                                // +0x44C0 think(): 0 wait until idle, 1 pause 0.5 s, 2 pick the next mode
    int m_mode;                                     // +0x44C4 0 measure the room, 1 shot volley, 2 attack pattern, 3 die (-1 after construction)
    int m_step;                                     // +0x44C8 step inside the mode
    float m_timer;                                  // +0x44CC
    bool m_active;                                  // +0x44D0 the fight has started (slot +0x01C / +0x080 / a received command)
    bool m_busy;                                    // +0x44D1 a mode is running
    unsigned char _pad44D2[0x2];
    float m_thinkTimer;                             // +0x44D4
    float m_speed;                                  // +0x44D8 motion speed (spawn flags 0x0F / 16)
    int m_brokenCount;                              // +0x44DC body parts broken off
    int m_shotLevel;                                // +0x44E0 spawn flags 0xFF0000, passed with every shot
    float m_shotPower;                              // +0x44E4 spawn flags 0xFF000000 / 16, scales the shot strength
    float m_fxTimer;                                // +0x44E8 mode 1: effect every 0.5 s while shots fly
    float m_syncTimer;                              // +0x44EC online: one part's damage every 0.2 s
    int m_syncPart;                                 // +0x44F0 next part whose damage is sent (1..10)
    unsigned int m_brokenMask;                      // +0x44F4 bit per broken part (+ health thresholds)
    unsigned int m_shotMask;                        // +0x44F8 bit per shot slot that ended
    unsigned int m_sentBroken;                      // +0x44FC m_brokenMask as last sent
    unsigned int m_sentShot;                        // +0x4500 m_shotMask as last sent
    int m_roomTop;                                  // +0x4504 room bounds measured in mode 0 (16-pixel cells, centre)
    int m_roomBottom;                               // +0x4508
    int m_roomLeft;                                 // +0x450C
    int m_roomRight;                                // +0x4510
    unsigned int m_tag;                             // +0x4514 0x81F45C1D; every shot request carries its address
    unsigned char m_shotState[32];                  // +0x4518 0 free, 1 fired, 2 live, 3 ended (set by the original game)
    unsigned char m_shotState2[32];                 // +0x4538 3: told to end
    float m_angle;                                  // +0x4558 turning angle (pi per second, twice that while aiming)
    bool m_aiming;                                  // +0x455C
    unsigned char _pad455D[0x3];
    float m_aim[2];                                 // +0x4560 the aim point handed out while m_aimMode is 2
    float m_points[18];                             // +0x4568 the start position and 8 points of the measured room
    int m_aimMode;                                  // +0x45B0 1 aiming, 2 aiming at m_aimPos
    float m_aimPos[2];                              // +0x45B4
    int m_liveShots;                                // +0x45BC shots alive (state 2)
    int m_volley;                                   // +0x45C0 mode 1 shot count
    int m_level;                                    // +0x45C4 mode 2 shot count
    int m_attackKind;                               // +0x45C8 mode 2 pattern (1..6)
    int m_toFire;                                   // +0x45CC shots to fire in this mode
    int m_fired;                                    // +0x45D0
    float m_fireGap;                                // +0x45D4 time between two shots
    BeelPart m_parts[11];                           // +0x45D8 the body parts
    BeelWing m_wings[3];                            // +0x4AA8
    unsigned int m_msgOut[2];                       // +0x4B20 the sync message (+0x4400 / +0x4404)
    BeelMutex m_mutex;                              // +0x4B28
    BeelMsgList m_in;                               // +0x4B60 messages received (slot +0x150), under m_mutex
    BeelMsgList m_cmds;                             // +0x4B6C mode commands taken from m_in
    // </layout:EnemyPsbeel>
};

