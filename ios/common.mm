/*
 *  common.mm
 *  BallDemo
 *
 *  Created by Josh Kropf on 11-04-09.
 *  Copyright 2011 slashdev.ca. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>
#include "logging.h"
#include "assets.h"

void logv(log_level_t level, const char *cfmt, va_list args) {
   NSString *prefix;
   switch (level) {
      case LOG_LEVEL_ERROR:
         prefix = @"ERROR: "; break;
      default:
         prefix = @"INFO: ";
   }
   
   NSString *fmt = [NSString stringWithCString:cfmt encoding:NSASCIIStringEncoding];
   NSLogv([prefix stringByAppendingString:fmt], args);
}

asset_t * loadAsset(const char * cpath) {
   logInfo("loadAsset(%s)", cpath);
   
   NSString *path = [NSString stringWithCString:cpath encoding:NSASCIIStringEncoding];
   NSString *bundlePath = [[NSBundle mainBundle] bundlePath];
   
   // Xcode puts assets into top level "assets" directory in bundle
   path = [@"assets" stringByAppendingPathComponent:path];
   path = [bundlePath stringByAppendingPathComponent:path];
   
   NSData *data = [NSData dataWithContentsOfFile:path];
   if (!data) {
      logError("file not found: %s", cpath);
      return NULL;
   }
   
   asset_t * asset = new asset_t;
   
   asset->size = [data length];
   asset->data = new uint8_t[asset->size];
   
   [data getBytes:asset->data length:asset->size];
   
   return asset;
}

void freeAsset(asset_t * asset) {
   delete asset->data;
   delete asset;
}
