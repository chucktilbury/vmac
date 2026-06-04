#ifndef _CLASS2_H_
#define _CLASS2_H_

#include "vm_common.h"
#include "operands.h"

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wimplicit-function-declaration\"")

static inline void _shl(void) {
    opcode_t reg = _fetch_8();
    uint8_t byte = _fetch_8();
}

static inline void _shr(void) {
    opcode_t reg = _fetch_8();
    uint8_t byte = _fetch_8();
}

_Pragma("clang diagnostic pop")

#endif /* _CLASS2_H_ */
