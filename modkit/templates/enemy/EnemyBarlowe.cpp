// Dll/ModEnemy/Barlowe/EnemyBarlowe.cpp - dllfusimon, the whip-swinging
// skeleton Simon (path and names inferred). Module code.
//
// Status: decompiled. Not here: the iostream static initialiser / terminator
// pair /, the enemy library copy and everything after
// it that is not listed in the library sources (Dinkumware locale, string and
// exception code, SDK), and the three 8-byte "return 1" stubs at the end of
// the image (Dinkumware facet virtuals).

#include "EnemyBarlowe.h"

#include <math.h>
#include <string.h>

typedef IEnemyObj* (*EnemyFactoryFunc)(DllAllocFunc alloc, DllFreeFunc free);

static inline int fbits(float f)
{
    int i;
    memcpy(&i, &f, 4);
    return i;
}

// Called by moduleUnload when the module is unloaded; nothing to clean up.
extern "C" int cvhdModuleShutdown()
{
    return 1;
}

// Saves the heap hooks and creates the object (the
// constructor is inlined).
extern "C" IEnemyObj* DllCreate(DllAllocFunc alloc, DllFreeFunc free)
{
    g_dllAlloc = alloc;
    g_dllFree = free;
    return DLL_NEW EnemyBarlowe;
}

extern "C" EnemyFactoryFunc DllGetFactory()
{
    return DllCreate;
}

// Module entry: hands the factory to the loader.
extern "C" int cvhdModuleInit(unsigned int, void* argp)
{
    *(EnemyFactoryFunc*)argp = DllGetFactory();
    return 0;
}

EnemyBarlowe::EnemyBarlowe()
{
    m_state = 0;
    m_timer = 0;
    m_facing = 0;
    m_stateInit = false;
    m_dead = false;
    m_b44CE = false;
    m_wake = false;
    m_hit = false;
    m_lostTimer = 0;
    m_attackWait = 0;
    m_name = "DLL_barlowe";
}

EnemyBarlowe::~EnemyBarlowe()
{
}

void EnemyBarlowe::release() { delete this; }

void EnemyBarlowe::startMotion0()
{
    m_motionChanged = true;
    setMotion(0, true);
}

void EnemyBarlowe::faceDir()
{
    m_b268 = true;
    m_f238[1] = 4.0f;
    m_f238[0] = m_facing * 10.0f;
}

void EnemyBarlowe::setBoxes26A()
{
    m_b26A = true;
    m_f248[0] = -10.0f;
    m_f248[1] = -14.0f;
    m_b26B = true;
    m_f250[0] = 10.0f;
    m_f250[1] = -14.0f;
}

void EnemyBarlowe::init()
{
    addHitBox0(0, true, 0);
    m_hitBoxes0[0].b2A = true;
    m_hitBoxes0[0].b66 = true;
    m_s222 = 0;
    setB229(true);
    m_b26A = true;
    m_b26B = true;
    m_f248[0] = -10.0f;
    m_f248[1] = -14.0f;
    m_f250[1] = -14.0f;
    m_b268 = true;
    m_motionChanged = true;
    m_f250[0] = 10.0f;
    m_f238[1] = 4.0f;
    m_f238[0] = m_facing * 10.0f;
    setMotion(0, true);
    setFlagSet(4, 0);
    setFlagSet(0, 0);
}

// Turns the body hit box with the facing.
void EnemyBarlowe::setFacing(float f)
{
    float v;
    if (f < 0.0f) {
        m_hitBoxes0[0].i30 = 0;
        v = -1.0f;
    } else {
        m_hitBoxes0[0].i30 = 2;
        v = 1.0f;
    }
    m_facing = v;
    m_b268 = true;
    m_f238[1] = 4.0f;
    m_f238[0] = v * 10.0f;
}

void EnemyBarlowe::start()
{
    setFacing(m_f0BC[0]);
    EnemyHitBox* hb = &m_hitBoxes0[0];
    hb[0].s5C = m_s222;
    float ctx = (float)(long long)(m_hostContext & 0xFFFF);
    hb[0].f14 = fmaf(ctx * 0.001f, 2.0f, 10000.0f);
    const EnemyRect& rc = hb0Rects(0)->at(0);
    m_hasRect29C = true;
    m_rect29C[0] = (int)(rc.x0 - 5.0f);
    m_rect29C[1] = (int)rc.y0 + 1;
    m_rect29C[2] = (int)rc.x1;
    m_rect29C[3] = (int)rc.y1 + 1;
    m_hitBoxes0[0].b66 = false;
}

