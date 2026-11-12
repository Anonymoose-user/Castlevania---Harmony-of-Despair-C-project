// Dll/Shot/Byakko/ShotByakko.h - dllbyakko's shot class (
// 0x32C bytes): the White Tiger soul (ShotInfo name "Byakko" in kanji). It
// leaps forward and up, falls, bounces off what it hits, then fades out over
// 0.2 s. The class adds one virtual (+0x594, the "finish" hook vfunc044
// calls). Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotByakko : public ShotBase {
public:
    ShotByakko();                                // (DllCreate inlines it)
    virtual ~ShotByakko();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void vfunc024(float dt);
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vfunc044(const unsigned int* info);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);
    // the class's own 358th virtual
    virtual void finish(const unsigned int* info);

public:
    float m_time;                                // +0x318 total time (10 s limit)
    float m_fade;                                // +0x31C fade-out time
    bool m_left;                                 // +0x320 facing left at start
    unsigned char _pad321[0x7];
    int m_state;                                 // +0x328 0 rising, 1 bouncing, 2 end, 3 fading, 4 dead
};

