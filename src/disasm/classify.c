
#include "common.h"
#include "classify.h"

inst_class_t classify_instruction(opcode_t op) {

    switch(op) {
        // instructions that require exactly 3 operands and the first
        // must be a register.
        case OP_ADD:
        case OP_SUB:
        case OP_MUL:
        case OP_DIV:
        case OP_MOD:
        case OP_ADDU:
        case OP_SUBU:
        case OP_MULU:
        case OP_DIVU:
        case OP_MODU:
        case OP_AND:
        case OP_OR:
        case OP_XOR:
            return CLASS_1;

        // instructions that require exactly 3 operands. The first one must
        // be a register and the last one must be a UINT8 or an INT8
        case OP_SHL:
        case OP_SHR:
            return CLASS_2;

        // instructions that require exactly 2 operands and the first one
        // must be a register.
        case OP_INC:
        case OP_DEC:
        case OP_INCU:
        case OP_DECU:
        case OP_NOT:
            return CLASS_3;

        // instructions that require exactly 2 general operands
        case OP_MOV:
        case OP_EQU:
        case OP_EQUU:
        case OP_NEQ:
        case OP_NEQU:
        case OP_LT:
        case OP_LTU:
        case OP_GT:
        case OP_GTU:
        case OP_LTE:
        case OP_LTEU:
        case OP_GTE:
        case OP_GTEU:
            return CLASS_4;

        // instructions that require exactly one operand. If the operand is
        // a name, then it must be a code label.
        case OP_JMP:
        case OP_JMPT:
        case OP_JMPF:
        case OP_JMPR:
        case OP_JMPRT:
        case OP_JMPRF:
        case OP_CALL:
        case OP_CALLT:
        case OP_CALLF:
        case OP_CALLR:
        case OP_CALLRT:
        case OP_CALLRF:
            return CLASS_5;

        // Exactly one operand that must be a register.
        case OP_PUSH:
        case OP_POP:
            return CLASS_6;

        // No operands.
        case OP_RET:
        case OP_RETT:
        case OP_RETF:
        case OP_CLRT:
        case OP_SETT:
        case OP_EXIT:
        case OP_ABORT:
        case OP_NOP:
            return CLASS_7;

        // One operand that must be an index to a quoted string. May
        // be anonymous.
        case OP_EXTERN:
        case OP_LOAD:
            return CLASS_8;

        default:
            error("expected an instruction but got %s", opcode_to_str(op));
    }

    return 256;
}

