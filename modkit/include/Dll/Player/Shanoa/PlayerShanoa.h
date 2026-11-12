// Dll/Player/Shanoa/PlayerShanoa.h - Shanoa, the dllshanoa module (vtable
// no members beyond PlayerBase). Names are inferred;
// the voice names come from the module's own table (VX_SHA_*).
//
// Shanoa's states mostly wrap the library's default for their id and, after
// its update, start the glyph-union state 0x25 when the union button (8) is
// pressed close enough to the union target (PlayerShanoa::checkUnion). Her
// state classes keep no pointer back to the player.
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerShanoa : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerShanoa();
    virtual void release();                     // +0x008
    virtual void init();                        // +0x00C
    virtual void update();                      // +0x014
    virtual void finalize();                    // +0x01C
    virtual int  vfunc244();                    // +0x244
    virtual int  vfunc248();                    // +0x248
    virtual int  vfunc24C();                    // +0x24C
    virtual bool vfunc250();                    // +0x250
    virtual bool vfunc254();                    // +0x254
    virtual bool vfunc25C();                    // +0x25C
    virtual void getModelScale(float* out);     // +0x264
    virtual const char* getOpdPath(bool* outFlag, int variant);  // +0x268
    virtual void getAnimTable(PlayerAnimEntry* out);   // +0x26C
    virtual int  getMenuId(int i);              // +0x270
    virtual void getHitBox(float* l, float* t, float* r, float* b, bool alt);  // +0x298
    virtual int  vfunc420();                    // +0x420
    virtual bool vfunc424(int action);          // +0x424
    virtual bool vfunc430(unsigned int mask);   // +0x430
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual int  getComboAnim(int kind, int action);   // +0x464
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474

    void deleteState(int id);
    template <class T> void createState(int id);    // one instance per state class,
    float getUnionRange();
    bool checkUnion();
};

// --- Shanoa's states --------------------------------------------------------

// Id 0x17, standing attack.
class ShanoaState17 : public PlayerState17 {
public:
    explicit ShanoaState17(PlayerBase* p);
    virtual ~ShanoaState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x18, crouching attack.
class ShanoaState18 : public PlayerState18 {
public:
    explicit ShanoaState18(PlayerBase* p);
    virtual ~ShanoaState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x19, air attack.
class ShanoaState19 : public PlayerState19 {
public:
    explicit ShanoaState19(PlayerBase* p);
    virtual ~ShanoaState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Ids 0x1A-0x1D, hit reactions (vtables ).
class ShanoaState1A : public PlayerState1A {
public:
    explicit ShanoaState1A(PlayerBase* p);
    virtual ~ShanoaState1A();
    virtual void update();
};

class ShanoaState1B : public PlayerState1B {
public:
    explicit ShanoaState1B(PlayerBase* p);
    virtual ~ShanoaState1B();
    virtual void update();
};

class ShanoaState1C : public PlayerState1C {
public:
    explicit ShanoaState1C(PlayerBase* p);
    virtual ~ShanoaState1C();
    virtual void update();
};

class ShanoaState1D : public PlayerState1D {
public:
    explicit ShanoaState1D(PlayerBase* p);
    virtual ~ShanoaState1D();
    virtual void update();
};

// Id 0x06, back dash.
class ShanoaState06 : public PlayerState06 {
public:
    explicit ShanoaState06(PlayerBase* p);
    virtual ~ShanoaState06();
    virtual void enter();
    virtual void update();
};

// Id 0x0A, slide.
class ShanoaState0A : public PlayerState0A {
public:
    explicit ShanoaState0A(PlayerBase* p);
    virtual ~ShanoaState0A();
    virtual void enter();
    virtual void update();
};

// Ids 0x0F/0x10, falling (vtables ).
class ShanoaState0F : public PlayerState0F {
public:
    explicit ShanoaState0F(PlayerBase* p);
    virtual ~ShanoaState0F();
    virtual void update();
};

class ShanoaState10 : public PlayerState10 {
public:
    explicit ShanoaState10(PlayerBase* p);
    virtual ~ShanoaState10();
    virtual void update();
};

// Ids 0x0B-0x0E, jumps (vtables ).
class ShanoaState0B : public PlayerState0B {
public:
    explicit ShanoaState0B(PlayerBase* p);
    virtual ~ShanoaState0B();
    virtual void update();
};

class ShanoaState0D : public PlayerState0D {
public:
    explicit ShanoaState0D(PlayerBase* p);
    virtual ~ShanoaState0D();
    virtual void update();
};

class ShanoaState0C : public PlayerState0C {
public:
    explicit ShanoaState0C(PlayerBase* p);
    virtual ~ShanoaState0C();
    virtual void update();
};

class ShanoaState0E : public PlayerState0E {
public:
    explicit ShanoaState0E(PlayerBase* p);
    virtual ~ShanoaState0E();
    virtual void update();
};

// Id 0x16, dive kick.
class ShanoaState16 : public PlayerState16 {
public:
    explicit ShanoaState16(PlayerBase* p);
    virtual ~ShanoaState16();
    virtual void update();
};

// Ids 0x11-0x14, landings (vtables ).
class ShanoaState11 : public PlayerState11 {
public:
    explicit ShanoaState11(PlayerBase* p);
    virtual ~ShanoaState11();
    virtual void update();
};

class ShanoaState12 : public PlayerState12 {
public:
    explicit ShanoaState12(PlayerBase* p);
    virtual ~ShanoaState12();
    virtual void update();
};

class ShanoaState13 : public PlayerState13 {
public:
    explicit ShanoaState13(PlayerBase* p);
    virtual ~ShanoaState13();
    virtual void update();
};

class ShanoaState14 : public PlayerState14 {
public:
    explicit ShanoaState14(PlayerBase* p);
    virtual ~ShanoaState14();
    virtual void update();
};

// Id 0x25, glyph union: pulled toward the union target (PlayerBase slot
// +0x43C) while button 8 is held, steered by stick 1 or the d-pad; releasing
// it launches the player at the target and goes to state 0x26
// Animation 0xFA.
class ShanoaState25 : public PlayerState {
public:
    explicit ShanoaState25(PlayerBase* p);
    virtual ~ShanoaState25();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();

