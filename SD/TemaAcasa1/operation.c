/* NENCIU George-Robert - 313CC */
#include <stdio.h>
#include <stdlib.h>
#include "operation.h"

Node* moveLeft(List* list, Node* finger, Stack* stackMem) {
    if(finger->prev->ch == '|') {
        printf("ERROR\n");
        return finger;
    } else return finger->prev;
}

Node* moveRight(List* list, Node* finger, Stack* stackMem) {
    if(finger->next) return finger->next;
    finger->next = createNode('#');
    list->total++;
    return finger->next;
}

Node* moveLeftChar(List* list, Node* finger, Stack* stackMem, unsigned char ch) {
    Node *p = finger;
    while(p->ch != ch && p->prev) p = p->prev;
    if(p->ch == ch) return p;
    printf("ERROR\n");
    return finger;
}

Node* moveRightChar(List* list, Node* finger, Stack* stackMem, unsigned char ch) {
    Node *p = finger;
    while(p->ch != ch && p->next) p = p->next;
    if(p->ch == ch) return p;
    p->next = createNode('#');
    list->total++;
    return p->next;
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
Node* undo(/*pass*/);
Node* redo(/*pass*/);
void execute(/*pass*/);