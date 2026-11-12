// Dll/DllMutex.h - the enemy modules' mutex wrappers (one class per module,
// each holding a std::recursive_mutex through a pointer field). It is placed in malloc memory: module operator
// new goes to the game heap, which is not set yet while module static
// initializers run (the mutexes are members of module objects).
// Use inside a wrapper class's members.
#pragma once

#include <stdlib.h>
#include <mutex>
#include <new>
#define DLL_MUTEX_FIELD std::recursive_mutex* m_native;   // native only (the original class ends at m_id)
#define DLL_MUTEX_CREATE() (m_native = new (malloc(sizeof(std::recursive_mutex))) std::recursive_mutex)
#define DLL_MUTEX_DESTROY() (m_native ? (m_native->~recursive_mutex(), free(m_native), m_native = nullptr) : nullptr)
#define DLL_MUTEX_LOCK() (m_native->lock(), 0)
#define DLL_MUTEX_UNLOCK() (m_native->unlock(), 0)