    float m_steerX;                             // +0x14
    float m_steerY;                             // +0x18
};

// Id 0x26, flying out of a union: the air attack keeps
// running, one jump (animation 0x20) is allowed, the stick steers.
class ShanoaState26 : public PlayerState {
public:
    explicit ShanoaState26(PlayerBase* p);
    virtual ~ShanoaState26();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
    virtual bool canInterrupt();
    void restoreB256();
    void endFlight();
    void land();

    int m_phase;                                // +0x14 1 while flying
    float m_time;                               // +0x18
    bool m_jumped;                              // +0x1C
    bool m_steering;                            // +0x1D
};

// Id 0x21, looking up: animation 7 once interrupted.
class ShanoaState21 : public PlayerState21 {
public:
    explicit ShanoaState21(PlayerBase* p);
    virtual ~ShanoaState21();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    bool m_animSet;                             // +0x19
};

// Ids 0x07-0x09, crouching (vtables ).
class ShanoaState07 : public PlayerState07 {
public:
    explicit ShanoaState07(PlayerBase* p);
    virtual ~ShanoaState07();
    virtual void update();
};

class ShanoaState08 : public PlayerState08 {
public:
    explicit ShanoaState08(PlayerBase* p);
    virtual ~ShanoaState08();
    virtual void update();
};

class ShanoaState09 : public PlayerState09 {
public:
    explicit ShanoaState09(PlayerBase* p);
    virtual ~ShanoaState09();
    virtual void update();
};

// Id 0x01, standing.
class ShanoaState01 : public PlayerState01 {
public:
    explicit ShanoaState01(PlayerBase* p);
    virtual ~ShanoaState01();
    virtual void update();
};

// Ids 0x05, 0x02-0x04, 0x15: turning and walking (vtables ).
class ShanoaState05 : public PlayerState05 {
public:
    explicit ShanoaState05(PlayerBase* p);
    virtual ~ShanoaState05();
    virtual void update();
};

class ShanoaState02 : public PlayerState02 {
public:
    explicit ShanoaState02(PlayerBase* p);
    virtual ~ShanoaState02();
    virtual void update();
};

class ShanoaState03 : public PlayerState03 {
public:
    explicit ShanoaState03(PlayerBase* p);
    virtual ~ShanoaState03();
    virtual void update();
};

class ShanoaState04 : public PlayerState04 {
public:
    explicit ShanoaState04(PlayerBase* p);
    virtual ~ShanoaState04();
    virtual void update();
};

class ShanoaState15 : public PlayerState15 {
public:
    explicit ShanoaState15(PlayerBase* p);
    virtual ~ShanoaState15();
    virtual void update();
};
