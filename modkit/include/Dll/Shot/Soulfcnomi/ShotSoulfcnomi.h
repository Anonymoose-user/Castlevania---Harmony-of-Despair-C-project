// Dll/Shot/Soulfcnomi/ShotSoulfcnomi.h - dllshotsoulfcnomi's shot class
// (vtable ): the Fleaman soul ("L. Nomi-otoko" in Japanese, ShotInfo
// name). A fleaman that hops along the floor: two low hops then a high one
// (or a high one after touching a wall), bouncing back from walls, for 3 s
// plus 0.25 s per kind step; then it plays its vanish sprite and dies.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcnomi : public ShotBase {
public:
    ShotSoulfcnomi();                            // (DllCreate inlines it)
    virtual ~ShotSoulfcnomi();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void vanish();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual helpers (only setDir is called; the rest are unreferenced)
    void setHitRect();
    void setFloorBox();
    void setCeilingBox();
    void setWallBoxes();
    void clearFloorBox();
    void clearCeilingBox();
    void clearWallBoxes();
    bool wallAhead();
    bool onFloor();
    bool onCeiling();
    void setDir(float d);
    void turn();
    void end();
    void tickEnd(float dt);
    bool takeEnd();

public:
    int m_state;                                 // +0x318 0 falling, 1 landed, 2 low hop, 3 high jump, 4 ending, 5 vanishing, 6 done
    float m_wait;                                // +0x31C time on the floor
    float m_time;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endPending;                           // +0x328
    bool m_ended;                                // +0x329
    float m_life;                                // +0x32C
    bool m_turnPending;                          // +0x330 touched a wall while rising: turn on landing
    bool m_highJump;                             // +0x331 touched a wall: next jump is high
    unsigned char m_hops;                        // +0x332 hops since the last high jump
};

