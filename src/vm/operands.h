#ifndef _OPERANDS_H_
#define _OPERANDS_H_

#include <stdint.h>
#include "common.h"
#include "opcodes.h"
#include "fetch.h"

typedef struct _operand_t {
    opcode_t type;
    uint32_t index;
    union {
        uint8_t opcode;
        const char* str;
        int8_t inum8;
        uint8_t unum8;
        int16_t inum16;
        uint16_t unum16;
        int32_t inum32;
        uint32_t unum32;
        int64_t inum64;
        uint64_t unum64;
        double fnum;
    } __attribute__((packed)) value;
} operand_t;

static inline operand_t* _fetch_operand(void) {

    operand_t* oper = _ALLOC_TYPE(operand_t);
    oper->type = _fetch_8();
    switch(oper->type) {
        case OPERAND_INT8:
            oper->value.inum8 = (int8_t)_fetch_8();
            break;
        case OPERAND_INT16:
            oper->value.inum16 = (int16_t)_fetch_16();
            break;
        case OPERAND_INT32:
            oper->value.inum32 = (int32_t)_fetch_32();
            break;
        case OPERAND_INT64:
            oper->value.inum64 = (int64_t)_fetch_64();
            break;
        case OPERAND_UINT8:
            oper->value.unum8 = _fetch_8();
            break;
        case OPERAND_UINT16:
            oper->value.unum16 = _fetch_16();
            break;
        case OPERAND_UINT32:
            oper->value.unum32 = _fetch_32();
            break;
        case OPERAND_UINT64:
            oper->value.unum64 = _fetch_64();
            break;
        case OPERAND_REG:
        case OPERAND_IREG:
            oper->value.opcode = _fetch_8();
            break;
        case OPERAND_FLOAT: {
                uint64_t tmp = _fetch_64();
                oper->value.unum64 = *((double*)(&tmp));
            }
            break;
        case OPERAND_LABEL: {
                uint32_t idx = _fetch_32();
                if(idx & 0x01) {
                    // operand referrs to data
                }
                else {
                    // operand referrs to code
                }
            }
            break;
        case OPERAND_ILABEL: {
                uint32_t idx = _fetch_32();
                if(idx & 0x01) {
                    // operand referrs to data
                }
                else {
                    // operand referrs to code
                }
            }
            break;
        case OPERAND_STRING:
            break;
        default:
            error("unknown operand type: %s", opcode_to_str(oper->type));

    }
    return oper;
}

#endif /* _OPERANDS_H_ */
