#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include <stdint.h>
#include <stddef.h>
#include "opcodes.h"
#include "string_buffer.h"

typedef struct _symbol_t {
    string_t* tag;
    uint32_t index;
    opcode_t type;
    struct _symbol_t* right;
    struct _symbol_t* left;
} symbol_t;

void read_symbols(void);
symbol_t* find_symbol(size_t idx);

#endif /* _SYMBOLS_H_ */
