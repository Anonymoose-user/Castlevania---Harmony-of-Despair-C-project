// net_plugin.cpp - a template network plugin for CVHD online play
// (include/Port/cvhd_net_plugin.h). Fill in the TODOs with your networking
// library (Steam, your own relay, WebRTC, ...). Build (Visual Studio x64
// command prompt or clang-cl):
//
//   cl /nologo /LD /O2 /MT /I ..\..\include net_plugin.cpp /Fe:myonline.dll
//
// Install: copy myonline.dll to the game's net\ folder and pick it (CVHDEdit
// Mods > Network plugins..., or install_net_plugin.bat myonline.dll).
//
// The rules: up to 6 players, slot 0 is the host. When a client joins, the
// host gives it a free slot and tells everyone: host calls peerJoined(slot,
// name) for the newcomer; the newcomer gets assigned(slot, host->nowMs()) and
// peerJoined for everyone already there. Every game packet that arrives goes
// to receive(fromSlot, data, size) unchanged. send(slot, ...) slot -1 means
// everyone (a client sends to the host, which passes it on).
#include "Port/cvhd_net_plugin.h"

#include <string.h>

static const CvhdNetHost* g_host;

static int pInit(const CvhdNetHost* host)
{
    g_host = host;
    g_host->log("my online plugin: ready");
    return 1;   // 0 if your library cannot start
}

static void pShutdown() {}

static int pHost(uint16_t port, const char* name)
{
    // TODO: start listening; slot 0 is you (the game already knows)
    (void)port; (void)name;
    return 1;
}

static int pJoin(const char* address, const char* name)
{
    // TODO: connect to `address` (whatever your lobby / search gave), send your name;
    // when the host answers: g_host->assigned(mySlot, hostClockMs) and
    // g_host->peerJoined(slot, name) for each player already in
    (void)address; (void)name;
    return 0;
}

static void pLeave()
{
    // TODO: close connections
}

static void pSend(int slot, const void* data, size_t size, int reliable)
{
    // TODO: deliver to that slot (-1: everyone)
    (void)slot; (void)data; (void)size; (void)reliable;
}

static void pPoll()
{
    // TODO: pump your library; for each packet: g_host->receive(fromSlot, data, size);
    // a player gone: g_host->peerLeft(slot) (slot 0 on a client = lost the host)
}

static const CvhdNetPlugin kPlugin = {
    CVHD_NET_PLUGIN_VERSION, "My online service",
    pInit, pShutdown, pHost, pJoin, pLeave, pSend, pPoll,
    0, 0, 0, 0,   // lobbyCreate / lobbyUpdate / lobbyDestroy / lobbySearch: fill in for a lobby list
    0,            // addressIsMine
};

extern "C" __declspec(dllexport) const CvhdNetPlugin* cvhdNetPlugin(void) { return &kPlugin; }
