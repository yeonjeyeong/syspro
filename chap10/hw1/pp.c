#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

struct node* push(struct node *top, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("Memory allocation failed\n");
        return top;
    }
    new_node->data = data;
    new_node->next = top;
    return new_node;
}

struct node* pop(struct node *top) {
    if (top == NULL) {
        printf("Stack is empty\n");
        return top;
    }
    struct node *temp = top;
    int popped_data = temp->data;
    top = temp->next;
    free(temp);
    return top;
}

void print_stack(struct node *top) {
    printf("Print stack\n");
    while (top != NULL) {
        printf("%d\n", top->data);
        top = top->next;
    }
}

int extract_integer_part(char *input) {
    char integer_part[100] = "";
    int i = 0;

    while (input[i] != '\0') {
        if (isdigit(input[i])) {
            strncat(integer_part, &input[i], 1);
        } else if (input[i] == '.') {
            break;
        } else {
            return -1;
        }
        i++;
    }

    if (strlen(integer_part) > 0) {
        return atoi(integer_part);
    }
    return -1;
}

int is_natural_number(char *input) {
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    struct node *stack = NULL;
    char input[100];

    while (1) {
        scanf("%s", input);

        if (!is_natural_number(input)) {
            int extracted_number = extract_integer_part(input);

            if (extracted_number != -1) {
                stack = push(stack, extracted_number);
            }

            print_stack(stack);
            break;
        }

        int num = atoi(input);
        stack = push(stack, num);
    }

    return 0;
}

