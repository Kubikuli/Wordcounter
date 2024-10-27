// wordcount.c
// IJC-DU2, příklad 2), 24.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0
/* 
    Hash table size (N) explanation:
    Hash table should have more buckets than expected number of different keys, and ideally should be a prime number,
    according to some sources it should be about 1.3x maximum number of keys that will actually be in the table
    source: https://cseweb.ucsd.edu/~kube/cls/100/Lectures/lec16/lec16-8.html
    according to: https://writing.stackexchange.com/questions/6988/how-many-different-words-are-in-the-average-novel
    average book has about 5k-10k unique words, so taking the upper border x1.3 and the closest higher prime number is 13001
    /
    comments in this file explain only briefly what the program does
    for better explanation of each function check other files
*/

#include <stdio.h>
#include <string.h>

#include "htab.h"
#include "io.h"

#define MAX_WORD_LENGTH 255     // limit for word length
#define N 13001                // size of the hash table

// Prints key and value of hash table pair
void print_items (htab_pair_t *pair) {
    fprintf(stdin, "%s\t%d\n", pair->key, pair->value);
    return;
}

int main() {
    // Creates hash table
    htab_t *hashtab = htab_init(N);
    if (hashtab == NULL) {
        fprintf(stderr, "htab_init: memory allocation failed\n");
        return 1;
    }

    char buffer[MAX_WORD_LENGTH];
    htab_pair_t *pair_ptr;
    // variable for printing error (but only once) when finding word longer than MAX_WORD_LENGHT

    // Reads all the words from file and saves them into hash table
    while (read_word(buffer, MAX_WORD_LENGTH, stdin) != EOF) {
        // Tries to find each word first
        pair_ptr = htab_find(hashtab, buffer);

        // If it's not yet there, adds it to hash table and increments counter
        if (pair_ptr == NULL) {
            pair_ptr = htab_lookup_add(hashtab, buffer);
            if (pair_ptr == NULL) {
                fprintf(stderr, "htab_lookupAdd: Failed to allocate memory\n");
                htab_free(hashtab);
                return 1;
            }
        }
        pair_ptr->value++;
    }

    // Prints out results
    htab_for_each(hashtab, print_items);

    // if defined, prints statistic of linked lists lengths
    #ifdef STATISTICS
        htab_statistics(hashtab);
    #endif

    // Deletes hash table with all its parts
    htab_free(hashtab);

    return 0;
}
