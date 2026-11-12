// Dll/Shot/Regionlaser/ShotRegionlaser.h - dllregionlaser's shot class
// (vtable ): the Legion's laser ("Legion: laser",
// ShotInfo name). A charge animation, then a beam that grows from the
// emitter (m_v048 plus an offset) in one of eight directions while it fades
// in, and fades out again; each frame it queues the beam quad (IShot +0x444)
// and, while it touches something, sparks. Launched by the Legion it is tied
// to the Legion's shared record (m_link, copied every frame). Names are
// inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

// The record the Legion shares with its lasers (0x69 bytes, copied into
// ShotRegionlaser::m_offs.. by preUpdate()).
struct RegionLaserLink {
    Vec2 offs[8];                                // +0x00 emitter offsets by direction
    float angles[8];                             // +0x40 beam angles by direction
    bool done[8];                                // +0x60 a laser of that direction ended
    bool dead;                                   // +0x68 the Legion is gone
};

class ShotRegionlaser : public ShotBase {
public:
    ShotRegionlaser();                           // (32 bytes, calls )
    virtual ~ShotRegionlaser();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void vfunc034();
    virtual void onHit(unsigned int flags);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // four identical, unreferenced zeroing helpers (Vec2 constructors)
    static void zeroVec0(Vec2* v);
    static void zeroVec1(Vec2* v);
    static void zeroVec2(Vec2* v);
    static void zeroVec3(Vec2* v);

public:
    float m_time;                                // +0x318 seconds since start()
    int m_i31C;                                  // +0x31C (unused)
    int m_phase;                                 // +0x320 0 charge, 1 fade in, 2 fade out, 3 dead
    float m_len;                                 // +0x324 beam length
    float m_alpha;                               // +0x328
    float m_timer;                               // +0x32C animation frame timer (0.03 s)
    int m_step;                                  // +0x330 beam animation direction (+1 / -1)
    bool m_spark;                                // +0x334 the beam touched something this frame
    RegionLaserLink* m_link;                     // +0x338 the Legion's record (start(): m_ownerLink), or 0
    Vec2 m_offs[8];                              // +0x33C copy of m_link->offs
    float m_angles[8];                           // +0x37C copy of m_link->angles
    bool m_done[8];                              // +0x39C copy of m_link->done
    bool m_linkDead;                             // +0x3A4 copy of m_link->dead
    int m_index;                                 // +0x3A8 direction 0..7
    Vec2 m_startPos;                             // +0x3AC
    int m_w3B4[8];                               // +0x3B4 (only cleared)
    float m_sparkTimer;                          // +0x3D4 spark sound interval (0.2 s)
};

