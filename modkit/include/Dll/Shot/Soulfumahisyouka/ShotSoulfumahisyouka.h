// Dll/Shot/Soulfumahisyouka/ShotSoulfumahisyouka.h - dllshotsoulfumahisyouka's
// shot class (vtable ): Getsu Fuma's Hisyouka soul
// ("ソウル　風魔　飛翔花", ShotInfo name). A flower creature that hops along
// the floor (arcs of -110 px/s up, 80 px/s forward, 320 px/s² gravity),
// turning at walls, for 3 s plus 0.25 s per kind step, then leaves an effect
// and dies. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfumahisyouka : public ShotBase {
public:
    ShotSoulfumahisyouka();                      // (DllCreate inlines it)
    virtual ~ShotSoulfumahisyouka();

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
    bool onFloor();
    bool onCeiling();
    void setDir(float d);
    void turn();
    bool wallAhead();
    void end();
    void tickEnd(float dt);
    bool takeEnd();

public:
    int m_state;                                 // +0x318 0 falling, 1 landed, 2 hopping, 3 ending, 4 done
    float m_wait;                                // +0x31C time on the floor
    float m_time;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endPending;                           // +0x328
    bool m_ended;                                // +0x329
    float m_life;                                // +0x32C
    unsigned int m_u330;                         // +0x330 never used by the module
};

