/* NENCIU George-Robert - 313CC */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "myStructs.h"

int charToNum(char str[]) {
	int size = strlen(str);
	int n = 0, i;
	for(i = 0; i < size && str[i] != ' '; i++) n = n * 10 + str[i] - '0';
	return n;
}

void sendErrorOfNull(const char *name, const  char *type, const char *funcName) {
    char errMes[8][100] = {"Couldn't alloc memory to pointer '",
                           "_name_to_be_inserted_",
                           "' (type: '",
                           "_type_to_be_inserted_", "') ",
                           "because after calloc in function '",
                           "_function_name_to_be_inserted_",
                           "' the returned value is NULL.\n"};

    //adaug informatia necesara
    strcpy(errMes[1], name);
    strcpy(errMes[3], type);
    strcpy(errMes[6], type);
    int i;
    char toSend[50];
    strcpy(toSend, errMes[0]);
    for(i = 1; i < 8; i++) strcat(toSend, errMes[i]); //formez mesajul
    fprintf(stderr, "%s", toSend);
    exit(1);
}

void sendErrorOfFileNull(const char *name, const  char *type, const char *funcName) {
    char errMes[8][100] = {"Couldn't open file '",
                           "_name_to_be_inserted_",
                           "' (type: '",
                           "_type_to_be_inserted_", "') ",
                           "because after calling it in function '",
                           "_function_name_to_be_inserted_",
                           "' the returned value is NULL.\n"};

    //adaug informatia necesara
    strcpy(errMes[1], name);
    strcpy(errMes[3], type);
    strcpy(errMes[6], type);
    int i;
    char toSend[50];
    strcpy(toSend, errMes[0]);
    for(i = 1; i < 8; i++) strcat(toSend, errMes[i]); //formez mesajul
    fprintf(stderr, "%s", toSend);
    exit(1);
}

QueueNode* createQueueNode(QuadTree *node) {
    QueueNode *new = (QueueNode*) calloc(1, sizeof(QueueNode));
    if(!new) sendErrorOfNull("new", "QueueNode*", "createQueueNode");

    new->node = node;
    return new;
}

QueueNode* enqueueNode(QueueNode *queue, int *size, QuadTree* node) {
    if(!(*size)) { //coada e goala
        queue = createQueueNode(node);
        (*size)++;
        return queue;
    }
    QueueNode *new = createQueueNode(node), *p = queue;
    while(p->next) p = p->next;
    p->next = new;
    (*size)++;
    return queue;
}

QueueNode* dequeueNode(QueueNode *queue, int *size) {
    QueueNode *aux = queue;
    queue = queue->next;
    (*size)--;
    free(aux);
    return queue;
}

QuadTree* frontQueue(QueueNode *queue) { return queue->node; }

QueueNode* rearQueue(QueueNode *queue) {
    QueueNode *p = queue;
    while(p->next) p = p->next;
    return p;
}

void freeQueue(QueueNode *queue, int *size) {
    int i;
    for(i = 0; i < *size; i++) queue = dequeueNode(queue, size);
}

QuadTree* initQuadTree() {
    QuadTree *qTree = (QuadTree*) calloc(1, sizeof(QuadTree));
    if(!qTree) sendErrorOfNull("qTree", "QuadTree*", "initQuadTree");

    qTree->type = 0;
    return qTree;
}

QuadTree* newNode(unsigned char type) {
    QuadTree *new = (QuadTree*) calloc(1, sizeof(QuadTree));
    if(!new) sendErrorOfNull("new", "QuadTree*", "newNode");
    new->type = type;
    return new;
}