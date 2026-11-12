// Dll/Player/PlayerParam.h - the player's vital values, status effects and
// movement integrator, owned by PlayerBase at +0x58 (0x254 bytes, vtable
// dllsoma ). Class and member names are inferred from behaviour:
// HP dropping below 1 sets the life state, MP and hearts clamp to max + bonus,
// a single timed status effect ticks HP/MP, and position integrates velocity.
#pragma once

#include "Port/BadgeEffects.h"

#include "Dll/DllAllocator.h"

#include <vector>

struct PlayerVital {          // 12 bytes
    float hp;
    float mp;
    unsigned int hearts;
};

// Stat block summed over the active status effects (21 words).
struct PlayerBuffStats {
    PlayerVital vital;        // +0x00
    float attr[5];            // +0x0C
    float resist[13];         // +0x20
};

struct PlayerBuff {           // 0x70 bytes
    PlayerBuffStats stats;    // +0x00
    float hpTick;             // +0x54 HP added every interval
    float mpTick;             // +0x58 MP added every interval
    float unk5C;
    float interval;           // +0x60
    float tickTimer;          // +0x64
    float duration;           // +0x68
    float elapsed;            // +0x6C
};

// 0x37 words copied as one block; the multipliers read by
// getMoveSpeed/getScale190/getScale18C live at +0x1C..+0x28 (walking uses
// getMoveSpeed, PlayerState::walk).
struct PlayerEquipStats {
    float v[6];               // +0x00 (PlayerParam +0x168)
    bool  flag;               // +0x18
    float speed;              // +0x1C (+0x184)
    float speedBonus;         // +0x20 (+0x188)
    float v18C;               // +0x24 (+0x18C)
    float v190;               // +0x28 (+0x190)
    float rest[44];           // +0x2C
};

enum PlayerLifeState {
    PLAYER_ALIVE = 0,
    PLAYER_DEAD = 1,          // HP dropped below 1
    PLAYER_LIFE_2 = 2,        // set by setLifeState2, meaning unknown
};

class PlayerParam {
public:
    PlayerParam();
    virtual ~PlayerParam();
    virtual void reset();                        // +0x08
    virtual void vfunc0C();                      // +0x0C (empty)
    virtual void commitMove(float dt);           // +0x10 (dt unused)
    virtual void update(float dt, bool slow, bool regenExtra);   // +0x14
    virtual void clearPush(float dt);            // +0x18 (dt unused)

    // life state
    void revive();                               // (life state -> alive)
    void clearStatusFlags();
    bool isDown() const;
    void kill();
    void setLifeState2();
    bool isLifeState2() const;
    void restore();

    // vitals
    void addMp(float v);
    void addHp(float v);
    void setHp(float v);
    void setMp(float v);
    void setHearts(unsigned int v);
    void addHearts(int v);
    float getHp() const;
    float getMp() const;
    unsigned int getHearts() const;
    void setCurrent(const PlayerVital& v);
    void setMax(const PlayerVital& v);
    void setMaxBonus(const PlayerVital& v);
    PlayerVital* getMax();
    PlayerVital* getMaxBonus();

    float getMpRegen() const;
    float getHpRegen() const;
    float getMpRegenExtra() const;
    float getHpRegenExtra() const;
    void setHpRegen(float v);
    void setMpRegen(float v);
    void setHpRegenBonus(float v);
    void setMpRegenBonus(float v);
    void setHpRegenExtra(float v);
    void setMpRegenExtra(float v);
    float getHpRegenBase() const;
    float getMpRegenBase() const;
    float getHpRegenBonus() const;
    float getMpRegenBonus() const;

