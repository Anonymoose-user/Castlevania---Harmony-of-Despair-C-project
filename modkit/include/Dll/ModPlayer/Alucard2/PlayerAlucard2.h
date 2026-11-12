// Dll/ModPlayer/Alucard2/PlayerAlucard2.h - Alucard2, the dllalucard2 module (vtable
// no members beyond PlayerBase). Names are inferred;
// the voice names come from the module's own table (VX_ALC_*).
//
// Alucard2 registers his own class for most state ids; each derives from the
// library's default for that id (PlayerStates.h). Ids 0x25/0x26 turn him into
// a bat and back (animation 0x102); id 0x27 is his input-command special.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerAlucard2 : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerAlucard2();
    virtual void release();                     // +0x008
    virtual void init();                        // +0x00C
    virtual void update();                      // +0x014
    virtual void finalize();                    // +0x01C
    virtual bool isSpecialWeapon(int weapon);   // +0x184
    virtual bool vfunc208();                    // +0x208
    virtual int  vfunc244();                    // +0x244
    virtual int  vfunc248();                    // +0x248
    virtual int  vfunc24C();                    // +0x24C
    virtual bool vfunc250();                    // +0x250
    virtual bool vfunc254();                    // +0x254
    virtual bool vfunc258();                    // +0x258
    virtual void getModelScale(float* out);     // +0x264
    virtual const char* getOpdPath(bool* outFlag, int variant);   // +0x268
    virtual void getAnimTable(PlayerAnimEntry* out);   // +0x26C
    virtual int  getMenuId(int i);              // +0x270
    virtual void getHitBox(float* l, float* t, float* r, float* b, bool alt);  // +0x298
    virtual bool isNotAction40to45(int action); // +0x3A8
    virtual bool vfunc3AC();                    // +0x3AC
    virtual void getFacingDir(float* dir, int* out2);   // +0x3E8
    virtual void getAttackInfo(int kind, float charge, PlayerAttackInfo* out);   // +0x3EC
    virtual int  vfunc41C(int a, int action);   // +0x41C
    virtual int  vfunc420();                    // +0x420
    virtual bool vfunc424(int action);          // +0x424
    virtual bool vfunc430(unsigned int mask);   // +0x430
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual int  getComboAnim(int kind, int action);   // +0x464
    virtual bool canAttack(int slot, int action, int weapon);   // +0x470
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474
    virtual int  vfunc480();                    // +0x480

    void deleteState(unsigned int id);
    template <class T> void createState(int id);    // one instance per state class,
    // the posture value behind slot +0x41C (0..6)
    int  postureForAction(int a, int action);   // body
    int  airPosture();
    int  airPostureDown();
    int  airPostureLow();
    int  postureFromI134();
    void chainAttack17(int posture, bool checkInput, bool leaveNow);
};

// --- Alucard2's states --------------------------------------------------------

// Id 0x17, standing attack.
class Alucard2State17 : public PlayerState17 {
public:
    explicit Alucard2State17(PlayerBase* p);
    virtual ~Alucard2State17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void chainAttack(int posture, bool checkInput, bool leaveNow);
    static int weaponGroup(int weapon, int action);   // (first argument unused)
    static bool isNotAction0E(int action);      // (first argument unused)

    bool m_hitSent;                             // +0x2C
    int m_charged;                              // +0x30
};

// Id 0x18, crouching attack.
class Alucard2State18 : public PlayerState18 {
public:
    explicit Alucard2State18(PlayerAlucard2* alucard2);
    virtual ~Alucard2State18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerAlucard2* m_alucard2;                   // +0x2C
};

// Id 0x19, air attack.
class Alucard2State19 : public PlayerState19 {
public:
    explicit Alucard2State19(PlayerAlucard2* alucard2);
    virtual ~Alucard2State19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void setAirAnim(int anim, int fallAnim, int riseAnim);

    PlayerAlucard2* m_alucard2;                   // +0x2C
    float m_time;                               // +0x30
};

