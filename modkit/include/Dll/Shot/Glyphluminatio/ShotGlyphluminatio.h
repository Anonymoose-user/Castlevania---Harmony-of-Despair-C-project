// Dll/Shot/Glyphluminatio/ShotGlyphluminatio.h - dllshotglyphluminatio's shot
// class (vtable ): Shanoa's Luminatio glyph ("グリフ
// ルミナーレ", ShotInfo name). A ball of light that appears in front of the
// owner, grows a halo, swings half a turn up around its start point, circles
// once more, then spirals outwards with its halo fading and dies. Besides the
// model it draws a 16-segment halo disc (IShot +0x03C fills the vertices and
// the placement matrix). Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotGlyphluminatio : public ShotBase {
public:
    ShotGlyphluminatio();                        // (thunk), (DllCreate calls )
    virtual ~ShotGlyphluminatio();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void vfunc03C(const int* a, ShotVertex* verts, ShotMatrix4* m);   // halo disc
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // the inlined vectormath placement: *m = T(tx, ty, tz) * R(rx, ry, rz)
    // * S(sx, sy, 1) (non-virtual; this is unused)
    void buildMatrix(float* m, float tx, float ty, float sx, float sy, float rx, float ry, float rz, float tz);
    // buildMatrix() for a sprite of the module's size (m_f008 x m_f00C over
    // m_f004) centred on (x, y), turned by angle (unreferenced)
    void placeMatrix(float* m, float x, float y, float sx, float sy, float angle);

public:
    int m_state;                                 // +0x318 0 appear, 1 halo in, 2 swing, 3 circle, 4 spiral, 5 fade, 6 end
    float m_time;                                // +0x31C time spiralling
    float m_dir;                                 // +0x320 -1 facing left, 1 right
    bool m_ending;                               // +0x324 forces the fade (state >= 5)
    unsigned char _pad325[0x3];
    Vec2 m_center;                               // +0x328 the point it circles
    Vec2 m_offset;                               // +0x330 offset from m_center last frame
    int m_i338;                                  // +0x338 (unused)
    float m_radius;                              // +0x33C
    float m_speed;                               // +0x340 radius growth while spiralling
    float m_angle;                               // +0x344
    float m_angleBase;                           // +0x348 -pi at level 0
    float m_fade;                                // +0x34C halo fade timer
    float m_halo;                                // +0x350 halo radius
};

