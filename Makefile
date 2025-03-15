all: cache_money

CC = gcc
CFLAGS = -Wall

cache_money: cache_money.o money_to_words.o
	$(CC) $(CFLAGS) cache_money.o money_to_words.o -o cache_money -lm

cache_money.o: cache_money.c money_to_words.h
	$(CC) $(CFLAGS) -c cache_money.c

money_to_words.o: money_to_words.c money_to_words.h
	$(CC) $(CFLAGS) -c money_to_words.c

clean:
	rm -f *.o cache_money