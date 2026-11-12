/* cvhd_api.h - the game's plain C API for mods (hook system + a starter game API).
 *
 * Everything here is C ABI with plain C types, so C, C++, Lua bindings and C#
 * (P/Invoke or function pointers) can all use it. The functions are exported
 * from cvhd.exe; find them with GetProcAddress(GetModuleHandleA(0), "cvhd...")
 * or get them all at once from cvhdGetApi() (C++ modules: Dll/DllHooks.h).
 * Docs: docs/modding_hooks.md (every event and its fields).
 *
 * Threads: the game frame runs on 2 worker threads. A listener runs on the
 * thread that emitted the event, possibly at the same time as another
 * listener call on the other thread. Listeners must be quick, must not block
 * or hold locks across calls, and must not register/unregister from inside a
 * listener of the same event while expecting it to affect that same emit.
 *
 * Plugins: an enabled mod's mods/<mod>/plugins/<name>.dll is loaded at the first
 * game frame. Entry point (required):
 *     __declspec(dllexport) int cvhdPluginInit(const CvhdApi* api);   // 0 = ok
 * optional:
 *     __declspec(dllexport) void cvhdPluginShutdown(void);
 * `api` stays valid for the whole run; api->modDir is the mod's folder.
 */
#ifndef CVHD_API_H
#define CVHD_API_H

