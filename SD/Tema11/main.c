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

typedef struct edge {
    int src, dest, cost;
} edge;

int compare(const void* a, const void* b) { return ((edge*)a)->cost - ((edge*)b)->cost; }
void kruskal(graph G) {
    node **neighbours = G.neighbours;
    edge *edges = calloc(G.nr_nodes, (G.nr_nodes - 1) / 2 * sizeof(edge));
    int numEdge = 0, numResult = 0;

    for(int i = 0; i < G.nr_nodes; i++) {
        node* p = neighbours[i];
        while(p->next) {
            p = p->next;
            if(i < p->val) {
                edges[numEdge].src = i + 1;
                edges[numEdge].dest = p->val;
                edges[numEdge].cost = p->cost;
                numEdge++;
            }
        }
    }
    qsort(edges, numEdge, sizeof(edge), compare);

    int* parent = calloc(G.nr_nodes, sizeof(int));
    for(int i = 0; i < G.nr_nodes; i++) parent[i] = i;

    edge *result = calloc((G.nr_nodes - 1), sizeof(edge));

    for(int i = 0; i < numEdge; i++) {
        int srcParent = parent[edges[i].src - 1], destParent = parent[edges[i].dest - 1];
        if(srcParent != destParent) {
            result[numResult] = edges[i];
            numResult++;

            for(int j = 0; j < G.nr_nodes; j++)
                if(parent[j] == destParent) parent[j] = srcParent;
        }
    }

    free(edges);
    free(parent);
    free(result);
}

void prim(graph G) {
    node** neighbours = G.neighbours;

    int *costs = calloc(G.nr_nodes, sizeof(int)), *parent = calloc(G.nr_nodes, sizeof(int));
    int *isVisited = calloc(G.nr_nodes, sizeof(int)), minIndex, mincosts;

    for(int i = 0; i < G.nr_nodes; i++) costs[i] = 1000000;

    costs[0] = 0;
    parent[0] = -1;

    for(int count = 0; count < G.nr_nodes - 1; count++) {
        mincosts = 1000000;
        for(int v = 0; v < G.nr_nodes; v++) {
            if(isVisited[v] == 0 && costs[v] < mincosts) {
                mincosts = costs[v];
                minIndex = v;
            }
        }
        isVisited[minIndex] = 1;
        node* p = neighbours[minIndex];

        while(p->next) {
            p = p->next;
            int v = p->val - 1;
            int cost = p->cost;

            if(isVisited[v] == 0 && cost < costs[v]) {
                parent[v] = minIndex;
                costs[v] = cost;
            }
        }
    }
    free(costs);
    free(parent);
    free(isVisited);
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