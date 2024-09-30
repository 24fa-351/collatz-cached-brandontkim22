#include <stdbool.h>

#ifndef CACHE_H
#define CACHE_H

void cache_init(unsigned long long cache_size);

int cmp_last_used(const void* val1, const void* val2);

bool lru_cache_contains(unsigned long long number);

bool fifo_cache_contains(unsigned long long number);

unsigned long long cache_value(unsigned long long number);

void cache_insert(unsigned long long number, unsigned steps);

void inc_access_count(void);

double cache_hit(void);

void free_cache(void);

#endif