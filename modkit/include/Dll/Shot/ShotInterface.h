// Dll/Shot/ShotInterface.h - the interface the original game drives a shot module
// through (dllshotfcmdaiko, 357 slots, all pure). Each shot
// family module's DllCreate returns one of these (written out per module,
// see src/Dll/Shot/Fcmdaiko/ShotFcmdaiko.cpp).
// Unlike the player family's DllObject, release() is slot +0x000 and the two
// destructors follow it (+0x004 D1, +0x008 D0), so IShot is its own root.
// Names are inferred; the slot list lives in ShotSlots.inc.
#pragma once

#include "Dll/DllRuntime.h"
#include "Dll/Shot/ShotTypes.h"

class IShot {
public:
#define SHOT_SLOT(off, ret, name, params, base) virtual ret name params = 0;
#define SHOT_DTOR virtual ~IShot();   // (slots +0x004, +0x008)
#include "Dll/Shot/ShotSlots.inc"
#undef SHOT_DTOR
#undef SHOT_SLOT
};

typedef IShot* (*ShotFactoryFunc)(DllAllocFunc alloc, DllFreeFunc free);
