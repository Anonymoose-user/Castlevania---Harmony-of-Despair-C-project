// Dll/Shot/Soulfumadokugan/ShotSoulfumadokugan.h - dllshotsoulfumadokugan's
// shot class (vtable ): the one-eyed Dokugan soul
// ("Soul Fuma Dokugan Dokuto", ShotInfo name). m_i284 packs the mode (low
// nibble) and the soul level (next nibble):
//   0  the summoned head: blinks while it spits one (or, detached, two) fire
//      shots, then fades;
//   1  a fire shot: flies along its start velocity with probes; a hit on a
//      wall spreads up to four sparks and a pillar (by level), then bursts;
//   2  a pillar part falling under gravity;
//   3  the three-object pillar, turned to the wall it grows from;
//   4  a falling ember that leaves a burst record.
// All of them end after 3 s. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfumadokugan : public ShotBase {
public:
    ShotSoulfumadokugan();                       // (DllCreate inlines it)
    virtual ~ShotSoulfumadokugan();

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

    void end();
    void tickLife(float dt);
    bool checkFade();
    void updateEmber(float dt);                  // (mode 4)
    void updatePillar(float dt);                 // (mode 3)
    void updatePart(float dt);                   // (mode 2)
    void blinkStep();
    void updateFire(float dt);                   // (mode 1)
    void updateHead(float dt);                   // (mode 0)

public:
    int m_state;                                 // +0x318 0 head spits, 1 head waits, 2 fire flies, 3 fire bursts, 4..6 mode 2..4, 7 ended, 8 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for the end
    bool m_ended;                                // +0x329
    unsigned short m_blink;                      // +0x32A 0..6
    bool m_detached;                             // +0x32C the head was not started by the owner (getB314() false)
    int m_count;                                 // +0x330 fire shots spat
    int m_mode;                                  // +0x334 m_i284 & 0xF (5 until start())
    int m_level;                                 // +0x338 (m_i284 >> 4) & 0xF
};

