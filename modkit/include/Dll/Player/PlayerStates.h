// Dll/Player/PlayerStates.h - the default player states every player module
// links (dllsoma ). Each class is the library's version
// of one state id; a module either registers it as is or derives its own
// class for that id (dllsoma derives most, see Soma/PlayerSoma.h). Classes
// are named after the id (decomp/analysis/module/states_dllsoma.json); what an
// id means is noted where the code makes it plain.
#pragma once

#include "Dll/Player/PlayerState.h"

// --- attack states (PlayerActionState) --------------------------------------

// Id 0x17, standing attack. Animation 0x49 / 0x4F.
class PlayerState17 : public PlayerActionState {
public:
    explicit PlayerState17(PlayerBase* p);
    virtual ~PlayerState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x18, crouching attack. Animation 0x4A / 0x50.
class PlayerState18 : public PlayerActionState {
public:
    explicit PlayerState18(PlayerBase* p);
    virtual ~PlayerState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x19, air attack. Animation 0x4B / 0x51.
class PlayerState19 : public PlayerActionState {
public:
    explicit PlayerState19(PlayerBase* p);
    virtual ~PlayerState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// --- hit reactions ----------------------------------------------------------

// Common base of 0x1A-0x1D: plays a pain voice.
class PlayerHitState : public PlayerState {
public:
    explicit PlayerHitState(PlayerBase* p);
    virtual ~PlayerHitState();
    virtual void enter();
    virtual void update();                      // (empty)
    virtual void interrupt();                   // (empty)
    virtual bool canInterrupt();
};

// Id 0x1A, standing flinch. Animation 0x32 / 0x36.
class PlayerState1A : public PlayerHitState {
public:
    explicit PlayerState1A(PlayerBase* p);
    virtual ~PlayerState1A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    void recover();
};

// Id 0x1B, crouching flinch. Animation 0x37.
class PlayerState1B : public PlayerHitState {
public:
    explicit PlayerState1B(PlayerBase* p);
    virtual ~PlayerState1B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    void recover();
};

// Id 0x1C, knocked back into the air. Animation 0x38.
class PlayerState1C : public PlayerHitState {
public:
    explicit PlayerState1C(PlayerBase* p);
    virtual ~PlayerState1C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
};

// Id 0x1D. Animation 0xFD. Not registered by dllsoma.
class PlayerState1D : public PlayerHitState {
public:
    explicit PlayerState1D(PlayerBase* p);
    virtual ~PlayerState1D();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
};

// --- dashes -----------------------------------------------------------------

// Id 0x06, back dash. Animation 0x2A, 0.4 s.
class PlayerState06 : public PlayerState {
public:
    explicit PlayerState06(PlayerBase* p);
    virtual ~PlayerState06();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();

    float m_speed;                              // +0x14
    float m_accel;                              // +0x18
    bool m_started;                             // +0x1C
};

// Id 0x0A, crouching slide. Animation 0x18, 0.6 s.
class PlayerState0A : public PlayerState {
public:
    explicit PlayerState0A(PlayerBase* p);
    virtual ~PlayerState0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();

    float m_speed;                              // +0x14
    float m_accel;                              // +0x18
    bool m_started;                             // +0x1C
};

// --- down, air, jump --------------------------------------------------------

// Id 0x1F, knocked down / out of HP. Animation 0x46.
class PlayerState1F : public PlayerState {
public:
    explicit PlayerState1F(PlayerBase* p);
    virtual ~PlayerState1F();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    bool m_landed;                              // +0x14
};

// Base of the falling states 0x0F/0x10: the air attack
// (state 0x19) runs inside it.
class PlayerAirState : public PlayerState {
public:
    explicit PlayerAirState(PlayerBase* p);
    virtual ~PlayerAirState();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();

