#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 256

void print_lines(int fd, int start_line, int end_line) {
    char buf;
    int current_line = 1;
    int reading = 0;

    while (read(fd, &buf, 1) > 0) {
        if (current_line >= start_line && current_line <= end_line) {
            if (!reading) {
                reading = 1;
            }
            putchar(buf); 
        }

        if (buf == '\n') {
            if (current_line >= start_line && current_line <= end_line) {
                reading = 0;
            }
            current_line++; 
        }

        if (current_line > end_line) {
            break;
        }
    }
}

void print_line_list(int fd, char *input) {
    char *token = strtok(input, ",");
    while (token != NULL) {
        int line_number = atoi(token);
        lseek(fd, 0, SEEK_SET); 
        print_lines(fd, line_number, line_number);
        token = strtok(NULL, ",");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		int fd = open(argv[1], O_RDONLY);
		print_lines(fd, 1, 2);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }


    int total_lines = 0;
    char buf;
    while (read(fd, &buf, 1) > 0) {
        if (buf == '\n') {
            total_lines++;
        }
    }
    
    char input[50];
    scanf("%s", input);

    lseek(fd, 0, SEEK_SET); 

    if (strcmp(input, "*") == 0) {
        print_lines(fd, 1, total_lines);
    } else if (strstr(input, "-") != NULL) {
        int start, end;
        sscanf(input, "%d-%d", &start, &end);
        print_lines(fd, start, end);
    } else if (strstr(input, ",") != NULL) {
        print_line_list(fd, input);
    } else {
        int line_number;
        sscanf(input, "%d", &line_number);
        print_lines(fd, line_number, line_number);
    }

    close(fd);
    return 0;
}

