#include <stdio.h>
#include <malloc.h>
#include <time.h>

int main() {
    clock_t start, end;
    long double time;
    start = clock();
    for (int x = 0; x <= 64; ++x) {
        (int *) malloc(2 ^ x);
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of malloc() of 2 ^ x (in milliseconds): %Lf\n", time);
    start = clock();
    for (int x = 0; x <= 64; ++x) {
        (int *) malloc(2 ^ (x + 1));
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of malloc() of 2 ^ (x + 1) (in milliseconds): %Lf\n", time);
    start = clock();
    for (int x = 0; x <= 64; ++x) {
        (int *) calloc(2 ^ x, sizeof(int));
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of calloc() of 2 ^ x (in milliseconds): %Lf\n", time);
    start = clock();
    for (int x = 0; x <= 64; ++x) {
        (int *) calloc(2 ^ (x + 1), sizeof(int));
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of calloc() of 2 ^ (x + 1) (in milliseconds): %Lf\n", time);
    start = clock();
    for (int x = 0; x <= 64; ++x) {
        (int *) alloca(sizeof(int) * (2 ^ x));
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of alloca() of 2 ^ x (in milliseconds): %Lf\n", time);
    start = clock();
    for (int x = 0; x <= 64; ++x) {
        (int *) alloca(sizeof(int) * (2 ^ (x + 1)));
    }
    end = clock();
    time = ((long double)(end - start))/ (CLOCKS_PER_SEC / 1000);
    printf("Time of alloca() of 2 ^ (x + 1) (in milliseconds): %Lf\n", time);
    return 0;
}
