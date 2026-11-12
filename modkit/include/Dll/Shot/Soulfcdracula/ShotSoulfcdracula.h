// Dll/Shot/Soulfcdracula/ShotSoulfcdracula.h - dllshotsoulfcdracula's shot
// class (vtable ): the FC Dracula soul (ShotInfo
// name "Soul L.Dracula" in Japanese). A small Dracula that hops along the
// floor, turning at walls, blinks after 2 s and is gone at 2.5 s.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcdracula : public ShotBase {
public:
    ShotSoulfcdracula();                         // (DllCreate inlines it)
    virtual ~ShotSoulfcdracula();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual helpers (the collision boxes and floor/wall queries; most
    // are unreferenced)
    void setHitRect();
    void setFloorProbe();
    void setCeilingProbe();
    void setWallProbes();
    void followFloor();
    bool onFloor();
    void setFloorProbeLanded();
    bool onCeiling();
    void setDir(float dir);
    void turn();
    bool facingWall();
    void clearWallProbes();
    void clearCeilingProbe();
    void clearFloorProbe();

public:
    int m_state;                                 // +0x318 0 in the air, 1 landing, 2 on the floor
    float m_time;                                // +0x31C landing time
    float m_life;                                // +0x320 blinks from 2 s, dies at 2.5 s
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_blink;                                // +0x328
};

