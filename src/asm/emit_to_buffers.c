/*
 * Traverse the AST and emit the code and data to the buffers.
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

static void _code_operand(operand_t* op) {
    ENTER;

    switch(op->type) {
        case OPERAND_INT8:
            TRACE("int8: %d", op->value.inum8);
            emit_code_uint8(op->type);
            emit_code_int8(op->value.inum8);
            break;
        case OPERAND_INT16:
            TRACE("int16: %d", op->value.inum16);
            emit_code_uint8(op->type);
            emit_code_int16(op->value.inum16);
            break;
        case OPERAND_INT32:
            TRACE("int32: %d", op->value.inum32);
            emit_code_uint8(op->type);
            emit_code_int32(op->value.inum32);
            break;
        case OPERAND_INT64:
            TRACE("int64: %ld", op->value.inum64);
            emit_code_uint8(op->type);
            emit_code_int64(op->value.inum64);
            break;
        case OPERAND_UINT8:
            TRACE("uint8: %u", op->value.unum8);
            emit_code_uint8(op->type);
            emit_code_uint8(op->value.unum8);
            break;
        case OPERAND_UINT16:
            TRACE("uint16: %u", op->value.unum16);
            emit_code_uint8(op->type);
            emit_code_uint16(op->value.unum16);
            break;
        case OPERAND_UINT32:
            TRACE("uint32: %u", op->value.unum32);
            emit_code_uint8(op->type);
            emit_code_uint32(op->value.unum32);
            break;
        case OPERAND_UINT64:
            TRACE("uint64: %lu", op->value.unum64);
            emit_code_uint8(op->type);
            emit_code_uint64(op->value.unum64);
            break;
        // case OPERAND_ARRAY:
        //     TRACE("uint8: %d", op->value.unum8);
        //     break;
        case OPERAND_FLOAT:
            TRACE("float: %lf", op->value.fnum);
            emit_code_uint8(op->type);
            emit_code_uint64(*((uint64_t*)&(op->value.fnum)));
            break;
        // case OPERAND_STRING:
        //     TRACE("string: %s", op->value.str);
        //     emit_code_uint8(op->type);
        //     break;
        case OPERAND_REG:
            TRACE("register: %s", opcode_to_str(op->value.opcode));
            emit_code_uint8(op->type);
            emit_code_uint8(op->value.opcode);
            break;
        case OPERAND_IREG:
            TRACE("indirect register: %s", opcode_to_str(op->value.opcode));
            emit_code_uint8(op->type);
            emit_code_uint8(op->value.opcode);
            break;
        case OPERAND_LABEL:
            TRACE("label: %s", op->value.str);
            TRACE("location: 0x%08X", op->index);
            emit_code_uint8(op->type);
            op->index = get_code_index();
            emit_code_uint32(0);
            break;
        case OPERAND_ILABEL:
            TRACE("indirect label: %s", op->value.str);
            TRACE("location: 0x%08X", op->index);
            emit_code_uint8(op->type);
            op->index = get_code_index();
            emit_code_uint32(0);
            break;
        default:
            error("unknown operand type: %s", opcode_to_str(op->type));
    }
    RETURN();
}

static void _data_operand(operand_t* op) {
    ENTER;

    switch(op->type) {
        case OPERAND_INT8:
            TRACE("int8: %d", op->value.inum8);
            emit_data_int8(op->value.inum8);
            break;
        case OPERAND_INT16:
            TRACE("int16: %d", op->value.inum16);
            emit_data_int16(op->value.inum16);
            break;
        case OPERAND_INT32:
            TRACE("int32: %d", op->value.inum32);
            emit_data_int32(op->value.inum32);
            break;
        case OPERAND_INT64:
            TRACE("int64: %ld", op->value.inum64);
            emit_data_int64(op->value.inum64);
            break;
        case OPERAND_UINT8:
            TRACE("uint8: %u", op->value.unum8);
            emit_data_uint8(op->value.unum8);
            break;
        case OPERAND_UINT16:
            TRACE("uint16: %u", op->value.unum16);
            emit_data_uint16(op->value.unum16);
            break;
        case OPERAND_UINT32:
            TRACE("uint32: %u", op->value.unum32);
            emit_data_uint32(op->value.unum32);
            break;
        case OPERAND_UINT64:
            TRACE("uint64: %lu", op->value.unum64);
            emit_data_uint64(op->value.unum64);
            break;
        // case OPERAND_ARRAY:
        //     TRACE("uint8: %d", op->value.unum8);
        //     break;
        case OPERAND_FLOAT:
            TRACE("float: %lf", op->value.fnum);
            emit_data_uint64(*((uint64_t*)&(op->value.fnum)));
            break;
        case OPERAND_STRING:
            TRACE("string: %s", op->value.str);
            emit_data_uint16((uint16_t)strlen(op->value.str)+1);
            emit_data_str(op->value.str);
            break;
        case OPERAND_REG:
            TRACE("register: %s", opcode_to_str(op->value.opcode));
            emit_data_uint8(op->value.opcode);
            break;
        case OPERAND_IREG:
            TRACE("indirect register: %s", opcode_to_str(op->value.opcode));
            emit_data_uint8(op->value.opcode);
            break;
// TODO: fix this VV
        case OPERAND_LABEL:
            TRACE("label: %s", op->value.str);
            emit_data_uint32(0);
            break;
        case OPERAND_ILABEL:
            TRACE("indirect label: %s", op->value.str);
            emit_data_uint32(0);
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

    node->index = get_code_index();
    node->sym->index = node->index;
    TRACE("name: \"%s\" index: 0x%08X", node->name, node->index);

    RETURN();
}

static void _data_label(ast_data_label_t* node) {
    ENTER;

    node->index = get_data_index();
    node->sym->index = node->index;
    TRACE("type: %s: name: \"%s\" index: 0x%08X", opcode_to_str(node->type), node->name, node->index);
    emit_data_uint8(node->type);


    RETURN();
}

static void _data_definition(ast_data_definition_t* node) {
    ENTER;

    _data_label(node->label);
    if(node->oper != NULL) {
        _data_operand(node->oper);
    }
    else if(node->nitems != NULL) {
        uint16_t limit = 0;
        emit_data_uint8(OPERAND_ARRAY);
        switch(node->nitems->type) {
            case OPERAND_INT8:
                limit = (uint16_t)node->nitems->value.inum8;
                break;
            case OPERAND_UINT8:
                limit = (uint16_t)node->nitems->value.unum8;
                break;
            case OPERAND_INT16:
                limit = (uint16_t)node->nitems->value.inum16;
                break;
            case OPERAND_UINT16:
                limit = node->nitems->value.unum8;
                break;
            default:
                error("array size limit exceeded");
        }
        TRACE("emit %d items", limit);
        emit_data_uint16(limit);
        operand_t* op = create_operand(node->label->type);
        for(uint16_t i = 0; i < limit; i++)
            _data_operand(op);
    }
    else if(node->oper_list != NULL) {
        emit_data_uint8(OPERAND_ARRAY);
        emit_data_uint16((uint16_t)node->oper_list->len);
        size_t mark = 0;
        operand_t* op = NULL;
        do {
            op = iterate_operand_list(node->oper_list, &mark);
            _data_operand(op);
        } while(op != NULL);
    }
    else {
        operand_t* op = create_operand(node->label->type);
        _data_operand(op);
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
    emit_code_uint8(node->instr);
    TRACE("register: %s", opcode_to_str(node->reg));
    emit_code_uint8(node->reg);
    _code_operand(node->oper1);
    _code_operand(node->oper2);
    RETURN();
}

static void _class2_instruction(ast_class2_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    emit_code_uint8(node->instr);
    TRACE("register: %s", opcode_to_str(node->reg));
    emit_code_uint8(node->reg);
    TRACE("num: 0x%02X", node->unum);
    emit_code_uint8(node->unum);
    RETURN();
}

static void _class3_instruction(ast_class3_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    emit_code_uint8(node->instr);
    TRACE("register: %s", opcode_to_str(node->reg));
    emit_code_uint8(node->reg);
    RETURN();
}

static void _class4_instruction(ast_class4_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    emit_code_uint8(node->instr);
    _code_operand(node->oper1);
    _code_operand(node->oper2);
    RETURN();
}

static void _class5_instruction(ast_class5_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    emit_code_uint8(node->instr);
    _code_operand(node->oper);
    RETURN();
}

static void _class6_instruction(ast_class6_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    emit_code_uint8(node->instr);
    TRACE("register: %s", opcode_to_str(node->reg));
    emit_code_uint8(node->reg);
    RETURN();
}

static void _class7_instruction(ast_class7_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    emit_code_uint8(node->instr);
    RETURN();
}

static void _class8_instruction(ast_class8_instruction_t* node) {
    ENTER;
    TRACE("instruction: %s", opcode_to_str(node->instr));
    emit_code_uint8(node->instr);
    TRACE("string: %s", node->str);
    RETURN();
}

void emit_to_buffers(void) {
    ENTER;
    LEGEND("begin emit_to_buffers");
    _module(ast_root);
    LEGEND("end emit_to_buffers");
    RETURN();
}

