#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"
#include "collatz.h"


int main(int argc, char* argv[]) {
    unsigned long long number_of_tests = 0;
    unsigned long long min = 0;
    unsigned long long max = 0;
    unsigned long long cache_size = 0;
    double cache_hit_count = 0;
    char cache_policy[5];

    sscanf(argv[1], "%llu", &number_of_tests);
    sscanf(argv[2], "%llu", &min);
    sscanf(argv[3], "%llu", &max);
    sscanf(argv[4], "%s", cache_policy);
    sscanf(argv[5], "%llu", &cache_size);

    cache_init(cache_size);

    FILE *fptr = fopen("collatz.csv", "w+");
    
    while (number_of_tests != 0) {
        unsigned long long steps = 0;
        unsigned long long rnd_num = rand() % (max - min + 1) + min;

        if (strcmp(cache_policy, "LRU") == 0) {
            steps = lru_collatz(rnd_num);
        } else if (strcmp(cache_policy, "FIFO") == 0) {
            steps = fifo_collatz(rnd_num);
        } else if (strcmp(cache_policy, "none") == 0) {
            steps = collatz(rnd_num);
        } else {
            printf("Invalid cache policy!\n");
            break;
        }

        fprintf(fptr, "%llu, %llu\n", rnd_num, steps);

        number_of_tests -= 1;
    }

    if (strcmp(cache_policy, "none") != 0) {
        cache_hit_count = cache_hit();
        printf("Cache hit percentage: %f\n", cache_hit_count);
    }

    fclose(fptr);
    free_cache();
 
    return 0;
}