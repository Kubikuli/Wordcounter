// io.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include <stdlib.h>
#include "htab.h"
#include "htab_content.h"

// Destroys all the items, hash table becomes empty
void htab_clear(htab_t *t) {
    htab_item_t *prev_item = NULL;
    htab_item_t *item;
    
    // Goes through the whole hash table
    for (size_t i = 0, size = t->arr_size; i < size; i++) {
        item = t->htab_bucket_ptrs[i];
        // If there's a linked list on the index "i"
        while (item != NULL) {
            // If it's the last item in linked list, we can destroy it
            if (item->next == NULL) {
                free(item->pair.key);
                free(item);
                // If it wasn't the only item in linked list
                if (prev_item != NULL) {
                    prev_item->next = NULL;
                    prev_item = NULL;           // reset
                }
                
                // If it was the first item of linked list
                else {
                    t->htab_bucket_ptrs[i] = NULL;
                }
                item = t->htab_bucket_ptrs[i];
            }

            // If it't pointing to next item, we have to move to next
            else {
                prev_item = item;
                item = item->next;
            }
        }
    }
    t->size = 0;
}
