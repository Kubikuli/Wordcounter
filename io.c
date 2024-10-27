// io.c
// IJC-DU2, příklad 2), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0

#include <ctype.h>
#include <stdbool.h>
#include "io.h"

// Reads one word from file "f", separated by "isspace" chars and save it to s
// Returns it's length
int read_word(char *s, int max, FILE *f) {
    int length = 0;
    int c = fgetc(f);
    static bool printed_error = false;

    // Ignores all the white chars before the word
    while (isspace(c) && (c != EOF)) {
        c = fgetc(f);
    }

    // Reads the word until reaching EOF, "isspace" char or maximum length
    while (!isspace(c) && (c != EOF)) {
        if (length < max-1) {
            s[length] = c;
            length++;
            c = fgetc(f);
        }

        // If the word was longer than max, ignores the rest of the word
        else {
            while (!(isspace(c)) && (c != EOF)) {
                c = fgetc(f);
            }
            // and prints out error if it haven't already
            if (!printed_error) {
                fprintf(stderr, "Word too long\n");
                printed_error = true;
            }
        }
    }

    // If it read only EOF
    if (length == 0) {
        return EOF;
    }

    // If it read something, adds \0 separator and returns length
    s[length] = '\0';
    length++;
    return length;
}
