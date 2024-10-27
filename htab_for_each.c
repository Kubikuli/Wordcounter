// htab_for_each.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include "htab.h"
#include "htab_content.h"

// Goes through all the items and calls function "f" with them
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)) {
    htab_item_t *item;
    // Goes through the whole hash table
    for (size_t i = 0, size = t->arr_size; i < size; i++) {
        item = t->htab_bucket_ptrs[i];
        // If it finds an item, calls with it the given function
        while(item != NULL) {
            (*f)(&item->pair);
            item = item->next;
        }
    }
}
