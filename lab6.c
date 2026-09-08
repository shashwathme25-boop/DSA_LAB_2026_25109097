#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int main() {

    struct Node *head = NULL;
    struct Node *tail = NULL;
    struct Node *NewNode;

    int n, i, val;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    // Create linked list
    for (i = 0; i < n; i++) {

        NewNode = (struct Node *)malloc(sizeof(struct Node));

        printf("Enter data: ");
        scanf("%d", &val);

        NewNode->data = val;
        NewNode->next = NULL;

        if (head == NULL) {
            head = NewNode;
            tail = NewNode;
        }
        else {
            tail->next = NewNode;
            tail = NewNode;
        }
    }

    // Print original list
    printf("Original linked list: ");

    struct Node *temp = head;

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    // Reverse the linked list
    struct Node *prev = NULL;
    struct Node *current = head;
    struct Node *next = NULL;

    while (current != NULL) {

        next = current->next;
        current->next = prev;

        prev = current;
        current = next;
    }

    head = prev;

    // Print reversed list
    printf("\nReversed linked list: ");

    temp = head;

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    return 0;
}