/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#import <Foundation/Foundation.h>
#include "logging.h"
#include "assets.h"

///
/// Implementation of the logv() function that calls NSLog(). Since NSLog
/// doesn't have severity level output is prefixed with "ERROR" or "INFO".
///
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

///
/// Implementation of the loadAsset() function that opens and reads files
/// inside the application bundle.
///
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

/// Delete assets data then the asset struct.
void freeAsset(asset_t * asset) {
   delete asset->data;
   delete asset;
}
