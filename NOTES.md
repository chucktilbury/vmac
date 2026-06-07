# NOTES
Design notes that could change a lot.

## General
* All registers and data slots are uint64_t.
    * These are treated as bit fields, not numbers.
* All code addresses are int32_t.
    * Signed because relative addresses could be negative.
    * Addresses are the byte index in the code buffer.
* All data addresses are uint32_t.
    * Unsigned because data addresses can never be negative.
    * A data address is the index of the byte where the word exists in the ``byte_buffer_t``, not the index of the word.

## Operand format
Operands are embedded in the instruction stream as part of the instruction definition. Only ``LOAD`` and ``STOR`` instructions use operands. All other instructions operate on registers, except for the "special" instructions that operate on external libraries. They have the format of ``byte:type, value`` where the size of the data is given by the type. The value is a packed union of the type of the value.

* Literal numbers can be stored in the instruction stream as signed or unsigned of 8, 16, 32, of 64 bits. A float is 64 bits.
    * ``type:uint8_t, value:variable``
    * The size of the variable is given by the type of the operand.
    * Note that floats are not operated on directly by the VM. The ability to load and store them is implemented more for external libraries to use.
* An anonymous string is stored in the data area without a name. So it cannot be accessed again beyond this instruction.
    * ``type:byte, value:int32_t``
* A data symbol implies a data address.  This is encoded when the assembler finds a name as the operand.
    * ``type:uint8_t, size:uint8_t, value:variable``
    * The size byte indicates the size of the value, which is stored in the instruction stream.
* Register is the actual data in the register.
    * Registers include the SP or the IP register on read (STOR) operations.
    * The IP register cannot be written directly. The assembler will refuse to assemble it.
    * ``type:uint8_t, reg:uint8_t``
* Indirect register is always the address of an element in the data area.
    * ``type:uint8_t, reg:uint8_t``
* An indexed register holds the address of a data element, which is indexed by a register. The register holds the index of the element in bytes. The index arithmetic is based on the fact that the data store is composed of register sized words. For example, a string cannot be accessed directly without shifting bytes around.
    * ``type:uint8_t, reg:uint8_t, index_type``
        * index_type == register? int8_t: uint32_t

### Operand type definitions
Note that the definitions for OPER_ARRAY and OPER_ILABEL have been removed. See above.
```
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

```

## Data storage format
The data store is very simple. It is composed of register-sized words. These words, same as registers, are bit fields, not numbers, so they are codified as unsigned. Type information is lost once it is stored in the data store. It is assumed that the developer is keeping track of the types of objects in the data store.

* NOTE that defining data elements by type does not make sense. The assembler needs to have the ability to properly store data in this contiguous array of words.

### Strings
Strings are allocated to the data store as contiguous words. The first 16 bits are the length of the string in bytes. The actual string data is packed into the following words as in-order bytes. Strings cannot be accessed by the VM directly. This is intended more for external libraries.

## Opcode definition
These are the actual instructions with their class. Instructions are classed by the operands they accept.

```
    // CLASS0
    // These instructions/operations are likely to change over time.
    // opcode, operand
    // anon string operands
    OP_EXTERN = 0xC5,
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

```

