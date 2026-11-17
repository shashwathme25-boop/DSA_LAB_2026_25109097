//Q1

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

struct Node*insertRoot(int x){
    struct Node*newNode;
    newNode=createNode(x);
    if(newNode==NULL)
        return NULL;
    printf("The element %d has been inserted as the root.\n",x);
    return newNode;
}

void insertChild(struct Node*parent,int x,char side){
    struct Node*newNode;
    if(parent==NULL){
        printf("Insertion failed! The parent node does not exist.\n");
        return;
    }
    if(side=='L'&&parent->left!=NULL){
        printf("Insertion failed! The left child of %d already exists.\n",parent->data);
        return;
    }
    if(side=='R'&&parent->right!=NULL){
        printf("Insertion failed! The right child of %d already exists.\n",parent->data);
        return;
    }

    newNode=createNode(x);
    if(newNode==NULL)
        return;
    if(side=='L'){
        parent->left=newNode;
        printf("The element %d has been inserted as the left child of %d.\n",x,parent->data);
    }
    else{
        parent->right=newNode;
        printf("The element %d has been inserted as the right child of %d.\n",x,parent->data);
    }
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

void topView(){
    struct Node**queue;
    struct Node*temp;
    int*hd;
    int*seen;
    int*val;
    int n,size,front,rear,h,low,high,i;

    if(root==NULL){
        printf("The tree is empty! There is no top view.\n");
        return;
    }

    n=countNodes(root);
    size=2*n+1;
    queue=(struct Node**)malloc(n*sizeof(struct Node*));
    hd=(int*)malloc(n*sizeof(int));
    seen=(int*)calloc(size,sizeof(int));
    val=(int*)malloc(size*sizeof(int));
    if(queue==NULL||hd==NULL||seen==NULL||val==NULL){
        printf("Memory allocation failed! The top view could not be computed.\n");
        free(queue);
        free(hd);
        free(seen);
        free(val);
        return;
    }
    front=0;
    rear=0;
    queue[rear]=root;
    hd[rear]=0;
    rear++;
    low=0;
    high=0;
    while(front<rear){
        temp=queue[front];
        h=hd[front];
        front++;
        if(seen[h+n]==0){
            seen[h+n]=1;
            val[h+n]=temp->data;
            if(h<low)
                low=h;
            if(h>high)
                high=h;
        }
        if(temp->left!=NULL){
            queue[rear]=temp->left;
            hd[rear]=h-1;
            rear++;
        }
        if(temp->right!=NULL){
            queue[rear]=temp->right;
            hd[rear]=h+1;
            rear++;
        }
    }

    printf("The top view of the tree is: ");
    for(i=low;i<=high;i++)
        printf("%d ",val[i+n]);
    printf("\n");

    free(queue);
    free(hd);
    free(seen);
    free(val);
}

void freeTree(struct Node*temp){
    if(temp==NULL)
        return;

    freeTree(temp->left);
    freeTree(temp->right);
    free(temp);
}

int main(){
    root=NULL;

    printf("\nDisplaying the empty tree:\n");
    display();

    printf("\nPrinting the top view of the empty tree:\n");
    topView();

    printf("\nInserting the nodes into the tree:\n");
    root=insertRoot(1);
    insertChild(root,2,'L');
    insertChild(root,3,'R');
    insertChild(root->left,4,'R');
    insertChild(root->left->right,5,'R');
    insertChild(root->left->right->right,6,'R');

    printf("\nDisplaying the tree:\n");
    display();

    printf("\nPrinting the top view of the tree:\n");
    topView();

    printf("\nInserting a new node into the tree:\n");
    insertChild(root->left,7,'L');

    printf("\nDisplaying the tree:\n");
    display();

    printf("\nPrinting the top view of the tree:\n");
    topView();

    freeTree(root);
    root=NULL;

    return 0;
}











//Q2

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node*left;
    struct Node*right;
};

