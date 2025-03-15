#include <math.h>
#include <stdio.h>
#include <string.h>

#include "money_to_words.h"

typedef char* (*char_ptr_func_ptr)(int param);
char_ptr_func_ptr dollarsToString_provider;

// Caching:
#define MAX_MEMOIZED 100
#define ARRAY_SIZE (MAX_MEMOIZED + 1)
#define NO_VALUE_YET NULL
char_ptr_func_ptr _original_provider;
char* _memoization_data[ARRAY_SIZE];

char* cache_func(int value) {
    //printf(__FILE__ ":%2d   cache_func(%d) called\n", __LINE__, value);
    printf("CACHE FUNCTION CALLED!\n");

    if (value > MAX_MEMOIZED)
        return (*_original_provider)(value);
    
    if (_memoization_data[value] == NO_VALUE_YET)
        _memoization_data[value] = (*_original_provider)(value);

    return _memoization_data[value];
}

char_ptr_func_ptr init_cache(char_ptr_func_ptr real_provider) {
    for (int ix = 0; ix < ARRAY_SIZE; ix++ )
        _memoization_data[ix] = NO_VALUE_YET;

    _original_provider = real_provider;
    return cache_func;
}


int main() {

    //int value = 1001001135;
    //printf("%s\n", intToString(1001001135));
    printf("%s\n", intToString(20));

    dollarsToString_provider = init_cache(intToString);

    printf("%s\n", (*dollarsToString_provider)(1));
    printf("%s\n", (*dollarsToString_provider)(1));
    printf("%s\n", (*dollarsToString_provider)(1));
    printf("%s\n", (*dollarsToString_provider)(1));
    //printf("%s\n", (*dollarsToString_provider)(2));
    return 0;
}
