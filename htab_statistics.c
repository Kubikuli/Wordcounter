// htab_statistics.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include <stdio.h>
#include <limits.h>
#include "htab.h"
#include "htab_content.h"

// Prints out minimal, maximal and average length of linked list 
void htab_statistics(const htab_t *t) {
    size_t min = ULONG_MAX;
    size_t max = 0;
    size_t size = 0;
    int bucket = 0;
    double average;
    htab_item_t *item;

    // Goes through every linked list in hash table
    for (size_t i = 0, arr_size = t->arr_size; i < arr_size; i++) {
        size = 0;
        item = t->htab_bucket_ptrs[i];

        // for 0 items in linked list
        if (item == NULL) {
            if (size < min) {
                min = size;
            }
            continue;
        }

        size++;
        bucket++;

        // if there is at least one item in linked list, counts how many items there are
        while (item->next != NULL) {
            item = item->next;
            size++;
        }

        if (size > max) {
            max = size;
        }

        if (size < min) {
            min = size;
        }
    }

    average = t->size / (double)bucket;

    fprintf(stderr, "Min: %lu\tMax: %lu\tAverage: %f\n", min, max, average);
}
