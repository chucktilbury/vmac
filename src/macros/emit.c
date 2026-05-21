
#include "common.h"
#include "emit.h"

static string_t* _out_buffer = NULL;

void create_output_buffer(void) {
    ENTER;
    _out_buffer = create_string(NULL);
    RETURN();
}

void destroy_output_buffer(void) {
    ENTER;
    destroy_string(_out_buffer);
    RETURN();
}

void write_output_buffer(string_t* name) {

    ENTER;
    if(name != NULL) {
        FILE* ofile = fopen(name->buffer, "w");
        if(ofile == NULL)
            FATAL("cannot open output file: \"%s\": %s", name->buffer, strerror(errno));
        TRACE("output stream = %s", name->buffer);
        fwrite(_out_buffer->buffer, sizeof(char), _out_buffer->len, ofile);
        fclose(ofile);
    }
    else {
        TRACE("output stream = stdout");
        fwrite(_out_buffer->buffer, sizeof(char), _out_buffer->len, stdout);
    }
    RETURN();
}

void emit_char(int ch) {

#ifdef USE_TRACE
    if(verbosity >= DEFAULT_TRACE + 10) {
        trace_pad(level*2, ' ');
        printf("EMIT: '");
        prnch(ch);
        printf("'\n");
    }
#endif
    append_string_char(_out_buffer, ch);
}

void emit_str(const char* str) {

#ifdef USE_TRACE
    if(verbosity >= DEFAULT_TRACE + 10) {
        trace_pad(level*2, ' ');
        printf("EMIT: \"");
        prnstr(str);
        printf("\"\n");
    }
#endif
    append_string(_out_buffer, str);
}

void emit_string(string_t* str) {

#ifdef USE_TRACE
    if(verbosity >= DEFAULT_TRACE + 10) {
        trace_pad(level*2, ' ');
        printf("EMIT: \"");
        prnstr(str->buffer);
        printf("\"\n");
    }
#endif
    append_string_str(_out_buffer, str);
}

void dump_output_buffer(void) {
    LEGEND("begin output buffer");
    TRACE("statistics: cap: %d, len: %d", _out_buffer->cap, _out_buffer->len);
    LEGEND(NULL);
    fwrite(_out_buffer->buffer, sizeof(char), _out_buffer->len, stdout);
    LEGEND("end output buffer");
}

