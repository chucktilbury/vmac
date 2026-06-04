#ifndef _CLASS3_H_
#define _CLASS3_H_

#include "vm_common.h"
#include "operands.h"

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wimplicit-function-declaration\"")

static inline void _inc(void) {
    opcode_t reg = _fetch_8();
    REG(reg)++;
}

static inline void _dec(void) {
    opcode_t reg = _fetch_8();
    REG(reg)++;
}

static inline void _incu(void) {
    opcode_t reg = _fetch_8();
    REG(reg)++;
}

static inline void _decu(void) {
    opcode_t reg = _fetch_8();
    REG(reg)--;
}

static inline void _not(void) {
    opcode_t reg = _fetch_8();
    REG(reg) = ~(uint64_t)REG(reg);
}

_Pragma("clang diagnostic pop")

#endif /* _CLASS3_H_ */
