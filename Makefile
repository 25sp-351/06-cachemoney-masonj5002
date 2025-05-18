all: cache_money random_replacement.so

CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -ldl -lm

cache_money: cache_money.o money_to_words.o cache.o
	$(CC) $(CFLAGS) cache_money.o money_to_words.o cache.o -o cache_money $(LDFLAGS)

cache_money.o: cache_money.c money_to_words.h cache.h
	$(CC) $(CFLAGS) -c cache_money.c

money_to_words.o: money_to_words.c money_to_words.h
	$(CC) $(CFLAGS) -c money_to_words.c

cache.o: cache.c cache.h
	$(CC) $(CFLAGS) -c cache.c

random_replacement.so: random_replacement.c cache.h
	$(CC) $(CFLAGS) -shared -o random_replacement.so random_replacement.c

clean:
	rm -f *.o *.so cache_money
