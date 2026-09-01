#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node *head=NULL, *tail=NULL;
struct node *ptr, *tmp, *start;

int main(){
    int a, val;

    printf("Enter size of linked list: ");
    scanf("%d", &a);

    for (int i=1; i<=a; i++) {
        printf("Enter the number to be input: ");
        scanf("%d",&val);
        struct node *NewNode=(struct node *)malloc(sizeof(struct node));
        NewNode->data=val;
        if (head==NULL) {
            head=NewNode;
            tail=NewNode;
            NewNode->link=head;
        }
        else {
            tail->link=NewNode;
            tail=NewNode;
            tail->link=head;
        }
    }

    start=head;

    if (head==NULL){
        printf("Empty linked list");
    }
    else{
        struct node *cur = head;

        do{
            printf("%d ",cur->data);
            cur=cur->link;
        } while(cur!=head);
    }
    printf("\n");

    //Inserion at beginning

    struct node *NewNode = (struct node *)malloc(sizeof(struct node));
    NewNode->data = 10;
    NewNode->link = head;
    head = NewNode;
    tail->link = head;

    if (head==NULL){
        printf("Empty linked list");
    }
    else{
        struct node *cur = head;

        do{
            printf("%d ",cur->data);
            cur=cur->link;
        } while(cur!=head);
    }
    printf("\n");

    //insertion at end

    NewNode = (struct node *)malloc(sizeof(struct node));
    NewNode->data=20;
    NewNode->link = head;
    tail->link = NewNode;
    tail = NewNode;

    if (head==NULL){
        printf("Empty linked list");
    }
    else{
        struct node *cur = head;

        do{
            printf("%d ",cur->data);
            cur=cur->link;
        } while(cur!=head);
    }
    printf("\n");

    //insertion at a position
    NewNode=(struct node *)malloc(sizeof(struct node));
    NewNode->data=30;
    int count=0;
    ptr=head;
    do{
        count++;
        ptr = ptr->link;
    } while (ptr != head);
    ptr=head;
    for (int i=1;i<=count/2;i++){
        ptr=ptr->link;
    }
    NewNode->link=ptr->link;
    ptr->link=NewNode;

    if (head==NULL){
        printf("Empty linked list");
    }
    else{
        struct node *cur = head;

        do{
            printf("%d ",cur->data);
            cur=cur->link;
        } while(cur!=head);
    }
    printf("\n");

    //delete from start
    if (head==NULL){
    printf("Empty linked list");
    }
    else if(head==tail){
        free(head);
        head=NULL;
        tail=NULL;
    }
    else {
        ptr=head;
        while (ptr->link != head) {
            ptr=ptr->link;
        }
        struct node *temp=head;
        head=head->link;
        ptr->link=head;
        free(temp);
    }

    if (head==NULL){
        printf("Empty linked list");
    }
    else{
        struct node *cur = head;

        do{
            printf("%d ",cur->data);
            cur=cur->link;
        } while(cur!=head);
    }
    printf("\n");

    //delete from end
    if (head==NULL){
    printf("Empty linked list");
    }
    else if(head==tail){
        free(tail);
        head=NULL;
        tail=NULL;
    }
    else{
    ptr=head;
    while (ptr->link != tail) {
        ptr = ptr->link;
    }
    struct node *temp = tail;
    tail = ptr;
    tail->link = head;
    free(temp);
    }

    if (head==NULL){
        printf("Empty linked list");
    }
    else{
        struct node *cur = head;

        do{
            printf("%d ",cur->data);
            cur=cur->link;
        } while(cur!=head);
    }
    printf("\n");

    //delete from position 3

    int pos = 3;

    if (head==NULL){
        printf("Empty linked list");
    }
    else if(head==tail) {
        if (pos==1){
            free(head);
            head=NULL;
            tail=NULL;
        }
        else {
            printf("Invalid position");
        }
    }
    else{
        ptr=head;
        for (int i=1;i<pos-1;i++){
            ptr=ptr->link;
        }
        struct node *temp=ptr->link;
        ptr->link=temp->link;
        if (temp==tail) {
            tail=ptr;
        }
        free(temp);

        if (head==NULL){
        printf("Empty linked list");
    }
        else{
        struct node *cur = head;

        do{
            printf("%d ",cur->data);
            cur=cur->link;
        } while(cur!=head);
    }
    printf("\n");
    }

    return 0;
}