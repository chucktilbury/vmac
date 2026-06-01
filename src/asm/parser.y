%{
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"
#include "opcodes.h"
#include "operands.h"
#include "symbols.h"
#include "emit.h"
#include "ast_node.h"

ast_module_t* ast_root;

%}
%code requires {
    #include "opcodes.h"
    #include "operands.h"
    #include "symbols.h"
    #include "emit.h"
    #include "ast_node.h"
    int yylex(void);
    void yyerror(const char*);
}

%code provides {
    int get_uint_size(uint64_t val);
    int get_int_size(int64_t val);
    extern ast_module_t* ast_root;
}

%union {
    char* str;
    int64_t inum;
    uint64_t unum;
    double fnum;
    opcode_t op;
    operand_t* oper;
    operand_list_t* op_list;
    //symbol_t* sym;

    ast_node_t* ast_node;
    ast_module_t* ast_module;
    ast_module_item_t* ast_module_item;
    ast_code_label_t* ast_code_label;
    ast_data_label_t* ast_data_label;
    ast_data_definition_t* ast_data_definition;
    ast_instruction_t* ast_instruction;
    ast_class1_instruction_t* ast_class1_instruction;
    ast_class2_instruction_t* ast_class2_instruction;
    ast_class3_instruction_t* ast_class3_instruction;
    ast_class4_instruction_t* ast_class4_instruction;
    ast_class5_instruction_t* ast_class5_instruction;
    ast_class6_instruction_t* ast_class6_instruction;
    ast_class7_instruction_t* ast_class7_instruction;
    ast_class8_instruction_t* ast_class8_instruction;
}

%token R00 R01 R02 R03 R04 R05 R06 R07 R08 R09 R10 R11 R12 R13 R14 R15
%token R16 R17 R18 R19 R20 R21 R22 R23 R24 R25 R26 R27 R28 R29 R30 R31

%token <op> SP IP
%token <op> MOV PUSH POP ADD SUB MUL DIV MOD ADDU SUBU MULU DIVU MODU
%token <op> INC DEC INCU DECU SHL SHR AND OR XOR NOT EQU EQUU NEQ NEQU LT
%token <op> LTU GT GTU LTE LTEU GTE GTEU JMP JMPT JMPF JMPR JMPRT JMPRF CALL
%token <op> CALLT CALLF CALLR CALLRT CALLRF RET RETT RETF EXTERN LOAD CLRT
%token <op> SETT EXIT ABORT NOP

%token <op> INT8 INT16 INT32 INT64 UINT8 UINT16 UINT32 UINT64 FLOAT STRING

%token <str> NAME QSTR
%token <inum> LITERAL_INT8 LITERAL_INT16 LITERAL_INT32 LITERAL_INT64
%token <unum> LITERAL_UINT8 LITERAL_UINT16 LITERAL_UINT32 LITERAL_UINT64
%token <fnum> LITERAL_FLOAT

%type <op> register iregister type_spec
%type <op> class1_opcode class2_opcode class3_opcode class4_opcode
%type <op> class5_opcode class6_opcode class7_opcode class8_opcode
%type <oper> literal_value literal_number src_operand dest_operand
%type <oper> literal_small_number literal_byte
%type <op_list> literal_list

%type <ast_module> module
%type <ast_module_item> module_item
%type <ast_code_label> code_label
%type <ast_data_label> data_label
%type <ast_data_definition> data_definition
%type <ast_instruction> instruction
%type <ast_class1_instruction> class1_instruction
%type <ast_class2_instruction> class2_instruction
%type <ast_class3_instruction> class3_instruction
%type <ast_class4_instruction> class4_instruction class4a_instruction
%type <ast_class5_instruction> class5_instruction
%type <ast_class6_instruction> class6_instruction
%type <ast_class7_instruction> class7_instruction
%type <ast_class8_instruction> class8_instruction

%locations
%define parse.error detailed
%define parse.lac full

%%

