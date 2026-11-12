// Dll/Shot/Glyphglobus/ShotGlyphglobus.h - dllshotglyphglobus's shot class
// (vtable ): Shanoa's Globus glyph ("gurobusu",
// ShotInfo name), a bouncing orb. Launched at +-15 degrees (by m_i284; the
// main orb, m_i284 == 0, also spawns its partner through a ShotElem274 record),
// it flies at 400 px/s, reflects off the surface normal (m_v0A4) when it hits
// in a new 16 px cell, and fades out after its life (4.5 s + 0.25 s a kind
// level) or its fifth bounce. A ShotElem174 trail follows it.
// The library's m_i234..m_i240 are ints here (collision flags).
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotGlyphglobus : public ShotBase {
public:
    ShotGlyphglobus();
    virtual ~ShotGlyphglobus();

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

    void addTrail();
    void setAlpha(float a);
    void setVisible(bool v);
    void moveTrail();
    void end();
    void tickLife(float dt);
    bool beginUpdate();
    void markTrail();
    int classifyHit(unsigned int flags);
    void tickBlink(float dt);

public:
    int m_state;                                 // +0x318 0 launch, 1 fly, 2 fade, 3 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_lifeMax;                             // +0x324
    bool m_endRequest;                           // +0x328
    bool m_ended;                                // +0x329
    unsigned char _pad32A[2];
    int m_cellX;                                 // +0x32C last bounce cell (16 px)
    int m_cellY;                                 // +0x330
    float m_blinkTime;                           // +0x334
    bool m_blinkDone;                            // +0x338
    bool m_launched;                             // +0x339
    unsigned char _pad33A[2];
    int m_trail;                                 // +0x33C ShotElem174 index
    bool m_hit;                                  // +0x340 set by onHit, counted by beginUpdate
    unsigned char _pad341[3];
    int m_bounces;                               // +0x344
    bool m_markTrail;                            // +0x348
};

