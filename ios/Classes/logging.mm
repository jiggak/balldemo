/*
 *  logging.mm
 *  BallDemo
 *
 *  Created by Josh Kropf on 11-04-09.
 *  Copyright 2011 slashdev.ca. All rights reserved.
 *
 */

#include "logging.h"
#import <Foundation/Foundation.h>

void _logv(NSString *prefix, NSString *fmt, va_list args) {
   NSLogv([prefix stringByAppendingString:fmt], args);
}

void logError(const char *fmt, ...) {
   va_list args;
   va_start(args, fmt);
   
   NSString *f = [NSString stringWithCString:fmt encoding:NSASCIIStringEncoding];
   _logv(@"ERROR: ", f, args);
   
   va_end(args);
}

void logInfo(const char *fmt, ...) {
   va_list args;
   va_start(args, fmt);
   
   NSString *f = [NSString stringWithCString:fmt encoding:NSASCIIStringEncoding];
   _logv(@"INFO: ", f, args);
   
   va_end(args);
}
