#ifndef _PARSE_H_
#define _PARSE_H_

#include "string_buffer.h"

typedef enum {
    NOT_A_DIRECTIVE,
    IF_DIRECTIVE,
    ELSE_DIRECTIVE,
    DEFINE_DIRECTIVE,
    IMPORT_DIRECTIVE,
    MESSAGE_DIRECTIVE,
    ERROR_DIRECTIVE,
} directive_type_t;

void consume_space(void);
void emit_space(void);
void test_end_error(void);
//const char* prnch(int ch);
string_t* scan_name(void);
string_t* scan_literal_string(void);
directive_type_t directive_type(string_t* str);

void parse_error(void);
void parse_message(void);
void parse_import(void);
void parse_comment(void);
void parse_directive(void);
void parse_input(void);

#ifdef USE_TRACE
#define PRNCH do { \
    if(verbosity >= DEFAULT_TRACE + 10) {   \
        INDENT;                        \
        printf("PRNCH: '"); \
        prnch(crnt_char()); \
        printf("': %s:%d:%d\n", raw_string(get_file_name()), get_line_no(), get_col_no()); \
    } \
} while(false)
#else
#define PRNCH
#endif

#endif /* _PARSE_H_ */
