#ifndef _TRACE_H_
#define _TRACE_H_

#ifdef USE_TRACE
extern int verbosity;
extern int level;
#define DEFAULT_TRACE 50

#define INDENT trace_pad(level * 2, ' ')

#define ENTER                                  \
    do {                                       \
        if(verbosity >= DEFAULT_TRACE) {       \
            INDENT;                            \
            printf("%s %s()\n", colorize(fgYEL, aBOLD, 0, "ENTER:"), __func__); \
            level++;                           \
        }                                      \
    } while(false)

#define RETURN(...)                                               \
    do {                                                          \
        if(verbosity >= DEFAULT_TRACE) {                          \
            level--;                                              \
            INDENT;                                               \
            printf("%s %s()\n", colorize(fgYEL, aBOLD, 0, "RETURN(%s)", #__VA_ARGS__), __func__); \
        }                                                         \
        return __VA_ARGS__;                                       \
    } while(false)

#define TRACE(...)                         \
    do {                                   \
        if(verbosity >= DEFAULT_TRACE) {   \
            INDENT;                        \
            printf("%s", colorize(fgCYA, aBOLD, 0, "TRACE: ")); \
            printf(__VA_ARGS__); \
            fputc('\n', stdout);           \
        }                                  \
    } while(false)

#define TRACEX(n, ...)                     \
    do {                                   \
        if(verbosity >= (n)) {             \
            INDENT;                        \
            printf("\x1b[1;36mTRACE:\x1b[m " __VA_ARGS__); \
            fputc('\n', stdout);           \
        }                                  \
    } while(false)


#define LEGEND(s) print_legend(s)
void print_legend(const char* str);
void prnch(int ch);
#include "string_buffer.h"
void prnstr(const char* str);
void trace_pad(int num, int ch);

#else

#define ENTER
#define RETURN(...)         \
    do {                    \
        return __VA_ARGS__; \
    } while(false)
#define TRACE(...)
#define TRACEX(n, ...)
#define LEGEND(s)
#endif

#endif /* _TRACE_H_ */
