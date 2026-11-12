// Dll/Player/Jonathan/PlayerJonathan.h - Jonathan Morris, the dlljonathan
// module (vtable: PlayerBase plus one flag). Names are
// inferred; the voice names come from the module's own table (VX_JON_*).
//
// Jonathan registers his own class for most state ids; each derives from the
// library's default for that id (PlayerStates.h). Unlike Soma's they keep no
// pointer back to the player. Ids 0x25-0x28 are his input-command specials
// (g_jonathanCommandStates), 0x29/0x2A a guard held with button 8, 0x2B a
// follow-up whip swing.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerJonathan : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerJonathan();
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
    virtual void getFacingDir(float* dir, int* out2);  // +0x3E8
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual int  getComboAnim(int kind, int action);   // +0x464
    virtual bool canAttack(int slot, int action, int weapon);   // +0x470
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474
    virtual int  vfunc480();                    // +0x480

    virtual int  vfunc41C(int a, int action);   // +0x41C
    virtual bool vfunc430(unsigned int mask);   // +0x430

    void deleteState(unsigned int id);
    template <class T> void createState(int id);    // one instance per state class,
    void setFollowUp(bool v);
    bool getFollowUp();

    bool m_followUp;                            // +0x348 a whip attack chains into 0x2B
};

// --- Jonathan's states -------------------------------------------------------

// Id 0x17, standing attack.
class JonathanState17 : public PlayerState17 {
public:
    explicit JonathanState17(PlayerBase* p);
    virtual ~JonathanState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    bool m_airWeapon;                           // +0x2C air attack with weapon 1
    bool m_released;                            // +0x2D button 7 released
};

