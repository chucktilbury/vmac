
#include "common.h"

#ifdef USE_TRACE
int verbosity = 0;
int level = 0;

void trace_pad(int num, int ch) {

    for(int i = 0; i < num; i++)
        putc(ch, stdout);
}

void print_legend(const char* str) {

    if(str != NULL) {
        int len = strlen(str);
        trace_pad((80 - (len + 2)) / 2, '-');
        cprintf(aBOLD, 0, 0, " %s ", str);
        trace_pad((80 - (len + 2)) / 2 + ((!(len & 0x01)) ? 0 : 1), '-');
        putc('\n', stdout);
    }
    else {
        trace_pad(80, '-');
        putc('\n', stdout);
    }
}

void prnch(int ch) {

    if(isprint(ch) && !isspace(ch))
        printf("%c", ch);
    else {
        cprintf(fgRED, aBOLD, 0, "%02X", ch);
    }
}

void prnstr(const char* str) {

    for(int i = 0; str[i] != '\0'; i++) {
        prnch(str[i]);
    }
}

#endif
