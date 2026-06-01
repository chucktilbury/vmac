#ifndef _SCAN_H_
#define _SCAN_H_

#include <stdint.h>

typedef struct _pseudo_sym_t {
    uint32_t idx;
    struct _pseudo_sym_t* left;
    struct _pseudo_sym_t* right;
} pseudo_sym_t;

void scan_code(void);
pseudo_sym_t* find_sym(uint32_t idx);

#endif /* _SCAN_H_ */