// Ids 0x1A-0x1C, hit reactions (vtables ).
class Alucard2State1A : public PlayerState1A {
public:
    explicit Alucard2State1A(PlayerBase* p);
    virtual ~Alucard2State1A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class Alucard2State1B : public PlayerState1B {
public:
    explicit Alucard2State1B(PlayerBase* p);
    virtual ~Alucard2State1B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class Alucard2State1C : public PlayerState1C {
public:
    explicit Alucard2State1C(PlayerBase* p);
    virtual ~Alucard2State1C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x06, back dash.
class Alucard2State06 : public PlayerState06 {
public:
    explicit Alucard2State06(PlayerBase* p);
    virtual ~Alucard2State06();
    virtual void update();
};

// Id 0x0A, slide. Animation 0x17, then 0x18.
class Alucard2State0A : public PlayerState0A {
public:
    explicit Alucard2State0A(PlayerBase* p);
    virtual ~Alucard2State0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_animSwitched;                         // +0x20
};

// Ids 0x0F/0x10, falling (vtables ).
class Alucard2State0F : public PlayerState0F {
public:
    explicit Alucard2State0F(PlayerBase* p);
    virtual ~Alucard2State0F();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class Alucard2State10 : public PlayerState10 {
public:
    explicit Alucard2State10(PlayerBase* p);
    virtual ~Alucard2State10();
    virtual void update();
};

// Id 0x25, turning into a bat: 0.3 s of transformation,
// then flying with the stick (or the d-pad) for as long as m_time stays under
// 0.1 s... until button 8 or the time ends it (state 0x26).
class Alucard2State25 : public PlayerState {
public:
    explicit Alucard2State25(PlayerBase* p);
    virtual ~Alucard2State25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    int m_phase;                                // +0x14
    float m_time;                               // +0x18
    float m_blend;                              // +0x1C passed to event 3 by address
    // Alucard 2's bat (not in the original): continuous flight with a dash and an attack
    float m_dashTime;                           // time left in a dash
    float m_attackTime;                         // time left in the attack animation
    void batFlight(float scale);
};

// Id 0x26, turning back from a bat.
class Alucard2State26 : public PlayerState {
public:
    explicit Alucard2State26(PlayerBase* p);
    virtual ~Alucard2State26();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    int m_phase;                                // +0x14
    float m_time;                               // +0x18
    float m_blend;                              // +0x1C passed to event 3 by address
};

// Ids 0x0B-0x0E, jumps (vtables ): the bat command
// replaces the jump's own update for that frame.
class Alucard2State0B : public PlayerState0B {
public:
    explicit Alucard2State0B(PlayerBase* p);
    virtual ~Alucard2State0B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_anim;                                 // +0x34 0, 1 (0x1E), 2 (0x1F)
};

class Alucard2State0D : public PlayerState0D {
public:
    explicit Alucard2State0D(PlayerBase* p);
    virtual ~Alucard2State0D();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class Alucard2State0C : public PlayerState0C {
public:
    explicit Alucard2State0C(PlayerBase* p);
    virtual ~Alucard2State0C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class Alucard2State0E : public PlayerState0E {
public:
    explicit Alucard2State0E(PlayerBase* p);
    virtual ~Alucard2State0E();
    virtual void update();
};

// Id 0x16, dive kick.
class Alucard2State16 : public PlayerState16 {
public:
    explicit Alucard2State16(PlayerBase* p);
    virtual ~Alucard2State16();
    virtual void update();
};

// Ids 0x11-0x14, landings (vtables ).
class Alucard2State11 : public PlayerState11 {
public:
    explicit Alucard2State11(PlayerBase* p);
    virtual ~Alucard2State11();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class Alucard2State12 : public PlayerState12 {
public:
    explicit Alucard2State12(PlayerBase* p);
    virtual ~Alucard2State12();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class Alucard2State13 : public PlayerState13 {
public:
    explicit Alucard2State13(PlayerBase* p);
    virtual ~Alucard2State13();
    virtual void update();
};

class Alucard2State14 : public PlayerState14 {
public:
    explicit Alucard2State14(PlayerBase* p);
    virtual ~Alucard2State14();
    virtual void update();
};

// Id 0x21, looking up.
class Alucard2State21 : public PlayerState21 {
public:
    explicit Alucard2State21(PlayerBase* p);
    virtual ~Alucard2State21();
    virtual void enter();
};

// Ids 0x07-0x09, crouching (vtables ): m_i2F0 other
// than -1 shows animation 0xD8 / 6.
class Alucard2State07 : public PlayerState07 {
public:
    explicit Alucard2State07(PlayerBase* p);
    virtual ~Alucard2State07();
    virtual void update();
};

class Alucard2State08 : public PlayerState08 {
public:
    explicit Alucard2State08(PlayerBase* p);
    virtual ~Alucard2State08();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_i2F0;                                 // +0x14 last m_i2F0 shown, -1 none
};

class Alucard2State09 : public PlayerState09 {
public:
    explicit Alucard2State09(PlayerBase* p);
    virtual ~Alucard2State09();
    virtual void update();
};

// Id 0x01, standing with an idle cycle: after 10 s
// animation 4/5, then back.
class Alucard2State01 : public PlayerState01 {
public:
    explicit Alucard2State01(PlayerBase* p);
    virtual ~Alucard2State01();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_idlePhase;                            // +0x14
    float m_idleTime;                           // +0x18
    int m_i2F0;                                 // +0x1C last m_i2F0 shown, -1 none
};

// Id 0x1E, petrified: one of three animations.
class Alucard2State1E : public PlayerState1E {
public:
    explicit Alucard2State1E(PlayerBase* p);
    virtual ~Alucard2State1E();
    virtual void enter();
};

// Ids 0x05, 0x02-0x04, 0x15: turning and walking (vtables ).
class Alucard2State05 : public PlayerState05 {
public:
    explicit Alucard2State05(PlayerAlucard2* alucard2);
    virtual ~Alucard2State05();
    virtual void update();

    PlayerAlucard2* m_alucard2;                   // +0x14
};

class Alucard2State02 : public PlayerState02 {
public:
    explicit Alucard2State02(PlayerAlucard2* alucard2);
    virtual ~Alucard2State02();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_turned;                               // +0x14
    PlayerAlucard2* m_alucard2;                   // +0x18
};

class Alucard2State03 : public PlayerState03 {
public:
    explicit Alucard2State03(PlayerAlucard2* alucard2);
    virtual ~Alucard2State03();
    virtual void update();

    PlayerAlucard2* m_alucard2;                   // +0x14
};

class Alucard2State04 : public PlayerState04 {
public:
    explicit Alucard2State04(PlayerBase* p);
    virtual ~Alucard2State04();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class Alucard2State15 : public PlayerState15 {
public:
    explicit Alucard2State15(PlayerAlucard2* alucard2);
    virtual ~Alucard2State15();
    virtual void update();

    PlayerAlucard2* m_alucard2;                   // +0x14
};

// Id 0x27, the input-command special. What it does
// depends on the command's kind (PlayerBase::m_i16C).
class Alucard2State27 : public PlayerState {
public:
    explicit Alucard2State27(PlayerBase* p);
    virtual ~Alucard2State27();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_phase;                                // +0x14
    bool m_hitSent;                             // +0x18
    float m_hitTime;                            // +0x1C -1
    float m_minTime;                            // +0x20
    int m_returnAnim;                           // +0x24 passed to state 1
};
