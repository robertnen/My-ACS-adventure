/* NENCIU George-Robert - 313CC */
#ifndef ESSENTIALS_H_
#define ESSENTIALS_H_
#include "errorFuncs.h"
#define infinity 100000000

typedef struct Node {
    int id, edgeCounter, cost;
    struct Node* next;
} Node;

typedef struct Graph {
    int size, *areas, *nodes, *depths; //nodes memoreaza cate noduri are o zona
    Node **adjLists;
    char **names;
} Graph;

int charToNum(char str[]);
int cmpQSort(const void *x, const void *y);
Node* getAdress(Graph g, int row, int col);
int getPosOfSpace(char str[]);
int findPosOfNode(Node* base, int id);
int findPosOfName(Graph g, char name[]);
Node* createNode(Node* base, int id);
int* BFS(Graph g, int pos, int isVisited[], int queue[]);
void showRoad(int *path, int pos, Graph g, int *maxim, char output[]);
int* shortestPathWithDijkstra(Graph g, int start, int *costs, int *isVisited);

#endif