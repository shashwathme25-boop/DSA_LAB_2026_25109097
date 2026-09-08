#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *prev;
    struct Node *next;
};

int main(){
    struct Node *head=NULL;
    struct Node *temp, *newNode;
    int n, i, value;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    // Input
    for (i=0;i<n;i++){
        newNode=(struct Node *)malloc(sizeof(struct Node));

        printf("Enter data: ");
        scanf("%d", &value);

        newNode->data=value;
        newNode->next=NULL;
        newNode->prev=NULL;

        if (head==NULL){
            head=newNode;
        } 
        else{
            temp=head;

            while(temp->next!=NULL){
                temp=temp->next;
            }

            temp->next=newNode;
            newNode->prev=temp;
        }
    }

    // Display original list
    printf("\nOriginal list: ");
    temp=head;

    while (temp!=NULL) {
        printf("%d ", temp->data);
        temp=temp->next;
    }

    // Reverse
    temp = NULL;
    struct Node *cur=head;

    while (cur!=NULL) {
        temp=cur->prev;
        cur->prev=cur->next;
        cur->next=temp;

        cur=cur->prev;
    }

    if (temp!=NULL) {
        head=temp->prev;
    }

    // Display reversed list
    printf("\nReversed list: ");
    temp=head;

    while (temp!=NULL) {
        printf("%d ", temp->data);
        temp=temp->next;
    }

    return 0;
}