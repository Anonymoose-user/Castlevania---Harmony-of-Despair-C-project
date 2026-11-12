// Dll/Shot/Soulfumaryukibi/ShotSoulfumaryukibi.h - dllshotsoulfumaryukibi's
// shot class (vtable ): the Ryuzukibi soul ("Soul
// Fuma Ryuzukibi" in Japanese, the ShotInfo name). One module, seven shot
// kinds packed into m_i284 (bits 0-3 kind, 4-7 sub-kind, bit 8 gravity sign,
// bit 9 strong):
//   0 summoner: spawns its fireball records (addElem274, 1 or 2 per soul
//     level) and dies; 1 bouncing fireball (on a hit it splits into two or
//     three records); 2 / 3 falling / still fire; 4 homing fireball that
//     steers toward the owner's anchor; 5 burst that ends on animation
//     frame 15; 6 straight fireball.
// Names are inferred.
#pragma once

#include "Dll/Shot/ShotBase.h"

class ShotSoulfumaryukibi : public ShotBase {
public:
    ShotSoulfumaryukibi();                       // (calls )
    virtual ~ShotSoulfumaryukibi();

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

    // kind updates: 6 straight, 5 burst, 4 homing, 3 still, 2 fall, 1 bounce,
    // 0 summon; end() and checkFade() are unreferenced
    void cycleAnim();
    void end();
    void tickLife(float dt);
    bool checkFade();
    void updateStraight(float dt);
    void updateBurst();
    void updateHoming(float dt);
    void updateStill(float dt);
    void updateFall(float dt);
    void updateBounce(float dt);
    void updateSummon(float dt);

    // the SDK's Dinkumware atan2f (Soulfumaryukibi/SoulfumaryukibiMath.cpp)
    static float atan2f(float y, float x);
    static float atanReduced(float x, unsigned int idx);
    static short fdtest(const float* p);

public:
    int m_state;                                 // +0x318
    float m_time;                                // +0x31C
    float m_life;                                // +0x320
    float m_dir;                                 // +0x324 -1 left, 1 right
    bool m_fadeReq;                              // +0x328 end() asks for state 9
    bool m_ended;                                // +0x329
    unsigned short m_anim;                       // +0x32A animation cycle index, 0..6
    bool m_unowned;                              // +0x32C summoner without an owner (getB314 false)
    unsigned char _pad32D[3];
    int m_spawned;                               // +0x330 records a summoner has spawned
    int m_kind;                                  // +0x334 m_i284 bits 0-3
    int m_sub;                                   // +0x338 m_i284 bits 4-7
    float m_gravity;                             // +0x33C -1 / 1 from m_i284 bit 8
    bool m_strong;                               // +0x340 m_i284 bit 9
    unsigned char _pad341[3];
    float m_angle;                               // +0x344 homing heading
    float m_speed;                               // +0x348 homing speed
    float m_turnRate;                            // +0x34C homing turn rate (rad/s)
    float m_aimY;                                // +0x350 homing target height offset
};

