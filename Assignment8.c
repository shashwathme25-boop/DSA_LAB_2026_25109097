#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>


// Q - Parentheses Count

int LongestValidParantheses(char* s){
    int n=strlen(s);
    int r=0,l=0,max=0;

    //L to R
    for(int i=0;i<n;i++){
        if(s[i]=='(') l++; else r++;
        if(l==r){
            if(2*r>max){
                max=2*r;
            }
        }
        else if(r>l){
            r=l=0;//reset
        }
    }
    l=r=0;//reset

    //R to L
    for(int i=n-1;i>=0;i--){
        if(s[i]=='(') l++; else r++;
        if(l==r){
            if(2*l>max){
                max=2*l;
            }
        }
        else if(r<l){
            r=l=0;//reset
        }
    }
    l=r=0;

    return max;
}

int main(){
    int a=LongestValidParantheses("((()())");
    printf("%d",a);
    return 0;
}















// Q - Board Game

#define MAX 30

int removeGroups(char board[], int n){
    char stack[MAX];
    int top = -1;

    for(int i=0;i<n;i++){
        // Push current ball
        stack[++top] = board[i];
        // Count consecutive same balls at top
        int count = 0;

        for(int j=top;j>=0 && stack[j]==stack[top];j--)
            count++;

        if (count >= 3){
            top -= count;
            // Cascading removal
            int changed = 1;
            while (changed && top>=0){
                changed=0;
                int cnt=1;
                for(int j=top-1;j>=0;j--){
                    if (stack[j]==stack[top])
                        cnt++;
                    else
                        break;
                }
                if (cnt >= 3){
                    top -= cnt;
                    changed = 1;
                }
            }
        }
    }

    // Copy stack back to board
    int newSize = top + 1;
    for (int i= 0;i<newSize;i++)
        board[i] = stack[i];

    board[newSize] = '\0';
    return newSize;
}


// Recursive function
int solve(char board[], int n, char hand[], int h){
    // Board completely cleared (base case)
    if (n == 0)
        return 0;
    // No balls left in hand 
    if (h == 0)
        return INT_MAX;

    int answer = INT_MAX;

    // Try every ball from hand
    for(int k=0;k<h;k++){
        // Avoid trying the same colored ball twice
        if(k>0 && hand[k]==hand[k - 1])
            continue;
        char ball = hand[k];

        // Try inserting at every position
        for(int pos=0;pos<=n;pos++){
            char newBoard[MAX];
            // Copy board and insert ball
            int x =0;

            for(int i=0;i<pos;i++)
                newBoard[x++] = board[i];
            newBoard[x++]=ball;

            for(int i=pos;i<n;i++)
                newBoard[x++] = board[i];
            newBoard[x] = '\0';

            // Remove groups
            int newN = removeGroups(newBoard,n + 1);

            // Create new hand without selected ball
            char newHand[MAX];
            int y=0;
            for(int i=0;i<h;i++){
                if(i != k)
                    newHand[y++]=hand[i];
            }
            newHand[y]='\0';

            // Solve remaining board
            int result=solve(newBoard, newN, newHand, h - 1);

            if (result!=INT_MAX){
                if (result+1<answer)
                    answer=result+1;
            }
        }
    }
    return answer;
}


int main(){
    char board[MAX];
    char hand[MAX];

    printf("Enter board : ");
    scanf("%s", board);

    printf("Enter hand : ");
    scanf("%s", hand);

    int n=strlen(board);
    int h=strlen(hand);

    // Sort hand so duplicate balls are together
    for(int i=0;i<h-1;i++){
        for(int j=i+1;j<h;j++){
            if (hand[i]>hand[j]){
                char temp = hand[i];
                hand[i] = hand[j];
                hand[j] = temp;
            }
        }
    }

    int answer=solve(board, n, hand, h);

    if(answer==INT_MAX)
        printf("-1\n");
    else
        printf("Minimum balls inserted = %d\n", answer);

    return 0;
}






// Q - Infix to Postfix

#define MAX 100

typedef struct{
    int top;
    char items[MAX];
}Stack;

void push(Stack *s,char value){
    if(s->top<MAX-1){
        s->items[++(s->top)]=value;
    }
}

char pop(Stack*s){
    if(s->top>=0){
        return s->items[(s->top)--];
    }
    return '\0';
}

char peek(Stack *s){
    if(s->top>=0){
        return s->items[s->top];
    }
    return '\0';
}

int isEmpty(Stack *s){
    return s->top==-1;
}

int precedence(char ch){
    switch(ch){
        case '^':
        return 3;
        case '%':
        case '*':
        case '/':
        return 2;
        case '+':
        case '-':
        return 1;
        default :
        return 0;
    }
}

int isRightAssociative(char ch){
    if (ch=='^'){
        return 1;
    }
    return 0;
}

void InToPost(char*infix, char* postfix){
    Stack s;
    s.top=-1;
    int k=0;

    for(int i=0;infix[i]!='\0';i++){
        char c=infix[i];
        if(isalnum(c)){
            postfix[k++]=c;
        }
        else if(c=='('){
            push(&s,c);
        }
        else if(c==')'){
            while(!isEmpty(&s) && peek(&s)!='('){
                postfix[k++]=pop(&s);
            }
            pop(&s);
        }
        else{
            while((!isEmpty(&s) && peek(&s)!='(') && precedence(peek(&s))>precedence(c) || precedence(peek(&s))==precedence(c) && !isRightAssociative(c)){
                postfix[k++]=pop(&s);
            }
            push(&s, c);
        }
    }
    while(!isEmpty(&s)){
        postfix[k++]=pop(&s);
    }

    postfix[k] = '\0';
}

int main(){
    char infix[MAX]="A+B*C^D-E%F";
    char postfix[MAX];

    printf("Infix expression : %s\n",infix);
    InToPost(infix,postfix);
    printf("Postfix expression : %s\n",postfix);
    return 0;
}


