/* NENCIU George-Robert - 313CC */
#ifndef OPERATION_H
#define OPERATION_H
#include "list.h"

Node* moveLeft(List* list, Node* finger, Stack* stackMem);
Node* moveRight(List* list, Node* finger, Stack* stackMem);
Node* moveLeftChar(List* list, Node* finger, Stack* stackMem, unsigned char ch);
Node* moveRightChar(List* list, Node* finger, Stack* stackMem, unsigned char ch);
Node* insertLeftChar(List* list, Node* finger, unsigned char ch);
Node* insertRightChar(List* list, Node* finger, unsigned char ch);
void writeChar(Node* finger, unsigned char ch);
void show(List* list, Node* finger);
void showCurrent(Node* finger);
Node* undo(Stack* stackUndo, Stack* stackRedo, Node* finger, int* totalUndo, int* totalRedo);
Node* redo(Stack* stackUndo, Stack* stackRedo, Node* finger, int* totalUndo, int* totalRedo);
Node* execute(Queue* queueExec, Node* finger, Stack** stackUndo, Stack** stackRedo, List* list, int* totalU, int* totalR);

#endif