// Dll/Shot/Soulfcmedusa/ShotSoulfcmedusa.h - dllshotsoulfcmedusa's shot class
// (vtable ): the Medusa soul ("L.medyuusa", ShotInfo
// name). Two modes, chosen by m_i284 at start():
//  - summoner (m_i284 == 0): spawns one to three pairs of heads (ShotElem274
//    records, mirrored left / right; more for higher kind bytes), waits 1 s
//    and dies;
//  - head (m_i284 != 0): falls to the ground and slides along it until a
//    wall, 3 s, or vanish ends it.
// The library's m_i234 / m_i23C / m_i240 are ints here (ground offset, wall
// flags), as in dllshotsoulfczombi. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcmedusa : public ShotBase {
public:
    ShotSoulfcmedusa();                          // (DllCreate inlines it)
    virtual ~ShotSoulfcmedusa();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void vanish();
    virtual void vfunc04C();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual helpers (tickLife and the two updates are called)
    void fallProbe();
    void setFeet();
    void end();
    void tickLife(float dt);
    bool beginUpdate();
    void updateSummoner(float dt);
    void landProbe();
    void snapToGround();
    bool onGround();
    bool hitWall();
    void updateHead(float dt);
    void clearFeet();
    void clearProbe();

public:
    int m_state;                                 // +0x318 head 0 slide, 1 fall; summoner 2 spawn, 3 wait; 4 end, 5 fade, 6 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endRequest;                           // +0x328
    bool m_ended;                                // +0x329
    bool m_isHead;                               // +0x32A
    bool m_blink;                                // +0x32B
};

