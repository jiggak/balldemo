/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#include <sys/types.h>
#include <stdint.h>

#ifndef TEX_H_
#define TEX_H_

///
/// 2D texture struct. Textures are currently limited to 32bit uncompressed
/// RGBA format.
///
typedef struct tex_t {
   unsigned int width, height;
   uint8_t *pixels;
} tex_t;

///
/// Load TGA file from relative asset path. Textures created by this function
/// must be destroyed with texFree().
/// @param path relative asset path to TGA file
/// @return texture struct or NULL if asset not found
///
tex_t* texLoadTGA(const char * path);

///
/// Load TGA file from loaded asset. Textures created by this function must be
/// destroyed with texFree().
/// @param asset loaded asset
/// @return texture struct or NULL if TGA file is invalid
///
tex_t* texLoadTGA(const struct asset_t * asset);

///
/// Free memory used by texture.
///
void texFree(tex_t * texture);

#endif /* TEX_H_ */
