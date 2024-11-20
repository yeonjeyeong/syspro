#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int child, pid, status;
	pid = fork();
	if(pid ==0){
		execvp(argv[1],&argv[1]);
		fprintf(stderr, "%s impossible to run\n",argv[1]);
	}else{
		printf("[%d] child process %d end\n", getpid(), pid);
		printf("\t end code %d \n", status>>8);
	}
}
