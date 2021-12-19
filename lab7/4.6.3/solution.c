#include <stdio.h>
#include <stdlib.h>
#include <signal.h>


void sighandler(int sig) {
	static int sum1, sum2;
	sum1 += (sig == SIGUSR1);
	sum2 += (sig == SIGUSR2);
	if (sig == SIGTERM) {
		printf("%d %d\n", sum1, sum2);
		exit(0);
	}
}

int main() {
	signal(SIGUSR1, sighandler);
	signal(SIGUSR2, sighandler);
	signal(SIGTERM, sighandler);
	while(1);
}
