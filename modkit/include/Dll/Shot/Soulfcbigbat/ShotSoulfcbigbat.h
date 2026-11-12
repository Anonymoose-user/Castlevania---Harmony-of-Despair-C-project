// Dll/Shot/Soulfcbigbat/ShotSoulfcbigbat.h - dllshotsoulfcbigbat's shot class
// (vtable ): the giant bat soul ("L.ookoumori", giant bat,
// ShotInfo name). The bat rises, hovers, then swoops forward and falls; it
// lives 3 s and ends early on vanish or hit. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcbigbat : public ShotBase {
public:
    ShotSoulfcbigbat();                          // (DllCreate inlines it)
    virtual ~ShotSoulfcbigbat();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual, unreferenced copies of parts of update / vanish
    void end();
    void tickLife(float dt);
    bool beginUpdate();

public:
    int m_state;                                 // +0x318 0 rise, 1 hover, 2 swoop, 3 end, 4 fade, 5 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320 seconds left (3 at start)
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endRequest;                           // +0x328
    bool m_ended;                                // +0x329
    bool m_b32A;                                 // +0x32A end request through the delay below
    bool m_b32B;                                 // +0x32B
};

