#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define n 5

typedef struct {
    int ele[n];
    int top;
} Stack;

void stack(Stack *s){
    s->top=-1; 
} //initial state of stack i.e empty

bool isFull(Stack *s){
    return s->top==n-1;
} //check for full stack

bool isEmpty(Stack *s){
    return s->top==-1;
} //check for empty stack

void Push(Stack *s, int a){
    if(isFull(s)){
        printf("Overflow!!!\n");
        return;
    }
    s->top++;
    s->ele[s->top]=a;
    printf("Pushed %d onto the stack.\n",a);
}

int Pop(Stack *s){
    if(isEmpty(s)){
        printf("Underflow!!!\n");
        return -1;
    }
    int popVal=s->ele[s->top];
    s->top--;
    return popVal;
}

int Peek(Stack *s){
    if(isEmpty(s)){
        printf("Underflow!!!\n");
        return -1;
    }
    return s->ele[s->top];
}

void display(Stack *s){
    if(isEmpty(s)){
        printf("Underflow!!!\n");
        return;
    }
    printf("Stack elements (top to bottom): ");
    for (int i=s->top;i>=0;i--) {
        printf("%d ",s->ele[i]);
    }
    printf("\n");
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

    // Testing overflow
    Push(&myStack, 40);
    Push(&myStack, 50);
    Push(&myStack, 60); 
    Push(&myStack, 70); // This should trigger overflow if MAX is 5

    return 0;
}