module
    : module_item {
            $$ = ast_root = (ast_module_t*)create_ast_node(AST_MODULE);
            ast_root->node_list = create_ast_node_list();
            append_ast_node_list(ast_root->node_list, (ast_node_t*)$1);
        }
    | module module_item {
            append_ast_node_list($1->node_list, (ast_node_t*)$2);
        }
    ;

module_item
    : instruction {
            ast_module_item_t* node = (ast_module_item_t*)create_ast_node(AST_MODULE_ITEM);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    | data_definition {
            ast_module_item_t* node = (ast_module_item_t*)create_ast_node(AST_MODULE_ITEM);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    | code_label {
            ast_module_item_t* node = (ast_module_item_t*)create_ast_node(AST_MODULE_ITEM);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    ;

code_label
    : NAME ':' {
            ast_code_label_t* node = (ast_code_label_t*)create_ast_node(AST_CODE_LABEL);
            node->name = _COPY_STRING($1);
            node->index = 0;
            node->is_init = false;
            node->sym = insert_symbol($1, SEC_CODE, OPERAND_LABEL, 0);
            $$ = node;
        }
    ;

data_label
    : type_spec NAME {
            TRACE("data label name: %s", $2);
            ast_data_label_t* node = (ast_data_label_t*)create_ast_node(AST_DATA_LABEL);
            node->name = _COPY_STRING($2);
            node->type = $1;
            node->index = 0;
            node->is_init = false;
            node->sym = insert_symbol($2, SEC_DATA, OPERAND_LABEL, 0);
            $$ = node;
        }
    ;

type_spec
    : INT8 { $$ = OPERAND_INT8; }
    | INT16 { $$ = OPERAND_INT16; }
    | INT32 { $$ = OPERAND_INT32; }
    | INT64 { $$ = OPERAND_INT64; }
    | UINT8 { $$ = OPERAND_UINT8; }
    | UINT16 { $$ = OPERAND_UINT16; }
    | UINT32 { $$ = OPERAND_UINT32; }
    | UINT64 { $$ = OPERAND_UINT64; }
    | FLOAT { $$ = OPERAND_FLOAT; }
    | STRING { $$ = OPERAND_STRING; }
    ;

data_definition
    : data_label {
            ast_data_definition_t* node = (ast_data_definition_t*)create_ast_node(AST_DATA_DEFINITION);
            node->label = $1;
            node->oper = NULL;
            node->oper_list = NULL;
            node->nitems = NULL;
            //node->oper->section = SEC_DATA;
            $$ = node;
        }
    | data_label '[' literal_small_number ']' {
            ast_data_definition_t* node = (ast_data_definition_t*)create_ast_node(AST_DATA_DEFINITION);
            node->label = $1;
            node->oper = NULL;
            node->oper_list = NULL;
            node->nitems = $3;
            //node->oper->section = SEC_DATA;
            $$ = node;
        }
    | data_label '=' literal_value {
            ast_data_definition_t* node = (ast_data_definition_t*)create_ast_node(AST_DATA_DEFINITION);
            node->label = $1;
            node->oper = $3;
            node->oper_list = NULL;
            node->nitems = NULL;
            node->oper->section = SEC_DATA;
            $$ = node;
        }
    | data_label '=' '[' literal_list ']' {
            ast_data_definition_t* node = (ast_data_definition_t*)create_ast_node(AST_DATA_DEFINITION);
            node->label = $1;
            node->oper = NULL;
            node->oper_list = $4;
            node->nitems = NULL;
            //node->oper->section = SEC_DATA;
            $$ = node;
        }
    ;

literal_byte
    : LITERAL_INT8 {
            operand_t* oper = create_operand(OPERAND_INT8);
            oper->value.inum8 = $1;
            $$ = oper;
        }
    | LITERAL_UINT8 {
            operand_t* oper = create_operand(OPERAND_UINT8);
            oper->value.unum8 = $1;
            $$ = oper;
        }
    ;

literal_small_number
    : literal_byte { $$ = $1; }
    | LITERAL_INT16 {
            operand_t* oper = create_operand(OPERAND_INT16);
            oper->value.inum16 = $1;
            $$ = oper;
        }
    | LITERAL_UINT16 {
            operand_t* oper = create_operand(OPERAND_UINT16);
            oper->value.unum16 = $1;
            $$ = oper;
        }
    ;

literal_number
    : literal_small_number { $$ = $1; }
    | LITERAL_INT32 {
            operand_t* oper = create_operand(OPERAND_INT32);
            oper->value.inum32 = $1;
            $$ = oper;
        }
    | LITERAL_INT64 {
            operand_t* oper = create_operand(OPERAND_INT64);
            oper->value.inum64 = $1;
            $$ = oper;
        }
    | LITERAL_UINT32 {
            operand_t* oper = create_operand(OPERAND_UINT32);
            oper->value.unum32 = $1;
            $$ = oper;
        }
    | LITERAL_UINT64 {
            operand_t* oper = create_operand(OPERAND_UINT64);
            oper->value.unum64 = $1;
            $$ = oper;
        }
    ;

literal_value
    : literal_number {
            $$ = $1;
        }
    | QSTR {
            operand_t* oper = create_operand(OPERAND_STRING);
            oper->value.str = _COPY_STRING($1);
            $$ = oper;
        }
    | LITERAL_FLOAT {
            operand_t* oper = create_operand(OPERAND_FLOAT);
            oper->value.fnum = $1;
            $$ = oper;
        }
    ;

    // operand list
literal_list
    : literal_value {
            operand_list_t* lst = create_operand_list();
            add_operand_list(lst, $1);
            $$ = lst;
        }
    | literal_list ',' literal_value {
            add_operand_list($1, $3);
        }
    ;

register
    : R00 { $$ = REG_R00; }
    | R01 { $$ = REG_R01; }
    | R02 { $$ = REG_R02; }
    | R03 { $$ = REG_R03; }
    | R04 { $$ = REG_R04; }
    | R05 { $$ = REG_R05; }
    | R06 { $$ = REG_R06; }
    | R07 { $$ = REG_R07; }
    | R08 { $$ = REG_R08; }
    | R09 { $$ = REG_R09; }
    | R10 { $$ = REG_R10; }
    | R11 { $$ = REG_R11; }
    | R12 { $$ = REG_R12; }
    | R13 { $$ = REG_R13; }
    | R14 { $$ = REG_R14; }
    | R15 { $$ = REG_R15; }
    | R16 { $$ = REG_R16; }
    | R17 { $$ = REG_R17; }
    | R18 { $$ = REG_R18; }
    | R19 { $$ = REG_R19; }
    | R20 { $$ = REG_R20; }
    | R21 { $$ = REG_R21; }
    | R22 { $$ = REG_R22; }
    | R23 { $$ = REG_R23; }
    | R24 { $$ = REG_R24; }
    | R25 { $$ = REG_R25; }
    | R26 { $$ = REG_R26; }
    | R27 { $$ = REG_R27; }
    | R28 { $$ = REG_R28; }
    | R29 { $$ = REG_R29; }
    | R30 { $$ = REG_R30; }
    | R31 { $$ = REG_R31; }
    | IP { $$ = REG_IP; }
    | SP { $$ = REG_SP; }
    ;

iregister
    : '#' register { $$ = $2 + 0x30; }
    ;

dest_operand
    : register {
            operand_t* oper = create_operand(OPERAND_REG);
            oper->value.opcode = $1;
            $$ = oper;
        }
    | iregister {
            operand_t* oper = create_operand(OPERAND_IREG);
            oper->value.opcode = $1;
            $$ = oper;
        }
    | NAME {
            operand_t* oper = create_operand(OPERAND_LABEL);
            oper->value.str = _COPY_STRING($1);
            $$ = oper;
        }
    | '#' NAME {
            operand_t* oper = create_operand(OPERAND_ILABEL);
            oper->value.str = _COPY_STRING($2);
            $$ = oper;
        }
    ;


src_operand
    : literal_number { $$ = $1; }
    | dest_operand { $$ = $1; }
    ;

instruction
    : class1_instruction {
            ast_instruction_t* node = (ast_instruction_t*)create_ast_node(AST_INSTRUCTION);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    | class2_instruction {
            ast_instruction_t* node = (ast_instruction_t*)create_ast_node(AST_INSTRUCTION);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    | class3_instruction {
            ast_instruction_t* node = (ast_instruction_t*)create_ast_node(AST_INSTRUCTION);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    | class4_instruction {
            ast_instruction_t* node = (ast_instruction_t*)create_ast_node(AST_INSTRUCTION);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    | class4a_instruction {
            ast_instruction_t* node = (ast_instruction_t*)create_ast_node(AST_INSTRUCTION);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    | class5_instruction {
            ast_instruction_t* node = (ast_instruction_t*)create_ast_node(AST_INSTRUCTION);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    | class6_instruction {
            ast_instruction_t* node = (ast_instruction_t*)create_ast_node(AST_INSTRUCTION);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    | class7_instruction {
            ast_instruction_t* node = (ast_instruction_t*)create_ast_node(AST_INSTRUCTION);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    | class8_instruction {
            ast_instruction_t* node = (ast_instruction_t*)create_ast_node(AST_INSTRUCTION);
            node->item = (ast_node_t*)$1;
            $$ = node;
        }
    ;

class1_opcode
    : ADD { $$ = OP_ADD; }
    | SUB { $$ = OP_SUB; }
    | MUL { $$ = OP_MUL; }
    | DIV { $$ = OP_DIV; }
    | MOD { $$ = OP_MOD; }
    | ADDU { $$ = OP_ADDU; }
    | SUBU { $$ = OP_SUBU; }
    | MULU { $$ = OP_MULU; }
    | DIVU { $$ = OP_DIVU; }
    | MODU { $$ = OP_MODU; }
    | AND { $$ = OP_AND; }
    | OR { $$ = OP_OR; }
    | XOR { $$ = OP_XOR; }
    ;

class1_instruction
    : class1_opcode register ',' src_operand ',' src_operand {
            // binary arithmetic operators
            ast_class1_instruction_t* node = (ast_class1_instruction_t*)create_ast_node(AST_CLASS1_INSTRUCTION);
            node->instr = $1;
            node->reg = $2;
            node->oper1 = $4;
            node->oper2 = $6;
            $$ = node;
        }
    ;

class2_opcode
    : SHL { $$ = OP_SHL; }
    | SHR { $$ = OP_SHR; }
    ;

class2_instruction
    : class2_opcode register ',' literal_byte {
            // unary operators with a parameter
            ast_class2_instruction_t* node = (ast_class2_instruction_t*)create_ast_node(AST_CLASS2_INSTRUCTION);
            node->instr = $1;
            node->reg = $2;
            node->unum = (uint8_t)$4->value.unum8;
            $$ = node;
        }
    ;

class3_opcode
    : INC { $$ = OP_INC; }
    | DEC { $$ = OP_DEC; }
    | INCU { $$ = OP_INCU; }
    | DECU { $$ = OP_DECU; }
    | NOT { $$ = OP_NOT; }
    ;

class3_instruction
    : class3_opcode register {
            // unary operators
            ast_class3_instruction_t* node = (ast_class3_instruction_t*)create_ast_node(AST_CLASS3_INSTRUCTION);
            node->instr = $1;
            node->reg = $2;
            $$ = node;
        }
    ;

class4_opcode
    : EQU { $$ = OP_EQU; }
    | EQUU { $$ = OP_EQUU; }
    | NEQ { $$ = OP_NEQ; }
    | NEQU { $$ = OP_NEQU; }
    | LT { $$ = OP_LT; }
    | LTU { $$ = OP_LTU; }
    | GT { $$ = OP_GT; }
    | GTU { $$ = OP_GTU; }
    | LTE { $$ = OP_LTE; }
    | LTEU { $$ = OP_LTEU; }
    | GTE { $$ = OP_GTE; }
    | GTEU { $$ = OP_GTEU; }
    ;

class4_instruction
    : class4_opcode src_operand ',' src_operand {
            // move and compare
            ast_class4_instruction_t* node = (ast_class4_instruction_t*)create_ast_node(AST_CLASS4_INSTRUCTION);
            node->instr = $1;
            node->oper1 = $2;
            node->oper2 = $4;
            $$ = node;
        }
    ;

class4a_instruction
    : MOV dest_operand ',' src_operand {
            // move and compare
            ast_class4_instruction_t* node = (ast_class4_instruction_t*)create_ast_node(AST_CLASS4_INSTRUCTION);
            node->instr = OP_MOV;
            node->oper1 = $2;
            node->oper2 = $4;
            $$ = node;
        }
    ;

class5_opcode
    : JMP { $$ = OP_JMP; }
    | JMPT { $$ = OP_JMPT; }
    | JMPF { $$ = OP_JMPF; }
    | JMPR { $$ = OP_JMPR; }
    | JMPRT { $$ = OP_JMPRT; }
    | JMPRF { $$ = OP_JMPRF; }
    | CALL { $$ = OP_CALL; }
    | CALLT { $$ = OP_CALLT; }
    | CALLF { $$ = OP_CALLF; }
    | CALLR { $$ = OP_CALLR; }
    | CALLRT { $$ = OP_CALLRT; }
    | CALLRF { $$ = OP_CALLRF; }
    ;

class5_instruction
    : class5_opcode src_operand {
            // jmp and call
            ast_class5_instruction_t* node = (ast_class5_instruction_t*)create_ast_node(AST_CLASS5_INSTRUCTION);
            node->instr = $1;
            node->oper = $2;
            $$ = node;
        }
    ;

class6_opcode
    : POP { $$ = OP_POP; }
    | PUSH { $$ = OP_PUSH; }
    ;

class6_instruction
    : class6_opcode register {
            // push and pop
            ast_class6_instruction_t* node = (ast_class6_instruction_t*)create_ast_node(AST_CLASS6_INSTRUCTION);
            node->instr = $1;
            node->reg = $2;
            $$ = node;
        }
    ;

class7_opcode
    : RET { $$ = OP_RET; }
    | RETT { $$ = OP_RETT; }
    | RETF { $$ = OP_RETF; }
    | CLRT { $$ = OP_CLRT; }
    | SETT { $$ = OP_SETT; }
    | EXIT { $$ = OP_EXIT; }
    | ABORT { $$ = OP_ABORT; }
    | NOP { $$ = OP_NOP; }
    ;

class7_instruction
    : class7_opcode {
            // ret and exit, no operands
            ast_class7_instruction_t* node = (ast_class7_instruction_t*)create_ast_node(AST_CLASS7_INSTRUCTION);
            node->instr = $1;
            $$ = node;
        }
    ;

class8_opcode
    : EXTERN { $$ = OP_EXTERN; }
    | LOAD { $$ = OP_LOAD; }
    ;

class8_instruction
    : class8_opcode QSTR {
            // string parameter emits anonymous string in the data
            ast_class8_instruction_t* node = (ast_class8_instruction_t*)create_ast_node(AST_CLASS8_INSTRUCTION);
            node->instr = $1;
            node->str = _COPY_STRING($2);
            $$ = node;
        }
    ;

%%

int get_int_size(int64_t val) {

    if(val >= INT8_MIN && val <= INT8_MAX)
        return OPERAND_INT8;
    else if(val >= INT16_MIN && val <= INT16_MAX)
        return OPERAND_INT16;
    else if(val >= INT32_MIN && val <= INT32_MAX)
        return OPERAND_INT32;
    else if(val >= INT64_MIN && val <= INT64_MAX)
        return OPERAND_INT64;
    return LITERAL_INT64;
}

int get_uint_size(uint64_t val) {

    if(val <= UINT8_MAX)
        return OPERAND_UINT8;
    else if(val <= UINT16_MAX)
        return OPERAND_UINT16;
    else if(val <= UINT32_MAX)
        return OPERAND_UINT32;
    else if(val <= UINT64_MAX)
        return OPERAND_UINT64;
    return OPERAND_UINT64;
}
