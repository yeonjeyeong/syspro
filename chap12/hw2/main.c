#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 100

void to_uppercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
}

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid1, pid2;
    char buffer[BUFFER_SIZE];

    printf("parent process start\n");

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid1 = fork();
    if (pid1 == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        close(pipe1[0]);
        printf("Input string: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        write(pipe1[1], buffer, strlen(buffer) + 1);
        close(pipe1[1]);
        exit(0);
    }

    pid2 = fork();
    if (pid2 == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (pid2 == 0) {
        close(pipe1[1]);
        read(pipe1[0], buffer, BUFFER_SIZE);
        close(pipe1[0]);
        to_uppercase(buffer);
        close(pipe2[0]);
        write(pipe2[1], buffer, strlen(buffer) + 1);
        close(pipe2[1]);
        exit(0);
    }

    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[1]);
    read(pipe2[0], buffer, BUFFER_SIZE);
    close(pipe2[0]);
    printf("%s\n", buffer);
    return 0;
}

