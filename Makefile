# Makefile
# IJC-DU2, 24.4.2024
# Author: Jakub Lůčný, VUT FIT

# To run the wordcount-dynamic ---- export LD_LIBRARY_PATH="." && ./wordcount-dynamic <"input_file"
# 							   ---- or use "make run_dynamic" that runs the program with file named "input"

CC = gcc
CFLAGS = -O2 -g -std=c11 -pedantic -Wall -Wextra

LD_LIBRARY_PATH="."

OBJECTS = htab_hash_function.o htab_init.o htab_size.o htab_bucket_count.o htab_find.o htab_lookup_add.o htab_erase.o htab_for_each.o htab_clear.o htab_free.o htab_statistics.o
DOBJECTS = d_htab_hash_function.o d_htab_init.o d_htab_size.o d_htab_bucket_count.o d_htab_find.o d_htab_lookup_add.o d_htab_erase.o d_htab_for_each.o d_htab_clear.o d_htab_free.o d_htab_statistics.o

all: tail wordcount wordcount-dynamic libhtab.a libhtab.so

run_dynamic: wordcount-dynamic
	export LD_LIBRARY_PATH="." && ./wordcount-dynamic <input

tail: tail.c
	$(CC) $(CFLAGS) tail.c -o tail

# Static library
libhtab.a: $(OBJECTS)
	ar rcs libhtab.a $(OBJECTS)

# Dynamic library
libhtab.so: $(DOBJECTS)
	$(CC) -shared -fPIC -o libhtab.so $(DOBJECTS)

# exe files
wordcount: wordcount.o io.o libhtab.a
	$(CC) -static wordcount.o io.o -o wordcount -L. -lhtab

wordcount-dynamic: wordcount.o io.o libhtab.so
	$(CC) wordcount.o io.o -o wordcount-dynamic -L. -lhtab


# Object files for static library
htab_hash_function.o: htab.h
	$(CC) $(CFLAGS) -c htab_hash_function.c -o htab_hash_function.o

htab_init.o: htab_init.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c htab_init.c -o htab_init.o

htab_size.o: htab_size.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c htab_size.c -o htab_size.o

htab_bucket_count.o: htab_bucket_count.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c htab_bucket_count.c -o htab_bucket_count.o

htab_find.o: htab_find.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c htab_find.c -o htab_find.o

htab_lookup_add.o: htab_lookup_add.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c htab_lookup_add.c -o htab_lookup_add.o

htab_erase.o: htab_erase.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c htab_erase.c -o htab_erase.o

htab_for_each.o: htab_for_each.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c htab_for_each.c -o htab_for_each.o

htab_clear.o: htab_clear.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c htab_clear.c -o htab_clear.o

htab_free.o: htab_free.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c htab_free.c -o htab_free.o

htab_statistics.o: htab_statistics.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c htab_statistics.c -o htab_statistics.o

# Object files for dynamic library 
d_htab_hash_function.o: htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_hash_function.c -o d_htab_hash_function.o

d_htab_init.o: htab_init.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_init.c -o d_htab_init.o

d_htab_size.o: htab_size.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_size.c -o d_htab_size.o

d_htab_bucket_count.o: htab_bucket_count.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_bucket_count.c -o d_htab_bucket_count.o

d_htab_find.o: htab_find.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_find.c -o d_htab_find.o

d_htab_lookup_add.o: htab_lookup_add.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_lookup_add.c -o d_htab_lookup_add.o

d_htab_erase.o: htab_erase.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_erase.c -o d_htab_erase.o

d_htab_for_each.o: htab_for_each.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_for_each.c -o d_htab_for_each.o

d_htab_clear.o: htab_clear.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_clear.c -o d_htab_clear.o

d_htab_free.o: htab_free.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_free.c -o d_htab_free.o

d_htab_statistics.o: htab_statistics.c htab_content.h htab.h
	$(CC) $(CFLAGS) -c -fPIC htab_statistics.c -o d_htab_statistics.o

# Other object files
io.o: io.c io.h
	$(CC) $(CFLAGS) -c io.c -o io.o

wordcount.o: wordcount.c io.h htab.h
	$(CC) $(CFLAGS) -c wordcount.c -o wordcount.o

# Equivalent C++ file
wordcount-: wordcount-.cc
	g++ wordcount-.cc -o wordcount-


clean:
	rm *.o libhtab.so libhtab.a tail wordcount wordcount-dynamic wordcount-
