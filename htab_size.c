// htab_size.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include "htab.h"
#include "htab_content.h"

// Returns number of elements saved in hash table
size_t htab_size(const htab_t * t) {
    return t->size;
}
