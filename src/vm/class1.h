#ifndef _CLASS1_H_
#define _CLASS1_H_

#include "vm_common.h"
#include "operands.h"

_Pragma("clang diagnostic push")
_Pragma("clang diagnostic ignored \"-Wimplicit-function-declaration\"")

/*
    All instructions have a register followed by 2 generic operands.
*/

static inline void _add(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _sub(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _mul(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _div(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _mod(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _addu(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _subu(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _mulu(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _divu(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _modu(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _and(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _or(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

static inline void _xor(void) {
    opcode_t reg = _fetch_8();
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

_Pragma("clang diagnostic pop")

#endif /* _CLASS1_H_ */
