// Dll/Shot/Fcaxe/ShotFcaxe.h - dllshotfcaxe's shot class (
// 0x32C bytes): the axe armor's thrown axe ("L.アックスアーマー", ShotInfo
// name). A boomerang axe: it flies forward for 1.6 s, brakes for 0.3 s, flies
// back and is caught (or ends after 10 s / on a hit), then plays a second
// object out and dies. Thrown by a powered-up owner it starts in the return
// flight with a per-level arc. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFcaxe : public ShotBase {
public:
    ShotFcaxe();                                 // (DllCreate inlines it)
    virtual ~ShotFcaxe();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual, unreferenced copies of parts of update() / vanish()
    void tickLifetime(float dt);
    bool takeHit();
    void end();

public:
    int m_state;                                 // +0x318 0 out, 1 braking, 2 back, 3 caught, 4 second object, 5 end, 6 arc
    float m_time;                                // +0x31C time in the current flight phase
    float m_life;                                // +0x320 seconds since start()
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_ending;                               // +0x328 vanish() asked for the end
    bool m_ended;                                // +0x329 end() ran
    bool m_ownerFlag;                            // +0x32A the byte at m_ownerLink was set (no catching)
    unsigned char _pad32B[0x1];
};

