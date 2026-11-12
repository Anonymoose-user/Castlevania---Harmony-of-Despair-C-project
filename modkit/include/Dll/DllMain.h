// Dll/DllMain.h - the four functions every game module defines with the same
// shape (names inferred). They are the first code in each module's own
// translation unit, which suggests one macro in a shared header, modelled
// here as DLL_IMPLEMENT_FACTORY.
//
// Protocol:
//   cvhdModuleInit(args, argp) stores the factory's function descriptor at
// *argp and returns 0 (stays loaded). The game later calls
//   factory(alloc, free): the module saves the two heap hooks and returns a
//   new object. The object is destroyed with its release() virtual.
// Game side: moduleLoad / moduleUnload (src/System/ModuleLoader.cpp).
#pragma once

#include "Dll/DllRuntime.h"

typedef DllObject* (*DllFactoryFunc)(DllAllocFunc alloc, DllFreeFunc free);

#define DLL_IMPLEMENT_FACTORY(Class)                                        \
    extern "C" DllObject* DllCreate(DllAllocFunc alloc, DllFreeFunc free)   \
    {                                                                       \
        g_dllAlloc = alloc;                                                 \
        g_dllFree = free;                                                   \
        return DLL_NEW Class;                                                 \
    }                                                                       \
    static DllFactoryFunc DllGetFactory() { return DllCreate; }             \
    void Class::release() { delete this; }

// Emitted further down the module's file than the factory (dllsoma ).
#define DLL_IMPLEMENT_MODULE_START()                                        \
    extern "C" int cvhdModuleInit(unsigned int, void* argp)                   \
    {                                                                       \
        *(DllFactoryFunc*)argp = DllGetFactory();                           \
        return 0;                                                           \
    }
