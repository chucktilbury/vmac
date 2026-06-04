#ifndef _CLASS5_H_
#define _CLASS5_H_

#include "vm_common.h"
#include "operands.h"

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wimplicit-function-declaration\"")

static inline void _jmp(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _jmpt(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _jmpf(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _jmpr(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _jmprt(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _jmprf(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _call(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _callt(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _callf(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _callr(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _callrt(void) {
    operand_t* oper = _fetch_operand();
}

static inline void _callrf(void) {
    operand_t* oper = _fetch_operand();
}

_Pragma("clang diagnostic pop")

#endif /* _CLASS5_H_ */
