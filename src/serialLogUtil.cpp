#include "serialLogUtil.h"

void colorPrintf(const char* fmt, LOG_COLOR color, ...)
{
    char buffer[4096];
    va_list args;
    va_start(args, color);
    int rc = vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    
    printf("\x1b[3%dm%s\033[m", (int) color, buffer);
}