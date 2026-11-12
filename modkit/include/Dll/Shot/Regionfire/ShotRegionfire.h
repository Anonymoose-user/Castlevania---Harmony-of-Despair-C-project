// Dll/Shot/Regionfire/ShotRegionfire.h - dllregionfire's shot class (vtable
// ): the Legion's fire ("レギオン：ファイア", ShotInfo
// name). A flame of one of three looks (picked by a host random number) that
// grows to double size, vanishes after 10 s or 200 units from where it
// started, and then fades out over 0.2 s. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotRegionfire : public ShotBase {
public:
    ShotRegionfire();                            // (DllCreate inlines it)
    virtual ~ShotRegionfire();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);


public:
    float m_time;                                // +0x318 seconds since start()
    float m_fade;                                // +0x31C fade-out time left (0.2 s)
    float m_grow;                                // +0x320 0..1, the scale is 1 + m_grow
    bool m_ending;                               // +0x324 fading out
    unsigned char _pad325[0x3];
    int m_state;                                 // +0x328 4 once the fade-out is over
    Vec2 m_origin;                               // +0x32C position at start()
};

