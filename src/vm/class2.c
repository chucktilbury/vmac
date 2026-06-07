
#include "vm_common.h"
#include "operands.h"

void _shl(void) {
    opcode_t reg = _fetch_8();
    uint8_t byte = _fetch_8();
}

void _shr(void) {
    opcode_t reg = _fetch_8();
    uint8_t byte = _fetch_8();
}
