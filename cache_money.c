#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "cache.h"
#include "money_to_words.h"

typedef char* (*char_ptr_func_ptr)(int param);
char_ptr_func_ptr dollarsToString_provider;
ProviderFunction cached_provider = NULL;

char* intToString_adapter(int value);
char* cached_wrapper(int value);

int main(int argc, char** argv) {
    const char* libname = NULL;
    if (strstr(argv[0], "rr")) {
        libname = "./random_replacement.so";
    } else if (strstr(argv[0], "lru")) {
        libname = "./least_recently_used.so";
    } else if (strstr(argv[0], "lfu")) {
        libname = "./least_frequently_used.so";
    } else {
        fprintf(stderr,
                "Unknown caching policy. Use cache_money_rr, cache_money_lru, "
                "or cache_money_lfu.\n");
        return 1;
    }

    // Load the selected cache module
    Cache* cache_hooks = load_cache_module(libname);
    if (!cache_hooks) {
        fprintf(stderr, "Failed to load cache policy: %s\n", libname);
        return 1;
    }

    cached_provider = cache_hooks->set_provider_func(intToString_adapter);
    dollarsToString_provider = cached_wrapper;

    printf("%s\n\n", (*dollarsToString_provider)(0));
    printf("%s\n\n", (*dollarsToString_provider)(22));
    printf("%s\n\n", (*dollarsToString_provider)(1500));
    printf("%s\n\n", (*dollarsToString_provider)(99999));
    printf("%s\n\n", (*dollarsToString_provider)(1024));
    printf("%s\n\n", (*dollarsToString_provider)(22));
    printf("%s\n\n", (*dollarsToString_provider)(0));
    printf("%s\n\n", (*dollarsToString_provider)(188289));
    printf("%s\n\n", (*dollarsToString_provider)(1024));
    printf("%s\n\n", (*dollarsToString_provider)(1024));
    printf("%s\n\n", (*dollarsToString_provider)(1025));
    printf("%s\n\n", (*dollarsToString_provider)(1026));

    print_cache_stats(STDOUT_FILENO, cache_hooks->get_statistics());

    cache_hooks->cache_cleanup();
    free(cache_hooks);

    return 0;
}

char* intToString_adapter(int value) {
    printf("ADAPTER CALLED for %d\n", value);
    return intToString(value);
}

char* cached_wrapper(int value) {
    return (*cached_provider)(value);
}
