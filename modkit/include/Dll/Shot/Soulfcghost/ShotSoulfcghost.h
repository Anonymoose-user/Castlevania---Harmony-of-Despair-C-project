// Dll/Shot/Soulfcghost/ShotSoulfcghost.h - dllshotsoulfcghost's shot class (vtable
// ): the Ghost soul (ShotInfo name "FC Goosuto" in
// Japanese). One to three ghosts (by kind) float around the owner; the first
// queues the others (ShotElem274 records) and passes its flags on through a
// pointer to its +0x371. Now and then a ghost asks the original game for a target
// (IShot +0x4EC.. / +0x524..) and homes in on it slowly (turning at most
// 0.03 rad a frame) for up to 3 s, then drifts back. They blink out when the
// owner's flags say so. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcghost : public ShotBase {
public:
    ShotSoulfcghost();                             // (thunk), (DllCreate calls )
    virtual ~ShotSoulfcghost();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual (faceSide is unreferenced)
    void faceDir(float d);
    float angleTo(const Vec2* from, const Vec2* to);
    void faceVelocity();
    float clampDist(const Vec2* a, const Vec2* b, float maxDist);
    void faceSide(int side);

public:
    int m_state;                                 // +0x318 0 new, 1 placed, 2 circling, 3 homing, 4 done
    int m_sub;                                   // +0x31C homing step
    Vec2 m_home;                                 // +0x320 the point it circles to
    Vec2 m_target;                               // +0x328 the target (IShot +0x538)
    Vec2 m_moveDir;                              // +0x330 homing direction
    int m_i338;                                  // +0x338 cleared, never read
    int m_i33C;                                  // +0x33C cleared, never read
    float m_speed;                               // +0x340
    float m_cruise;                              // +0x344 floating speed (70..140)
    float m_phase;                               // +0x348 circling phase
    float m_time;                               // +0x34C
    int m_chance;                                // +0x350 1 in m_chance per frame to look for a target
    float m_heading;                             // +0x354 angle of travel
    float m_cooldown;                            // +0x358
    int m_index;                                 // +0x35C ghost number (0 leads)
    int m_count;                                 // +0x360 ghosts in the group
    bool m_canSwoop;                             // +0x364 fully faded in
    bool m_leaving;                              // +0x365 owner flag 1 seen: blink out
    bool m_hasTarget;                            // +0x366
    bool m_seeking;                              // +0x367 target request pending
    int m_targetId;                              // +0x368
    float m_blinkTime;                           // +0x36C
    bool m_visible;                              // +0x370 blink phase
    bool m_flag1;                                // +0x371 owner flags the lead bat copies (followers read them)
    bool m_flag2;                                // +0x372
};

