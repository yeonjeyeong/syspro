#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main(int argc, char* argv[]) {
    char *command1, *command2;
    char *args1[64], *args2[64];
    int fd[2], i;

    if (argc == 1) {
        printf("[shell] ");
        char str[1024];
        fgets(str, sizeof(str), stdin);
        str[strlen(str) - 1] = '\0';

        if (strchr(str, '|') != NULL) {
            command1 = strtok(str, "|");
            command2 = strtok(NULL, "|");

            i = 0;
            args1[i] = strtok(command1, " ");
            while (args1[i] != NULL) {
                i++;
                args1[i] = strtok(NULL, " ");
            }
            args1[i] = NULL;

            i = 0;
            args2[i] = strtok(command2, " ");
            while (args2[i] != NULL) {
                i++;
                args2[i] = strtok(NULL, " ");
            }
            args2[i] = NULL;

            pipe(fd);

            if (fork() == 0) {
                close(fd[READ]);
                dup2(fd[WRITE], STDOUT_FILENO);
                close(fd[WRITE]);

                execvp(args1[0], args1);
                perror("execvp failed");
                exit(1);
            } else {
                close(fd[WRITE]);
                dup2(fd[READ], STDIN_FILENO);
                close(fd[READ]);

                execvp(args2[0], args2);
                perror("execvp failed");
                exit(1);
            }
        }
    } else if (argc >= 3) {
        command1 = argv[1];
        command2 = argv[2];

        i = 0;
        args1[i] = strtok(command1, " ");
        while (args1[i] != NULL) {
            i++;
            args1[i] = strtok(NULL, " ");
        }
        args1[i] = NULL;

        i = 0;
        args2[i] = strtok(command2, " ");
        while (args2[i] != NULL) {
            i++;
            args2[i] = strtok(NULL, " ");
        }
        args2[i] = NULL;

        pipe(fd);

        if (fork() == 0) {
            close(fd[READ]);
            dup2(fd[WRITE], STDOUT_FILENO);
            close(fd[WRITE]);

            execvp(args1[0], args1);
            perror("execvp failed");
            exit(1);
        } else {
            close(fd[WRITE]);
            dup2(fd[READ], STDIN_FILENO);
            close(fd[READ]);

            execvp(args2[0], args2);
            perror("execvp failed");
            exit(1);
        }
    }

    return 0;
}

