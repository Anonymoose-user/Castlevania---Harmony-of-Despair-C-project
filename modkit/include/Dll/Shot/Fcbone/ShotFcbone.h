// Dll/Shot/Fcbone/ShotFcbone.h - dllshotfcbone's shot class (vtable
// ): "FC summon skeleton" (ShotInfo name, katakana).
// Two modes, chosen by m_i284 at start():
//  - summoner (m_i284 == 0): a skeleton beside the owner that throws bones
//    (ShotElem274 records, one every 0.1 s; how many depends on the kind byte
//    m_u204), then leaves after 1 s;
//  - bone (m_i284 != 0): a thrown bone that falls under gravity, spinning
//    through six frames, until it ends (10 s, vanish, hit).
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotFcbone : public ShotBase {
public:
    ShotFcbone();                                // (DllCreate inlines it)
    virtual ~ShotFcbone();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void vfunc01C();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void vfunc050();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    void end();
    void tickLife(float dt);
    void updateSummoner(float dt);
    void spin(float dt);
    bool beginUpdate();
    void updateBone(float dt);

public:
    int m_state;                                 // +0x318 summoner 1 throw, 2 leave, 5 dead; bone 0 fly, 3 end, 4 fade, 5 dead
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endRequest;                           // +0x328
    bool m_ended;                                // +0x329
    bool m_isBone;                               // +0x32A
    bool m_blink;                                // +0x32B
    unsigned char m_thrown;                      // +0x32C bones thrown so far
    unsigned char _pad32D[3];
    float m_spinTime;                            // +0x330
    int m_frame;                                 // +0x334 spin frame 0..5
    int m_nextI30;                               // +0x338 object flip for the next frame
    bool m_flipPending;                          // +0x33C
};

