//Q1

#include<stdio.h>

void heapify(int arr[],int n,int i)
{
    int largest=i;
    int left=2*i+1;
    int right=2*i+2;
    int temp;

    if(left<n && arr[left]>arr[largest])
        largest=left;

    if(right<n && arr[right]>arr[largest])
        largest=right;

    if(largest!=i)
    {
        temp=arr[i];
        arr[i]=arr[largest];
        arr[largest]=temp;
        heapify(arr,n,largest);
    }
}

void heapSort(int arr[],int n)
{
    int i,temp;

    for(i=n/2-1;i>=0;i--)
        heapify(arr,n,i);

    for(i=n-1;i>0;i--)
    {
        temp=arr[0];
        arr[0]=arr[i];
        arr[i]=temp;
        heapify(arr,i,0);
    }
}

int main()
{
    int n,i;

    printf("Enter number of elements: ");
    scanf("%d",&n);

    int arr[n];

    printf("Enter %d integers: ",n);
    for(i=0;i<n;i++)
        scanf("%d",&arr[i]);

    heapSort(arr,n);

    printf("Sorted array: ");
    for(i=0;i<n;i++)
        printf("%d ",arr[i]);

    return 0;
}





















//Q2

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;
    bool lthread; // true if left pointer is an inorder predecessor thread
    bool rthread; // true if right pointer is an inorder successor thread
}Node;

struct Node *createNode(int data){
    struct Node *newNode=(struct Node *)malloc(sizeof(struct Node));
    newNode->data=data;
    newNode->data=data;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->lthread=0;
    newNode->rthread=0;
    return newNode;
}

struct Node* insert(struct Node* root,int data)
{
    if(root==NULL)
        return createNode(data);
    if(data<root->data)
        root->left=insert(root->left,data);
    else if(data>root->data)
        root->right=insert(root->right,data);
    return root;
}


void convert(struct Node* root){
    struct Node *curr=root,*prev=NULL,*temp;

    while(curr!=NULL){
        if(curr->left==NULL){
            if(prev!=NULL && prev->right==NULL){
                prev->right=curr;
                prev->rthread=1;
            }

            curr->lthread=1;
            curr->left=prev;

            prev=curr;
            curr=curr->right;
        }
        else{
            temp=curr->left;

            while(temp->right!=NULL && temp->right!=curr)
                temp=temp->right;

            if(temp->right==NULL){
                temp->right=curr;
                curr=curr->left;
            }
            else{
                temp->right=NULL;

                if(prev!=NULL && prev->right==NULL){
                    prev->right=curr;
                    prev->rthread=1;
                }

                prev=curr;
                curr=curr->right;
            }
        }
    }
    if(prev!=NULL && prev->right==NULL)
        prev->rthread=1;
}

void inOrder(struct Node *root){
    struct Node* curr=root;
    if(root==NULL)
        return;
    
    while(curr->lthread==0 && curr->left!=NULL)
        curr=curr->left;
    while(curr!=NULL){
        printf("%d ",curr->data);
        if(curr->rthread==1)
            curr=curr->right;
        else{
            curr=curr->right;
            while(curr!=NULL && curr->lthread==0 && curr->left!=NULL)
                curr=curr->left;
        }
    }
}

int main(){
    struct Node* root=NULL;
    int n,i,x;

    printf("Enter number of nodes: ");
    scanf("%d",&n);

    printf("Enter node values: ");
    for(i=0;i<n;i++){
        scanf("%d",&x);
        root=insert(root,x);
    }

    convert(root);

    printf("Inorder Traversal: ");
    inOrder(root);

    return 0;
}













//Q3

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node*left;
    struct Node*right;
};

struct Node*root;

struct Node*createNode(int x){
    struct Node*newNode;
    newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        printf("Memory allocation failed! The node could not be created.\n");
        return NULL;
    }
    newNode->data=x;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