    // attributes (5) and resistances (13), base and bonus. One setter per
    // element,.. (see PlayerParam.cpp).
    void setAttr0(float v);  void setAttr1(float v);  void setAttr2(float v);
    void setAttr3(float v);  void setAttr4(float v);
    void setAttrBonus0(float v); void setAttrBonus1(float v); void setAttrBonus2(float v);
    void setAttrBonus3(float v); void setAttrBonus4(float v);
    // /.., 8 bytes each
    void setResist0(float v);
    void setResist1(float v);
    void setResist2(float v);
    void setResist3(float v);
    void setResist4(float v);
    void setResist5(float v);
    void setResist6(float v);
    void setResist7(float v);
    void setResist8(float v);
    void setResist9(float v);
    void setResist10(float v);
    void setResist11(float v);
    void setResist12(float v);
    void setResistBonus0(float v);
    void setResistBonus1(float v);
    void setResistBonus2(float v);
    void setResistBonus3(float v);
    void setResistBonus4(float v);
    void setResistBonus5(float v);
    void setResistBonus6(float v);
    void setResistBonus7(float v);
    void setResistBonus8(float v);
    void setResistBonus9(float v);
    void setResistBonus10(float v);
    void setResistBonus11(float v);
    void setResistBonus12(float v);
    void setAttrs(const float* v);
    void setAttrBonuses(const float* v);
    float* getAttrs();
    float* getAttrBonuses();
    void setResists(const float* v);
    void setResistBonuses(const float* v);
    float* getResists();
    float* getResistBonuses();
    void getBuffVital(PlayerVital* out) const;
    void getBuffAttrs(float* out) const;
    void getBuffResists(float* out) const;

    // status effects
    bool tickBuff(PlayerBuff* b, float dt);      // true once expired
    void addBuff(const PlayerBuff& b);           // (replaces the current one)
    void setStatusFlag(unsigned int bit, bool on);
    unsigned int getStatusFlags() const;
    bool hasStatusFlag(unsigned int bit) const;
    void setFlag138(bool v);
    bool getFlag138() const;

    // equipment-derived scales
    void setEquip(const PlayerEquipStats& e);
    PlayerEquipStats* getEquip();
    float getMoveSpeed() const;
    float getScale190() const;
    float getScale18C() const;
    void setScale(float s);
    float getScale() const;

    // movement
    void setPos(float x, float y);
    void getPos(float* x, float* y) const;
    float getPosX() const;
    float getPosY() const;
    float getPrevPosX() const;
    float getPrevPosY() const;
    void setVelY(float v);
    void setVelX(float v);
    void setVel(float x, float y);
    void setAccelY(float v);
    void setAccelX(float v);
    void setAccel(float x, float y);
    void setPushY(float v);
    void setPushX(float v);
    void setPush(float x, float y);
    void getVel(float* x, float* y) const;
    float getVelX() const;
    float getVelY() const;
    void getAccel(float* x, float* y) const;
    float getAccelX() const;
    float getAccelY() const;
    void getPush(float* x, float* y) const;

public:
    PlayerVital m_cur;              // +0x04
    PlayerVital m_max;              // +0x10
    PlayerVital m_maxBonus;         // +0x1C
    PlayerVital m_regen;            // +0x28 (hearts field unused)
    PlayerVital m_regenBonus;       // +0x34
    PlayerVital m_regenExtra;       // +0x40 (added when update(..., regenExtra))
    float m_attr[5];                // +0x4C
    float m_attrBonus[5];           // +0x60
    float m_resist[13];             // +0x74
    float m_resistBonus[13];        // +0xA8
    PlayerBuffStats m_buffTotal;    // +0xDC
    unsigned int m_statusFlags;     // +0x130
    int m_lifeState;                // +0x134 PlayerLifeState
    bool m_flag138;                 // +0x138
    float m_scale;                  // +0x13C
    float m_prevPos[2];             // +0x140
    float m_pos[2];                 // +0x148
    float m_vel[2];                 // +0x150
    float m_accel[2];               // +0x158
    float m_push[2];                // +0x160 one-frame displacement
    PlayerEquipStats m_equip;       // +0x168
    std::vector<PlayerBuff, DllAllocator<PlayerBuff> > m_buffs;   // +0x244
    BadgeEffects m_badge;           // native: equipped badge accessories (Port/BadgeEffects.h), set each frame by PlayerBase::update
};
