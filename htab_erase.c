// htab_erase.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include <stdlib.h>
#include <stdio.h>
#include "htab.h"
#include "htab_content.h"

// Tries to erase item of hash table with given "key"
// Returns true on success, false if failed
bool htab_erase(htab_t * t, htab_key_t key) {
    htab_pair_t *pair = htab_find(t, key);
    // If not found
    if (pair == NULL) {
        fprintf(stderr, "Item not found\n");
        return false;
    }

    // Found
    size_t index = htab_hash_function(key) % t->arr_size;
    htab_item_t *item = t->htab_bucket_ptrs[index];
    htab_item_t *prev_item = NULL;

    while (item != NULL) {
        if (!strcmp(item->pair.key, key)) {
            prev_item->next = item->next;
            free(item);
            return true;
        }
        prev_item = item;
        item = item->next;
    }
    // Code should never reach this point, but just in case anything actually goes wrong
    return false;
}
