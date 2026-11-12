// Dll/Shot/Psbeelshot/ShotPsbeelshot.h - dllshotpsbeelshot's shot class
// (vtable ): Beelzebub's shot ("PS Beruzebubu:
// shotto", ShotInfo name), one of up to 32 flies of a swarm. m_i284 packs
// the fly's slot (bits 0-7), a formation (bits 8-11, 0: orbit the boss) and
// the hit power / 10 (bits 16-23). m_ownerLink points at the boss's
// swarm block (magic 0x81F45C1D: slot states, the orbit angle and centre,
// a target point and the formation anchor points); m_probe is the
// original's floor query (called with the integer position).
// A fly fades in, flies its formation path (or orbits, then dives at the
// target) and fades out when it leaves the floor it started on, the block
// says so, or the shot is ended. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotPsbeelshot : public ShotBase {
public:
    ShotPsbeelshot();
    virtual ~ShotPsbeelshot();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void vfunc020();
    virtual void update(float dt);
    virtual void vfunc054();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // (exercised through start / update: its byte out-parameter
    // does not fit the per-function test's word buffers)
    bool slotPos(Vec2* out, void* flip, int formation, int index);
    void homePos(Vec2* out);
    void setPhase(int phase);
    void end(bool killed);

public:
    int m_slot;                                  // +0x318 slot in the swarm (0..31, -1: none)
    int m_phase;                                 // +0x31C 0 appear, 1 fade in, 2 orbit, 3 dive, 4 formation, 5 fade out, 6 dead
    int m_step;                                  // +0x320
    float m_time;                                // +0x324
    int m_formation;                             // +0x328 0: orbit
    int m_index;                                 // +0x32C point of the formation path
    float m_speed;                               // +0x330
    int m_facingSign;                            // +0x334
    float m_dir;                                 // +0x338 -1 left, 1 right
    bool m_killed;                               // +0x33C ended by the boss (fades out at once)
    bool m_ending;                               // +0x33D
    unsigned char _pad33E[2];
    void* m_swarm;                               // +0x340 the swarm block (m_ownerLink)
    float m_f344;                                // +0x344
    float m_f348;                                // +0x348
    float m_f34C;                                // +0x34C
    Vec2 m_from;                                 // +0x350
    Vec2 m_goal;                                 // +0x358
    Vec2 m_target;                               // +0x360
};

