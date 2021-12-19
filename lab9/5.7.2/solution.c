#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    int s = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in local;

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(atoi(argv[1]));
    local.sin_family = AF_INET;


    bind(s, (struct sockaddr *) &local, sizeof(local));

    char buf[BUFSIZ * 5];

    while (1) {
        memset(buf, 0, BUFSIZ * 5);
        read(s, buf, BUFSIZ * 5);

        if (strcmp(buf, "OFF\n") == 0) {
            break;
        } else {
            printf("%s\n", buf);
        }
    }
    return 0;
}