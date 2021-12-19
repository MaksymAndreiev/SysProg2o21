#include <stdio.h>
#include <netdb.h>



int main(int argc, char *argv[]) {

    struct hostent *he = gethostbyname(argv[1]);
    char **ptr = he->h_addr_list;
    while (*ptr) {
        char *res = *ptr;
        printf("%d.%d.%d.%d\n", *res, *(res + 1), *(res + 2), *(res + 3));
        **ptr++;
    }
    return 0;
}