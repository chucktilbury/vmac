#ifndef _CLASS6_H_
#define _CLASS6_H_

#include "vm_common.h"
#include "operands.h"

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wimplicit-function-declaration\"")

static inline void _push(void) {
    opcode_t reg = _fetch_8();
}

static inline void _pop(void) {
    opcode_t reg = _fetch_8();
}

_Pragma("clang diagnostic pop")

#endif /* _CLASS6_H_ */
