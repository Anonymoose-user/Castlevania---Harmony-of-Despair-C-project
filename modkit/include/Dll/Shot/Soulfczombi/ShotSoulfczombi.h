// Dll/Shot/Soulfczombi/ShotSoulfczombi.h - dllshotsoulfczombi's shot class
// (vtable ): the zombie soul ("L.zonbi", ShotInfo
// name). The zombie drops to the ground, then walks forward, turning at
// walls, until its life (3 s + 0.25 s per kind level) runs out or it is
// vanished. Names are inferred.
//
// The library's m_i234 / m_i23C / m_i240 are really ints here: the ground
// offset under the feet (0: in the air) and the left / right wall flags.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfczombi : public ShotBase {
public:
    ShotSoulfczombi();                           // (DllCreate inlines it)
    virtual ~ShotSoulfczombi();

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
    void landProbe();
    void setFeet();
    void clearFeet();
    void snapToGround();
    void fallProbe();
    bool onGround();
    void setDir(float dir);
    void turn();
    bool hitWall();
    void end();
    void tickLife(float dt);
    bool beginUpdate();
    void clearProbe();

public:
    int m_state;                                 // +0x318 0 drop, 1 fall, 2 walk, 3 end, 4 fade, 5 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320 seconds alive
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endRequest;                           // +0x328
    bool m_ended;                                // +0x329
    unsigned char _pad32A[2];
    float m_lifeMax;                             // +0x32C
};

