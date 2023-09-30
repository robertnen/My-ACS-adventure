/* NENCIU George-Robert - 313CC */
#include "essentials.h"

int charToNum(char str[]) {
	int size = strlen(str);
	int n = 0, i;
	for(i = 0; i < size && str[i] != ' '; i++) n = n * 10 + str[i] - '0';
	return n;
}

int cmpQSort(const void *x, const void *y) { return (*(int*)x - *(int*)y); }

Node* getAdress(Graph g, int row, int col) {

    int i;
    Node *p = g.adjLists[row];
    for(i = 0; i <= col; i++) p = p->next;
    return p; //returnez nodul cautat (NU POATE FI NULL)
}

int getPosOfSpace(char str[]) {
    int index = 0;
    while(str[index++] != ' ');
    return index;
}

int findPosOfNode(Node* base, int id) {
    int i;
    Node *p = base;
    for(i = 0; i < base->edgeCounter; i++) {
        p = p->next;
        if(id == p->id) return i; //intre base si id exista arc / muchie
    }
    return -1; //nu exista arc / muchie intre base si id
}

int findPosOfName(Graph g, char name[]) {
    int i;
    for(i = 0; i < g.size; i++)
        if(!strcmp(g.names[i], name)) return i; //exista un nod acest nume
    return -1; //nu exista nod cu acest nume
}

Node* createNode(Node* base, int id) {
    Node *new = (Node*) calloc(1, sizeof(Node));
    if(!new) sendErrorOfNull("new", "Node*", "createNode");
    new->id = id;

    base->edgeCounter++;
    new->next = base->next; //adaug nodul in lista
    base->next = new;
    return base;
}

int* BFS(Graph g, int pos, int isVisited[], int queue[]) {
    int st, dr, id, front, i;
    st = dr = 0;
    isVisited[pos] = 1;
    queue[dr++] = pos;

    while(st < dr) {
        front = queue[st++];
        for(i = 0; i< g.adjLists[front]->edgeCounter; i++) {
            id = getAdress(g, front, i)->id;
            if(!isVisited[id]) {
                    isVisited[id] = 1;
                    queue[dr++] = id;
            }
        }
    }
    return queue;
}

void showRoad(int *path, int pos, Graph g, int *maxim, char output[]) {
    if(pos == -1) return; //sunt in radacina
    if(g.depths[pos] < *maxim && g.depths[pos] != 1) (*maxim) = g.depths[pos];
    showRoad(path, path[pos], g, maxim, output); //inca nu am ajuns la radacina
    strcat(output, g.names[pos]);
    strcat(output, " ");
}

int* shortestPathWithDijkstra(Graph g, int start, int *costs, int *isVisited) {
    int i, j, pos, minim, *path;
    for(i = 0; i < g.size; i++) costs[i] = infinity;

    path = (int*) calloc(g.size, sizeof(int));
    if(!path) sendErrorOfNull("path", "int*", "shortestPathWithDijkstra");

    costs[start] = 0;
    path[start] = -1; //e radacina
    for(i = 0; i < g.size - 1; i++) {
        minim = infinity;
        for(j = 0; j < g.size; j++) {
            if(!isVisited[j] && costs[j] <= minim) {
                minim = costs[j];
                pos = j; //am gasit unde trebuie sa merg
            }
        }
        isVisited[pos] = 1;
        for(j = 0; j < g.size; j++) {
            if(isVisited[j]) continue;
            if(findPosOfNode(g.adjLists[pos], j) == -1) continue;
            if(costs[pos] == infinity) continue;
            if(costs[pos] + getAdress(g, pos, findPosOfNode(g.adjLists[pos], j))->cost < costs[j]) {
                costs[j] = costs[pos] + getAdress(g, pos, findPosOfNode(g.adjLists[pos], j))->cost;
                path[j] = pos; //pun care este parintele nodului j
            }
        }
    }
    return path; //returnez vectorul de tati
}