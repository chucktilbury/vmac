#ifndef _STACK_H_
#define _STACK_H_

#include <stdint.h>
#include "vm_common.h"

typedef struct _stack_t {
    int64_t* buffer;
    uint32_t cap;
} stack_t;

extern stack_t* vm_stack;

static inline void push_stack(int64_t val) {

    if(REG(REG_SP) + 1 > vm_stack->cap) {
        vm_stack->cap <<= 1;
        vm_stack->buffer = _REALLOC_ARRAY(vm_stack->buffer, int64_t, vm_stack->cap);
    }

    vm_stack->buffer[REG(REG_SP)] = val;
    REG(REG_SP)++;
}

static inline int64_t pop_stack(void) {

    if(REG(REG_SP) > 0) {
        REG(REG_SP)--;
        return vm_stack->buffer[REG(REG_SP)];
    }
    else
        error("stack underrun in pop_vm_stack()");

    return 0; // cannot happen because error() does not return
}

static inline int64_t peek_stack(void) {

    if(REG(REG_SP) > 0)
        return vm_stack->buffer[REG(REG_SP) - 1];
    else
        error("stack underrun in peek_vm_stack()");

    return 0; // cannot happen
}

#endif /* _STACK_H_ */
