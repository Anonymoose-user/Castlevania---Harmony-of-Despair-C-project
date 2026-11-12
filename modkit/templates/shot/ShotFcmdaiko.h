// Dll/Shot/Fcmdaiko/ShotFcmdaiko.h - dllshotfcmdaiko's shot class (vtable
// ): Getsu Fuma's guard drum ("FC月風魔：守り太鼓",
// ShotInfo name). Spawned in front of the owner, it waits 0.7 s (or until
// vanish()) and then kills itself. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFcmdaiko : public ShotBase {
public:
    ShotFcmdaiko();                              // (DllCreate inlines it)
    virtual ~ShotFcmdaiko();

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

    // non-virtual, unreferenced copies of the vanish logic
    void end();
    void tickEnd(float dt);

public:
    int m_state;                                 // +0x318 0 waiting, 1 ending
    float m_time;                                // +0x31C
    float m_dir;                                 // +0x320 -1 facing left, 1 right
};

