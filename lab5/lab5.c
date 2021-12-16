#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <math.h>

int main() {
    clock_t start, end;
    long double time;
    start = clock();
    int x;
    for (x = 0; x <= 64; ++x) {
        (int *) malloc(pow(2, x));
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of malloc() of 2 ^ x (in milliseconds): %Lf, x up to %d\n", time, x-1);
    printf("x: %d", x);
    start = clock();
    for (x = 0; x <= 64; ++x) {
        (int *) malloc(pow(2, (x + 1)));
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of malloc() of 2 ^ (x + 1) (in milliseconds): %Lf, x up to %d\n", time, x-1);
    start = clock();
    for (x = 0; x <= 64; ++x) {
        (int *) calloc(pow(2, x), sizeof(int));
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of calloc() of 2 ^ x (in milliseconds): %Lf, x up to %d\n", time, x-1);
    start = clock();
    for (x = 0; x <= 64; ++x) {
        (int *) calloc(pow(2, (x + 1)), sizeof(int));
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of calloc() of 2 ^ (x + 1) (in milliseconds): %Lf, x up to %d\n", time, x-1);
    start = clock();
    for (x = 0; x <= 64; ++x) {
        (int *) alloca(sizeof(int) * (pow(2, x)));
        if (x%2== 0){
            printf("x: %d\t", x);
        } else {
            printf("x: %d\n", x);
        }
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of alloca() of 2 ^ x (in milliseconds): %Lf\n", time);
    start = clock();
    for (x = 0; x <= 64; ++x) {
        (int *) alloca(sizeof(int) * (pow(2, (x + 1))));
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of alloca() of 2 ^ (x + 1) (in milliseconds): %Lf, x up to %d\n", time, x-1);
    return 0;
}
