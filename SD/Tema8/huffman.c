#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char ch;
    int counter;
    struct Node *left, *right;
} Node;

typedef struct Heap {
    int size;
    int maxSize;
    struct Node** treeArr;
} Heap;

Node* newNode(char ch, int counter) {

    Node* tmp = (Node*) calloc(1, sizeof(Node));
    tmp->ch = ch;
    tmp->counter = counter;
    return tmp;
}

Heap* createHeap(int maxSize) {

    Heap* h = (Heap*) calloc(1, sizeof(Heap));
    h->size = 0;
    h->maxSize = maxSize;
    h->treeArr = (Node**) calloc(h->maxSize, sizeof(Node*));
    return h;
}

void swapNode(Node** x, Node** y) {

    Node* aux = *x;
    *x = *y;
    *y = aux;
}

void recheckHeap(Heap* h, int pos) {

    int minimum = pos;
    int left = 2 * pos + 1;
    int right = 2 * pos + 2;

    if(left < h->size && h->treeArr[left]->counter < h->treeArr[minimum]->counter) minimum = left;
    if(right < h->size && h->treeArr[right]->counter < h->treeArr[minimum]->counter) minimum = right;

    if(minimum != pos) {
        swapNode(&h->treeArr[minimum], &h->treeArr[pos]);
        recheckHeap(h, minimum);
    }
}

int isSizeOne(Heap* h) { return (h->size == 1); }

Node* getMin(Heap* h) {

    Node* tmp = h->treeArr[0];
    h->treeArr[0] = h->treeArr[h->size - 1];
    h->size--;
    recheckHeap(h, 0);
    return tmp;
}

void insertHeap(Heap* h, Node* node) {

    h->size++;
    int i = h->size - 1;

    while(i && node->counter < h->treeArr[(i - 1) / 2]->counter) {
        h->treeArr[i] = h->treeArr[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->treeArr[i] = node;
}

void buildHeap(Heap* h) { for(int i = h->size / 2 - 1; i >= 0; --i) recheckHeap(h, i); }

void printArr(int arr[], int n) {

    for(int i = 0; i < n; ++i) printf("%d", arr[i]);
    printf("\n");
}

int isLeaf(Node* root) { return !(root->left) && !(root->right); }

Heap* setHeap(char ch[], int counter[], int size) {

    Heap* h = createHeap(size);
    for(int i = 0; i < size; ++i) h->treeArr[i] = newNode(ch[i], counter[i]);

    h->size = size;
    buildHeap(h);
    return h;
}

Node* buildHuffmanTree(char ch[], int counter[], int size) {

    Node *left, *right, *top;
    Heap* h = setHeap(ch, counter, size);

    while(!isSizeOne(h)) {

        left = getMin(h);
        right = getMin(h);

        top = newNode('?', left->counter + right->counter);
        top->left = left;
        top->right = right;

        insertHeap(h, top);
    }

    return getMin(h);
}

void printHuffCodes(Node* root, int arr[], int top) {

    if (root->left) arr[top] = 0, printHuffCodes(root->left, arr, top + 1);
    if (root->right) arr[top] = 1, printHuffCodes(root->right, arr, top + 1);
    if (isLeaf(root)) {
        printf("%c -> ", root->ch);
        printArr(arr, top);
    }
}

void HuffmanCodes(char ch[], int counter[], int size) {

    Node* root = buildHuffmanTree(ch, counter, size);
    int arr[1000], top = 0;
    printHuffCodes(root, arr, top);
}

int main() {

    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f',
                  'g', 'h', 'i', 'j', 'k', 'l'};
    int counter[] = {125,  14,  23,  52, 192,   9,
                       7,   2, 102,   1,   1,  12};
    int size = 12;

    HuffmanCodes(arr, counter, size);
    return 0;
}