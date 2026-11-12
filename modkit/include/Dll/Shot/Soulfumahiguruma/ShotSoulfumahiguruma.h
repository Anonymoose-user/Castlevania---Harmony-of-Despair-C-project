// Dll/Shot/Soulfumahiguruma/ShotSoulfumahiguruma.h - dllshotsoulfumahiguruma's
// shot class (vtable ): the Getsu Fuma fire-wheel
// soul ("Soul Fuma Higuruma", ShotInfo name). Bounces forward: leaps, lands,
// leaps again, turning at walls, until its time is up (3 s + kind / 4) or it
// is ended; then it leaves a burst record and dies. It uses the library's
// probe points (m_b230..m_b233 with m_v084..m_v0A0) and reads their results
// back from m_i234..m_i240. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfumahiguruma : public ShotBase {
public:
    ShotSoulfumahiguruma();                      // (DllCreate inlines it)
    virtual ~ShotSoulfumahiguruma();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void vanish();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual helpers (most inlined into start() / update(), unreferenced)
    void initRect();
    void setFrontProbe();
    void setFloorProbe();
    void setSideProbes();
    void clearFrontProbe();
    void clearFloorProbe();
    void clearSideProbes();
    void setWideSideProbes();
    bool hitCeiling();
    void turn(float dir);
    void turnAround();
    bool hitWall();
    bool offFloor();
    void end();
    void tickLife(float dt);
    bool checkFade();

public:
    int m_state;                                 // +0x318 0 leap, 1 rolling, 2 leap, 3 fall (wide probes), 4 ended, 5 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for the burst
    bool m_ended;                                // +0x329
    float m_lifeMax;                             // +0x32C
};

