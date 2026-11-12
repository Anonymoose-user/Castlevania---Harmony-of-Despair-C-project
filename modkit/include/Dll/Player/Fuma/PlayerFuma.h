// Dll/Player/Fuma/PlayerFuma.h - Getsu Fuma, the dllfuma module (vtable
// PlayerBase plus a hold timer and a flag). Names
// are inferred. Besides the library states he registers his own attacks
// (0x17-0x19), which fire a second hit event when action 0x90 is held for
// 0.1 s on the ground.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerFuma : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerFuma();
    virtual void release();                     // +0x008
    virtual void init();                        // +0x00C
    virtual void update();                      // +0x014
    virtual void finalize();                    // +0x01C
    virtual int  vfunc244();                    // +0x244
    virtual int  vfunc248();                    // +0x248
    virtual int  vfunc24C();                    // +0x24C
    virtual bool vfunc250();                    // +0x250
    virtual bool vfunc254();                    // +0x254
    virtual void getModelScale(float* out);     // +0x264
    virtual const char* getOpdPath(bool* outFlag, int variant);  // +0x268
    virtual void getAnimTable(PlayerAnimEntry* out);   // +0x26C
    virtual int  getMenuId(int i);              // +0x270
    virtual void getHitBox(float* l, float* t, float* r, float* b, bool alt);  // +0x298
    virtual int  vfunc3B4();                    // +0x3B4
    virtual void getAttackInfo(int kind, float charge, PlayerAttackInfo* out);  // +0x3EC
    virtual int  vfunc41C(int a, int action);   // +0x41C (returns 0, 1 or 2)
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474

    bool alwaysTrue();                          // (unreferenced)
    void setHoldDone(bool v);
    void clearHoldTime();
    void deleteState(unsigned int id);
    float addHoldTime(float dt);                // returns the old value
    bool getHoldDone();
    template <class T> void createState(int id);    // one instance per state class,

    float m_holdTime;                           // +0x348
    bool m_holdDone;                            // +0x34C
};

// --- Fuma's states ------------------------------------------------------------

// Id 0x17, standing attack: animation 0x49 on the
// ground, 0xEF (0xDE for action 0x11) in the air.
class FumaState17 : public PlayerState17 {
public:
    explicit FumaState17(PlayerFuma* fuma);
    virtual ~FumaState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerFuma* m_fuma;                         // +0x2C
};

// Id 0x18, crouching attack: animation 0x4A; in the air
// it hands over to the standing attack.
class FumaState18 : public PlayerState18 {
public:
    explicit FumaState18(PlayerFuma* fuma);
    virtual ~FumaState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerFuma* m_fuma;                         // +0x2C
};

// Id 0x19, air attack: animation 0x4B on the ground,
// 0xF0 (0xDF for action 0x11) in the air.
class FumaState19 : public PlayerState19 {
public:
    explicit FumaState19(PlayerFuma* fuma);
    virtual ~FumaState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerFuma* m_fuma;                         // +0x2C
};
