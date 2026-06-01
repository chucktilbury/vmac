#ifndef _OPERANDS_H_
#define _OPERANDS_H_

#include <stddef.h>
#include <stdint.h>
#include "opcodes.h"

typedef struct _operand_t {
    opcode_t type;
    opcode_t section;
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

typedef struct _operand_list_t {
    operand_t** buffer;
    size_t cap;
    size_t len;
} operand_list_t;

operand_t* create_operand(opcode_t type);
void destroy_operand(operand_t* op);

operand_list_t* create_operand_list(void);
void destroy_operand_list(operand_list_t* lst);
void add_operand_list(operand_list_t* lst, operand_t* op);
void clear_operand_list(operand_list_t* lst);
operand_t* iterate_operand_list(operand_list_t* lst, size_t* mark);


#endif /* _OPERANDS_H_ */
