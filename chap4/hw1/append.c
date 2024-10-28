#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    FILE *file1, *file2;
    char line[1024];
    char content[2048] = "";

    file2 = fopen(argv[2], "r");
    if (file2 == NULL) {
        perror("Error opening file2");
        return 1;
    }

    while (fgets(line, sizeof(line), file2) != NULL) {
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '\n') {
                line[i] = '\0';
            }
        }
        strcat(content, line);
    }
    fclose(file2);

    file1 = fopen(argv[1], "r");
    if (file1 == NULL) {
        perror("Error opening file1");
        return 1;
    }

    while (fgets(line, sizeof(line), file1) != NULL) {
        for (int i = 0; line[i] != '\0'; i++) {
            if (line[i] == '\n') {
                line[i] = '\0';
            }
        }
        strcat(content, line);
    }
    fclose(file1);

    file2 = fopen(argv[2], "w");
    if (file2 == NULL) {
        perror("Error opening file2 for writing");
        return 1;
    }
    fprintf(file2, "%s", content);
    fclose(file2);

    return 0;
}

