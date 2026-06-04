
#include "vm_common.h"

#include "stack.h"

stack_t* vm_stack = NULL;

void create_stack(void) {

    vm_stack = _ALLOC_TYPE(stack_t);
    vm_stack->cap = 0x01 << 3;
    vm_stack->buffer = _ALLOC_ARRAY(int64_t, vm_stack->cap);
}

void destroy_stack(void) {

    if(vm_stack != NULL) {
        _FREE(vm_stack->buffer);
        _FREE(vm_stack);
    }
}
