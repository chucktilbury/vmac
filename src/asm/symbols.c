
#include "common.h"
#include "symbols.h"


symbol_t* sym_table = NULL;

symbol_t* create_symbol(const char* tag, opcode_t section, opcode_t type, uint32_t index) {

    ENTER;
    TRACE("create_symbol: %s", tag);
    symbol_t* sym = _ALLOC_TYPE(symbol_t);
    sym->tag = _COPY_STRING(tag);
    sym->type = type;
    sym->index = index;
    sym->section = section;
    sym->is_defined = false;

    RETURN(sym);
}

void _destroy_sym_table(symbol_t* node) {

    if(node != NULL) {
        _destroy_sym_table(node->left);
        _destroy_sym_table(node->right);

        _FREE(node->tag);
        _FREE(node);
    }
}

void destroy_sym_table(void) {

    ENTER;
    _destroy_sym_table(sym_table);
    RETURN();
}

static void _insert_symbol(symbol_t* node, symbol_t* sym) {

    int val = strcmp(node->tag, sym->tag);
    if(0 > val) {
        if(node->right != NULL)
            _insert_symbol(node->right, sym);
        else
            node->right = sym;
    }
    else if(0 < val) {
        if(node->left != NULL)
            _insert_symbol(node->left, sym);
        else
            node->left = sym;
    }
    else {
        warning("ignoring re-definition of symbol: \"%s\"", sym->tag);
    }
}

symbol_t* insert_symbol(const char* tag, opcode_t section, opcode_t type, uint32_t index) {

    ENTER;

    symbol_t* sym = create_symbol(tag, section, type, index);
    if(sym_table == NULL)
        sym_table = sym;
    else
        _insert_symbol(sym_table, sym);

    RETURN(sym);
}

static symbol_t* _find_symbol(symbol_t* root, const char* tag) {

    if(root == NULL)
        return NULL;

    int val = strcmp(root->tag, tag);
    if(0 > val) {
        if(root->right != NULL)
            return _find_symbol(root->right, tag);
        else
            return NULL;
    }
    else if(0 < val) {
        if(root->left != NULL)
            return _find_symbol(root->left, tag);
        else
            return NULL;
    }
    else
        return root;
}

symbol_t* find_symbol(const char* tag) {

    ENTER;
    TRACE("search for: %s", tag);

    symbol_t* sym = NULL;
    if(sym_table != NULL)
        sym = _find_symbol(sym_table, tag);

    TRACE("found = %s", sym ? "TRUE" : "FALSE");
    RETURN(sym);
}

static void _dump_sym_table(symbol_t* node) {

    if(node != NULL) {
        _dump_sym_table(node->left);
        _dump_sym_table(node->right);

        printf("\ntag: \"%s\"\n", node->tag);
        printf("section:  %s\n", opcode_to_str(node->section));
        printf("type:  %s\n", opcode_to_str(node->type));
        printf("index: 0x%08X\n", node->index);
    }
}

void dump_symbol_table(void) {

    print_legend("begin symbols");
    _dump_sym_table(sym_table);
    fputc('\n', stdout);
    print_legend("end symbols");
}
