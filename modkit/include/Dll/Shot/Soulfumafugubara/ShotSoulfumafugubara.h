// Dll/Shot/Soulfumafugubara/ShotSoulfumafugubara.h - dllshotsoulfumafugubara's
// shot class (vtable ): the Fugubara soul ("Soul Fuma
// Fugubara" in Japanese, the ShotInfo name). A puffer that hops along the
// ground: it falls (gravity 640) until the host reports ground contact
// (ShotBase m_i234), then walks at 80 with wall probes
// (m_v094 / m_v09C, flags +0x232 / +0x233) and ends on hitting a wall, after
// 3 s + 0.25 s per soul level, or on vanish. The library fields +0x230..+0x240
// are used as ground/wall state here. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfumafugubara : public ShotBase {
public:
    ShotSoulfumafugubara();                      // (DllCreate inlines it)
    virtual ~ShotSoulfumafugubara();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void update(float dt);
    virtual void vanish();
    virtual void vfunc04C();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual helpers, all unreferenced (update() has them inline)
    void unused050C();                         // an empty member no vtable uses
    void setWallProbes();
    void clearWallProbes();
    void snapToGround();
    void hopSmall();
    bool onGround();
    void end();
    bool hitWall();
    void hopBig();
    void tickLife(float dt);
    bool checkFade();
    void clearB230();
    void face(float d);
    void turn();

public:
    int m_state;                                 // +0x318 0 start, 1 falling, 2 walking, 3 end, 4 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for state 3
    bool m_ended;                                // +0x329
    unsigned char _pad32A[2];
    float m_limit;                               // +0x32C life limit
};

