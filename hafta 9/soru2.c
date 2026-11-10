#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height; 
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
    n->height = 1;
    n->left = NULL;
    n->right = NULL;
    return n;
}

int maxInt(int a, int b) { return a > b ? a : b; }

int height(Node *n) { return n ? n->height : 0; }

void updateHeight(Node *n) {
    n->height = 1 + maxInt(height(n->left), height(n->right));
}

int balanceFactor(Node *n) {
    return n ? height(n->left) - height(n->right) : 0;
}


Node *rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

Node *rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

Node *insertAVL(Node *node, int key) {

    if (node == NULL)
        return createNode(key);
    if (key < node->key)
        node->left = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node; 

    updateHeight(node);

    int bf = balanceFactor(node);


    if (bf > 1 && key < node->left->key) {
        printf("  %d dugumunde LL dengesizligi -> Sag rotasyon\n", node->key);
        return rotateRight(node);
    }

    if (bf < -1 && key > node->right->key) {
        printf("  %d dugumunde RR dengesizligi -> Sol rotasyon\n", node->key);
        return rotateLeft(node);
    }

    if (bf > 1 && key > node->left->key) {
        printf("  %d dugumunde LR dengesizligi -> Sol + Sag (cift) rotasyon\n", node->key);
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (bf < -1 && key < node->right->key) {
        printf("  %d dugumunde RL dengesizligi -> Sag + Sol (cift) rotasyon\n", node->key);
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void preorder(Node *root) {
    if (root == NULL)
        return;
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void printTree(Node *root, int level) {
    if (root == NULL)
        return;
    printTree(root->right, level + 1);
    for (int i = 0; i < level; i++)
        printf("    ");
    printf("%d\n", root->key);
    printTree(root->left, level + 1);
}

void freeTree(Node *root) {
    if (root == NULL)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

typedef struct {
    const char *name;
    int keys[3];
} Test;

int main(void) {
    Test tests[] = {
        {"A (LL)", {30, 20, 10}},
        {"B (RR)", {10, 20, 30}},
        {"C (LR)", {30, 10, 20}},
        {"D (RL)", {10, 30, 20}},
    };
    int testCount = sizeof(tests) / sizeof(tests[0]);

    for (int t = 0; t < testCount; t++) {
        Node *root = NULL; 

        printf("Test %s: ekleme sirasi %d, %d, %d\n", tests[t].name,
               tests[t].keys[0], tests[t].keys[1], tests[t].keys[2]);

        for (int i = 0; i < 3; i++)
            root = insertAVL(root, tests[t].keys[i]);

        printf("  Kok: %d\n", root->key);
        printf("  Preorder: ");
        preorder(root);
        printf("\n  Agac (yatay):\n");
        printTree(root, 2);
        printf("\n");

        freeTree(root);
    }
    return 0;
}