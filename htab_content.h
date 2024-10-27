// htab_content.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#ifndef _HTAB_CONTENT
#define _HTAB_CONTENT

#include "htab.h"

typedef struct htab_item {
    htab_pair_t pair;
    struct htab_item *next;
} htab_item_t;

struct htab {
    size_t size;
    size_t arr_size;
    htab_item_t *htab_bucket_ptrs[];
};

#endif      // _HTAB_CONTENT
