/* NENCIU George-Robert - 313CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operation.h"

Node* moveLeft(List* list, Node* finger, Stack* stackMem) {
    if(finger->prev->ch == '|') {
        printf("ERROR\n");
        return finger;
    } else {
        stackMem->total = pushStack(stackMem, finger);
        return finger->prev;
    }
}

Node* moveRight(List* list, Node* finger, Stack* stackMem) {
    stackMem->total = pushStack(stackMem, finger);
    if(finger->next) return finger->next;
    else return addNode(list, list->total + 1, '#');
}

Node* moveLeftChar(List* list, Node* finger, Stack* stackMem, unsigned char ch) {
    Node *p = finger;
    while(p->ch != ch && p->prev) p = p->prev;
    if(p->ch == ch) {
        stackMem->total = pushStack(stackMem, finger);
        return p;
    }else {
        printf("ERROR\n");
        return finger;
    }
}

Node* moveRightChar(List* list, Node* finger, Stack* stackMem, unsigned char ch) {
    Node *p = finger;
    while(p->ch != ch && p->next) p = p->next;
    if(p->ch == ch) return p;
    else {
        p->next = createNode('#');
        list->total++;
        stackMem->total = pushStack(stackMem, finger);
        return p->next;
    }
}

Node* insertLeftChar(List* list, Node* finger, unsigned char ch) {
    int pos = 0;
    Node *p = finger;
    while(p->ch != '|') {
        p = p->prev;
        pos++;
    }
    addNode(list, pos, ch);
    return finger->prev;
}

Node* insertRightChar(List* list, Node* finger, unsigned char ch) {
    int pos = 0;
    Node *p = finger;
    while(p->ch != '|') {
        p = p->prev;
        pos++;
    }
    addNode(list, pos + 1, ch);
    return finger->next;
}

void writeChar(Node* finger, unsigned char ch) { finger->ch = ch; }

void show(List* list, Node* finger) {
    int pos = 0, i;
    Node *p = finger;
    while(p->ch != '|') {
        p = p->prev;
        pos++;
    }
    p = list->head->next;
    for(i = 1; i < pos; i++) {
        printf("%c", p->ch);
        p = p->next;
    }
    printf("|%c|", finger->ch);
    p = finger->next;
    while(p) {
        printf("%c", p->ch);
        p = p->next;
    }
    printf("\n");
}
void showCurrent(Node* finger) { printf("%c\n", finger->ch); };

Node* undo(Stack* stackUndo, Stack* stackRedo, Node* finger) {
    Node* old = topStack(stackUndo);
    popStack(&stackUndo);
    pushStack(stackRedo, finger);
    return old;
}

Node* redo(Stack* stackUndo, Stack* stackRedo, Node* finger) {
    Node* old = topStack(stackRedo);
    popStack(&stackRedo);
    pushStack(stackRedo, finger);
    return old;
}

Node* execute(Queue* queueExec, Node* finger, Stack** stackUndo, Stack** stackRedo, List* list, int* totalU, int* totalR) {
    const char* COMM[] = {"MOVE_LEFT_CHAR", "MOVE_RIGHT_CHAR", "MOVE_LEFT",
                                       "MOVE_RIGHT", "WRITE"};

    char aux[20];
    int pos, i;
    strcpy(aux, frontQueue(queueExec));
    remQueue(queueExec);

    for(i = 0; i < 5; i++) //caut a cata comanda e din lista
            if(strstr(aux, COMM[i])) {
                pos = i + 1; break;
            }

    switch (pos) {
        case 3:
            finger = moveLeft(list, finger, (*stackUndo));
            break;
        case 4:
            finger = moveRight(list, finger, (*stackUndo));
            break;
        case 1:
            finger = moveLeftChar(list, finger, (*stackUndo), aux[15]);
            break;
        case 2:
            finger = moveRightChar(list, finger, (*stackUndo), aux[16]);
            break;
        case 5:
            writeChar(finger, aux[6]);
            (*totalU) = (*stackUndo)->total;
            (*totalR) = (*stackRedo)->total;
            freeStack((*stackUndo), (*stackUndo)->total);
            freeStack((*stackRedo), (*stackRedo)->total);
            (*stackUndo) = initStack();
            (*stackRedo) = initStack();
            break;
    }
    (*totalU) = (*stackUndo)->total;
    (*totalR) = (*stackRedo)->total;
    return finger;
}