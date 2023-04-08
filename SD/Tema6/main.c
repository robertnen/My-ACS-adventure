#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct BSTree {
    int key;
    struct BSTree *left, *right;
} BSTree;

BSTree* init() {
    BSTree *tree = (BSTree*) calloc(1, sizeof(BSTree));
    tree->key = -9999;
    return tree;
}

BSTree* search(BSTree *tree, int key) {
    BSTree *p = tree;
    int i = 0;
    if(tree->key == key) printf("%d\n", tree->key);
    while(p->key != key) {
        printf("%d -> ", p->key);
        if(p->left && p->left->key < key) p = p->right;
        else if(p->right) p = p->left;
    }
    printf("%d\n", p->key);
    return p;
}

BSTree* insertTree(BSTree* tree, int key) {
    if(tree->key == -9999) {
        tree->key = key;
        return tree;
    }
    BSTree *node = (BSTree*) calloc(1, sizeof(BSTree));
    BSTree *parent;
    node->key = key;
    if(tree == NULL) return node;
    while(tree != NULL) {
        parent = tree;
        if(key < tree->key) tree = tree->left;
        else tree = tree->right;
    }

    if(key < parent->key) parent->left = node;
    else parent->right = node;

    return tree;
}

BSTree* findSuccesor(BSTree *tree, int key) {
    BSTree *p = tree, *succesor, *parent;
    int i = 0;
    if(tree->key == key) printf("%d\n", tree->key);
    while(p->key != key) {
        if(p->left && p->left->key < key) p = p->right;
        else if(p->right) p = p->left;
    }

    succesor = p;
    parent = p;
    p = p->right;
    while(p) {
        parent = succesor;
        succesor = p;
        p = p->left;
    }

    return succesor;
}

BSTree* delNode(BSTree *tree, int key) {
    if(tree == NULL) return NULL;
    printf("key = %d\n", tree->key);
    BSTree *succesor, *parent, *p;

    if(tree->key == key) {
        printf("%d %d\n", tree->left == NULL, tree->right == NULL);
        if(tree->left == NULL && tree->right == NULL) {
            free(tree);
            tree = NULL;
            return tree;
        }

        if(tree->left == NULL) {
            p = tree;
            tree = tree->right;
            free(p);
            return tree;
        }

        if(tree->right == NULL) {
            p = tree;
            tree = tree->left;
            free(p);
            return tree;
        }
        tree->key = findSuccesor(tree, key)->key;
        tree->right = delNode(tree->right, tree->key);
        printf("%d\n", tree->left == NULL);
        return tree;
    }
    if(tree->key > key) {
        tree->left = delNode(tree->left, key);
        return tree;
    }

    if(tree->key < key) {
        tree->right = delNode(tree->right, key);
        return tree;
    }
}

void preorderTree(BSTree *tree) {
  if(tree == NULL) return;
  printf("%d ", tree->key);
  preorderTree(tree->left);
  preorderTree(tree->right);
}

void postorderTree(BSTree *tree) {
  if(tree == NULL) return;
  postorderTree(tree->left);
  postorderTree(tree->right);
  printf("%d ", tree->key);
}

void inorderTree(BSTree *tree) {
  if(tree == NULL) return;
  inorderTree(tree->left);
  printf("%d ", tree->key);
  inorderTree(tree->right);
}

void freeTree(BSTree *tree) {
  if(tree == NULL) return;
  freeTree(tree->left);
  printf("Nodul cu cheia %d a fost sters!\n", tree->key);
  free(tree);
  freeTree(tree->right);
}

int height(int size) { return floor(log(size));}

int search_prev(BSTree *tree, int x) {
    int maxi = -1, aux;
    if(tree == NULL) return -1;
    if(maxi < tree->key && tree->key < x) maxi = tree->key;
    aux = search_prev(tree->left, x);
    if(maxi < aux && aux < x) maxi = aux;
    aux = search_prev(tree->right, x);
    if(maxi < aux && aux < x) maxi = aux;
    return maxi;
}
int search_next(BSTree *tree, int x) {
    int min = 9999, aux;
    if(tree == NULL) return 9999;
    if(min > tree->key && tree->key > x) min = tree->key;
    aux = search_next(tree->left, x);
    if(min > aux && aux > x) min = aux;
    aux = search_next(tree->right, x);
    if(min > aux && aux > x) min = aux;
    return min;
}

int main() {

    BSTree *tree = init();
    insertTree(tree, 3);
    insertTree(tree, 1);
    insertTree(tree, 7);
    insertTree(tree, 2);
    insertTree(tree, 5);
    insertTree(tree, 6);
    insertTree(tree, 0);
    insertTree(tree, 4);
    insertTree(tree, 9);

    preorderTree(tree);
    printf("\n");
    inorderTree(tree);
    printf("\n");
    postorderTree(tree);
    printf("\n");

    printf("%d\n", height(9));
    search(tree, 4);
    printf("%d\n", search_prev(tree, 8));
    printf("%d\n", search_next(tree, 8));

    delNode(tree, 5);
    preorderTree(tree);
    printf("\n");

    freeTree(tree);

    return 0;
}