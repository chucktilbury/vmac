#ifndef _CLASS7_H_
#define _CLASS7_H_

#include "vm_common.h"
#include "operands.h"

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wimplicit-function-declaration\"")

static inline void _ret(void) {
}

static inline void _rett(void) {
}

static inline void _retf(void) {
}

static inline void _clrt(void) {
    CLR_TRUE_FLAG;
}

static inline void _sett(void) {
    SET_TRUE_FLAG;
}

static inline void _exit(void) {
}

static inline void _abort(void) {
}

static inline void _nop(void) {
}

static inline void _break(void) {
}

_Pragma("clang diagnostic pop")

#endif /* _CLASS7_H_ */