    float m_softLanding;                        // +0x14 200: landing speed for 0x11
    float m_hardLanding;                        // +0x18 400: landing speed for 0x12
};

// Id 0x0F, falling.
class PlayerState0F : public PlayerAirState {
public:
    explicit PlayerState0F(PlayerBase* p);
    virtual ~PlayerState0F();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x10, falling with its own gravity.
class PlayerState10 : public PlayerAirState {
public:
    explicit PlayerState10(PlayerBase* p);
    virtual ~PlayerState10();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    float m_gravity;                            // +0x1C 627.2
};

// Id 0x20, held. Animation 0xFC, 0x32 while struck.
class PlayerState20 : public PlayerState {
public:
    explicit PlayerState20(PlayerBase* p);
    virtual ~PlayerState20();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    float m_flinchTime;                         // +0x14
};

// Base of the jump states 0x0B-0x0E.
class PlayerJumpState : public PlayerState {
public:
    explicit PlayerJumpState(PlayerBase* p);
    virtual ~PlayerJumpState();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
    void toFall();
    void toFall10();

    float m_shortHop;                           // +0x14 0.45 s
    float m_holdTime;                           // +0x18 0.05 s
    float m_jumpSpeed;                          // +0x1C -290
    float m_apexSpeed;                          // +0x20 -8
    float m_highJumpSpeed;                      // +0x24 -203
    float m_maxRise;                            // +0x28 -50
    float m_gravity;                            // +0x2C 630
    bool m_canSteer;                            // +0x30
};

// Id 0x0B, jump. Animation 0x1C, 0x1F when moving.
class PlayerState0B : public PlayerJumpState {
public:
    explicit PlayerState0B(PlayerBase* p);
    virtual ~PlayerState0B();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x0D, falling out of a jump.
class PlayerState0D : public PlayerJumpState {
public:
    explicit PlayerState0D(PlayerBase* p);
    virtual ~PlayerState0D();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x0C, double jump. Animation 0x20.
class PlayerState0C : public PlayerJumpState {
public:
    explicit PlayerState0C(PlayerBase* p);
    virtual ~PlayerState0C();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x0E, end of a short hop.
class PlayerState0E : public PlayerJumpState {
public:
    explicit PlayerState0E(PlayerBase* p);
    virtual ~PlayerState0E();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// --- dive kick, landings ----------------------------------------------------

// Id 0x16, dive kick: 450 down, up to 260 sideways from
// the stick. Animation 0x2D straight down, 0x2E diagonal.
class PlayerState16 : public PlayerState {
public:
    explicit PlayerState16(PlayerBase* p);
    virtual ~PlayerState16();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
};

// Base of the landing states 0x11-0x14.
class PlayerLandState : public PlayerState {
public:
    explicit PlayerLandState(PlayerBase* p);
    virtual ~PlayerLandState();
    virtual void enter();
    virtual void update();
    virtual void interrupt() = 0;
    virtual bool canInterrupt();
};

// Id 0x11, soft landing. Animation 0x23.
class PlayerState11 : public PlayerLandState {
public:
    explicit PlayerState11(PlayerBase* p);
    virtual ~PlayerState11();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x12, hard landing. Animation 0x25.
class PlayerState12 : public PlayerLandState {
public:
    explicit PlayerState12(PlayerBase* p);
    virtual ~PlayerState12();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x13, landing with a skid. Animation 0x26, friction 480.
class PlayerState13 : public PlayerLandState {
public:
    explicit PlayerState13(PlayerBase* p);
    virtual ~PlayerState13();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x14, landing with a long skid. Animation 0x27,
// friction 960.
class PlayerState14 : public PlayerLandState {
public:
    explicit PlayerState14(PlayerBase* p);
    virtual ~PlayerState14();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
};

// Id 0x21, looking up: animation 6 while button 2 is
// held, voice 0x0E after 1.5 s.
class PlayerState21 : public PlayerState {
public:
    explicit PlayerState21(PlayerBase* p);
    virtual ~PlayerState21();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    virtual bool canInterrupt();

