/* NENCIU George-Robert - 313CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

Node* createNode(unsigned char ch) {
    Node* new = (Node*) calloc(1, sizeof(Node));
    new->ch = ch;
    return new;
}

List* initLista() {
    List* list = (List*) calloc(1, sizeof(List));
    list->total = 0; //primul nod nu poate fi modificat
    list->head = createNode('|'); //nu se modifica
    return list;
}

Node* addNode(List* list, int pos, unsigned char ch) {
    list->total++;
    Node* new = createNode(ch), *p;
    if(pos == 1) { //devine primul mod modificabil din lista
        new->prev = list->head;
        new->next = list->head->next;
        if(list->head->next) list->head->next->prev = new;
        list->head->next = new;
    } else {
            Node* p = list->head;
            int i;
            for(i = 0; i < pos - 1; i++) p = p->next;
            new->next = p->next;
            new->prev = p;
            p->next = new;
            if(new->next) new->next->prev = new;
        }
    p = new;
    return p;
}

void remNode(List* list, int pos) {
    list->total--;
    if(pos == 1) {
            if(list->total) { //banda nu e goala
                Node *p = list->head->next;
                list->head->next = p->next;
                if(p->next) p->next->prev = list->head;
                free(p);
            } else {
                  list->head->next->ch = '#';
                  list->total = 1;
                }
    } else {
        Node *p = list->head, *q;
        int i;
        for(i = 0; i < pos - 1; i++) p = p->next;
        q = p->next;
        p->next = q->next;
        if(q->next) q->next->prev = p;
        free(q);
    }
}
void freeList(List* list) {
    int i, length = list->total;
    for(i = 0; i <= length; i++) remNode(list, 1);
    free(list->head->next);
    free(list->head);
    free(list);
}

Stack* initStack() {
    Stack* stack = (Stack*) calloc(1, sizeof(Stack));
    stack->total = 0; //primul nod nu poate fi modificat
    stack->last = (Node2*) calloc(1, sizeof(Node2));
    stack->top = stack->last;
    return stack;
}

int pushStack(Stack* stack, Node* finger) {
    Node2 *new = (Node2*) calloc(1, sizeof(Node2));
    new->nptr = finger;
    new->prev = stack->top;
    stack->top->next = new;
    stack->top = new;
    return ++stack->total;
}

int popStack(Stack** stack) {
    Node2 *p = (*stack)->last;
    int pos = 0;
    while(p->next) {
        p = p->next;
        pos++;
    }
    if(!pos) return (*stack)->total;
    p->prev->next = NULL;
    (*stack)->top = p->prev;
    free(p);

    return --(*stack)->total;
}

Node* topStack(Stack* stack) { return stack->top->nptr; }

void freeStack(Stack* stack, int length) {
    int i;
    for(i = 0; i < length; i++) popStack(&stack);
    free(stack->last);
    free(stack);
}

Queue* initQueue() {
    Queue* queue = (Queue*) calloc(1, sizeof(Queue));
    queue->total = 0; //primul nod nu poate fi modificat
    queue->front = (Node3*) calloc(1, sizeof(Node3));
    queue->rear = queue->front;
    return queue;
}

void enqueue(Queue* queue, char* text) {
    Node3 *new = (Node3*) calloc(1, sizeof(Node3));
    strcpy(new->text, text);
    queue->rear->next = new;
    new->prev = queue->rear;
    queue->rear = new;
    queue->total++;
}

char* frontQueue(Queue* queue) { return queue->front->next->text; }

void dequeue(Queue* queue) {
    Node3 *p = queue->front->next;
    queue->front->next = p->next;
    if(p->next) p->next->prev = queue->front;
    else queue->rear = queue->front;
    free(p);
    queue->total--;
}
void freeQueue(Queue* queue) {
    int i, length = queue->total;
    for(i = 0; i < length; i++) dequeue(queue);
    free(queue->front);
    free(queue);
}
