/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <josh@slashdev.ca> wrote this file. As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return Josh Kropf
 * ----------------------------------------------------------------------------
 */
#ifndef LOGGING_H_
#define LOGGING_H_

#include <cstdarg>

///
/// Logging is platform specific. Each platform must provide an implementation
/// of the logv() function.
///

/// Constants defining the category/severity of log messages.
typedef enum {
   LOG_LEVEL_INFO,
   LOG_LEVEL_ERROR
} log_level_t;

///
/// Base logging function used by all other logging functions. Caller must
/// use va_start() and va_end() macros to initialize and destroy args list.
/// @param level category/severity of log message
/// @param fmt printf style format string
/// @param args variable arguments list
///
void logv(log_level_t level, const char *fmt, va_list args);

/// Log message with LOG_LEVEL_ERROR severity.
void logError(const char *fmt, ...);

/// Log message with LOG_LEVEL_INFO severity.
void logInfo(const char *fmt, ...);

#endif /* LOGGING_H_ */
