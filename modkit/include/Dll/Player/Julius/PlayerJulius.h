// Dll/Player/Julius/PlayerJulius.h - Julius Belmont, the dlljulius module
// (vtable: PlayerBase plus one flag). Names are
// inferred; the voice names come from the module's own table (VX_JUL_*).
//
// Julius registers the library's default state for most ids; his own are the
// three attacks (0x17-0x19, which can chain into the whip hold 0x27), the
// slide 0x0A, the two command specials 0x25/0x26 and the whip swing
// 0x28 -> 0x29.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerJulius : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerJulius();
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
    virtual const char* getOpdPath(bool* outFlag, int variant);   // +0x268
    virtual void getAnimTable(PlayerAnimEntry* out);   // +0x26C
    virtual int  getMenuId(int i);              // +0x270
    virtual void getHitBox(float* l, float* t, float* r, float* b, bool alt);  // +0x298
    virtual void getFacingDir(float* dir, int* out2);  // +0x3E8
    virtual int  vfunc41C(int a, int action);   // +0x41C
    virtual bool vfunc430(unsigned int mask);   // +0x430
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474
    virtual int  getAnimGroupBase(int anim);    // +0x478
    virtual int  vfunc480();                    // +0x480

    void deleteState(unsigned int id);
    template <class T> void createState(int id);    // one instance per state class,
    void setWhipHold(bool v);
    bool getWhipHold();

    bool m_whipHold;                            // +0x348 attack ends in the whip hold (0x27)
};

// --- Julius's states --------------------------------------------------------

// Id 0x17, standing attack. Up-aimed whip animations
// 0xBB/0xC1/0xC2 by stick direction.
class JuliusState17 : public PlayerState17 {
public:
    explicit JuliusState17(PlayerBase* p);
    virtual ~JuliusState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x18, crouching attack. Animation 0xBC / 0xC0.
class JuliusState18 : public PlayerState18 {
public:
    explicit JuliusState18(PlayerBase* p);
    virtual ~JuliusState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x19, air attack.
class JuliusState19 : public PlayerState19 {
public:
    explicit JuliusState19(PlayerBase* p);
    virtual ~JuliusState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x27, holding the whip out after an attack while button 5 is held
// queues event 10 with m_event.
class JuliusState27 : public PlayerState {
public:
    explicit JuliusState27(PlayerBase* p);
    virtual ~JuliusState27();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    int m_returnAnim;                           // +0x14 passed to state 1 / 8
    int m_eventAction;                          // +0x18 event 10 argument block
    int m_eventKind;                            // +0x1C 0x10
    float m_eventF20;                           // +0x20
    float m_eventF24;                           // +0x24
    float m_eventF28;                           // +0x28
    float m_eventF2C;                           // +0x2C 4
    unsigned int m_prevMask;                    // +0x30
};

// Id 0x0A, slide. Animation 0x18/0x1B by stick lean.
class JuliusState0A : public PlayerState0A {
public:
    explicit JuliusState0A(PlayerJulius* julius);
    virtual ~JuliusState0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerJulius* m_julius;                     // +0x20
    bool m_animStarted;                         // +0x24
};

// Id 0x25, command special 0: a backward hop that turns
// around at 0.2 s. Animation 0x28.
class JuliusState25 : public PlayerState {
public:
    explicit JuliusState25(PlayerBase* p);
    virtual ~JuliusState25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    virtual bool canInterrupt();
    void finish();

    int m_phase;                                // +0x14
};

// Id 0x26, command special 1: a rising jump.
// Animation 0x21.
class JuliusState26 : public PlayerState {
public:
    explicit JuliusState26(PlayerBase* p);
    virtual ~JuliusState26();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)
    void finish();
};

// Id 0x28, swinging from a whip point: a pendulum
// around the point PlayerBase::getWarpB names, released into 0x29 by
// button 8. Animation 0x102-0x104; event 0xD with m_event*.
class JuliusState28 : public PlayerState {
public:
    explicit JuliusState28(PlayerBase* p);
    virtual ~JuliusState28();
    virtual void enter();
    virtual void update();
    virtual void interrupt();                   // (empty)

    unsigned char _pad14[0x8];                  // +0x14 not used
    float m_x;                                  // +0x1C last position set
    float m_y;                                  // +0x20
    float m_height;                             // +0x24 -hit box top
    float m_anchorX;                            // +0x28
    float m_anchorY;                            // +0x2C
    float m_angle;                              // +0x30 0 = straight down
    float m_angVel;                             // +0x34
    float m_radius;                             // +0x38 10-30
    int m_eventKind;                            // +0x3C 10, event 0xD argument block
    float m_eventRadius;                        // +0x40
    float m_eventAngle;                         // +0x44
    float m_eventAnchorX;                       // +0x48
    float m_eventAnchorY;                       // +0x4C
    float m_eventX;                             // +0x50
    float m_eventY;                             // +0x54
};

// Id 0x29, flying off the whip swing: the air attack
// (state 0x19) runs inside it; button 4 jumps once.
class JuliusState29 : public PlayerState {
public:
    explicit JuliusState29(PlayerBase* p);
    virtual ~JuliusState29();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
    void restoreB256();
    void toFall();
    void land();

    float m_time;                               // +0x14
    bool m_jumped;                              // +0x18
    bool m_steered;                             // +0x19
};

// Dinkumware atan2f and its kernel as linked into dlljulius (SDK runtime,
// used by the whip swing; dllsoma does not link them).
struct JuliusMath {
    static float atan2f(float y, float x);
    static float atan(float x, unsigned int idx);   // (_FAtan)
};
