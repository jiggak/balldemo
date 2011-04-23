/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#ifndef ASSETS_H_
#define ASSETS_H_

#include <stdint.h>

///
/// Asset loading is platform specific. Each platform must provide an
/// implementation of the loadAsset() and freeAsset() functions.
///

///
/// Asset structure containing raw asset data and the size of the asset.
///
typedef struct asset_t {
   uint8_t *data;
   int size;
} asset_t;


///
/// Load asset from relative path. The relative path must be to a file in the
/// top-level assets directory.
/// @param path assets relative path
/// @return allocated asset structure or NULL if not found
///
asset_t * loadAsset(const char * path);

///
/// Deallocate an asset structure returned by loadAsset() function.
/// @param asset the asset to free
///
void freeAsset(asset_t * asset);

#endif /* ASSETS_H_ */
