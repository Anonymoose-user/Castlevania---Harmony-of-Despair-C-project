// Dll/Shot/Glyphacerbatus/ShotGlyphacerbatus.h - dllshotglyphacerbatus's
// shot class (vtable ): the Acerbatus glyph
// ("アケルブス", ShotInfo name), a spinning ring thrown forward that slows
// down, flies on for 0.8 s and comes back (object A 0), trailed by three
// pulsing ring images (objects A 1-3, timed by m_rings). It fades out over
// 0.3 s once its throw animation ends, at most 30 s. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

// one trail image's timer (8 bytes)
struct GlyphRing {
    float t;                                     // +0x0 seconds, starts at -0.1 * index
    bool shown;                                  // +0x4 took the current angle this cycle
    bool done;                                   // +0x5 hidden for good
};

typedef std::vector<GlyphRing, DllAllocator<GlyphRing> > GlyphRingVec;

class ShotGlyphacerbatus : public ShotBase {
public:
    ShotGlyphacerbatus();
    virtual ~ShotGlyphacerbatus();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void vfunc04C();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    void tickRings(float dt);
    // non-virtual, unreferenced copies of parts of update() / the hooks
    void end();
    void tickLife(float dt);
    bool checkFade();
    void pause();

public:
    int m_state;                                 // +0x318 0 thrown, 1 flying, 2 turning, 3 back, 4 fading, 5 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_fadeReq;                              // +0x328
    bool m_ended;                                // +0x329
    float m_launchSpeed;                         // +0x32C
    float m_accel;                               // +0x330
    float m_angle;                               // +0x334
    float m_spin;                                // +0x338 4 pi per second
    float m_pauseTime;                           // +0x33C
    bool m_paused;                               // +0x340
    Vec2 m_savedVel;                             // +0x344
    GlyphRingVec m_rings;                        // +0x34C
    bool m_ringsStop;                            // +0x35C
};

