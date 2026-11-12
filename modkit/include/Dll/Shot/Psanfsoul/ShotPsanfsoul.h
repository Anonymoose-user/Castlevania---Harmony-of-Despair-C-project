// Dll/Shot/Psanfsoul/ShotPsanfsoul.h - dllshotpsanfsoul's shot class (vtable
// ): the Anfauglir soul ("PSアンフアゥグリア：ソウル",
// ShotInfo name). Launched forward at a speed set by the kind byte (m_u204),
// it slows to a stop; after 5 s (or vanish(), or once object 0's b28 flag is
// set) it fades out over 0.3 s and kills itself. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotPsanfsoul : public ShotBase {
public:
    ShotPsanfsoul();                             // (DllCreate inlines it)
    virtual ~ShotPsanfsoul();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void vfunc04C();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual, unreferenced copies of the end logic
    void end();
    void tickEnd(float dt);

public:
    int m_state;                                 // +0x318 0 flying, 1 fading, 2 done
    float m_time;                                // +0x31C
    float m_dir;                                 // +0x320 -1 facing left, 1 right
    float m_fade;                                // +0x324 fade-out time (start() clears it)
};

