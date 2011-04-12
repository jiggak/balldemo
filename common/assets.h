/*
 * assets.h
 *
 *  Created on: April 11, 2011
 *      Author: josh
 */

#ifndef ASSETS_H_
#define ASSETS_H_

#include <stdint.h>

typedef struct asset_t {
   uint8_t *data;
   int size;
} asset_t;

asset_t * loadAsset(const char * path);

void freeAsset(asset_t * asset);

#endif /* ASSETS_H_ */
