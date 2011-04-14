/*
 * tex.cpp
 *
 *  Created on: Apr 1, 2011
 *      Author: josh
 */
#include "tex.h"
#include "assets.h"
#include "logging.h"
#include <cstring>

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

   uint bufsz = header->width * header->height * (header->bits_per_pixel/8);
   texture->pixels = new uint8_t[bufsz];

   if (bufsz > (asset->size - cursor)) {
      logError("tga file has incomplete pixel data");
      texFree(texture);
      return NULL;
   }

   memcpy(texture->pixels, asset->data + cursor, bufsz);

   // TGA pixel data is BGR packed, convert to RGB
   for (uint i=0; i<bufsz; i+=4) {
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
