// htab_hash_function.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include <stdint.h>
#include "htab.h"

// hash function, sdbm variant from: http://www.cse.yorku.ca/~oz/hash.html
// Returns hash value for given string
size_t htab_hash_function(const char *str) {
    uint32_t h = 0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p=(const unsigned char*)str; *p!='\0'; p++) {
        h = 65599*h + *p;
    }
    return h;
}
