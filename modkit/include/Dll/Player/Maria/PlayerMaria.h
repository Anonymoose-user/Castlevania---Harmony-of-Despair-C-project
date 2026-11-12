// Dll/Player/Maria/PlayerMaria.h - Maria Renard, the dllmaria module (vtable
// no members beyond PlayerBase). Names are inferred;
// the voice names come from the module's own table (VX_MAR_*).
//
// Maria registers her own class for most state ids; each derives from the
// library's default for that id (PlayerStates.h). Unlike Soma's, her state
// classes keep no pointer back to the player. Holding button 8 (a skill,
// PlayerState::trySkill) enters the hold states 0x26 (ground) / 0x27 (air).
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerMaria : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerMaria();
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
    virtual const char* getOpdPath(bool* outFlag, int variant);// +0x268
    virtual void getAnimTable(PlayerAnimEntry* out);   // +0x26C
    virtual int  getMenuId(int i);              // +0x270
    virtual void getHitBox(float* l, float* t, float* r, float* b, bool alt);  // +0x298
    virtual bool vfunc424(int action);          // +0x424
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual bool canAttack(int slot, int action, int weapon);   // +0x470
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474
    virtual int  vfunc47C();                    // +0x47C

    void deleteState(int id);
    template <class T> void createState(int id);    // one instance per state class,
};

// --- Maria's states ---------------------------------------------------------

// Id 0x17, standing attack. Action 4 is a long-lasting
// move that ends the state after 4.727 s.
class MariaState17 : public PlayerState17 {
public:
    explicit MariaState17(PlayerBase* p);
    virtual ~MariaState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x18, crouching attack.
class MariaState18 : public PlayerState18 {
public:
    explicit MariaState18(PlayerBase* p);
    virtual ~MariaState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x19, air attack.
class MariaState19 : public PlayerState19 {
public:
    explicit MariaState19(PlayerBase* p);
    virtual ~MariaState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x06, back dash.
class MariaState06 : public PlayerState06 {
public:
    explicit MariaState06(PlayerBase* p);
    virtual ~MariaState06();
    virtual void update();
};

// Id 0x0A, slide. Animation 0x18/0x1B by stick lean.
class MariaState0A : public PlayerState0A {
public:
    explicit MariaState0A(PlayerBase* p);
    virtual ~MariaState0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    bool m_animStarted;                         // +0x1D
};

// Ids 0x0F/0x10, falling (vtables ).
class MariaState0F : public PlayerState0F {
public:
    explicit MariaState0F(PlayerBase* p);
    virtual ~MariaState0F();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class MariaState10 : public PlayerState10 {
public:
    explicit MariaState10(PlayerBase* p);
    virtual ~MariaState10();
    virtual void update();
};

// Id 0x26, holding button 8 on the ground. Animation 0xEA.
class MariaState26 : public PlayerState {
public:
    explicit MariaState26(PlayerBase* p);
    virtual ~MariaState26();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    void endHold();
};

// Id 0x27, holding button 8 in the air. Animation 0xEB.
class MariaState27 : public PlayerState {
public:
    explicit MariaState27(PlayerBase* p);
    virtual ~MariaState27();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    void endHold();
};

// Id 0x25, the input-command special. Animation 0xD9,
// m_b2B8 set for the first 0.5 s.
class MariaState25 : public PlayerState {
public:
    explicit MariaState25(PlayerBase* p);
    virtual ~MariaState25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void finish();
};

// Ids 0x0B-0x0E, jumps (vtables ): the air skill
// replaces the jump's own update for that frame.
class MariaState0B : public PlayerState0B {
public:
    explicit MariaState0B(PlayerBase* p);
    virtual ~MariaState0B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    void* m_unused34;                           // +0x34 never written (0x38-byte object)
};

class MariaState0D : public PlayerState0D {
public:
    explicit MariaState0D(PlayerBase* p);
    virtual ~MariaState0D();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class MariaState0C : public PlayerState0C {
public:
    explicit MariaState0C(PlayerBase* p);
    virtual ~MariaState0C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class MariaState0E : public PlayerState0E {
public:
    explicit MariaState0E(PlayerBase* p);
    virtual ~MariaState0E();
    virtual void update();
};

// Ids 0x11-0x14, landings (vtables ).
class MariaState11 : public PlayerState11 {
public:
    explicit MariaState11(PlayerBase* p);
    virtual ~MariaState11();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class MariaState12 : public PlayerState12 {
public:
    explicit MariaState12(PlayerBase* p);
    virtual ~MariaState12();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class MariaState13 : public PlayerState13 {
public:
    explicit MariaState13(PlayerBase* p);
    virtual ~MariaState13();
    virtual void update();
};

class MariaState14 : public PlayerState14 {
public:
    explicit MariaState14(PlayerBase* p);
    virtual ~MariaState14();
    virtual void update();
};

// Id 0x21, looking up: the voice comes after 3.42 s.
class MariaState21 : public PlayerState21 {
public:
    explicit MariaState21(PlayerBase* p);
    virtual ~MariaState21();
    virtual void enter();
    virtual void update();
};

// Ids 0x07-0x09, crouching (vtables ).
class MariaState07 : public PlayerState07 {
public:
    explicit MariaState07(PlayerBase* p);
    virtual ~MariaState07();
    virtual void update();
};

class MariaState08 : public PlayerState08 {
public:
    explicit MariaState08(PlayerBase* p);
    virtual ~MariaState08();
    virtual void update();
};

class MariaState09 : public PlayerState09 {
public:
    explicit MariaState09(PlayerBase* p);
    virtual ~MariaState09();
    virtual void update();
};

// Id 0x01, standing.
class MariaState01 : public PlayerState01 {
public:
    explicit MariaState01(PlayerBase* p);
    virtual ~MariaState01();
    virtual void update();
};

// Ids 0x05, 0x02-0x04, 0x15: turning and walking (vtables ).
class MariaState05 : public PlayerState05 {
public:
    explicit MariaState05(PlayerBase* p);
    virtual ~MariaState05();
    virtual void update();
};

class MariaState02 : public PlayerState02 {
public:
    explicit MariaState02(PlayerBase* p);
    virtual ~MariaState02();
    virtual void update();
};

class MariaState03 : public PlayerState03 {
public:
    explicit MariaState03(PlayerBase* p);
    virtual ~MariaState03();
    virtual void update();
};

class MariaState04 : public PlayerState04 {
public:
    explicit MariaState04(PlayerBase* p);
    virtual ~MariaState04();
    virtual void update();
};

class MariaState15 : public PlayerState15 {
public:
    explicit MariaState15(PlayerBase* p);
    virtual ~MariaState15();
    virtual void update();
};
