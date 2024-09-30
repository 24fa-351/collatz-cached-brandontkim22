#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int val;
    int steps;
    int last_used;
} CacheNode;

CacheNode* cache;

unsigned long long size_of_cache = 0;
unsigned long cache_hit_count = 0;
unsigned long access_count = 0;
int current_time = 0;

// Cache initialization
void cache_init(unsigned long long cache_size) {
    size_of_cache = cache_size;
    cache = malloc(cache_size * sizeof(struct CacheNode*));

    for (int ix = 0; ix <= cache_size; ++ix) {
        cache[ix].val = -1;
        cache[ix].steps = 0;
        cache[ix].last_used = current_time;
    }
}

// Compare function used for qsort (sort by last_used [LRU])
int cmp_last_used(const void* val1, const void* val2)
{
    CacheNode* current_element = (CacheNode*)val1;
    CacheNode* next_element = (CacheNode*)val2;
    if (current_element->last_used < next_element->last_used) {
        return -1;
    }
    if (current_element->last_used > next_element->last_used) {
        return 1;
    }
    return 0;
}

// LRU Cache lookup
bool lru_cache_contains(unsigned long long number) {
    bool value_exists = false;

    for (int ix = 0; ix <= size_of_cache; ++ix) {
        if (cache[ix].val == number) {
            cache[ix].last_used = current_time++;
            value_exists = true;
            cache_hit_count++;
            break;
        }
    }

    return value_exists;
}

// FIFO Cache lookup; Does not update the last_used of found element
bool fifo_cache_contains(unsigned long long number) {
    bool value_exists = false;

    for (int ix = 0; ix <= size_of_cache; ++ix) {
        if (cache[ix].val == number) {
            value_exists = true;
            cache_hit_count++;
            break;
        }
    }

    return value_exists;
}

// Returns specified cache entry's number of steps
unsigned long long cache_value(unsigned long long number) {
    unsigned long long num_steps = 0;
    for (int ix = 0; ix <= size_of_cache; ++ix) {
        if (cache[ix].val == number) {
            num_steps = cache[ix].steps;
        }
    }

    return num_steps;
}

// Eviction/Insertion method for cache
void cache_insert(unsigned long long number, unsigned steps) {
    qsort(cache, size_of_cache, sizeof(CacheNode), cmp_last_used);
    
    cache[0].val = number;
    cache[0].steps = steps;
    cache[0].last_used = current_time++;

    // Testcase for first element in the cache
    if (cache[0].val != -1 && cache[0].last_used == 0) {
        cache[0].last_used = 1;
        current_time++;
    }

    qsort(cache, size_of_cache, sizeof(CacheNode), cmp_last_used);
}

void inc_access_count(void) {
    access_count++;
}

double cache_hit(void) {
    return (double)cache_hit_count / access_count * 100;
}

void free_cache(void) {
    free(cache);
}