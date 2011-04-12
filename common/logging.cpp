/*
 * logging.cpp
 *
 *  Created on: Apr 12, 2011
 *      Author: josh
 */
#include "logging.h"

void logError(const char *fmt, ...) {
   va_list argp;
   va_start(argp, fmt);
   logv(LOG_LEVEL_ERROR, fmt, argp);
   va_end(argp);
}

void logInfo(const char *fmt, ...) {
   va_list argp;
   va_start(argp, fmt);
   logv(LOG_LEVEL_INFO, fmt, argp);
   va_end(argp);
}
