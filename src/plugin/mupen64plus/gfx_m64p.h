#pragma once

#include "api/m64p_plugin.h"
#include "api/m64p_common.h"
#include "plugin/plugin.h"

#ifdef __cplusplus
    extern "C" {
#endif

#include "core/n64video.h"

#ifdef _WIN32
#define DLSYM(a, b) GetProcAddress(a, b)
#else
#include <dlfcn.h>
#define DLSYM(a, b) dlsym(a, b)
#endif

extern void(*render_callback)(int);
extern void (*debug_callback)(void *, int, const char *);
extern void *debug_call_context;

m64p_error GFXANGRYLION_RegisterAPI(gfx_plugin_functions* funcs);

EXPORT m64p_error CALL GFXANGRYLION_PluginStartup(void *Context,
    void(*DebugCallback)(void *, int, const char *));

#ifdef __cplusplus
}
#endif
