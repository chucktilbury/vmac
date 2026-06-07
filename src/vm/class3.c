
#include "vm_common.h"
#include "operands.h"

void _inc(void) {
    opcode_t reg = _fetch_8();
    REG(reg)++;
}

void _dec(void) {
    opcode_t reg = _fetch_8();
    REG(reg)++;
}

void _incu(void) {
    opcode_t reg = _fetch_8();
    REG(reg)++;
}

void _decu(void) {
    opcode_t reg = _fetch_8();
    REG(reg)--;
}

void _not(void) {
    opcode_t reg = _fetch_8();
    REG(reg) = ~(uint64_t)REG(reg);
}
