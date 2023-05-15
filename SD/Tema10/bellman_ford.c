#include <stdio.h>
#include <stdlib.h>
#define infinity 100000000

typedef struct graph {
    int nr_nodes;
    struct node** neighbours;
} graph;

typedef struct node {
    int val, cost;
    struct node* next;
} node;

void bellmanFord(graph G, int src, int dist[]) {

    for(int i = 0; i < G.nr_nodes; i++)
        dist[i] = infinity;

    dist[src] = 0;

    for(int i = 0; i < G.nr_nodes - 1; i++)
        for(int u = 0; u < G.nr_nodes; u++) {
            node* p = G.neighbours[u];
            while(p) {
                int v = p->val - 1;
                int weight = p->cost;
                if(dist[u] != infinity && dist[u] + weight < dist[v])
                    dist[v] = dist[u] + weight;
                p = p->next;
            }
        }

    for(int u = 0; u < G.nr_nodes; u++) {
        node* p = G.neighbours[u];
        while(p) {
            int v = p->val - 1;
            int weight = p->cost;
            if(dist[u] != infinity && dist[u] + weight < dist[v]) {
                printf("Ciclu negativ\n");
                return;
            }
            p = p->next;
        }
    }
}

int main() {

    FILE *fin = fopen("graf.in", "r");
    graph G;
    node *p, *q;
    int dist[100][100] = {{0}, {0}}, distV[100] = {0};

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

    bellmanFord(G, 1, distV);

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