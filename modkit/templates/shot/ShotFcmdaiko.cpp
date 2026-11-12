// Dll/Shot/Fcmdaiko/ShotFcmdaiko.cpp - dllshotfcmdaiko:
// the module glue (cvhdModuleInit first in this module, then DllCreate and its
// factory getter) and the guard-drum shot class. Path and names inferred.
//
// Not written out: the translation unit's static initialiser and finaliser
// ( and ), which construct and destroy the <iostream>
// ios_base::Init objects (compiler-generated from the SDK header).
//
// Status: decompiled.

#include "ShotFcmdaiko.h"

#include <math.h>

// the model this shot uses
static const char s_opdPath[] = "data/opd/player/fuma/p_fuma.opd";

// its display name, "FC月風魔：守り太鼓" in UTF-8
static const char s_name[] = "FC\xE6\x9C\x88\xE9\xA2\xA8\xE9\xAD\x94\xEF\xBC\x9A\xE5\xAE\x88\xE3\x82\x8A"
                             "\xE5\xA4\xAA\xE9\xBC\x93";

extern "C" IShot* DllCreate(DllAllocFunc alloc, DllFreeFunc free);

extern "C" ShotFactoryFunc DllGetFactory()
{
    return DllCreate;
}

extern "C" int cvhdModuleInit(unsigned int, void* argp)
{
    *(ShotFactoryFunc*)argp = DllGetFactory();
    return 0;
}

// Called by moduleUnload when the module is unloaded; nothing to clean up.
extern "C" int cvhdModuleShutdown()
{
    return 1;
}

ShotFcmdaiko::ShotFcmdaiko()
{
    m_state = 0;
    m_time = 0;
    m_dir = 0;
    m_b2F4 = true;
    m_b20A = false;
}

// Saves the heap hooks and makes the shot.
extern "C" IShot* DllCreate(DllAllocFunc alloc, DllFreeFunc free)
{
    g_dllAlloc = alloc;
    g_dllFree = free;
    return DLL_NEW ShotFcmdaiko;
}

void ShotFcmdaiko::release()
{
    delete this;
}

ShotFcmdaiko::~ShotFcmdaiko()
{
}

int ShotFcmdaiko::getResourceCount() { return 1; }

// Resource index -> path, kind 3 (opd).
const char* ShotFcmdaiko::getResource(unsigned int index, int* kind)
{
    if (index < (unsigned int)getResourceCount() && getPath((int)index) != 0) {
        *kind = 3;
        return getPath((int)index);
    }
    *kind = 0;
    return 0;
}

// Placed just ahead of the owner,
// moving forward; one object with a doubled scale for kind 8.
void ShotFcmdaiko::start()
{
    float dir = -1.0f;
    if (m_facing == 0) {
        dir = 1.0f;
    }
    m_dir = dir;
    m_v064.y = 0;
    m_v064.x = dir * 209.79f;
    m_pos.x = fmaf(dir, 6.0f, m_pos.x);
    m_pos.y = m_pos.y + -4.0f;
    float scale = 1.0f;
    if (getU204() == 8) {
        scale = 2.0f;
    }
    addObjA(0x1E, true, 0);
    m_objsA[0].b2A = true;
    setObjAI18(0, 5);
    setObjAScale(0, scale);
    setB206(true);
    setB208(true);
    addPoint(499, &m_pos, false);
}

void ShotFcmdaiko::vfunc01C() {}

void ShotFcmdaiko::end()
{
    if (m_state == 0) {
        setB208(false);
        m_state = 1;
    }
}

void ShotFcmdaiko::tickEnd(float dt)
{
    if (m_state == 0) {
        m_time = m_time + dt;
        if (m_time > 0.7f) {
            setB208(false);
            m_state = 1;
        }
    }
}

// After 0.7 s the shot ends and dies.
void ShotFcmdaiko::update(float dt)
{
    if (isDead()) {
        return;
    }
    int s = m_state;
    if (s == 0) {
        m_time = m_time + dt;
        if (!(m_time > 0.7f)) {
            return;
        }
        setB208(false);
        m_state = 1;
    } else if (s < 0 || s > 1) {
        return;
    }
    kill();
}

void ShotFcmdaiko::vfunc050() {}

void ShotFcmdaiko::vanish()
{
    if (m_state == 0) {
        setB208(false);
        m_state = 1;
    }
}

void ShotFcmdaiko::vfunc04C() {}
void ShotFcmdaiko::onHit(unsigned int) {}

const char* ShotFcmdaiko::getPath(int index)
{
    if (index == 0) {
        return s_opdPath;
    }
    return 0;
}

void ShotFcmdaiko::getInfo(ShotInfo* info)
{
    info->i00 = 1;
    info->f0C = 10.0f;
    info->i04 = 0x11;
    info->name = s_name;
    info->u08 = 0x8000010Au;
    info->i10 = 0;
    info->b14 = false;
    info->i18 = 0;
}
