#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

int main() {
    int pid = fork();

    if (!pid) {
        signal(SIGURG, exit);
        setsid();
        chdir("/");

        while (4 > pid)
            close(pid++);

        while (1);
    }

    return printf("%d\n", pid) & 0;
}
