// csharp_host - a native CVHD plugin that runs C# plugins (.NET 10) via nethost/hostfxr.
//
// Install (per mod):
//   mods/<mod>/plugins/csharp_host.dll
//   mods/<mod>/plugins/csharp.txt                      list of C# plugins (below)
//   mods/<mod>/plugins/csharp/<Asm>.dll                the C# plugin assembly
//   mods/<mod>/plugins/csharp/<Asm>.runtimeconfig.json its runtimeconfig
// (The C# files may also sit directly in plugins/: the game then tries them as
// native plugins first, logs "no cvhdPluginInit export, unloaded" and goes on.)
//
// csharp.txt: one plugin per line, '#' starts a comment, paths relative to plugins/:
//   csharp/CvhdExample.dll  CvhdExample.CvhdPlugin
// (optional 3rd column: method name, default CvhdPluginInit). The runtimeconfig is
// <assembly without .dll>.runtimeconfig.json next to it. The method must be
//   [UnmanagedCallersOnly(CallConvs = new[]{typeof(CallConvCdecl)})] static int M(IntPtr api)
//
// The runtime is started once per process (first csharp_host to run, using the
// first listed plugin's runtimeconfig). Later plugins/mods reuse it, so all C#
// plugins must target a compatible framework (net10.0). Errors go to the game
// log; nothing here throws or crashes the game. Needs the .NET 10 runtime
// (x64) installed, or a dotnet/ folder next to cvhd.exe (see DOTNET_ROOT below).
//
// Build (Git Bash; NH = the SDK's nethost folder):
//   NH="C:/Program Files/dotnet/packs/Microsoft.NETCore.App.Host.win-x64/10.0.12/runtimes/win-x64/native"
//   "C:/Program Files/LLVM/bin/clang-cl" -nologo -O2 -std:c++17 -MT -I../../include -I"$NH" \
//       -c csharp_host.cpp -Focsharp_host.obj
//   "C:/Program Files/LLVM/bin/lld-link" -nologo -dll -out:csharp_host.dll csharp_host.obj \
//       "$NH/libnethost.lib" libcmt.lib libvcruntime.lib libucrt.lib kernel32.lib advapi32.lib
// libnethost.lib is the static nethost (needs NETHOST_USE_AS_STATIC); nethost.lib would
// need nethost.dll shipped next to csharp_host.dll.
#define _CRT_SECURE_NO_WARNINGS
#define NETHOST_USE_AS_STATIC
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "Port/cvhd_api.h"

#include <nethost.h>
#include <hostfxr.h>
#include <coreclr_delegates.h>

#include <stdio.h>
#include <string>
#include <vector>

static const CvhdApi* g_api;

static void logf(const char* fmt, ...)
{
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    if (g_api && g_api->log) g_api->log(buf);
    else fprintf(stderr, "%s\n", buf);
}

static std::wstring widen(const char* s)
{
    if (!s) return std::wstring();
    int n = MultiByteToWideChar(CP_UTF8, 0, s, -1, 0, 0);
    if (n <= 0) return std::wstring();
    std::wstring w((size_t)n - 1, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s, -1, &w[0], n);
    return w;
}

static std::string narrow(const wchar_t* s)
{
    int n = WideCharToMultiByte(CP_UTF8, 0, s, -1, 0, 0, 0, 0);
    if (n <= 0) return std::string();
    std::string r((size_t)n - 1, '\0');
    WideCharToMultiByte(CP_UTF8, 0, s, -1, &r[0], n, 0, 0);
    return r;
}

// ---- hostfxr (process-wide: the hostfxr module is shared even if several mods ship csharp_host)
static hostfxr_initialize_for_runtime_config_fn fxInit;
static hostfxr_get_runtime_delegate_fn fxGetDelegate;
static hostfxr_close_fn fxClose;
static load_assembly_and_get_function_pointer_fn g_loadAsm;
static bool g_tried;

static bool loadHostfxr()
{
    char_t path[MAX_PATH];
    size_t size = MAX_PATH;
    // An app-local runtime (dotnet/ next to cvhd.exe) wins over the installed one.
    std::wstring local;
    {
        wchar_t exe[MAX_PATH];
        DWORD n = GetModuleFileNameW(0, exe, MAX_PATH);
        if (n > 0 && n < MAX_PATH) {
            std::wstring e(exe);
            size_t s = e.find_last_of(L"\\/");
            local = e.substr(0, s + 1) + L"dotnet";
            if (GetFileAttributesW((local + L"\\host\\fxr").c_str()) == INVALID_FILE_ATTRIBUTES) local.clear();
        }
    }
    get_hostfxr_parameters params = { sizeof(get_hostfxr_parameters), nullptr, local.empty() ? nullptr : local.c_str() };
    int rc = get_hostfxr_path(path, &size, &params);
    if (rc != 0) {
        logf("csharp_host: .NET runtime not found (get_hostfxr_path 0x%08x); install the .NET 10 x64 runtime", (unsigned)rc);
        return false;
    }
    HMODULE lib = LoadLibraryW(path);
    if (!lib) {
        logf("csharp_host: cannot load %s (error %lu)", narrow(path).c_str(), GetLastError());
        return false;
    }
    fxInit = (hostfxr_initialize_for_runtime_config_fn)GetProcAddress(lib, "hostfxr_initialize_for_runtime_config");
    fxGetDelegate = (hostfxr_get_runtime_delegate_fn)GetProcAddress(lib, "hostfxr_get_runtime_delegate");
    fxClose = (hostfxr_close_fn)GetProcAddress(lib, "hostfxr_close");
    if (!fxInit || !fxGetDelegate || !fxClose) {
        logf("csharp_host: hostfxr is missing exports (too old?)");
        return false;
    }
    return true;
}

