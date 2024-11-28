#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void alarmHandler(int signo);

int main()
{
	signal(SIGALRM, alarmHandler);
	alarm(5);
	short i = 0;
	while (1){
		sleep(1);
		i++;
		printf("%d second\n",i);
	}
	printf("end\n");
}

void alarmHandler(int signo)
{
	printf("Wake up\n");
	exit(0);
}

