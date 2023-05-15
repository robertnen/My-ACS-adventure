/* NENCIU George-Robert - 313CC */
#ifndef TREEFUNC_H
#define TREEFUNC_H

    #include "myStructs.h"

    unsigned long long getMeanValue(Pixel **grid, int size, int x, int y, Pixel *pixel);
    void generateTree(QuadTree *qTree, Pixel **grid, int size, int x, int y, int tol, int *counter, int *treeSize);
    int quadTreeHeight(QuadTree *qTree, int height);
    void BFS(QuadTree *qTree, Queue *queue);
    int quadMaxSize(QuadTree *qTree, int size);
    void remakeQuadTree(QuadTree *qTree, QueueNode **queueTree, QueueNode **parents, int *size1, int *size2);
    void remakeImage(QuadTree *qTree, Pixel **grid, int size, int x, int y);

#endif