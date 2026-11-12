// Dll/Enemy/Fuhbsr/EnemyFuhbsr.h - dllfuhbsr, the fire pillar ("hibashira")
// of the Getsu Fuma Den ("Fu") enemy set: a jet of flame that bursts from a
// floor, ceiling or wall at intervals (object 0x44DC
// bytes). Names are inferred.
//
// States (m_state): 0 initial delay, 1 off (waits m_offTime, then picks the
// burst size and switches the hit box on), 2 burning (0.4..0.9 s by size;
// pushes the hit box's first rectangle, turned to the pillar's direction, as
// a +0x18C request every frame).
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFuhbsr's own fields: the  layout dump.
class EnemyFuhbsr : public EnemyObjBase {
public:
    EnemyFuhbsr();
    virtual ~EnemyFuhbsr();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void setSpawnFlags(unsigned int flags); // +0x014
    virtual void v018();                         // +0x018 moves it onto its wall once
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0

    // module helpers (no caller in dllfuhbsr)
    void setMotionB1CTu(bool off);
    void startMotion0();

public:
    // <layout:EnemyFuhbsr>
    int m_state;                                    // +0x44C0 0 delay, 1 off, 2 burning
    float m_timer;                                  // +0x44C4 time in the state (the overshoot carries over)
    bool m_placed;                                  // +0x44C8 slot +0x018 has moved it to its wall
    unsigned char _pad44C9[0x3];
    int m_size;                                     // +0x44CC spawn flags 0..3: pillar size (0 random, 1 small .. 3 large)
    int m_dir;                                      // +0x44D0 spawn flags 4..7: 0 up, 1 down, 2 right, 3 left
    float m_offTime;                                // +0x44D4 spawn flags 8..15 / 10 s (2 s, or 1 s with +0x230, when 0)
    float m_delay;                                  // +0x44D8 spawn flags 16..23 / 10 s: wait before the first burst
    // </layout:EnemyFuhbsr>
};

