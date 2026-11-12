// Dll/DllAllocator.h - STL allocator over the module's heap hooks (name
// inferred). Every std::vector in the player library calls g_dllAlloc /
// g_dllFree directly when it grows (e.g. dllsoma ),
// not operator new, so the containers carry an allocator like this one.
#pragma once

#include "Dll/DllRuntime.h"

#include <cstddef>
#include <new>

template <class T>
class DllAllocator {
public:
    typedef T              value_type;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;
    template <class U> struct rebind { typedef DllAllocator<U> other; };

    DllAllocator() {}
    template <class U> DllAllocator(const DllAllocator<U>&) {}

    pointer allocate(size_type n, const void* = 0) { return (pointer)g_dllAlloc(n * sizeof(T)); }
    void deallocate(pointer p, size_type) { g_dllFree(p); }
    void construct(pointer p, const T& v) { new ((void*)p) T(v); }
    void destroy(pointer p) { p->~T(); }
    size_type max_size() const { return size_type(-1) / sizeof(T); }
    pointer address(reference r) const { return &r; }
    const_pointer address(const_reference r) const { return &r; }
};

template <class T, class U>
inline bool operator==(const DllAllocator<T>&, const DllAllocator<U>&) { return true; }
template <class T, class U>
inline bool operator!=(const DllAllocator<T>&, const DllAllocator<U>&) { return false; }
