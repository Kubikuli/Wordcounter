// htab_free.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include <stdlib.h>
#include "htab.h"
#include "htab_content.h"

// Destroys the hash table
void htab_free(htab_t * t) {
    htab_clear(t);
    free(t);
}
