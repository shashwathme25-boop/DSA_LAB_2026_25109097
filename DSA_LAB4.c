#include <stdio.h>
#include <stdlib.h>

int main() {
    struct node {
        int data;
        struct node *link;
    };

    struct node *ptr, *start, *tmp, *second, *third;

    tmp=(struct node *)malloc(sizeof(struct node));
    second=(struct node *)malloc(sizeof(struct node));
    third=(struct node *)malloc(sizeof(struct node));

    tmp->data=0;
    tmp->link=second;
    start=tmp;

    second->data=10;
    second->link=third;

    third->data=20;
    third->link=NULL;

    printf("\n");
    printf("Original Linked List : ");
    ptr=start;
    while(ptr!=NULL){
        printf("%d ", ptr->data);
        ptr=ptr->link;
    }
    printf("\n");

    //inserting node at beginning
    tmp=(struct node *)malloc(sizeof(struct node));
    tmp->data=30;
    tmp->link=start;
    start=tmp;

    printf("\n");
    printf("Insertion at head : ");
    ptr=start;
    while(ptr!=NULL){
        printf("%d ", ptr->data);
        ptr=ptr->link;
    }
    printf("\n");

    //inserting node at end
    tmp=(struct node *)malloc(sizeof(struct node));
    tmp->data=40;
    tmp->link=NULL;
    ptr=start;
    while(ptr->link!=NULL){
        ptr=ptr->link;
    }
    ptr->link=tmp;

    printf("\n");
    printf("Insertion at tail : ");
    ptr=start;
    while(ptr!=NULL){
        printf("%d ", ptr->data);
        ptr=ptr->link;
    }
    printf("\n");

    //inserting at mid position
    tmp=(struct node *)malloc(sizeof(struct node));
    tmp->data=50;
    int count=0;
    ptr=start;
    while(ptr->link!=NULL){
        ptr=ptr->link;
        count++;
    }
    ptr=start;
    for(int i=1;i<=(int)(count/2)-1;i++){
        ptr=ptr->link;
    }
    tmp->link=ptr->link;
    ptr->link=tmp;

    printf("\n");
    printf("Insertion at mid : ");
    ptr=start;
    while(ptr!=NULL){
        printf("%d ", ptr->data);
        ptr=ptr->link;
    }
    printf("\n");

    //deleting from the start
    start=start->link;

    printf("\n");
    printf("Deletion from Head : ");
    ptr=start;
    while(ptr!=NULL){
        printf("%d ", ptr->data);
        ptr=ptr->link;
    }
    printf("\n");

    //deletion from a position
    int pos=3;
    ptr=start;
    for(int i=1;i<pos-1;i++){
        ptr=ptr->link;
    }
    ptr->link=ptr->link->link;

    printf("\n");
    printf("Deletion from mid : ");
    ptr=start;
    while(ptr!=NULL){
        printf("%d ", ptr->data);
        ptr=ptr->link;
    }
    printf("\n");

    //delete from tail
    ptr=start;
    while(ptr->link->link!=NULL){
        ptr=ptr->link;
    }
    ptr->link=NULL;

    ptr=start;
    printf("\n");
    printf("Deletion from Tail : ");
    while(ptr!=NULL){
        printf("%d ", ptr->data);
        ptr=ptr->link;
    }
    printf("\n");
}
