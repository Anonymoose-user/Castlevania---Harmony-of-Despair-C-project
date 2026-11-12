// Dll/Shot/Soulfumasimon/ShotSoulfumasimon.h - dllshotsoulfumasimon's shot
// class (vtable ): the Shimon soul ("Soul Fuma Shimon"
// in Japanese, the ShotInfo name), a skeleton that drops to the ground and
// walks at 60, turning at walls (the library's ground / wall fields +0x230..
// +0x240); when the host reports a target ahead (getB29D false)
// it stops and attacks (animation 1; at frame 4 it queues a hit box,
// queueElem1B4), then walks on. It ends after 3 s + 0.25 s per soul level,
// leaving an effect record (addElem1A4). Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfumasimon : public ShotBase {
public:
    ShotSoulfumasimon();                         // (DllCreate inlines it)
    virtual ~ShotSoulfumasimon();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void vanish();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual helpers, all unreferenced but face() (update() has the rest inline)
    void hopSmall();
    void setWallProbes();
    void clearWallProbes();
    void snapToGround();
    void hopZero();
    bool onGround();
    void face(float d);
    void turn();
    bool hitWall();
    void end();
    void tickLife(float dt);
    bool checkFade();
    void clearB230();

public:
    int m_state;                                 // +0x318 0 start, 1 falling, 2 walking, 3 attacking, 4 end, 5 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for state 4
    bool m_ended;                                // +0x329
    unsigned char _pad32A[2];
    float m_limit;                               // +0x32C life limit
    bool m_grounded;                             // +0x330 was on the ground last frame
    unsigned char _pad331[3];
    int m_attack;                                // +0x334 the owner's getI1F8() at start (attack power)
};

