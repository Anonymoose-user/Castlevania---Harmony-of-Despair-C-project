/* Port/cvhd_net_plugin.h - the network plugin interface (C ABI).
 *
 * Online play goes through one plugin DLL in the game's net/ folder
 * (net/<name>.dll). The game picks it with the setting "netPlugin <name>"
 * in save/config.txt (default "gns", GameNetworkingSockets); CVHDEdit's
 * Online > Network plugins... (or install_net_plugin.bat) installs and picks one.
 * Without a plugin the game runs normally; only Online Play cannot connect.
 *
 * A plugin moves byte packets between up to 6 players (slot 0 = the host;
 * clients send to the host, which forwards; or any layout the plugin likes,
 * as long as the calls below are made). It exports:
 *
 *     __declspec(dllexport) const CvhdNetPlugin* cvhdNetPlugin(void);
 *
 * Everything is called on the game's main thread (poll() once a frame).
 */
#ifndef CVHD_NET_PLUGIN_H
#define CVHD_NET_PLUGIN_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CVHD_NET_PLUGIN_VERSION 1
#define CVHD_NET_MAX_PLAYERS 6

/* What the game gives the plugin (init). */
typedef struct CvhdNetHost {
    int version;                                                     /* CVHD_NET_PLUGIN_VERSION */
    /* the plugin reports: */
    void (*receive)(int fromSlot, const void* data, size_t size);    /* a game packet from that player */
    void (*peerJoined)(int slot, const char* name);                  /* a player is in (host: give it a slot first) */
    void (*peerLeft)(int slot);                                      /* gone (slot 0 on a client: lost the host) */
    void (*assigned)(int localSlot, uint32_t hostClockMs);           /* client: the host gave us our slot */
    /* the plugin may ask: */
    uint32_t (*nowMs)(void);                                         /* the session clock (host's) */
    int (*memberPresent)(int slot);
    const char* (*memberName)(int slot);
    void (*log)(const char* line);                                   /* to cvhd.log */
    const char* gameFolder;                                          /* where cvhd.exe is (plugin settings) */
} CvhdNetHost;

/* A lobby the plugin found (lobbySearch). */
typedef struct CvhdNetLobby {
    char address[128];   /* what join() takes */
    char name[64];
    char code[16];
    int  stage, hard, level, players, maxPlayers;
} CvhdNetLobby;

typedef struct CvhdNetPlugin {
    int version;                                                     /* CVHD_NET_PLUGIN_VERSION */
    const char* name;                                                /* shown in the menus / editor */
    int  (*init)(const CvhdNetHost* host);                           /* 0 = cannot run (no network, ...) */
    void (*shutdown)(void);
    /* the session (required) */
    int  (*host)(uint16_t port, const char* name);                   /* start hosting; 1 = ok */
    int  (*join)(const char* address, const char* name);             /* join a host; 1 = started */
    void (*leave)(void);
    void (*send)(int slot, const void* data, size_t size, int reliable);   /* slot -1 = everyone */
    void (*poll)(void);
    /* lobbies (optional, null = none: players join by typed address / LAN search) */
    int  (*lobbyCreate)(const char* code, const char* name);
    void (*lobbyUpdate)(int stage, int hard, int level, int players, int maxPlayers);
    void (*lobbyDestroy)(void);
    int  (*lobbySearch)(const char* code, CvhdNetLobby* out, int max);   /* code null = all; returns count */
    int  (*addressIsMine)(const char* address);                      /* 1 when join() takes this address form */
} CvhdNetPlugin;

typedef const CvhdNetPlugin* (*CvhdNetPluginEntry)(void);

#ifdef __cplusplus
}
#endif

#endif
