#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[ ])
{
   if (symlink(argv[1], argv[2]) == -1) {
	   perror("Error creating symbolic link");
	   exit(1);
   }
   exit(0);
}

