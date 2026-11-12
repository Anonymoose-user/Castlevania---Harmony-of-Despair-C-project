// Dll/Shot/Soulfcmummy/ShotSoulfcmummy.h - dllshotsoulfcmummy's shot class
// (vtable ): the Mummy Man soul ("L. Mummy Man" in
// Japanese, the ShotInfo name). Attached to its owner (m_i284 == 0) it is a
// summoner: after start it spawns one to three bandage records (addElem274,
// by soul level) and ends a second later. Detached, it flies along the given
// direction at speed 90, bobbing on a 1.5 s sine wave, and ends after 3 s or
// on any hit / vanish. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcmummy : public ShotBase {
public:
    ShotSoulfcmummy();                           // (DllCreate inlines it)
    virtual ~ShotSoulfcmummy();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void vfunc04C();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    void unused0724();                         // an empty member no vtable uses
    void tickLife(float dt);
    void updateSummon(float dt);
    void updateFly(float dt);
    // non-virtual, unreferenced copies of parts of the above
    void end();
    bool checkFade();

public:
    int m_state;                                 // +0x318 summon: 1 spawn, 2 wait, 3, 5 die; fly: 0, 3, 4, 5 die
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for state 3
    bool m_ended;                                // +0x329
    bool m_fly;                                  // +0x32A detached flier
    bool m_blink;                                // +0x32B
    float m_wave;                                // +0x32C bob phase time, 0..1.5 s
    Vec2 m_base;                                 // +0x330 position without the bob
    Vec2 m_vel;                                  // +0x338 flight velocity
};

