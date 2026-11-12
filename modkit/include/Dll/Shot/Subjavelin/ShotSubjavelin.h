// Dll/Shot/Subjavelin/ShotSubjavelin.h - dllshotsubjavelin's shot class
// (vtable ): the javelin sub-weapon ("ジャベリン",
// ShotInfo name). Thrown forward and slightly up, it falls under gravity
// with its sprite turned along the flight; a hit stops it, it then waits
// 0.5 s, fades out over 0.5 s and dies (30 s at most). Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSubjavelin : public ShotBase {
public:
    ShotSubjavelin();                            // (DllCreate inlines it)
    virtual ~ShotSubjavelin();

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

    void aim();
    // non-virtual, unreferenced copies of parts of update()
    void end();
    void tickLife(float dt);
    bool checkFade();

    // the SDK's Dinkumware atan2f (fatan2.c / xfatan.c / xfdtest.c)
    static float atan2f(float y, float x);
    static float atanReduced(float x, unsigned int idx);
    static int fdtest(const float* p);

public:
    int m_state;                                 // +0x318 0 flying, 1 stuck, 2 fading, 3 dead
    float m_time;                               // +0x31C time in states 1 and 2
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for the fade
    bool m_ended;                                // +0x329
};

