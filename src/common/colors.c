
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "colors.h"

#ifdef USE_COLORS
static char buffer[1024];
const char* colorize(colors_t arg1, colors_t arg2, colors_t arg3, const char* fmt, ...) {

    va_list args;
    size_t tlen = sizeof(buffer);
    size_t slen = 0;
    memset(buffer, 0, tlen);

    strcat(buffer, "\x1b[");
    slen = strlen(buffer);

    if(arg1 != 0)
        slen += snprintf(&buffer[slen], tlen-slen, "%d", arg1);
    if(arg2 != 0)
        slen += snprintf(&buffer[slen], tlen-slen, ";%d", arg2);
    if(arg3 != 0)
        slen += snprintf(&buffer[slen], tlen-slen, ";%d", arg3);
    strcat(&buffer[slen], "m");
    slen++;

    va_start(args, fmt);
    slen += vsnprintf(&buffer[slen], tlen-slen, fmt, args);
    va_end(args);

    snprintf(&buffer[slen], tlen-slen, "\x1b[m");

    return buffer;
}

void cprintf(colors_t arg1, colors_t arg2, colors_t arg3, const char* fmt, ...) {

    va_list args;

    fputs("\x1b[", stdout);

    if(arg1 != 0)
        printf("%d", arg1);
    if(arg2 != 0)
        printf(";%d", arg2);
    if(arg3 != 0)
        printf(";%d", arg3);
    fputc('m', stdout);

    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);

    fputs("\x1b[m", stdout);
}

#else
const char* colorize(colors_t attr, colors_t fg, colors_t bg, const char* fmt, ...) {

    (void) attr, fg, bg;

    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);

    return buffer;
}

void cprintf(colors_t arg1, colors_t arg2, colors_t arg3, const char* fmt, ...) {

    (void) attr, fg, bg;

    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
}

#endif

