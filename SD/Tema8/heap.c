#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *left, *right;
} Node;

typedef struct Heap {
    int no_nodes;
    Node *root;
} Heap;

int getPowerOfTwo(int n) {
    if(n < 1) return -1;
    int p = 1, counter = 0;
    while(p < n) counter++, p <<= 1;
    if(n - p) return counter - 1;
    return counter;
}

Heap* reoderHeap(Heap *h, int tree[]) {

    int isSorted = 0, i, power, log;
    Node *p, *q;

    while(!isSorted) {
        isSorted = 1;
        for(i = 0; i < h->no_nodes - 1; i++)
            if(tree[i] < tree[i + 1]) {
                isSorted = 0;
                tree[i] ^= tree[i + 1];
                tree[i + 1] ^= tree[i];
                tree[i] ^= tree[i + 1];

                log = getPowerOfTwo(i + 1);
                power = (1 << (log - 1));
                p = h->root;
                while(log--) {
                    if((power & i + 1) == power) p = p->right;
                    else p = p->left;
                }

                log = getPowerOfTwo(i + 2);
                power = (1 << (log - 1));
                q = h->root;
                while(log--) {
                    if((power & (i + 2)) == power) q = q->right;
                    else q = q->left;
                }
                //swap in arbore
                p->val ^= q->val;
                q->val ^= p->val;
                p->val ^= q->val;
            }
    }
    return h;
}

Heap* insert(Heap *h, int val, int tree[]) {
    if(!h) {
        h = (Heap*) calloc(1, sizeof(Heap));
        h->root = (Node*) calloc(1, sizeof(Node));
        h->root->val = val;
        h->no_nodes = 1;
        tree[h->no_nodes - 1] = val;
        return h;
    }

    Node *p = h->root;
    int log = getPowerOfTwo(++h->no_nodes), power, pos;
    power = (1 << log); //codul pe biti

    pos = 1;
    power >>= 1; //radacina e 1
    while(log-- > 1) {
        if(p->val < val) {
            tree[pos - 1] = val;
            p->val ^= val;
            val ^= p->val;
            p->val ^= val;
            }
        pos <<= 1;
        if((power & h->no_nodes) == power) {
            p = p->right;
            pos++;
        } else p = p->left;
        power >>= 1;
    }

    if(p->val < val) {
        tree[pos - 1] = val;
        p->val ^= val;
        val ^= p->val;
        p->val ^= val;
    }
    if((power & h->no_nodes) == power) {
        p->right = (Node*) calloc(1, sizeof(Node));
        p->right->val = val;
    } else {
        p->left = (Node*) calloc(1, sizeof(Node));
        p->left->val = val;
    }
    tree[h->no_nodes - 1] = val;
    return reoderHeap(h, tree);
}

Heap* remove_root(Heap *h, int tree[], int *result) {
    Node *p = h->root;
    *result = h->root->val;

    while(p->left) p = p->left;
    h->root->val = p->val;
    tree[0] = -999;
    h = reoderHeap(h, tree);
    h->no_nodes--;
    free(p);
    return h;
}

int main() {

    Heap *h = NULL;
    int tree[100], val;
    h = insert(h, 3, tree);
    h = insert(h, 2, tree);
    h = insert(h, 1, tree);
    h = insert(h, 5, tree);
    h = insert(h, 4, tree);
    h = insert(h, -1, tree);
    h = insert(h, 0, tree);
    h = insert(h, -3, tree);
    h = insert(h, -2, tree);

    for(int i = 0; i < h->no_nodes; i++)
        printf("%d ", tree[i]);

    h = remove_root(h, tree, &val);
    printf("\nval = %d\n", val);

    for(int i = 0; i < h->no_nodes; i++)
        printf("%d ", tree[i]);

    return 0;
}