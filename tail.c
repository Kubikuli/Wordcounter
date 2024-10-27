// tail.c
// IJC-DU2, příklad 1), 22.4.2024
// Author: Jakub Lůčný, VUT FIT
// Compiled with: gcc 11.4.0
/*
    Prints out last 10 lines of given file.
    If there is no file given, reads from stdin
    If there is parameter -n "number", prints out last "number" lines (ignoring sign)
    RUN OPTIONS:    ./tail
                    ./tail "file"
                    ./tail -n "nmb"
                    ./tail "file" -n "nmb"
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ROW_LENGTH 2048         // maximum line length

// Function declarations
char **cbuf_create(int n);
int cbuf_put(FILE *file, char **cbuffer, int length, int writeIndex);
int cbuf_get(char **cbuffer, int length, int readIndex, int writeIndex);
void cbuf_free(char **cbuffer, int lenght);


int main(int argc, char*argv[]) {
    // Default options
    int length = 10;
    FILE *file = stdin;

    // Command-line arguments parsing
    // Default options get overwritten if user chooses different options
    switch (argc) {
        case 1:
            break;
        case 2:
            file = fopen(argv[1], "r");
            if (file == NULL) {
                fprintf(stderr, "Error: Invalid file\n");
                return 1;
            }
            break;
        case 3:
            if (strcmp(argv[argc-2], "-n") == 0) {
                length = strtol(argv[argc-1], NULL, 10);
                
                if (length <= 0) {
                    fprintf(stderr, "Error: Negative or zero value of \"-n\" parameter\n");
                    return 1;
                }
            }
            break;
        default:
            if (strcmp(argv[2], "-n") == 0) {
                length = strtol(argv[3], NULL, 10);
                
                if (length <= 0) {
                    fprintf(stderr, "Error: Negative or zero value of \"-n\" parameter\n");
                    return 1;
                }
            }

            file = fopen(argv[1], "r");
            if (file == NULL) {
                fprintf(stderr, "Error: Invalid file\n");
                return 1;
            }
            break;
    }
    // Creates and initializes cyclic buffer
    int writeIndex = 0;
    int readIndex = 0;
    char **cbuffer = cbuf_create(length);

    bool printed_error = false;

    // Fills the cylic buffer with lines from file
    while(!cbuf_put(file, cbuffer, length, writeIndex)) {
        // If read line longer than maximum limit, prints out warning message and ignores rest of the word
        if (strlen(cbuffer[writeIndex % length]) == MAX_ROW_LENGTH-1 && cbuffer[writeIndex % length][MAX_ROW_LENGTH-1] != '\n') {
            if (!printed_error) {
                fprintf(stderr, "Warning: Line %d is longer than the maximum of %d chars\n", writeIndex, MAX_ROW_LENGTH-1);
                printed_error = true;
            }
            // cbuffer[writeIndex][MAX_ROW_LENGTH - 1] = '\n';              // If we wanted to append '\n' at the end of the "over the max" word
            // Ignoring rest of the word
            int c;
            while ((c = fgetc(file)) != '\n' && c != EOF) {}
        }
        writeIndex++;
    }

    // If we read more lines than size of buffer, we need to move the readIndex
    if (writeIndex > length) {
        readIndex = writeIndex;
    }

    // Prints out the whole buffer
    for (int i = 0; i < length; i++) {
        if (cbuf_get(cbuffer, length, readIndex, writeIndex)) {break;}
        readIndex++;
    }

    cbuf_free(cbuffer, length);
    return 0;
}

// Creates array of N pointers to strings
// Returns pointer to this array
char **cbuf_create(int n) {
    char **cbuffer = calloc(n, sizeof(char*));
    if (cbuffer == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory\n");
    }
    return cbuffer;
}

// Puts new line into the cyclic buffer
// Returns 0 on succes, 1 if something failed
int cbuf_put(FILE *file, char **cbuffer, int length, int writeIndex) {
    // If the buffer isn't full yet allocates new line
    if (writeIndex < length) {
        cbuffer[writeIndex] = malloc(MAX_ROW_LENGTH * sizeof(char));
        if (cbuffer[writeIndex] == NULL) {
            fprintf(stderr, "Error: cbuf_put -- Failed to allocate memory\n");
            return 1;
        }
    }

    // If it's full, overwrites the oldest line is cyclic buffer
    char *tmp = fgets(cbuffer[writeIndex % length], MAX_ROW_LENGTH, file);
    if (tmp == NULL) {
        if (writeIndex < length) {
            free(cbuffer[writeIndex]);
            cbuffer[writeIndex] = NULL;
        }
        return 1;
    }
    return 0;
}

// Prints line from buffer at readIndex index
// Returns 0 on succes, 1 if something failed
int cbuf_get(char **cbuffer, int length, int readIndex, int writeIndex) {
    // If tried to read from buffer with 0 lines or read after the writeIndex
    if ((writeIndex == 0 && writeIndex == readIndex) || (cbuffer[readIndex % length] == NULL)) {
        fprintf(stderr, "Warning: Tried to read from empty buffer (probably tried to print more lines than the file has)\n");
        return 1;
    }

    printf("%s", cbuffer[readIndex % length]);
    return 0;
}

// Destroys the cyclic buffer
void cbuf_free(char **cbuffer, int lenght) {
    for (int i = 0; i < lenght; i++) {
        free(cbuffer[i]);
    }

    free(cbuffer);
}
