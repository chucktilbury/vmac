
#include "common.h"
#include "operands.h"
#include "emit.h"

operand_t* create_operand(opcode_t type) {

    operand_t* op = _ALLOC_TYPE(operand_t);
    op->type = type;
    op->section = SEC_NONE;

    memset(&(op->value), 0, sizeof(op->value));

    return op;
}

void destroy_operand(operand_t* op) {

    if(op != NULL) {
        if(op->type == OPERAND_STRING && op->value.str != NULL)
            _FREE(op->value.str);
        _FREE(op);
    }
}

operand_list_t* create_operand_list(void) {

    operand_list_t* ptr = _ALLOC_TYPE(operand_list_t);
    ptr->cap = 0x01 << 3;
    ptr->len = 0;
    ptr->buffer = _ALLOC_ARRAY(operand_t*, ptr->cap);

    return ptr;
}

void destroy_operand_list(operand_list_t* ptr) {

    if(ptr != NULL) {
        for(size_t i = 0; i < ptr->len; i++)
            destroy_operand(ptr->buffer[i]);
        _FREE(ptr->buffer);
        _FREE(ptr);
    }
}

void add_operand_list(operand_list_t* lst, operand_t* op) {

    if(lst->len + 1 >= lst->cap) {
        lst->cap <<= 1;
        lst->buffer = _REALLOC_ARRAY(lst->buffer, operand_t*, lst->cap);
    }

    lst->buffer[lst->len] = op;
    lst->len++;
}

void clear_operand_list(operand_list_t* ptr) {

    for(size_t i = 0; i < ptr->len; i++)
        destroy_operand(ptr->buffer[i]);
    ptr->len = 0;
}

operand_t* iterate_operand_list(operand_list_t* lst, size_t* mark) {

    if(*mark < lst->len) {
        operand_t* op = lst->buffer[*mark];
        *mark = *mark + 1;
        return op;
    }
    return NULL;
}

