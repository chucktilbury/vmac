#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include "string_buffer.h"
#include <stdbool.h>
#include <stdint.h>
#include "opcodes.h"

typedef enum _symbol_section_t {
    SYM_CODE,
    SYM_DATA,
} symbol_section_t;

typedef struct symbol_t {
    opcode_t section;
    opcode_t type;
    const char* tag;
    uint32_t index;
    struct symbol_t* left;
    struct symbol_t* right;
} symbol_t;

symbol_t* create_symbol(const char* tag, opcode_t section, opcode_t type, uint32_t index);
void destroy_sym_table(void);

symbol_t* insert_symbol(const char* tag, opcode_t section, opcode_t type, uint32_t index);
symbol_t* find_symbol(const char* tag);

void dump_symbol_table(void);

#endif /* _SYMBOLS_H_ */
