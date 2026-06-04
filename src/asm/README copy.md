#ASM
This is a simple assembler for the virtual machine. It is intended that the macro processor will be run on the input before this program is executed. It outputs a binary file for the VM to run.

## General format of input
The input to the assembler is basically free-form. A data definition can appear anywhere in the source code, as well as instructions. Data definitions are always placed in the data store in the order in which they are encountered, same as instructions. The macro processor is used to include source code from other files and all is processed in a single pass to produce a single binary which can be loaded by the VM. When the binary is emitted, all names and type information are lost, converted to literal offsets and placed in the data or code segments as required.

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
* Single bit over-flow register. Set when an arithmetic instructions when the operation produces a number that will is larger than will fit into the register. Cleared when an arithmetic operation does not do that.
* Single bit under-flow register. Set when an arithmetic operation wraps past zero. Cleared when an operation does not do that.

## Instructions
Instructions that are data specific are automatically encoded by the assembler. For example, instructions that access registers, data, or the stack. All instructions are encoded into a single byte that may have additional data encoded into the instruction stream.

The assembler understands data-specific instructions, but it is preferred to allow the assembler to choose which instruction to encode, based upon the parameters.


#Everything below this point is wrong....

### Instruction format
* Data movement instruction format: ``INST DEST,SRC``
* Unary instruction format: ``INST OPERAND``
* Binary instruction format: ``INST DEST,LEFT,RIGHT``

### Operand formats
An operand can have the literal value, or the literal value can be an offset into the data store. An offset is signified by the ``'#'`` character in the assembler.

### Data movement
The ``MOV`` instruction can access any register except the instruction pointer. Addresses into the data segment may be specified, but addresses into the instruction store are illegal and create an exception.

#### Generic form
* ``MOV DEST, SRC // The assembler will select the proper instruction based upon the operands.``

#### Data specific form
* ``MOVS REG, SP // copy the value of the SP into the REG``
* ``MOVLS REG, #SP // copy the value of the SP as an address in the data store into the REG``
* ``SMOV SP, REG // copy the value of the REG into the SP``
* ``LSMOV #SP, REG // copy the value of the REG into the SP used as an address into the data store``
* ``MOVI REG, IP // copy the value of the instruction pointer into the REG``
* ``MOVLD REG, data-index // copy the value at the literal data index into the REG``
* ``MOVD REG, #REG // SRC register holds the address of the data in the data store``
* ``LDMOV data-index, REG // copy the value of the REG into the data index``
* ``DMOV #REG, REG // DEST register holds the address of the data in the data store``

#### Stack manipulation
* ``PUSH REG // Push the value in the REG on the stack``
* ``POP REG // Pop the value on the top of the stack into the REG``

Note that there is no data-data or data-stack instruction.

### Arithmetic instructions
The arithmetic instructions are mainly intended for use with the stack or instruction pointers. Only ``REG`` to ``REG`` operations are supported. Left, right and dest must all be registers. The form of the instruction must be state explicitly whether it's signed or unsigned.
* ``ADD DEST, LEFT, RIGHT // unsigned integer add``
* ``SUB DEST, LEFT, RIGHT // unsigned integer subtract``
* ``MUL DEST, LEFT, RIGHT // unsigned integer multiply``
* ``DIV DEST, LEFT, RIGHT // unsigned integer divide``
* ``MOD DEST, LEFT, RIGHT // unsigned integer modulo``
* ``ADDS DEST, LEFT, RIGHT // signed integer add``
* ``SUBS DEST, LEFT, RIGHT // signed integer subtract``
* ``MULS DEST, LEFT, RIGHT // signed integer multiply``
* ``DIVS DEST, LEFT, RIGHT // signed integer divide``
* ``MODS DEST, LEFT, RIGHT // signed integer modulo``
* ``SHL DEST, REG, literal_number // Bitwise shift left by literal number``
* ``SHLR DEST, REG, REG // Bitwise shift left by value in register``
* ``SHR DEST, REG, literal_number // Bitwise shift right by literal number``
* ``SHRR DEST, REG, REG // Bitwise shift right by value in register``
* ``AND DEST, REG, REG // Bitwise AND the two registers and place the result in DEST``
* ``ANDL DEST, REG, literal_number // Bitwise AND the register with the literal and place the result in DEST``
* ``OR DEST, REG, REG // Bitwise OR the two registers and place the result in DEST``
* ``ORL DEST, REG, literal_number // Bitwise OR the register with the literal and place the result in DEST``
* ``XOR DEST, REG, REG // Bitwise XOR the two registers and place the result in DEST``
* ``XORL DEST, REG, literal_number // Bitwise XOR the register with the literal and place the result in DEST``
* ``NOT DEST, REG // Bitwise NOT the register and place the result in the DEST``
* ``INC DEST, REG // Increment the value in the register``
* ``DEC DEST, REG // Decrement the value in the register``

