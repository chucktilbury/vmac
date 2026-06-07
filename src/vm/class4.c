
#include "vm_common.h"
#include "operands.h"

void _mov(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _equ(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _equu(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _neq(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _nequ(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _lt(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _ltu(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _gt(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _gtu(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _lte(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _lteu(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _gte(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}

void _gteu(void) {
    operand_t* oper1 = _fetch_operand();
    operand_t* oper2 = _fetch_operand();
}
