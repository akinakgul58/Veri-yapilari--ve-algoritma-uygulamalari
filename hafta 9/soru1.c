#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int key) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (n == NULL) {
        fprintf(stderr, "Bellek ayirma hatasi!\n");
        exit(1);
    }
    n->key = key;
    n->left = NULL;
    n->right = NULL;
    return n;
}


Node *insertBST(Node *root, int key) {
    if (root == NULL)
        return createNode(key);
    if (key < root->key)
        root->left = insertBST(root->left, key);
    else if (key > root->key)
        root->right = insertBST(root->right, key);
    return root; /* ayni anahtar eklenmez */
}

int height(Node *n) {
    if (n == NULL)
        return 0;
    int hl = height(n->left);
    int hr = height(n->right);
    return 1 + (hl > hr ? hl : hr);
}


int balanceFactor(Node *n) {
    if (n == NULL)
        return 0;
    return height(n->left) - height(n->right);
}


Node *rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;   
    x->right = T2; 

    return y;      
}

void inorder(Node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void preorder(Node *root) {
    if (root == NULL)
        return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void freeTree(Node *root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main(void) {
    int keys[] = {10, 20, 30};
    int n = sizeof(keys) / sizeof(keys[0]);
    Node *root = NULL;

    for (int i = 0; i < n; i++) {
        root = insertBST(root, keys[i]);
        int bf = balanceFactor(root);
        printf("%d eklendi. BF(kok) = %d\n", keys[i], bf);

       
        if (bf < -1 && balanceFactor(root->right) <= 0) {
            printf("RR dengesizligi: Sol rotasyon!\n");
            root = rotateLeft(root);
        }
    }

    printf("\nKok: %d\n", root->key);

    printf("Inorder: ");
    inorder(root);
    printf("\n");

    printf("Preorder: ");
    preorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}