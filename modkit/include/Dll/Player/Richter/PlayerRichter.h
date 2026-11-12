// Dll/Player/Richter/PlayerRichter.h - Richter Belmont, the dllrichter module
// (vtable: PlayerBase plus four flags). Names are
// inferred; the voice names come from the module's own table (VX_RIC_*).
//
// Richter's own moves: state 0x25 (input command 0), 0x26 (skill 0x26,
// a backward hop), 0x27 (button 9 in the air), 0x28 (button 4, back flip),
// 0x29 (input command 1, a rising jump) and 0x2A (a held-attack stance). Each
// air move can be used once per jump (m_airUsed, cleared on the ground).
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerRichter : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerRichter();
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
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474

    virtual bool vfunc430(unsigned int mask);   // +0x430

    void clearAirUsed();
    void deleteState(int id);
    template <class T> void createState(int id);    // one instance per state class,
    void setB348(bool v);
    bool getB348();
    int  airIndex(int posture);
    void setAirUsed(bool v, int posture);
    bool getAirUsed(int posture);
    bool tryCommandMove(bool once);
    bool trySkillMove(bool once);
    bool tryAirMove27();
    bool tryMove28();

    bool m_b348;                                // +0x348 held-attack stance armed (state 0x2A)
    bool m_airUsed[3];                          // +0x349 by airIndex(): command, skill, 0x27
};

// --- Richter's states --------------------------------------------------------

// Id 0x17, standing attack: animation 0xBB on the ground,
// 0xEF in the air.
class RichterState17 : public PlayerState17 {
public:
    explicit RichterState17(PlayerRichter* r);
    virtual ~RichterState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerRichter* m_richter;                   // +0x2C
};

// Id 0x18, crouching attack. Animation 0xBC.
class RichterState18 : public PlayerState18 {
public:
    explicit RichterState18(PlayerRichter* r);
    virtual ~RichterState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerRichter* m_richter;                   // +0x2C
};

// Id 0x19, air attack. Animation 0xBD / 0xF0.
class RichterState19 : public PlayerState19 {
public:
    explicit RichterState19(PlayerBase* p);
    virtual ~RichterState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x2A, the held-attack stance: entered when an
// attack ends with button 5 still held; new presses go to the host
// (PlayerBase::setI2DC) until it is released.
class RichterState2A : public PlayerState {
public:
    explicit RichterState2A(PlayerBase* p);
    virtual ~RichterState2A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    int m_returnAnim;                           // +0x14 passed back to state 1/8
    int m_evAction;                             // +0x18 event 10 payload
    int m_evI1C;                                // +0x1C 0x10
    float m_evF20;                              // +0x20 0
    float m_evF24;                              // +0x24 26
    float m_evF28;                              // +0x28 -6 (+16 crouching)
    float m_evF2C;                              // +0x2C 4
    unsigned int m_prevMask;                    // +0x30
};

// Id 0x06, back dash.
class RichterState06 : public PlayerState06 {
public:
    explicit RichterState06(PlayerRichter* r);
    virtual ~RichterState06();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x20
};

// Id 0x0A, slide: the back flip (0x28) can start in its
// first half second.
class RichterState0A : public PlayerState0A {
public:
    explicit RichterState0A(PlayerRichter* r);
    virtual ~RichterState0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    PlayerRichter* m_richter;                   // +0x20
};

// Ids 0x0F/0x10, falling (vtables ).
class RichterState0F : public PlayerState0F {
public:
    explicit RichterState0F(PlayerRichter* r);
    virtual ~RichterState0F();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerRichter* m_richter;                   // +0x1C
};

class RichterState10 : public PlayerState10 {
public:
    explicit RichterState10(PlayerRichter* r);
    virtual ~RichterState10();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x20
};

// Ids 0x0B-0x0E, jumps (vtables ): an air move replaces
// the jump's own update for that frame.
class RichterState0B : public PlayerState0B {
public:
    explicit RichterState0B(PlayerRichter* r);
    virtual ~RichterState0B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerRichter* m_richter;                   // +0x34
    unsigned char _pad38[4];                    // object is 0x3C bytes, never touched
};

class RichterState0D : public PlayerState0D {
public:
    explicit RichterState0D(PlayerRichter* r);
    virtual ~RichterState0D();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerRichter* m_richter;                   // +0x34
};

class RichterState0C : public PlayerState0C {
public:
    explicit RichterState0C(PlayerRichter* r);
    virtual ~RichterState0C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerRichter* m_richter;                   // +0x34
};

class RichterState0E : public PlayerState0E {
public:
    explicit RichterState0E(PlayerRichter* r);
    virtual ~RichterState0E();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x34
};

// Ids 0x11-0x14, landings (vtables ).
class RichterState11 : public PlayerState11 {
public:
    explicit RichterState11(PlayerRichter* r);
    virtual ~RichterState11();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerRichter* m_richter;                   // +0x14
};

class RichterState12 : public PlayerState12 {
public:
    explicit RichterState12(PlayerRichter* r);
    virtual ~RichterState12();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerRichter* m_richter;                   // +0x14
};

class RichterState13 : public PlayerState13 {
public:
    explicit RichterState13(PlayerRichter* r);
    virtual ~RichterState13();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x14
};

class RichterState14 : public PlayerState14 {
public:
    explicit RichterState14(PlayerRichter* r);
    virtual ~RichterState14();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x14
};

// Ids 0x07-0x09, crouching (vtables ).
class RichterState07 : public PlayerState07 {
public:
    explicit RichterState07(PlayerRichter* r);
    virtual ~RichterState07();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x14
};

class RichterState08 : public PlayerState08 {
public:
    explicit RichterState08(PlayerRichter* r);
    virtual ~RichterState08();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x14
};

class RichterState09 : public PlayerState09 {
public:
    explicit RichterState09(PlayerRichter* r);
    virtual ~RichterState09();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x14
};

// Id 0x28, back flip from the ground. Animation 0x19.
class RichterState28 : public PlayerState {
public:
    explicit RichterState28(PlayerRichter* r);
    virtual ~RichterState28();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
    void land();

