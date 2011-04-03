/*
 * tex.cpp
 *
 *  Created on: Apr 1, 2011
 *      Author: josh
 */
#include "tex.h"
#include "logging.h"
#include <fstream>

using namespace std;

tex_t* texLoadTGA(const char * fname)
{
   ifstream f(fname, ios::in|ios::binary);
   if (!f.is_open()) {
      logError("unable to open file %s", fname);
      return NULL;
   }

   tga_header_t header;
   if (!f.read((char*)&header, sizeof(tga_header_t)).good()) {
      logError("reader read failed on %s", fname);
      return NULL;
   }

   if (header.data_type_code != 2) {
      logError("%s has incomplete tga header");
      return NULL;
   }

   if (header.bits_per_pixel != 32) {
      logError("%s is not a 32-bit uncompressed RGB tga file", fname);
      return NULL;
   }

   if (!f.seekg(header.id_length, ios::cur).good()) {
      logError("%s has incomplete id string", fname);
      return NULL;
   }

   int color_map_size = header.color_map_length * (header.color_map_depth/8);
   if (!f.seekg(color_map_size, ios::cur).good()) {
      logError("%s has incomplete color map", fname);
      return NULL;
   }

   tex_t *texture = new tex_t;

   texture->width = header.width;
   texture->height = header.height;

   uint bufsz = header.width * header.height * (header.bits_per_pixel/8);
   texture->pixels = new uint8_t[bufsz];

   f.read((char*)texture->pixels, bufsz);
   if (f.gcount() != bufsz) {
      logError("%s has incomplete image", fname);
      return NULL;
   }

   return texture;
}

void texFree(tex_t *texture) {
   delete texture->pixels;
   delete texture;
}
