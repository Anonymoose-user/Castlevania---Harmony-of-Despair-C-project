// Dll/Shot/Psfishhsoul/ShotPsfishhsoul.h - dllshotpsfishhsoul's shot class
// (vtable ): the Fishhead soul ("PSフィッシュヘッド：ソウル",
// ShotInfo name). A spinning head thrown in an arc that bounces once on the
// floor, ends on a wall/ceiling hit, the second landing or after 5 s, then
// hops up and fades out. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotPsfishhsoul : public ShotBase {
public:
    ShotPsfishhsoul();                           // (DllCreate inlines it)
    virtual ~ShotPsfishhsoul();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void vfunc04C();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual, unreferenced copies of the end logic
    void end();
    void tickEnd(float dt);

public:
    int m_state;                                 // +0x318 0 flying, 1 ended, 2 hop and fade, 3 done
    float m_time;                                // +0x31C
    float m_dir;                                 // +0x320 -1 facing left, 1 right
    float m_fade;                                // +0x324 fade-out time (0..1)
    float m_angle;                               // +0x328 sprite rotation
    int m_bounced;                               // +0x32C landed once
};

