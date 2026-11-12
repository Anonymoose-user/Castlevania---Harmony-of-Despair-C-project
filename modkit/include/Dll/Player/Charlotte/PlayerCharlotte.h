// Dll/Player/Charlotte/PlayerCharlotte.h - Charlotte Aulin, the dllcharlotte
// module (vtable, no members beyond PlayerBase).
// Names are inferred; the voice names come from the module's own table
// (VX_CHA_*).
//
// Charlotte registers her own class for most state ids; each derives from the
// library's default for that id (PlayerStates.h). Unlike Soma's states they
// keep no pointer back to the player. Her skills are states 0x25 (standing),
// 0x26 (crouching) and 0x27 (air), entered through PlayerState::trySkill and
// held with button 8 while skill points last.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerCharlotte : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerCharlotte();
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
    virtual int  vfunc3B0(int action);          // +0x3B0
    virtual int  vfunc3B4();                    // +0x3B4
    virtual const char* getOpdPath(bool* outFlag, int variant);  // +0x268
    virtual void getModelScale(float* out);     // +0x264
    virtual void getAnimTable(PlayerAnimEntry* out);   // +0x26C
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474
    virtual int  getMenuId(int i);              // +0x270
    virtual void getHitBox(float* l, float* t, float* r, float* b, bool alt);  // +0x298
    virtual bool canAttack(int slot, int action, int weapon);   // +0x470
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual int  getComboAnim(int kind, int action);   // +0x464
    virtual int  vfunc47C();                    // +0x47C
    virtual int  vfunc46C();                    // +0x46C
    virtual bool vfunc430(unsigned int mask);   // +0x430

    void deleteState(int id);
    template <class T> void createState(int id);    // one instance per state class,
};

// --- Charlotte's states -----------------------------------------------------

