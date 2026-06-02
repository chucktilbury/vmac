#ifndef _REGISTERS_H_
#define _REGISTERS_H_

#include <stdint.h>
typedef int64_t register_t;
extern register_t registers[34];

#define READ_REGISTER(n) (registers[n])
#define WRITE_REGISTER(n, v) ((registers[n])=(register_t)(v))
#define REG(n) (registers[n])
#define IP_REG (REG(REG_IP))
#define SP_REG (REG(REG_SP))

#endif /* _REGISTERS_H_ */
