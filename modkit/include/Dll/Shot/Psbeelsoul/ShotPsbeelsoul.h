// Dll/Shot/Psbeelsoul/ShotPsbeelsoul.h - dllshotpsbeelsoul's shot class
// (vtable ): the Beelzebub soul (ShotInfo name
// "PS Beruzebubu Souru" in Japanese). Level 0 is a spawner: every 0.21 s it
// queues one fly (a ShotElem274 record for the original game) at a fixed offset,
// 1 to 5 of them by kind, then dies. Higher levels are a fly: it swirls in
// for 0.25 s, then flies ahead at 300 px/s; after 2 s or a hit it slows down,
// fades out over 0.5 s and dies. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotPsbeelsoul : public ShotBase {
public:
    ShotPsbeelsoul();                            // (DllCreate inlines it)
    virtual ~ShotPsbeelsoul();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual (end and takeEnd are unreferenced)
    void updateSpawner(float dt);
    void end();
    void tickEnd(float dt);
    bool takeEnd();
    void updateFly(float dt);

public:
    int m_state;                                 // +0x318 fly: 0 swirl, 1 flying, 2 fading, 4 done; spawner: 3 spawning, 4 done
    float m_timer;                               // +0x31C
    float m_time;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_fly;                                  // +0x328 level > 0
    bool m_endPending;                           // +0x329
    bool m_ended;                                // +0x32A
    unsigned char m_spawned;                     // +0x32B flies queued so far
};

