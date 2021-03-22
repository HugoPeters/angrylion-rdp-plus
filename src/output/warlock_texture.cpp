#include "warlock_texture.h"
#include "RC_Texture.h"
#include "C_Mutex.h"
#include "C_Atomic.h"

extern "C"
{
    #include "core/n64video.h"

    static C_Mutex gTexMutex;
    static C_AtomicInt gNeedsStagingSync;
    static wkTextureHandle gStagingTexture = NULL;
    static C_Vector<n64video_pixel> gPixels;
    static int gFboWidth = 0;
    static int gFboHeight = 0;

    void wk_init_texture()
    {
        gNeedsStagingSync = 0;
    }

    void wk_commit_pixels(void* pixels, int width, int height)
    {
        gTexMutex.Lock();

        if (gPixels.Count() < (width * height))
            gPixels.Resize(width * height);

        const n64video_pixel* src = (const n64video_pixel*)pixels;

        for (int i = 0; i < width * height; ++i)
            gPixels[i] = src[i];

        gFboWidth = width;
        gFboHeight = height;

        gTexMutex.Unlock();

        gNeedsStagingSync = 1;
    }

    wkTextureHandle wk_get_staging_texture()
    {
        if (gNeedsStagingSync == 0)
            return gStagingTexture;

        if (gFboHeight == 0 || gFboWidth == 0)
            return gStagingTexture;

        gTexMutex.Lock();

        RC_Texture* stagingTex = (RC_Texture*)gStagingTexture;

        if (!stagingTex || (stagingTex->GetWidth() != gFboWidth || stagingTex->GetHeight() != gFboHeight))
        {
            if (stagingTex)
                delete stagingTex;

            gStagingTexture = RC_Texture::Create2D(gPixels.GetBuffer(), gFboWidth, gFboHeight, RC_Format::RGBA_uint8, RC_BufferCPUAccessFlags::ReadWrite());
        }
        else
        {
            stagingTex->UpdateSubImage(gPixels.GetBuffer(), 0, 0, gFboWidth, gFboHeight);
        }

        gTexMutex.Unlock();

        gNeedsStagingSync = 0;

        return gStagingTexture;
    }
}