void buildTree(int*arr,int n){
    struct Node**queue;
    struct Node*temp;
    int front,rear,i;
    if(n<=0||arr[0]==-1){
        printf("The level-order representation is empty. No tree has been built.\n");
        return;
    }
    queue=(struct Node**)malloc(n*sizeof(struct Node*));
    if(queue==NULL){
        printf("Memory allocation failed! The tree could not be built.\n");
        return;
    }
    root=createNode(arr[0]);
    if(root==NULL){
        free(queue);
        return;
    }
    front=0;
    rear=0;
    queue[rear]=root;
    rear++;
    i=1;
    while(front<rear&&i<n){
        temp=queue[front];
        front++;
        if(arr[i]!=-1){
            temp->left=createNode(arr[i]);
            if(temp->left!=NULL){
                queue[rear]=temp->left;
                rear++;
            }
        }
        i++;
        if(i<n&&arr[i]!=-1){
            temp->right=createNode(arr[i]);
            if(temp->right!=NULL){
                queue[rear]=temp->right;
                rear++;
            }
        }
        i++;
    }
    free(queue);
    printf("The tree has been built from the level-order representation.\n");
}

int countNodes(struct Node*temp){
    if(temp==NULL)
        return 0;
    return 1+countNodes(temp->left)+countNodes(temp->right);
}

void preorder(struct Node*temp){
    if(temp==NULL)
        return;
    printf("%d ",temp->data);
    preorder(temp->left);
    preorder(temp->right);
}

void inorder(struct Node*temp){
    if(temp==NULL)
        return;
    inorder(temp->left);
    printf("%d ",temp->data);
    inorder(temp->right);
}

void display(){
    if(root==NULL){
        printf("The tree is empty.\n");
        return;
    }
    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
}

void kDistance(int s,int k){
    struct Node**nodes;
    struct Node*temp;
    int*par;
    int*lc;
    int*rc;
    int*dist;
    int*queue;
    int n,head,tail,i,t,u,count;
    if(root==NULL){
        printf("The tree is empty.\n");
        return;
    }
    if(k<0){
        printf("Invalid K! The distance cannot be negative.\n");
        return;
    }
    n=countNodes(root);
    nodes=(struct Node**)malloc(n*sizeof(struct Node*));
    par=(int*)malloc(n*sizeof(int));
    lc=(int*)malloc(n*sizeof(int));
    rc=(int*)malloc(n*sizeof(int));
    dist=(int*)malloc(n*sizeof(int));
    queue=(int*)malloc(n*sizeof(int));
    if(nodes==NULL||par==NULL||lc==NULL||rc==NULL||dist==NULL||queue==NULL){
        printf("Memory allocation failed! The rooms could not be searched.\n");
        free(nodes);
        free(par);
        free(lc);
        free(rc);
        free(dist);
        free(queue);
        return;
    }
    nodes[0]=root;
    par[0]=-1;
    tail=1;
    for(head=0;head<n;head++){
        temp=nodes[head];
        lc[head]=-1;
        rc[head]=-1;
        if(temp->left!=NULL){
            nodes[tail]=temp->left;
            par[tail]=head;
            lc[head]=tail;
            tail++;
        }
        if(temp->right!=NULL){
            nodes[tail]=temp->right;
            par[tail]=head;
            rc[head]=tail;
            tail++;
        }
    }
    t=-1;
    for(i=0;i<n;i++){
        dist[i]=-1;
        if(nodes[i]->data==s)
            t=i;
    }
    if(t==-1){
        printf("The room %d does not exist in the tree.\n",s);
        free(nodes);
        free(par);
        free(lc);
        free(rc);
        free(dist);
        free(queue);
        return;
    }
    head=0;
    tail=0;
    queue[tail]=t;
    tail++;
    dist[t]=0;
    while(head<tail){
        u=queue[head];
        head++;
        if(lc[u]!=-1&&dist[lc[u]]==-1){
            dist[lc[u]]=dist[u]+1;
            queue[tail]=lc[u];
            tail++;
        }
        if(rc[u]!=-1&&dist[rc[u]]==-1){
            dist[rc[u]]=dist[u]+1;
            queue[tail]=rc[u];
            tail++;
        }
        if(par[u]!=-1&&dist[par[u]]==-1){
            dist[par[u]]=dist[u]+1;
            queue[tail]=par[u];
            tail++;
        }
    }
    count=0;
    for(i=0;i<tail;i++)
        if(dist[queue[i]]==k)
            count++;
    if(count==0)
        printf("No room exists at distance %d from the room %d.\n",k,s);
    else{
        printf("The rooms at distance %d from the room %d are: ",k,s);
        for(i=0;i<tail;i++)
            if(dist[queue[i]]==k)
                printf("%d ",nodes[queue[i]]->data);
        printf("\n");
    }
    free(nodes);
    free(par);
    free(lc);
    free(rc);
    free(dist);
    free(queue);
}

