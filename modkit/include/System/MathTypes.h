// System/MathTypes.h - small math types shared by every subsystem.
// Namespace me::math::normal is inferred from the engine's "me" library; the
// constants are static-initialised bss globals.
#pragma once

#ifndef ME_MATH_VECTOR2_DEFINED
#define ME_MATH_VECTOR2_DEFINED
namespace me { namespace math { namespace normal {
struct Vector2 { float x, y; };
} } }
#endif

typedef me::math::normal::Vector2 Vec2;

// A plain 2-float vector (menu, effect and param code; one definition, it used
// to be restated in Menu/MenuPages.h, Effect/EffectObjectInlines.h and
// Param/ParamUnity.h).
struct Vec2f { float x, y; };

// All set up by the static initialiser (decoded with
// the decompilation project). Two sets exist (probably Vector* and Point*
// types); the first is at, the second at.
extern const Vec2 g_vec2Zero;
extern const Vec2 g_vec2UnitX;
extern const Vec2 g_vec2UnitY;
extern const Vec2 g_vec2One;
extern const Vec2 g_vec2Zero2;   // , (0, 0): second set,
                                 // not (1, 1) as first assumed
extern const Vec2 g_vec2UnitX2;
extern const Vec2 g_vec2UnitY2;
extern const Vec2 g_vec2One2;

// 16-byte constants (x, y, z, w), same initialiser:
// zero X (1,0,0,0) Y Z (0,0,1,1)
// zero X Y Z (0,0,1,1)
// zero4 X Y Z (0,0,1,0) W
// zero quat identity quat (0,0,0,1)
// 3x3 zero 3x3 identity (rows X, Y, Z)
// 4x4 zero 4x4 identity
// The me SIMD helpers use their own zero/one/epsilon (1e-5) splats at
// / / (see me/vecmath.h).
