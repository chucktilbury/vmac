#ifndef _FETCH_H_
#define _FETCH_H_

#include <stdint.h>
#include "byte_buffer.h"
#include "registers.h"
#include "opcodes.h"

extern byte_buffer_t* _code;

static inline uint8_t _fetch_8(void) {

    uint8_t val = *((uint8_t*)(&_code->buffer[IP_REG]));
    IP_REG += sizeof(uint8_t);
    return val;
}

static inline uint16_t _fetch_16(void) {

    uint16_t val = *((uint16_t*)(&_code->buffer[IP_REG]));
    IP_REG += sizeof(uint16_t);
    return val;
}

static inline uint32_t _fetch_32(void) {

    uint32_t val = *((uint32_t*)(&_code->buffer[IP_REG]));
    IP_REG += sizeof(uint32_t);
    return val;
}

static inline uint64_t _fetch_64(void) {

    uint64_t val = *((uint64_t*)(&_code->buffer[IP_REG]));
    IP_REG += sizeof(uint64_t);
    return val;
}

#endif /* _FETCH_H_ */
