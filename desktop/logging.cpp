#include "logging.h"
#include <stdio.h>
#include <stdarg.h>

void logError(const char *fmt, ...) {
   va_list argp;
   va_start(argp, fmt);
   printf("ERROR: ");
   vprintf(fmt, argp);
   printf("\n");
   va_end(argp);
}

void logInfo(const char *fmt, ...) {
   va_list argp;
   va_start(argp, fmt);
   printf("INFO: ");
   vprintf(fmt, argp);
   printf("\n");
   va_end(argp);
}
