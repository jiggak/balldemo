/*
 * logging.cpp
 *
 *  Created on: Mar 31, 2011
 *      Author: josh
 */
#include "logging.h"
#include <android/log.h>

#define LOG_TAG "balldemo"

void logError(const char *fmt, ...) {
   va_list argp;
   va_start(argp, fmt);
   __android_log_vprint(ANDROID_LOG_ERROR, LOG_TAG, fmt, argp);
   va_end(argp);
}

void logInfo(const char *fmt, ...) {
   va_list argp;
   va_start(argp, fmt);
   __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG, fmt, argp);
   va_end(argp);
}
