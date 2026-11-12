// Dll/Shot/Psukobachfire/ShotPsukobachfire.h - dllshotpsukobachfire's shot
// class (vtable ): the Ukoback's fireball
// (ShotInfo name "PS Yukobakku: hi no tama"). It fades in over 0.2 s, lives 5 s
// (10 s when getB314() is false), then shrinks away and kills itself.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotPsukobachfire : public ShotBase {
public:
    ShotPsukobachfire();                         // (DllCreate inlines it)
    virtual ~ShotPsukobachfire();

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

    // non-virtual, unreferenced copies of the ending logic
    void end();
    void tickEnd(float dt);

public:
    int m_state;                                 // +0x318 0 alive, 1 shrinking, 2 gone
    float m_time;                                // +0x31C
    float m_life;                                // +0x320 5 or 10 s
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    float m_scale;                               // +0x328 1 -> 0 while shrinking
    float m_fadeIn;                              // +0x32C 0 -> 0.2 s
    bool m_short;                                // +0x330 getB314() at start: 5 s, offset spawn
};

