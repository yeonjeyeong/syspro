#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int fd1, fd2;

	if((fd1 = creat("myfile", 0600))== -1)
		perror("myfile");

	write(fd1, "Hello! LInux", 12);
	fd2 = dup(fd1);
	write(fd2,"Bye! Linux", 10);

	close(fd1);
	close(fd2);
	exit(0);
}

