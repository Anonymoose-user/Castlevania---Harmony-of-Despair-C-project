// Dll/Shot/Fumaryukotsusoul/ShotFumaryukotsusoul.h - dllshotfumaryukotsusoul's
// shot class (vtable ): the Ryukotsuki soul
// ("Getsu Fuma Den Ryukotsuki: Soul", the ShotInfo name). One to three bone-dragon objects
// (more for higher soul levels) held in front of the owner; it ends after
// 5 s (1.5 s when detached, m_i284), on vanish()/onHit() when detached, or when
// object 0's animation reports done. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFumaryukotsusoul : public ShotBase {
public:
    ShotFumaryukotsusoul();                      // (DllCreate inlines it)
    virtual ~ShotFumaryukotsusoul();

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

    // non-virtual, unreferenced
    void place(bool keep);
    void end();
    void tickEnd(float dt);

public:
    int m_state;                                 // +0x318 0 active, 1 ending
    unsigned char _pad31C[4];                    // never touched
    float m_time;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    unsigned char _pad328[8];                    // never touched
};