    PlayerRichter* m_richter;                   // +0x14
    bool m_canChain;                            // +0x18 cleared once button 4 is released
    int m_evKind;                               // +0x1C event 0xC payload
    int m_evI20;                                // +0x20
    float m_evF24;                              // +0x24
    float m_evF28;                              // +0x28
    bool m_evB2C;                               // +0x2C
};

// Id 0x27, backward air move. Animation 0xFE.
class RichterState27 : public PlayerState {
public:
    explicit RichterState27(PlayerRichter* r);
    virtual ~RichterState27();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();

    PlayerRichter* m_richter;                   // +0x14
    bool m_invincible;                          // +0x18 PlayerBase::setB2B8 for 0.2 s
};

// Id 0x26, backward hop (skill 0x26). Animation 0xDA.
class RichterState26 : public PlayerState {
public:
    explicit RichterState26(PlayerBase* p);
    virtual ~RichterState26();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void end();

    int m_phase;                                // +0x14
    int m_evKind;                               // +0x18 event 0xC payload
    int m_evI1C;                                // +0x1C
    float m_evF20;                              // +0x20
    float m_evF24;                              // +0x24
    bool m_evB28;                               // +0x28
};

// Id 0x01, standing; owns the move checks.
class RichterState01 : public PlayerState01 {
public:
    explicit RichterState01(PlayerRichter* r);
    virtual ~RichterState01();
    virtual void update();
    bool tryCommandMove();
    bool trySkillMove();
    bool tryAirMove27();
    bool tryMove28();

    PlayerRichter* m_richter;                   // +0x14
};

// Id 0x25, command 0: a sliding dash. Animation 0xD9.
class RichterState25 : public PlayerState {
public:
    explicit RichterState25(PlayerBase* p);
    virtual ~RichterState25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void end();

    int m_phase;                                // +0x14
};

// Ids 0x05, 0x02-0x04, 0x15: turning and walking (vtables ).
class RichterState05 : public PlayerState05 {
public:
    explicit RichterState05(PlayerRichter* r);
    virtual ~RichterState05();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x14
};

// Id 0x29, command 1: a rising jump. Animation 0x21.
class RichterState29 : public PlayerState {
public:
    explicit RichterState29(PlayerBase* p);
    virtual ~RichterState29();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    void end();
};

class RichterState02 : public PlayerState02 {
public:
    explicit RichterState02(PlayerRichter* r);
    virtual ~RichterState02();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x14
};

class RichterState03 : public PlayerState03 {
public:
    explicit RichterState03(PlayerRichter* r);
    virtual ~RichterState03();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x14
};

class RichterState04 : public PlayerState04 {
public:
    explicit RichterState04(PlayerRichter* r);
    virtual ~RichterState04();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x14
};

class RichterState15 : public PlayerState15 {
public:
    explicit RichterState15(PlayerRichter* r);
    virtual ~RichterState15();
    virtual void update();

    PlayerRichter* m_richter;                   // +0x14
};
