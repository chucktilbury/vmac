
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
    ENTER;
    TRACE("section: %s", opcode_to_str(op->section));
    switch(op->type) {
        case OPERAND_INT8:
            TRACE("int8: %d", op->value.inum8);
            break;
        case OPERAND_INT16:
            TRACE("int16: %d", op->value.inum16);
            break;
        case OPERAND_INT32:
            TRACE("int32: %d", op->value.inum32);
            break;
        case OPERAND_INT64:
            TRACE("int64: %ld", op->value.inum64);
            break;
        case OPERAND_UINT8:
            TRACE("uint8: %u", op->value.unum8);
            break;
        case OPERAND_UINT16:
            TRACE("uint16: %u", op->value.unum16);
            break;
        case OPERAND_UINT32:
            TRACE("uint32: %u", op->value.unum32);
            break;
        case OPERAND_UINT64:
            TRACE("uint64: %lu", op->value.unum64);
            break;
        // case OPERAND_ARRAY:
        //     TRACE("uint8: %d", op->value.unum8);
        //     break;
        case OPERAND_FLOAT:
            TRACE("float: %lf", op->value.fnum);
            break;
        case OPERAND_STRING:
            TRACE("string: %s", op->value.str);
            break;
        case OPERAND_REG:
            TRACE("register: %s", opcode_to_str(op->value.opcode));
            break;
        case OPERAND_IREG:
            TRACE("indirect register: %s", opcode_to_str(op->value.opcode));
            break;
        case OPERAND_LABEL:
            TRACE("label: %s", op->value.str);
            break;
        case OPERAND_ILABEL:
            TRACE("indirect label: %s", op->value.str);
            break;
        default:
            error("unknown operand type: %s", opcode_to_str(op->type));
    }
    RETURN();
}

static void _module(ast_module_t* node) {
    ENTER;

    ast_node_list_t* lst = node->node_list;
    for(size_t i = 0; i < lst->len; i++) {
        _module_item((ast_module_item_t*)lst->list[i]);
    }

    RETURN();
}

static void _module_item(ast_module_item_t* node) {
    ENTER;

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

    RETURN();
}

static void _code_label(ast_code_label_t* node) {
    ENTER;

    TRACE("name: \"%s\" index: 0x%08X", node->name, node->index);

    RETURN();
}

static void _data_label(ast_data_label_t* node) {
    ENTER;

    TRACE("type: %s: name: \"%s\" index: 0x%08X", opcode_to_str(node->type), node->name, node->index);

    RETURN();
}

static void _data_definition(ast_data_definition_t* node) {
    ENTER;

    _data_label(node->label);
    if(node->oper != NULL)
        _operand(node->oper);
    if(node->nitems != NULL)
        _operand(node->nitems);
    if(node->oper_list != NULL) {
        size_t mark = 0;
        operand_t* op = NULL;
        do {
            op = iterate_operand_list(node->oper_list, &mark);
            _operand(op);
        } while(op != NULL);
    }

    RETURN();
}

static void _instruction(ast_instruction_t* node) {
    ENTER;

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

    RETURN();
}

static void _class1_instruction(ast_class1_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    TRACE("register: %s", opcode_to_str(node->reg));
    _operand(node->oper1);
    _operand(node->oper2);
    RETURN();
}

static void _class2_instruction(ast_class2_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    TRACE("register: %s", opcode_to_str(node->reg));
    TRACE("num: 0x%02X", node->unum);
    RETURN();
}

static void _class3_instruction(ast_class3_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    TRACE("register: %s", opcode_to_str(node->reg));
    RETURN();
}

static void _class4_instruction(ast_class4_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    _operand(node->oper1);
    _operand(node->oper2);
    RETURN();
}

static void _class5_instruction(ast_class5_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    _operand(node->oper);
    RETURN();
}

static void _class6_instruction(ast_class6_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    TRACE("register: %s", opcode_to_str(node->reg));
    RETURN();
}

static void _class7_instruction(ast_class7_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    RETURN();
}

static void _class8_instruction(ast_class8_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    TRACE("string: %s", node->str);
    RETURN();
}

void show_trace(void) {
    ENTER;
    LEGEND("begin trace");
    _module(ast_root);
    LEGEND("end trace");
    RETURN();
}
