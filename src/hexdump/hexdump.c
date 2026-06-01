#include "common.h"


void cmdline(int argc, char** argv, char** env) {

    init_cmdline("hexdump", "Dump a file as binary hex codes", "0.1");
    add_cmdline('i', "infile", "ifile", "Specify the input file name", NULL, NULL, CMD_STR | CMD_ARGS | CMD_REQD);
    // add_cmdline('o', "outfile", "ofile", "Specify the output file name", NULL, NULL, CMD_STR | CMD_ARGS | CMD_REQD);
    // add_cmdline('I', NULL, "path", "Add to the import path", NULL, NULL, CMD_STR | CMD_ARGS | CMD_LIST);
    // add_cmdline('v', "verbosity", "verbosity", "Print more information", "1", NULL, CMD_NUM | CMD_ARGS);
    add_cmdline('h', "help", NULL, "Print this helpful information", NULL, cmdline_help, CMD_NONE);
    add_cmdline('V', "version", NULL, "Show the program version", NULL, cmdline_vers, CMD_NONE);
    parse_cmdline(argc, argv, env);

    setup_env();
}

int main(int argc, char** argv, char** env) {

    cmdline(argc, argv, env);

    ENTER;
    string_t* fname = get_cmd_opt("ifile");

    load_input_buffer(fname);
    string_t* str = get_crnt_input_buffer();

    if(str != NULL) {
        LEGEND(NULL);
        hexdump((const unsigned char*)str->buffer, str->len);
        LEGEND(NULL);
    }


    RETURN(0);
}