void freeTree(struct Node*temp){
    if(temp==NULL)
        return;
    freeTree(temp->left);
    freeTree(temp->right);
    free(temp);
}

void deleteTree(){
    if(root==NULL){
        printf("Tree Underflow! The tree is empty.\n");
        return;
    }
    freeTree(root);
    root=NULL;
    printf("The entire tree has been deleted.\n");
}

int main(){
    int arr[]={3,5,1,6,2,0,8,-1,-1,7,4};
    root=NULL;
    printf("\nBuilding the tree from the level-order representation:\n");
    buildTree(arr,11);
    printf("\nDisplaying the tree:\n");
    display();
    printf("\nFinding the rooms at distance 2 from the room 5:\n");
    kDistance(5,2);
    printf("\nFinding the rooms at distance 0 from the room 5:\n");
    kDistance(5,0);
    printf("\nFinding the rooms at distance 3 from the room 5:\n");
    kDistance(5,3);
    printf("\nFinding the rooms at distance 5 from the room 5:\n");
    kDistance(5,5);
    printf("\nFinding the rooms at distance 1 from the missing room 99:\n");
    kDistance(99,1);
    printf("\nDeleting the tree:\n");
    deleteTree();
    printf("\nFinding the rooms at distance 1 from the room 5 in the empty tree:\n");
    kDistance(5,1);
    root=NULL;
    return 0;
}









//Q4

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node*left;
    struct Node*right;
};

struct Node*root;
struct Node*result;
int*sorted;
int total;
int idx;
int count;

struct Node*createNode(int x){
    struct Node*newNode;
    newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        printf("Memory allocation failed! The node could not be created.\n");
        return NULL;
    }
    newNode->data=x;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

void buildTree(int*arr,int n){
    struct Node**queue;
    struct Node*temp;
    int front,rear,i;
    if(n<=0||arr[0]==-1){
        printf("The level-order representation is empty. No tree has been built.\n");
        return;
    }
    queue=(struct Node**)malloc(n*sizeof(struct Node*));
    if(queue==NULL){
        printf("Memory allocation failed! The tree could not be built.\n");
        return;
    }
    root=createNode(arr[0]);
    if(root==NULL){
        free(queue);
        return;
    }
    front=0;
    rear=0;
    queue[rear]=root;
    rear++;
    i=1;
    while(front<rear&&i<n){
        temp=queue[front];
        front++;
        if(arr[i]!=-1){
            temp->left=createNode(arr[i]);
            if(temp->left!=NULL){
                queue[rear]=temp->left;
                rear++;
            }
        }
        i++;
        if(i<n&&arr[i]!=-1){
            temp->right=createNode(arr[i]);
            if(temp->right!=NULL){
                queue[rear]=temp->right;
                rear++;
            }
        }
        i++;
    }
    free(queue);
    printf("The tree has been built from the level-order representation.\n");
}

void insert(int x){
    struct Node*newNode;
    struct Node*temp;
    struct Node*parent;
    newNode=createNode(x);
    if(newNode==NULL)
        return;
    if(root==NULL){
        root=newNode;
        printf("The element %d has been inserted into the tree as the root.\n",x);
        return;
    }
    temp=root;
    parent=NULL;
    while(temp!=NULL){
        parent=temp;
        if(x<temp->data)
            temp=temp->left;
        else if(x>temp->data)
            temp=temp->right;
        else{
            printf("The element %d already exists in the tree.\n",x);
            free(newNode);
            return;
        }
    }
    if(x<parent->data)
        parent->left=newNode;
    else
        parent->right=newNode;
    printf("The element %d has been inserted into the tree.\n",x);
}

