// Dll/Shot/Fchadouken/ShotFchadouken.h - dllshotfchadouken's shot class
// (vtable ): Getsu Fuma's wave-motion sword
// ("FC月風魔：波動剣", ShotInfo name). A charge level below 0xFF (ShotBase
// m_i284) makes it spawn 1-3 wave records (addElem274) and die at once;
// otherwise it is a flying slash that ends after 0.46 s (or on vanish /
// onHit / the +0x04C / +0x050 hooks). Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFchadouken : public ShotBase {
public:
    ShotFchadouken();
    virtual ~ShotFchadouken();

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
};

