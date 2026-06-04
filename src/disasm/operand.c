
#include "common.h"
#include "symbols.h"

extern byte_buffer_t* _code;
extern byte_buffer_t* _data;
extern bool debug_flag;

void do_operand(FILE* fp, size_t* mark) {
    opcode_t op = iterate_byte_buffer_uint8(_code, mark);
    switch(op) {
        case OPERAND_INT8: {
            int8_t val = (int8_t)iterate_byte_buffer_uint8(_code, mark);
            fprintf(fp, "%d", val);
        } break;
        case OPERAND_INT16: {
            int16_t val = (int16_t)iterate_byte_buffer_uint16(_code, mark);
            fprintf(fp, "%d", val);
        } break;
        case OPERAND_INT32: {
            int32_t val = (int32_t)iterate_byte_buffer_uint32(_code, mark);
            fprintf(fp, "%d", val);
        } break;
        case OPERAND_INT64: {
            int64_t val = (int64_t)iterate_byte_buffer_uint64(_code, mark);
            fprintf(fp, "%ld", val);
        } break;
        case OPERAND_UINT8: {
            uint8_t val = (uint8_t)iterate_byte_buffer_uint8(_code, mark);
            fprintf(fp, "0x%02X", val);
        } break;
        case OPERAND_UINT16: {
            uint16_t val = iterate_byte_buffer_uint16(_code, mark);
            fprintf(fp, "0x%04X", val);
        } break;
        case OPERAND_UINT32: {
            uint32_t val = iterate_byte_buffer_uint32(_code, mark);
            fprintf(fp, "0x%08X", val);
        } break;
        case OPERAND_UINT64: {
            uint64_t val = iterate_byte_buffer_uint64(_code, mark);
            fprintf(fp, "0x%016lX", val);
        } break;
        case OPERAND_FLOAT: {
            uint64_t val = iterate_byte_buffer_uint64(_code, mark);
            fprintf(fp, "%f", *((double*)&val));
        } break;
        case OPERAND_IREG:
        case OPERAND_REG: {
            opcode_t reg = iterate_byte_buffer_uint8(_code, mark);
            fprintf(fp, "%s", opcode_to_str(reg));
        } break;
        case OPERAND_LABEL: {
            uint32_t idx = iterate_byte_buffer_uint32(_code, mark);
            if(debug_flag) {
                symbol_t* sym = find_symbol(idx >>= 0x01);
                if(sym != NULL)
                    fprintf(fp, "%s", sym->tag->buffer);
            }
            else
                fprintf(fp, "_%08X_code", idx);
        } break;
        case OPERAND_ILABEL: {
            uint32_t idx = iterate_byte_buffer_uint32(_code, mark);
            if(debug_flag) {
                symbol_t* sym = find_symbol(idx >>= 0x01);
                if(sym != NULL)
                    fprintf(fp, "# %s", sym->tag->buffer);
            }
            else
                fprintf(fp, "_%08X_data", idx >>= 0x01);
        } break;
        default:
            error("invalid operand type: %s", opcode_to_str(op));
    }
}
