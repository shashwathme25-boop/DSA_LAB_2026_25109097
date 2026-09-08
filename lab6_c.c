#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

int main() {
    struct Node *head=NULL;
    struct Node *newNode, *temp;
    int n, i, value;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    // Input
    for(i=0;i<n;i++){
        newNode=(struct Node *)malloc(sizeof(struct Node));

        printf("Enter data: ");
        scanf("%d", &value);

        newNode->data=value;

        if(head==NULL){
            head=newNode;
            newNode->next=head;
        }
        else{
            temp=head;

            while (temp->next!=head) {
                temp=temp->next;
            }

            temp->next=newNode;
            newNode->next=head;
        }
    }

    // Display original list
    printf("\nOriginal list: ");

    temp=head;

    if(head!=NULL){
        do{
            printf("%d ", temp->data);
            temp=temp->next;
        }while(temp!=head);
    }

    // Reverse circular linked list
    struct Node *prev=NULL;
    struct Node *cur=head;
    struct Node *nextNode;

    if (head!=NULL) {
        do{
            nextNode=cur->next;
            cur->next=prev;
            prev=cur;
            cur=nextNode;
        }while(cur!=head);

        head->next=prev;
        head=prev;
    }

    // Display reversed list
    printf("\nReversed list: ");

    temp=head;

    if(head!=NULL){
        do{
            printf("%d ", temp->data);
            temp=temp->next;
        }while(temp!=head);
    }

    return 0;
}