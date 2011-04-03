/*
 * tex.h
 *
 *  Created on: Apr 1, 2011
 *      Author: josh
 */
#include <sys/types.h>
#include <stdint.h>

#ifndef TEX_H_
#define TEX_H_

typedef struct tex_t {
   uint width, height;
   uint8_t *pixels;
} tex_t;

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

tex_t* texLoadTGA(const char * fname);

void texFree(tex_t *texture);

#endif /* TEX_H_ */
