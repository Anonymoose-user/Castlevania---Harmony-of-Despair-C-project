// Dll/Shot/Soulfumakyokotsu/ShotSoulfumakyokotsu.h - dllshotsoulfumakyokotsu's
// shot class (vtable ): Getsu Fuma's Kyokotsu
// Gyugai soul (ShotInfo name "Soul Fuma Kyokotsu Gyugai" in Japanese), a
// skeletal ox that appears beside its anchor (the getV300() point), blinks
// in, charges forward and fades. Three modes by getI284(): 0 the summoned
// ox (spawns up to two followers, ShotElem274 records, by the kind byte),
// 1 a follower tied to an original game record (ShotBase::m_ownerLink, read and
// written back every frame in preUpdate), 2 a charge-only variant.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

// The record a mode-1 shot follows (the original game owns it; 0x1C bytes).
struct KyokotsuLink {
    Vec2 off;                    // +0x00 position relative to getV048()
    bool done;                   // +0x08 leave now
    bool visible;                // +0x09 written back by the shot
    unsigned char _pad0A[2];
    int phase;                   // +0x0C 1: start the charge (cleared by the shot)
    float dir;                   // +0x10 charge direction
    unsigned char frame;         // +0x14 first animation frame
    bool active;                 // +0x15 written back by the shot
    unsigned char _pad16[2];
    int i18;
};

class ShotSoulfumakyokotsu : public ShotBase {
public:
    ShotSoulfumakyokotsu();                      // (calls; DllCreate too)
    virtual ~ShotSoulfumakyokotsu();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void preUpdate(float dt);
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void vfunc04C();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    // non-virtual helpers
    // unreferenced
    bool takeEnd();
    // mode 2
    void updateCharge(float dt);
    void setDir(float dir);
    // unreferenced; inlined in the updates
    void nextFrame();
    // unreferenced
    void setDirFlag(int right);
    // mode 1
    void updateFollower(float dt);
    // unreferenced
    void end();
    // mode 0
    void updateSummon(float dt);

public:
    int m_state;                                 // +0x318
    float m_time;                                // +0x31C
    float m_dir;                                 // +0x320 -1 facing left, 1 right
    bool m_endReq;                               // +0x324
    bool m_ended;                                // +0x325
    unsigned short m_frame;                      // +0x326 animation frame index 0-6
    int m_flags;                                 // +0x328 getI1F8() at vfunc01C
    unsigned char m_index;                       // +0x32C follower index (getI284() of a summon)
    unsigned char _pad32D[0x3];
    float m_spawnTime;                           // +0x330
    bool m_spawned;                              // +0x334
    unsigned char _pad335[0x3];
    KyokotsuLink* m_linkRec;                     // 0x338 (original pointer; not a test field)
    // +0x33C: a copy of *m_linkRec (preUpdate), mode 1
    float m_linkX;                               // +0x33C
    float m_linkY;                               // +0x340
    bool m_linkDone;                             // +0x344
    bool m_visible;                              // +0x345
    unsigned char _pad346[0x2];
    int m_linkPhase;                             // +0x348
    float m_linkDir;                             // +0x34C
    unsigned char m_linkFrame;                   // +0x350
    bool m_active;                               // +0x351
    unsigned char _pad352[0x2];
    int m_link18;                                // +0x354
};

