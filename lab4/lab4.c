#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main() {
    time_t rawtime;
    struct tm *current_time;
    time_t seconds1;
    struct timeval seconds2;
    struct timespec seconds3;
    clock_t start, stop;

    time(&rawtime);
    current_time = localtime(&rawtime);
    printf("Current local time and date: %s", asctime(current_time));

    printf("------------------------ time() ------------------------\n");
    start = clock();
    seconds1 = time(&seconds1);
    stop = clock();
    printf("Absolute time (seconds since January 1, 1970): %ld\n", seconds1);
    printf("time() required: %ld ms\n", stop - start);

    printf("------------------------ gettimeofday() ------------------------\n");
    start = clock();
    gettimeofday(&seconds2, NULL);
    stop = clock();
    printf("Absolute time (seconds since January 1, 1970): %ld\n", seconds2.tv_sec);
    printf("gettimeofday() required: %ld ms\n", stop - start);

    printf("------------------------ clock_gettime() ------------------------\n");
    start = clock();
    clock_gettime(CLOCK_REALTIME, &seconds3);
    stop = clock();
    printf("Absolute time (seconds since January 1, 1970): %ld\n", seconds3.tv_sec);
    printf("clock_gettime() required: %ld ms\n", stop - start);
    return 0;
}
