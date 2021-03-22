#ifndef _warlock_texture_h_
#define _warlock_texture_h_

#ifdef __cplusplus
extern "C" {
#endif

typedef void* wkTextureHandle;

void wk_init_texture();
void wk_commit_pixels(void* pixels, int width, int height);
wkTextureHandle wk_get_staging_texture();

#ifdef __cplusplus
}
#endif

#endif // _warlock_texture_h_