### Comparison instructions
These instructions compare two registers and set the ``true`` flag as a result. The comparison is done on the numerical value that is in the registers. Both left and right must be registers. The form of the instruction must be state explicitly whether it's signed or unsigned.
* ``EQU LEFT, RIGHT // unsigned integer compare, set true flag if equal``
* ``NEQ LEFT, RIGHT // unsigned integer compare, set true flag if not equal``
* ``GT LEFT, RIGHT // unsigned integer compare, set true flag if LEFT is greater than RIGHT``
* ``LT LEFT, RIGHT // unsigned integer compare, set true flag if LEFT is less than RIGHT``
* ``GTE LEFT, RIGHT // unsigned integer compare, set true flag if LEFT is greater than or equal to RIGHT``
* ``LTE LEFT, RIGHT // unsigned integer compare, set true flag if LEFT is less than or equal to RIGHT``
* ``GTS LEFT, RIGHT // signed integer compare, set true flag if LEFT is greater than RIGHT``
* ``LTS LEFT, RIGHT // signed integer compare, set true flag if LEFT is less than RIGHT``
* ``GTES LEFT, RIGHT // signed integer compare, set true flag if LEFT is greater than or equal to RIGHT``
* ``LTES LEFT, RIGHT // signed integer compare, set true flag if LEFT is less than or equal to RIGHT``
* ``EQUL LEFT, literal_number // unsigned integer compare, set true flag if equal``
* ``NEQL LEFT, literal_number // unsigned integer compare, set true flag if not equal``
* ``GTL LEFT, literal_number // unsigned integer compare, set true flag if LEFT is greater than RIGHT``
* ``LTL LEFT, literal_number // unsigned integer compare, set true flag if LEFT is less than RIGHT``
* ``GTEL LEFT, literal_number // unsigned integer compare, set true flag if LEFT is greater than or equal to RIGHT``
* ``LTEL LEFT, literal_number // unsigned integer compare, set true flag if LEFT is less than or equal to RIGHT``
* ``GTSL LEFT, literal_number // signed integer compare, set true flag if LEFT is greater than RIGHT``
* ``LTSL LEFT, literal_number // signed integer compare, set true flag if LEFT is less than RIGHT``
* ``GTESL LEFT, literal_number // signed integer compare, set true flag if LEFT is greater than or equal to RIGHT``
* ``LTESL LEFT, literal_number // signed integer compare, set true flag if LEFT is less than or equal to RIGHT``
* ``LEQU LEFT, RIGHT // unsigned integer compare, set true flag if equal``
* ``LNEQ LEFT, RIGHT // unsigned integer compare, set true flag if not equal``
* ``LGT literal_number, RIGHT // unsigned integer compare, set true flag if LEFT is greater than RIGHT``
* ``LLT literal_number, RIGHT // unsigned integer compare, set true flag if LEFT is less than RIGHT``
* ``LGTE literal_number, RIGHT // unsigned integer compare, set true flag if LEFT is greater than or equal to RIGHT``
* ``LLTE literal_number, RIGHT // unsigned integer compare, set true flag if LEFT is less than or equal to RIGHT``
* ``LGTS literal_number, RIGHT // signed integer compare, set true flag if LEFT is greater than RIGHT``
* ``LLTS literal_number, RIGHT // signed integer compare, set true flag if LEFT is less than RIGHT``
* ``LGTES literal_number, RIGHT // signed integer compare, set true flag if LEFT is greater than or equal to RIGHT``
* ``LLTES literal_number, RIGHT // signed integer compare, set true flag if LEFT is less than or equal to RIGHT``

### Flow control instructions
These instructions control where the current execution is taking place. In the assembler, when a name is provided as the destination of a jump or call, the name is translated to a literal number which is loaded accordingly.

#### Jump instructions
These do not have any effect on other registers except the instruction pointer. If the developer specifies a name as the operand, then that is converted to a literal index into the code store. If the name has not been previously defined then a syntax error is generated.
* ``JMP REG // REG has the absolute address to JMP to``
* ``JMPT REG // REG has the absolute address to JMP to if the true register is set``
* ``JMPF REG // REG has the absolute address to JMP to if the true register is clear``
* ``JMPP #REG // REG has the absolute address to JMP to``
* ``JMPPT #REG // REG points to the absolute address to JMP to if the true register is set``
* ``JMPPF #REG // REG points to the absolute address to JMP to if the true register is clear``
* ``JMPL literal_number // The literal number is the index to JMP to``
* ``JMPLT literal_number // The literal number is the index to JMP to if the true register is set``
* ``JMPLF literal_number // The literal number is the index to JMP to if the true register is clear``
* ``JMPR REG // JMP relative to the signed value in the register``
* ``JMPRC signed_char // Jump relative to the signed char``
* ``JMPRS signed_short // Jump relative to the signed short``
* ``JMPRI signed_int // ump relative to the signed integer``
* ``JMPRL signed long // ump relative to the signed long``
* ``JMPRCT signed_char // Jump relative to the signed char if comp register is set``
* ``JMPRST signed_short // Jump relative to the signed short if comp register is set``
* ``JMPRIT signed_int // Jump relative to the signed integer if comp register is set``
* ``JMPRLT signed long // Jump relative to the signed long if comp register is set``
* ``JMPRCF signed_char // Jump relative to the signed char if comp register is clear``
* ``JMPRSF signed_short // Jump relative to the signed short if comp register is clear``
* ``JMPRIF signed_int // Jump relative to the signed integer if comp register is clear``
* ``JMPRLF signed long // Jump relative to the signed long if comp register is clear``

