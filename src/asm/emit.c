
#include <stdarg.h>
#include <stdint.h>
#include "common.h"
#include "emit.h"
#include "symbols.h"
#include "parser.h"

#define CAST_TO(t, v) (t)(*(t*)(v))

byte_buffer_t* data_buffer = NULL;
byte_buffer_t* code_buffer = NULL;
extern byte_buffer_t* debug_buffer;
extern bool debug_flag;

static void _emit_literal(byte_buffer_t* buf, opcode_t type, void* val) {
    ENTER;
    switch(type) {
        case OPERAND_INT8:
            TRACE("%s: %d", opcode_to_str(type), CAST_TO(int8_t, val));
            write_byte_buffer_uint8(buf, CAST_TO(int8_t, val));
            break;
        case OPERAND_INT16:
            TRACE("%s: %d", opcode_to_str(type), CAST_TO(int16_t, val));
            write_byte_buffer_uint16(buf, CAST_TO(int16_t, val));
            break;
        case OPERAND_INT32:
            TRACE("%s: %d", opcode_to_str(type), CAST_TO(int32_t, val));
            write_byte_buffer_uint32(buf, CAST_TO(int32_t, val));
            break;
        case OPERAND_INT64:
            TRACE("%s: %ld", opcode_to_str(type), CAST_TO(int64_t, val));
            write_byte_buffer_uint64(buf, CAST_TO(int64_t, val));
            break;
        case OPERAND_UINT8:
            TRACE("%s: 0x%X", opcode_to_str(type), CAST_TO(uint8_t, val));
            write_byte_buffer_uint8(buf, CAST_TO(uint8_t, val));
            break;
        case OPERAND_UINT16:
            TRACE("%s: 0x%X", opcode_to_str(type), CAST_TO(uint16_t, val));
            write_byte_buffer_uint16(buf, CAST_TO(uint16_t, val));
            break;
        case OPERAND_UINT32:
            TRACE("%s: 0x%X", opcode_to_str(type), CAST_TO(uint32_t, val));
            write_byte_buffer_uint32(buf, CAST_TO(uint32_t, val));
            break;
        case OPERAND_UINT64:
            TRACE("%s: 0x%lX", opcode_to_str(type), CAST_TO(uint64_t, val));
            write_byte_buffer_uint64(buf, CAST_TO(uint64_t, val));
            break;
        case OPERAND_FLOAT:
            TRACE("%s: %f", opcode_to_str(type), CAST_TO(double, val));
            write_byte_buffer_uint64(buf, CAST_TO(uint64_t, val));
            break;
        case OPERAND_STRING: {
            const char* str = CAST_TO(const char*, val);
            size_t len = strlen(str);
            TRACE("%s: %lu: %s", opcode_to_str(type), len, str);
            write_byte_buffer_uint16(buf, len);
            write_byte_buffer_str(buf, str);
            }
            break;
        case OPERAND_REG:
            TRACE("%s: %s", opcode_to_str(type), opcode_to_str(CAST_TO(int8_t, val)));
            write_byte_buffer_uint8(buf, CAST_TO(uint8_t, val));
            break;
        case OPERAND_IREG:
            TRACE("%s: %s", opcode_to_str(type), opcode_to_str(CAST_TO(int8_t, val)));
            write_byte_buffer_uint8(buf, CAST_TO(uint8_t, val));
            break;
        case OPERAND_ARRAY:
            TRACE("%s: %d", opcode_to_str(type), CAST_TO(int8_t, val));
            write_byte_buffer_uint8(buf, OPERAND_ARRAY);
            break;
        case OPERAND_LABEL: {
                TRACE("%s: 0x%08lX", opcode_to_str(type), CAST_TO(int64_t, val));
                opcode_t size = get_uint_size(CAST_TO(uint64_t, val));
                TRACE("size: %s", opcode_to_str(size));
                write_byte_buffer_uint8(buf, size);
                _emit_literal(buf, size, val); // recursive entry
            }
            break;
        default: error("unknown data type in emit_data()");
    }
    RETURN();
}

void init_output_buffer(void) {
    data_buffer = create_byte_buffer();
    code_buffer = create_byte_buffer();
}

void destroy_output_buffer(void) {
    destroy_byte_buffer(data_buffer);
    destroy_byte_buffer(code_buffer);
}

void emit_data(opcode_t type, void* val) {
    ENTER;
    TRACE("type %s", opcode_to_str(type));
    _emit_literal(data_buffer, type, val);
    RETURN();
}

