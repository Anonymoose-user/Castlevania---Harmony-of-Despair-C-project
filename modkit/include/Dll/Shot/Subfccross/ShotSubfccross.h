// Dll/Shot/Subfccross/ShotSubfccross.h - dllshotsubfccross's shot class
// (vtable ): the FC cross sub-weapon ("sabu FC kurosu", sub FC cross,
// ShotInfo name), a boomerang cross. It flies out, turns, flies back and
// dies when it reaches the owner (or after 5 s / on vanish or hit it starts
// a short end sequence). Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSubfccross : public ShotBase {
public:
    ShotSubfccross();                            // (DllCreate inlines it)
    virtual ~ShotSubfccross();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual, unreferenced copies of parts of update / vanish
    void tickLife(float dt);
    bool beginUpdate();
    void end();

public:
    int m_state;                                 // +0x318 0 out, 1 turn, 2 back, 3 end, 4 fade, 5 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320 seconds alive (ends after 5)
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endRequest;                           // +0x328 set by vanish / onHit
    bool m_ended;                                // +0x329
};

