#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *left, *right;
};

struct Node* createTree(){
    int x;
    printf("Enter data (-1 for NULL): ");
    scanf("%d", &x);

    if (x==-1)
        return NULL;

    struct Node* newNode=(struct Node*)malloc(sizeof(struct Node));

    newNode->data=x;

    printf("Left child of %d:\n", x);
    newNode->left=createTree();

    printf("Right child of %d:\n", x);
    newNode->right=createTree();

    return newNode;
}

//Mirror Tree

int isMirror(struct Node* L, struct Node* R){
    if(L==NULL && R==NULL)
        return 1;

    if(L==NULL || R==NULL)
        return 0;

    if(L->data != R->data)
        return 0;

    return isMirror(L->left,R->right) && isMirror(L->right,R->left);
}

int isSymmetric(struct Node* root){
    if(root==NULL)
        return 1;
    
    return isMirror(root->left,root->right);
}

// Minimum Depth

int minDepth(struct Node* root){
    if(root==NULL)
        return 0;

    if(root->left==NULL && root->right==NULL)
        return 1;
    
    if(root->left==NULL)
        return 1+minDepth(root->right);

    if(root->right==NULL)
        return 1+minDepth(root->left);

    int L=minDepth(root->left);
    int R=minDepth(root->right);

    return 1+(L<R?L:R);
}

int main(){
    printf("Create the binary tree:\n");
    struct Node* root=createTree();

    if (isSymmetric(root))
        printf("Tree is symmetric.\n");
    else
        printf("Tree is not symmetric.\n");

    printf("The minimum depth of given tree is: %d",minDepth(root));

    return 0;
}

// 
// 
// 
// 
// 
// 
// 

//kth smallest largest in bst

struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* createNode(int data) {
    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

void inorder(struct Node* root, int arr[], int *i) {
    if (root == NULL)
        return;

    inorder(root->left, arr, i);
    arr[(*i)++] = root->data;
    inorder(root->right, arr, i);
}

void kthSmallestLargest(struct Node* root, int k, int n) {
    int arr[1000];
    int i = 0;

    if (k < 1 || k > n) {
        printf("Invalid value of k\n");
        return;
    }

    inorder(root, arr, &i);

    printf("Kth smallest = %d\n", arr[k - 1]);
    printf("Kth largest = %d\n", arr[n - k]);
}

int main(){
    struct Node* root=NULL;
    int n, data, k;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    if (n < 1 || n > 1000){
        printf("Number of nodes must be between 1 and 1000\n");
        return 0;
    }

    printf("Enter node values:\n");
    for (int i=0;i<n;i++){
        scanf("%d", &data);
        root = insert(root, data);
    }

    printf("Inorder traversal: ");
    int arr[1000], i=0;
    inorder(root, arr, &i);

    for (int j=0;j<i;j++)
        printf("%d ", arr[j]);

    printf("\nEnter k: ");
    scanf("%d", &k);

    kthSmallestLargest(root, k, n);

    return 0;
}

// 
// 
// 
// 
// 
// 
// 
// 
// 

// sort using tree
struct Node {
    int data;
    struct Node *left, *right;
};

struct Node* insert(struct Node* root, int x)
{
    if (root == NULL){
        struct Node* n = malloc(sizeof(struct Node));
        n->data = x;
        n->left = n->right = NULL;
        return n;
    }

    if (x < root->data)
        root->left = insert(root->left, x);
    else
        root->right = insert(root->right, x);

    return root;
}

void inorder2(struct Node* root)
{
    if (root == NULL)
        return;

    inorder2(root->left);
    printf("%d ", root->data);
    inorder2(root->right);
}

void treeSort(int a[], int n){
    struct Node* root = NULL;

    for (int i = 0; i < n; i++)
        root = insert(root, a[i]);

    inorder2(root);
}

int main(){
    int n, a[100];

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);

    printf("Sorted array: ");
    treeSort(a, n);

    return 0;
}