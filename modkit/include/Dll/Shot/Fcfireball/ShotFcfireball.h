// Dll/Shot/Fcfireball/ShotFcfireball.h - dllshotfcfireball's shot class
// (vtable ): a fireball ("L. fireball", ShotInfo
// name). Flies at 150 per second along its start velocity (or ahead of the
// owner); the first one (m_i284 == 0) also queues extra fireballs by kind.
// Ended (a hit, vanish(), or 3 s) it plays its burst animation and dies.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFcfireball : public ShotBase {
public:
    ShotFcfireball();                            // (DllCreate inlines it)
    virtual ~ShotFcfireball();

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

    // non-virtual, unreferenced copies of parts of update()
    void end();
    void tickLife(float dt);
    bool checkFade();

public:
    int m_state;                                 // +0x318 0 start, 1 flying, 2 ended, 3 bursting, 4 dead
    float m_time;                                // +0x31C (only cleared)
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for the burst
    bool m_ended;                                // +0x329
};

