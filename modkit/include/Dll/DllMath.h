// Dll/DllMath.h - Dinkumware C math entry points the player modules call
// directly (identified, see src/Dll/StdRuntime/README.md).
#pragma once

// _FSin(x, 0) is sinf(x), _FSin(x, 1) cosf(x). dllsoma.
extern "C" float _FSin(float x, unsigned int qoff);
