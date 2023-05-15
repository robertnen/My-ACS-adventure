/* NENCIU George-Robert - 313CC */
#ifndef MYSTRUCTS_H
#define MYSTRUCTS_H

    typedef struct Pixel {
        unsigned char r, g, b;
    } Pixel;

    typedef struct QuadTree {
        unsigned char type; // nod intern sau extern
        Pixel pixel;
        struct QuadTree *tl, *tr, *bl, *br;
    } QuadTree;

    typedef struct Queue { //folosit pentru cerintele 1 si 2
        int rear, front;
        QuadTree *node;
    } Queue;

    typedef struct QueueNode { //folosit pentru cerinta 3
        QuadTree *node;
        struct QueueNode *next;
    } QueueNode;

    int charToNum(char str[]);
    void sendErrorOfNull(const char *name, const  char *type, const char *funcName);
    void sendErrorOfFileNull(const char *name, const  char *type, const char *funcName);
    QueueNode* createQueueNode(QuadTree *node);
    QueueNode* enqueueNode(QueueNode *queue, int *size, QuadTree* node);
    QueueNode* dequeueNode(QueueNode *queue, int *size);
    QuadTree* frontQueue(QueueNode *queue);
    QueueNode* rearQueue(QueueNode *queue);
    void freeQueue(QueueNode *queue, int *size);
    QuadTree* initQuadTree();
    QuadTree* newNode(unsigned char type);

#endif