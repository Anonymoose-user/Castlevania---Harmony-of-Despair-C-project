// Dll/Shot/Glyphdextrocustos/ShotGlyphdextrocustos.h - dllshotglyphdextrocustos's
// shot class (vtable ): the glyph "Dextro Custos"
// ("Glyph De Custos" in katakana, ShotInfo name), Shanoa's familiar arm. It drops in
// beside the owner, decelerates, fades out over 0.3 s and kills itself; it
// follows the owner's anchor (getV300) and floats up while the owner is in
// one of a few states. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotGlyphdextrocustos : public ShotBase {
public:
    ShotGlyphdextrocustos();                     // (DllCreate inlines neither)
    virtual ~ShotGlyphdextrocustos();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void vfunc038(const int* a, void* b, bool c);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

public:
    int m_state;                                 // +0x318 0 placing, 1 sliding, 2 fading, 3 dead
    float m_time;                                // +0x31C
    float m_dir;                                 // +0x320 -1 facing left, 1 right
    float m_accel;                               // +0x324
    float m_speed;                               // +0x328
    float m_offX;                                // +0x32C offset from the owner's anchor
    float m_offY;                                // +0x330
    float m_lift;                                // +0x334 0..16, extra height
    bool m_lifted;                               // +0x338 owner state is one that lifts
};

