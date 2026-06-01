#include "common.h"
#include "classify.h"
#include "operand.h"
#include "scan.h"

extern byte_buffer_t* _code;
extern byte_buffer_t* _data;

pseudo_sym_t* _root = NULL;

#if USE_DUMP
#define DUMP dump(_root)

void dump(pseudo_sym_t* root) {
    if(root->right != NULL)
        dump(root->right);
    if(root->left != NULL)
        dump(root->right);
    printf("index: 0x%08X\n", root->idx);
}

#else
#define DUMP
#endif

static void __insert(pseudo_sym_t* root, pseudo_sym_t* node) {

    if(root->idx > node->idx) {
        if(root->right != NULL)
            __insert(root->right, node);
        else
            root->right = node;
    }
    else if(root->idx < node->idx) {
        if(root->left != NULL)
            __insert(root->left, node);
        else
            root->left = node;
    }
    // else do nothing
}

static void _insert_sym(uint32_t idx) {

    pseudo_sym_t* sym = _ALLOC_TYPE(pseudo_sym_t);
    sym->idx = idx;

    if(_root == NULL)
        _root = sym;
    else
        __insert(_root, sym);
}

pseudo_sym_t* __find(pseudo_sym_t* root, uint32_t idx) {

    if(root->idx > idx) {
        if(root->right != NULL)
            return __find(root->right, idx);
        else
            return NULL;
    }
    else if(root->idx < idx) {
        if(root->left != NULL)
            return __find(root->left, idx);
        else
            return NULL;
    }
    else
        return root;
}

pseudo_sym_t* find_sym(uint32_t idx) {

    return __find(_root, idx);
}

static void _operand(size_t* mark) {
    //ENTER;
    opcode_t op = iterate_byte_buffer_uint8(_code, mark);
    switch(op) {
        case OPERAND_INT16:
        case OPERAND_UINT16:
            iterate_byte_buffer_uint16(_code, mark);
            break;
        case OPERAND_INT32:
        case OPERAND_UINT32:
        case OPERAND_ILABEL:
            iterate_byte_buffer_uint32(_code, mark);
            break;
        case OPERAND_INT64:
        case OPERAND_UINT64:
        case OPERAND_FLOAT:
            iterate_byte_buffer_uint64(_code, mark);
            break;
        case OPERAND_UINT8:
        case OPERAND_INT8:
        case OPERAND_IREG:
        case OPERAND_REG:
            iterate_byte_buffer_uint8(_code, mark);
            break;
        case OPERAND_LABEL: {
                uint32_t idx = iterate_byte_buffer_uint32(_code, mark);
                _insert_sym(idx);
                //printf("_%08X_code\n", idx);
            }
            break;
        default:
            error("invalid operand type: %s", opcode_to_str(op));
    }
    //RETURN();
}


void scan_code(void) {

    ENTER;
    bool finished = false;
    size_t mark = 0;

    while(!finished) {
        opcode_t op = iterate_byte_buffer_uint8(_code, &mark);
        switch(classify_instruction(op)) {
            case CLASS_1:
            case CLASS_2:
                iterate_byte_buffer_uint8(_code, &mark);
            case CLASS_3:
            case CLASS_4:
                _operand(&mark);
                _operand(&mark);
                break;
            case CLASS_5:
                _operand(&mark);
                break;
            case CLASS_6:
                iterate_byte_buffer_uint8(_code, &mark);
                break;
            case CLASS_7:
                break;
            case CLASS_8:
                _operand(&mark);
                break;
            default:
                error("bad instruction class (never happens)");
        }

        if(mark >= _code->len) {
            finished = true;
        }

    }

    DUMP;
    RETURN();
}

