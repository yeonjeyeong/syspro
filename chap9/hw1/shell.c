#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 1024
#define MAX_ARGS 100

void execute_command(char *cmd);
void parse_and_execute(char *line);

int main() {
    char line[MAX_LINE];

    while (1) {
        printf("[shell] ");
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0) {
            break;
        }

        parse_and_execute(line);
    }

    return 0;
}

void parse_and_execute(char *line) {
    char *cmd = strtok(line, ";");
    while (cmd != NULL) {
        execute_command(cmd);
        cmd = strtok(NULL, ";");
    }
}

void execute_command(char *cmd) {
    char *args[MAX_ARGS];
    int background = 0;
    int redirect_in = 0, redirect_out = 0;
    char *input_file = NULL, *output_file = NULL;

    if (strchr(cmd, '&') != NULL) {
        background = 1;
        cmd[strcspn(cmd, "&")] = '\0';
    }

    char *redir_in_pos = strchr(cmd, '<');
    char *redir_out_pos = strchr(cmd, '>');
    if (redir_in_pos != NULL) {
        redirect_in = 1;
        *redir_in_pos = '\0';
        input_file = strtok(redir_in_pos + 1, " ");
    }
    if (redir_out_pos != NULL) {
        redirect_out = 1;
        *redir_out_pos = '\0';
        output_file = strtok(redir_out_pos + 1, " ");
    }

    int i = 0;
    char *token = strtok(cmd, " ");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL) {
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        if (redirect_in && input_file != NULL) {
            int fd_in = open(input_file, O_RDONLY);
            if (fd_in < 0) {
                perror("Input redirection failed");
                exit(EXIT_FAILURE);
            }
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }

        if (redirect_out && output_file != NULL) {
            int fd_out = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out < 0) {
                perror("Output redirection failed");
                exit(EXIT_FAILURE);
            }
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }

        if (execvp(args[0], args) == -1) {
            perror("Command execution failed");
            exit(EXIT_FAILURE);
        }
    } else if (pid > 0) {
        if (!background) {
            waitpid(pid, NULL, 0);
        }
    } else {
        perror("Fork failed");
    }
}

