#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include "string_buffer.h"
#include <stdbool.h>

typedef struct parm_t {
    string_t* name;
    string_t* repl;
} parm_t;

typedef struct parm_list_t {
    parm_t** lst;
    int cap;
    int len;
} parm_list_t;

typedef struct symbol_t {
    string_t* tag;
    parm_list_t* plist;
    string_t* repl_text;
    int arity;
    int line;
    int col;
    string_t* fname;
    struct symbol_t* left;
    struct symbol_t* right;
} symbol_t;

symbol_t* create_symbol(string_t* tag);
void destroy_sym_table(void);

symbol_t* insert_symbol(string_t* tag);
symbol_t* find_symbol(string_t* tag);
string_t* get_parm(symbol_t* sym, string_t* name);
bool parm_exists(symbol_t* sym, string_t* name);

void dump_symbol_table(void);

#endif /* _SYMBOLS_H_ */
