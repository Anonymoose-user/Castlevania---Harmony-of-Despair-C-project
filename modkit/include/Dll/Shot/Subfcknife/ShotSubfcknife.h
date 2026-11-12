// Dll/Shot/Subfcknife/ShotSubfcknife.h - dllshotsubfcknife's shot class
// (vtable ): the FC knife sub-weapon ("サブ　ＦＣナイフ",
// ShotInfo name). A knife thrown straight ahead (object A 0) with a spark
// (object A 1); on a hit or after 5 s the knife disappears, the spark plays
// out and the shot dies. Kind 4+ with the m_b314 flag also queues one or two
// trail records. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSubfcknife : public ShotBase {
public:
    ShotSubfcknife();                            // (DllCreate inlines it)
    virtual ~ShotSubfcknife();

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

    // non-virtual, unreferenced copies of parts of update() / vanish()
    void tickLife(float dt);
    bool checkEnd();
    void end();


public:
    int m_state;                                 // +0x318 0 flying, 1 ending, 2 spark, 3 dead
    float m_time;                                // +0x31C (only cleared)
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 facing left, 1 right
    bool m_endReq;                               // +0x328 end() asks update() to end
    bool m_ended;                                // +0x329
};

