// htab_bucket_count.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include "htab.h"
#include "htab_content.h"

// Returns size of hash table (number of linked lists)
size_t htab_bucket_count(const htab_t * t) {
    return t->arr_size;
}