int countNodes(struct Node*temp){
    if(temp==NULL)
        return 0;
    return 1+countNodes(temp->left)+countNodes(temp->right);
}

void preorder(struct Node*temp){
    if(temp==NULL)
        return;
    printf("%d ",temp->data);
    preorder(temp->left);
    preorder(temp->right);
}

void inorder(struct Node*temp){
    if(temp==NULL)
        return;
    inorder(temp->left);
    printf("%d ",temp->data);
    inorder(temp->right);
}

void display(){
    if(root==NULL){
        printf("The tree is empty.\n");
        return;
    }
    printf("Preorder traversal: ");
    preorder(root);
    printf("\n");
    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
}

void inorderK(struct Node*temp,int k){
    if(temp==NULL||result!=NULL)
        return;
    inorderK(temp->left,k);
    if(result!=NULL)
        return;
    count++;
    if(count==k){
        result=temp;
        return;
    }
    inorderK(temp->right,k);
}

struct Node*kthInorder(int k){
    if(k<=0){
        printf("Invalid k! The value of k must be at least 1.\n");
        return NULL;
    }
    count=0;
    result=NULL;
    inorderK(root,k);
    if(result==NULL){
        printf("Invalid k! The value %d is greater than the number of products, which is %d.\n",k,count);
        return NULL;
    }
    printf("The product ID with rank %d is %d.\n",k,result->data);
    return result;
}

void fillArray(struct Node*temp){
    if(temp==NULL)
        return;
    fillArray(temp->left);
    sorted[idx]=temp->data;
    idx++;
    fillArray(temp->right);
}

void buildArray(){
    free(sorted);
    sorted=NULL;
    total=0;
    if(root==NULL){
        printf("The tree is empty. The sorted array could not be prepared.\n");
        return;
    }
    total=countNodes(root);
    sorted=(int*)malloc(total*sizeof(int));
    if(sorted==NULL){
        printf("Memory allocation failed! The sorted array could not be prepared.\n");
        total=0;
        return;
    }
    idx=0;
    fillArray(root);
    printf("The sorted array of %d product IDs has been prepared with one inorder traversal.\n",total);
}

int*kthFast(int k){
    if(sorted==NULL){
        printf("The sorted array has not been prepared yet.\n");
        return NULL;
    }
    if(k<=0){
        printf("Invalid k! The value of k must be at least 1.\n");
        return NULL;
    }
    if(k>total){
        printf("Invalid k! The value %d is greater than the number of products, which is %d.\n",k,total);
        return NULL;
    }
    printf("The product ID with rank %d is %d.\n",k,sorted[k-1]);
    return &sorted[k-1];
}

void freeTree(struct Node*temp){
    if(temp==NULL)
        return;
    freeTree(temp->left);
    freeTree(temp->right);
    free(temp);
}

int main(){
    int arr[]={8,3,10,1,6,-1,14,-1,-1,4,7,13};
    root=NULL;
    result=NULL;
    sorted=NULL;
    total=0;
    idx=0;
    count=0;
    printf("\nBuilding the BST from the level-order representation:\n");
    buildTree(arr,12);
    printf("\nDisplaying the BST:\n");
    display();
    printf("\nFinding the rank 3 product ID using inorder traversal:\n");
    kthInorder(3);
    printf("\nFinding the rank 0 product ID using inorder traversal:\n");
    kthInorder(0);
    printf("\nFinding the rank 10 product ID using inorder traversal:\n");
    kthInorder(10);
    printf("\nPreparing the sorted array with one inorder traversal:\n");
    buildArray();
    printf("\nAnswering the queries 1, 3, 5 and 8:\n");
    kthFast(1);
    kthFast(3);
    kthFast(5);
    kthFast(8);
    printf("\nAnswering the invalid queries 0 and 10:\n");
    kthFast(0);
    kthFast(10);
    printf("\nInserting a new product ID into the BST:\n");
    insert(12);
    printf("\nDisplaying the BST:\n");
    display();
    printf("\nPreparing the sorted array again:\n");
    buildArray();
    printf("\nAnswering the queries 8 and 9:\n");
    kthFast(8);
    kthFast(9);
    freeTree(root);
    free(sorted);
    root=NULL;
    result=NULL;
    sorted=NULL;
    total=0;
    return 0;
}












