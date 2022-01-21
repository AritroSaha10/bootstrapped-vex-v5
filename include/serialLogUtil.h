#include <stdio.h>
#include <stdarg.h>

enum LOG_COLOR {
    BLACK = 0,
    RED = 1,
    GREEN = 2,
    YELLOW = 3,
    BLUE = 4,
    MAGENTA = 5,
    CYAN = 6,
    WHITE = 7
};

extern void colorPrintf(const char* fmt, LOG_COLOR color, ...);