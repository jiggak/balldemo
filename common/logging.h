/*
 * logging.h
 *
 *  Created on: Mar 31, 2011
 *      Author: josh
 */
#ifndef LOGGING_H_
#define LOGGING_H_

#include <cstdarg>

typedef enum {
   LOG_LEVEL_INFO,
   LOG_LEVEL_ERROR
} log_level_t;

void logv(log_level_t level, const char *fmt, va_list args);

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

#endif /* LOGGING_H_ */