#ifdef __cplusplus
extern "C" {
#endif

#define CVHD_API_VERSION 1

#if defined(CVHD_API_BUILD)
#define CVHD_API __declspec(dllexport)
#else
#define CVHD_API
#endif

typedef struct CvhdHookEvent CvhdHookEvent;   /* opaque to users */
typedef unsigned int CvhdHookHandle;          /* 0 = failed */
typedef unsigned long long CvhdHandle;        /* a game object handle or a pointer, as a number */

/* Listener: return CVHD_HOOK_CONTINUE (0) or CVHD_HOOK_STOP (1, no later listeners run). */
typedef int (*CvhdHookFn)(CvhdHookEvent* ev, void* user);
#define CVHD_HOOK_CONTINUE 0
#define CVHD_HOOK_STOP     1

/* ---- version / log */
CVHD_API int  cvhdApiVersion(void);
CVHD_API void cvhdLog(const char* text);   /* one line to the game log (stderr), prefixed "[mod]" */

/* ---- hooks. Higher priority runs first; equal priorities run in register order. */
CVHD_API CvhdHookHandle cvhdHookRegister(const char* event, CvhdHookFn fn, void* user, int priority);
CVHD_API int            cvhdHookUnregister(CvhdHookHandle h);   /* 1 = removed */

/* ---- event access (only inside a listener). Getters convert int<->float; a
 * missing field gives `def` (NULL for strings). Setters change an existing
 * field (or add it while there is room); return 1 on success. */
CVHD_API const char* cvhdEventName(const CvhdHookEvent* ev);
CVHD_API int         cvhdEventHas(const CvhdHookEvent* ev, const char* field);
CVHD_API int         cvhdEventGetInt(const CvhdHookEvent* ev, const char* field, int def);
CVHD_API float       cvhdEventGetFloat(const CvhdHookEvent* ev, const char* field, float def);
CVHD_API const char* cvhdEventGetString(const CvhdHookEvent* ev, const char* field);
CVHD_API CvhdHandle  cvhdEventGetHandle(const CvhdHookEvent* ev, const char* field);
CVHD_API int         cvhdEventSetInt(CvhdHookEvent* ev, const char* field, int v);
CVHD_API int         cvhdEventSetFloat(CvhdHookEvent* ev, const char* field, float v);
/* The result slot: the value the game uses after the emit (e.g. a damage
 * amount). Events without one ignore SetResult. */
CVHD_API int         cvhdEventHasResult(const CvhdHookEvent* ev);
CVHD_API float       cvhdEventGetResult(const CvhdHookEvent* ev);
CVHD_API void        cvhdEventSetResult(CvhdHookEvent* ev, float v);
/* Cancel: only events documented as cancellable honour it (returns 0 otherwise). */
CVHD_API int         cvhdEventCancel(CvhdHookEvent* ev);
CVHD_API int         cvhdEventIsCancelled(const CvhdHookEvent* ev);

/* ---- starter game API. Player slots 0-3; functions return 0 / -1 when there is nothing. */
CVHD_API int        cvhdPlayerCount(void);                                /* slots in use */
CVHD_API CvhdHandle cvhdPlayerHandle(int slot);                           /* 0 = empty slot */
CVHD_API int        cvhdPlayerSlot(CvhdHandle player);                    /* -1 = not a player */
CVHD_API int        cvhdPlayerPosition(int slot, float* x, float* y);     /* 1 = ok */
CVHD_API float      cvhdPlayerHp(int slot);                               /* -1 = no player */
/* A mod_shots sprite shot (data/shot/mod_shots.txt id) at x,y; speed in
 * pixels/s along angle (degrees, 0 = right, 90 = down). owner may be 0. */
CVHD_API CvhdHandle cvhdShotSpawn(int id, float x, float y, float speed, float angleDeg, CvhdHandle owner);
CVHD_API int        cvhdSoundPlay(const char* name);                      /* a sound effect by name; 1 = played */
CVHD_API int        cvhdRandom(int low, int high);                        /* [low, high), the game's LCG (own stream) */
CVHD_API int        cvhdStageId(void);                                    /* the selected stage ("room") id, 0 = none */
CVHD_API int        cvhdStageIndex(void);                                 /* its index, -1 = none */
CVHD_API int        cvhdStageActive(void);                                /* 1 while a stage is loaded */
CVHD_API unsigned   cvhdStageFlags(void);                                 /* Stage::flags (read only, see docs) */

/* ---- everything above as one table (plugins get it in cvhdPluginInit). */
typedef struct CvhdApi {
    int         version;   /* CVHD_API_VERSION */
    int         size;      /* sizeof(CvhdApi) */
    const char* modDir;    /* plugins: the mod's folder (UTF-8); NULL from cvhdGetApi */
    int            (*apiVersion)(void);
    void           (*log)(const char*);
    CvhdHookHandle (*hookRegister)(const char*, CvhdHookFn, void*, int);
    int            (*hookUnregister)(CvhdHookHandle);
    const char*    (*eventName)(const CvhdHookEvent*);
    int            (*eventHas)(const CvhdHookEvent*, const char*);
    int            (*eventGetInt)(const CvhdHookEvent*, const char*, int);
    float          (*eventGetFloat)(const CvhdHookEvent*, const char*, float);
    const char*    (*eventGetString)(const CvhdHookEvent*, const char*);
    CvhdHandle     (*eventGetHandle)(const CvhdHookEvent*, const char*);
    int            (*eventSetInt)(CvhdHookEvent*, const char*, int);
    int            (*eventSetFloat)(CvhdHookEvent*, const char*, float);
    int            (*eventHasResult)(const CvhdHookEvent*);
    float          (*eventGetResult)(const CvhdHookEvent*);
    void           (*eventSetResult)(CvhdHookEvent*, float);
    int            (*eventCancel)(CvhdHookEvent*);
    int            (*eventIsCancelled)(const CvhdHookEvent*);
    int            (*playerCount)(void);
    CvhdHandle     (*playerHandle)(int);
    int            (*playerSlot)(CvhdHandle);
    int            (*playerPosition)(int, float*, float*);
    float          (*playerHp)(int);
    CvhdHandle     (*shotSpawn)(int, float, float, float, float, CvhdHandle);
    int            (*soundPlay)(const char*);
    int            (*random)(int, int);
    int            (*stageId)(void);
    int            (*stageIndex)(void);
    int            (*stageActive)(void);
    unsigned       (*stageFlags)(void);
    /* version 1 ends here; later versions only append */
} CvhdApi;

CVHD_API const CvhdApi* cvhdGetApi(void);

typedef int  (*CvhdPluginInitFn)(const CvhdApi* api);
typedef void (*CvhdPluginShutdownFn)(void);

#ifdef __cplusplus
}
#endif

#endif /* CVHD_API_H */
