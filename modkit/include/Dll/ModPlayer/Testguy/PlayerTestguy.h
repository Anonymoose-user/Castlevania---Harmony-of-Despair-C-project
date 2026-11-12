// Dll/ModPlayer/Testguy/PlayerTestguy.h - Testguy Cruz, the dlltestguy module (vtable
// no members beyond PlayerBase). Names are inferred;
// the voice names come from the module's own table (VX_SOM_*).
//
// Testguy registers his own class for most state ids; each derives from the
// library's default for that id (PlayerStates.h) and keeps a pointer back to
// the player.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerTestguy : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerTestguy();
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

// --- Testguy's states ----------------------------------------------------------

// Id 0x17, standing attack.
class TestguyState17 : public PlayerState17 {
public:
    explicit TestguyState17(PlayerTestguy* testguy);
    virtual ~TestguyState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void chainAttack(int posture, bool checkInput, bool leaveNow);

    PlayerTestguy* m_testguy;                         // +0x2C
};

// Id 0x18, crouching attack.
class TestguyState18 : public PlayerState18 {
public:
    explicit TestguyState18(PlayerTestguy* testguy);
    virtual ~TestguyState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerTestguy* m_testguy;                         // +0x2C
};

// Id 0x19, air attack.
class TestguyState19 : public PlayerState19 {
public:
    explicit TestguyState19(PlayerTestguy* testguy);
    virtual ~TestguyState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerTestguy* m_testguy;                         // +0x2C
};

// Id 0x06, back dash.
class TestguyState06 : public PlayerState06 {
public:
    explicit TestguyState06(PlayerTestguy* testguy);
    virtual ~TestguyState06();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x20
};

// Id 0x0A, slide. Animation 0x17/0x18 by stick lean.
class TestguyState0A : public PlayerState0A {
public:
    explicit TestguyState0A(PlayerTestguy* testguy);
    virtual ~TestguyState0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerTestguy* m_testguy;                         // +0x20
    bool m_animStarted;                         // +0x24
};

// Ids 0x0F/0x10, falling (vtables ): soul commands
// stay available.
class TestguyState0F : public PlayerState0F {
public:
    explicit TestguyState0F(PlayerTestguy* testguy);
    virtual ~TestguyState0F();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerTestguy* m_testguy;                         // +0x1C
};

class TestguyState10 : public PlayerState10 {
public:
    explicit TestguyState10(PlayerTestguy* testguy);
    virtual ~TestguyState10();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x20
};

// Id 0x27, holding a ground soul (kind 0x24) while button 8 is held and
// skill points last. Animation 0xE9/0xEA.
class TestguyState27 : public PlayerState {
public:
    explicit TestguyState27(PlayerBase* p);
    virtual ~TestguyState27();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void endHold();
};

// Ids 0x0B-0x0E, jumps (vtables ): a soul command
// replaces the jump's own update for that frame.
class TestguyState0B : public PlayerState0B {
public:
    explicit TestguyState0B(PlayerTestguy* testguy);
    virtual ~TestguyState0B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerTestguy* m_testguy;                         // +0x34
};

class TestguyState0D : public PlayerState0D {
public:
    explicit TestguyState0D(PlayerTestguy* testguy);
    virtual ~TestguyState0D();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerTestguy* m_testguy;                         // +0x34
};

class TestguyState0C : public PlayerState0C {
public:
    explicit TestguyState0C(PlayerTestguy* testguy);
    virtual ~TestguyState0C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerTestguy* m_testguy;                         // +0x34
};

class TestguyState0E : public PlayerState0E {
public:
    explicit TestguyState0E(PlayerTestguy* testguy);
    virtual ~TestguyState0E();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x34
};

// Id 0x16, dive kick.
class TestguyState16 : public PlayerState16 {
public:
    explicit TestguyState16(PlayerTestguy* testguy);
    virtual ~TestguyState16();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

// Ids 0x11-0x14, landings (vtables ).
class TestguyState11 : public PlayerState11 {
public:
    explicit TestguyState11(PlayerTestguy* testguy);
    virtual ~TestguyState11();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerTestguy* m_testguy;                         // +0x14
};

class TestguyState12 : public PlayerState12 {
public:
    explicit TestguyState12(PlayerTestguy* testguy);
    virtual ~TestguyState12();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerTestguy* m_testguy;                         // +0x14
};

class TestguyState13 : public PlayerState13 {
public:
    explicit TestguyState13(PlayerTestguy* testguy);
    virtual ~TestguyState13();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

class TestguyState14 : public PlayerState14 {
public:
    explicit TestguyState14(PlayerTestguy* testguy);
    virtual ~TestguyState14();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

// Id 0x26, holding an air soul (kinds 0x2F/0x43) while button 8 is held
class TestguyState26 : public PlayerState {
public:
    explicit TestguyState26(PlayerBase* p);
    virtual ~TestguyState26();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
    void endHold();
};

// Ids 0x07-0x09, crouching (vtables ).
class TestguyState07 : public PlayerState07 {
public:
    explicit TestguyState07(PlayerTestguy* testguy);
    virtual ~TestguyState07();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

class TestguyState08 : public PlayerState08 {
public:
    explicit TestguyState08(PlayerTestguy* testguy);
    virtual ~TestguyState08();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

class TestguyState09 : public PlayerState09 {
public:
    explicit TestguyState09(PlayerTestguy* testguy);
    virtual ~TestguyState09();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

// Id 0x01, standing; owns the soul-command check.
class TestguyState01 : public PlayerState01 {
public:
    explicit TestguyState01(PlayerBase* p);
    virtual ~TestguyState01();
    virtual void update();
    bool checkSoulInput();
};

// Ids 0x05, 0x02-0x04, 0x15: turning and walking (vtables ).
class TestguyState05 : public PlayerState05 {
public:
    explicit TestguyState05(PlayerTestguy* testguy);
    virtual ~TestguyState05();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

class TestguyState02 : public PlayerState02 {
public:
    explicit TestguyState02(PlayerTestguy* testguy);
    virtual ~TestguyState02();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

class TestguyState03 : public PlayerState03 {
public:
    explicit TestguyState03(PlayerTestguy* testguy);
    virtual ~TestguyState03();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

class TestguyState04 : public PlayerState04 {
public:
    explicit TestguyState04(PlayerTestguy* testguy);
    virtual ~TestguyState04();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

class TestguyState15 : public PlayerState15 {
public:
    explicit TestguyState15(PlayerTestguy* testguy);
    virtual ~TestguyState15();
    virtual void update();

    PlayerTestguy* m_testguy;                         // +0x14
};

// Id 0x25, the input-command special. What it does
// depends on the command's kind (PlayerBase::m_i16C): 0-3 and 5/0x12 are
// strikes, 4 is a rising arc driven by sin().
class TestguyState25 : public PlayerState {
public:
    explicit TestguyState25(PlayerBase* p);
    virtual ~TestguyState25();
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