struct Node*root;
struct Node*prev;
struct Node*first;
struct Node*second;

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

struct Node*insertRoot(int x){
    struct Node*newNode;

    newNode=createNode(x);
    if(newNode==NULL)
        return NULL;

    printf("The element %d has been inserted as the root.\n",x);
    return newNode;
}

void insertChild(struct Node*parent,int x,char side){
    struct Node*newNode;

    if(parent==NULL){
        printf("Insertion failed! The parent node does not exist.\n");
        return;
    }
    if(side=='L'&&parent->left!=NULL){
        printf("Insertion failed! The left child of %d already exists.\n",parent->data);
        return;
    }
    if(side=='R'&&parent->right!=NULL){
        printf("Insertion failed! The right child of %d already exists.\n",parent->data);
        return;
    }

    newNode=createNode(x);
    if(newNode==NULL)
        return;

    if(side=='L'){
        parent->left=newNode;
        printf("The element %d has been inserted as the left child of %d.\n",x,parent->data);
    }
    else{
        parent->right=newNode;
        printf("The element %d has been inserted as the right child of %d.\n",x,parent->data);
    }
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

void findSwapped(struct Node*temp){
    if(temp==NULL)
        return;

    findSwapped(temp->left);

    if(prev!=NULL&&prev->data>temp->data){
        if(first==NULL)
            first=prev;
        second=temp;
    }
    prev=temp;

    findSwapped(temp->right);
}

void recoverTree(){
    int t;

    if(root==NULL){
        printf("The tree is empty. There is nothing to recover.\n");
        return;
    }

    prev=NULL;
    first=NULL;
    second=NULL;
    findSwapped(root);

    if(first==NULL||second==NULL){
        printf("The tree is already a valid BST. No swapped values were found.\n");
        return;
    }
    t=first->data;
    first->data=second->data;
    second->data=t;
    printf("The swapped values %d and %d have been restored to their original nodes.\n",second->data,first->data);
}

void freeTree(struct Node*temp){
    if(temp==NULL)
        return;

    freeTree(temp->left);
    freeTree(temp->right);
    free(temp);
}

int main(){
    root=NULL;
    prev=NULL;
    first=NULL;
    second=NULL;

    printf("\nInserting the nodes into the tree:\n");
    root=insertRoot(6);
    insertChild(root,3,'L');
    insertChild(root,8,'R');
    insertChild(root->left,1,'L');
    insertChild(root->left,7,'R');
    insertChild(root->right,4,'L');
    insertChild(root->right,9,'R');

    printf("\nDisplaying the malfunctioned tree:\n");
    display();

    printf("\nRecovering the BST:\n");
    recoverTree();

    printf("\nDisplaying the recovered tree:\n");
    display();

    printf("\nRecovering the BST again:\n");
    recoverTree();

    freeTree(root);
    root=NULL;
    prev=NULL;
    first=NULL;
    second=NULL;

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

struct SNode{
    struct Node*ptr;
    struct SNode*next;
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

void push(struct SNode**top,struct Node*n){
    struct SNode*newNode;

    newNode=(struct SNode*)malloc(sizeof(struct SNode));
    if(newNode==NULL){
        printf("Memory allocation failed! The stack is full.\n");
        return;
    }

    newNode->ptr=n;
    newNode->next=*top;
    *top=newNode;
}

struct Node*pop(struct SNode**top){
    struct SNode*temp;
    struct Node*n;

    if(*top==NULL)
        return NULL;

    temp=*top;
    n=temp->ptr;
    *top=temp->next;
    free(temp);
    return n;
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

    printf("Inorder traversal: ");
    inorder(root);
    printf("\n");
}

void kClosest(int x,int k){
    struct SNode*ptop;
    struct SNode*stop;
    struct Node*temp;
    int count,usePred;

    if(root==NULL){
        printf("The tree is empty. There are no values to retrieve.\n");
        return;
    }
    if(k<=0){
        printf("Invalid k! The value of k must be positive.\n");
        return;
    }

    ptop=NULL;
    stop=NULL;
    temp=root;
    while(temp!=NULL){
        if(temp->data<x){
            push(&ptop,temp);
            temp=temp->right;
        }
        else{
            push(&stop,temp);
            temp=temp->left;
        }
    }

    printf("The %d closest values to %d are: ",k,x);
    count=0;
    while(count<k&&(ptop!=NULL||stop!=NULL)){
        usePred=0;
        if(stop==NULL)
            usePred=1;
        else if(ptop!=NULL&&x-ptop->ptr->data<=stop->ptr->data-x)
            usePred=1;

        if(usePred==1){
            temp=pop(&ptop);
            printf("%d ",temp->data);
            temp=temp->left;
            while(temp!=NULL){
                push(&ptop,temp);
                temp=temp->right;
            }
        }
        else{
            temp=pop(&stop);
            printf("%d ",temp->data);
            temp=temp->right;
            while(temp!=NULL){
                push(&stop,temp);
                temp=temp->left;
            }
        }
        count++;
    }
    printf("\n");
    if(count<k)
        printf("Only %d values are available in the tree.\n",count);
    while(ptop!=NULL)
        pop(&ptop);
    while(stop!=NULL)
        pop(&stop);
}

void freeTree(struct Node*temp){
    if(temp==NULL)
        return;
    freeTree(temp->left);
    freeTree(temp->right);
    free(temp);
}

int main(){
    root=NULL;

    printf("\nInserting the elements into the BST:\n");
    insert(10);
    insert(5);
    insert(15);
    insert(2);
    insert(7);
    insert(12);
    insert(20);
    insert(6);
    insert(8);

    printf("\nDisplaying the BST:\n");
    display();
    printf("\nFinding the 4 values closest to 9:\n");
    kClosest(9,4);
    printf("\nFinding the 3 values closest to 1 (smaller than the minimum):\n");
    kClosest(1,3);
    printf("\nFinding the 3 values closest to 30 (greater than the maximum):\n");
    kClosest(30,3);
    printf("\nFinding the 12 values closest to 9 (k larger than the tree size):\n");
    kClosest(9,12);
    printf("\nInserting the element 9 into the BST:\n");
    insert(9);
    printf("\nDisplaying the BST:\n");
    display();
    printf("\nFinding the 3 values closest to 9:\n");
    kClosest(9,3);
    freeTree(root);
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
int best;
int found;

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

struct Node*insertRoot(int x){
    struct Node*newNode;

    newNode=createNode(x);
    if(newNode==NULL)
        return NULL;

    printf("The element %d has been inserted as the root.\n",x);
    return newNode;
}

void insertChild(struct Node*parent,int x,char side){
    struct Node*newNode;

    if(parent==NULL){
        printf("Insertion failed! The parent node does not exist.\n");
        return;
    }
    if(side=='L'&&parent->left!=NULL){
        printf("Insertion failed! The left child of %d already exists.\n",parent->data);
        return;
    }
    if(side=='R'&&parent->right!=NULL){
        printf("Insertion failed! The right child of %d already exists.\n",parent->data);
        return;
    }

    newNode=createNode(x);
    if(newNode==NULL)
        return;

    if(side=='L'){
        parent->left=newNode;
        printf("The element %d has been inserted as the left child of %d.\n",x,parent->data);
    }
    else{
        parent->right=newNode;
        printf("The element %d has been inserted as the right child of %d.\n",x,parent->data);
    }
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

int solve(struct Node*temp,int*mn,int*mx,int*sum){
    int lmn,lmx,lsum,rmn,rmx,rsum,lok,rok;

    lok=1;
    rok=1;
    lmn=0;
    lmx=0;
    lsum=0;
    rmn=0;
    rmx=0;
    rsum=0;
    *mn=temp->data;
    *mx=temp->data;
    *sum=temp->data;

    if(temp->left!=NULL){
        lok=solve(temp->left,&lmn,&lmx,&lsum);
        if(lok==1&&lmx>=temp->data)
            lok=0;
    }

    if(temp->right!=NULL){
        rok=solve(temp->right,&rmn,&rmx,&rsum);
        if(rok==1&&rmn<=temp->data)
            rok=0;
    }

    if(lok==0||rok==0)
        return 0;

    if(temp->left!=NULL)
        *mn=lmn;
    if(temp->right!=NULL)
        *mx=rmx;
    *sum=temp->data+lsum+rsum;

    if(found==0||*sum>best){
        best=*sum;
        found=1;
    }
    return 1;
}

void maxBstSum(){
    int mn,mx,sum;

    if(root==NULL){
        printf("The tree is empty. There is no subtree to evaluate.\n");
        return;
    }

    best=0;
    found=0;
    solve(root,&mn,&mx,&sum);
    printf("The maximum BST subtree sum is %d.\n",best);
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
    root=NULL;
    best=0;
    found=0;

    printf("\nInserting the nodes into the first tree:\n");
    root=insertRoot(5);
    insertChild(root,4,'L');
    insertChild(root,8,'R');
    insertChild(root->left,3,'L');
    insertChild(root->left,6,'R');
    insertChild(root->right,7,'L');
    insertChild(root->right,9,'R');

    printf("\nDisplaying the first tree:\n");
    display();
    printf("\nFinding the maximum BST subtree sum of the first tree:\n");
    maxBstSum();
    printf("\nDeleting the first tree:\n");
    deleteTree();
    printf("\nFinding the maximum BST subtree sum of the empty tree:\n");
    maxBstSum();
    printf("\nInserting the nodes into the second tree:\n");
    root=insertRoot(-3);
    insertChild(root,-5,'L');
    insertChild(root,-1,'R');
    printf("\nDisplaying the second tree:\n");
    display();
    printf("\nFinding the maximum BST subtree sum of the second tree:\n");
    maxBstSum();
    freeTree(root);
    root=NULL;
    return 0;
}











//Q5

#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node*left;
    struct Node*right;
};

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

struct Node*insertRoot(int x){
    struct Node*newNode;

    newNode=createNode(x);
    if(newNode==NULL)
        return NULL;

    printf("The element %d has been inserted as the root.\n",x);
    return newNode;
}

void insertChild(struct Node*parent,int x,char side){
    struct Node*newNode;

    if(parent==NULL){
        printf("Insertion failed! The parent node does not exist.\n");
        return;
    }
    if(side=='L'&&parent->left!=NULL){
        printf("Insertion failed! The left child of %d already exists.\n",parent->data);
        return;
    }
    if(side=='R'&&parent->right!=NULL){
        printf("Insertion failed! The right child of %d already exists.\n",parent->data);
        return;
    }

    newNode=createNode(x);
    if(newNode==NULL)
        return;

    if(side=='L'){
        parent->left=newNode;
        printf("The element %d has been inserted as the left child of %d.\n",x,parent->data);
    }
    else{
        parent->right=newNode;
        printf("The element %d has been inserted as the right child of %d.\n",x,parent->data);
    }
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

void display(struct Node*temp){
    if(temp==NULL){
        printf("The tree is empty.\n");
        return;
    }

    printf("Preorder traversal: ");
    preorder(temp);
    printf("\n");
    printf("Inorder traversal: ");
    inorder(temp);
    printf("\n");
}

void writeTree(struct Node*temp,char*buf,int*pos){
    if(temp==NULL){
        buf[*pos]='#';
        (*pos)++;
        buf[*pos]=',';
        (*pos)++;
        return;
    }

    *pos+=sprintf(buf+*pos,"%d,",temp->data);
    writeTree(temp->left,buf,pos);
    writeTree(temp->right,buf,pos);
}

char*serialize(struct Node*root){
    char*buf;
    int n,size,pos;

    n=countNodes(root);
    size=n*12+(n+1)*2+1;
    buf=(char*)malloc(size);
    if(buf==NULL){
        printf("Memory allocation failed! The tree could not be serialized.\n");
        return NULL;
    }

    pos=0;
    writeTree(root,buf,&pos);
    buf[pos-1]='\0';
    printf("The tree has been serialized as: %s\n",buf);
    return buf;
}

struct Node*readTree(char**p){
    struct Node*newNode;
    int x,sign;

    if(**p=='\0')
        return NULL;

    if(**p=='#'){
        (*p)++;
        if(**p==',')
            (*p)++;
        return NULL;
    }

    sign=1;
    if(**p=='-'){
        sign=-1;
        (*p)++;
    }

    x=0;
    while(**p>='0'&&**p<='9'){
        x=x*10+(**p-'0');
        (*p)++;
    }
    if(**p==',')
        (*p)++;

    newNode=createNode(sign*x);
    if(newNode==NULL)
        return NULL;

    newNode->left=readTree(p);
    newNode->right=readTree(p);
    return newNode;
}

struct Node*deserialize(char*data){
    struct Node*newRoot;
    char*p;

    if(data==NULL){
        printf("Deserialization failed! The data is empty.\n");
        return NULL;
    }

    p=data;
    newRoot=readTree(&p);
    printf("The tree has been deserialized successfully.\n");
    return newRoot;
}

int sameTree(struct Node*a,struct Node*b){
    if(a==NULL&&b==NULL)
        return 1;
    if(a==NULL||b==NULL)
        return 0;
    if(a->data!=b->data)
        return 0;

    return sameTree(a->left,b->left)&&sameTree(a->right,b->right);
}

void compare(struct Node*a,struct Node*b){
    if(sameTree(a,b)==1)
        printf("The original and the deserialized trees are identical.\n");
    else
        printf("The original and the deserialized trees are different.\n");
}

void freeTree(struct Node*temp){
    if(temp==NULL)
        return;

    freeTree(temp->left);
    freeTree(temp->right);
    free(temp);
}

int main(){
    struct Node*root;
    struct Node*copy;
    char*data;
    root=NULL;
    copy=NULL;
    data=NULL;
    printf("\nSerializing the empty tree:\n");
    data=serialize(root);
    printf("\nDeserializing the empty data:\n");
    copy=deserialize(data);
    free(data);
    printf("\nDisplaying the deserialized tree:\n");
    display(copy);
    printf("\nInserting the nodes into the original tree:\n");
    root=insertRoot(1);
    insertChild(root,2,'L');
    insertChild(root,3,'R');
    insertChild(root->right,4,'L');
    insertChild(root->right,5,'R');
    printf("\nDisplaying the original tree:\n");
    display(root);
    printf("\nSerializing the original tree:\n");
    data=serialize(root);
    printf("\nDeserializing the data:\n");
    copy=deserialize(data);
    free(data);
    printf("\nDisplaying the deserialized tree:\n");
    display(copy);
    printf("\nComparing the two trees:\n");
    compare(root,copy);
    printf("\nInserting a new node into the original tree:\n");
    insertChild(root->left,6,'L');
    printf("\nDisplaying the original tree:\n");
    display(root);
    printf("\nComparing the two trees:\n");
    compare(root,copy);
    printf("\nSerializing the original tree again:\n");
    data=serialize(root);
    printf("\nDeserializing the data again:\n");
    freeTree(copy);
    copy=deserialize(data);
    free(data);
    printf("\nComparing the two trees:\n");
    compare(root,copy);
    freeTree(root);
    freeTree(copy);
    root=NULL;
    copy=NULL;
    data=NULL;
    return 0;
}


