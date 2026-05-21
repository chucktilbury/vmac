#ifndef _EMIT_H_
#define _EMIT_H_

#include "string_buffer.h"

void create_output_buffer(void);
void destroy_output_buffer(void);
void write_output_buffer(string_t* fname);
void emit_char(int ch);
void emit_str(const char* str);
void emit_string(string_t* str);
void dump_output_buffer(void);

#define EMITC(c) emit_char(c)
#define EMITS(s) emit_string(s)
#define EMITR(s) emit_str(s)

#endif /* _EMIT_H_ */
