// Dll/Enemy/Fcwhitedra/EnemyFcwhitedra.h - dllfcwhitedra, the white dragon
// (bone serpent) of the FC enemy set: a head and six neck segments that
// stick out of a wall (object 0x4574 bytes). Names are
// inferred; the state names describe what each state does.
//
// States (m_state): 0 hidden (waits for the player in front of it), 1 rise
// (pushes the head out, 44 units in 1 s / 0.5 s), 2 attack (follows the
// player's height, spits fireballs on the motion's fire frame), 3 bob (moves
// up and down at random), 4 die. update() then lays out the neck and the hit
// boxes (updateParts).
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// 0x14: the head and each neck segment. Its constructor zeroes
// it; the module constructor does the same inline.
struct WhitedraPart {
    int boxA;                    // +0x00 hit box index (body)
    int boxB;                    // +0x04 hit box index (hurt box)
    EnemyVec2 pos;               // +0x08 offset from the own position
    bool moving;                 // +0x10 following the part above
    WhitedraPart();
};

// Member layout of EnemyFcwhitedra's own fields: the  layout dump.
class EnemyFcwhitedra : public EnemyObjBase {
public:
    EnemyFcwhitedra();
    virtual ~EnemyFcwhitedra();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller in dllfcwhitedra)
    void startMotion();
    void setMotionB1Cn(bool off);
    void setFacing(float f);
    void copyPos(WhitedraPart* p);
    void updateBody(float dt);
    void updateParts(float dt);
    void stateDie();
    void setState(int s);
    bool inSight();
    void stateBob(float dt);
    void fire();
    void stateAttack(float dt);
    void stateRise(float dt);
    void stateHidden(float dt);
    bool handleEvents();
    bool sameSide();

    // the head and the six segments as WhitedraPart (0: head, 1..6: segments)
    WhitedraPart* parts() { return reinterpret_cast<WhitedraPart*>(&m_headBoxA); }

public:
    // <layout:EnemyFcwhitedra>
    int m_state;                                    // +0x44C0 0 hidden, 1 rise, 2 attack, 3 bob, 4 die
    int m_prevState;                                // +0x44C4
    float m_timer;                                  // +0x44C8 time in the state
    float m_facing;                                 // +0x44CC -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44D0 the state has run its entry code
    bool m_dead;                                    // +0x44D1
    bool m_wake;                                    // +0x44D2 set by slot +0x080
    bool m_hit;                                     // +0x44D3 set by slot +0x084
    bool m_placed;                                  // +0x44D4 slot +0x018 has moved it out of the wall
    unsigned char _pad44D5[0x3];
    int m_headBoxA;                                 // +0x44D8 head: hit box index (body)
    int m_headBoxB;                                 // +0x44DC head: hit box index (hurt box)
    float m_headX;                                  // +0x44E0 head: offset x from the own position
    float m_headY;                                  // +0x44E4 head: offset y
    bool m_headMoving;                              // +0x44E8 head: following the one above
    unsigned char _pad44E9[0x3];
    int m_seg0BoxA;                                 // +0x44EC segment 0: hit box index (body)
    int m_seg0BoxB;                                 // +0x44F0 segment 0: hit box index (hurt box)
    float m_seg0X;                                  // +0x44F4 segment 0: offset x from the own position
    float m_seg0Y;                                  // +0x44F8 segment 0: offset y
    bool m_seg0Moving;                              // +0x44FC segment 0: following the one above
    unsigned char _pad44FD[0x3];
    int m_seg1BoxA;                                 // +0x4500 segment 1: hit box index (body)
    int m_seg1BoxB;                                 // +0x4504 segment 1: hit box index (hurt box)
    float m_seg1X;                                  // +0x4508 segment 1: offset x from the own position
    float m_seg1Y;                                  // +0x450C segment 1: offset y
    bool m_seg1Moving;                              // +0x4510 segment 1: following the one above
    unsigned char _pad4511[0x3];
    int m_seg2BoxA;                                 // +0x4514 segment 2: hit box index (body)
    int m_seg2BoxB;                                 // +0x4518 segment 2: hit box index (hurt box)
    float m_seg2X;                                  // +0x451C segment 2: offset x from the own position
    float m_seg2Y;                                  // +0x4520 segment 2: offset y
    bool m_seg2Moving;                              // +0x4524 segment 2: following the one above
    unsigned char _pad4525[0x3];
    int m_seg3BoxA;                                 // +0x4528 segment 3: hit box index (body)
    int m_seg3BoxB;                                 // +0x452C segment 3: hit box index (hurt box)
    float m_seg3X;                                  // +0x4530 segment 3: offset x from the own position
    float m_seg3Y;                                  // +0x4534 segment 3: offset y
    bool m_seg3Moving;                              // +0x4538 segment 3: following the one above
    unsigned char _pad4539[0x3];
    int m_seg4BoxA;                                 // +0x453C segment 4: hit box index (body)
    int m_seg4BoxB;                                 // +0x4540 segment 4: hit box index (hurt box)
    float m_seg4X;                                  // +0x4544 segment 4: offset x from the own position
    float m_seg4Y;                                  // +0x4548 segment 4: offset y
    bool m_seg4Moving;                              // +0x454C segment 4: following the one above
    unsigned char _pad454D[0x3];
    int m_seg5BoxA;                                 // +0x4550 segment 5: hit box index (body)
    int m_seg5BoxB;                                 // +0x4554 segment 5: hit box index (hurt box)
    float m_seg5X;                                  // +0x4558 segment 5: offset x from the own position
    float m_seg5Y;                                  // +0x455C segment 5: offset y
    bool m_seg5Moving;                              // +0x4560 segment 5: following the one above
    unsigned char _pad4561[0x3];
    float m_goalY;                                  // +0x4564 head height the bob / attack states move to
    bool m_fired;                                   // +0x4568 the attack motion's fire frame has been handled
    unsigned char _pad4569[0x3];
    int m_shotCount;                                // +0x456C attack frames counted (fires every 2nd without +0x230)
    float m_lostTimer;                              // +0x4570 time the player has been out of sight (attack state)
    // </layout:EnemyFcwhitedra>
};

