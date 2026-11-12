// Dll/Shot/Soulfcaltair/ShotSoulfcaltair.h - dllshotsoulfcaltair's shot class
// (vtable ): the Altair soul ("L. Altair" in katakana,
// the ShotInfo name). A hawk (object 0) flies off along the throw direction
// (or the facing) with a trail object (1); it lives 0.6 s + 0.3 s per soul
// level, and at soul level 4+ a hit turns it around instead of ending it.
// Ending stops it and plays object 1 out. Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfcaltair : public ShotBase {
public:
    ShotSoulfcaltair();                          // (DllCreate inlines it)
    virtual ~ShotSoulfcaltair();

    virtual void release();
    virtual int getResourceCount();
    virtual const char* getResource(unsigned int index, int* kind);
    virtual void start();
    virtual void update(float dt);
    virtual void onHit(unsigned int flags);
    virtual void vanish();
    virtual void getInfo(ShotInfo* info);
    virtual const char* getPath(int index);

    void unused06AC();                         // an empty member no vtable uses
    // non-virtual, unreferenced copies of parts of update()
    void end();
    void tickLife(float dt);
    bool checkFade();

public:
    int m_state;                                 // +0x318 0 flying, 1 ending, 2 trail playing, 3 dead
    float m_time;                                // +0x31C cleared, otherwise unused
    float m_life;                                // +0x320 counts down
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for state 1
    bool m_ended;                                // +0x329
    bool m_turnReq;                              // +0x32A onHit() turned it around
    bool m_turnSeen;                             // +0x32B a turn waits one more frame
};

