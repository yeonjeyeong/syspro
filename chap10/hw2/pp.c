#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (!newNode) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (*tail != NULL) {
        (*tail)->next = newNode;
    }
    *tail = newNode;

    if (*head == NULL) {
        *head = newNode;
    }
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) {
        printf("The queue is empty.\n");
        return -1;
    }

    struct node *temp = *head;
    int data = temp->data;

    *head = (*head)->next;
    if (*head == NULL) {
        *tail = NULL;
    }

    free(temp);
    return data;
}

void printQueue(struct node *head) {
    printf("Print queue\n");
    struct node *current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    struct node *head = NULL;
    struct node *tail = NULL;

    int input;
    while (1) {
        if (scanf("%d", &input) != 1 || input <= 0) {
            printQueue(head);
            break;
        }
        addq(&head, &tail, input);
    }

    return 0;
}