void EnemyBarlowe::v018() {}

void EnemyBarlowe::nop560() {}

void EnemyBarlowe::clearB268() { m_b268 = false; }

void EnemyBarlowe::clearB26AB()
{
    m_b26A = false;
    m_b26B = false;
}

// State 3: drops the hit boxes, asks for the death
// effect (list +0x17C) once, then reports dead.
void EnemyBarlowe::stateDie()
{
    if (!m_stateInit) {
        m_vel[0] = 0;
        m_vel[1] = 0;
        m_timer = 0;
        m_hitBoxes0[0].b29 = false;
        setB229(false);
        m_b26A = false;
        m_b26B = false;
        m_b268 = false;
        EnemyReq58 q;
        q.w[0] = 1;
        q.b04 = true;         // a bool at +0x04 (true)
        q.w[2] = fbits(m_selfPos[0]);
        q.w[3] = fbits(m_selfPos[1] + -8.0f);
        q.w[4] = 0;
        q.w[5] = -1;
        q.w[6] = 0;
        q.w[7] = 0;
        q.w[8] = 0;
        q.w[9] = 0;
        q.w[10] = 0;
        q.w[11] = fbits(25000.0f);
        q.w[12] = 5;
        q.w[13] = 5;
        q.w[14] = 1;
        q.b3C = false;                 // a bool at +0x3C (false)
        q.w[16] = 0;
        q.w[17] = fbits(1.0f);
        q.b48 = false;                 // a bool at +0x48 (false)
        q.w[19] = 0;
        q.w[20] = -1;
        q.b54 = false;
        push17C(q);
        m_stateInit = true;
    }
    m_dead = true;
}

void EnemyBarlowe::setState(int s)
{
    m_state = s;
    m_stateInit = false;
}

bool EnemyBarlowe::inRange()
{
    if (m_b221 != m_b220) {
        return false;
    }
    float dx = m_playerPos[0] - m_selfPos[0];
    float dy = m_playerPos[1] - m_selfPos[1];
    return fabsf(dx) < 128.0f && dy > -80.0f && dy < 80.0f;
}

// State 2: swings the whip; while the hit box's +0x08
// is 4 it asks for the whip's hit area (queue +0x18C). Back to state 1 when
// the swing ends, to state 0 after 5 s out of range.
void EnemyBarlowe::stateAttack(float dt)
{
    if (!m_stateInit) {
        EnemyHitBox& hb = m_hitBoxes0[0];
        hb.u00 = 1;
        hb.b2B = false;
        hb.b28 = false;
        hb.f54 = 0;
        hb.b1C = true;
        m_vel[0] = 0;
        m_timer = 0;
        m_stateInit = true;
        return;
    }
    if (m_b221 == m_b220 && fabsf(m_playerPos[0] - m_selfPos[0]) < 128.0f &&
        m_playerPos[1] - m_selfPos[1] > -80.0f && m_playerPos[1] - m_selfPos[1] < 80.0f) {
        m_lostTimer = 0;
    } else {
        float lt = m_lostTimer + dt;
        m_lostTimer = lt;
        if (lt > 5.0f) {
            m_state = 0;
            m_stateInit = false;
            return;
        }
    }
    if (m_hitBoxes0[0].u08 == 4) {
        float tx = m_selfPos[0];
        float ty = m_selfPos[1];
        float facing = m_facing;
        EnemyReq24 q;
        q.w[0] = fbits(fmaf(facing, 48.0f, tx));
        q.w[1] = fbits(ty + -22.0f);
        q.w[2] = fbits(fmaf(facing, 8.0f, tx));
        q.w[3] = fbits(ty + -16.0f);
        q.w[4] = fbits(-1.0f);
        q.w[5] = fbits(-1.0f);
        q.w[6] = 0x400000C1;
        q.w[7] = fbits(getF1F0());
        q.w[8] = fbits(getF1E0());
        pushQueue24(q);
    }
    if (m_hitBoxes0[0].b28) {
        m_state = 1;
        m_stateInit = false;
    }
}