#### Call instructions
These push the current address on the stack and then update the IP to change the execution location. If the developer specifies a name as the operand, then that is converted to a literal index into the code store. If the name has not been previously defined then a syntax error is generated.
* ``CALL REG // REG has the absolute address to CALL to``
* ``CALLT REG // REG has the absolute address to CALL to if the true register is set``
* ``CALLF REG // REG has the absolute address to CALL to if the true register is clear``
* ``CALLP #REG // REG points to the absolute address to CALL to``
* ``CALLPT #REG // REG points to the absolute address to CALL to if the true register is set``
* ``CALLPF #REG // REG points to the absolute address to CALL to if the true register is clear``
* ``CALLL literal_number // The literal number is the index to CALL to``
* ``CALLLT literal_number // The literal number is the index to CALL to if the true register is set``
* ``CALLLF literal_number // The literal number is the index to CALL to if the true register is clear``
* ``CALLR REG // Call relative to the signed value in the register``
* ``CALLRC signed_char // Jump relative to the signed char``
* ``CALLRS signed_short // Jump relative to the signed short``
* ``CALLRI signed_int // ump relative to the signed integer``
* ``CALLRL signed long // ump relative to the signed long``
* ``CALLRCT signed_char // Jump relative to the signed char if comp register is set``
* ``CALLRST signed_short // Jump relative to the signed short if comp register is set``
* ``CALLRIT signed_int // Jump relative to the signed integer if comp register is set``
* ``CALLRLT signed long // Jump relative to the signed long if comp register is set``
* ``CALLRCF signed_char // Jump relative to the signed char if comp register is clear``
* ``CALLRSF signed_short // Jump relative to the signed short if comp register is clear``
* ``CALLRIF signed_int // Jump relative to the signed integer if comp register is clear``
* ``CALLRLF signed long // Jump relative to the signed long if comp register is clear``

#### Return instructions
These pop the top of the stack into instruction pointer to return from a call.
* ``RET // Unconditional return``
* ``RETT // Return if the true register is set``
* ``RETF // Return if the true register is clear``

#### External library interface
This allows a user program to implement access to any arbitrary external dynamically loaded library. The ``name`` parameter is a register that holds the address of the name in the data store. The name is converted by the VM from a unsigned long to a string. The resources exist in the VM to locate the file and load it as a library. The user's assembler code will define the interface by name for each of the libraries routines. The caller is responsible for setting up the call and cleaning up after. More will be added to this to make it actually work.
* ``EXT REG // Call the external routine by name.``
* ``LOAD REG // Load the external library by name.``

When a string is placed inline, it is added to to the data store anonymously and the literal address is substituted in the output.
* ``EXTL literal_number``
* ``LOADL literal_number``

### Miscellaneous instructions
These instructions Do not fit into any other category.
* ``CLRT // Clear the ``true`` register``
* ``SETT //Set the ``true`` register``
* ``EXIT // cause the VM to exit back to the operating system``
* ``NOP // No operation, used for padding``

## Data definition
Data definition reserves space in the data store. All of the cells in the data store are unsigned long, however, provision is made to store other entities such as a byte string in the data store. Once the data is stored in the data store, its type information is lost. The assumption is made that the programmer is aware of the type. How the data is stored is determined by the format of the initializer. Otherwise, the rules apply as shown below.

### Single word
A single word is 16 bytes long. So actually a small string (15 characters or less) can be stored in a single slot. A double precision float can be store there as well as any integer format. Note that the VM cannot manipulate objects like a float or a string directly. They are intended for external libraries to operate upon. There is no type information connected to a data location. It is assumed that the developer knows the type.

#### Storage formats
If no initializer is specified then the data is initialized to zero.
* ``DEF name = initializer // initialize a single word with the initializer.``
    * ``1234 // literal unsigned number``
    * ``0x1F34 // literal unsigned number``
    * ``-123 // literal signed number``
    * ``1.123e-10 // double precision float``
    * ``"a small string" // string is less than one slot``
    * ``"this is a larger string" // string is less than two slots``
    * ``[1, 2, 3, 4] // assign 4 slots with the numbers given``
* ``DEF name[5] // reserve 5 words associated with name with no initializer``
* ``DEF name // reserve one slot to name with no initializer``
