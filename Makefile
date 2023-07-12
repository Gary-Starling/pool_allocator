CC=gcc
CFLAGS=-c -Wall -Werror

all: pool_alloc

pool_alloc: main.o pool.o
	$(CC) main.o pool.o -o pool_alloc

main.o: main.c
	$(CC) $(CFLAGS) main.c

pool.o: pool.c
	$(CC) $(CFLAGS) pool.c

clean:
	rm -rf *.o pool_alloc