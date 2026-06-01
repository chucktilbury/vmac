%{
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "parser.h"
#include "emit.h"
#include "string_buffer.h"
static string_t* strbuf = NULL;

static int _get_int_size(int64_t val) {

    if(val >= INT8_MIN && val <= INT8_MAX)
        return LITERAL_INT8;
    else if(val >= INT16_MIN && val <= INT16_MAX)
        return LITERAL_INT16;
    else if(val >= INT32_MIN && val <= INT32_MAX)
        return LITERAL_INT32;
    else if(val >= INT64_MIN && val <= INT64_MAX)
        return LITERAL_INT64;
    return LITERAL_INT64;
}

static int _get_uint_size(uint64_t val) {

    if(val <= UINT8_MAX)
        return LITERAL_UINT8;
    else if(val <= UINT16_MAX)
        return LITERAL_UINT16;
    else if(val <= UINT32_MAX)
        return LITERAL_UINT32;
    else if(val <= UINT64_MAX)
        return LITERAL_UINT64;
    return LITERAL_UINT64;
}

%}

%x DQUOTE

%option yylineno
%option noinput
%option nounput
%option noyywrap

%%
"#" { return '#'; }
":" { return ':'; }
"=" { return '='; }
"[" { return '['; }
"]" { return ']'; }
"," { return ','; }

"INT8"  { return INT8; }
"INT16" { return INT16; }
"INT32" { return INT32; }
"INT64" { return INT64; }
"UINT8" { return UINT8; }
"UINT16"    { return UINT16; }
"UINT32"    { return UINT32; }
"UINT64"    { return UINT64; }
"STRING"     { return STRING; }

"R00"|"R0"  { return R00; }
"R01"|"R1"  { return R01; }
"R02"|"R2"  { return R02; }
"R03"|"R3"  { return R03; }
"R04"|"R4"  { return R04; }
"R05"|"R5"  { return R05; }
"R06"|"R6"  { return R06; }
"R07"|"R7"  { return R07; }
"R08"|"R8"  { return R08; }
"R09"|"R9"  { return R09; }
"R10" { return R10; }
"R11" { return R11; }
"R12" { return R12; }
"R13" { return R13; }
"R14" { return R14; }
"R15" { return R15; }
"R16" { return R16; }
"R17" { return R17; }
"R18" { return R18; }
"R19" { return R19; }
"R20" { return R20; }
"R21" { return R21; }
"R22" { return R22; }
"R23" { return R23; }
"R24" { return R24; }
"R25" { return R25; }
"R26" { return R26; }
"R27" { return R27; }
"R28" { return R28; }
"R29" { return R29; }
"R30" { return R30; }
"R31" { return R31; }
"SP"|"STACK" { return SP; }
"IP" { return IP; }

"MOV"|"MOVE" { return MOV; }
"PUSH"  { return PUSH; }
"POP"   { return POP; }
"ADD"   { return ADD; }
"SUB"   { return SUB; }
"MUL"   { return MUL; }
"DIV"   { return DIV; }
"MOD"   { return MOD; }
"ADDU"  { return ADDU; }
"SUBU"  { return SUBU; }
"MULU"  { return MULU; }
"DIVU"  { return DIVU; }
"MODU"  { return MODU; }
"INC"   { return INC; }
"DEC"   { return DEC; }
"INCU"  { return INCU; }
"DECU"  { return DECU; }
"SHL"   { return SHL; }
"SHR"   { return SHR; }
"AND"   { return AND; }
"OR"    { return OR; }
"XOR"   { return XOR; }
"NOT"   { return NOT; }
"EQU"   { return EQU; }
"EQUU"  { return EQUU; }
"NEQ"   { return NEQ; }
"NEQU"  { return NEQU; }
"LT"    { return LT; }
"LTU"   { return LTU; }
"GT"    { return GT; }
"GTU"   { return GTU; }
"LTE"   { return LTE; }
"LTEU"  { return LTEU; }
"GTE"   { return GTE; }
"GTEU"  { return GTEU; }
"JMP"   { return JMP; }
"JMPT"  { return JMPT; }
"JMPF"  { return JMPF; }
"JMPR"  { return JMPR; }
"JMPRT" { return JMPRT; }
"JMPRF" { return JMPRF; }
"CALL"  { return CALL; }
"CALLT" { return CALLT; }
"CALLF" { return CALLF; }
"CALLR" { return CALLR; }
"CALLRT"    { return CALLRT; }
"CALLRF"    { return CALLRF; }
"RET"   { return RET; }
"RETT"  { return RETT; }
"RETF"  { return RETF; }
"EXTERN"    { return EXTERN; }
"LOAD"  { return LOAD; }
"CLRT"  { return CLRT; }
"SETT"  { return SETT; }
"EXIT"  { return EXIT; }
"ABORT" { return ABORT; }
"NOP"   { return NOP; }


[a-zA-Z_][a-zA-Z_0-9]* {
    yylval.str = _COPY_STRING(yytext);
    return NAME;
}

"0"|(-?[1-9][0-9]*) {
    yylval.inum = strtol(yytext, NULL, 10);
    return _get_int_size(yylval.inum);
}

"0x"[0-9a-fA-F]* {
    yylval.unum = strtoll(yytext, NULL, 16);
    return _get_uint_size(yylval.unum);
}

(([1-9][0-9]*\.[0-9]+)|(0\.[0-9]+))([eE][-+]?[0-9]+)? {
    yylval.fnum = strtod(yytext, NULL);
    return LITERAL_FLOAT;
}

\" {
    if(strbuf == NULL)
        strbuf = create_string(NULL);
    else
        clear_string(strbuf);
    BEGIN(DQUOTE);
}

<DQUOTE>\n {
    fprintf(stderr, "scanner error: %d: unexpected end of line in literal string\n", yylineno);
    BEGIN(INITIAL);
}

<DQUOTE>\\n { append_string_char(strbuf, '\n'); }
<DQUOTE>\\r { append_string_char(strbuf, '\r'); }
<DQUOTE>\\t { append_string_char(strbuf, '\t'); }
<DQUOTE>\\v { append_string_char(strbuf, '\v'); }
<DQUOTE>\\a { append_string_char(strbuf, '\a'); }
<DQUOTE>\\b { append_string_char(strbuf, '\b'); }
<DQUOTE>\\f { append_string_char(strbuf, '\f'); }
<DQUOTE>\\e { append_string_char(strbuf, '\x1b'); }
<DQUOTE>\\\" { append_string_char(strbuf, '\"'); }
<DQUOTE>\\. { append_string_char(strbuf, yytext[1]); }

<DQUOTE>\\[xX][0-9A-Fa-f]{1,4} {
    int tmp = strtol(&yytext[2], NULL, 16);
    append_string_char(strbuf, tmp);
}

<DQUOTE>\"[ \t]*\\[ \t]*\n[ \t]*\" { /* line ignore continuation */ }

<DQUOTE>[^\\\n\"]+ { append_string(strbuf, yytext); }

<DQUOTE>\" {
    yylval.str = _COPY_STRING(strbuf->buffer);
    BEGIN(INITIAL);
    return QSTR;
}

[ \t\r\n\v\f]+ { /* ignore spaces */ }

. { warning("unexpected character: %c (0x%02X)", yytext[0], yytext[0]); }


%%

void yyerror(const char* str) {
    error("%s:%d %s", get_cmd_opt("ifile")->buffer, yylineno, str);
}