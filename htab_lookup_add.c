// htab_lookup_add.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include <stdio.h>
#include <stdlib.h>
#include "htab.h"
#include "htab_content.h"

// Searches hash table for "key"
// If found returns pointer to it
// If not found, create new item in the hash table and returns it's pointer
htab_pair_t *htab_lookup_add(htab_t * t, htab_key_t key) {
    htab_pair_t *pair = htab_find(t, key);
    // If it couldn't find, creates new item
    if (pair == NULL) {
        // Finds the correct index
        size_t index = htab_hash_function(key) % t->arr_size;
        htab_item_t *item = t->htab_bucket_ptrs[index];
        
        // Allocates memory for new item
        htab_item_t *new_item = malloc(sizeof(htab_item_t));
        if (new_item == NULL) {
            fprintf(stderr, "Malloc failed\n");
            return NULL;
        }

        // Allocates memory for key of the item
        char *tmp = malloc(strlen(key) + 1);
        if (tmp == NULL) {
            fprintf(stderr, "Malloc failed\n");
            return NULL;
        }
        strcpy(tmp, key);

        // Initializes the new item
        new_item->next = NULL;
        new_item->pair.key = tmp;
        new_item->pair.value = 0;
        t->size++;

        // If there's already an item at this index, append the new item to the end of the linked list
        if (item != NULL) {
            while (item->next != NULL) {
                item = item->next;
            }
            item->next = new_item;
        }
        // Otherwise, set the new item as the first item at this index
        else {
            t->htab_bucket_ptrs[index] = new_item;
        }
        return &new_item->pair;
    }

    // if found, returns pointer to it
    return pair;
}
