// Dll/Shot/Learningfcdeath/ShotLearningfcdeath.h - dllshotlearningfcdeath's
// shot class (vtable ): the learned FC Death skill
// (ShotInfo name "FC Death Sickle" in Japanese). Standing (getI284() == 0),
// Death throws a stream of sickles (ShotElem274 records, one every 0.1 s at
// a random angle and speed, as many as the kind byte allows) and leaves;
// as a flying sickle (getI284() != 0) it blinks for 1 s, then flies along
// its start velocity at 96, spinning, until ended or after 4 s.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotLearningfcdeath : public ShotBase {
public:
    ShotLearningfcdeath();                       // (DllCreate inlines it)
    virtual ~ShotLearningfcdeath();

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

    // non-virtual helpers
    void updateThrower(float dt);
    void spin(float dt);
    // unreferenced copy of vanish
    void end();
    void tickLife(float dt);
    // unreferenced
    bool takeEnd();
    void updateSickle(float dt);

public:
    int m_state;                                 // +0x318
    float m_time;                                // +0x31C
    float m_life;                                // +0x320 a sickle ends after 4 s
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endReq;                               // +0x328
    bool m_ended;                                // +0x329
    bool m_sickle;                               // +0x32A
    bool m_toggle;                               // +0x32B blink
    unsigned char m_thrown;                      // +0x32C sickles thrown so far
    unsigned char _pad32D[0x3];
    float m_spinTime;                            // +0x330
    int m_spin;                                  // +0x334 quarter turns 0-3
};

