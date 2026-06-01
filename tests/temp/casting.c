#include <stdio.h>
#include <stdint.h>

uint8_t cast_to_u8(void* val) {

    return (uint8_t)(*(uint8_t*)(val));
}

int main(void) {

    uint32_t val = -2;
    printf("0x%02X", cast_to_u8(&val));

    return 0;
}

