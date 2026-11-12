// Dll/Shot/Glyphsinestrocustos/ShotGlyphsinestrocustos.h - dllshotglyphsinestrocustos's
// shot class (vtable ): Shanoa's Sinestro Custos glyph
// ("gurifu shisu kusutoosu", ShotInfo name), the guardian that slides out
// beside the owner, holds, fades out and dies. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotGlyphsinestrocustos : public ShotBase {
public:
    ShotGlyphsinestrocustos();
    virtual ~ShotGlyphsinestrocustos();

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
    int m_state;                                 // +0x318 0 rise, 1 slide, 2 fade, 3 dead
    float m_time;                                // +0x31C
    float m_dir;                                 // +0x320 -1 facing left, 1 right
    float m_accel;                               // +0x324
    float m_speed;                               // +0x328
    float m_offX;                                // +0x32C offset from the owner (getV300)
    float m_offY;                                // +0x330
    float m_lift;                                // +0x334 extra height while the owner poses
    bool m_raised;                               // +0x338 owner in one of the raising states
};

