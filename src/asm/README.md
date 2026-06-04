#ASM
This is a simple assembler for the virtual machine. It is intended that the macro processor will be run on the input before this program is executed. It outputs a binary file for the VM to run.

## General format of input
The input to the assembler is basically free-form. Spaces and line feeds are generally ignored. A data definition can appear anywhere in the source code, as well as instructions. Data definitions are always placed in the data store in the order in which they are encountered, same as instructions. The macro processor is used to include source code from other files and all is processed in a single pass to produce a single binary which can be loaded by the VM. When the binary is emitted, all names and type information are lost, converted to literal offsets and placed in the data or code segments as required. See ``parser.y`` for the full grammar.

See the macro processor documentation for more information about how it works. In general both single and multi-line C comments are supported. Relevant macro directives are ``.include``, ``.define``, ``.if and .else``, ``.error``, and ``.message``.

## Memory Model
The memory model is very simple. There is a data store and an instruction store, which are kept in separate areas. Addresses are simple indexes into the space.

## Registers
The registers are all C unsigned longs.

### General purpose registers
* There are 32 general purpose registers and all of them support the same operations. Labeled ``R0 - R31``.
* A separate program counter is accessible read-only by VM instructions, but can only be updated with flow-control instructions. (and indirect access)
* The stack pointer register is automatically updated as a result of ``PUSH``, ``POP``, ``CALL``, and others. This register can be read or written by VM instructions. The stack grows as required. If the stack pointer wraps zero then a "stack underflow" exception is thrown.

### Flags register
* Single bit register that is the "true" register. When a logical comparison instruction is encountered, this register is set or cleared according to the result. This register can also be set or cleared explicitly.

## Instructions
Instructions that are data specific are automatically encoded by the assembler. For example, instructions that access registers, data, or the stack. All instructions are encoded into a single byte. Additional bytes follow to describe parameters such as registers and inline literal data. Many instructions have similar parameter requirements and no description byte is required.

### Standard operands
Most instruction accept the standard operands. They are encoded in a half byte after the instruction. If there is one operand, then the low 4 bits are used. If there are 2 operands, then the second operand is encoded into the upper 4 bits.

```
no_parameter = 0x00
register = 0x01    // register contains a literal value
iregister = 0x02   // register contains an index into the data store
// Note that literal SP and IP register designations never appear in the
// instruction stream.
SP = 0x03          // refers to the value of the stack pointer
dSP = 0x04         // value in the SP register is a data store index
reserved = 0x05
reserved = 0x06
reserved = 0x07
// The parser decides what the value will fit into and whether it's
// signed or not.
LITERAL_INT8 = 0x08
LITERAL_INT16 = 0x09
LITERAL_INT32 = 0x0A
LITERAL_INT64 = 0x0B
LITERAL_UINT8 = 0x0C
LITERAL_UINT16 = 0x0D
LITERAL_UINT32 = 0x0E
LITERAL_UINT64 = 0x0F

examples:
MOV R16, -12 // 0xC6, 0x18, 0x10, 0xFC (OP, descriptor, R16, literal data)
ADD R18, R14, #SP // 0xCA, 0x12, 0x14 (OP, R18, descriptor)
GTU R17,R0 // 0xE5 0x11 0x41 0x00 (OP, descriptor, R18, R0)
MUL R0,R12,R17 // 0xCC 0x00 0x11 0x0C 0x15 (OP, R0, descriptor, R12, R17)
```

### Class 1 instructions
* ``ADD register, operand, operand``
* ``SUB register, operand, operand``
* ``MUL register, operand, operand``
* ``DIV register, operand, operand``
* ``MOD register, operand, operand``
* ``ADDU register, operand, operand``
* ``SUBU register, operand, operand``
* ``MULU register, operand, operand``
* ``DIVU register, operand, operand``
* ``MODU register, operand, operand``
* ``AND register, operand, operand``
* ``OR register, operand, operand``
* ``XOR register, operand, operand``

### Class 2 instructions
* ``SHL register, operand, UINT8``
* ``SHR register, operand, UINT8``

### Class 3 instructions
* ``INC register, operand``
* ``DEC register, operand``
* ``INCU register, operand``
* ``DECU register, operand``
* ``NOT register, operand``


### Class 4 instructions
* ``MOV operand, operand``
* ``EQU operand, operand``
* ``EQUU operand, operand``
* ``NEQ operand, operand``
* ``NEQU operand, operand``
* ``LT operand, operand``
* ``LTU operand, operand``
* ``GT operand, operand``
* ``GTU operand, operand``
* ``LTE operand, operand``
* ``LTEU operand, operand``
* ``GTE operand, operand``
* ``GTEU operand, operand``

### Class 5 instructions
* ``JMP operand``
* ``JMPT operand``
* ``JMPF operand``
* ``JMPR operand``
* ``JMPRT operand``
* ``JMPRF operand``
* ``CALL operand``
* ``CALLT operand``
* ``CALLF operand``
* ``CALLR operand``
* ``CALLRT operand``
* ``CALLRF operand``
* ``PUSH operand``

### Class 6 instructions
* ``POP register``

### Class 7 instructions
* ``RET``
* ``RETT``
* ``RETF``
* ``CLRT``
* ``SETT``
* ``EXIT``
* ``ABORT``
* ``NOP``

### Class 8 instructions
* ``EXTERN string``
* ``LOAD string``
