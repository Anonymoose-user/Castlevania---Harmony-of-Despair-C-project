// Dll/Enemy/Skeleton/EnemySkeleton.h - dllskeleton, the bone-throwing
// skeleton of the regular (non-FC) enemy set: it keeps its distance from
// the player, backs off when he comes close, throws bones (shot 0x40000042)
// and falls apart in six parts when killed (311 slots:
// one more than EnemyObjBase; object 0x44E4 bytes). Names are inferred.
//
// States (m_state): 0 idle (until the player is within 160), 1 start
// walking, 2 walk / back off / pause, 3 throw, 4 in the air (+0x043 set),
// 5 die (fade out, then the death effects).
//
// Slot +0x068 is overridden by this module only: the original game calls it with a
// motion event and a kind as its two parameters. The override's body is onMotionEvent()
// below.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemySkeleton's own fields: the  layout dump.
class EnemySkeleton : public EnemyObjBase {
public:
    EnemySkeleton();
    virtual ~EnemySkeleton();

    // overridden slots
    virtual void v008();                         // +0x008 spawns a default shot request
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010
    virtual void update(float dt);               // +0x020
    virtual void destroy();                      // +0x02C
    virtual void v084(int part);                         // +0x084 hit: fall apart (state 5)
    virtual const char* getDataPath(int index);  // +0x174
    virtual void release();                      // +0x4D0
    // new in this class (slot +0x4D8)
    virtual const char* getResource(unsigned int index, int* kind);

    // module helpers
    void resetRange();
    void stateWalk(float dt);
    // slot +0x068 (see above): ev is the original's motion event (+0x04 its
    // frame kind, +0x3C a bool), kind the event type.
    virtual void v068(const void* ev, int kind); // +0x068: onMotionEvent
    void onMotionEvent(const int* ev, int kind);

public:
    // <layout:EnemySkeleton>
    int m_state;                                    // +0x44C0 0 idle, 1 start walking, 2 walk, 3 throw, 4 in the air, 5 die
    float m_retreatTimer;                           // +0x44C4 time spent backing off
    float m_retreatTime;                            // +0x44C8 how long to back off (random 0.5..1.5 or 2..3 s)
    float m_timer;                                  // +0x44CC time in the walk state
    float m_pauseTimer;                             // +0x44D0 pause left before walking on (state 2)
    float m_range;                                  // +0x44D4 preferred throwing distance (96 +- 32)
    bool m_retreat;                                 // +0x44D8 backing off from the player
    bool m_throwDone;                               // +0x44D9 the throw motion passed frame 0x32 (no more shots)
    bool m_stopped;                                 // +0x44DA stopped for the throw
    bool m_gone;                                    // +0x44DB the death has finished (effects asked for)
    bool m_pause;                                   // +0x44DC pausing in state 2
    bool m_b44DD;                                   // +0x44DD
    unsigned char _pad44DE[0x2];
    float m_alpha;                                  // +0x44E0 fade while dying (1 -> 0)
    // </layout:EnemySkeleton>
};