// The player is in front and within whip reach.
bool EnemyBarlowe::inReach()
{
    float dx = m_playerPos[0] - m_selfPos[0];
    float dy = m_playerPos[1] - m_selfPos[1];
    return m_facing * dx > 0.0f && fabsf(dx) < 80.0f && dy > -80.0f && dy < 80.0f;
}

bool EnemyBarlowe::isI258Clear()
{
    return m_i258 == 0;
}

bool EnemyBarlowe::isWallAhead()
{
    int v;
    if (m_facing < 0.0f) {
        v = m_i260;
    } else {
        v = m_i264;
    }
    return v != 0;
}

// A wall ahead or no ground.
bool EnemyBarlowe::mustTurn()
{
    int wall = m_facing < 0.0f ? m_i260 : m_i264;
    if (wall != 0) {
        return true;
    }
    return m_i258 == 0;
}

void EnemyBarlowe::faceTarget()
{
    if (m_playerPos[0] - m_selfPos[0] < 0.0f) {
        setFacing(-1.0f);
    } else {
        setFacing(1.0f);
    }
}

bool EnemyBarlowe::targetBehind()
{
    return m_facing * (m_playerPos[0] - m_selfPos[0]) > 0.0f;
}

// State 1: walks (40, 64 with +0x230), turns towards
// the player every 0.5 s, attacks (state 2) when he is within reach and 0.8 s
// have passed since the last attack, gives up (state 0) after 5 s out of range.
void EnemyBarlowe::stateWalk(float dt)
{
    float speed = 40.0f;
    bool fast = getB230();
    float facing = m_facing;
    float timer = m_timer;
    if (fast) {
        speed = 64.0f;
    }
    if (!m_stateInit) {
        EnemyHitBox& hb = m_hitBoxes0[0];
        hb.u00 = 0;
        hb.b2B = true;
        hb.b28 = false;
        hb.f54 = 0;
        hb.b1C = true;
        timer = 0.0f;
        if (m_playerPos[0] - m_selfPos[0] < 0.0f) {
            setFacing(-1.0f);
        } else {
            setFacing(1.0f);
        }
        facing = m_facing;
        m_timer = 0;
        m_lostTimer = 0;
        m_stateInit = true;
        m_vel[0] = facing * speed;
    }
    if (m_b221 == m_b220 && fabsf(m_playerPos[0] - m_selfPos[0]) < 128.0f &&
        m_playerPos[1] - m_selfPos[1] > -80.0f && m_playerPos[1] - m_selfPos[1] < 80.0f) {
        m_lostTimer = 0;
    } else {
        float lt = m_lostTimer + dt;
        m_lostTimer = lt;
        if (lt > 5.0f) {
            m_state = 0;
            m_stateInit = false;
            return;
        }
    }
    m_vel[0] = facing * speed;
    float t = timer + dt;
    m_timer = t;
    if (t > 0.5f) {
        m_timer = t - 0.5f;
        float dx = m_playerPos[0] - m_selfPos[0];
        if (!(facing * dx > 0.0f)) {
            if (dx < 0.0f) {
                setFacing(-1.0f);
            } else {
                setFacing(1.0f);
            }
            m_vel[0] = 0;
        }
    }
    if (mustTurn()) {
        m_vel[0] = 0;
    }
    float wait = m_attackWait;
    if (wait < 0.8f) {
        m_attackWait = wait + dt;
        return;
    }
    float dx = m_playerPos[0] - m_selfPos[0];
    float dy = m_playerPos[1] - m_selfPos[1];
    if (m_facing * dx > 0.0f && fabsf(dx) < 80.0f && dy > -80.0f && dy < 80.0f) {
        m_attackWait = 0;
        m_vel[0] = 0;
        m_state = 2;
        m_stateInit = false;
    }
}

void EnemyBarlowe::turnAround()
{
    if (m_facing < 0.0f) {
        setFacing(1.0f);
    } else {
        setFacing(-1.0f);
    }
}