// Id 0x17, standing attack: animation 0x49/0x4D on the
// ground; in the air (postures 2-5) a spell (event kind 5, animation 0xEF).
class CharlotteState17 : public PlayerState17 {
public:
    explicit CharlotteState17(PlayerBase* p);
    virtual ~CharlotteState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x18, crouching attack. Animation 0x4A/0x4E; in the
// air it hands over to the standing attack.
class CharlotteState18 : public PlayerState18 {
public:
    explicit CharlotteState18(PlayerBase* p);
    virtual ~CharlotteState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x19, air attack. Animation 0x4B; postures 2-5 cast
// (animation 0xF0) unless the action is 1, 3 or 0x11.
class CharlotteState19 : public PlayerState19 {
public:
    explicit CharlotteState19(PlayerBase* p);
    virtual ~CharlotteState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x06, back dash: the standing skill can start from it.
class CharlotteState06 : public PlayerState06 {
public:
    explicit CharlotteState06(PlayerBase* p);
    virtual ~CharlotteState06();
    virtual void update();
};

// Id 0x0A, slide. Defined in the module but never
// registered: init creates the library's PlayerState0A for id 0x0A.
class CharlotteState0A : public PlayerState0A {
public:
    explicit CharlotteState0A(PlayerBase* p);
    virtual ~CharlotteState0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
};

// Ids 0x0F/0x10, falling (vtables ): the air skill
// (0x27) stays available.
class CharlotteState0F : public PlayerState0F {
public:
    explicit CharlotteState0F(PlayerBase* p);
    virtual ~CharlotteState0F();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class CharlotteState10 : public PlayerState10 {
public:
    explicit CharlotteState10(PlayerBase* p);
    virtual ~CharlotteState10();
    virtual void update();
};

// Ids 0x0B-0x0E, jumps (vtables ): the air skill
// replaces the jump's own update for that frame.
class CharlotteState0B : public PlayerState0B {
public:
    explicit CharlotteState0B(PlayerBase* p);
    virtual ~CharlotteState0B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class CharlotteState0D : public PlayerState0D {
public:
    explicit CharlotteState0D(PlayerBase* p);
    virtual ~CharlotteState0D();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class CharlotteState0C : public PlayerState0C {
public:
    explicit CharlotteState0C(PlayerBase* p);
    virtual ~CharlotteState0C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class CharlotteState0E : public PlayerState0E {
public:
    explicit CharlotteState0E(PlayerBase* p);
    virtual ~CharlotteState0E();
    virtual void update();
};

// Ids 0x11-0x14, landings (vtables ).
class CharlotteState11 : public PlayerState11 {
public:
    explicit CharlotteState11(PlayerBase* p);
    virtual ~CharlotteState11();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class CharlotteState12 : public PlayerState12 {
public:
    explicit CharlotteState12(PlayerBase* p);
    virtual ~CharlotteState12();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class CharlotteState13 : public PlayerState13 {
public:
    explicit CharlotteState13(PlayerBase* p);
    virtual ~CharlotteState13();
    virtual void update();
};

class CharlotteState14 : public PlayerState14 {
public:
    explicit CharlotteState14(PlayerBase* p);
    virtual ~CharlotteState14();
    virtual void update();
};

// Id 0x25, standing skill: animation 0x102 while
// button 8 is held, half of m_i2FC skill points per second.
class CharlotteState25 : public PlayerState {
public:
    explicit CharlotteState25(PlayerBase* p);
    virtual ~CharlotteState25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    bool payCost(int next);
};

// Id 0x26, crouching skill. Animation 0x103.
class CharlotteState26 : public PlayerState {
public:
    explicit CharlotteState26(PlayerBase* p);
    virtual ~CharlotteState26();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
};

// Id 0x27, air skill: animation 0x104, hovering (no
// upward speed while m_b038) and steering; landing turns it into the
// standing skill.
class CharlotteState27 : public PlayerState {
public:
    explicit CharlotteState27(PlayerBase* p);
    virtual ~CharlotteState27();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    bool m_started;                             // +0x14 set after the first update
};

// Id 0x21, looking up: the voice comes after 5.65 s.
class CharlotteState21 : public PlayerState21 {
public:
    explicit CharlotteState21(PlayerBase* p);
    virtual ~CharlotteState21();
    virtual void enter();
    virtual void update();
};

// Ids 0x07-0x09, crouching (vtables ): 0x07/0x08 offer
// the crouching skill, 0x09 the standing one.
class CharlotteState07 : public PlayerState07 {
public:
    explicit CharlotteState07(PlayerBase* p);
    virtual ~CharlotteState07();
    virtual void update();
};

class CharlotteState08 : public PlayerState08 {
public:
    explicit CharlotteState08(PlayerBase* p);
    virtual ~CharlotteState08();
    virtual void update();
};

class CharlotteState09 : public PlayerState09 {
public:
    explicit CharlotteState09(PlayerBase* p);
    virtual ~CharlotteState09();
    virtual void update();
};

// Id 0x01, standing.
class CharlotteState01 : public PlayerState01 {
public:
    explicit CharlotteState01(PlayerBase* p);
    virtual ~CharlotteState01();
    virtual void update();
};

// Ids 0x05, 0x02-0x04, 0x15: turning and walking (vtables
class CharlotteState05 : public PlayerState05 {
public:
    explicit CharlotteState05(PlayerBase* p);
    virtual ~CharlotteState05();
    virtual void update();
};

class CharlotteState02 : public PlayerState02 {
public:
    explicit CharlotteState02(PlayerBase* p);
    virtual ~CharlotteState02();
    virtual void update();
};

class CharlotteState03 : public PlayerState03 {
public:
    explicit CharlotteState03(PlayerBase* p);
    virtual ~CharlotteState03();
    virtual void update();
};

class CharlotteState04 : public PlayerState04 {
public:
    explicit CharlotteState04(PlayerBase* p);
    virtual ~CharlotteState04();
    virtual void update();
};

class CharlotteState15 : public PlayerState15 {
public:
    explicit CharlotteState15(PlayerBase* p);
    virtual ~CharlotteState15();
    virtual void update();
};
