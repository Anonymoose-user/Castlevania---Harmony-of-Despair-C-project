// Dll/Shot/Psfishhshot/ShotPsfishhshot.h - dllshotpsfishhshot's shot class
// (vtable ): the fish head's shot ("PS fish head:
// shot", ShotInfo name). Flies straight ahead; once ended (a hit, vanish(),
// or 300 s) it bursts into effect records and kills itself. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotPsfishhshot : public ShotBase {
public:
    ShotPsfishhshot();                           // (DllCreate inlines it)
    virtual ~ShotPsfishhshot();

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
    int m_state;                                 // +0x318 0 flying, 1 ended (bursts next update)
    float m_time;                                // +0x31C
    float m_dir;                                 // +0x320 -1 facing left, 1 right
};

