// Dll/Shot/Soulfcwhitedra/ShotSoulfcwhitedra.h - dllshotsoulfcwhitedra's shot
// class (vtable ): the White Dragon soul ("L. White
// Dragon" in full-width katakana, the ShotInfo name). A bone serpent: a head
// object and 16 segment objects (list B) laid along a quadratic Bezier curve
// from the owner's anchor. It rises out of the owner (phase 0), sways
// (phase 1), lunges forward on a hit request (getB05A, phase 2) and sinks
// back (phase 3) when the owner lets go (getB1F1), then dies. It turns with
// the owner's facing. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcwhitedra : public ShotBase {
public:
    ShotSoulfcwhitedra();                        // (calls )
    virtual ~ShotSoulfcwhitedra();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    void setFlip(int flip);
    void placeObjs();
    Vec2 bezier(const Vec2* a, const Vec2* b, const Vec2* c, float t) const;
    void turnUpdate(float dt);
    void lungeUpdate(float dt);
    void sway(float dt);
    static void clearVec(Vec2* v);               // (unreferenced)

public:
    int m_state;                                 // +0x318 cleared, otherwise unused (m_phase is the state)
    float m_time;                                // +0x31C turn timer
    float m_lungeTime;                           // +0x320
    float m_swayPhase;                           // +0x324
    bool m_left;                                 // +0x328 facing left
    unsigned char _pad329[3];
    float m_side;                                // +0x32C -1 / 1: the side the body is bent to
    bool m_b330;                                 // +0x330 cleared, unused
    unsigned char _pad331[3];
    int m_i334;                                  // +0x334 cleared, unused
    int m_i338;                                  // +0x338 cleared, unused
    bool m_b33C;                                 // +0x33C cleared, unused
    bool m_shown;                                // +0x33D set by vfunc01C()
    unsigned char _pad33E[2];
    Vec2 m_anchor;                               // +0x340 the owner's anchor (m_v048)
    int m_phase;                                 // +0x348 0 rise, 1 sway, 2 lunge, 3 sink, 4 dead
    Vec2 m_head;                                 // +0x34C
    Vec2 m_segs[16];                             // at 0x354: segment positions
    float m_extend;                              // +0x3D4 0..1 along the curve
};

