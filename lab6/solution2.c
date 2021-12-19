#include <stdio.h>
#include <string.h>

int main() {
    int i;
    int counter = 0;
    for (i = 2; i < 100000; i++) {
        char filename[256];
        char process[256];
        sprintf(filename, "/proc/%d/comm", i);
        FILE *fd = fopen(filename, "r");
        if (fd != NULL) {
            fscanf(fd, "%s", process);
            if (!strcmp(process, "genenv"))
                counter++;
        }
    }
    printf("%d\n", counter);
    return 0;
}