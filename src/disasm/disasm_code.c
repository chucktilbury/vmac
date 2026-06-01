#include "common.h"
#include "classify.h"
#include "operand.h"
#include "scan.h"

extern byte_buffer_t* _code;
extern byte_buffer_t* _data;

void disasm_code(FILE* fp) {

    ENTER;
    //fputs("\n", fp);
    fputs("/*\n *  code section\n */\n", fp);
    bool finished = false;
    size_t mark = 0;

    fprintf(fp, "_00000000_code_start:\n");
    while(!finished) {
        pseudo_sym_t* sym = find_sym(mark);
        if(sym != NULL)
            fprintf(fp, "_%08lX_code:\n", mark);

        opcode_t op = iterate_byte_buffer_uint8(_code, &mark);
        fprintf(fp, "\t%s ", opcode_to_str(op));
        switch(classify_instruction(op)) {
            case CLASS_1:
                fprintf(fp, "%s", opcode_to_str(iterate_byte_buffer_uint8(_code, &mark)));
                //do_operand(fp, &mark);
                fputs(", ", fp);
                do_operand(fp, &mark);
                fputs(", ", fp);
                do_operand(fp, &mark);
                fputc('\n', fp);
                break;
            case CLASS_2:
                fprintf(fp, "%s", opcode_to_str(iterate_byte_buffer_uint8(_code, &mark)));
                //do_operand(fp, &mark);
                fputs(", ", fp);
                do_operand(fp, &mark);
                fputs(", ", fp);
                do_operand(fp, &mark);
                fputc('\n', fp);
                break;
            case CLASS_3:
            case CLASS_4:
                do_operand(fp, &mark);
                fputs(", ", fp);
                do_operand(fp, &mark);
                fputc('\n', fp);
                break;
            case CLASS_5:
                do_operand(fp, &mark);
                fputc('\n', fp);
                break;
            case CLASS_6:
                fprintf(fp, "%s", opcode_to_str(iterate_byte_buffer_uint8(_code, &mark)));
                fputc('\n', fp);
                break;
            case CLASS_7:
                break;
            case CLASS_8:
                do_operand(fp, &mark);
                fputc('\n', fp);
                break;
            default:
                error("bad instruction class (never happens)");
        }

        if(mark >= _code->len)
            finished = true;
    }

    fputs("\n", fp);
    RETURN();
}

