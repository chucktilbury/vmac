#ifndef _AST_NODE_H_
#define _AST_NODE_H_

#include <stdint.h>
#include <stdbool.h>
#include "pointer_list.h"
#include "opcodes.h"
#include "operands.h"
#include "symbols.h"

typedef enum _ast_node_type_t {
    AST_MODULE,
    AST_MODULE_ITEM,
    AST_CODE_LABEL,
    AST_DATA_LABEL,
    AST_DATA_DEFINITION,
    AST_INSTRUCTION,
    AST_CLASS1_INSTRUCTION,
    AST_CLASS2_INSTRUCTION,
    AST_CLASS3_INSTRUCTION,
    AST_CLASS4_INSTRUCTION,
    AST_CLASS5_INSTRUCTION,
    AST_CLASS6_INSTRUCTION,
    AST_CLASS7_INSTRUCTION,
    AST_CLASS8_INSTRUCTION,
} ast_node_type_t;

typedef struct _ast_node_t {
    ast_node_type_t type;
} ast_node_t;

typedef struct _ast_node_list_t {
    ast_node_t** list;
    size_t cap;
    size_t len;
} ast_node_list_t;

typedef struct _ast_module_t {
    ast_node_t node;
    ast_node_list_t* node_list;
} ast_module_t;

typedef struct _ast_module_item_t {
    ast_node_t node;
    ast_node_t* item;
} ast_module_item_t;

typedef struct _ast_code_label_t {
    ast_node_t node;
    const char* name;
    int32_t index;
    bool is_init;
    symbol_t* sym;
} ast_code_label_t;

typedef struct _ast_data_label_t {
    ast_node_t node;
    opcode_t type;
    const char* name;
    int32_t index;
    bool is_init;
    symbol_t* sym;
} ast_data_label_t;

typedef struct _ast_data_definition_t {
    ast_node_t node;
    struct _ast_data_label_t* label;
    operand_t* oper;
    operand_list_t* oper_list;
    operand_t* nitems;
} ast_data_definition_t;

typedef struct _ast_instruction_t {
    ast_node_t node;
    ast_node_t* item;
} ast_instruction_t;

typedef struct _ast_class1_instruction_t {
    ast_node_t node;
    opcode_t instr;
    opcode_t reg;
    operand_t* oper1;
    operand_t* oper2;
} ast_class1_instruction_t;

typedef struct _ast_class2_instruction_t {
    ast_node_t node;
    opcode_t instr;
    opcode_t reg;
    uint8_t unum;
} ast_class2_instruction_t;

typedef struct _ast_class3_instruction_t {
    ast_node_t node;
    opcode_t instr;
    opcode_t reg;
} ast_class3_instruction_t;

typedef struct _ast_class4_instruction_t {
    ast_node_t node;
    opcode_t instr;
    operand_t* oper1;
    operand_t* oper2;
} ast_class4_instruction_t;

typedef struct _ast_class5_instruction_t {
    ast_node_t node;
    opcode_t instr;
    operand_t* oper;
} ast_class5_instruction_t;

typedef struct _ast_class6_instruction_t {
    ast_node_t node;
    opcode_t instr;
    opcode_t reg;
} ast_class6_instruction_t;

typedef struct _ast_class7_instruction_t {
    ast_node_t node;
    opcode_t instr;
} ast_class7_instruction_t;

typedef struct _ast_class8_instruction_t {
    ast_node_t node;
    opcode_t instr;
    const char* str;
} ast_class8_instruction_t;

ast_node_t* create_ast_node(ast_node_type_t type);
ast_node_list_t* create_ast_node_list(void);
void append_ast_node_list(ast_node_list_t* lst, ast_node_t* node);
ast_node_t* iterate_ast_node_list(ast_node_list_t* lst, size_t* mark);
const char* ast_type_to_str(ast_node_type_t type);

#endif /* _AST_NODE_H_ */

