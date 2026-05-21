/*
 * This is the only place where text is substituted. When process_reference()
 * gets called, the replacement buffer is pushed on to the input buffer stack
 * and the parts of it that are not a reference are emitted. Except when the
 * reference is a parameter to a defined variable. In that case, the value that
 * the reference was called with is expanded and used as the replacement text.
 * It is expanded when that var is found in the expansion text.
 */
#include "common.h"
#include "symbols.h"
#include "parse.h"
//#include "parms.h"
#include <unistd.h>
// #include "context.h"
#include "parse_ref.h"
#include "emit.h"

#define MAX_RECURSION 10
static int recursion_level = 0;

typedef struct _context_t {
    symbol_t* sym;
    struct _context_t* next;
} context_t;

static context_t* _stack = NULL;

static void _destroy_context(context_t* cont) {

    if(cont != NULL) {
        _FREE(cont);
    }
}

/*
 * Push the context after the parameters have been successfully read.
 */
static void _push_context(symbol_t* sym) {
    ENTER;

    context_t* cont = _ALLOC_TYPE(context_t);
    cont->sym = sym;

    if(_stack != NULL)
        cont->next = _stack;
    _stack = cont;

    RETURN();
}

/*
 * Pop the local context after the repl text has been expended for the symbol.
 */
static void _pop_context(void) {
    ENTER;

    if(_stack != NULL) {
        context_t* old = _stack;
        _stack = _stack->next;
        _destroy_context(old);
    }

    RETURN();
}

static string_t* _is_parameter(string_t* name) {
    ENTER;
    if(_stack != NULL) {
        int len = _stack->sym->plist->len;
        for(int i = 0; i < len; i++) {
            string_t* str = _stack->sym->plist->lst[i]->name;
            TRACE("checking %s", str->buffer);
            if(!comp_string_str(str, name)) {
                TRACE("found parameter: %s", str->buffer);
                RETURN(_stack->sym->plist->lst[i]->repl);
            }
        }
    }
    RETURN(NULL);
}

/*
 * Search the context stack for the first name that appears and provide the
 * repl text for that name.
 */
static string_t* _find_repl(string_t* tag) {
    ENTER;
    TRACE("find: %s as param in %s", tag->buffer, _stack->sym->tag->buffer);

    if(_stack != NULL) {
        string_t* repl = _is_parameter(tag);
        if(repl != NULL)
            RETURN(repl);

        // if we reach here a parameter was not found, so search for a symbol.
        symbol_t* sym = find_symbol(tag);
        if(sym != NULL) {
            TRACE("found symbol: %s", sym->tag->buffer);
            RETURN(sym->repl_text);
        }

        TRACE("tag \"%s\" is not found", tag->buffer);
        RETURN(NULL);
    }

    TRACE("stack is NULL");
    RETURN(NULL);
}


/*
 * Set the value of the parameter when it is referenced. Macro parameters are
 * positional. If the parameter is just the name without the '@' then it is \
 * treated as simple text. If the '@' is present and the name has a value in
 * the symbol table, then the repl value is that.
 */
static void _set_parm(parm_list_t* lst, int index, string_t* repl) {
    ENTER;

    if(index >= 0 && index < lst->len) {
        if(lst->lst[index]->repl != NULL) {
            clear_string(lst->lst[index]->repl);
            append_string_str(lst->lst[index]->repl, repl);
        }
    }
    else
        error("too many parameters defined, expected %d", lst->len - 1);

    RETURN();
}

/*
 * Read everything in the parameters, if anything, and assign the value to the
 * replacement value of the parameter.
 */
static void _get_reference_parms(symbol_t* sym) {
    ENTER;

    ASSERT(sym != NULL, "attempt to get reference parms on empty symbol stack");
    //PRNCH;

    if(sym->arity != 0) // check for unwanted parameters
        consume_space();
    else
        RETURN();

    TRACE("sym->arity = %d", sym->arity);
    if(crnt_char() == '(') {
        consume_char();
        bool finished = false;
        int index = 0;
        string_t* repl = create_string(NULL);
        while(!finished) {
            int ch = crnt_char();
            while(ch != ',' && ch != ')' && ch != EOF) {
                append_string_char(repl, ch);
                consume_char();
                ch = crnt_char();
            }
            TRACE("value: %s", repl->buffer);
            _set_parm(sym->plist, index, repl);

            if(ch == ',') {
                index++;
                consume_char();
            }
            else if(ch == ')') {
                consume_char();
                finished = true;
            }
            clear_string(repl);
        }
        TRACE("index = %d", index);
        if(index + 1 != sym->arity) {
            error("expected %d parameters to macro \"%s\" but got %d",
                  sym->arity, sym->tag->buffer, index);
        }
    }
    else if(sym->arity != 0) {
        error("expected %d parameters to macro \"%s\" but got 0",
              sym->arity, sym->tag->buffer);
    }
#ifdef USE_TRACE
    else
        TRACE("no parms present");
#endif
    PRNCH;
    RETURN();
}

static void _parse_input(void) {
    ENTER;

    bool finished = false;
    while(!finished) {
        int ch = crnt_char();
        switch(ch) {
            case '/':
                parse_comment();
                break;
            case '.':
                parse_directive();
                break;
            case '@':
                parse_ref();
                break;
            case EOF:
            case EOI:
                TRACE("end of buffer");
                finished = true;
                break;
            default:
                // emit everything, including space
                // PRNCH;
                EMITC(crnt_char());
                consume_char();
                break;
        }
    }

    RETURN();
}

/*
 * Parse and store a reference.
 */
void parse_ref(void) {
    ENTER;

    if(recursion_level > MAX_RECURSION)
        error("macros are nested too deeply");
    recursion_level++;
    TRACE("recursion level = %d", recursion_level);

    PRNCH;
    TRACE("char should be a '@'");
    expect_char('@');
    consume_char();
    bool flag = false;

    string_t* name = scan_name();
    TRACE("\x1b[32;1mreference name = %s\x1b[m", name->buffer);
    if(name != NULL) {
        symbol_t* sym = find_symbol(name);
        if(sym != NULL) {
            _get_reference_parms(sym);
            if(!_is_parameter(name)) {
                _push_context(sym);
                flag = true;
            }
        }

        string_t* repl = _find_repl(name);
        if(repl != NULL) {
            push_input_buffer(repl);
            _parse_input();
            pop_input_buffer();
        }

        if(flag)
            _pop_context();
    }
    else {
        TRACE("not a reference");
        EMITC('@');
    }
    destroy_string(name);
    recursion_level--;

    RETURN();
}

