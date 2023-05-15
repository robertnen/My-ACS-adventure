#include <stdio.h>
#include <stdlib.h>

typedef struct graph {
    int nr_nodes;
    struct node** neighbours;
} graph;

typedef struct node {
    int val, cost;
    struct node* next;
} node;

typedef struct heap {
    int *data;
    int size, maxSize;
} heap;

heap* makeHeap(int maxSize) {
    heap* h = (heap*) calloc(1, sizeof(heap));
    h->data = (int*) calloc(maxSize, sizeof(int));
    h->size = 0;
    h->maxSize = maxSize;
    return h;
}

void freeHeap(heap* h) {
    free(h->data);
    free(h);
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void heapify(heap* h, int i) {
    int smallest = i, left = 2 * i + 1, right = 2 * i + 2;
    if(left < h->size && h->data[left] < h->data[smallest]) smallest = left;
    if(right < h->size && h->data[right] < h->data[smallest]) smallest = right;
    if(smallest != i) {
        swap(&h->data[i], &h->data[smallest]);
        heapify(h, smallest);
    }
}

void insert(heap* h, int val) {
    int i = h->size++;
    h->data[i] = val;
    while (i > 0 && h->data[i] < h->data[(i - 1) / 2]) {
        swap(&h->data[i], &h->data[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int getMin(heap* h) {
    int min = h->data[0];
    h->data[0] = h->data[--h->size];
    heapify(h, 0);
    return min;
}

int isEmpty(heap* h) {
    return h->size == 0;
}

void dijkstra(graph G, int source, int* dist) {
    heap* h = makeHeap(100);
    for (int i = 0; i < G.nr_nodes; i++) {
        dist[i] = 10000000;
    }
    dist[source - 1] = 0;
    insert(h, source);
    while (!isEmpty(h)) {
        int u = getMin(h);
        node* p = G.neighbours[u - 1];
        while (p) {
            int v = p->val;
            int w = p->cost;
            if (dist[u - 1] != 10000000 && dist[v - 1] > dist[u - 1] + w) {
                dist[v - 1] = dist[u - 1] + w;
                insert(h, v);
            }
            p = p->next;
        }
    }
    freeHeap(h);
}

int main() {

    FILE *fin = fopen("graf.in", "r");
    graph G;
    node *p, *q;
    int dist[100][100] = {{0}, {0}};

    int x, y, cost, n, m, isDouble;
    fscanf(fin, "%d%d", &n, &m);

    G.neighbours = (node**) calloc(n, sizeof(node*));
    for(int i = 0; i < n; i++)
        G.neighbours[i] = (node*) calloc(1, sizeof(node)), G.neighbours[i]->val = i + 1;

    G.nr_nodes = 0;

    for(int i = 0; i < m; i++) {
        fscanf(fin, "%d%d%d", &x, &y, &cost);

        dist[x][y] = dist[y][x] = cost;

        p = G.neighbours[x - 1];
        isDouble = 0;
        while(p->next) {
            if(p->val == y) {
                isDouble = 1;
                break;
            }
            p = p->next;
        }

        if(!isDouble && p->val != y) {
            p->next = (node*) calloc(1, sizeof(node));
            p->next->val = y;
            p->next->cost = cost;
        }

        p = G.neighbours[y - 1];
        isDouble = 0;
        while(p->next) {
            if(p->val == x) {
                isDouble = 1;
                break;
            }
            p = p->next;
        }

        if(!isDouble && p->val != x) {
            p->next = (node*) calloc(1, sizeof(node));
            p->next->val = x;
            p->next->cost = cost;
        }
    }

    //aflu numarul de noduri
    for(int i = 0; i < n; i++) {
        p = G.neighbours[i];
        if(!p->next) G.nr_nodes++;
    }

    G.nr_nodes = n - G.nr_nodes;

    // //afisez graful
    // for(int i = 0; i < G.nr_nodes; i++) {
    //     p = G.neighbours[i];
    //     printf("Id: %d: ", p->val);

    //     if(!p->next) G.nr_nodes++;
    //     while(p) {
    //         printf("%d ", p->val);
    //         p = p->next;
    //     }
    //     printf("\n");
    // }

    //eliberarea memoriei
    for(int i = 0; i < G.nr_nodes; i++) {
        p = G.neighbours[i];
        while(p->next) {
            q = p->next;
            if(!q->next) {
                p->next = NULL;
                free(q);
            } else {
                while(q->next->next)
                      q = q->next;
                free(q->next);
                q->next = NULL;
            }
        }
        free(G.neighbours[i]);
    }
    free(G.neighbours);

    return 0;
}