//Q5

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node*left;
    struct Node*right;
    int lthread;
    int rthread;
};

struct Node*root;
struct Node*prev;
int converted;

struct Node*createNode(int x){
    struct Node*newNode;
    newNode=(struct Node*)malloc(sizeof(struct Node));
    if(newNode==NULL){
        printf("Memory allocation failed! The node could not be created.\n");
        return NULL;
    }
    newNode->data=x;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->lthread=0;
    newNode->rthread=0;
    return newNode;
}

void insert(int x){
    struct Node*newNode;
    struct Node*temp;
    struct Node*parent;
    if(converted==1){
        printf("Insertion failed! The tree has already been converted to a threaded tree.\n");
        return;
    }

    newNode=createNode(x);
    if(newNode==NULL)
        return;
    if(root==NULL){
        root=newNode;
        printf("The score %d has been inserted into the tree as the root.\n",x);
        return;
    }
    temp=root;
    parent=NULL;
    while(temp!=NULL){
        parent=temp;
        if(x<temp->data)
            temp=temp->left;
        else if(x>temp->data)
            temp=temp->right;
        else{
            printf("The score %d already exists in the tree.\n",x);
            free(newNode);
            return;
        }
    }
    if(x<parent->data)
        parent->left=newNode;
    else
        parent->right=newNode;
    printf("The score %d has been inserted into the tree.\n",x);
}

void build(int*arr,int n){
    int i;
    if(n<=0){
        printf("The sequence of scores is empty. No tree has been built.\n");
        return;
    }
    for(i=0;i<n;i++)
        insert(arr[i]);
}

void convertNode(struct Node*temp){
    if(temp==NULL)
        return;
    convertNode(temp->left);
    if(temp->left==NULL){
        temp->lthread=1;
        temp->left=prev;
    }
    if(prev!=NULL&&prev->right==NULL){
        prev->rthread=1;
        prev->right=temp;
    }
    prev=temp;
    convertNode(temp->right);
}

void convert(){
    if(root==NULL){
        printf("The tree is empty. There is nothing to convert.\n");
        return;
    }
    if(converted==1){
        printf("The tree has already been converted.\n");
        return;
    }
    prev=NULL;
    convertNode(root);
    if(prev!=NULL)
        prev->rthread=1;
    converted=1;
    printf("The BST has been converted into a double-threaded binary tree in place.\n");
}

struct Node*leftmost(struct Node*temp){
    while(temp->lthread==0)
        temp=temp->left;
    return temp;
}

struct Node*successor(struct Node*temp){
    struct Node*s;
    s=temp->right;
    if(temp->rthread==1)
        return s;
    while(s->lthread==0)
        s=s->left;
    return s;
}

struct Node*predecessor(struct Node*temp){
    struct Node*p;

    p=temp->left;
    if(temp->lthread==1)
        return p;
    while(p->rthread==0)
        p=p->right;
    return p;
}

struct Node*findNode(int x){
    struct Node*temp;
    temp=root;
    while(temp!=NULL){
        if(x==temp->data)
            return temp;
        else if(x<temp->data){
            if(temp->lthread==1)
                return NULL;
            temp=temp->left;
        }
        else{
            if(temp->rthread==1)
                return NULL;
            temp=temp->right;
        }
    }
    return NULL;
}

int ready(){
    if(root==NULL){
        printf("The tree is empty.\n");
        return 0;
    }
    if(converted==0){
        printf("The tree has not been converted yet. Please convert it first.\n");
        return 0;
    }
    return 1;
}

void inorder(struct Node*temp){
    if(temp==NULL)
        return;
    inorder(temp->left);
    printf("%d ",temp->data);
    inorder(temp->right);
}

void display(){
    struct Node*temp;
    if(root==NULL){
        printf("The tree is empty.\n");
        return;
    }
    printf("Inorder traversal: ");
    if(converted==0)
        inorder(root);
    else{
        temp=leftmost(root);
        while(temp!=NULL){
            printf("%d ",temp->data);
            temp=successor(temp);
        }
    }
    printf("\n");
}

