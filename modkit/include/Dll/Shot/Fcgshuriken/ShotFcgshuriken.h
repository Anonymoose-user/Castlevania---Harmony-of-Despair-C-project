// Dll/Shot/Fcgshuriken/ShotFcgshuriken.h - dllshotfcgshuriken's shot class
// (vtable ): Getsu Fuma's throwing star
// ("FC Getsu Fuma: Gesshi shuriken", ShotInfo name). Started without a spawn word
// (m_i284 == 0) it queues one record per star to fire (3, 4 or 5 by kind)
// and kills itself; a star flies forward, falling, for 1 s. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFcgshuriken : public ShotBase {
public:
    ShotFcgshuriken();                           // (DllCreate inlines it)
    virtual ~ShotFcgshuriken();

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
    int m_state;                                 // +0x318 0 flying, 1 ending
    float m_time;                                // +0x31C
    float m_dir;                                 // +0x320 -1 facing left, 1 right
    float m_fallTime;                            // +0x324 time since start (not set by the constructor)
};

