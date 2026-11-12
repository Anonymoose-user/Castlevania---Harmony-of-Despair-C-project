// Dll/Enemy/Region/EnemyRegion.h - dllregion, Legion (the "region" boss: a
// ball of corpses with eight arms around a core;, object
// 0x4790 bytes; model data/enemy/DLL_region/p_region.opd). Names inferred.
//
// The nine parts (eight arms and the core) are the nine queued motions
// (m_motionQueue, see layouts/EnemyRegion.txt). It shoots from random arms
// (scatterShot) and runs one of six attacks (m_attack) chosen by aiStep():
// 0 spin (beams from every other arm), 1 all arms in turn, 2/3 punch with the
// arm facing the player, 4 beam from it, 5 a spray of shots from it.
//
// In multiplayer (+0x440A) the host instance (+0x4408) decides and sends
// 4-byte messages (m_msgWord: shots, attacks, the kill) and every instance
// sends the damage its parts took (the 12-byte m_hpMsg*); the others receive
// them through slot +0x150 into m_msgs / m_hpRecv (each guarded by an system
// mutex) and replay them in update().
#pragma once

#include "Dll/DllMutex.h"
#include "Dll/Enemy/EnemyObjBase.h"

// The game's system mutex wrapper (vtable; constructor,
// lock and unlock are inlined).
class EnemyRegionMutex {
public:
    EnemyRegionMutex();
    virtual ~EnemyRegionMutex();
    int lock();
    int unlock();

    DLL_MUTEX_FIELD
};

// A received 4-byte message and its sequence number (-1: replayed).
struct RegionMsg {
    int seq;
    unsigned int word;
    RegionMsg();
    RegionMsg(int s, unsigned int w) : seq(s), word(w) {}
};
typedef std::vector<RegionMsg, DllAllocator<RegionMsg> > RegionMsgList;

// Member layout of EnemyRegion's own fields: the  layout dump.
class EnemyRegion : public EnemyObjBase {
public:
    EnemyRegion();
    virtual ~EnemyRegion();

    // overridden slots
    virtual void v008();                         // +0x008 spawns three default shot requests
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014 the parts' hit points
    virtual void v01C(float dt);                 // +0x01C
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 calls wake(0), see wake()
    virtual void v084(int part);                         // +0x084 calls hit(0), see hit()
    virtual int onMessage(int a, const int* msg);   // +0x150 a received message
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // The bodies of slots +0x080 and +0x084: the original reads the id of
    // the woken / hit part as an extra parameter, which the slot list does not declare.
    void wake(int id);
    void hit(int id);

