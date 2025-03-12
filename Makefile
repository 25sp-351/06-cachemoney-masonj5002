all: memoization

CC = gcc
CFLAGS = -Wall

memoization: memoization.o
	gcc $(CFLAGS) memoization.o -o memoization -lm

memoization.o: memoization.c
	gcc $(CFLAGS) -c memoization.c

clean:
	rm -f *.o memoization