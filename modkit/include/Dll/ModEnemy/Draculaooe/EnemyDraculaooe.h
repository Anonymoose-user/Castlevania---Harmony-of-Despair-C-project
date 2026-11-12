// Dll/ModEnemy/Draculaooe/EnemyDraculaooe.h - Order of Ecclesia Dracula as a boss
// (mod boss_dracula_ooe; sprites and behaviour from the Unity remake's Enemy_Dracula_OoE, used with
// its team's permission), on the code of dllfusimon, the skeleton Simon of the
// Fuma-style ("FU") enemy set: it walks back and forth, turns towards the
// player when he comes near and swings its whip at him (
// object 0x44DC bytes). Names are inferred.
//
// States (m_state): 0 patrol (walk, turn at walls and ledges), 1 walk towards
// the player, 2 attack (whip swing, a hit request while the motion's +0x08
// is 4), 3 die.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyDraculaooe's own fields: the  layout dump.
class EnemyDraculaooe : public EnemyObjBase {
public:
    EnemyDraculaooe();
    virtual ~EnemyDraculaooe();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void v018();                         // +0x018 empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080 wake up
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (several have no caller)
    void startMotion0();
    void faceDir();
    void setBoxes26A();
    void setFacing(float f);
    void nop560();
    void clearB268();
    void clearB26AB();
    void stateDie();
    void setState(int s);
    bool inRange();
    void stateAttack(float dt);
    bool inReach();
    bool isI258Clear();
    bool isWallAhead();
    bool mustTurn();
    void faceTarget();
    bool targetBehind();
    void stateWalk(float dt);
    void turnAround();
    void statePatrol();
    bool handleEvents();
    void setMotionB1C(bool off);

public:
    // <layout:EnemyDraculaooe>
    int m_state;                                    // +0x44C0 0 patrol, 1 walk, 2 attack, 3 die
    float m_timer;                                  // +0x44C4 time in the state
    float m_facing;                                 // +0x44C8 -1 left, 1 right (setFacing)
    bool m_stateInit;                               // +0x44CC the state has run its entry code
    bool m_dead;                                    // +0x44CD
    bool m_b44CE;                                   // +0x44CE
    bool m_wake;                                    // +0x44CF set by slot +0x080
    bool m_hit;                                     // +0x44D0 set by slot +0x084
    unsigned char _pad44D1[0x3];
    float m_lostTimer;                              // +0x44D4 time the player has been out of range
    float m_attackWait;                             // +0x44D8 time since the last attack (attacks again from 0.8 s)
    // </layout:EnemyDraculaooe>
    // OoE Dracula boss (Unity remake behaviour; not in the original object)
    int m_attack;                                   // the move picked (DA_*)
    unsigned m_rng;
    int m_phase;                                    // 1, then 2 below half health (the Unity remake's fase 2)
    int m_attackStep;
    void bossIdle();
    void bossApproach(float dt);
    void bossAttack(float dt);
    void bossDie();
    void bossChangeForm(float dt);
    void hitArea(float x0, float y0, float x1, float y1);
    int  rnd(int n);
    void fire(int n, float x, float y, float vx, float vy);   // mod sprite shot n (data/shot/mod_shots.txt)
};

