#ifndef _BYTE_BUFFER_H_
#define _BYTE_BUFFER_H_

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct _byte_buffer_t {
    uint8_t* buffer;
    size_t cap;
    size_t len;
} byte_buffer_t;

byte_buffer_t* create_byte_buffer(void);
void destroy_byte_buffer(byte_buffer_t* buf);

void write_byte_buffer_uint8(byte_buffer_t* buf, uint8_t val);
void write_byte_buffer_uint16(byte_buffer_t* buf, uint16_t val);
void write_byte_buffer_uint32(byte_buffer_t* buf, uint32_t val);
void write_byte_buffer_uint64(byte_buffer_t* buf, uint64_t val);
void write_byte_buffer_str(byte_buffer_t* buf, const char* str);
size_t get_byte_buffer_write_index(byte_buffer_t* buf);

uint8_t read_byte_buffer_uint8(byte_buffer_t* buf, size_t index);
uint16_t read_byte_buffer_uint16(byte_buffer_t* buf, size_t index);
uint32_t read_byte_buffer_uint32(byte_buffer_t* buf, size_t index);
uint64_t read_byte_buffer_uint64(byte_buffer_t* buf, size_t index);
const char* read_byte_buffer_str(byte_buffer_t* buf, size_t index);

uint8_t iterate_byte_buffer_uint8(byte_buffer_t* buf, size_t* mark);
uint16_t iterate_byte_buffer_uint16(byte_buffer_t* buf, size_t* mark);
int32_t iterate_byte_buffer_uint32(byte_buffer_t* buf, size_t* mark);
uint64_t iterate_byte_buffer_uint64(byte_buffer_t* buf, size_t* mark);

byte_buffer_t* load_byte_buffer(FILE* fp);
void save_byte_buffer(byte_buffer_t* buf, FILE* fp);

#endif /* _BYTE_BUFFER_H_ */
