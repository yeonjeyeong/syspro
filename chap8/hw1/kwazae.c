#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		return 1;
	}

	char **ptr;
	extern char **environ;

	switch (argv[1][1]) {
		case 'i':
			printf("My process number: [%d] \n", getpid());
			break;

		case 'p':
			printf("My parent process number: [%d] \n", getppid());
			break;

		case 'u':
			printf("My Realistic User ID: %d(%s) \n", getuid(), getpwuid(getuid())->pw_name);
			printf("My Valid User ID: %d(%s) \n", geteuid(), getpwuid(geteuid())->pw_name);
			break;

		case 'g':
			printf("My Realistic Group ID: %d(%s) \n", getgid(), getgrgid(getgid())->gr_name);
			printf("My Valid Group ID: %d(%s) \n", getegid(), getgrgid(getegid())->gr_name);
			break;

		case 'e':
			if (argc == 2) {
				for (ptr = environ; *ptr != 0; ptr++) {
					printf("%s \n", *ptr);
				}
			} else if (argc == 3) {
				char *value = getenv(argv[2]);
				if (value) {
					printf("%s = %s \n", argv[2], value);
				} else {
					printf("Unknown \n");
				}
			} else {
				return 1;
			}
			break;

		default:
			printf("Invalid option \n");
			break;
	}

	return 0;
}

