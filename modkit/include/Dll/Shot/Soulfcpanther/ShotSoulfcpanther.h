// Dll/Shot/Soulfcpanther/ShotSoulfcpanther.h - dllshotsoulfcpanther's shot
// class (vtable ): the black panther soul ("L. black
// panther", ShotInfo name). Leaps forward, lands, runs along the floor
// (turning at walls, leaping again off ledges) until its time is up (3 s +
// kind / 4) or it is ended, then bursts and dies. It uses the library's
// probe points (m_b230..m_b233 with m_v084..m_v0A0) and reads their results
// back from m_i234..m_i240. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcpanther : public ShotBase {
public:
    ShotSoulfcpanther();                         // (DllCreate inlines it)
    virtual ~ShotSoulfcpanther();

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
    bool hitCeiling();
    bool hitWall();
    bool offFloor();
    void turn(float dir);
    void turnAround();
    void end();
    void tickLife(float dt);
    bool checkFade();

public:
    int m_state;                                 // +0x318 0 leap, 1 run, 2 leap off a ledge, 3 ended, 4 bursting, 5 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for the burst
    bool m_ended;                                // +0x329
    float m_lifeMax;                             // +0x32C
};

