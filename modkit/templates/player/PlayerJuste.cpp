// Dll/ModPlayer/Juste/PlayerJuste.cpp - Juste Belmont player module (dlljuste),
// the module's own translation unit plus its inline
// functions the linker placed later (state factories,
// destructors ). Path and names inferred; the structure
// follows the Soma module (Soma/PlayerSoma.cpp).
//
// Status: decompiled.

#include "PlayerJuste.h"
#include "JusteData.h"
#include "Dll/DllMain.h"

// Reached only through its descriptor,
// which nothing in the module reads; the module's only other plain function.
extern "C" int dllJusteQuery()
{
    return 1;
}

// DllCreate, DllGetFactory,
// PlayerJuste::release.
DLL_IMPLEMENT_FACTORY(PlayerJuste)

PlayerJuste::~PlayerJuste()
{
}

void PlayerJuste::deleteState(unsigned int id)
{
    if (id < STATE_COUNT) {
        PlayerState*& s = m_states[id];
        if (s) {
            delete s;
            s = 0;
        }
    }
}

// One instance per state class ( each).
template <class T>
void PlayerJuste::createState(int id)
{
    if (id >= 0 && id < STATE_COUNT) {
        if (id >= 0 && id < STATE_COUNT && m_states[id]) {
            delete m_states[id];
            m_states[id] = 0;
        }
        m_states[id] = DLL_NEW T(this);
    }
}

// (+0x00C).
void PlayerJuste::init()
{
    PlayerBase::init();
    createState<PlayerState01>(1);
    createState<PlayerState05>(5);
    createState<PlayerState02>(2);
    createState<PlayerState03>(3);
    createState<PlayerState04>(4);
    createState<PlayerState07>(7);
    createState<PlayerState08>(8);
    createState<PlayerState09>(9);
    createState<PlayerState0F>(0xF);
    createState<PlayerState10>(0x10);
    createState<PlayerState11>(0x11);
    createState<PlayerState12>(0x12);
    createState<PlayerState13>(0x13);
    createState<PlayerState14>(0x14);
    createState<PlayerState15>(0x15);
    createState<PlayerState06>(6);
    createState<PlayerState0B>(0xB);
    createState<PlayerState0D>(0xD);
    createState<PlayerState0C>(0xC);
    createState<PlayerState0E>(0xE);
    createState<PlayerState16>(0x16);
    createState<PlayerState0A>(0xA);
    createState<PlayerState1A>(0x1A);
    createState<PlayerState1B>(0x1B);
    createState<PlayerState1C>(0x1C);
    createState<PlayerState1D>(0x1D);
    createState<PlayerState1E>(0x1E);
    createState<PlayerState1F>(0x1F);
    createState<PlayerState20>(0x20);
    createState<PlayerState21>(0x21);
    createState<PlayerState22>(0x22);
    createState<PlayerState23>(0x23);
    createState<PlayerState24>(0x24);
    createState<JusteState17>(0x17);
    createState<JusteState18>(0x18);
    createState<JusteState19>(0x19);
    createState<PlayerState35>(0x35);
    createState<JusteState25>(0x25);
    m_param->setScale(90.0f);
    setF2C4(580.0f);
    m_param->setMpRegen(1.0f);
    addFlags210(1);
    m_commandCount = 1;
    m_commandMode = 9;
    m_commandArgs = 0;
    m_commands = g_justeCommands;
    m_commandStates = g_justeCommandAnims;
}

// (+0x014).
void PlayerJuste::update()
{
    PlayerBase::update();
}

// (+0x01C).
void PlayerJuste::finalize()
{
    PlayerBase::finalize();
    for (int i = 0; i < STATE_COUNT; i++) {
        deleteState(i);
    }
}

int PlayerJuste::vfunc244() { return 22; }
int PlayerJuste::vfunc248() { return 22; }
int PlayerJuste::vfunc24C() { return 0; }
bool PlayerJuste::vfunc250() { return false; }
bool PlayerJuste::vfunc254() { return true; }
int PlayerJuste::vfunc3B4() { return 3; }

// (+0x268).
const char* PlayerJuste::getOpdPath(bool* outFlag, int)
{
    *outFlag = vfunc254();
    return g_justeOpdPath;
}

// (+0x264).
void PlayerJuste::getModelScale(float* out)
{
    *out = 1.0f;
}

// (+0x26C).
void PlayerJuste::getAnimTable(PlayerAnimEntry* out)
{
    for (int i = 0; i < JUSTE_ANIM_COUNT; i++) {
        out[i] = g_justeAnimTable[i];
    }
}

// (+0x474).
const PlayerAnimEntry* PlayerJuste::getAnimEntry(int anim)
{
    return &g_justeAnimTable[anim];
}

// (+0x270).
int PlayerJuste::getMenuId(int i)
{
    if (i == 0) {
        return 0xF;
    }
    if (i == 1) {
        return 7;
    }
    return 0;
}

// (+0x298). Shorter while crouching.
void PlayerJuste::getHitBox(float* l, float* t, float* r, float* b, bool alt)
{
    float top;
    if (m_i134 == 1 && !alt) {
        top = -16.0f;
    } else {
        top = -30.0f;
    }
    *l = -4.0f;
    *t = top;
    *r = 4.0f;
    *b = -1.0f;
}

// (+0x184).
bool PlayerJuste::isSpecialWeapon(int weapon)
{
    return weapon == 0x19;
}

