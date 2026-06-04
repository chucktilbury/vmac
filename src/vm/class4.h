#ifndef _CLASS4_H_
#define _CLASS4_H_

#include "vm_common.h"
#include "operands.h"

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wimplicit-function-declaration\"")

static inline void _mov(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _equ(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _equu(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _neq(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _nequ(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _lt(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _ltu(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _gt(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _gtu(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _lte(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _lteu(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _gte(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _gteu(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

_Pragma("clang diagnostic pop")

#endif /* _CLASS4_H_ */
