// Dll/Shot/Soulfumahannya/ShotSoulfumahannya.h - dllshotsoulfumahannya's shot
// class (vtable ): the Kimen Hannya soul ("Soul Fuma
// Kimen Hannya" in Japanese, the ShotInfo name). A demon mask that walks
// forward at 160 while publishing a search box ahead of it (setV2A0 /
// setF2A8 / setV2BC); when the host reports a target (getI2B4 / getB2C4) it
// moves vertically to the target's height, then turns toward it and walks on.
// It ends after 3 s + 0.25 s per soul level or on any hit, leaving an
// effect record (addElem1A4). Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfumahannya : public ShotBase {
public:
    ShotSoulfumahannya();                        // (DllCreate inlines it)
    virtual ~ShotSoulfumahannya();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    void face(float dx);
    // non-virtual, unreferenced copies of parts of update()
    void end();
    void tickLife(float dt);
    bool checkFade();

public:
    int m_state;                                 // +0x318 0 walk, 1 found, 2 climb, 3 turned, 4 end, 5 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for state 4
    bool m_ended;                                // +0x329
    unsigned char _pad32A[2];
    float m_limit;                               // +0x32C life limit
};