// Starts the runtime (or attaches to the one already running) and gets the loader delegate.
static bool startRuntime(const std::wstring& runtimeConfig)
{
    if (g_loadAsm) return true;
    if (g_tried) return false;
    g_tried = true;
    if (!loadHostfxr()) return false;
    hostfxr_handle cx = nullptr;
    int rc = fxInit(runtimeConfig.c_str(), nullptr, &cx);
    // 0 = Success, 1 = Success_HostAlreadyInitialized, 2 = Success_DifferentRuntimeProperties
    if (rc < 0 || rc > 2 || !cx) {
        logf("csharp_host: hostfxr_initialize_for_runtime_config(%s) failed 0x%08x", narrow(runtimeConfig.c_str()).c_str(), (unsigned)rc);
        if (cx) fxClose(cx);
        return false;
    }
    void* fn = nullptr;
    rc = fxGetDelegate(cx, hdt_load_assembly_and_get_function_pointer, &fn);
    fxClose(cx);   // the runtime stays loaded; the handle is not needed any more
    if (rc != 0 || !fn) {
        logf("csharp_host: hostfxr_get_runtime_delegate failed 0x%08x", (unsigned)rc);
        return false;
    }
    g_loadAsm = (load_assembly_and_get_function_pointer_fn)fn;
    return true;
}

struct Entry { std::wstring assembly, type, method; std::string line; };

static std::vector<Entry> readList(const std::wstring& pluginsDir)
{
    std::vector<Entry> out;
    std::wstring listPath = pluginsDir + L"\\csharp.txt";
    FILE* f = _wfopen(listPath.c_str(), L"r");
    if (!f) {
        logf("csharp_host: no %s", narrow(listPath.c_str()).c_str());
        return out;
    }
    char buf[1024];
    while (fgets(buf, sizeof buf, f)) {
        char* hash = strchr(buf, '#');
        if (hash) *hash = 0;
        char a[512] = {0}, t[256] = {0}, m[128] = {0};
        int n = sscanf(buf, "%511s %255s %127s", a, t, m);
        if (n <= 0) continue;
        if (n < 2) { logf("csharp_host: csharp.txt line needs '<assembly.dll> <Namespace.Type>': %s", a); continue; }
        Entry e;
        std::wstring rel = widen(a);
        for (auto& c : rel) if (c == L'/') c = L'\\';
        e.assembly = pluginsDir + L"\\" + rel;
        e.method = widen(n >= 3 ? m : "CvhdPluginInit");
        // assembly-qualified type name: "Namespace.Type, AssemblyName"
        std::wstring file = rel.substr(rel.find_last_of(L'\\') == std::wstring::npos ? 0 : rel.find_last_of(L'\\') + 1);
        if (file.size() > 4 && _wcsicmp(file.c_str() + file.size() - 4, L".dll") == 0) file.resize(file.size() - 4);
        e.type = widen(t) + L", " + file;
        e.line = a;
        out.push_back(e);
    }
    fclose(f);
    return out;
}

static std::wstring runtimeConfigFor(const std::wstring& assembly)
{
    std::wstring base = assembly;
    if (base.size() > 4 && _wcsicmp(base.c_str() + base.size() - 4, L".dll") == 0) base.resize(base.size() - 4);
    return base + L".runtimeconfig.json";
}

extern "C" __declspec(dllexport) int cvhdPluginInit(const CvhdApi* api)
{
    if (!api || api->version < 1) return 1;
    g_api = api;
    std::wstring pluginsDir = widen(api->modDir ? api->modDir : ".") + L"\\plugins";
    std::vector<Entry> list = readList(pluginsDir);
    if (list.empty()) return 0;

    int ok = 0;
    for (const Entry& e : list) {
        if (GetFileAttributesW(e.assembly.c_str()) == INVALID_FILE_ATTRIBUTES) {
            logf("csharp_host: %s not found", e.line.c_str());
            continue;
        }
        if (!startRuntime(runtimeConfigFor(e.assembly))) {
            logf("csharp_host: .NET runtime unavailable, C# plugins skipped");
            break;
        }
        void* fn = nullptr;
        int rc = g_loadAsm(e.assembly.c_str(), e.type.c_str(), e.method.c_str(),
                           UNMANAGEDCALLERSONLY_METHOD, nullptr, &fn);
        if (rc != 0 || !fn) {
            logf("csharp_host: %s: cannot get %s.%s (0x%08x)", e.line.c_str(), narrow(e.type.c_str()).c_str(),
                 narrow(e.method.c_str()).c_str(), (unsigned)rc);
            continue;
        }
        int r = ((int (*)(const CvhdApi*))fn)(api);
        if (r != 0) logf("csharp_host: %s: init returned %d", e.line.c_str(), r);
        else ++ok;
    }
    logf("csharp_host: %d of %d C# plugin(s) started", ok, (int)list.size());
    return 0;
}

// The runtime cannot be unloaded; C# plugins remove their own hooks if they need to.
extern "C" __declspec(dllexport) void cvhdPluginShutdown(void) {}
