#ifndef _EMIT_H_
#define _EMIT_H_

#include <stddef.h>
#include <stdint.h>
#include "operands.h"
#include "opcodes.h"

void init_output_buffer(void);
void destroy_output_buffer(void);

void emit_data(opcode_t type, void* val);
void emit_data_int8(int8_t val);
void emit_data_int16(int16_t val);
void emit_data_int32(int32_t val);
void emit_data_int64(int64_t val);
void emit_data_uint8(uint8_t val);
void emit_data_uint16(uint16_t val);
void emit_data_uint32(uint32_t val);
void emit_data_uint64(uint64_t val);
void emit_data_fnum(double val);
void emit_data_str(const char* str);
void emit_data_operand(operand_t* op);
uint32_t get_data_index(void);

void emit_code(opcode_t type, void* val);
void emit_code_int8(int8_t val);
void emit_code_int16(int16_t val);
void emit_code_int32(int32_t val);
void emit_code_int64(int64_t val);
void emit_code_uint8(uint8_t val);
void emit_code_uint16(uint16_t val);
void emit_code_uint32(uint32_t val);
void emit_code_uint64(uint64_t val);
void emit_code_operand(operand_t* op);
void write_code_uint32(uint32_t val, uint32_t idx);
uint32_t get_code_index(void);

void save_buffers(const char* fname);
void dump_buffers(void);

#endif /* _EMIT_H_ */
