/*
 * Traverse the AST and update all of the forward references in the
 * JMP and CALL instructions.
 */
#include "common.h"
#include "parser.h"
#include "operands.h"
#include "ast_node.h"

static void _module_item(ast_module_item_t* node);
static void _code_label(ast_code_label_t* node);
static void _data_label(ast_data_label_t* node);
static void _data_definition(ast_data_definition_t* node);
static void _instruction(ast_instruction_t* node);
static void _class1_instruction(ast_class1_instruction_t* node);
static void _class2_instruction(ast_class2_instruction_t* node);
static void _class3_instruction(ast_class3_instruction_t* node);
static void _class4_instruction(ast_class4_instruction_t* node);
static void _class5_instruction(ast_class5_instruction_t* node);
static void _class6_instruction(ast_class6_instruction_t* node);
static void _class7_instruction(ast_class7_instruction_t* node);
static void _class8_instruction(ast_class8_instruction_t* node);

static void _operand(operand_t* op) {

    switch(op->type) {
        case OPERAND_LABEL: {
                ENTER;
                TRACE("code label");
                symbol_t* sym = find_symbol(op->value.str);
                if(sym != NULL) {
                    TRACE("location: 0x%08X index: 0x%08X", op->index, sym->index);
                    write_code_uint32(op->index, sym->index);
                }
                else
                    error("code symbol \"%s\" has no definition", op->value.str);
                RETURN();
            }
            break;
        case OPERAND_ILABEL: {
                ENTER;
                TRACE("data label");
                symbol_t* sym = find_symbol(op->value.str);
                if(sym != NULL) {
                    TRACE("location: 0x%08X index: 0x%08X", op->index, sym->index);
                    write_code_uint32(op->index, sym->index);
                }
                else
                    error("data symbol \"%s\" has no definition", op->value.str);
                RETURN();
            }
            break;
        default:
            {}
    }
}

static void _module(ast_module_t* node) {
    ast_node_list_t* lst = node->node_list;
    for(size_t i = 0; i < lst->len; i++) {
        _module_item((ast_module_item_t*)lst->list[i]);
    }
}

static void _module_item(ast_module_item_t* node) {
    switch(node->item->type) {
        case AST_INSTRUCTION:
            _instruction((ast_instruction_t*)node->item);
            break;
        case AST_CODE_LABEL:
            _code_label((ast_code_label_t*)node->item);
            break;
        case AST_DATA_DEFINITION:
            _data_definition((ast_data_definition_t*)node->item);
            break;
        default:
            error("unexpected node type: %s", ast_type_to_str(node->node.type));
    }
}

static void _code_label(ast_code_label_t* node) {
    (void)node;
}

static void _data_label(ast_data_label_t* node) {
    (void)node;
}

static void _data_definition(ast_data_definition_t* node) {
    _data_label(node->label);
}

static void _instruction(ast_instruction_t* node) {
    switch(node->item->type) {
        case AST_CLASS1_INSTRUCTION:
            _class1_instruction((ast_class1_instruction_t*)node->item);
            break;
        case AST_CLASS2_INSTRUCTION:
            _class2_instruction((ast_class2_instruction_t*)node->item);
            break;
        case AST_CLASS3_INSTRUCTION:
            _class3_instruction((ast_class3_instruction_t*)node->item);
            break;
        case AST_CLASS4_INSTRUCTION:
            _class4_instruction((ast_class4_instruction_t*)node->item);
            break;
        case AST_CLASS5_INSTRUCTION:
            _class5_instruction((ast_class5_instruction_t*)node->item);
            break;
        case AST_CLASS6_INSTRUCTION:
            _class6_instruction((ast_class6_instruction_t*)node->item);
            break;
        case AST_CLASS7_INSTRUCTION:
            _class7_instruction((ast_class7_instruction_t*)node->item);
            break;
        case AST_CLASS8_INSTRUCTION:
            _class8_instruction((ast_class8_instruction_t*)node->item);
            break;
        default:
            error("unknown instruction class");
    }
}

static void _class1_instruction(ast_class1_instruction_t* node) {
    _operand(node->oper1);
    _operand(node->oper2);
}

static void _class2_instruction(ast_class2_instruction_t* node) {
    (void)node;
}

static void _class3_instruction(ast_class3_instruction_t* node) {
    (void)node;
}

static void _class4_instruction(ast_class4_instruction_t* node) {
    _operand(node->oper1);
    _operand(node->oper2);
}

static void _class5_instruction(ast_class5_instruction_t* node) {
    _operand(node->oper);
}

static void _class6_instruction(ast_class6_instruction_t* node) {
    (void)node;
}

static void _class7_instruction(ast_class7_instruction_t* node) {
    (void)node;
}

static void _class8_instruction(ast_class8_instruction_t* node) {
    (void)node;
}

void update_references(void) {
    ENTER;
    LEGEND("begin update references");
    _module(ast_root);
    LEGEND("end update references");
    RETURN();
}

