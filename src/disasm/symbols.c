
#include "common.h"
#include "symbols.h"

extern byte_buffer_t* _debug;
symbol_t* stable = NULL;

static symbol_t* __find(symbol_t* root, uint32_t idx) {

    if(root->index == idx)
        return root;
    else if(root->index > idx) {
        if(root->right != NULL)
            return __find(root->right, idx);
        else
            return NULL;
    }
    else if(root->index < idx) {
        if(root->left != NULL)
            return __find(root->left, idx);
        else
            return NULL;
    }
    else
        return NULL;
}

/*
    add symbol by index
*/
static void __add(symbol_t* root, symbol_t* node) {

    if(root != NULL) {
        if(root->index > node->index) {
            if(root->right != NULL)
                __add(root->right, node);
            else
                root->right = node;
        }
        else if(root->index < node->index) {
            if(root->left != NULL)
                __add(root->left, node);
            else
                root->left = node;
        }
        // else it's a dupe. do not add
    }
}

static void _add_symbol(symbol_t* sym) {

    if(stable != NULL)
        __add(stable, sym);
    else
        stable = sym;
}

/*
    find the symbol by index
*/
symbol_t* find_symbol(size_t idx) {

    if(stable != NULL)
        return __find(stable, idx);
    else
        return NULL;
}

/*
    opcode_t type;
    opcode_t section
    uint32_t index;
    string_t* tag;
*/
void create_symbol(size_t* mark) {

    symbol_t* sym = _ALLOC_TYPE(symbol_t);
    sym->type = iterate_byte_buffer_uint8(_debug, mark);
    sym->index = iterate_byte_buffer_uint32(_debug, mark);
    uint16_t len = iterate_byte_buffer_uint16(_debug, mark);

    sym->tag = create_string(NULL);
    for(uint16_t i = 0; i < len; i++)
        append_string_char(sym->tag, iterate_byte_buffer_uint8(_debug, mark));

    TRACE("tag: %s", sym->tag->buffer);
    TRACE("string size = %d", len);
    TRACE("index: 0x%08X\n", sym->index);

    _add_symbol(sym);
}

void read_symbols(void) {

    ENTER;
    bool finished = false;
    size_t mark = 0;

    while(!finished) {
        create_symbol(&mark);
        if(mark >= _debug->len)
            finished = true;
    }
    RETURN();
}
