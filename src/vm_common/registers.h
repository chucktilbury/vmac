#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include <stdint.h>
#include "opcodes.h"
typedef uint64_t vm_register_t;
extern vm_register_t registers[MAX_REGS];

// register as a uint64_t
#define REG(n) (registers[n])
// register cast to a specific type
#define REG_AS(r, t) (*((t*)&REG(r)))

#define IP_REG (REG(REG_IP))
#define SP_REG (REG(REG_SP))

// just the one flag bit
#define SET_TRUE_FLAG (REG(REG_FLAGS) = 0x01)
#define CLR_TRUE_FLAG (REG(REG_FLAGS) = 0x00)
#define GET_TRUE_FLAG REG(REG_FLAGS)

#endif /* _REGISTERS_H_ */
