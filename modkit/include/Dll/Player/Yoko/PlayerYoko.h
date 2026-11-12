// Dll/Player/Yoko/PlayerYoko.h - Yoko Belnades, the dllyoko module (vtable
// no members beyond PlayerBase). Names are
// inferred. Besides the library states she registers her own attacks
// (0x17-0x19) and slide (0x0A).
#pragma once

#include "Dll/Player/PlayerStates.h"

class PlayerYoko : public PlayerBase {
public:
    // implicit constructor (PlayerBase + vtable), see DllCreate
    virtual ~PlayerYoko();
    virtual void release();                     // +0x008
    virtual void init();                        // +0x00C
    virtual void update();                      // +0x014
    virtual void finalize();                    // +0x01C
    virtual int  vfunc244();                    // +0x244
    virtual int  vfunc248();                    // +0x248
    virtual int  vfunc24C();                    // +0x24C
    virtual bool vfunc250();                    // +0x250
    virtual bool vfunc254();                    // +0x254
    virtual bool vfunc260();                    // +0x260
    virtual void getModelScale(float* out);     // +0x264
    virtual const char* getOpdPath(bool* outFlag, int variant);  // +0x268
    virtual void getAnimTable(PlayerAnimEntry* out);   // +0x26C
    virtual int  getMenuId(int i);              // +0x270
    virtual void getHitBox(float* l, float* t, float* r, float* b, bool alt);  // +0x298
    virtual bool vfunc424(int action);          // +0x424
    virtual const char* getVoicePath(bool japanese);   // +0x450
    virtual int  getVoiceCount();               // +0x454
    virtual const char* getVoiceName(int id);   // +0x458
    virtual int  getComboAnim(int kind, int action);   // +0x464
    virtual const PlayerAnimEntry* getAnimEntry(int anim);   // +0x474
    virtual int  vfunc47C();                    // +0x47C

    void deleteState(unsigned int id);
    template <class T> void createState(int id);    // one instance per state class,
};

// --- Yoko's states ------------------------------------------------------------

// Id 0x17, standing attack: animation 0x49/0x4D on the
// ground; in the air 0xDE/0xDF/0xEF by action, with a hit event and voice.
class YokoState17 : public PlayerState17 {
public:
    explicit YokoState17(PlayerBase* p);
    virtual ~YokoState17();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x18, crouching attack: animation 0x4A/0x4E; in the
// air it hands over to the standing attack.
class YokoState18 : public PlayerState18 {
public:
    explicit YokoState18(PlayerBase* p);
    virtual ~YokoState18();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x19, air attack: animation 0x4B on the ground.
class YokoState19 : public PlayerState19 {
public:
    explicit YokoState19(PlayerBase* p);
    virtual ~YokoState19();
    virtual void enter();
    virtual void update();
    virtual void interrupt();
};

// Id 0x0A, slide. Animation 0x18/0x1B by stick lean.
class YokoState0A : public PlayerState0A {
public:
    explicit YokoState0A(PlayerYoko* yoko);
    virtual ~YokoState0A();
    virtual void enter();
    virtual void update();
    virtual void interrupt();

    PlayerYoko* m_yoko;                         // +0x20
    bool m_animStarted;                         // +0x24
};
