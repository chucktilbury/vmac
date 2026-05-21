#ifndef _COLORS_H_
#define _COLORS_H_

typedef enum colors_t {
    aNORM = 0,
    aBOLD = 1,
    aUNDER = 4,
    aBLINK = 5,
    aREV = 7,
    aHIDDEN = 8,

    fgBLK = 30,
    fgRED = 31,
    fgGRN = 32,
    fgYEL = 33,
    fgBLU = 34,
    fgMAG = 35,
    fgCYA = 36,
    fgGRY = 37,

    bgBLK = 40,
    bgRED = 41,
    bgGRN = 42,
    bgYEL = 43,
    bgBLU = 44,
    bgMAG = 45,
    bgCYN = 46,
    bgGRY = 47,
} colors_t;

const char* colorize(colors_t attr, colors_t fg, colors_t bg, const char* fmt, ...);
void cprintf(colors_t arg1, colors_t arg2, colors_t arg3, const char* fmt, ...);

#endif /* _COLORS_H_ */
