#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int data;
    struct Node *link;
};

typedef struct {
    struct Node *top;
} Stack;

void stack(Stack *s){
    s->top=NULL;
}

bool isEmpty(Stack *s){
    return s->top==NULL;
}

void Push(Stack *s, int a){
    struct Node *newnode=(struct Node *)malloc(sizeof(struct Node));
    if(newnode==NULL){
        printf("Overflow!!!");
        return;
    }
    newnode->data=a;
    newnode->link=s->top;
    s->top=newnode;
    printf("Pushed %d onto the stack.\n",a);
}

int Pop(Stack *s){
    if(isEmpty(s)){
        printf("Underflow!!!");
        return -1;
    }
    struct Node *temp=s->top;
    int popVal=temp->data;
    s->top=s->top->link;
    return popVal;
}

int Peek(Stack *s){
    if(isEmpty(s)){
        printf("Underflow!!!");
        return -1;
    }
    return s->top->data;
}

void display(Stack *s){
    if(isEmpty(s)){
        printf("Underflow!!!");
        return ;
    }
    struct Node* cur=s->top;
    printf("Stack elements (top to bottom): ");
    while (cur!=NULL) {
        printf("%d -> ",cur->data);
        cur=cur->link;
    }
    printf("NULL\n");
}

void freeStack(Stack* s) {
    while (!isEmpty(s)) {
        Pop(s);
    }
}

int main(){
    Stack myStack;
    stack(&myStack);

    // Perform operations
    Push(&myStack, 10);
    Push(&myStack, 20);
    Push(&myStack, 30);
    display(&myStack);

    printf("Top element is: %d\n", Peek(&myStack));

    printf("Popped element: %d\n", Pop(&myStack));
    display(&myStack);

    Push(&myStack, 40);
    display(&myStack);

    // Free memory before exiting
    freeStack(&myStack);

    return 0;

}