void nextScore(int x){
    struct Node*temp;
    struct Node*s;
    if(ready()==0)
        return;
    temp=findNode(x);
    if(temp==NULL){
        printf("The score %d does not exist in the tree.\n",x);
        return;
    }
    s=successor(temp);
    if(s==NULL)
        printf("The inorder successor of %d does not exist. The result is NULL.\n",x);
    else
        printf("The inorder successor of %d is %d.\n",x,s->data);
}

void prevScore(int x){
    struct Node*temp;
    struct Node*p;
    if(ready()==0)
        return;
    temp=findNode(x);
    if(temp==NULL){
        printf("The score %d does not exist in the tree.\n",x);
        return;
    }
    p=predecessor(temp);
    if(p==NULL)
        printf("The inorder predecessor of %d does not exist. The result is NULL.\n",x);
    else
        printf("The inorder predecessor of %d is %d.\n",x,p->data);
}

void rangeScores(int l,int r){
    struct Node*temp;
    struct Node*start;
    if(ready()==0)
        return;
    if(l>r){
        printf("Invalid range! The value of L must not be greater than R.\n");
        return;
    }
    start=NULL;
    temp=root;
    while(temp!=NULL){
        if(temp->data>=l){
            start=temp;
            if(temp->lthread==1)
                break;
            temp=temp->left;
        }
        else{
            if(temp->rthread==1)
                break;
            temp=temp->right;
        }
    }
    if(start==NULL||start->data>r){
        printf("No scores exist in the range [%d,%d].\n",l,r);
        return;
    }
    printf("The scores in the range [%d,%d] are: ",l,r);
    temp=start;
    while(temp!=NULL&&temp->data<=r){
        printf("%d ",temp->data);
        temp=successor(temp);
    }
    printf("\n");
}

void kthScore(int k){
    struct Node*temp;
    int count;
    if(ready()==0)
        return;
    if(k<=0){
        printf("Invalid k! The value of k must be at least 1. The result is NULL.\n");
        return;
    }
    temp=leftmost(root);
    count=1;
    while(temp!=NULL&&count<k){
        temp=successor(temp);
        count++;
    }
    if(temp==NULL)
        printf("The rank %d does not exist in the tree. The result is NULL.\n",k);
    else
        printf("The score with rank %d is %d.\n",k,temp->data);
}

void freeTree(struct Node*temp){
    if(temp==NULL)
        return;
    freeTree(temp->left);
    freeTree(temp->right);
    free(temp);
}

void freeAll(){
    struct Node*temp;
    struct Node*next;
    if(root==NULL)
        return;
    if(converted==0){
        freeTree(root);
        return;
    }
    temp=leftmost(root);
    while(temp!=NULL){
        next=successor(temp);
        free(temp);
        temp=next;
    }
}

int main(){
    int scores[]={40,20,60,10,30,50,70};
    root=NULL;
    prev=NULL;
    converted=0;
    printf("\nBuilding the BST:\n");
    build(scores,7);
    printf("\nDisplaying the tree:\n");
    display();
    printf("\nFinding the successor of 30 before conversion:\n");
    nextScore(30);
    printf("\nConverting the BST into a double-threaded binary tree:\n");
    convert();
    printf("\nDisplaying the tree:\n");
    display();
    printf("\nFinding the successor of 30:\n");
    nextScore(30);
    printf("\nFinding the predecessor of 30:\n");
    prevScore(30);
    printf("\nFinding the successor of the maximum score 70:\n");
    nextScore(70);
    printf("\nFinding the predecessor of the minimum score 10:\n");
    prevScore(10);
    printf("\nFinding the successor of the missing score 35:\n");
    nextScore(35);
    printf("\nReporting the scores in the range 25 to 60:\n");
    rangeScores(25,60);
    printf("\nReporting the scores in the range 71 to 100:\n");
    rangeScores(71,100);
    printf("\nFinding the 5th smallest score:\n");
    kthScore(5);
    printf("\nFinding the 8th smallest score:\n");
    kthScore(8);
    freeAll();
    root=NULL;
    prev=NULL;
    converted=0;
    return 0;
}