// (+0x41C).
int PlayerJuste::vfunc41C(int, int action)
{
    if (action != 0x11) {
        return false;
    }
    return m_i134 == 1;
}

// (+0x450).
const char* PlayerJuste::getVoicePath(bool japanese)
{
    if (!japanese) {
        return g_justeVoicePath;
    }
    return g_justeVoicePathJp;
}

int PlayerJuste::getVoiceCount() { return 0; }

// (+0x458).
const char* PlayerJuste::getVoiceName(int id)
{
    if (id < 0 || id >= JUSTE_VOICE_COUNT) {
        return 0;
    }
    return g_justeVoiceNames[id];
}

DLL_IMPLEMENT_MODULE_START()

// ===========================================================================
// 0x17 standing attack
// ===========================================================================

JusteState17::JusteState17(PlayerBase* p) : PlayerState17(p) {}

JusteState17::~JusteState17() {}

// Standing: animation 0xBB; in the air (postures
// 2-5): 0xEF and an immediate hit event.
void JusteState17::enter()
{
    if (m_player == 0) {
        return;
    }
    PlayerState17::enter();
    if (getI260() == 6) {
        return;
    }
    int anim = 0;
    int post = getI260();
    if (post < 2) {
        if (post == 0) {
            anim = 0xBB;
        }
    } else if (post < 6) {
        anim = 0xEF;
        pushEvent2(getAction(), 2, 0, 0, 0, 0.0f, 0, 0, 0, 6);
    }
    setup(anim, 0);
    m_moveY = 0;
}

void JusteState17::update()
{
    if (m_player == 0) {
        return;
    }
    m_moveY = 0;
    PlayerState17::update();
    if (getNextStateId() == 0) {
        getI22C();   // result unused
    }
}

void JusteState17::interrupt()
{
    PlayerState17::interrupt();
}

// ===========================================================================
// 0x18 crouching attack
// ===========================================================================

JusteState18::JusteState18(PlayerBase* p) : PlayerState18(p) {}

JusteState18::~JusteState18() {}

// In the air it hands over to the standing attack.
void JusteState18::enter()
{
    if (m_player == 0) {
        return;
    }
    PlayerState18::enter();
    if (getI260() == 6) {
        return;
    }
    int anim = 0;
    int post = getI260();
    if (post < 2) {
        if (post == 0) {
            anim = 0xBC;
            m_moveY = 0;
        }
    } else if (post < 6) {
        changeState(0x17);
        getState(0x17)->enter();
        m_moveY = 0;
        return;
    }
    setup(anim, 0);
}

void JusteState18::update()
{
    if (m_player == 0) {
        return;
    }
    PlayerState18::update();
    if (getNextStateId() == 0) {
        getI22C();   // result unused
    }
}

void JusteState18::interrupt()
{
    PlayerState18::interrupt();
}

// ===========================================================================
// 0x19 air attack
// ===========================================================================

JusteState19::JusteState19(PlayerBase* p) : PlayerState19(p) {}

JusteState19::~JusteState19() {}

void JusteState19::enter()
{
    if (m_player == 0) {
        return;
    }
    PlayerState19::enter();
    int anim = 0;
    int post = getI260();
    if (post < 2) {
        if (post == 0) {
            anim = 0xBD;
        }
    } else if (post < 6) {
        anim = 0xF0;
        pushEvent2(getAction(), 2, 0, 0, 0, 0.0f, 0, 0, 0, 6);
    }
    setup(anim, 0);
    m_moveY = 0;
}

void JusteState19::update()
{
    if (m_player == 0) {
        return;
    }
    PlayerState19::update();
    if (getNextStateId() == 0) {
        getI22C();   // result unused
    }
}

void JusteState19::interrupt()
{
    PlayerState19::interrupt();
}

// ===========================================================================
// 0x25 command special
// ===========================================================================

JusteState25::JusteState25(PlayerBase* p) : PlayerState(p) {}

JusteState25::~JusteState25() {}

void JusteState25::enter()
{
    if (m_player == 0) {
        return;
    }
    setI134(0);
    stop();
    m_phase = 2;
    m_hitSent = false;
    if (getCommandA() == 0x19) {
        setI248(0xBB, true, true, 1.0f, 0.0f);
        m_player->setI284(getCommandD(), 0);
        setF268(0.0f, 0.0f);
        setI264Flag(false);
        m_phase = 0;
    }
}

// Phases 0 and 1 step the posture flag; in phase 2
// the hit event goes out once 0.18 s into the state.
void JusteState25::update()
{
    if (m_player == 0) {
        return;
    }
    if (checkDownOrHit() || tryLand()) {
        stop();
        leave();
        return;
    }
    int ph = m_phase;
    if (ph < 1) {
        if (ph >= 0) {
            setI264(1);
            m_phase = 1;
        }
        return;
    }
    if (ph < 2) {
        setI264(2);
        m_phase = 2;
    } else if (ph > 2) {
        return;
    }
    if (!m_hitSent && 0.18351686f <= getStateTime()) {
        m_hitSent = true;
        int kind = getCommandA();
        int arg = getI2F0();
        int target = getCommandD();
        pushEvent2(kind, 9, 0, arg, 0, 0.0f, 0, 0, 0, target);
    }
}

void JusteState25::interrupt()
{
    leave();
    setI264Flag(false);
    stop();
    requestState(1, 0, true);
}
