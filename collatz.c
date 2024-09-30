#include <stdio.h>

#include "cache.h"

// LRU collatz provider
unsigned long long collatz_lru_provider(unsigned long long number) {
    unsigned steps = 0;
    unsigned long long original_num = number;

    inc_access_count();
    if (lru_cache_contains(number)) {
        return cache_value(number);
    }

    while (number != 1) {
        if ((number % 2) == 0) {
            number /= 2;
        } else {
            number = (number * 3) + 1;
        }

        steps++;
    }

    inc_access_count();
    cache_insert(original_num, steps);

    return steps;
}

// FIFO collatz provider
unsigned long long collatz_fifo_provider(unsigned long long number) {
    unsigned steps = 0;
    unsigned long long original_num = number;

    inc_access_count();
    if (fifo_cache_contains(number)) {
        return cache_value(number);
    }

    while (number != 1) {
        if ((number % 2) == 0) {
            number /= 2;
        } else {
            number = (number * 3) + 1;
        }

        steps++;
    }

    inc_access_count();
    cache_insert(original_num, steps);

    return steps;
}

// LRU Wrapper function for collatz function
unsigned long long lru_collatz(unsigned long long number) {
    unsigned long long num_steps = 0;

    return num_steps = collatz_lru_provider(number);
}

// FIFO Wrapper function for collatz function
unsigned long long fifo_collatz(unsigned long long number) {
    unsigned long long num_steps = 0;

    return num_steps = collatz_fifo_provider(number);
}

// Original Collatz
unsigned long long collatz(unsigned long long number) {
    unsigned steps = 0;
    unsigned long long temp = number;

    while (number != 1) {
        if ((number % 2) == 0) {
            number /= 2;
        } else {
            number = (number * 3) + 1;
        }

        steps++;
    }

    return steps;
}
