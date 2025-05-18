# Cache Money Tests

Caching Running the caching program runs the tests

## Test List
```
printf("%s\n\n", (*dollarsToString_provider)(0));
printf("%s\n\n", (*dollarsToString_provider)(22));
printf("%s\n\n", (*dollarsToString_provider)(1500));
printf("%s\n\n", (*dollarsToString_provider)(99999));
printf("%s\n\n", (*dollarsToString_provider)(1024));
printf("%s\n\n", (*dollarsToString_provider)(22)); // Value cached
printf("%s\n\n", (*dollarsToString_provider)(0)); // Value cached
printf("%s\n\n", (*dollarsToString_provider)(188289));
printf("%s\n\n", (*dollarsToString_provider)(1024)); // Value cached
printf("%s\n\n", (*dollarsToString_provider)(1024)); // Value cached
printf("%s\n\n", (*dollarsToString_provider)(1025)); // Value cached
printf("%s\n\n", (*dollarsToString_provider)(1026)); // Cache is full and entry is evicted
```