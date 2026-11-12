// Dll/Enemy/Fcguillotine/EnemyFcguillotine.h - dllfcguillotine, the swinging
// guillotine blade trap of the FC enemy set (object 0x44CC
// bytes). Names are inferred.
//
// It has no states of its own: update() flips m_state whenever the current
// hit box (motion) has finished and starts the next swing.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcguillotine's own fields: the  layout dump.
class EnemyFcguillotine : public EnemyObjBase {
public:
    EnemyFcguillotine();
    virtual ~EnemyFcguillotine();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers
    void startMotion0();                         // (no caller)

public:
    // <layout:EnemyFcguillotine>
    int m_state;                                    // +0x44C0 0 / 1: which way the blade swings next (update)
    int m_type;                                     // +0x44C4 spawn flags & 0xF (0..2): picks the hit box / motion set
    float m_speed;                                  // +0x44C8 spawn flags >> 4 times 0.1 (1 when 0), hit box +0x10
    // </layout:EnemyFcguillotine>
};

