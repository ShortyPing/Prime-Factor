#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

long * prime_factors;

long idx = 0;
long number;

pthread_mutex_t idx_mutex = PTHREAD_MUTEX_INITIALIZER;

char is_prime(long n) {
    char is_prime = 1;
    for(long i = 2; i <= sqrt(n); i++) {
        if(n % i == 0)
            is_prime = 0;
    }

    return is_prime;
}

void add_prime_factor(long pf) {
    pthread_mutex_lock(&idx_mutex);
    prime_factors[idx++] = pf;
    number /= pf;

    pthread_mutex_unlock(&idx_mutex);
}


void* execute(void* fourth) {
    long part = (long) round((double) number / 8);
    int fourthInt = *((int *) fourth);

    while (number != 1) {

        for(long i = part * fourthInt; i >= part * (fourthInt - 1); i--) {
            if(i == 1)
                continue;
            if(number % i == 0) {
                if(is_prime(i)) {
                    add_prime_factor(i);
                }
            }
        }
    }

    return 0;
}

void single() {
    while (number != 1) {

        for(long i = number; i != 0; i--) {
            if(i == 1)
                continue;
            if(number % i == 0) {
                if(is_prime(i)) {
                    add_prime_factor(i);
                }
            }
        }
    }
}

int* create_heap_int(int i) {
    int* ptr = malloc(4);
    *ptr = i;
    return ptr;
}

int main(int argc, char ** argv) {

    prime_factors = calloc(100, sizeof (long));


    number = atol(argv[1]);

    pthread_t t1, t2, t3, t4, t5, t6, t7, t8;

    pthread_create(&t1, NULL, execute, create_heap_int(1));
    pthread_create(&t2, NULL, execute, create_heap_int(2));
    pthread_create(&t3, NULL, execute, create_heap_int(3));
    pthread_create(&t4, NULL, execute, create_heap_int(4));
    pthread_create(&t5, NULL, execute, create_heap_int(5));
    pthread_create(&t6, NULL, execute, create_heap_int(6));
    pthread_create(&t7, NULL, execute, create_heap_int(7));
    pthread_create(&t8, NULL, execute, create_heap_int(8));


    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    pthread_join(t5, NULL);
    pthread_join(t6, NULL);
    pthread_join(t7, NULL);
    pthread_join(t8, NULL);

    for(long i = 0; i < idx; i++) {
        printf("%ld ", prime_factors[i]);
    }
    printf("\n");

    free(prime_factors);




    return 0;
}

