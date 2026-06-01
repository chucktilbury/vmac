#include "common.h"
#include "classify.h"
#include "operand.h"
#include "disasm_data.h"
#include "disasm_code.h"
#include "scan.h"

byte_buffer_t* _data = NULL;
byte_buffer_t* _code = NULL;

void load_file(string_t* fname) {

    ENTER;
    TRACE("file name: %s", fname->buffer);

    FILE* fp = fopen(fname->buffer, "r");
    if(fp == NULL)
        error("cannot open input file \"%s\": %s", fname->buffer, strerror(errno));

    size_t magic[2];
    fread(magic, sizeof(size_t), 2, fp);
    _code = load_byte_buffer(fp);
    fread(magic, sizeof(size_t), 2, fp);
    _data = load_byte_buffer(fp);
    fread(magic, sizeof(size_t), 2, fp);

    fclose(fp);

    RETURN();
}


void cmdline(int argc, char** argv, char** env) {

    init_cmdline("disasm", "dis-assembler", "0.1");
    add_cmdline('i', "infile", "ifile", "Specify the input file name", NULL, NULL, CMD_STR | CMD_ARGS | CMD_REQD);
    add_cmdline('o', "outfile", "ofile", "Specify the output file name", NULL, NULL, CMD_STR | CMD_ARGS);
    // add_cmdline('I', NULL, "path", "Add to the import path", NULL, NULL, CMD_STR | CMD_ARGS | CMD_LIST);
    add_cmdline('v', "verbosity", "verbosity", "Print more information", "1", NULL, CMD_NUM | CMD_ARGS);
    add_cmdline('h', "help", NULL, "Print this helpful information", NULL, cmdline_help, CMD_NONE);
    add_cmdline('V', "version", NULL, "Show the program version", NULL, cmdline_vers, CMD_NONE);
    parse_cmdline(argc, argv, env);
    verbosity = atoi(raw_string(get_cmd_opt("verbosity")));
    setup_env();
}

int main(int argc, char** argv, char** env) {

    cmdline(argc, argv, env);

    ENTER;

    string_t* fname = get_cmd_opt("ifile");
    load_file(fname);
    fname = get_cmd_opt("ofile");
    FILE* fp = NULL;
    if(fname != NULL) {
        fp = fopen(fname->buffer, "w");
        if(fp == NULL)
            error("cannot open output file \"%s\": %s", fname->buffer, strerror(errno));
    }
    else
        fp = stdout;

#ifdef USE_TRACE
    if(verbosity >= DEFAULT_TRACE - 10) {
        fputs("/*\n", fp);
        fprintf(fp, "-- data buffer\n");
        hexdump(_data->buffer, _data->len);
        fprintf(fp, "\n-- code buffer\n");
        hexdump(_code->buffer, _code->len);
        fputs("\n*/\n\n", fp);

    }
#endif

    scan_code();
    disasm_data(fp);
    disasm_code(fp);
    fputc('\n', fp);

    RETURN(0);
}
