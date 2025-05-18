POLICIES = random_replacement least_recently_used least_frequently_used
POLICY_LIBS = $(addsuffix .so, $(POLICIES))
EXECUTABLES = cache_money_rr cache_money_lru cache_money_lfu

CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -ldl -lm

all: $(EXECUTABLES) $(POLICY_LIBS)

%.so: %.c cache.h
	$(CC) $(CFLAGS) -shared -o $@ $<

money_to_words.o: money_to_words.c money_to_words.h
	$(CC) $(CFLAGS) -c money_to_words.c

cache.o: cache.c cache.h
	$(CC) $(CFLAGS) -c cache.c

cache_money.o: cache_money.c money_to_words.h cache.h
	$(CC) $(CFLAGS) -c cache_money.c

cache_money_rr: cache_money.o money_to_words.o cache.o
	$(CC) $(CFLAGS) cache_money.o money_to_words.o cache.o -o cache_money_rr $(LDFLAGS)

cache_money_lru: cache_money.o money_to_words.o cache.o
	$(CC) $(CFLAGS) cache_money.o money_to_words.o cache.o -o cache_money_lru $(LDFLAGS)

cache_money_lfu: cache_money.o money_to_words.o cache.o
	$(CC) $(CFLAGS) cache_money.o money_to_words.o cache.o -o cache_money_lfu $(LDFLAGS)

clean:
	rm -f *.o *.so $(EXECUTABLES)
