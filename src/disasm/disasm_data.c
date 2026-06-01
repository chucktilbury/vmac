#include "common.h"

extern byte_buffer_t* _code;
extern byte_buffer_t* _data;

static const char* _convert_char(uint8_t ch) {

    static char buf[8];

    if(isprint(ch)) {
        buf[0] = ch;
        buf[1] = '\0';
    }
    else
        sprintf(buf, "\\x%02X", ch);

    return buf;
}

void disasm_data(FILE* fp) {

    ENTER;
    fputs("/*\n *  data section\n */\n", fp);
    bool finished = false;
    bool is_array = false;
    size_t tmp, mark = 0;
    while(!finished) {
        tmp = mark;
        uint8_t op = iterate_byte_buffer_uint8(_data, &mark);
        fprintf(fp, "%s _%08lX_data = ", opcode_to_str(op), tmp);

        uint16_t len = read_byte_buffer_uint8(_data, mark);
        if(len == OPERAND_ARRAY) {
            iterate_byte_buffer_uint8(_data, &mark); // consume the marker
            len = iterate_byte_buffer_uint16(_data, &mark); // get the size
            is_array = true;
            fputc('[', fp);
        }
        else {
            len = 1;
            is_array = false;
        }

        for(uint16_t i = 0; i < len; i++) {
            switch(op) {
                case OPERAND_INT8: {
                        uint8_t val = iterate_byte_buffer_uint8(_data, &mark);
                        fprintf(fp, "%d", (int8_t)val);
                    }
                    break;
                case OPERAND_INT16: {
                        uint16_t val = iterate_byte_buffer_uint16(_data, &mark);
                        fprintf(fp, "%d", (int16_t)val);
                    }
                    break;
                case OPERAND_INT32: {
                        uint32_t val = iterate_byte_buffer_uint32(_data, &mark);
                        fprintf(fp, "%d", (int32_t)val);
                    }
                    break;
                case OPERAND_INT64: {
                        uint64_t val = iterate_byte_buffer_uint64(_data, &mark);
                        fprintf(fp, "%ld", (int64_t)val);
                    }
                    break;
                case OPERAND_UINT8: {
                        uint8_t val = iterate_byte_buffer_uint8(_data, &mark);
                        fprintf(fp, "0x%02X", val);
                    }
                    break;
                case OPERAND_UINT16: {
                        uint16_t val = iterate_byte_buffer_uint16(_data, &mark);
                        fprintf(fp, "0x%04X", val);
                    }
                    break;
                case OPERAND_UINT32: {
                        uint32_t val = iterate_byte_buffer_uint32(_data, &mark);
                        fprintf(fp, "0x%08X", val);
                    }
                    break;
                case OPERAND_UINT64: {
                        uint64_t val = iterate_byte_buffer_uint64(_data, &mark);
                        fprintf(fp, "0x%016lX", val);
                    }
                    break;
                case OPERAND_FLOAT: {
                        uint64_t val = iterate_byte_buffer_uint64(_data, &mark);
                        fprintf(fp, "%lf", *((double*)&val));
                    }
                    break;
                case OPERAND_STRING: {
                        uint16_t slen = iterate_byte_buffer_uint16(_data, &mark);
                        fputc('\"', fp);
                        for(uint16_t i = 0; i < slen; i++) {
                            uint8_t ch = iterate_byte_buffer_uint8(_data, &mark);
                            fprintf(fp, "%s", _convert_char(ch));
                        }
                        fputs("\"", fp);
                    }
                    break;
                default:
                    error("unknown operand type: %s", opcode_to_str(op));
            }
            if(is_array && i+1 < len)
                fputs(", ", fp);
        }
        if(is_array)
            fputc(']', fp);
        fputc('\n', fp);

        if(mark >= _data->len)
            finished = true;
    }

    fputs("\n", fp);
    RETURN();
}

