#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[]) {
    FILE *fp;
    int c;
    int print_line_numbers = 0;
    int line_number = 0;

    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        print_line_numbers = 1;
        argv++;
        argc--;
    }

    if (argc < 2) {
        fp = stdin;
        if (print_line_numbers) {
            fprintf(stderr, "No files specified. Reading from standard input.\n");
        }
        
        while ((c = getc(fp)) != EOF) {
            putc(c, stdout);
        }
        return 0;
    }

    for (int i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "Error opening file: %s\n", argv[i]);
            continue;
        }

        if (print_line_numbers) {
            char buffer[MAXLINE];
            int line = 0;

            while (fgets(buffer, MAXLINE, fp) != NULL) {
                line++;
                printf("%d %s", line, buffer);
            }
        } else {
            while ((c = getc(fp)) != EOF) {
                putc(c, stdout);
            }
        }

        fclose(fp);
    }

    return 0;
}

