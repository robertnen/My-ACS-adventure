#include <stdio.h>
#include <stdlib.h>
#define min(a,b) ((a) < (b) ? (a) : (b))

typedef struct graph {
    int nr_nodes;
    struct node** neighbours;
} graph;

typedef struct node {
    int val;
    struct node* next;
} node;

typedef struct stack {
    int val;
    struct stack* next;
} stack;

void push(stack** s, int val) {
    stack* new_node = (stack*) malloc(sizeof(stack));
    new_node->val = val;
    new_node->next = *s;
    *s = new_node;
}

int pop(stack** s) {
    stack* node = *s;
    int val = node->val;
    *s = node->next;
    free(node);
    return val;
}

void strongConnect(graph G, int u, int* index, int* lowlink, int* onstack, stack** S, int* component) {
    static int time = 0;
    index[u] = lowlink[u] = ++time;
    push(S, u);
    onstack[u] = 1;

    node* v = G.neighbours[u - 1];
    while(v) {
        if(!index[v->val]) {
            strongConnect(G, v->val, index, lowlink, onstack, S, component);
            lowlink[u] = min(lowlink[u], lowlink[v->val]);
        } else if(onstack[v->val]) lowlink[u] = min(lowlink[u], index[v->val]);
        v = v->next;
    }

    if(lowlink[u] == index[u]) {
        int w = 0;
        do {
            w = pop(S);
            onstack[w] = 0;
            component[w] = u;
        } while(w != u);
    }
}

void tarjan(graph G) {
    int n = G.nr_nodes;
    int index[n + 1], lowlink[n + 1], onstack[n + 1], component[n + 1];
    for(int i = 1; i <= n; i++)
        index[i] = lowlink[i] = onstack[i] = component[i] = 0;

    stack* S = NULL;

    for(int u = 1; u <= n; u++)
        if(index[u] == 0) strongConnect(G, u, index, lowlink, onstack, &S, component);


    for(int i = 1; i <= n; i++) {
        if(component[i] == i) {
            printf("%d:", i);
            for(int j = 1; j <= n; j++)
                if(component[j] == i) printf(" %d", j);
            printf("\n");
        }
    }
}

int main() {

    FILE *fin = fopen("graf.in", "r");
    graph G;
    node *p, *q;

    int x, y, n, m, isDouble;
    fscanf(fin, "%d%d", &n, &m);

    G.neighbours = (node**) calloc(n, sizeof(node*));
    for(int i = 0; i < n; i++)
        G.neighbours[i] = (node*) calloc(1, sizeof(node)), G.neighbours[i]->val = i + 1;

    G.nr_nodes = 0;

    for(int i = 0; i < m; i++) {
        fscanf(fin, "%d%d", &x, &y);

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
        }
    }

    //aflu numarul de noduri
    for(int i = 0; i < n; i++) {
        p = G.neighbours[i];
        if(!p->next) G.nr_nodes++;
    }

    G.nr_nodes = n - G.nr_nodes;

    //afisez graful
    for(int i = 0; i < G.nr_nodes; i++) {
        p = G.neighbours[i];
        printf("Id: %d: ", p->val);

        if(!p->next) G.nr_nodes++;
        while(p) {
            printf("%d ", p->val);
            p = p->next;
        }
        printf("\n");
    }

    //bfs
    int queue[100], st, dr, dist[100] = {0}, isVisited[100] = {0};
    st = dr = 0;

    queue[0] = 1; //asa cere enuntul
    while(st <= dr) {
        x = queue[st++];
        isVisited[x] = 1;
        p = G.neighbours[x - 1];
        while(p) {
            if(!isVisited[p->val]) {
                queue[++dr] = p->val;
                dist[p->val] = dist[x] + 1;
            }
            p = p->next;
        }
    }

    for(int i = 0; i < G.nr_nodes; i++)
        printf("%d -> %d\n", i + 1, dist[i + 1]);

    //dfs
    for(int i = 0; i < 100; i++) isVisited[i] = 0;

    int stack[100], len = 1, findTime[100] = {0}, finishTime[100] = {0}, time = 0;
    stack[0] = 1; //asa se cere
    while(len) {
        x = stack[len-- - 1];
        if(!isVisited[x]) {
            printf("%d ", x);
            isVisited[x] = 1;
            findTime[x] = time++;
        }
        p = G.neighbours[x - 1];
        while(p) {
            if(!isVisited[p->val]) {
                stack[len++] = p->val;
                finishTime[x] = time++;
            }
            p = p->next;
        }
    }

    printf("\n");
    for(int i = 0; i < G.nr_nodes; i++) printf("%d ", findTime[i]);
    printf("\n");
    for(int i = 0; i < G.nr_nodes; i++) printf("%d ", finishTime[i]);

    int isSorted = 0;
    while(!isSorted) {
        isSorted = 1;
        for(int i = 0; i < G.nr_nodes - 1; i++)
            if(finishTime[i] > finishTime[i + 1]) {
                isSorted = 0;
                finishTime[i] ^= finishTime[i + 1];
                finishTime[i + 1] ^= finishTime[i];
                finishTime[i] ^= finishTime[i + 1];
                p = G.neighbours[i];
                G.neighbours[i] = G.neighbours[i + 1];
                G.neighbours[i + 1] = p;
            }
    }

    printf("\n");
    for(int i = 0; i < G.nr_nodes; i++) printf("%d ", G.neighbours[i]->val);
    printf("\n");


    tarjan(G);

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