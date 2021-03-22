#ifndef _warlock_texture_h_
#define _warlock_texture_h_

#ifdef __cplusplus
extern "C" {
#endif

typedef void* wkTextureHandle;

wkTextureHandle wk_create_texture(int width, int height, void* data);
void wk_write_texture(wkTextureHandle tex, void* data);
void wk_free_texture(wkTextureHandle tex);
wkTextureHandle wk_get_texture();

#ifdef __cplusplus
}
#endif

#endif // _warlock_texture_h_
