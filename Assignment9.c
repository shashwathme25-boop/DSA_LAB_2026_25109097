// Q1

#include<stdio.h>

int main(){
    int n,k;

    printf("Enter the number of passengers: ");
    scanf("%d",&n);

    int stress[n];

    printf("Enter the stress levels of passengers: ");
    for(int i=0;i<n;i++)
        scanf("%d",&stress[i]);

    printf("Enter the threshold K: ");
    scanf("%d",&k);

    int maxdq[n],mindq[n];
    int maxfront=0,maxrear=-1;
    int minfront=0,minrear=-1;
    int left=0,ans=0;

    for(int right=0;right<n;right++){

        while(maxrear>=maxfront&&stress[maxdq[maxrear]]<stress[right])
            maxrear--;
        maxdq[++maxrear]=right;
        while(minrear>=minfront&&stress[mindq[minrear]]>stress[right])
            minrear--;
        mindq[++minrear]=right;
        while(stress[maxdq[maxfront]]-stress[mindq[minfront]]>k){
            if(maxdq[maxfront]==left)
                maxfront++;
            if(mindq[minfront]==left)
                minfront++;
            left++;
        }

        if(right-left+1>ans)
            ans=right-left+1;
    }
    printf("The maximum number of consecutive passengers that can board together is %d.\n",ans);
    return 0;
}







//Q2

#include<stdio.h>
#include<stdlib.h>

int cmp(const void*a,const void*b){
    return (*(int*)a-*(int*)b);
}

int canComplete(int tasks[],int workers[],int m,int pills,int strength,int mid){
    int available[mid];
    int count=0,used=0;

    for(int i=m-mid;i<m;i++)
        available[count++]=workers[i];

    for(int i=0;i<count;i++){
        for(int j=i+1;j<count;j++){
            if(available[i]>available[j]){
                int temp=available[i];
                available[i]=available[j];
                available[j]=temp;
            }
        }
    }

    for(int i=mid-1;i>=0;i--){
        int pos=-1;

        for(int j=0;j<count;j++){
            if(available[j]>=tasks[i]){
                pos=j;
                break;
            }
        }

        if(pos!=-1){
            for(int j=pos;j<count-1;j++)
                available[j]=available[j+1];

            count--;
        }
        else{
            if(used==pills)
                return 0;

            for(int j=0;j<count;j++){
                if(available[j]+strength>=tasks[i]){
                    pos=j;
                    break;
                }
            }

            if(pos==-1)
                return 0;

            for(int j=pos;j<count-1;j++)
                available[j]=available[j+1];

            count--;
            used++;
        }
    }

    return 1;
}

int maxTaskAssign(int tasks[],int workers[],int n,int m,int pills,int strength){
    qsort(tasks,n,sizeof(int),cmp);
    qsort(workers,m,sizeof(int),cmp);

    int low=0;
    int high=(n<m)?n:m;
    int ans=0;

    while(low<=high){
        int mid=low+(high-low)/2;

        if(canComplete(tasks,workers,m,pills,strength,mid)){
            ans=mid;
            low=mid+1;
        }
        else
            high=mid-1;
    }

    return ans;
}

int main(){
    int n,m,pills,strength;

    printf("Enter the number of tasks: ");
    scanf("%d",&n);

    int tasks[n];

    printf("Enter the strength required for each task: ");
    for(int i=0;i<n;i++)
        scanf("%d",&tasks[i]);

    printf("Enter the number of workers: ");
    scanf("%d",&m);

    int workers[m];

    printf("Enter the strength of each worker: ");
    for(int i=0;i<m;i++)
        scanf("%d",&workers[i]);

    printf("Enter the number of available pills: ");
    scanf("%d",&pills);

    printf("Enter the strength provided by each pill: ");
    scanf("%d",&strength);

    int ans=maxTaskAssign(tasks,workers,n,m,pills,strength);

    printf("The maximum number of tasks that can be completed is %d.\n",ans);

    return 0;
}









//Q3 (Using ARRAY)

#include<stdio.h>

int queue[100];
int front=-1,rear=-1;

void enqueue(int x){
    if(rear==99){
        printf("Queue Overflow! Insertion is not possible.\n");
        return;
    }
    if(front==-1)
        front=0;

    queue[++rear]=x;
    printf("The element %d has been inserted into the queue.\n",x);
}

void dequeue(){
    if(front==-1){
        printf("Queue Underflow! The queue is empty.\n");
        return;
    }
    printf("The deleted element is %d.\n",queue[front]);
    front++;
    if(front>rear){
        front=-1;
        rear=-1;
    }
}

void display(){
    if(front==-1){
        printf("The queue is empty.\n");
        return;
    }
    printf("The elements in the queue are: ");
    for(int i=front;i<=rear;i++)
        printf("%d ",queue[i]);
    printf("\n");
}

int main(){
    printf("Inserting elements into the queue:\n");
    enqueue(10);
    enqueue(20);
    enqueue(30);
    printf("\nDisplaying the queue:\n");
    display();
    printf("\nDeleting an element from the queue:\n");
    dequeue();
    printf("\nDisplaying the queue after deletion:\n");
    display();
    printf("\nInserting another element:\n");
    enqueue(40);
    printf("\nDisplaying the final queue:\n");
    display();

    return 0;
}









//Q3 (Using LINKED LIST)

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node*next;
};

struct Node*front;
struct Node*rear;

void enqueue(int x){
    struct Node*newNode;
    newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        printf("Memory allocation failed.\n");
        return;
    }
    newNode->data=x;
    newNode->next=NULL;
    if(rear==NULL)
        front=rear=newNode;
    else{
        rear->next=newNode;
        rear=newNode;
    }

    printf("The element %d has been inserted into the queue.\n",x);
}

void dequeue(){
    struct Node*temp;
    if(front==NULL){
        printf("Queue Underflow! The queue is empty.\n");
        return;
    }
    temp=front;
    printf("The deleted element is %d.\n",temp->data);
    front=front->next;
    if(front==NULL)
        rear=NULL;
    free(temp);
}

void display(){
    struct Node*temp;
    if(front==NULL){
        printf("The queue is empty.\n");
        return;
    }
    temp=front;
    printf("The elements in the queue are: ");
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp=temp->next;
    }
    printf("\n");
}

int main(){
    front=NULL;
    rear=NULL;
    printf("Inserting elements into the queue:\n");
    enqueue(10);
    enqueue(20);
    enqueue(30);
    printf("\nDisplaying the queue:\n");
    display();
    printf("\nDeleting an element from the queue:\n");
    dequeue();
    printf("\nDisplaying the queue after deletion:\n");
    display();
    printf("\nInserting another element:\n");
    enqueue(40);
    printf("\nDisplaying the final queue:\n");
    display();
    while(front!=NULL){
        struct Node*temp;
        temp=front;
        front=front->next;
        free(temp);
    }
    rear=NULL;
    return 0;
}