#include "gfx_m64p.h"
#include "api/m64p_vidext.h"

#include "core/common.h"
#include "core/msg.h"

#include "output/screen.h"

#include <stdlib.h>

/* definitions of pointers to Core video extension functions */

// framebuffer texture states
int32_t win_width;
int32_t win_height;
int32_t win_fullscreen;

void* IntGetProcAddress(const char *name)
{
    //return CoreVideo_GL_GetProcAddress(name);
    return NULL;
}

void screen_init(struct n64video_config* config)
{
    UNUSED(config);

    /* Get the core Video Extension function pointers from the library handle */
    VidExt_Init();

//#ifndef GLES
//    CoreVideo_GL_SetAttribute(M64P_GL_CONTEXT_PROFILE_MASK, M64P_GL_CONTEXT_PROFILE_CORE);
//    CoreVideo_GL_SetAttribute(M64P_GL_CONTEXT_MAJOR_VERSION, 3);
//    CoreVideo_GL_SetAttribute(M64P_GL_CONTEXT_MINOR_VERSION, 3);
//#else
//    CoreVideo_GL_SetAttribute(M64P_GL_CONTEXT_PROFILE_MASK, M64P_GL_CONTEXT_PROFILE_ES);
//    CoreVideo_GL_SetAttribute(M64P_GL_CONTEXT_MAJOR_VERSION, 3);
//    CoreVideo_GL_SetAttribute(M64P_GL_CONTEXT_MINOR_VERSION, 0);
//#endif

    VidExt_SetVideoMode(win_width, win_height, 0, win_fullscreen ? M64VIDEO_FULLSCREEN : M64VIDEO_WINDOWED, M64VIDEOFLAG_SUPPORT_RESIZING);
}

void screen_adjust(int32_t width_out, int32_t height_out, int32_t* width, int32_t* height, int32_t* x, int32_t* y)
{
    UNUSED(width_out);
    UNUSED(height_out);

    *width = win_width;
    *height = win_height;
    *x = 0;
    *y = 0;
}

void screen_update(void)
{
    (*render_callback)(1);
    //CoreVideo_GL_SwapBuffers();
}

void screen_toggle_fullscreen(void)
{
    VidExt_ToggleFullScreen();
}

void screen_close(void)
{
    VidExt_Quit();
}
