// Dll/Player/Simon/PlayerSimon.h - Simon Belmont, the dllsimon module (vtable
// ). Names are inferred. Simon uses the library state
// for every id except the three attacks and the command special 0x25.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerSimon : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerSimon();
    virtual void release();                     // +0x008
    virtual void init();                        // +0x00C
    virtual void update();                      // +0x014
    virtual void finalize();                    // +0x01C
    virtual bool isSpecialWeapon(int weapon);   // +0x184
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
    virtual int  vfunc41C(int a, int action);   // +0x41C
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474

    void deleteState(unsigned int id);
    template <class T> void createState(int id);    // one instance per state class,

    unsigned int m_u348;                        // +0x348 never used by the module
};

// --- Simon's states ---------------------------------------------------------

// Id 0x17, standing attack.
class SimonState17 : public PlayerState17 {
public:
    explicit SimonState17(PlayerBase* p);
    virtual ~SimonState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x18, crouching attack.
class SimonState18 : public PlayerState18 {
public:
    explicit SimonState18(PlayerBase* p);
    virtual ~SimonState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x19, air attack.
class SimonState19 : public PlayerState19 {
public:
    explicit SimonState19(PlayerBase* p);
    virtual ~SimonState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x25, command special (vtable ): command 0x19
// plays animation 0xBB and fires one hit event 0.18 s in.
class SimonState25 : public PlayerState {
public:
    explicit SimonState25(PlayerBase* p);
    virtual ~SimonState25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_phase;                                // +0x14
    bool m_hitSent;                             // +0x18
};
