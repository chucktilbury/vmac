# NOTES

* All registers and data slots are uint64_t.
* All code addresses are int32_t.

## Operand format
Operands are embedded in the instruction stream as part of the instruction definition. Only ``LOAD`` and ``STOR`` instructions use operands. All other instructions operate on registers, except for the "special" instructions that operate on external libraries. They have the format of ``byte:type, value`` where the size of the data is given by the type. The value is a packed union of the type of the value.

* Literal numbers can be stored in the instruction stream as signed or unsigned of 8, 16, 32, of 64 bits. A float is 64 bits.
    * ``type:byte, value:variable``
    * The size of the variable is given by the type of the operand.
    * Note that floats are not operated on directly by the VM. The ability to load and store them is implemented more for external libraries to use.
* An anonymous string is stored in the data area without a name. So it cannot be accessed again beyond this instruction.
    * ``type:byte, value:data index``
* A data symbol implies a data address.  This is encoded when the assembler finds a name as the operand.
    * ``type:byte, size:byte, value:variable``
    * The size byte indicates the size of the value, which is stored in the instruction stream.
* Register is the actual data in the register.
    * Registers include the SP or the IP register on read (STOR) operations.
    * The IP register cannot be written directly. The assembler will refuse to assemble it.
    * ``type:byte, reg:byte``
* Indirect register is always the address of an element in the data area.
    * ``type:byte, reg:byte``
* An indexed register holds the address of a data element, which is indexed by a register. The register holds the index of the element in bytes. The index arithmetic is based on the fact that the data store is composed of register sized words. For example, a string cannot be accessed directly without shifting bytes around.
    * ``type:byte, reg:byte, index_type``
        * index_type == register? register: literal number

## Data storage format
The data store is very simple. It is composed of register-sized words. These words, same as registers, are bit fields, not numbers, so they are codified as unsigned. Type information is lost once it is stored in the data store. It is assumed that the developer is keeping track of the types of objects in the data store.

* NOTE that defining data elements by type does not make sense. The assembler needs to have the ability to properly store data in this contiguous array of words.

### Strings
Strings are allocated to the data store as contiguous words. The first 16 bits are the length of the string in bytes. The actual string data is packed into the following words as in-order bytes. Strings cannot be accessed by the VM directly. This is intended more for external libraries.

## Opcode definition
```
    // CLASS1
    // reg, operand
    // operand can be:
    //  literal number (incl float)
    //  anonymous string
    //  address of a data symbol
    //  register
    //  indirect register
    //  indexed register
    OP_LOAD = 0xC5,

    // CLASS2
    // operand, reg
    // operand can be
    //  a data symbol
    //  register
    //  indirect register
    //  indexed register
    OP_STOR = 0xC6,

    // CLASS3
    // reg, reg, reg
    // destination, left operand, right operand
    OP_ADD = 0xC7,
    OP_SUB = 0xC8,
    OP_MUL = 0xC9,
    OP_DIV = 0xCA,
    OP_MOD = 0xCB,
    OP_ADDU = 0xCC,
    OP_SUBU = 0xCD,
    OP_MULU = 0xCE,
    OP_DIVU = 0xCF,
    OP_MODU = 0xD0,
    OP_AND = 0xD1,
    OP_OR = 0xD2,
    OP_XOR = 0xD3,

    // CLASS4
    // reg, reg
    // left operand, right operand
    OP_EQU = 0xD4,
    OP_EQUU = 0xD5,
    OP_NEQ = 0xD6,
    OP_NEQU = 0xD7,
    OP_LT = 0xD8,
    OP_LTU = 0xD9,
    OP_GT = 0xDA,
    OP_GTU = 0xDB,
    OP_LTE = 0xDC,
    OP_LTEU = 0xDD,
    OP_GTE = 0xDE,
    OP_GTEU = 0xDF,

    // CLASS5 (one register)
    // reg
    //  relative signed value in a register
    //      even values are relative reg
    //      odd values are absolute code label
    OP_JMP = 0xE0,
    OP_JMPV = 0xE1,
    OP_JMPT = 0xE2,
    OP_JMPVT = 0xE3,
    OP_JMPF = 0xE4,
    OP_JMPVF = 0xE5,
    OP_CALL = 0xE6,
    OP_CALLV = 0xE7,
    OP_CALLT = 0xE8,
    OP_CALLVT = 0xE9,
    OP_CALLF = 0xEA,
    OP_CALLVF = 0xEB,

    // value in a register
    OP_PUSH = 0xEC,
    OP_POP = 0xED,
    OP_INC = 0xEE,
    OP_DEC = 0xEF,
    OP_INCU = 0xF0,
    OP_DECU = 0xF1,
    OP_NOT = 0xF2,

    // CLASS6
    // reg, byte
    OP_SHL = 0xF3,
    OP_SHR = 0xF4,

    // CLASS7
    // no operands
    OP_RET = 0xF5,
    OP_RETT = 0xF6,
    OP_RETF = 0xF7,
    OP_CLRT = 0xF8,
    OP_SETT = 0xF9,
    OP_EXIT = 0xFA,
    OP_ABORT = 0xFB,
    OP_NOP = 0xFC,
    OP_BREAK = 0xFD,

    // CLASS8
    // anon string operands
    OP_EXTERN = 0xFE,
    OP_LINK = 0xFF,

```

