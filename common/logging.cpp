/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
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
