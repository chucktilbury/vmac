
#include "common.h"
#include "symbols.h"

byte_buffer_t* debug_buffer;
extern symbol_t* sym_table;

static void _traverse(symbol_t* node) {

    if(node != NULL) {
        _traverse(node->right);
        _traverse(node->left);

        write_byte_buffer_uint8(debug_buffer, node->type);
        write_byte_buffer_uint32(debug_buffer, node->index);
        write_byte_buffer_uint16(debug_buffer, (uint16_t)strlen(node->tag) + 1);
        write_byte_buffer_str(debug_buffer, node->tag);
    }
}

void emit_debug_buffer(void) {

    debug_buffer = create_byte_buffer();
    _traverse(sym_table);
}
