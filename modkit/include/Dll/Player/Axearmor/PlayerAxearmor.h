// Dll/Player/Axearmor/PlayerAxearmor.h - Axe Armor, the dllaxearmor module
// (vtable, no members beyond PlayerBase). Names are
// inferred. He has no voices and no input commands; besides the library
// states he registers his own attacks (0x17-0x19) and one idle state class
// for the soul ids 0x25-0x34.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerAxearmor : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerAxearmor();
    virtual void release();                     // +0x008
    virtual void init();                        // +0x00C
    virtual void update();                      // +0x014
    virtual void finalize();                    // +0x01C
    virtual int  vfunc244();                    // +0x244
    virtual int  vfunc248();                    // +0x248
    virtual int  vfunc24C();                    // +0x24C
    virtual bool vfunc250();                    // +0x250
    virtual bool vfunc254();                    // +0x254
    virtual bool vfunc260();                    // +0x260
    virtual void getModelScale(float* out);     // +0x264
    virtual const char* getOpdPath(bool* outFlag, int variant);  // +0x268
    virtual void getAnimTable(PlayerAnimEntry* out);   // +0x26C
    virtual int  getMenuId(int i);              // +0x270
    virtual void getHitBox(float* l, float* t, float* r, float* b, bool alt);  // +0x298
    virtual bool vfunc424(int action);          // +0x424
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474

    void deleteState(unsigned int id);
    template <class T> void createState(int id);    // one instance per state class,
};

// --- Axe Armor's states ------------------------------------------------------

// Id 0x17, standing attack: animation 0x49 on the
// ground, 0xEF in the air.
class AxearmorState17 : public PlayerState17 {
public:
    explicit AxearmorState17(PlayerBase* p);
    virtual ~AxearmorState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x18, crouching attack; in the air it hands over to
// the standing attack.
class AxearmorState18 : public PlayerState18 {
public:
    explicit AxearmorState18(PlayerBase* p);
    virtual ~AxearmorState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x19, air attack: animation 0x49 / 0xF0.
class AxearmorState19 : public PlayerState19 {
public:
    explicit AxearmorState19(PlayerBase* p);
    virtual ~AxearmorState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Ids 0x25-0x34: stands still in animation 2.
class AxearmorState25 : public PlayerState {
public:
    explicit AxearmorState25(PlayerBase* p);
    virtual ~AxearmorState25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    void finish();                              // (unreferenced)
};
