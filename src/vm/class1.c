
#include "vm_common.h"
#include "operands.h"

enum {
    OPER_ADD,
    OPER_SUB,
    OPER_MUL,
    OPER_DIV,
    OPER_MOD,
    OPER_UADD,
    OPER_USUB,
    OPER_UMUL,
    OPER_UDIV,
    OPER_AND,
    OPER_OR,
    OPER_XOR,
};



static inline void operate(uint8_t oper, uint8_t reg, operand_t* left, operand_t* right) {

}

void _add(void) {
    operate(OPER_ADD, _fetch_8(), _fetch_operand(), _fetch_operand());
    // opcode_t reg = _fetch_8();
    // operand_t* left = _fetch_operand();
    // operand_t* right = _fetch_operand();
}

void _sub(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _mul(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _div(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _mod(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _addu(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _subu(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _mulu(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _divu(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _modu(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _and(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _or(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}

void _xor(void) {
    opcode_t reg = _fetch_8();
    operand_t* left = _fetch_operand();
    operand_t* right = _fetch_operand();
}
