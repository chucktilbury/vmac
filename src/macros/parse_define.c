/*
 * Define a symbol. A symbol can have replacement text or not. No checking or
 * replacement is done on the replacement text when the define is parsed. It
 * is copied verbatim.
 *
 * The
 */

#include "common.h"
#include "parse_define.h"
#include "symbols.h"
#include "parse.h"
//#include "parms.h"

static void _append_parm_list(symbol_t* sym, string_t* name) {
    ENTER;

    if(!parm_exists(sym, name)) {
        if(sym->plist->len + 1 > sym->plist->cap) {
            sym->plist->cap <<= 1;
            sym->plist->lst = _REALLOC_ARRAY(sym->plist->lst, parm_t*, sym->plist->cap);
        }

        parm_t* p = _ALLOC_TYPE(parm_t);
        p->name = copy_string(name);
        p->repl = create_string(NULL);

        sym->plist->lst[sym->plist->len] = p;
        sym->plist->len++;
    }
    else
        warning("duplicate parameter name \"%s\" is ignored", name->buffer);

    RETURN();
}

/*
 * Read the parameters for a definition. The parameters are stored by
 * position in the order in which they are encountered. Whatever is between
 * the commas with the spaces stripped from the ends is what is stored.
 */
static void _get_param_names(symbol_t* sym) {

    ENTER;
    // symbol_t* sym = peek_symbol_context();
    ASSERT(sym != NULL, "attempt to define reference parms on empty symbol stack");

    // should be a '('
    TRACE("char on entry: \'%c\'", crnt_char());
    expect_char('(');

    consume_char();
    consume_space();
    test_end_error();

    bool finished = false;
    while(!finished) {
        consume_space();
        test_end_error();
        int ch = crnt_char();
        if(ch == ',')
            consume_char();
        else if(ch == ')') {
            consume_char();
            finished = true;
        }
        else {
            string_t* name = scan_name();
            if(name == NULL)
                consume_error("a name");
            else {
                _append_parm_list(sym, name);
                sym->arity++;
            }
        }
    }
    TRACE("arity: %d", sym->arity);
    TRACE("buffer len: %d", sym->plist->len);

    RETURN();
}

static void _define_body(symbol_t* sym) {

    ENTER;
    PRNCH;

    // should be a '{'
    expect_char('{');
    consume_char();
    PRNCH;

    int ch;
    int count = 1;
    string_t* tmp = create_string(NULL);
    while(true) {
        test_end_error();
        ch = crnt_char();
        if(ch == '}') {
            count--;
            if(count == 0) {
                if(tmp->len > 0)
                    sym->repl_text = tmp;
                consume_char();
                PRNCH;
                RETURN();
            }
        }
        else if(ch == '{') {
            count++;
        }
        append_string_char(tmp, ch);
        consume_char();
    }

    TRACE(">>>> NEVER HAPPENS!");
    RETURN(); // never happens
}

/*
 * High level processor for define directive. The word ".define" has already
 * been consumed.
 */
void parse_define(void) {
    ENTER;
    PRNCH;

    consume_space();
    test_end_error();

    // get the symbol name
    string_t* name = scan_name();
    if(name != NULL) {
        symbol_t* sym = insert_symbol(name);

        // get the parameter list, which is optional
        consume_space();
        if(crnt_char() == '(') {
            _get_param_names(sym);

            // the body is not optional.
            consume_space();
            test_end_error();
            if(crnt_char() == '{')
                _define_body(sym);
            else
                error("a definition body is required if there are macro parameters");
        }
        else {
            // the body is optional.
            if(crnt_char() == '{')
                _define_body(sym);
        }
    }
    else
        error("expected name for .define");
    consume_space();

    PRNCH;
    RETURN();
}

void add_define(string_t* str) {
    ENTER;
    string_t* cpy = copy_string(str); // do not alter the original
    char* val = strchr(cpy->buffer, '=');
    size_t nlen;
    size_t vlen = 0;

    if(val != NULL) {
        *val = '\0';
        val++;
        vlen = strlen(val);
    }

    nlen = strlen(cpy->buffer);
    if(nlen > 0) {
        symbol_t* sym = insert_symbol(create_string(cpy->buffer));
        if(vlen > 0)
            sym->repl_text = create_string(val);
    }

    destroy_string(cpy);
    RETURN();
}
