/* NENCIU George-Robert - 313CC */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operation.h"

Node* moveLeft(List* list, Node* finger, Stack* stackMem) {
    if(finger->prev->ch == '|') return finger;
    stackMem->total = pushStack(stackMem, finger); //pt undo / redo
    return finger->prev;
}

Node* moveRight(List* list, Node* finger, Stack* stackMem) {
    stackMem->total = pushStack(stackMem, finger); //pt undo / redo
    if(finger->next) return finger->next;
    else return addNode(list, list->total + 1, '#'); //urmatorul nod
}

Node* moveLeftChar(List* list, Node* finger, Stack* stackMem, unsigned char ch) {
    Node *p = finger;
    while(p->ch != ch && p->prev) p = p->prev;
    if(p->ch == ch) {
        stackMem->total = pushStack(stackMem, finger); //pt undo / redo
        return p;
    }else {
        FILE* dest = fopen("tema1.out", "a");
        fputs("ERROR\n", dest);
        fclose(dest);
        return finger;
    }
}

Node* moveRightChar(List* list, Node* finger, Stack* stackMem, unsigned char ch) {
    Node *p = finger;
    while(p->ch != ch && p->next) p = p->next;
    if(p->ch == ch) return p;
    else {
        addNode(list, list->total + 1, '#');
        stackMem->total = pushStack(stackMem, finger); //pt undo / redo
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
    if(pos == 1) {
        FILE* dest = fopen("tema1.out", "a");
        fputs("ERROR\n", dest);
        fclose(dest);
        return finger;
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
    while(p->ch != '|' && p->prev) { //caut pozitia unde ma aflu
        p = p->prev;
        pos++;
    }
    p = list->head->next;

    FILE* dest = fopen("tema1.out", "a");
    for(i = 1; i < pos; i++) { //afisez pana la pozitia curenta normal
        fputc(p->ch, dest);
        p = p->next;
    }
    fputc('|', dest);
    fputc(finger->ch, dest); //afisez caracterul intre |
    fputc('|', dest);
    p = finger->next;
    while(p) {  //afisez restul normal
        fputc(p->ch, dest);
        p = p->next;
    }
    fputc('\n', dest);
    fclose(dest);
}
void showCurrent(Node* finger) {
    FILE* dest = fopen("tema1.out", "a");
    fputc(finger->ch, dest);
    fputc('\n', dest);
    fclose(dest);
};

Node* undo(Stack* stackUndo, Stack* stackRedo, Node* finger, int* totalUndo, int* totalRedo) {
    Node* old = topStack(stackUndo);
    (*totalRedo) = pushStack(stackRedo, finger);
    (*totalUndo) = popStack(&stackUndo);
    return old;
}

Node* redo(Stack* stackUndo, Stack* stackRedo, Node* finger, int* totalUndo, int* totalRedo) {
    Node* old = topStack(stackRedo);
    (*totalRedo) = popStack(&stackRedo);
    (*totalUndo) = pushStack(stackUndo, finger);
    return old;
}

Node* execute(Queue* queueExec, Node* finger, Stack** stackUndo, Stack** stackRedo, List* list, int* totalU, int* totalR) {
    const char* COMM[] = {"MOVE_LEFT_CHAR", "MOVE_RIGHT_CHAR", "MOVE_LEFT",
                       "MOVE_RIGHT", "WRITE", "INSERT_LEFT", "INSERT_RIGHT"};

    char aux[20];
    int pos, i;
    strcpy(aux, frontQueue(queueExec));
    dequeue(queueExec);

    for(i = 0; i < 7; i++) //caut a cata comanda e din lista
            if(strstr(aux, COMM[i])) {
                pos = i + 1; break;
            }

    switch (pos) { //executarea operatiilor cerute
        case 1:
            finger = moveLeftChar(list, finger, (*stackUndo), aux[15]);
            break;
        case 2:
            finger = moveRightChar(list, finger, (*stackUndo), aux[16]);
            break;
        case 3:
            finger = moveLeft(list, finger, (*stackUndo));
            break;
        case 4:
            finger = moveRight(list, finger, (*stackUndo));
            break;
        case 5:
            writeChar(finger, aux[6]);
            freeStack((*stackUndo), (*stackUndo)->total); //trebuie sa golesc stivele...
            freeStack((*stackRedo), (*stackRedo)->total);
            (*stackUndo) = initStack();
            (*stackRedo) = initStack();
            break;
        case 6:
                finger = insertLeftChar(list, finger, aux[12]);
                break;
        case 7:
                finger = insertRightChar(list, finger, aux[13]);
                break;
    }
    (*totalU) = (*stackUndo)->total;
    (*totalR) = (*stackRedo)->total;
    return finger;
}