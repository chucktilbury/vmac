#include "common.h"
#include "ast_node.h"

static size_t _get_node_size(ast_node_type_t type) {

    size_t size = 0;
    switch(type) {
        case AST_MODULE:
            size = sizeof(ast_module_t);
            break;
        case AST_MODULE_ITEM:
            size = sizeof(ast_module_item_t);
            break;
        case AST_CODE_LABEL:
            size = sizeof(ast_code_label_t);
            break;
        case AST_DATA_LABEL:
            size = sizeof(ast_data_label_t);
            break;
        case AST_DATA_DEFINITION:
            size = sizeof(ast_data_definition_t);
            break;
        case AST_INSTRUCTION:
            size = sizeof(ast_instruction_t);
            break;
        case AST_CLASS1_INSTRUCTION:
            size = sizeof(ast_class1_instruction_t);
            break;
        case AST_CLASS2_INSTRUCTION:
            size = sizeof(ast_class2_instruction_t);
            break;
        case AST_CLASS3_INSTRUCTION:
            size = sizeof(ast_class3_instruction_t);
            break;
        case AST_CLASS4_INSTRUCTION:
            size = sizeof(ast_class4_instruction_t);
            break;
        case AST_CLASS5_INSTRUCTION:
            size = sizeof(ast_class5_instruction_t);
            break;
        case AST_CLASS6_INSTRUCTION:
            size = sizeof(ast_class6_instruction_t);
            break;
        case AST_CLASS7_INSTRUCTION:
            size = sizeof(ast_class7_instruction_t);
            break;
        case AST_CLASS8_INSTRUCTION:
            size = sizeof(ast_class8_instruction_t);
            break;
    }
    return size;
}

const char* ast_type_to_str(ast_node_type_t type) {

    return (type == AST_MODULE)              ? "MODULE" :
            (type == AST_MODULE_ITEM)        ? "MODULE_ITEM" :
            (type == AST_CODE_LABEL)         ? "CODE_LABEL" :
            (type == AST_DATA_LABEL)         ? "DATA_LABEL" :
            (type == AST_DATA_DEFINITION)    ? "DATA_DEFINITION" :
            (type == AST_INSTRUCTION)        ? "INSTRUCTION" :
            (type == AST_CLASS1_INSTRUCTION) ? "CLASS1_INSTRUCTION" :
            (type == AST_CLASS2_INSTRUCTION) ? "CLASS2_INSTRUCTION" :
            (type == AST_CLASS3_INSTRUCTION) ? "CLASS3_INSTRUCTION" :
            (type == AST_CLASS4_INSTRUCTION) ? "CLASS4_INSTRUCTION" :
            (type == AST_CLASS5_INSTRUCTION) ? "CLASS5_INSTRUCTION" :
            (type == AST_CLASS6_INSTRUCTION) ? "CLASS6_INSTRUCTION" :
            (type == AST_CLASS7_INSTRUCTION) ? "CLASS7_INSTRUCTION" :
            (type == AST_CLASS8_INSTRUCTION) ? "CLASS8_INSTRUCTION" :
                                               "UNKNOWN";
}

ast_node_t* create_ast_node(ast_node_type_t type) {

    size_t size = _get_node_size(type);
    // TRACE("create node: %s: %lu", ast_type_to_str(type), size);
    ast_node_t* node = _ALLOC(size);
    node->type = type;

    return node;
}

ast_node_list_t* create_ast_node_list(void) {

    ast_node_list_t* lst = _ALLOC_TYPE(ast_node_list_t);
    lst->cap = 1 << 3;
    lst->len = 0;
    lst->list = _ALLOC_ARRAY(ast_node_t*, lst->cap);

    return lst;
}

void append_ast_node_list(ast_node_list_t* lst, ast_node_t* node) {

    if(lst->len + 1 >= lst->cap) {
        lst->cap <<= 1;
        lst->list = _REALLOC_ARRAY(lst->list, ast_node_t*, lst->cap);
    }

    lst->list[lst->len] = node;
    lst->len++;
}

ast_node_t* iterate_ast_node_list(ast_node_list_t* lst, size_t* mark) {

    ast_node_t* node = NULL;
    if(*mark < lst->len) {
        node = lst->list[*mark];
        *mark = *mark + 1;
    }

    return node;
}
