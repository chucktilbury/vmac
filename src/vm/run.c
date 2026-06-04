#include "vm.h"
#include "fetch.h"
#include "operands.h"
#include "class1.h"
#include "class2.h"
#include "class3.h"
#include "class4.h"
#include "class5.h"
#include "class6.h"
#include "class7.h"
#include "class8.h"

void run(void) {
    ENTER;

    WRITE_REGISTER(REG_IP, 0);
    bool finished = false;
    while(!finished) {
        opcode_t op = _fetch_8();
        TRACE("instruction: %s", opcode_to_str(op));
        switch(op) {
            // class 1 instructions
            case OP_ADD:    _add();    break;
            case OP_SUB:    _sub();    break;
            case OP_MUL:    _mul();    break;
            case OP_DIV:    _div();    break;
            case OP_MOD:    _mod();    break;
            case OP_ADDU:   _addu();   break;
            case OP_SUBU:   _subu();   break;
            case OP_MULU:   _mulu();   break;
            case OP_DIVU:   _divu();   break;
            case OP_MODU:   _modu();   break;
            case OP_AND:    _and();    break;
            case OP_OR:     _or();     break;
            case OP_XOR:    _xor();    break;

            // class 2 instructions
            case OP_SHL:    _shl();    break;
            case OP_SHR:    _shr();    break;

            // class 3 instructions
            case OP_INC:    _inc();    break;
            case OP_DEC:    _dec();    break;
            case OP_INCU:   _incu();   break;
            case OP_DECU:   _decu();   break;
            case OP_NOT:    _not();    break;

            // class 4 instructions
            case OP_MOV:    _mov();    break;
            case OP_EQU:    _equ();    break;
            case OP_EQUU:   _equu();   break;
            case OP_NEQ:    _neq();    break;
            case OP_NEQU:   _nequ();   break;
            case OP_LT:     _lt();     break;
            case OP_LTU:    _ltu();    break;
            case OP_GT:     _gt();     break;
            case OP_GTU:    _gtu();    break;
            case OP_LTE:    _lte();    break;
            case OP_LTEU:   _lteu();   break;
            case OP_GTE:    _gte();    break;
            case OP_GTEU:   _gteu();   break;

            // class 5 instructions
            case OP_JMP:    _jmp();    break;
            case OP_JMPT:   _jmpt();   break;
            case OP_JMPF:   _jmpf();   break;
            case OP_JMPR:   _jmpr();   break;
            case OP_JMPRT:  _jmprt();  break;
            case OP_JMPRF:  _jmprf();  break;
            case OP_CALL:   _call();   break;
            case OP_CALLT:  _callt();  break;
            case OP_CALLF:  _callf();  break;
            case OP_CALLR:  _callr();  break;
            case OP_CALLRT: _callrt(); break;
            case OP_CALLRF: _callrf(); break;

            // class 6 instructions
            case OP_PUSH:   _push();   break;
            case OP_POP:    _pop();    break;

            // class 7 instructions
            case OP_RET:    _ret();    break;
            case OP_RETT:   _rett();   break;
            case OP_RETF:   _retf();   break;
            case OP_CLRT:   _clrt();   break;
            case OP_SETT:   _sett();   break;
            case OP_EXIT:   _exit();   break;
            case OP_ABORT:  _abort();  break;
            case OP_NOP:    _nop();    break;
            case OP_BREAK:  _break();  break;

            // class 8 instructions
            case OP_EXTERN: _extern(); break;
            case OP_LOAD:   _load();   break;

            default: error("expected instruction but got %s at 0x%08lX", opcode_to_str(op), IP_REG);
        }

        if(IP_REG >= (vm_register_t)_code->len)
            finished = true;
    }

    RETURN();
}

