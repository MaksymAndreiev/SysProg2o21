#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>


int cmpChars(const void *chr1, const void *chr2) {
    return *((char *) chr2) - *((char *) chr1);
}


int main(int argc, char *argv[]) {
    if (argc == 2) {
        int sfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sfd >= 0) {
            int reuse;
            setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

            struct sockaddr_in sockaddr;
            sockaddr.sin_family = AF_INET;
            sockaddr.sin_port = htons(atoi(argv[1]));
            sockaddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
            if (!bind(sfd, (struct sockaddr *) &sockaddr, sizeof(sockaddr)) && !listen(sfd, 1)) {
                int s = accept(sfd, NULL, 0);
                if (s >= 0) {
                    char buf[1024];
                    ssize_t size;
                    while (((size = recv(s, buf, sizeof(buf), 0)) > 0) && strncmp(buf, "OFF", 3)) {
                        qsort(buf, size - 1, sizeof(char), cmpChars);
                        send(s, buf, size, 0);
                    }
                    close(s);
                }
            }
            close(sfd);
        }
    }
    return 0;
}