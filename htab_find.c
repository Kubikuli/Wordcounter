// htab_find.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include <stdio.h>
#include "htab.h"
#include "htab_content.h"

// Searches hash table for "key"
// If found, returns pointer to it, if not returns NULL 
htab_pair_t *htab_find(const htab_t * t, htab_key_t key) {
    size_t index = htab_hash_function(key) % t->arr_size;
    htab_item_t *item = t->htab_bucket_ptrs[index];
    size_t key_len = strlen(key);

    // Goes through all the items in linked list
    while (item != NULL) {
        if (!strcmp(item->pair.key, key) && key_len == strlen(item->pair.key)) {
            return &item->pair;
        }
        item = item->next;
    }

    return NULL;
}
