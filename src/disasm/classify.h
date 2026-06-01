#ifndef _CLASSIFY_H_
#define _CLASSIFY_H_

#include "opcodes.h"

typedef enum _inst_class_t {
    CLASS_1,
    CLASS_2,
    CLASS_3,
    CLASS_4,
    CLASS_5,
    CLASS_6,
    CLASS_7,
    CLASS_8,
} inst_class_t;

inst_class_t classify_instruction(opcode_t op);

#endif /* _CLASSIFY_H_ */
