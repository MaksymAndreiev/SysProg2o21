#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/ipc.h>

int main(int argc, char **argv) {
    int *array[3];
    int i, j;
    key_t key = ftok(argv[0], 0);

    for (i = 0; i != 3; ++i) {
        if (!i) {
            int shmid = shmget(key, 1000, 0666 | IPC_CREAT | IPC_EXCL);
            array[i] = shmat(shmid, NULL, 0);
        } else {
            int shmid = shmget(atoi(argv[i]), 1000, 0);
            array[i] = shmat(shmid, NULL, SHM_RDONLY);
            for (j = 0; j != 100; ++j) {
                array[0][j] += array[i][j];
            }
            shmdt(array[i]);
        }
    }

    return printf("%d\n", key) & shmdt(array[0]);
}
