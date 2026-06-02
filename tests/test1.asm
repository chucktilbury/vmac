
int8 some_name
int32 another_name[5]
string foob = "this is a string"

start:
    mov r0, r12
    add r31, r1, 12
    lt R00, r31
    jmpf eggs
bacon:
    mov r12, #foob
    mov #sp , 0x2323
    jmpt bacon
eggs:
    push r12
    mov #sp , 0x8023
    exit

