// htab_init.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include <stdlib.h>
#include "htab.h"
#include "htab_content.h"

// Creates hash table of size n and initializes all the initial bucket pointers to NULL
// Returns pointer to the hash table
htab_t *htab_init(const size_t n) {
    // Allocates memory for the hash table
    htab_t *t = malloc(sizeof(htab_t) + n*sizeof(htab_item_t *));
    if (t == NULL) {
        return t;
    }

    t->size = 0;
    t->arr_size = n;

    // Initializes all the pointers
    for (size_t i = 0; i < n; i++) {
        t->htab_bucket_ptrs[i] = NULL;
    }

    return t;
}
