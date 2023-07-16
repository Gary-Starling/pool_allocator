CC=g++
CFLAGS=-c -Wall -Werror

all: test

test: main.o pool.o
	$(CC) main.o pool.o -lgtest -lgtest_main -o test

main.o: main.c
	$(CC) $(CFLAGS) main.c

pool.o: ../pool.c
	$(CC) $(CFLAGS) ../pool.c

clean:
	rm -rf *.o test a.out