// State 0: walks, turning at walls and ledges, until
// the player comes in range (then state 1, ready to attack).
void EnemyBarlowe::statePatrol()
{
    float speed = 40.0f;
    if (getB230()) {
        speed = 64.0f;
    }
    if (!m_stateInit) {
        EnemyHitBox& hb = m_hitBoxes0[0];
        float facing = m_facing;
        hb.u00 = 0;
        hb.b2B = true;
        hb.b28 = false;
        hb.f54 = 0;
        hb.b1C = true;
        m_timer = 0;
        m_stateInit = true;
        m_vel[0] = facing * speed;
    }
    if (mustTurn()) {
        if (m_facing < 0.0f) {
            setFacing(1.0f);
        } else {
            setFacing(-1.0f);
        }
        m_vel[0] = m_facing * speed;
    }
    if (m_b221 == m_b220 && fabsf(m_playerPos[0] - m_selfPos[0]) < 128.0f &&
        m_playerPos[1] - m_selfPos[1] > -80.0f && m_playerPos[1] - m_selfPos[1] < 80.0f) {
        m_state = 1;
        m_attackWait = 0.8f;
        m_stateInit = false;
    }
}

// The event part of update: false once dead.
bool EnemyBarlowe::handleEvents()
{
    if (m_dead) {
        return false;
    }
    if (m_hit) {
        m_hit = false;
        m_state = 3;
        m_stateInit = false;
    }
    m_wake = false;
    return true;
}

// Slot +0x020. Barlowe: 0 waits for the player, 1 floats and waits 3-4 s
// (the Unity remake's wait), then picks one of five glyph spells with equal
// odds, 2 casts it, 3 dies.
void EnemyBarlowe::update(float dt)
{
    if (m_dead) {
        return;
    }
    if (m_hit) {
        m_hit = false;
        m_state = 3;
        m_stateInit = false;
    }
    m_wake = false;
    switch (m_state) {
    case 0: bossIdle(); break;
    case 1: bossApproach(dt); break;
    case 2: bossAttack(dt); break;
    case 3: bossDie(); break;
    }
}

enum { BA_IDLE = 0, BA_FIRE = 1, BA_GRANDO = 2, BA_THUNDER = 3, BA_GLOBUS = 4, BA_FIST = 5,
       BA_DEAD = 6, BA_AIR = 8, BA_FIST_READY = 14 };

int EnemyBarlowe::rnd(int n)
{
    m_rng = m_rng * 1103515245u + 12345u;
    return (int)((m_rng >> 16) % (unsigned)n);
}

void EnemyBarlowe::hitArea(float x0, float y0, float x1, float y1)
{
    EnemyReq24 q;
    q.w[0] = fbits(x0 < x1 ? x0 : x1);
    q.w[1] = fbits(y0);
    q.w[2] = fbits(x0 < x1 ? x1 : x0);
    q.w[3] = fbits(y1);
    q.w[4] = fbits(-1.0f);
    q.w[5] = fbits(-1.0f);
    q.w[6] = 0x400000C1;
    q.w[7] = fbits(getF1F0());
    q.w[8] = fbits(getF1E0());
    pushQueue24(q);
}

// Mod sprite shot n of this mod (mods/.../data/shot/mod_shots.txt, skill
// 4000 + n, category 12): its sprite, damage and life come from that file.
void EnemyBarlowe::fire(int n, float x, float y, float vx, float vy)
{
    EnemyShotReq r;
    r.x = x;
    r.y = y;
    r.vx = vx;
    r.vy = vy;
    r.i10 = 12;
    r.i14 = 4000 + n;
    r.i18 = m_facing < 0.0f ? 1 : 0;
    r.f24 = getF1F0();
    pushShotReq(r);
}

void EnemyBarlowe::bossIdle()
{
    if (!m_stateInit) {
        m_hitBoxes0[0].u00 = BA_IDLE;
        m_hitBoxes0[0].b28 = false;
        m_vel[0] = 0;
        m_stateInit = true;
        m_rng = (unsigned)(m_hostContext & 0xFFFF) + 13;
    }
    if (fabsf(m_playerPos[0] - m_selfPos[0]) < 450.0f && fabsf(m_playerPos[1] - m_selfPos[1]) < 250.0f) {
        m_attackWait = 2.0f;
        setState(1);
    }
}

