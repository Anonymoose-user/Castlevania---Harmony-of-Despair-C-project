// Dll/Player/Soma/PlayerSoma.h - Soma Cruz, the dllsoma module (vtable
// no members beyond PlayerBase). Names are inferred;
// the voice names come from the module's own table (VX_SOM_*).
//
// Soma registers his own class for most state ids; each derives from the
// library's default for that id (PlayerStates.h) and keeps a pointer back to
// the player.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerSoma : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerSoma();
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
    virtual int  vfunc3B0(int action);          // +0x3B0
    virtual bool vfunc424(int action);          // +0x424
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual int  getComboAnim(int kind, int action);   // +0x464
    virtual int  getChargeAnim(int action);     // +0x468
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474
    virtual int  vfunc480();                    // +0x480

    void deleteState(unsigned int id);
    template <class T> void createState(int id);    // one instance per state class,
    void chainAttack17(int posture, bool checkInput, bool leaveNow);
    bool checkSoulInput();
};

// --- Soma's states ----------------------------------------------------------

// Id 0x17, standing attack.
class SomaState17 : public PlayerState17 {
public:
    explicit SomaState17(PlayerSoma* soma);
    virtual ~SomaState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void chainAttack(int posture, bool checkInput, bool leaveNow);

    PlayerSoma* m_soma;                         // +0x2C
};

// Id 0x18, crouching attack.
class SomaState18 : public PlayerState18 {
public:
    explicit SomaState18(PlayerSoma* soma);
    virtual ~SomaState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerSoma* m_soma;                         // +0x2C
};

// Id 0x19, air attack.
class SomaState19 : public PlayerState19 {
public:
    explicit SomaState19(PlayerSoma* soma);
    virtual ~SomaState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerSoma* m_soma;                         // +0x2C
};

// Id 0x06, back dash.
class SomaState06 : public PlayerState06 {
public:
    explicit SomaState06(PlayerSoma* soma);
    virtual ~SomaState06();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x20
};

// Id 0x0A, slide. Animation 0x17/0x18 by stick lean.
class SomaState0A : public PlayerState0A {
public:
    explicit SomaState0A(PlayerSoma* soma);
    virtual ~SomaState0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerSoma* m_soma;                         // +0x20
    bool m_animStarted;                         // +0x24
};

// Ids 0x0F/0x10, falling (vtables ): soul commands
// stay available.
class SomaState0F : public PlayerState0F {
public:
    explicit SomaState0F(PlayerSoma* soma);
    virtual ~SomaState0F();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerSoma* m_soma;                         // +0x1C
};

class SomaState10 : public PlayerState10 {
public:
    explicit SomaState10(PlayerSoma* soma);
    virtual ~SomaState10();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x20
};

// Id 0x27, holding a ground soul (kind 0x24) while button 8 is held and
// skill points last. Animation 0xE9/0xEA.
class SomaState27 : public PlayerState {
public:
    explicit SomaState27(PlayerBase* p);
    virtual ~SomaState27();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void endHold();
};

// Ids 0x0B-0x0E, jumps (vtables ): a soul command
// replaces the jump's own update for that frame.
class SomaState0B : public PlayerState0B {
public:
    explicit SomaState0B(PlayerSoma* soma);
    virtual ~SomaState0B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerSoma* m_soma;                         // +0x34
};

class SomaState0D : public PlayerState0D {
public:
    explicit SomaState0D(PlayerSoma* soma);
    virtual ~SomaState0D();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerSoma* m_soma;                         // +0x34
};

class SomaState0C : public PlayerState0C {
public:
    explicit SomaState0C(PlayerSoma* soma);
    virtual ~SomaState0C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerSoma* m_soma;                         // +0x34
};

class SomaState0E : public PlayerState0E {
public:
    explicit SomaState0E(PlayerSoma* soma);
    virtual ~SomaState0E();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x34
};

// Id 0x16, dive kick.
class SomaState16 : public PlayerState16 {
public:
    explicit SomaState16(PlayerSoma* soma);
    virtual ~SomaState16();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

// Ids 0x11-0x14, landings (vtables ).
class SomaState11 : public PlayerState11 {
public:
    explicit SomaState11(PlayerSoma* soma);
    virtual ~SomaState11();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerSoma* m_soma;                         // +0x14
};

class SomaState12 : public PlayerState12 {
public:
    explicit SomaState12(PlayerSoma* soma);
    virtual ~SomaState12();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerSoma* m_soma;                         // +0x14
};

class SomaState13 : public PlayerState13 {
public:
    explicit SomaState13(PlayerSoma* soma);
    virtual ~SomaState13();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

class SomaState14 : public PlayerState14 {
public:
    explicit SomaState14(PlayerSoma* soma);
    virtual ~SomaState14();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

// Id 0x26, holding an air soul (kinds 0x2F/0x43) while button 8 is held
class SomaState26 : public PlayerState {
public:
    explicit SomaState26(PlayerBase* p);
    virtual ~SomaState26();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
    void endHold();
};

// Ids 0x07-0x09, crouching (vtables ).
class SomaState07 : public PlayerState07 {
public:
    explicit SomaState07(PlayerSoma* soma);
    virtual ~SomaState07();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

class SomaState08 : public PlayerState08 {
public:
    explicit SomaState08(PlayerSoma* soma);
    virtual ~SomaState08();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

class SomaState09 : public PlayerState09 {
public:
    explicit SomaState09(PlayerSoma* soma);
    virtual ~SomaState09();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

// Id 0x01, standing; owns the soul-command check.
class SomaState01 : public PlayerState01 {
public:
    explicit SomaState01(PlayerBase* p);
    virtual ~SomaState01();
    virtual void update();
    bool checkSoulInput();
};

// Ids 0x05, 0x02-0x04, 0x15: turning and walking (vtables ).
class SomaState05 : public PlayerState05 {
public:
    explicit SomaState05(PlayerSoma* soma);
    virtual ~SomaState05();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

class SomaState02 : public PlayerState02 {
public:
    explicit SomaState02(PlayerSoma* soma);
    virtual ~SomaState02();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

class SomaState03 : public PlayerState03 {
public:
    explicit SomaState03(PlayerSoma* soma);
    virtual ~SomaState03();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

class SomaState04 : public PlayerState04 {
public:
    explicit SomaState04(PlayerSoma* soma);
    virtual ~SomaState04();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

class SomaState15 : public PlayerState15 {
public:
    explicit SomaState15(PlayerSoma* soma);
    virtual ~SomaState15();
    virtual void update();

    PlayerSoma* m_soma;                         // +0x14
};

// Id 0x25, the input-command special. What it does
// depends on the command's kind (PlayerBase::m_i16C): 0-3 and 5/0x12 are
// strikes, 4 is a rising arc driven by sin().
class SomaState25 : public PlayerState {
public:
    explicit SomaState25(PlayerBase* p);
    virtual ~SomaState25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    int m_phase;                                // +0x14
    bool m_hitSent;                             // +0x18
    bool m_soundSent;                           // +0x19
    float m_f1C;                                // +0x1C -1
    float m_minTime;                            // +0x20
    int m_returnAnim;                           // +0x24 passed to state 1
};
