// Dll/Enemy/Fcdrapet/EnemyFcdrapet.h - dllfcdrapet ("DLL_FcDraPet", vtable
// object 0x44C4 bytes). It has no motion or hit boxes of its own:
// it only waits until the flags +0x220 / +0x221 agree and then sets +0x03E
// (slot +0x01C). Names are inferred.
#pragma once

#include "Dll/Enemy/EnemyObjBase.h"

// Member layout of EnemyFcdrapet's own fields: the  layout dump.
class EnemyFcdrapet : public EnemyObjBase {
public:
    EnemyFcdrapet();
    virtual ~EnemyFcdrapet();

    // overridden slots
    virtual void init();                         // +0x00C
    virtual void start();                        // +0x010 empty
    virtual void v01C(float dt);                 // +0x01C
    virtual void destroy();                      // +0x02C
    virtual void release();                      // +0x4D0

public:
    // <layout:EnemyFcdrapet>
    bool m_triggered;                               // +0x44C0 set by slot +0x01C once +0x220 == +0x221
    unsigned char _pad44C1[0x3];
    // </layout:EnemyFcdrapet>
};

