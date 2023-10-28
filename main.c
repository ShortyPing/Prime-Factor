#include <stdio.h>
#include <stdlib.h>

char is_prime(int n) {
    char is_prime = 1;
    for(int i = 2; i < n; i++) {
        if(n % i == 0)
            is_prime = 0;
    }

    return is_prime;
}


int main(int argc, char ** argv) {

    int* prime_factors = calloc(100, sizeof (int));

    int number = atoi(argv[1]);
    int idx = 0;

    while (number != 0) {
        for(int i = number; i != 1; i--) {
            if(number % i == 0) {
                if(is_prime(i)) {
                    printf("%d\n", i);
                    prime_factors[idx++] = i;
                    number /= i;
                }

            }
        }
    }

    int ptr = 0;
    while (prime_factors[ptr++] != 0) {
        printf("%d", prime_factors[ptr-1]);
    }

    free(prime_factors);




    return 0;
}