// Id 0x18, crouching attack.
class JonathanState18 : public PlayerState18 {
public:
    explicit JonathanState18(PlayerBase* p);
    virtual ~JonathanState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x19, air attack.
class JonathanState19 : public PlayerState19 {
public:
    explicit JonathanState19(PlayerBase* p);
    virtual ~JonathanState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x2B, the whip follow-up: animation 0xBB-0xC1,
// button 5 held keeps it going.
class JonathanState2B : public PlayerState {
public:
    explicit JonathanState2B(PlayerBase* p);
    virtual ~JonathanState2B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    int m_returnAnim;                           // +0x14
    int m_evAction;                             // +0x18 event 10 data, by address
    int m_evKind;                               // +0x1C
    float m_evX;                                // +0x20
    float m_evY;                                // +0x24
    float m_evZ;                                // +0x28
    float m_evW;                                // +0x2C
    unsigned int m_prevMask;                    // +0x30
};

// Id 0x06, back dash.
class JonathanState06 : public PlayerState06 {
public:
    explicit JonathanState06(PlayerBase* p);
    virtual ~JonathanState06();
    virtual void update();
};

// Id 0x0A, slide; not registered by init (the library
// state is).
class JonathanState0A : public PlayerState0A {
public:
    explicit JonathanState0A(PlayerBase* p);
    virtual ~JonathanState0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
};

// Ids 0x0F/0x10, falling (vtables ).
class JonathanState0F : public PlayerState0F {
public:
    explicit JonathanState0F(PlayerBase* p);
    virtual ~JonathanState0F();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class JonathanState10 : public PlayerState10 {
public:
    explicit JonathanState10(PlayerBase* p);
    virtual ~JonathanState10();
    virtual void update();
};

// Id 0x29, guarding on the ground while button 8 is held.
// Animation 0xEA.
class JonathanState29 : public PlayerState {
public:
    explicit JonathanState29(PlayerBase* p);
    virtual ~JonathanState29();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    void endGuard();
};

// Id 0x2A, guarding in the air. Animation 0xEB.
class JonathanState2A : public PlayerState {
public:
    explicit JonathanState2A(PlayerBase* p);
    virtual ~JonathanState2A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    void endGuard();
};

// Ids 0x0B-0x0E, jumps (vtables ).
class JonathanState0B : public PlayerState0B {
public:
    explicit JonathanState0B(PlayerBase* p);
    virtual ~JonathanState0B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    unsigned char _pad34[4];                    // the factory allocates 0x38 bytes
};

class JonathanState0D : public PlayerState0D {
public:
    explicit JonathanState0D(PlayerBase* p);
    virtual ~JonathanState0D();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class JonathanState0C : public PlayerState0C {
public:
    explicit JonathanState0C(PlayerBase* p);
    virtual ~JonathanState0C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class JonathanState0E : public PlayerState0E {
public:
    explicit JonathanState0E(PlayerBase* p);
    virtual ~JonathanState0E();
    virtual void update();
};

// Id 0x16, dive kick; not registered by init (the
// library state is).
class JonathanState16 : public PlayerState16 {
public:
    explicit JonathanState16(PlayerBase* p);
    virtual ~JonathanState16();
    virtual void update();
};

// Id 0x25, command special 0: a backflip that bounces off the wall when
// m_b27C is set. Animation 0xDA.
class JonathanState25 : public PlayerState {
public:
    explicit JonathanState25(PlayerBase* p);
    virtual ~JonathanState25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void finish();

    int m_phase;                                // +0x14
    int m_evA;                                  // +0x18 event 0xC data, by address
    int m_evB;                                  // +0x1C
    float m_evC;                                // +0x20
    float m_evD;                                // +0x24
    bool m_evE;                                 // +0x28
};

// Ids 0x11-0x14, landings (vtables ).
class JonathanState11 : public PlayerState11 {
public:
    explicit JonathanState11(PlayerBase* p);
    virtual ~JonathanState11();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class JonathanState12 : public PlayerState12 {
public:
    explicit JonathanState12(PlayerBase* p);
    virtual ~JonathanState12();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

class JonathanState13 : public PlayerState13 {
public:
    explicit JonathanState13(PlayerBase* p);
    virtual ~JonathanState13();
    virtual void update();
};

class JonathanState14 : public PlayerState14 {
public:
    explicit JonathanState14(PlayerBase* p);
    virtual ~JonathanState14();
    virtual void update();
};

// Id 0x27, command special 2: a forward slide.
// Animation 0xD9.
class JonathanState27 : public PlayerState {
public:
    explicit JonathanState27(PlayerBase* p);
    virtual ~JonathanState27();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void finish();

    bool m_slowed;                              // +0x14
};

// Ids 0x07-0x09, crouching (vtables ).
class JonathanState07 : public PlayerState07 {
public:
    explicit JonathanState07(PlayerBase* p);
    virtual ~JonathanState07();
    virtual void update();
};

class JonathanState08 : public PlayerState08 {
public:
    explicit JonathanState08(PlayerBase* p);
    virtual ~JonathanState08();
    virtual void update();
};

class JonathanState09 : public PlayerState09 {
public:
    explicit JonathanState09(PlayerBase* p);
    virtual ~JonathanState09();
    virtual void update();
};

// Id 0x26, command special 1: a dash strike. Animation
// 0xE0, then 0xE2.
class JonathanState26 : public PlayerState {
public:
    explicit JonathanState26(PlayerBase* p);
    virtual ~JonathanState26();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void finish();

    int m_phase;                                // +0x14
    float m_time;                               // +0x18
    bool m_struck;                              // +0x1C
    bool m_ended;                               // +0x1D
    bool m_listSent;                            // +0x1E
};

// Id 0x01, standing.
class JonathanState01 : public PlayerState01 {
public:
    explicit JonathanState01(PlayerBase* p);
    virtual ~JonathanState01();
    virtual void update();
};

// Id 0x05, turning.
class JonathanState05 : public PlayerState05 {
public:
    explicit JonathanState05(PlayerBase* p);
    virtual ~JonathanState05();
    virtual void update();
};

// Id 0x28, command special 3: an upward leap.
// Animation 0x21.
class JonathanState28 : public PlayerState {
public:
    explicit JonathanState28(PlayerBase* p);
    virtual ~JonathanState28();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    void finish();
};

// Ids 0x02-0x04, 0x15, walking (vtables ).
class JonathanState02 : public PlayerState02 {
public:
    explicit JonathanState02(PlayerBase* p);
    virtual ~JonathanState02();
    virtual void update();
};

class JonathanState03 : public PlayerState03 {
public:
    explicit JonathanState03(PlayerBase* p);
    virtual ~JonathanState03();
    virtual void update();
};

class JonathanState04 : public PlayerState04 {
public:
    explicit JonathanState04(PlayerBase* p);
    virtual ~JonathanState04();
    virtual void update();
};

class JonathanState15 : public PlayerState15 {
public:
    explicit JonathanState15(PlayerBase* p);
    virtual ~JonathanState15();
    virtual void update();
};
