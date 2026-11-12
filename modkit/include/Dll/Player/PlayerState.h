// Dll/Player/PlayerState.h - player state objects. PlayerBase owns one per
// state id (m_states[1..53]); the running one gets enter() once and update()
// every frame. Names are inferred; accessor names follow the PlayerBase
// member they reach (PlayerBase.h).
#pragma once

#include "Dll/Player/PlayerBase.h"

class PlayerInput;

// Root (vtable dllsoma ).
class PlayerState {
public:
    explicit PlayerState(PlayerBase* player);
    virtual ~PlayerState();
    virtual void enter() = 0;                   // +0x08
    virtual void update() = 0;                  // +0x0C
    virtual void interrupt() = 0;               // +0x10 also PlayerBase::stateEvent
    virtual bool canInterrupt();                // +0x14
    virtual void leave();                       // +0x18

    // transitions and helpers
    void requestState(int id, int arg, bool onlyIfNone);
    int  getI2B4() const;
    bool checkDownOrHit();
    void stopIfMovingAway(bool forward);
    void setFacing(int v);
    int  getI260() const;
    int  getI048() const;
    int  getI044() const;
    int  getI134() const;
    void walk(bool turn);
    void stop();
    int  getI03C() const;
    bool tryLand();
    float getDeltaTime() const;
    bool fall();
    bool getB038() const;
    bool getB254() const;
    void setGroundSpeed();
    float getStateTime() const;
    bool isTimeUp() const;
    void clearTimeLimit();
    void setTimeLimit(float t);
    int  getVfunc248();
    int  getI22C() const;
    unsigned int random() const;
    PlayerState* getState(int id) const;
    int  getI25C() const;
    void resetI25C();
    void setI260(int v);
    int  getAction() const;
    int  getI13C() const;
    int  getWeapon() const;
    unsigned int getWeaponFlags() const;
    void setI264Flag(bool v);
    void setI264(int v);
    void setI264To3();
    int  getI264() const;
    bool isBusy();
    void setF268(float a, float b);
    void setI278(int v);
    void getF270Both(float* a, float* b) const;
    float getF270() const;
    float getF274() const;
    void setF270(float a, float b);
    int  getI280() const;
    void setB27D(bool v);
    void changeState(int id);
    void setStateId(int id);
    int  getStateId() const;
    int  getPrevStateId() const;
    int  getNextStateId() const;
    bool takeB257();
    void countU258();
    void setI248(int v, bool b007, bool b008, float f00C, float f010);
    void setF024(float v);
    void setF00C(float v);
    void setF028(float v);
    void setF1F0(float v);
    void setF1F4(float v);
    int  getI248();
    int  getI24C();
    bool getB004() const;
    int  getI01C() const;
    void setB005(bool v);
    int  getI020() const;
    void setB018(bool v);
    void setB02C(bool v);
    void setB02D(bool v);
    void setF030(float a, float b);
    bool isKind2or7or8(int kind) const;
    unsigned int getFlags04C() const;
    void setFlags04C(unsigned int v);
    void addFlags04C(unsigned int bits);
    void clearFlags04C(unsigned int bits);
    bool getSlow() const;
    float getF050() const;
    void latchI308();
    void clearI30C();
    bool hasI30C() const;
    bool isI30CCurrent() const;
    int  getI310() const;
    void setI134(int v);
    bool isI134Is2or3() const;
    bool isFacing(int dir) const;
    int  getFacing() const;
    void setB256(bool v);
    bool getB256() const;
    void setI2B4(int v);
    void setF2BC(float v);
    float getF2C4() const;
    void launch();
    float getEquipSpeedScale();
    float getF2C8() const;
    void pushEvent(int a, bool b, const int* c, int d);
    void pushEventFlag2();
    void pushEventDefault();
    void pushEvent2(int a0, int a1, int a2, int a3, int a4, float f, int a6, int a7, int a8,
                    int a9);
    float getF1E4() const;
    void clearF1E4();
    void setF1E8(float v);
    void setF1EC(float v);
    void setB28C(bool v);
    bool getB28C() const;
    bool getB290() const;
    int  getI2A4() const;
    int  getI29C() const;
    int  getI2A8() const;
    void getHitParams(int* i29C, float* f2A0, float* f294, float* f298, int* i2A4,
                      float* f2AC) const;
    int  getI2B0() const;
    int  getI2F4() const;
    int  getI2F8() const;
    int  getI2FC() const;
    int  getI300() const;
    void setB2EC(bool v);
    int  getI2F0() const;
    bool tryState0B();
    bool tryState07();
    bool tryTurn();
    bool tryWalk();
    bool tryState16();
    bool tryState0C();
    bool tryState06();
    void pushList(int v);
    void pushWeaponList(bool alt);
    bool tryComboAttack();
    void finishAttack(int id);
    bool tryState21();
    bool tryJump();
    bool tryState35();
    bool tryLandFromKind();
    bool trySkill(int id, bool needB254, bool needF304);
    bool canRunCommand();
    bool tryCommand();
    bool tryHitState();
    bool tryState23();
    bool checkI03C();
    int  getCommandA() const;
    int  getCommandB() const;
    int  getCommandC() const;
    int  getCommandD() const;
    int  callHost340(int a, int b);
    void playVoice(int v);
    void playVoiceChance(int v);
    int  getComboAnim(int kind, int action);

    PlayerBase* m_player;                       // +0x04
    PlayerParam* m_param;                       // +0x08
    PlayerInput* m_input;                       // +0x0C
    float m_timeLimit;                          // +0x10
};

// Action state base (vtable ): adds a phase counter and
// a pending move used by most ground/air states.
class PlayerActionState : public PlayerState {
public:
    explicit PlayerActionState(PlayerBase* player);
    virtual ~PlayerActionState();
    virtual void enter();                       // +0x08
    virtual void update();                      // +0x0C
    virtual void interrupt();                   // +0x10
    virtual bool canInterrupt();                // +0x14
    virtual void leave();                       // +0x18
    virtual void setup(int i248, int i1C);      // +0x1C

    void setB20(bool v);
    bool getB20() const;
    int  getI1C() const;
    void setI1C(int v);
    int  getPhase() const;
    void setPhase(int v);

    int m_phase;                                // +0x14
    int m_i18;                                  // +0x18
    int m_i1C;                                  // +0x1C
    bool m_b20;                                 // +0x20
    float m_moveX;                              // +0x24
    float m_moveY;                              // +0x28
};
