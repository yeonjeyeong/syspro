#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAXARG 100

int main() {
    char input[256];
    char *args[MAXARG];
    char *cmd;
    char *saveptr;
    pid_t pid;
    int status;

    while (1) {
        printf("Pls input cmd : ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "exit") == 0) {
            printf("Exit\n");
            break;
        }

        int i = 0;
        cmd = strtok_r(input, " ", &saveptr);
        while (cmd != NULL && i < MAXARG - 1) {
            args[i++] = cmd;
            cmd = strtok_r(NULL, " ", &saveptr);
        }
        args[i] = NULL;

        int background = 0;
        if (i > 0 && strcmp(args[i - 1], "&") == 0) {
            background = 1;
            args[i - 1] = NULL;
        }

        pid = fork();
        if (pid < 0) {
            perror("fork failed");
            continue;
        } else if (pid == 0) {
            printf("[%d] child process start\n", getpid());
            if (execvp(args[0], args) < 0) {
                perror("exec failed");
            }
            exit(1);
        } else {
            printf("[%d] Parent process start\n", getpid());
            if (!background) {
                waitpid(pid, &status, 0);
                printf("[%d] child process end %d\n", getpid(), pid);
            }
        }
    }
    printf("Parent process end\n");
    return 0;
}

