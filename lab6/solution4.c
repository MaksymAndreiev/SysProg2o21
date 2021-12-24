#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int cntChilds(pid_t ppid)
{
    int sum = 0;
    char cmd[32];
    sprintf(cmd, "ps -o pid= --ppid %d", ppid);
    FILE *f = popen(cmd, "r");
    pid_t pid;
    while (fscanf(f, "%d", &pid) != EOF) {
        sum += 1 + cntChilds(pid);
    }
    pclose(f);
    return sum;
}

int main(int argc, char *argv[]) {
    printf("%d\n", cntChilds(atoi(argv[1])) + 1);
}
