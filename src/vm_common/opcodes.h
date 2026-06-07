#ifndef _OPCODES_H_
#define _OPCODES_H_

#define MAGIC_NUMBER 0xF02DEDEADBEEF000
#define SEPARATOR 0xFFFFFFFFFFFFFFFF

typedef enum _opcode_t {
    // register encodings
    REG_R00 = 0x00,
    REG_R01 = 0x01,
    REG_R02 = 0x02,
    REG_R03 = 0x03,
    REG_R04 = 0x04,
    REG_R05 = 0x05,
    REG_R06 = 0x06,
    REG_R07 = 0x07,
    REG_R08 = 0x08,
    REG_R09 = 0x09,
    REG_R10 = 0x0A,
    REG_R11 = 0x0B,
    REG_R12 = 0x0C,
    REG_R13 = 0x0D,
    REG_R14 = 0x0E,
    REG_R15 = 0x0F,
    REG_R16 = 0x10,
    REG_R17 = 0x11,
    REG_R18 = 0x12,
    REG_R19 = 0x13,
    REG_R20 = 0x14,
    REG_R21 = 0x15,
    REG_R22 = 0x16,
    REG_R23 = 0x17,
    REG_R24 = 0x18,
    REG_R25 = 0x19,
    REG_R26 = 0x1A,
    REG_R27 = 0x1B,
    REG_R28 = 0x1C,
    REG_R29 = 0x1D,
    REG_R30 = 0x1E,
    REG_R31 = 0x1F,
    REG_SP = 0x20,
    REG_IP = 0x21,
    REG_FLAGS = 0x22,
    MAX_REGS = 0x23,

    // relative registers
    REG_IR00 = 0x30,
    REG_IR01 = 0x31,
    REG_IR02 = 0x32,
    REG_IR03 = 0x33,
    REG_IR04 = 0x34,
    REG_IR05 = 0x35,
    REG_IR06 = 0x36,
    REG_IR07 = 0x37,
    REG_IR08 = 0x38,
    REG_IR09 = 0x39,
    REG_IR10 = 0x3A,
    REG_IR11 = 0x3B,
    REG_IR12 = 0x3C,
    REG_IR13 = 0x3D,
    REG_IR14 = 0x3E,
    REG_IR15 = 0x3F,
    REG_IR16 = 0x40,
    REG_IR17 = 0x41,
    REG_IR18 = 0x42,
    REG_IR19 = 0x43,
    REG_IR20 = 0x44,
    REG_IR21 = 0x45,
    REG_IR22 = 0x46,
    REG_IR23 = 0x47,
    REG_IR24 = 0x48,
    REG_IR25 = 0x49,
    REG_IR26 = 0x4A,
    REG_IR27 = 0x4B,
    REG_IR28 = 0x4C,
    REG_IR29 = 0x4D,
    REG_IR30 = 0x4E,
    REG_IR31 = 0x4F,
    REG_ISP = 0x50,
    REG_IIP = 0x51,

    // operand types
    // literal numbers
    OPER_INT8 = 0x60,
    OPER_INT16 = 0x61,
    OPER_INT32 = 0x62,
    OPER_INT64 = 0x63,
    OPER_UINT8 = 0x64,
    OPER_UINT16 = 0x65,
    OPER_UINT32 = 0x66,
    OPER_UINT64 = 0x67,
    OPER_FLOAT = 0x68,
    // registers
    OPER_REG = 0x69,
    OPER_IREG = 0x6A, // Indirect
    OPER_XREG = 0x6B, // indeXed
    // others
    OPER_STR = 0x6C,
    OPER_LABEL = 0x6D,

    // section designator
    SEC_NONE = 0x70,
    SEC_CODE = 0x71,
    SEC_DATA = 0x72,

    MIN_INSTRUCTION = 0xC5,
    // CLASS0
    // These instructions/operations are likely to change over time.
    // opcode, operand
    // anon string operands
    // call an external function
    OP_EXTERN = 0xC5,
    // load an external library
    OP_LINK = 0xC6,

    // CLASS1
    // opcode, reg, operand
    // operand can be:
    //  literal number (incl float)
    //  anonymous string
    //  address of a data symbol
    //  register
    //  indirect register
    //  indexed register
    OP_LOAD = 0xC7,

    // CLASS2
    // opcode, operand, reg
    // operand can be
    //  a data symbol
    //  register
    //  indirect register
    //  indexed register
    OP_STOR = 0xC8,

    // CLASS3
    // opcode, reg, reg, reg
    // destination, left operand, right operand
    //      even numbers represent signed operations
    //      odd numbers represent unsigned
    OP_ADD = 0xC9,
    OP_ADDU = 0xCA,
    OP_SUB = 0xCB,
    OP_SUBU = 0xCC,
    OP_MUL = 0xCD,
    OP_MULU = 0xCE,
    OP_DIV = 0xCF,
    OP_DIVU = 0xD0,
    OP_MOD = 0xD1,
    OP_MODU = 0xD2,
    OP_AND = 0xD3,
    OP_OR = 0xD4,
    OP_XOR = 0xD5,

    // CLASS4
    // opcode, reg, reg
    // left operand, right operand
    //      even numbers represent signed operations
    //      odd numbers represent unsigned
    OP_EQU = 0xD6,
    OP_EQUU = 0xD7,
    OP_NEQ = 0xD8,
    OP_NEQU = 0xD9,
    OP_LT = 0xDA,
    OP_LTU = 0xDB,
    OP_GT = 0xDC,
    OP_GTU = 0xDD,
    OP_LTE = 0xDE,
    OP_LTEU = 0xDF,
    OP_GTE = 0xE0,
    OP_GTEU = 0xE1,

    // CLASS5 (one register)
    // opcode, reg
    //  relative signed value in a register
    //      even values are relative reg
    //      odd values are absolute code label
    OP_JMP = 0xE2,
    OP_JMPA = 0xE3,
    OP_JMPT = 0xE4,
    OP_JMPAT = 0xE5,
    OP_JMPF = 0xE6,
    OP_JMPAF = 0xE7,
    OP_CALL = 0xE8,
    OP_CALLA = 0xE9,
    OP_CALLT = 0xEA,
    OP_CALLAT = 0xEB,
    OP_CALLF = 0xEC,
    OP_CALLAF = 0xED,

    // value in a register
    OP_PUSH = 0xEE,
    OP_POP = 0xEF,
    OP_INC = 0xF0,
    OP_DEC = 0xF1,
    OP_INCU = 0xF2,
    OP_DECU = 0xF3,
    OP_NOT = 0xF4,

    // CLASS6
    // opcode, reg, byte
    OP_SHL = 0xF5,
    OP_SHR = 0xF6,

    // CLASS7
    // opcode
    // no operands
    OP_BREAK = 0xF7,
    OP_RET = 0xF8,
    OP_RETT = 0xF9,
    OP_RETF = 0xFA,
    OP_CLRT = 0xFB,
    OP_SETT = 0xFC,
    OP_EXIT = 0xFD,
    OP_ABORT = 0xFE,
    OP_NOP = 0xFF,
    MAX_INSTRUCTION = 0xFF,

} opcode_t;

#define INSTR_IDX(v) ((v)-MIN_INSTRUCTION)
#define VALIDATE_INSTR(i) do { \
        if(INSTR_IDX(i) < MIN_INSTRUCTION || INSTR_IDX(i) > MAX_INSTRUCTION) { \
            error("invalid instruction at 0x%08X: 0x%02X", i, IP_REG); \
        } \
    } while(false)
const char* opcode_to_str(opcode_t type);

#endif /* _OPCODES_H_ */
