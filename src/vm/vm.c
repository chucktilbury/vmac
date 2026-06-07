#include "vm.h"

byte_buffer_t* _data = NULL;
byte_buffer_t* _code = NULL;
byte_buffer_t* _debug = NULL;
bool debug_flag = false;

void load_file(string_t* fname) {

    ENTER;
    TRACE("file name: %s", fname->buffer);

    FILE* fp = fopen(fname->buffer, "r");
    if(fp == NULL)
        error("cannot open input file \"%s\": %s", fname->buffer, strerror(errno));

    size_t magic[2];
    fread(magic, sizeof(size_t), 2, fp);
    debug_flag = magic[0] & 0x01;

    _code = load_byte_buffer(fp);
    fread(magic, sizeof(size_t), 2, fp);
    _data = load_byte_buffer(fp);
    fread(magic, sizeof(size_t), 2, fp);

    if(debug_flag) {
        _debug = load_byte_buffer(fp);
        fread(magic, sizeof(size_t), 2, fp);
    }

    fclose(fp);

    RETURN();
}


void cmdline(int argc, char** argv, char** env) {

    init_cmdline("vm", "virtual machine", "0.1");
    add_cmdline('v', "verbosity", "verbosity", "Print more information", "1", NULL, CMD_NUM | CMD_ARGS);
    add_cmdline('d', "debug", "debug", "debug mode", "0", NULL, CMD_SWITCH);
    add_cmdline('h', "help", NULL, "Print this helpful information", NULL, cmdline_help, CMD_NONE);
    add_cmdline('V', "version", NULL, "Show the program version", NULL, cmdline_vers, CMD_NONE);
    add_cmdline(0, NULL, NULL, NULL, NULL, NULL, CMD_DIV);
    add_cmdline(0, NULL, "ifile", "Name of file to input", NULL, NULL, CMD_REQD | CMD_ANON);
    parse_cmdline(argc, argv, env);

    verbosity = atoi(raw_string(get_cmd_opt("verbosity")));
    debug_flag = atoi(raw_string(get_cmd_opt("debug")));

    setup_env();
}

void run(void);

int main(int argc, char** argv, char** env) {

    cmdline(argc, argv, env);

    ENTER;
    string_t* fname = get_cmd_opt("ifile");
    load_file(fname);

    run();

    RETURN(0);
}