    float m_voiceDelay;                         // +0x14
    bool m_voiced;                              // +0x18
};

// --- standing, crouching, walking ------------------------------------------

// Id 0x01, standing. Animation 2 unless m_i24C names one.
class PlayerState01 : public PlayerState {
public:
    explicit PlayerState01(PlayerBase* p);
    virtual ~PlayerState01();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
};

// Id 0x07, crouching down. Animation 0x14.
class PlayerState07 : public PlayerState {
public:
    explicit PlayerState07(PlayerBase* p);
    virtual ~PlayerState07();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
};

// Id 0x08, crouching. Animation 0x15 unless m_i24C names one.
class PlayerState08 : public PlayerState {
public:
    explicit PlayerState08(PlayerBase* p);
    virtual ~PlayerState08();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
};

// Id 0x09, standing up, a standing state with its own
// animation (0x16).
class PlayerState09 : public PlayerState01 {
public:
    explicit PlayerState09(PlayerBase* p);
    virtual ~PlayerState09();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x35: animation 0x49, queues event 0x17 after 0.1 s.
class PlayerState35 : public PlayerState {
public:
    explicit PlayerState35(PlayerBase* p);
    virtual ~PlayerState35();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();

    bool m_sent;                                // +0x14
};

// Id 0x1E, petrified (status flag 2): mash buttons to break free
// Animation 0x41.
class PlayerState1E : public PlayerState {
public:
    explicit PlayerState1E(PlayerBase* p);
    virtual ~PlayerState1E();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    bool step();                                // true once free

    unsigned int m_presses;                     // +0x14
    float m_shake;                              // +0x18
    float m_stun;                               // +0x1C
    unsigned int m_prevMask;                    // +0x20
    int m_eventArg;                             // +0x24 0x40, passed by address
};

// Id 0x05, turning around. Animation 0x11.
class PlayerState05 : public PlayerState {
public:
    explicit PlayerState05(PlayerBase* p);
    virtual ~PlayerState05();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
};

// Id 0x22, grabbed. Animation 0xEC; any new button press
// escapes.
class PlayerState22 : public PlayerState {
public:
    explicit PlayerState22(PlayerBase* p);
    virtual ~PlayerState22();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    unsigned int m_prevMask;                    // +0x14
};

// Id 0x23: waits for m_i2B0 to say 0x24 or back to 1.
class PlayerState23 : public PlayerState {
public:
    explicit PlayerState23(PlayerBase* p);
    virtual ~PlayerState23();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
};

// Id 0x24, thrown by an enemy grab: pulled to the
// grabber over 0.3 s, held 0.5 s, then released.
class PlayerState24 : public PlayerState {
public:
    explicit PlayerState24(PlayerBase* p);
    virtual ~PlayerState24();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    void setThrownAnim();

    int m_phase;                                // +0x14
    float m_targetX;                            // +0x18
    float m_targetY;                            // +0x1C
    float m_startX;                             // +0x20
    float m_startY;                             // +0x24
    int m_kind;                                 // +0x28
    int m_facing;                               // +0x2C
    float m_pullTime;                           // +0x30
    float m_holdTime;                           // +0x34
};

// Base of the walking states 0x02-0x04, 0x15.
class PlayerWalkState : public PlayerState {
public:
    explicit PlayerWalkState(PlayerBase* p);
    virtual ~PlayerWalkState();
    virtual void enter() = 0;
    virtual void update() = 0;
    virtual void interrupt() = 0;
    virtual bool canInterrupt();
    bool tryAttack();
    bool isPushingForward();
};

// Id 0x02, walking. Animation 9.
class PlayerState02 : public PlayerWalkState {
public:
    explicit PlayerState02(PlayerBase* p);
    virtual ~PlayerState02();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x15, walking after an attack. Animation 0x0B.
class PlayerState15 : public PlayerState02 {
public:
    explicit PlayerState15(PlayerBase* p);
    virtual ~PlayerState15();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x03, starting to walk. Animation 0x0C.
class PlayerState03 : public PlayerWalkState {
public:
    explicit PlayerState03(PlayerBase* p);
    virtual ~PlayerState03();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
};

// Id 0x04, stopping. Animation 0x0D.
class PlayerState04 : public PlayerWalkState {
public:
    explicit PlayerState04(PlayerBase* p);
    virtual ~PlayerState04();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};
