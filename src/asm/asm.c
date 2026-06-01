#include "common.h"
#include "symbols.h"
#include "emit.h"
#include "scanner.h"
#include "parser.h"
#include "./trace.h"
#include "emit_to_buffers.h"
#include "update_references.h"


void cmdline(int argc, char** argv, char** env) {

    init_cmdline("asm", "assembler", "0.1");
    add_cmdline('i', "infile", "ifile", "Specify the input file name", NULL, NULL, CMD_STR | CMD_ARGS | CMD_REQD);
    add_cmdline('o', "outfile", "ofile", "Specify the output file name", NULL, NULL, CMD_STR | CMD_ARGS | CMD_REQD);
    //add_cmdline('I', NULL, "path", "Add to the import path", NULL, NULL, CMD_STR | CMD_ARGS | CMD_LIST);
    add_cmdline('v', "verbosity", "verbosity", "Print more information", "1", NULL, CMD_NUM | CMD_ARGS);
    add_cmdline('h', "help", NULL, "Print this helpful information", NULL, cmdline_help, CMD_NONE);
    add_cmdline('V', "version", NULL, "Show the program version", NULL, cmdline_vers, CMD_NONE);
    parse_cmdline(argc, argv, env);

    verbosity = atoi(raw_string(get_cmd_opt("verbosity")));

    setup_env();
}

int main(int argc, char** argv, char** env) {

    cmdline(argc, argv, env);

// printf("sizeof(ast_data_label_t) = %lu\n", sizeof(ast_data_label_t));
// printf("sizeof(ast_data_definition_t) = %lu\n", sizeof(ast_data_definition_t));
// printf("sizeof(ast_instruction_t) = %lu\n", sizeof(ast_instruction_t));

    ENTER;
    string_t* fname = get_cmd_opt("ifile");

    //load_input_buffer(fname);
    FILE* fp = fopen(fname->buffer, "r");
    if(fp == NULL) {
        error("cannot open input file: \"%s\": %s", fname->buffer, strerror(errno));
        exit(1);
    }
    else
        yyin = fp;

    init_output_buffer();
    yyparse();
    emit_to_buffers();
    update_references();

    fname = get_cmd_opt("ofile");
    save_buffers(fname->buffer);

#ifdef USE_TRACE
    if(verbosity >= DEFAULT_TRACE - 10) {
        dump_buffers();
        dump_symbol_table();
    }

    // if(verbosity >= DEFAULT_TRACE + 10)
    //     show_trace();
#endif


    if(verbosity && fname != NULL) {
        printf("%d errors, %d warnings\n", get_errors(), get_warnings());
    }

    RETURN(0);
}
