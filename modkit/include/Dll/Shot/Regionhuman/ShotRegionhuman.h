// Dll/Shot/Regionhuman/ShotRegionhuman.h - dllregionhuman's shot class
// (vtable ): one of Legion's corpses (ShotInfo name
// "Legion: human" in Japanese). It walks forward (object A walks, object B
// is the falling body), drops off ledges, and when ended it falls apart,
// dropping debris, and fades out over 0.5 s. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotRegionhuman : public ShotBase {
public:
    ShotRegionhuman();                           // (DllCreate inlines it)
    virtual ~ShotRegionhuman();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vfunc044(const unsigned int* info);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

public:
    float m_fade;                                // +0x318 fade-out time
    float m_time;                                // +0x31C total time (300 s limit)
    float m_debris;                              // +0x320 time to the next debris drop
    int m_state;                                 // +0x324 0 falling, 1 walking, 2 end, 3 fading, 4 dead
    float m_speedMul;                            // +0x328 0.7 on some floors
    float m_speed;                               // +0x32C walking speed (signed)
    bool m_left;                                 // +0x330 facing left at start
};