void emit_data_int8(int8_t val) {
    write_byte_buffer_uint8(data_buffer, val);
}

void emit_data_int16(int16_t val) {
    write_byte_buffer_uint16(data_buffer, val);
}

void emit_data_int32(int32_t val) {
    write_byte_buffer_uint32(data_buffer, val);
}

void emit_data_int64(int64_t val) {
    write_byte_buffer_uint64(data_buffer, val);
}

void emit_data_fnum(double val) {
    write_byte_buffer_uint64(data_buffer, val);
}

void emit_data_uint8(uint8_t val) {
    write_byte_buffer_uint8(data_buffer, val);
}

void emit_data_uint16(uint16_t val) {
    write_byte_buffer_uint16(data_buffer, val);
}

void emit_data_uint32(uint32_t val) {
    write_byte_buffer_uint32(data_buffer, val);
}

void emit_data_uint64(uint64_t val) {
    write_byte_buffer_uint64(data_buffer, val);
}

void emit_data_str(const char* str) {
    write_byte_buffer_str(data_buffer, str);
}

uint32_t get_data_index(void) {
    return get_byte_buffer_write_index(data_buffer);
}

void emit_data_operand(operand_t* op) {
    ENTER;
    emit_data_uint8(op->type);
    emit_data(op->type, (void*)&op->value);
    RETURN();
}

void emit_code(opcode_t type, void* val) {
    ENTER;
    TRACE("type %s", opcode_to_str(type));
    _emit_literal(code_buffer, type, val);
    RETURN();
}

void emit_code_int8(int8_t val) {
    write_byte_buffer_uint8(code_buffer, val);
}

void emit_code_int16(int16_t val) {
    write_byte_buffer_uint16(code_buffer, val);
}

void emit_code_int32(int32_t val) {
    write_byte_buffer_uint32(code_buffer, val);
}
void emit_code_int64(int64_t val) {
    write_byte_buffer_uint64(code_buffer, val);
}

void emit_code_uint8(uint8_t val) {
    write_byte_buffer_uint8(code_buffer, val);
}

void emit_code_uint16(uint16_t val) {
    write_byte_buffer_uint16(code_buffer, val);
}

void emit_code_uint32(uint32_t val) {
    write_byte_buffer_uint32(code_buffer, val);
}

void emit_code_uint64(uint64_t val) {
    write_byte_buffer_uint64(code_buffer, val);
}

// this function presumes that the index has already been validated
// by the parser.
void write_code_uint32(uint32_t loc, uint32_t val) {

    *((uint32_t*)(&(code_buffer->buffer[loc]))) = val;
}

uint32_t get_code_index(void) {
    return get_byte_buffer_write_index(code_buffer);
}

void emit_code_operand(operand_t* op) {
    ENTER;
    emit_code_uint8(op->type);
    emit_code(op->type, (void*)&op->value);
    RETURN();
}

void save_buffers(const char* fname) {
    ENTER;
    FILE* fp = fopen(fname, "w");
    if(fp == NULL)
        error("cannot open output file \"%s\": %s", fname, strerror(errno));

    size_t magic[2] = {MAGIC_NUMBER, SEPARATOR};
    if(debug_flag)
        magic[0] |= 0x01;

    fwrite(magic, sizeof(size_t), 2, fp);
    save_byte_buffer(code_buffer, fp);

    magic[0] = SEPARATOR;
    fwrite(magic, sizeof(size_t), 2, fp);
    save_byte_buffer(data_buffer, fp);

    if(debug_flag) {
        fwrite(magic, sizeof(size_t), 2, fp);
        if(get_cmd_opt("debug"))
            save_byte_buffer(debug_buffer, fp);
    }

    fwrite(magic, sizeof(size_t), 2, fp);
    fclose(fp);
    RETURN();
}

void dump_buffers(void) {

    if(verbosity >= DEFAULT_TRACE) {
        LEGEND("begin assembler output");

        LEGEND("begin code section");
        hexdump(code_buffer->buffer, code_buffer->len);
        LEGEND("end code section");

        LEGEND("begin data section");
        hexdump(data_buffer->buffer, data_buffer->len);
        LEGEND("end data section");

        if(debug_flag) {
            LEGEND("begin debug section");
            hexdump(debug_buffer->buffer, debug_buffer->len);
            LEGEND("end debug section");
        }

        LEGEND("end assembler output");
    }
}

