// Dll/Shot/Fccurseexpl/ShotFccurseexpl.h - dllshotfccurseexpl's shot class
// (vtable ): Getsu Fuma's cursed explosive ("FC Getsu
// Fuma: noroi no bakuyaku", ShotInfo name). Two modes, by m_i284 at start():
//  - bomb (m_i284 == 0): thrown forward, falls until it touches ground or a
//    wall (or 1 s passes), then bursts into 3-5 fragments (ShotElem274
//    records spread over 180 degrees) and dies;
//  - fragment (m_i284 != 0): flies at the angle in the low byte of m_i284
//    for 0.4 s and dies.
// The library's m_i234..m_i240 are ints here (ground / wall flags).
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFccurseexpl : public ShotBase {
public:
    ShotFccurseexpl();                           // (DllCreate inlines it)
    virtual ~ShotFccurseexpl();

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

    // non-virtual, unreferenced copies of parts of update / vanish
    void end();
    void tickTimer(float dt);

public:
    int m_state;                                 // +0x318 0 flying, 1 burst, 2 dead
    float m_time;                                // +0x31C
    float m_duration;                            // +0x320 1 s (bomb) / 0.4 s (fragment)
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_isBomb;                               // +0x328
};