void EnemyBarlowe::bossApproach(float dt)
{
    if (!m_stateInit) {
        m_hitBoxes0[0].u00 = BA_AIR;
        m_hitBoxes0[0].b28 = false;
        m_vel[0] = 0;
        m_stateInit = true;
        m_timer = 3.0f + rnd(100) * 0.01f;   // Random.Range(waitTimeMin 3, waitTimeMax 4)
    }
    faceTarget();
    m_attackWait += dt;
    if (m_attackWait < m_timer) {
        return;
    }
    static const int kSpell[5] = { BA_FIRE, BA_GRANDO, BA_THUNDER, BA_GLOBUS, BA_FIST };
    m_attack = kSpell[rnd(5)];
    m_attackWait = 0;
    setState(2);
}

void EnemyBarlowe::bossAttack(float dt)
{
    EnemyHitBox& hb = m_hitBoxes0[0];
    if (!m_stateInit) {
        faceTarget();
        hb.u00 = m_attack == BA_FIST ? BA_FIST_READY : m_attack;
        hb.b28 = false;
        m_timer = 0;
        m_vel[0] = 0;
        m_stateInit = true;
        m_lostTimer = m_playerPos[0];
        m_b44CE = false;
        m_attackStep = -1;
        return;
    }
    m_timer += dt;
    float t = m_timer, x = m_selfPos[0], y = m_selfPos[1], f = m_facing;
    switch (m_attack) {
    case BA_FIRE:       // Ignis (Usutio): a fire burst in front
        if (!m_b44CE && t > 0.5f) {
            m_b44CE = true;
            fire(0, x + f * 70.0f, y - 44.0f, 0.0f, 0.0f);
        }
        break;
    case BA_GRANDO:     // Grando: rock spikes rising along the floor both ways
        if (t > 0.6f && t < 1.8f && (int)((t - 0.6f) * 6.0f) != m_attackStep) {
            m_attackStep = (int)((t - 0.6f) * 6.0f);
            float d = 40.0f + m_attackStep * 50.0f;
            fire(1, x + d, y - 28.0f, 0.0f, 0.0f);
            fire(1, x - d, y - 28.0f, 0.0f, 0.0f);
        }
        break;
    case BA_THUNDER:    // Tonitrus: three bolts at the player's spot and either side
        if (t > 0.8f && t < 1.4f) {
            for (int k = -1; k <= 1; k++) {
                float bx = m_lostTimer + k * 90.0f;
                hitArea(bx - 14.0f, y - 260.0f, bx + 14.0f, y + 20.0f);
            }
        }
        break;
    case BA_GLOBUS:     // Globus: two orbs, angled up and down
        if (!m_b44CE && t > 0.5f) {
            m_b44CE = true;
            fire(2, x + f * 30.0f, y - 60.0f, f * 220.0f, -110.0f);
            fire(2, x + f * 30.0f, y - 60.0f, f * 220.0f, 110.0f);
        }
        break;
    case BA_FIST:       // a charged glyph fist, then a lunge
        if (t > 0.6f && hb.u00 == BA_FIST_READY) {
            hb.u00 = BA_FIST;
            hb.b28 = false;
        }
        m_vel[0] = t > 0.6f && t < 1.0f && !mustTurn() ? f * 380.0f : 0.0f;
        if (t > 0.6f && t < 1.0f) {
            hitArea(x, y - 70.0f, x + f * 60.0f, y - 20.0f);
        }
        break;
    }
    if ((hb.b28 && t > 1.0f) || t > 2.4f) {
        m_vel[0] = 0;
        setState(1);
    }
}

void EnemyBarlowe::bossDie()
{
    if (!m_stateInit) {
        m_hitBoxes0[0].u00 = BA_DEAD;
        m_hitBoxes0[0].b28 = false;
    }
    stateDie();
}

void EnemyBarlowe::destroy()
{
    release();
}

const char* EnemyBarlowe::getDataPath(int index)
{
    if (index == 0) {
        return "data/enemy/DLL_barlowe/p_barlowe.opd";
    }
    if (index == 1) {
        return "data/enemy/DLL_fumacom/p_fumacom.opd";
    }
    return 0;
}

void EnemyBarlowe::v080(int) { m_wake = true; }

void EnemyBarlowe::v084(int) { m_hit = true; }

void EnemyBarlowe::setMotionB1C(bool off) { m_motion.b1C = !off; }
