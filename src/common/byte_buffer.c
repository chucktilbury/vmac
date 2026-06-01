
#include "common.h"
#include "byte_buffer.h"

#define RAW_PTR(b, i) (&b->buffer[i])
#define MAKE_WCAST(b, t) ((t*)RAW_PTR(b, b->len))
#define MAKE_RCAST(b, t, i) ((t*)RAW_PTR(b, i))

static inline void _grow_buffer(byte_buffer_t* buf, size_t size) {

    if(buf->len + size > buf->cap) {
        while(buf->len + size > buf->cap)
            buf->cap <<= 1;
        buf->buffer = _REALLOC_ARRAY(buf->buffer, uint8_t, buf->cap);
    }
}

static inline void _validate_index(byte_buffer_t* buf, size_t index) {

    if(!(index < buf->len))
        error("invalid buffer index: %lu", index);
}

byte_buffer_t* create_byte_buffer(void) {

    byte_buffer_t* ptr = _ALLOC_TYPE(byte_buffer_t);
    ptr->cap = 1 << 3;
    ptr->len = 0;
    ptr->buffer = _ALLOC_ARRAY(uint8_t, ptr->cap);

    return ptr;
}

void destroy_byte_buffer(byte_buffer_t* buf) {

    if(buf != NULL) {
        _FREE(buf->buffer);
        _FREE(buf);
    }
}

void write_byte_buffer_uint8(byte_buffer_t* buf, uint8_t val) {

    _grow_buffer(buf, sizeof(uint8_t));
    *MAKE_WCAST(buf, uint8_t) = val;
    buf->len += sizeof(uint8_t);
}

void write_byte_buffer_uint16(byte_buffer_t* buf, uint16_t val) {

    _grow_buffer(buf, sizeof(uint16_t));
    *MAKE_WCAST(buf, uint16_t) = val;
    buf->len += sizeof(uint16_t);
}

void write_byte_buffer_uint32(byte_buffer_t* buf, uint32_t val) {

    _grow_buffer(buf, sizeof(uint32_t));
    *MAKE_WCAST(buf, uint32_t) = val;
    buf->len += sizeof(uint32_t);
}

void write_byte_buffer_uint64(byte_buffer_t* buf, uint64_t val) {

    _grow_buffer(buf, sizeof(uint64_t));
    *MAKE_WCAST(buf, uint64_t) = val;
    buf->len += sizeof(uint64_t);
}

void write_byte_buffer_str(byte_buffer_t* buf, const char* str) {

    for(int i = 0; str[i] != '\0'; i++)
        write_byte_buffer_uint8(buf, str[i]);
    write_byte_buffer_uint8(buf, 0);
}

size_t get_byte_buffer_write_index(byte_buffer_t* buf) {

    return buf->len;
}

uint8_t read_byte_buffer_uint8(byte_buffer_t* buf, size_t index) {

    _validate_index(buf, index);
    return *MAKE_RCAST(buf, uint8_t, index);
}

uint16_t read_byte_buffer_uint16(byte_buffer_t* buf, size_t index) {

    _validate_index(buf, index);
    return *MAKE_RCAST(buf, uint16_t, index);
}

uint32_t read_byte_buffer_uint32(byte_buffer_t* buf, size_t index) {

    _validate_index(buf, index);
    return *MAKE_RCAST(buf, uint32_t, index);
}

uint64_t read_byte_buffer_uint64(byte_buffer_t* buf, size_t index) {

    _validate_index(buf, index);
    return *MAKE_RCAST(buf, uint64_t, index);
}

const char* read_byte_buffer_str(byte_buffer_t* buf, size_t index) {

    _validate_index(buf, index);
    return MAKE_RCAST(buf, const char, index);
}

uint8_t iterate_byte_buffer_uint8(byte_buffer_t* buf, size_t* mark) {

    uint8_t val = read_byte_buffer_uint8(buf, *mark);
    *mark += sizeof(uint8_t);
    return val;
}

uint16_t iterate_byte_buffer_uint16(byte_buffer_t* buf, size_t* mark) {

    uint16_t val = read_byte_buffer_uint16(buf, *mark);
    *mark += sizeof(uint16_t);
    return val;
}

int32_t iterate_byte_buffer_uint32(byte_buffer_t* buf, size_t* mark) {

    uint32_t val = read_byte_buffer_uint32(buf, *mark);
    *mark += sizeof(uint32_t);
    return val;
}

uint64_t iterate_byte_buffer_uint64(byte_buffer_t* buf, size_t* mark) {

    uint64_t val = read_byte_buffer_uint64(buf, *mark);
    *mark += sizeof(uint64_t);
    return val;
}

byte_buffer_t* load_byte_buffer(FILE* fp) {

    byte_buffer_t* buf = create_byte_buffer();

    size_t rval = fread(&buf->cap, sizeof(uint8_t), sizeof(size_t), fp);
    if(rval != sizeof(size_t))
        error("cannot read buffer_section 1: %s", strerror(errno));

    rval = fread(&buf->len, sizeof(uint8_t), sizeof(size_t), fp);
    if(rval != sizeof(size_t))
        error("cannot read buffer_section 2: %s", strerror(errno));

    buf->buffer = _REALLOC_ARRAY(buf->buffer, uint8_t, buf->cap);

    rval = fread(buf->buffer, sizeof(uint8_t), buf->len, fp);
    if(rval != buf->len)
        error("cannot read buffer_section 3: %s", strerror(errno));

    return buf;
}

void save_byte_buffer(byte_buffer_t* buf, FILE* fp) {

    size_t rval = fwrite(&buf->cap, sizeof(uint8_t), sizeof(size_t), fp);
    if(rval != sizeof(size_t))
        error("cannot write buffer_section 1: %s", strerror(errno));

    rval = fwrite(&buf->len, sizeof(uint8_t), sizeof(size_t), fp);
    if(rval != sizeof(size_t))
        error("cannot write buffer_section 2: %s", strerror(errno));

    rval = fwrite(buf->buffer, sizeof(uint8_t), buf->len, fp);
    if(rval != buf->len)
        error("cannot write buffer_section 3: %s", strerror(errno));
}

