// Dll/Enemy/Psukobach/EnemyPsukobach.h - dllpsukobach, the Ukoback (a fire
// imp of the "PS" enemy set) that bounces through the
// room off walls, floor and ceiling and spits fireballs (
// object 0x44F4 bytes). Names are inferred.
//
// States (m_state): 0 spawn (goes to 1 at once), 1 fly, 2 die (slow down,
// burst into ten embers, fade out), 3 gone.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyPsukobach's own fields: the  layout dump.
class EnemyPsukobach : public EnemyObjBase {
public:
    EnemyPsukobach();
    virtual ~EnemyPsukobach();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default fireball request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014 0: starts flying up
    virtual void v018();                         // +0x018 empty
    virtual void v01C(float dt);                 // +0x01C empty
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v080(int part);                         // +0x080
    virtual void v084(int part);                         // +0x084 hit: go to the die state
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers
    void setBoxes();
    void setFacing(float f);
    void setState(int s);
    bool stateDie(float dt);
    bool stateFly(float dt);
    int returnOne();

public:
    // <layout:EnemyPsukobach>
    int m_state;                                    // +0x44C0 0 spawn, 1 fly, 2 die, 3 gone
    int m_step;                                     // +0x44C4 die sub-step: 0 start, 1 slow down, 2 fade out
    float m_dirX;                                   // +0x44C8 -1 / 1: sign of the x velocity (setFacing)
    float m_dirY;                                   // +0x44CC -1 / 1: sign of the y velocity (spawn flag)
    float m_timer;                                  // +0x44D0 fire timer, fade time in the die state
    float m_firePeriod;                             // +0x44D4 1 s between fireballs
    float m_speed;                                  // +0x44D8 flying speed (slows down when dying)
    float m_angle;                                  // +0x44DC flying direction (radians)
    int m_layer;                                    // +0x44E0 +0x221 when it started
    int m_frame;                                    // +0x44E4 update count (blinks hit box 0's +0x0C)
    float m_startPos[2];                            // +0x44E8 target position at start()
    bool m_wake;                                    // +0x44F0 set by slot +0x080 (cleared every update)
    bool m_hit;                                     // +0x44F1 set by slot +0x084
    bool m_turned;                                  // +0x44F2 turned around after a layer change
    unsigned char _pad44F3[0x1];
    // </layout:EnemyPsukobach>
};

