#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid;
    char parent_msg[] = "Hello from PID";
    char child_msg[] = "Hello from PID";
    char buffer[128];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) {
        close(pipefd[0]);
        snprintf(buffer, sizeof(buffer), "%s %d", parent_msg, getpid());
        write(pipefd[1], buffer, strlen(buffer) + 1);
        close(pipefd[1]);

        wait(NULL);

        printf("Send: [%d] %s\n", getpid(), buffer);
    } else {
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));
        close(pipefd[0]);

        printf("Recv: [%d] %s\n", getpid(), buffer);
    }

    return 0;
}

