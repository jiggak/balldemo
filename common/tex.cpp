/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#include "tex.h"
#include "assets.h"
#include "logging.h"
#include <cstring>


typedef struct {
   uint8_t id_length;
   uint8_t color_map_type;
   uint8_t data_type_code;
   uint16_t color_map_origin;
   uint16_t color_map_length;
   uint8_t color_map_depth;
   uint16_t x_origin;
   uint16_t y_origin;
   uint16_t width;
   uint16_t height;
   uint8_t bits_per_pixel;
   uint8_t image_descriptor;
} __attribute__((__packed__)) tga_header_t;


tex_t* texLoadTGA(const char * path)
{
   asset_t * asset = loadAsset(path);
   if (!asset) {
      return NULL;
   }

   tex_t *texture = texLoadTGA(asset);
   freeAsset(asset);

   if (!texture) {
      return NULL;
   }

   return texture;
}

tex_t* texLoadTGA(const asset_t * asset)
{
   int cursor = 0;

   tga_header_t *header = (tga_header_t*)asset->data;
   cursor += sizeof(tga_header_t);

   cursor += header->id_length;

   int color_map_size = header->color_map_length * (header->color_map_depth/8);
   cursor += color_map_size;

   tex_t *texture = new tex_t;

   texture->width = header->width;
   texture->height = header->height;

   int bufsz = header->width * header->height * (header->bits_per_pixel/8);
   texture->pixels = new uint8_t[bufsz];

   if (bufsz > (asset->size - cursor)) {
      logError("tga file has incomplete pixel data");
      texFree(texture);
      return NULL;
   }

   memcpy(texture->pixels, asset->data + cursor, bufsz);

   // TGA pixel data is BGR packed, convert to RGB
   for (int i=0; i<bufsz; i+=4) {
      uint8_t b = texture->pixels[i];
      texture->pixels[i] = texture->pixels[i+2];
      texture->pixels[i+2] = b;
   }

   return texture;
}

void texFree(tex_t *texture) {
   delete texture->pixels;
   delete texture;
}
