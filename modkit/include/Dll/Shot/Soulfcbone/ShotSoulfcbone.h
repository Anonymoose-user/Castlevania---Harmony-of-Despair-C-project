// Dll/Shot/Soulfcbone/ShotSoulfcbone.h - dllshotsoulfcbone's shot class
// (vtable ): the skeleton soul's thrown bone ("FC
// bone throw", ShotInfo name). Thrown in an arc (three arcs by m_i284),
// spinning through six frames; the first throw queues one or two more bones
// at higher kinds. Ended (a hit, vanish(), 300 s) it bursts and dies.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcbone : public ShotBase {
public:
    ShotSoulfcbone();                            // (DllCreate inlines it)
    virtual ~ShotSoulfcbone();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    void spin(float dt);
    // non-virtual, unreferenced copies of parts of update()
    void end();
    void tickLife(float dt);
    bool checkFade();

public:
    int m_state;                                 // +0x318 0 flying, 1 ended, 2 bursting, 3 dead
    float m_time;                                // +0x31C (only cleared)
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for the burst
    bool m_ended;                                // +0x329
    float m_spinTime;                            // +0x32C
    int m_spinFrame;                             // +0x330 0..5
    int m_spinAnim;                              // +0x334 object animation of the next frame
    bool m_spinDirty;                            // +0x338 m_spinAnim not applied yet
};

