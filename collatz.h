
#ifndef COLLATZ_H
#define COLLATZ_H

unsigned long long collatz_lru_provider(unsigned long long number);

unsigned long long collatz_fifo_provider(unsigned long long number);

unsigned long long lru_collatz(unsigned long long number);

unsigned long long fifo_collatz(unsigned long long number);

unsigned long long collatz(unsigned long long number);


#endif