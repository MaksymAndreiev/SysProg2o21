#define _POSIX_C_SOURCE 3
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        perror("argc != 3");
        exit(EXIT_FAILURE);
    }

    size_t cmdlen = strlen("'' '' ");
    cmdlen += strlen(argv[1]);
    cmdlen += strlen(argv[2]);
    char *command = malloc(cmdlen);

    snprintf(command, cmdlen, "'%s' '%s'", argv[1], argv[2]);

    FILE *p;
    if (!(p = popen(command, "r"))) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    size_t zeros_count = 0;

    int c;
    while ((c = fgetc(p)) != EOF) {
        if ('0' == (char)c)
            ++zeros_count;
    }

    pclose(p);
    printf("%zu\n", zeros_count);
}
