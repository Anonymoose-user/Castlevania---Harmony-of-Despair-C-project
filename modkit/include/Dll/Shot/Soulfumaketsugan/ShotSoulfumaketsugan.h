// Dll/Shot/Soulfumaketsugan/ShotSoulfumaketsugan.h - dllshotsoulfumaketsugan's
// shot class (vtable ): Getsu Fuma's Ketsugan soul
// ("ソウル　風魔　毛細血眼", ShotInfo name). The eye appears in front of the
// owner, blinks for 0.2 s, after 0.2 s drops one trail record (unless the
// ground probe ShotBase::m_probe says the two points in front differ),
// then plays its closing animation, adds an effect record and dies. Names
// are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfumaketsugan : public ShotBase {
public:
    ShotSoulfumaketsugan();                      // (DllCreate inlines it)
    virtual ~ShotSoulfumaketsugan();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

public:
    int m_state;                                 // +0x318 0 open, 1 closing, 2 end
    float m_time;                                // +0x31C until the trail record (0.2 s)
    float m_dir;                                 // +0x320 -1 facing left, 1 right
    bool m_b324;                                 // +0x324
    bool m_b325;                                 // +0x325
    bool m_trailDone;                            // +0x326 trail record made (or not wanted)
    unsigned char _pad327[0x1];
    float m_blink;                               // +0x328 blink time (0.2 s)
};