    // module helpers (several have no caller in dllregion)
    void placeArm(int i);
    void sendHp(float dt);
    void sendShot(int x, int y, bool flip);
    void fireShot(const EnemyVec2* off, bool flip);
    void scatterShot(float dt);
    void sendAttack();
    void sendSpin();
    void sendAimed();
    void chooseAttack();
    void pickArmAttack();
    int sector();
    void aiStep(float dt);
    unsigned int msgParts(unsigned int w);
    bool msgAggro(unsigned int w);
    bool msgFlip(unsigned int w);
    int msgY(unsigned int w);
    int msgX(unsigned int w);
    unsigned int msgSide(unsigned int w);
    unsigned int msgAttack(unsigned int w);
    bool msgIsAttack(unsigned int w);
    bool msgIsKill(unsigned int w);
    void animArm(float dt, int i);
    void attackSpray(float dt);
    void fireArm(int i);
    void attackPunch(float dt);
    void fireBeam(int i);
    void attackBeam(float dt);
    void attackAll(float dt);
    void attackSpin(float dt);
    void attackStep(float dt);
    void breakPart(float dt, int i);
    void sendKill();
    bool msgBit0(unsigned int w);

public:
    // <layout:EnemyRegion>
    unsigned int m_hurt;                            // +0x44C0 parts out of hit points (bit per part, 0x1FF all)
    unsigned int m_broken;                          // +0x44C4 parts whose break-up has run
    unsigned int m_armOut;                          // +0x44C8 arms stretching out (bit per arm)
    unsigned int m_armBack;                         // +0x44CC arms pulling back
    int m_armIdx;                                   // +0x44D0 arm the all-arms attack is at
    int m_armCount;                                 // +0x44D4 arms back from the all-arms attack
    bool m_spinOdd;                                 // +0x44D8 the spin attack uses the odd arms
    bool m_aggro;                                   // +0x44D9 the player has been seen
    unsigned char _pad44DA[0x2];
    int m_blink;                                    // +0x44DC hit box animation frame (0..3)
    float m_blinkTimer;                             // +0x44E0
    bool m_burst;                                   // +0x44E4 the death burst has run
    unsigned char _pad44E5[0x3];
    float m_smokeTimer;                             // +0x44E8 death smoke interval
    float m_fadeTimer;                              // +0x44EC death fade-out
    float m_armTip[16];                             // +0x44F0 arm tip positions (x, y), relative
    float m_armAngle[8];                            // +0x4530 arm tip directions
    bool m_armHit[8];                               // +0x4550 set by the original game when an arm tip hits
    bool m_wasDead;                                 // +0x4558 slot +0x088 of the last frame
    unsigned char _pad4559[0x3];
    int m_aiStep;                                   // +0x455C attack chooser step
    int m_attack;                                   // +0x4560 0 spin, 1 all arms, 2/3 punch, 4 beam, 5 spray (-1 none)
    int m_atkStep;                                  // +0x4564 step inside the attack
    float m_frameTimer[8];                          // +0x4568 arm animation timers
    int m_frame[8];                                 // +0x4588 arm hit box frame (9..13)
    int m_frameDir[8];                              // +0x45A8 +1 / -1
    float m_phase[8];                               // +0x45C8 arm swing phase
    unsigned char _pad45E8[0x20];
    float m_extTimer[8];                            // +0x4608 arm stretch timers
    int m_extFrame[8];                              // +0x4628 arm tip hit box frame (57..59)
    float m_atkTimer;                               // +0x4648
    unsigned char _pad464C[0x4];
    float m_beamTimer;                              // +0x4650
    float m_sfxTimer;                               // +0x4654
    bool m_attacking;                               // +0x4658 an attack is running
    bool m_altPunch;                                // +0x4659 alternates the two punch attacks
    unsigned char _pad465A[0x2];
    float m_bob;                                    // +0x465C bobbing phase
    int m_side;                                     // +0x4660 arm (sector) facing the player
    float m_sprayTimer;                             // +0x4664
    float m_shotTimer;                              // +0x4668
    bool m_fast;                                    // +0x466C woken: shoots twice as often for a while
    unsigned char _pad466D[0x3];
    float m_fastTimer;                              // +0x4670
    unsigned int m_msgWord;                         // +0x4674 the 4-byte multiplayer message (+0x4400)
    RegionMsgList m_msgs;                           // +0x4678 received messages (slot +0x150)
    int m_sendSeq;                                  // +0x4688 sequence number of the next received message
    int m_recvSeq;                                  // +0x468C next message to replay
    EnemyRegionMutex m_msgLock;                     // +0x4690 guards m_msgs
    int m_hpMsgSeq;                                 // +0x46C8 the 12-byte hit point message: -1
    unsigned char m_hpMsgPart;                      // +0x46CC part (0..8)
    unsigned char _pad46CD[0x3];
    float m_hpMsgDamage;                            // +0x46D0
    float m_hpRecv[9];                              // +0x46D4 damage received per part (slot +0x150)
    float m_hpSend[9];                              // +0x46F8 damage to send per part
    float m_hpLast[9];                              // +0x471C hit points of the last frame
    float m_hpTimer;                                // +0x4740 hit point message interval
    unsigned char _pad4744[0x4];
    EnemyRegionMutex m_hpLock;                      // +0x4748 guards m_hpRecv
    float m_hpScale;                                // +0x4780 hit points of parts 0..7 (spawn flags & 0xFFF)
    float m_hpScaleCore;                            // +0x4784 hit points of part 8 (spawn flags >> 12)
    int m_weightA;                                  // +0x4788 attack choice weights
    int m_weightB;                                  // +0x478C
    // </layout:EnemyRegion>
};

