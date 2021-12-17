#include <stdio.h>
#include <time.h>

int main() {
    time_t rawtime;
    struct tm *timeinfo;
    time_t seconds;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("Current local time and date: %s", asctime(timeinfo));
    seconds = time(&seconds);
    printf("Absolute time (seconds since January 1, 1970): %ld\n", seconds);
    return 0;
}
