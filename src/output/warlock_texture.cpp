#include "warlock_texture.h"
#include "RC_Texture.h"

extern "C"
{
    static wkTextureHandle gCurTexture = NULL;

    wkTextureHandle wk_create_texture(int width, int height, void* data)
    {
        gCurTexture = RC_Texture::Create2D(data, width, height, RC_Format::RGBA_uint8, RC_BufferCPUAccessFlags::ReadWrite());
        return gCurTexture;
    }

    void wk_free_texture(wkTextureHandle tex)
    {
        delete (RC_Texture*)tex;
        gCurTexture = NULL;
    }

    void wk_write_texture(wkTextureHandle tex, void* data)
    {
        RC_Texture* wkTex = (RC_Texture*)tex;
        wkTex->UpdateSubImage(data, 0, 0, wkTex->GetWidth(), wkTex->GetHeight());
    }

    wkTextureHandle wk_get_texture()
    {
        return gCurTexture;
    }
}


