#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 256

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1; 
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1; 
    }

    char *lines[MAX_LINES];
    int line_count = 0;
    char buffer[MAX_LINE_LENGTH];

    while (line_count < MAX_LINES) {
        ssize_t bytes_read = read(fd, buffer, MAX_LINE_LENGTH - 1);

        if (bytes_read <= 0) {
            break; 
        }

        buffer[bytes_read] = '\0'; 

        char *line = strtok(buffer, "\n");
        while (line != NULL && line_count < MAX_LINES) {
            lines[line_count] = malloc(strlen(line) + 1);
            strcpy(lines[line_count], line);
            line_count++;
            line = strtok(NULL, "\n");
        }
    }

    close(fd); 

    for (int i = line_count - 1; i >= 0; i--) {
        printf("%s\n", lines[i]);
        free(lines[i]); 
    }

    return 0;
}

