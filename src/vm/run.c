#include "vm.h"
#include "fetch.h"
//#include "operands.h"
#include "class1.h"
#include "class2.h"
#include "class3.h"
#include "class4.h"
#include "class5.h"
#include "class6.h"
#include "class7.h"
#include "class8.h"

typedef void(*func_t)(void);
static func_t instr_table[] = {
    _break, _mov, _push, _pop, _add, _sub, _mul, _div, _mod,
    _addu, _subu, _mulu, _divu, _modu, _inc, _dec, _incu, _decu,
    _shl, _shr, _and, _or, _xor, _not, _equ, _equu, _neq, _nequ, _lt,
    _ltu, _gt, _gtu, _lte, _lteu, _gte, _gteu, _jmp, _jmpt, _jmpf,
    _jmpr, _jmprt, _jmprf, _call, _callt, _callf, _callr, _callrt,
    _callrf, _ret, _rett, _retf, _extern, _load, _clrt, _sett, __exit,
    _abort, _nop
};

void run(void) {
    ENTER;

    IP_REG = 0;
    SP_REG = 0;

    bool finished = false;
    while(!finished) {
        opcode_t op = _fetch_8();
        TRACE("instruction: %s", opcode_to_str(op));

        if(INSTR_IDX(op) >= 0 && INSTR_IDX(op) <= MAX_INSTRUCTION)
            instr_table[INSTR_IDX(op)]();
        else
            error("expected instruction but got %s at 0x%08lX", opcode_to_str(op), IP_REG);

        if(IP_REG >= (vm_register_t)_code->len)
            finished = true;
    }

    RETURN();
}
