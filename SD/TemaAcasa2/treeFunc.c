/* NENCIU George-Robert - 313CC */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "treeFunc.h"


unsigned long long getMeanValue(Pixel **grid, int size, int x, int y, Pixel *pixel) {

    unsigned long long red, green, blue, mean, tmp;
    int i, j;
    mean = red = green = blue = 0;
    for(i = y; i < y + size; i++)
        for(j = x; j < x + size; j++) { //calculez sumele
            red += grid[i][j].r;
            blue += grid[i][j].b;
            green += grid[i][j].g;
        }

    red /= (size * size);
    blue /= (size * size);
    green /= (size * size);

    for(i = y; i < y + size; i++) //calculez media
        for(j = x; j < x + size; j++) {
            mean += (red - grid[i][j].r) * (red - grid[i][j].r);
            mean += (blue - grid[i][j].b) * (blue - grid[i][j].b);
            mean += (green - grid[i][j].g) * (green - grid[i][j].g);
        }

    tmp = 3 * size * size;
    mean = (unsigned long long)(mean / tmp);
    pixel->r = red;
    pixel->g = green;
    pixel->b = blue; //ce se returneaza
    return mean;
}

void generateTree(QuadTree *qTree, Pixel **grid, int size, int x, int y, int tol, int *counter, int *treeSize) {
    if(size == 1) { //nu pot imparti blocul
        getMeanValue(grid, size, x, y, &qTree->pixel);
        (*counter)++;
        return;
    }

    unsigned long long mean = getMeanValue(grid, size, x, y, &qTree->pixel);
    if(mean <= tol) { //frunza
        (*counter)++;
        return;
    }
    qTree->type = 0;

    qTree->tl = newNode(1); //momentan presupun ca sunt frunze
    qTree->tr = newNode(1);
    qTree->br = newNode(1);
    qTree->bl = newNode(1);

    (*treeSize) += 4;

    generateTree(qTree->tl, grid, size / 2, x, y, tol, counter, treeSize);
    generateTree(qTree->tr, grid, size / 2, x + size / 2, y, tol, counter, treeSize);
    generateTree(qTree->br, grid, size / 2, x + size / 2, y + size / 2, tol, counter, treeSize);
    generateTree(qTree->bl, grid, size / 2, x, y + size / 2, tol, counter, treeSize);
}

int quadTreeHeight(QuadTree *qTree, int height) {
    if(!qTree || !qTree->tl || !qTree->tr || !qTree->bl || !qTree->br) return height;
    int aux, max = height;

    aux = quadTreeHeight(qTree->tl, height + 1);
    if(max < aux) max = aux;

    aux = quadTreeHeight(qTree->tr, height + 1);
    if(max < aux) max = aux;

    aux = quadTreeHeight(qTree->br, height + 1);
    if(max < aux) max = aux;

    aux = quadTreeHeight(qTree->bl, height + 1);
    if(max < aux) max = aux;

    return max;
}

void BFS(QuadTree *qTree, Queue *queue) {
    if(!qTree) return;
    QuadTree *current;
    queue->front = queue->rear = 0;
    queue[0].node = qTree;
    while(queue->front <= queue->rear) {
        current = queue[queue->front++].node;
        if(current->tl) queue[++queue->rear].node = current->tl;
        if(current->tr) queue[++queue->rear].node = current->tr;
        if(current->br) queue[++queue->rear].node = current->br;
        if(current->bl) queue[++queue->rear].node = current->bl;
    }
}

int quadMaxSize(QuadTree *qTree, int size) {
    if(!qTree || !qTree->tl || !qTree->tr || !qTree->bl || !qTree->br) return size;
    int aux, max = 0;

    aux = quadMaxSize(qTree->tl, size / 2);
    if(max < aux) max = aux;

    aux = quadMaxSize(qTree->tr, size / 2);
    if(max < aux) max = aux;

    aux = quadMaxSize(qTree->br, size / 2);
    if(max < aux) max = aux;

    aux = quadMaxSize(qTree->bl, size / 2);
    if(max < aux) max = aux;

    return max;
}

void remakeQuadTree(QuadTree *qTree, QueueNode **queueTree, QueueNode **parents, int *size1, int *size2) {

    if(*size1 == 1) {    //imaginea se reprezinta doar cu un patrat
        qTree = frontQueue(*parents);
        *parents = dequeueNode(*parents, size2);
        *queueTree = dequeueNode(*queueTree, size1);
        return;
    }

    *queueTree = dequeueNode(*queueTree, size1);

    while(*size1) {
        qTree = frontQueue(*parents); //scot nodul care este parinte
        *parents = dequeueNode(*parents, size2);

        //adaug fiecare fiu
        qTree->tl = frontQueue(*queueTree);
        *queueTree = dequeueNode(*queueTree, size1);

        qTree->tr = frontQueue(*queueTree);
        *queueTree = dequeueNode(*queueTree, size1);

        qTree->br = frontQueue(*queueTree);
        *queueTree = dequeueNode(*queueTree, size1);

        qTree->bl = frontQueue(*queueTree);
        *queueTree = dequeueNode(*queueTree, size1);
    }
}

void remakeImage(QuadTree *qTree, Pixel **grid, int size, int x, int y) {
    if(!qTree) return;
    if(qTree->type) {
        int i, j;
        for(i = y; i < y + size; i++)
            for(j = x; j < x + size; j++) {
                grid[i][j].r = qTree->pixel.r;
                grid[i][j].g = qTree->pixel.g;
                grid[i][j].b = qTree->pixel.b;
            }
        return;
    }

    remakeImage(qTree->tl, grid, size / 2, x, y);
    remakeImage(qTree->tr, grid, size / 2, x + size / 2, y);
    remakeImage(qTree->br, grid, size / 2, x + size / 2, y + size / 2);
    remakeImage(qTree->bl, grid, size / 2, x, y + size / 2);
}