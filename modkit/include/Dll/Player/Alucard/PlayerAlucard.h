// Dll/Player/Alucard/PlayerAlucard.h - Alucard, the dllalucard module (vtable
// no members beyond PlayerBase). Names are inferred;
// the voice names come from the module's own table (VX_ALC_*).
//
// Alucard registers his own class for most state ids; each derives from the
// library's default for that id (PlayerStates.h). Ids 0x25/0x26 turn him into
// a bat and back (animation 0x102); id 0x27 is his input-command special.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerAlucard : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerAlucard();
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

// --- Alucard's states --------------------------------------------------------

// Id 0x17, standing attack.
class AlucardState17 : public PlayerState17 {
public:
    explicit AlucardState17(PlayerBase* p);
    virtual ~AlucardState17();
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
class AlucardState18 : public PlayerState18 {
public:
    explicit AlucardState18(PlayerAlucard* alucard);
    virtual ~AlucardState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerAlucard* m_alucard;                   // +0x2C
};

// Id 0x19, air attack.
class AlucardState19 : public PlayerState19 {
public:
    explicit AlucardState19(PlayerAlucard* alucard);
    virtual ~AlucardState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void setAirAnim(int anim, int fallAnim, int riseAnim);

    PlayerAlucard* m_alucard;                   // +0x2C
    float m_time;                               // +0x30
};

// Ids 0x1A-0x1C, hit reactions (vtables ).
class AlucardState1A : public PlayerState1A {
public:
    explicit AlucardState1A(PlayerBase* p);
    virtual ~AlucardState1A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class AlucardState1B : public PlayerState1B {
public:
    explicit AlucardState1B(PlayerBase* p);
    virtual ~AlucardState1B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class AlucardState1C : public PlayerState1C {
public:
    explicit AlucardState1C(PlayerBase* p);
    virtual ~AlucardState1C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x06, back dash.
class AlucardState06 : public PlayerState06 {
public:
    explicit AlucardState06(PlayerBase* p);
    virtual ~AlucardState06();
    virtual void update();
};

// Id 0x0A, slide. Animation 0x17, then 0x18.
class AlucardState0A : public PlayerState0A {
public:
    explicit AlucardState0A(PlayerBase* p);
    virtual ~AlucardState0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_animSwitched;                         // +0x20
};

// Ids 0x0F/0x10, falling (vtables ).
class AlucardState0F : public PlayerState0F {
public:
    explicit AlucardState0F(PlayerBase* p);
    virtual ~AlucardState0F();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class AlucardState10 : public PlayerState10 {
public:
    explicit AlucardState10(PlayerBase* p);
    virtual ~AlucardState10();
    virtual void update();
};

// Id 0x25, turning into a bat: 0.3 s of transformation,
// then flying with the stick (or the d-pad) for as long as m_time stays under
// 0.1 s... until button 8 or the time ends it (state 0x26).
class AlucardState25 : public PlayerState {
public:
    explicit AlucardState25(PlayerBase* p);
    virtual ~AlucardState25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    int m_phase;                                // +0x14
    float m_time;                               // +0x18
    float m_blend;                              // +0x1C passed to event 3 by address
};

// Id 0x26, turning back from a bat.
class AlucardState26 : public PlayerState {
public:
    explicit AlucardState26(PlayerBase* p);
    virtual ~AlucardState26();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    int m_phase;                                // +0x14
    float m_time;                               // +0x18
    float m_blend;                              // +0x1C passed to event 3 by address
};

// Ids 0x0B-0x0E, jumps (vtables ): the bat command
// replaces the jump's own update for that frame.
class AlucardState0B : public PlayerState0B {
public:
    explicit AlucardState0B(PlayerBase* p);
    virtual ~AlucardState0B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_anim;                                 // +0x34 0, 1 (0x1E), 2 (0x1F)
};

class AlucardState0D : public PlayerState0D {
public:
    explicit AlucardState0D(PlayerBase* p);
    virtual ~AlucardState0D();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class AlucardState0C : public PlayerState0C {
public:
    explicit AlucardState0C(PlayerBase* p);
    virtual ~AlucardState0C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class AlucardState0E : public PlayerState0E {
public:
    explicit AlucardState0E(PlayerBase* p);
    virtual ~AlucardState0E();
    virtual void update();
};

// Id 0x16, dive kick.
class AlucardState16 : public PlayerState16 {
public:
    explicit AlucardState16(PlayerBase* p);
    virtual ~AlucardState16();
    virtual void update();
};

// Ids 0x11-0x14, landings (vtables ).
class AlucardState11 : public PlayerState11 {
public:
    explicit AlucardState11(PlayerBase* p);
    virtual ~AlucardState11();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class AlucardState12 : public PlayerState12 {
public:
    explicit AlucardState12(PlayerBase* p);
    virtual ~AlucardState12();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class AlucardState13 : public PlayerState13 {
public:
    explicit AlucardState13(PlayerBase* p);
    virtual ~AlucardState13();
    virtual void update();
};

class AlucardState14 : public PlayerState14 {
public:
    explicit AlucardState14(PlayerBase* p);
    virtual ~AlucardState14();
    virtual void update();
};

// Id 0x21, looking up.
class AlucardState21 : public PlayerState21 {
public:
    explicit AlucardState21(PlayerBase* p);
    virtual ~AlucardState21();
    virtual void enter();
};

// Ids 0x07-0x09, crouching (vtables ): m_i2F0 other
// than -1 shows animation 0xD8 / 6.
class AlucardState07 : public PlayerState07 {
public:
    explicit AlucardState07(PlayerBase* p);
    virtual ~AlucardState07();
    virtual void update();
};

class AlucardState08 : public PlayerState08 {
public:
    explicit AlucardState08(PlayerBase* p);
    virtual ~AlucardState08();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_i2F0;                                 // +0x14 last m_i2F0 shown, -1 none
};

class AlucardState09 : public PlayerState09 {
public:
    explicit AlucardState09(PlayerBase* p);
    virtual ~AlucardState09();
    virtual void update();
};

// Id 0x01, standing with an idle cycle: after 10 s
// animation 4/5, then back.
class AlucardState01 : public PlayerState01 {
public:
    explicit AlucardState01(PlayerBase* p);
    virtual ~AlucardState01();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_idlePhase;                            // +0x14
    float m_idleTime;                           // +0x18
    int m_i2F0;                                 // +0x1C last m_i2F0 shown, -1 none
};

// Id 0x1E, petrified: one of three animations.
class AlucardState1E : public PlayerState1E {
public:
    explicit AlucardState1E(PlayerBase* p);
    virtual ~AlucardState1E();
    virtual void enter();
};

// Ids 0x05, 0x02-0x04, 0x15: turning and walking (vtables ).
class AlucardState05 : public PlayerState05 {
public:
    explicit AlucardState05(PlayerAlucard* alucard);
    virtual ~AlucardState05();
    virtual void update();

    PlayerAlucard* m_alucard;                   // +0x14
};

class AlucardState02 : public PlayerState02 {
public:
    explicit AlucardState02(PlayerAlucard* alucard);
    virtual ~AlucardState02();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_turned;                               // +0x14
    PlayerAlucard* m_alucard;                   // +0x18
};

class AlucardState03 : public PlayerState03 {
public:
    explicit AlucardState03(PlayerAlucard* alucard);
    virtual ~AlucardState03();
    virtual void update();

    PlayerAlucard* m_alucard;                   // +0x14
};

class AlucardState04 : public PlayerState04 {
public:
    explicit AlucardState04(PlayerBase* p);
    virtual ~AlucardState04();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class AlucardState15 : public PlayerState15 {
public:
    explicit AlucardState15(PlayerAlucard* alucard);
    virtual ~AlucardState15();
    virtual void update();

    PlayerAlucard* m_alucard;                   // +0x14
};

// Id 0x27, the input-command special. What it does
// depends on the command's kind (PlayerBase::m_i16C).
class AlucardState27 : public PlayerState {
public:
    explicit AlucardState27(PlayerBase* p);
    virtual ~AlucardState27();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_phase;                                // +0x14
    bool m_hitSent;                             // +0x18
    float m_hitTime;                            // +0x1C -1
    float m_minTime;                            // +0x20
    int m_returnAnim;                           // +0x24 passed to state 1
};
