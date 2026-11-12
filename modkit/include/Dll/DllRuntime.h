// Dll/DllRuntime.h - what every game module ("dll" module, USRDIR/dynamic and
// USRDIR/dlc/*/dll) links in besides its own class: the host-allocator hooks,
// the module entry point and the one-function export the original game calls.
//
// File and symbol names are inferred; the module modules carry no source paths.
// Addresses in comments are the recomp's relocated addresses for dllsoma
// (; the decompilation project). Subtract the base for
// the offset inside the module; every module has its own copy.
#pragma once

#include <stddef.h>

// The host hands the module its heap at creation time. Both hooks are plain
// function pointers, called with the size / pointer only.
typedef void* (*DllAllocFunc)(size_t size);
typedef void  (*DllFreeFunc)(void* p);

extern DllAllocFunc g_dllAlloc;   // bss
extern DllFreeFunc  g_dllFree;    // bss

// Root of every object a module hands to the original game (three
// slots). The original game never deletes module objects itself; it calls release,
// which runs the module's own operator delete and so the module's g_dllFree.
class DllObject {
public:
    virtual ~DllObject();
    virtual void release() = 0;          // +0x08
};

// Game code allocates through a second, non-throwing operator new: call sites
// pass only the size (the second argument is never read) and null-check the result. An
// overload with an empty tag struct passed by value compiles exactly like
// that, so it is modelled as one (name inferred). Use DLL_NEW(Type).
struct DllHeapTag {};
void* operator new(size_t size, DllHeapTag) throw();
void* operator new[](size_t size, DllHeapTag) throw();
void  operator delete(void* p, DllHeapTag) throw();
inline DllHeapTag dllHeap() { return DllHeapTag(); }
#define DLL_NEW new (dllHeap())

// Module entry point (cvhdModuleInit, exported by every module DLL).
// argp receives the module's factory function (see DllMain.cpp).
extern "C" int cvhdModuleInit(unsigned int args, void* argp);
